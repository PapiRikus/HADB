//
// Created by richard on 11/06/17.
//

#include "Almacenamiento.h"
// Implementación de la clase Datos.
void Datos::Guardar(bool &x) {
    // Insertar al final:
    clear();
    seekg(0, ios::end);
    write(reinterpret_cast<char *> (&x), sizeof(bool));
}

bool Datos::Recupera(long n, bool &x) {
    clear();
    seekg(n*sizeof(bool), ios::beg);
    read(reinterpret_cast<char *> (&x), sizeof(bool));
    return gcount() > 0;
}

// Marca el registro como borrado:
void Datos::editar(long n, bool &x) {

    clear();

    seekg(n*sizeof(bool), ios::beg);
    write(reinterpret_cast<char *> (&x), sizeof(bool));
}


// Este metodo es el que crea las tablas;
long Datos::crearTabla(int indice) {
    string value = pasarIntBinario(indice);
    long posicion = 1;
    int x = 1;
    bool p = true;
    while(p){
            if(!(this->recuperarEntero(posicion)=="")){
                x = x + 1;
                posicion =  posicion + this->tamanoTabla;
            }else{
                p = false;
            }
        }
    this->escribirEntero(value,posicion);
    string valor = pasarIntBinario(x);
    this->escribirEntero(valor, posicion + 32);
    this->cantidadGeneral = cantidadGeneral + 1;
    return x;
}

/**
 * This function add data in tables
 * @param tabla
 * @param indicecolumna
 * @param valor
 */
/*void Datos::agregarFila(int tabla, int indicecolumna, string valor) {
    string value = pasarIntBinario(tabla);
    long posicion = 1;
    bool p = true;
    while(p){
        if(!(this->recuperarEntero(posicion)=="")){
            posicion =  posicion + this->tamanoTabla;
        }else{
            p = false;
        }
    }
    this->escribirEntero(value,posicion);
    string valor = pasarIntBinario(this->cantidadGeneral);
    this->escribirEntero(valor, posicion + 32);
    this->cantidadGeneral = cantidadGeneral + 1;
}*/


bool Datos::recuperarAux(long posicion) {
    bool x;
    this->Recupera(posicion,x);
        if(x == true){
            return true;
        }if(x == false){
            return false;
        }else{
        return false;
    }


}

string Datos::recuperarEntero(long posicion) {
    string retorno = "";
    cout << retorno;
    int x = 0;
    while(x < 32){
        if(recuperarAux(posicion)){
            retorno = retorno + "1";
        }else {
            retorno = retorno + "0";
        }


        x = x+1;
        posicion = posicion + 1;
    }
    retorno = this->cortarString(retorno);
    return retorno;
}

string Datos::recuperarCaracteres(long posicion) {
    string retorno = "";
    cout << retorno;
    int x = 0;
    while(x < this->bloqueString){
        if(recuperarAux(posicion)){
            retorno = retorno + "1";
        }else {
            retorno = retorno + "0";
        }


        x = x+1;
        posicion = posicion + 1;
    }
    retorno = this->cortarString(retorno);
    return retorno;
}




string Datos::cortarString(string string1) {
    string retorno = "";
    int x = 0;
    bool activar = false;
    while(x < string1.size()){
        if(!activar){
            if(string1[x] == '1'){
                activar = true;

            }

        }if(activar){
            retorno = retorno + string1[x];
        }

        x = x + 1;
    }
    return retorno;
}
/**
 * esta clase escribe los enteros en el disco,
 * @param std
 * @param posicion
 */

void Datos::escribirEntero(string std, long posicion) {
    int ciclo = 0;
    bool QEscribir;
    while(ciclo < std.size()){
        if(std[ciclo] == '1'){
            QEscribir = true;
        }else if(std[ciclo]== '0'){
            QEscribir = false;
        }
        this->editar(posicion+(32-std.size()), QEscribir);
        posicion = posicion + 1;
        ciclo = ciclo + 1;
    }

}


void Datos::eliminarCaracter(long posicion) {
    bool escritura = false;
    int x = 0;
    while (x < this->bloqueString){
        this->editar(posicion, escritura);
        posicion++;
        x++;
    }
}


void Datos::eliminarEntero(long posicion) {
    bool escritura = false;
    int x = 0;
    while (x < this->bloqueEntero){
        this->editar(posicion, escritura);
        posicion++;
        x++;
    }
}



bool Datos::EliminarFila(int indiceTabla, int posicion) {
    string tabla = pasarIntBinario(indiceTabla);
    long pos = 1;
    while(this->recuperarEntero(pos)!="") {
        if ((this->recuperarEntero(pos) == tabla)){
            cout<<endl<<"valor: "<<this->recuperarEntero(pos + 32)<<endl;
            if(this->recuperarEntero(pos + 32) == this->pasarIntBinario(posicion)){
                this->eliminarEntero(pos);
                this->eliminarEntero(pos + this->bloqueEntero);
                int x = 0;
                while(x<10){
                    this->eliminarCaracter(pos + 64 +(this->bloqueString*x));
                    x = x+1;
                }
            }
        }
        pos = pos + this->tamanoTabla;
    }
}


/**
 * este metodo escribe los caracteres en el 'disco' asigna 2048 bits
 * @param std
 * @param posicion
 */


void Datos::escribirCaracteres(string std, long posicion) {
    int ciclo = 0;
    bool QEscribir;
    while(ciclo < std.size()){
        if(std[ciclo] == '1'){
            QEscribir = true;
        }else if(std[ciclo]== '0'){
            QEscribir = false;
        }
        this->editar(posicion+(this->bloqueString-std.size()), QEscribir);
        posicion = posicion + 1;
        ciclo = ciclo + 1;
    }

}

/**
 * is used to insert data
 * @param indice
 * @param posicion
 * @param dato
 */
void Datos::agregarDatoColumna(int indiceTabla, int posicion,int locacion , string dato) {

    long pos = 1;
    int x;
    string tabla = pasarIntBinario(indiceTabla);
    while(this->recuperarEntero(pos)!="") {
        if ((this->recuperarEntero(pos) == tabla)){
            if(this->recuperarEntero(pos + 32) == this->pasarIntBinario(posicion)){
                long valor = pos + this->bloqueString*(locacion-1) + 64;
                cout<<" se agrega el dato: "<<dato <<" en la tabla: "<< "en la columna: " << posicion << " en la locacion: " <<locacion;
               // this->eliminarCaracter(valor);
                this->escribirCaracteres(dato, valor);

                break;
            }
        }
        pos = pos + this->tamanoTabla;
    }

}

void Datos::eliminarDatoColumna(int indiceTabla, int posicion,int locacion) {

    long pos = 1;
    int x;
    string tabla = pasarIntBinario(indiceTabla);
    while(this->recuperarEntero(pos)!="") {
        if ((this->recuperarEntero(pos) == tabla)){
            if(this->recuperarEntero(pos + 32) == this->pasarIntBinario(posicion)){
                long valor = pos + this->bloqueString*(locacion-1) + 64;
                this->eliminarCaracter(valor);
                
                break;
            }
        }
        pos = pos + this->tamanoTabla;
    }

}

string Datos::BuscarDatoColumna(int indiceTabla, int posicion,int locacion) {

    long pos = 1;
    string retorno;
    int x;
    string tabla = pasarIntBinario(indiceTabla);
    while(this->recuperarEntero(pos)!="") {
        if ((this->recuperarEntero(pos) == tabla)){
            if(this->recuperarEntero(pos + 32) == this->pasarIntBinario(posicion)){
                long valor = pos + this->bloqueString*(locacion-1) + 64;
                retorno = this->recuperarCaracteres(valor);
                break;
            }
        }
        pos = pos + this->tamanoTabla;
    }
    return retorno;

}
/**
 * este metodo pasa los enteros a binario
 * @param numero
 * @return
 */
string Datos::pasarIntBinario(int numero) {
    int dividendo, resto, divisor = 2;
    string binario = "";

    dividendo = numero;
    while(dividendo >= divisor){ //Mientras el dividendo sea mayor o igual que el divisor, es decir, mayor o igual que 2.
        resto = dividendo % 2;
        if(resto == 1)
            binario = "1" + binario; //Si el resto es igual a 1 concatenamos 1 a la variable string llamada binario
        else
            binario = "0" + binario; // Sino concatenamos 0
        //Es importante este orden de concatenación (primero el bit y luego el valor de la variable) esto para que nuestro número
        //en sistema binario esté ordenado correctamente.
        dividendo = dividendo/divisor; // Actualizamos el valor del dividendo dividiendolo entre 2.
    }
    if(dividendo == 1)
        binario = "1" + binario; // Por último sí el valor final del dividendo es 1 concatenamos 1 sino concatenamos 0.
    else
        binario = "0" + binario;
    return binario;
}