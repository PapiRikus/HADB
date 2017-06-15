/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "HuffmanCompresor.h"
#include <stdio.h>

void HuffmanCompresor::compress(char* in_file, char* out_file) {
    tipoNodo *Lista;       /* Lista de letras y frecuencias */
    tipoNodo *Arbol;       /* Arbol de letras y frecuencias */

    FILE *fe, *fs;         /* Ficheros de entrada y salida */
    char c;                /* variables auxiliares */
    tipoNodo *p;
    tipoTabla *t;
    int nElementos;        /* Número de elementos en tabla */
    long int Longitud = 0; /* Longitud del fichero original */

    unsigned long int dWORD; /* Soble palabra usada durante la codificación */
    int nBits;               /* Número de bits usados de dWORD */

    Lista = NULL;
    /* Fase 1: contar frecuencias */
    fe = fopen(in_file, "r");
    while((c = fgetc(fe)) != EOF)
    {
        Longitud++;       /* Actualiza la cuenta de la longitud del fichero */
        Cuenta(Lista, c); /* Actualiza la lista de frecuencias */
    }
    fclose(fe);

    /* Ordenar la lista de menor a mayor */
    Ordenar(Lista);

    /* Crear el arbol */
    Arbol = Lista;
    while(Arbol && Arbol->sig) /* Mientras existan al menos dos elementos en la lista */
    {
        p = (tipoNodo *)malloc(sizeof(tipoNodo)); /* Un nuevo árbol */
        p->letra = 0;                             /* No corresponde a ninguna letra */
        p->uno = Arbol;                           /* Rama uno */
        Arbol = Arbol->sig;                       /* Siguiente nodo en */
        p->cero = Arbol;                          /* Rama cero */
        Arbol = Arbol->sig;                       /* Siguiente nodo */
        p->frecuencia = p->uno->frecuencia +
                        p->cero->frecuencia;      /* Suma de frecuencias */
        InsertarOrden(Arbol, p);                  /* Inserta en nuevo nodo */
    }                                            /* orden de frecuencia */

    /* Construir la tabla de códigos binarios */
    Tabla = NULL;
    CrearTabla(Arbol, 0, 0);

    /* Crear fichero comprimido */
    fs = fopen(out_file, "wb");
    /* Escribir la longitud del fichero */
    fwrite(&Longitud, sizeof(long int), 1, fs);
    /* Cuenta el número de elementos de tabla */
    nElementos = 0;
    t = Tabla;
    while(t)
    {
        nElementos++;
        t = t->sig;
    }
    /* Escribir el número de elemenos de tabla */
    fwrite(&nElementos, sizeof(int), 1, fs);
    /* Escribir tabla en fichero */
    t = Tabla;
    while(t)
    {
        fwrite(&t->letra, sizeof(char), 1, fs);
        fwrite(&t->bits, sizeof(unsigned long int), 1, fs);
        fwrite(&t->nbits, sizeof(char), 1, fs);
        t = t->sig;
    }

    /* Codificación del fichero de entrada */
    fe = fopen(in_file, "r");
    dWORD = 0; /* Valor inicial. */
    nBits = 0; /* Ningún bit */
    while((c = fgetc(fe)) != EOF)
    {
        /* Busca c en tabla: */
        t = BuscaCaracter(Tabla, c);
        /* Si nBits + t->nbits > 32, sacar un byte */
        while(nBits + t->nbits > 32)
        {
            c = dWORD >> (nBits-8);           /* Extrae los 8 bits de mayor peso */
            fwrite(&c, sizeof(char), 1, fs);  /* Y lo escribe en el fichero */
            nBits -= 8;                       /* Ya tenemos hueco para 8 bits más */
        }
        dWORD <<= t->nbits; /* Hacemos sitio para el nuevo caracter */
        dWORD |= t->bits;   /* Insertamos el nuevo caracter */
        nBits += t->nbits;  /* Actualizamos la cuenta de bits */
    }
    /* Extraer los cuatro bytes que quedan en dWORD*/
    while(nBits>0)
    {
        if(nBits>=8) c = dWORD >> (nBits-8);
        else c = dWORD << (8-nBits);
        fwrite(&c, sizeof(char), 1, fs);
        nBits -= 8;
    }

    fclose(fe);  /* Cierra los ficheros */
    fclose(fs);

    /* Borrar Arbol */
    BorrarArbol(Arbol);

    /* Borrar Tabla */
    while(Tabla)
    {
        t = Tabla;
        Tabla = t->sig;
        free(t);
    }
}

void HuffmanCompresor::decompress(char* in_file, char* out_file) {
    tipoTNodo *Arbol;        /* Arbol de codificación */
    long int Longitud;      /* Longitud de fichero */
    int nElementos;         /* Elementos de árbol */
    unsigned long int bits; /* Almacen de bits para decodificación */
    FILE *fe, *fs;          /* Ficheros de entrada y salida */

    tipoTNodo *p, *q;        /* Auxiliares */
    unsigned char a;
    int i, j;

    /* Crear un arbol con la información de la tabla */
    Arbol = (tipoTNodo *)malloc(sizeof(tipoTNodo)); /* un nodo nuevo */
    Arbol->letra = 0;
    Arbol->uno = Arbol->cero = NULL;
    fe = fopen(in_file, "rb");
    fread(&Longitud, sizeof(long int), 1, fe); /* Lee el número de caracteres */
    fread(&nElementos, sizeof(int), 1, fe); /* Lee el número de elementos */
    for(i = 0; i < nElementos; i++) /* Leer todos los elementos */
    {
        p = (tipoTNodo *)malloc(sizeof(tipoTNodo)); /* un nodo nuevo */
        fread(&p->letra, sizeof(char), 1, fe); /* Lee el carácter */
        fread(&p->bits, sizeof(unsigned long int), 1, fe); /* Lee el código */
        fread(&p->nbits, sizeof(char), 1, fe); /* Lee la longitud */
        p->cero = p->uno = NULL;
        /* Insertar el nodo en su lugar */
        j = 1 << (p->nbits-1);
        q = Arbol;
        while(j > 1)
        {
            if(p->bits & j) /* es un uno*/
                if(q->uno) q = q->uno;   /* Si el nodo existe, nos movemos a él */
                else                     /* Si no existe, lo creamos */
                {
                    q->uno = (tipoTNodo *)malloc(sizeof(tipoTNodo)); /* un nodo nuevo */
                    q = q->uno;
                    q->letra = 0;
                    q->uno = q->cero = NULL;
                }
            else /* es un cero */
            if(q->cero) q = q->cero; /* Si el nodo existe, nos movemos a él */
            else                     /* Si no existe, lo creamos */
            {
                q->cero = (tipoTNodo *)malloc(sizeof(tipoTNodo)); /* un nodo nuevo */
                q = q->cero;
                q->letra = 0;
                q->uno = q->cero = NULL;
            }
            j >>= 1;  /* Siguiente bit */
        }
        /* Ultimo Bit */
        if(p->bits & 1) /* es un uno*/
            q->uno = p;
        else            /* es un cero */
            q->cero = p;
    }
    /* Leer datos comprimidos y extraer al fichero de salida */
    bits = 0;
    fs = fopen(out_file, "w");
    /* Lee los primeros cuatro bytes en la dobel palabra bits */
    fread(&a, sizeof(char), 1, fe);
    bits |= a;
    bits <<= 8;
    fread(&a, sizeof(char), 1, fe);
    bits |= a;
    bits <<= 8;
    fread(&a, sizeof(char), 1, fe);
    bits |= a;
    bits <<= 8;
    fread(&a, sizeof(char), 1, fe);
    bits |= a;
    j = 0; /* Cada 8 bits leemos otro byte */
    q = Arbol;
    /* Bucle */
    do {
        if(bits & 0x80000000) q = q->uno; else q = q->cero; /* Rama adecuada */
        bits <<= 1;           /* Siguiente bit */
        j++;
        if(8 == j)            /* Cada 8 bits */
        {
            i = fread(&a, sizeof(char), 1, fe); /* Leemos un byte desde el fichero */
            bits |= a;                    /* Y lo insertamos en bits */
            j = 0;                        /* No quedan huecos */
        }
        if(!q->uno && !q->cero)          /* Si el nodo es una letra */
        {
            putc(q->letra, fs);           /* La escribimos en el fich de salida */
            Longitud--;                   /* Actualizamos longitud que queda */
            q=Arbol;                      /* Volvemos a la raiz del árbol */
        }
    } while(Longitud);                  /* Hasta que acabe el fichero */
    /* Procesar la cola */

    fclose(fs);                         /* Cerramos ficheros */
    fclose(fe);

    BorrarArbol(Arbol);                 /* Borramos el árbol */
}

/* Actualiza la cuenta de frecuencia del carácter c */
/* El puntero a Lista se pasa por referencia, ya que debe poder cambiar */
/* Ya sea por que la lista esté vacía, o porque el nuevo elemento sea el */
/* primero */
void HuffmanCompresor::Cuenta(tipoNodo* &Lista, char c)
{
    tipoNodo *p, *a, *q;

    if(!Lista)  /* Si la lista está vacía, el nuevo nodo será Lista */
    {
        Lista = (tipoNodo *)malloc(sizeof(tipoNodo)); /* Un nodo nuevo */
        Lista->letra = c;                             /* Para c */
        Lista->frecuencia = 1;                        /* en su 1ª aparición */
        Lista->sig = Lista->cero = Lista->uno = NULL;
    }
    else
    {
        /* Buscar el caracter en la lista (ordenada por letra) */
        p = Lista;
        a = NULL;
        while(p && p->letra < c)
        {
            a = p;      /* Guardamos el elemento actual para insertar */
            p = p->sig; /* Avanzamos al siguiente */
        }
        /* Dos casos: */
        /* 1) La letra es c se encontró */
        if(p && p->letra == c) p->frecuencia++; /* Actualizar frecuencia */
        else
            /* 2) La letra c no se encontró*/
        {
            /* Insertar un elemento nuevo */
            q = (tipoNodo *)malloc(sizeof(tipoNodo));
            q->letra = c;
            q->frecuencia = 1;
            q->cero = q->uno = NULL;
            q->sig = p;        /* Insertar entre los nodos p */
            if(a) a->sig = q;  /* y a */
            else Lista = q;    /* Si a es NULL el nuevo es el primero */
        }
    }
}

/* Ordena Lista de menor a mayor por frecuencias */
/* De nuevo pasamos el puntero a lista por referencia */
void HuffmanCompresor::Ordenar(tipoNodo* &Lista)
{
    tipoNodo *Lista2, *a;

    if(!Lista) return; /* Lista vacia */
    Lista2 = Lista;
    Lista = NULL;
    while(Lista2)
    {
        a = Lista2;              /* Toma los elementos de Lista2 */
        Lista2 = a->sig;
        InsertarOrden(Lista, a); /* Y los inserta por orden en Lista */
    }
}

/* Inserta el elemento e en la Lista ordenado por frecuencia de menor a mayor */
/* El puntero a Cabeza se pasa por referencia */
void HuffmanCompresor::InsertarOrden(tipoNodo* &Cabeza, tipoNodo *e)
{
    tipoNodo *p, *a;

    if(!Cabeza) /* Si Cabeza en NULL, e es el primer elemento */
    {
        Cabeza = e;
        Cabeza->sig = NULL;
    }
    else
    {
        /* Buscar el caracter en la lista (ordenada por frecuencia) */
        p = Cabeza;
        a = NULL;
        while(p && p->frecuencia < e->frecuencia)
        {
            a = p;      /* Guardamos el elemento actual para insertar */
            p = p->sig; /* Avanzamos al siguiente */
        }
        /* Insertar el elemento */
        e->sig = p;
        if(a) a->sig = e;   /* Insertar entre a y p */
        else Cabeza = e;    /* el nuevo es el primero */
    }
}

/* Función recursiva para crear Tabla */
/* Recorre el árbol cuya raiz es n y le asigna el código v de l bits */
void HuffmanCompresor::CrearTabla(tipoNodo *n, int l, int v)
{
    if(n->uno)  CrearTabla(n->uno, l+1, (v<<1)|1);
    if(n->cero) CrearTabla(n->cero, l+1, v<<1);
    if(!n->uno && !n->cero) InsertarTabla(n->letra, l, v);
}

/* Insertar un elemento en la tabla */
void HuffmanCompresor::InsertarTabla(char c, int l, int v)
{
    tipoTabla *t, *p, *a;

    t = (tipoTabla *)malloc(sizeof(tipoTabla)); /* Crea un elemento de tabla */
    t->letra = c;                               /* Y lo inicializa */
    t->bits = v;
    t->nbits = l;

    if(!Tabla)         /* Si tabla es NULL, entonces el elemento t es el 1º */
    {
        Tabla = t;
        Tabla->sig = NULL;
    }
    else
    {
        /* Buscar el caracter en la lista (ordenada por frecuencia) */
        p = Tabla;
        a = NULL;
        while(p && p->letra < t->letra)
        {
            a = p;      /* Guardamos el elemento actual para insertar */
            p = p->sig; /* Avanzamos al siguiente */
        }
        /* Insertar el elemento */
        t->sig = p;
        if(a) a->sig = t;  /* Insertar entre a y p */
        else Tabla = t;    /* el nuevo es el primero */
    }
}

/* Buscar un caracter en la tabla, devielve un puntero al elemento de la tabla */
tipoTabla* HuffmanCompresor::BuscaCaracter(tipoTabla *Tabla, char c)
{
    tipoTabla *t;

    t = Tabla;
    while(t && t->letra != c) t = t->sig;
    return t;
}

/* Función recursiva para borrar un arbol */
void HuffmanCompresor::BorrarArbol(tipoNodo *n)
{
    if(n->cero) BorrarArbol(n->cero);
    if(n->uno)  BorrarArbol(n->uno);
    free(n);
}
void HuffmanCompresor::BorrarArbol(tipoTNodo *n)
{
    if(n->cero) BorrarArbol(n->cero);
    if(n->uno)  BorrarArbol(n->uno);
    free(n);
}

string HuffmanCompresor::compress(string to_compress) {
    FILE *f = fopen("String.txt", "w");
    for (int i = 0; i < to_compress.length(); ++i) {
        putc(to_compress[i],f);
    }
    fclose(f);
    compress("String.txt","compresedString");
    f = fopen("compresedString", "rt");
    char c;
    string rc;
    while (c!=EOF)
    {
        c=fgetc(f);
        rc+=c;
    }
    fclose(f);
    return rc;
}

string HuffmanCompresor::decompress(string to_compress) {
    FILE *f = fopen("cString", "wt");
    for (int i = 0; i < to_compress.length(); ++i) {
        putc(to_compress[i],f);
    }
    fclose(f);
    decompress("cString","dString.txt");
    f = fopen("dString.txt", "rt");
    char c;
    string rc;
    while (c!=EOF)
    {
        c=fgetc(f);
        rc+=c;
    }
    fclose(f);
    return rc;
}

