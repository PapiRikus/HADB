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
void Datos::crearTabla(int indice) {
    string value = pasarIntBinario(indice);
    long posicion = 1;
    bool p = true;
    while(p){
            if(!(this->recuperarEntero(posicion)=="")){
                posicion =  posicion + this->tamanoTabla;
            }else{
                p = false;
            }
        }
    this->escribirString(value,posicion);
}




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


void Datos::escribirString(string std, long posicion) {
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






void Datos::agregarColumna(int indice) {
    string tabla = this->pasarIntBinario(indice);
    long posicion = 1;
    int x;
    while(this->recuperarEntero(posicion)!="") {
            if ((this->recuperarEntero(posicion) == tabla)) {

                x = 1;
                while (x <= 10) {
                    if (this->recuperarEntero(posicion + 32*x) == "") {
                        string indiceTabla = this->pasarIntBinario(x);
                        this->escribirString(indiceTabla, posicion + 32*x);
                        cout<<"agrega Columna: "<< x ;
                        break;
                    }
                    x = x+1;
                }
            }
        posicion = posicion + this->tamanoTabla;
    }
}






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