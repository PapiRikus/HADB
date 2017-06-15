#include "ArbolBmas.h"//
// Created by richard on 24/05/17.
//

ArbolBmas::ArbolBmas(): fstream("alea.dat", ios::in | ios::out | ios::binary){
    if(!good()) {
        open("alea.dat", ios::in | ios::out | ios::trunc | ios::binary);
        cout << "fichero creado" << endl;
        cin.get();
    }
    cuentas = k = 0;
    esta    = ea = false;
    MAX     = 4;
    MIN     = 2;
    nivel   =0;
    vsam    = raiz = P = N = Xr = NULL;
    contT= contTot=bandera = bandera2 = eli =0;
}
#include "ArbolBmas.h"
// Metodo refrescar
void ArbolBmas::refrescar(){
    nivel = Altura ();
    NodoBmas *aux = raiz;

    while (!arbolVacio(aux->ramas[0]))
        aux= aux->ramas[0];

    vsam = aux;
}

// Metodo de Insertar
void ArbolBmas::insertar (NodoProducto clave){
    ea = false;
    empujar (clave, raiz);
    if(ea){
        NodoBmas *nuevo = new NodoBmas();
        nuevo->cuentas = 1;
        nuevo->claves[1] = mediana;
        nuevo->ramas [0] = raiz;
        nuevo->ramas [1] = Xr;
        raiz = nuevo;
    }
    refrescar();
}

// Metodo Empujar
void ArbolBmas::empujar (NodoProducto clave, NodoBmas *nodo){
    if(nodo == NULL){
        ea= true;
        mediana= clave;
        Xr= NULL;
    }
    else{
        esta = buscarNodo (clave, nodo);
        if(esta)
            std::cout << "\nCodigo Repetido: "<< clave.Codigo << std::endl;
        else{
            empujar (clave, nodo->ramas[k]);
            buscarNodo(clave, nodo);

            if(ea){
                if(nodo->cuentas < MAX){
                    //cout << "Voy a meterhoja!" <<endl;
                    ea = false;
                    P = nodo;
                    // Usa las variables globales
                    meterHoja();
                }
                else{
                    //cout << "Voy a dividir!" << endl;
                    ea = true;
                    P = nodo;
                    // Usa las variables globales.
                    dividir();
                }
            }
        }
    }
}

// Metodo Meter Hoja que usa las variables globales: Mediana, P, K, Xr
void ArbolBmas::meterHoja(){
    for(int i = P->cuentas; i >= k + 1; i--){
        P->claves[i + 1] = P->claves[i];
        P->ramas [i + 1] = P->ramas [i];
    }
    P->claves[k + 1] = mediana;
    P->ramas [k + 1] = Xr;
    P->cuentas++;
}

// Metodo Dividir Nodo que usa las variables asignadas por Meter Hoja Mediana, P, K, Xr.
void ArbolBmas::dividir(){
    NodoBmas *mde = new NodoBmas();
    int pos;

    if (k <= MIN)
        pos= MIN;
    else
        pos= MIN+1;

    for(int i= pos+1; i <= MAX; i++){
        mde->claves[i-pos] = P->claves[i];
        mde->ramas [i-pos] = P->ramas [i];
    }

    mde->cuentas = MAX-pos;
    P->cuentas = pos;

    if (k <= MIN)
        meterHoja();
    else{
        k = k-pos;
        NodoBmas *aux = P;
        P = mde;
        meterHoja();
        P = aux;
    }
    mediana = P->claves[P->cuentas];

    if(arbolVacio(P->ramas[0]))
        doblar(mde);

    mde->ramas[0] = P->ramas[P->cuentas];
    mde->shojas = P->shojas;
    P->shojas = mde;

    P->cuentas--;
    Xr= mde;
}

// Metodo que duplica un Nodo
void ArbolBmas::doblar (NodoBmas *mde){
    for(int i = mde->cuentas; i >= 1; i--){
        mde->claves[i + 1] = mde->claves[i];
        mde->ramas [i + 1] = mde->ramas [i];
    }
    mde->claves[ 1] = mediana;
    mde->cuentas++;
}

// Metodo Arbol Vacio
bool ArbolBmas::arbolVacio(NodoBmas *nodo){
    return ((nodo == NULL) || (nodo->cuentas == 0));
}

// Metodo buscar que retorna si el nodo existe o no
bool ArbolBmas::buscar(NodoProducto clave){
    return buscarNodo (clave, raiz);
}

// Metodo buscar que retorna si el nodo existe o no
bool ArbolBmas::buscar(NodoProducto clave, NodoBmas *nodo){
    if(nodo->cuentas == 0)
        esta = false;
    else{
        buscarNodo(clave, nodo);
        if(esta)
            N= nodo;
        else
            esta = buscar(clave, nodo->ramas[k]);
    }
    return esta;
}

// Metodo buscar nodo
bool ArbolBmas::buscarNodo(NodoProducto clave, NodoBmas *nodo){
    if(nodo == NULL)
        return false;
    else{
        if(clave.Codigo < nodo->claves[1].Codigo){
            k = 0;
            return esta = false;
        }
        else{
            k = nodo->cuentas;
            while((k > 1) && (clave.Codigo <nodo->claves[k].Codigo))
                k--;

            esta = (clave.Codigo == nodo->claves[k].Codigo);
        }
        return esta;
    }
}

// Realiza un Imprimir Recursivo
void ArbolBmas::print_rec (){
    if (!arbolVacio(raiz)){
        print_rec_aux(raiz);
        std::cout << std::endl;
    }
    else
        std::cout << "\nEl Arbol B+ esta Vacio!" << std::endl;
}

// Metodo auxiliar de print_rec
void ArbolBmas::print_rec_aux (NodoBmas *nodo){
    if(!arbolVacio(nodo)){
        print_rec_aux (nodo->ramas[0]);
        for(int i = 1; i <= nodo->cuentas; i++){
            std::cout << nodo->claves[i].Codigo << " ";
            print_rec_aux (nodo->ramas[i]);
        }
    }
}

// Metodo que retorna la Altura del arbol B+
int ArbolBmas::Altura (){
    int res = 0;
    NodoBmas *aux = raiz;
    if (arbolVacio(aux)){
        std::cout << "\nEl Arbol B+ esta Vacio!" << std::endl;
        return 0;
    }
    else{
        while (!arbolVacio(aux)){
            res++;
            aux = aux->ramas[0];
        }
        return res;
    }
}


// Realiza el recorrido en Anchura
void ArbolBmas:: Anchura(){
    int largo = Altura();
    int con = 1;
    NodoBmas *pg = raiz;
    std::cout<<"Impresion del arbol B+ en anchura:"<<std::endl;
    Anchura_aux (pg, largo, con);
    std::cout << std::endl;
}

// Metodo auxiliar de Anchura
void ArbolBmas:: Anchura_aux (NodoBmas *nodo, int largo, int con){
    if (arbolVacio(nodo)){
    }
    else{
        if (largo >= con){
            std::cout<<std::endl;
            ImprimeNivel (nodo, con);
            con++;
            Anchura_aux(nodo,largo, con);
        }
    }
}

void ArbolBmas::ImprimeNivel (NodoBmas *nodo, int con){
    if(arbolVacio(nodo)){
    }
    else{
        std::cout<<"     ";
        if (con == 1){
            for(int i= 1; i<= nodo->cuentas; i++){
                std::cout<<nodo->claves[i].Codigo<<" ";
            }
        }
        else{
            con--;
            for(int r= 0; r <= nodo->cuentas; r++)
                ImprimeNivel(nodo->ramas[r], con);
        }
    }
}

// Metodo Imprimir Arbol B+
void ArbolBmas ::Imprimir (){
    NodoBmas *aux= vsam;
    if (arbolVacio(aux))
        std::cout << "\nEl Arbol B+ esta Vacio!" << std::endl;
    else{
        std::cout<<"Impresion del arbol B+:"<<std::endl;
        while (!arbolVacio(aux)){
            for (int i= 1; i <= aux->cuentas; i++)
                std::cout<<aux->claves[i].Codigo<<" ";
            aux = aux->shojas;
        }
    }
    std::cout << std::endl;
}

/****************************/

bool ArbolBmas::Buscar(int c){
    int i;

    NodoBmas *nodo = vsam;
    while (nodo != NULL){
        i = 0;

        for(; i <= (nodo->cuentas); i++){
            if (nodo->claves[i].Codigo == c){
                return  true;
            }
        }
        nodo = (*nodo).shojas;
    }
    return false;
}

//ve si el el codigo c existe
int ArbolBmas:: Esta(int c){
    int i;
    NodoBmas *nodo = vsam;
    while (nodo != NULL){
        i = 0;
        for(; i <= ((nodo->cuentas) - 1); i++){
            if (nodo->claves[i].Codigo == c)
                return  true;
        }
        nodo = (*nodo).shojas;
    }
    return false;
}

//encuentra y retorna el nodo buscado
NodoProducto* ArbolBmas:: Encontrar(int c){
    int i;
    NodoBmas *nodo = vsam;
    NodoProducto *siesta;
    while (nodo != NULL){
        i = 0;

        for(; i <= (nodo->cuentas); i++){
            if (nodo->claves[i].Codigo == c){
                siesta = new NodoProducto (nodo->claves[i].Codigo ,
                                           nodo->claves[i].Precio, nodo->claves[i].Descripcion);/////ojo
                return  siesta;
            }
        }
        nodo = (*nodo).shojas;
    }
    return NULL;
}

/*******************************************************************************************/
/*******************************************************************************************/

void ArbolBmas::preOrdenRecursivo(NodoBmas *raiz){
    preOrdenRecursivoAux(raiz);
}

/* Realiza un recorrido del arbol de forma iterativa */
void ArbolBmas::preOrdenRecursivoAux(NodoBmas *raiz){

    NodoBmas *pg = raiz;

    if( raiz != NULL ){

        std::cout << pg->claves[1].Codigo << " ";

        // llamada recursiva por la primera hoja
        this->preOrdenRecursivoAux(pg->ramas[0]);

        if(pg->ramas[0] != NULL){
            // llamada recursiva por la primera hoja
            this->preOrdenRecursivoAux(pg->ramas[1]);
        }

        for(int i = 2; i <= pg->cuentas; i++){

            std::cout << pg->claves[i].Codigo  << " ";
            this->preOrdenRecursivoAux(pg->ramas[i]);
        }
    }

}

//fstream file7("PostOrRecBmas.txt", ios::out); //archivo salida de recorrido

void ArbolBmas::postOrdenRecursivo(NodoBmas *raiz){
    postOrdenRecursivoAux(raiz);
}

/* Realiza un recorrido del arbol de forma recursiva */
void ArbolBmas::postOrdenRecursivoAux(NodoBmas *raiz){

    NodoBmas *pg = raiz;

    if( raiz != NULL ){

        // llamada recursiva por la primera hoja
        this->postOrdenRecursivoAux(pg->ramas[0]);

        if(pg->ramas[0] != NULL){
            // llamada recursiva por la primera hoja
            this->postOrdenRecursivoAux(pg->ramas[1]);
        }

        std::cout << pg->claves[1].Codigo << " ";

        for(int i = 2; i <= pg->cuentas; i++){
            this->postOrdenRecursivoAux(pg->ramas[i]);
            std::cout << pg->claves[i].Codigo  << " ";

        }
    }
}
/**************************************************************/

//fstream file8("PreOrIteBmas.txt", ios::out); //archivo salida de recorrido

void ArbolBmas::preOrdenIterativo(NodoBmas *raiz){
    preOrdenIterativoAux(raiz);
}

/* Realiza un recorrido del arbol de forma iterativo */
void ArbolBmas::preOrdenIterativoAux(NodoBmas *raiz){
    NodoBmas *pg = raiz;

    if( raiz != NULL ){

        std::cout << pg->claves[1].Codigo << " ";

        // llamada recursiva por la primera hoja
        this->preOrdenIterativoAux(pg->ramas[0]);

        if(pg->ramas[0] != NULL){
            // llamada recursiva por la primera hoja
            this->preOrdenIterativoAux(pg->ramas[1]);
        }

        for(int i = 2; i <= pg->cuentas; i++){

            std::cout << pg->claves[i].Codigo  << " ";
            this->preOrdenIterativoAux(pg->ramas[i]);
        }
    }

}

//fstream file9("PostOrIteBmas.txt", ios::out); //archivo salida de recorrido

void ArbolBmas::postOrdenIterativo(NodoBmas *raiz){
    postOrdenIterativoAux(raiz);
}

/* Realiza un recorrido del arbol de forma iterativo */
void ArbolBmas::postOrdenIterativoAux(NodoBmas *raiz){
    NodoBmas *pg = raiz;

    if( raiz != NULL ){

        // llamada recursiva por la primera hoja
        this->postOrdenIterativoAux(pg->ramas[0]);

        if(pg->ramas[0] != NULL){
            // llamada recursiva por la primera hoja
            this->postOrdenIterativoAux(pg->ramas[1]);
        }

        std::cout << pg->claves[1].Codigo << " ";

        for(int i = 2; i <= pg->cuentas; i++){
            this->postOrdenIterativoAux(pg->ramas[i]);
            std::cout << pg->claves[i].Codigo  << " ";
        }
    }
}

