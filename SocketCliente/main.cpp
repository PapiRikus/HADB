/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: cp
 *
 * Created on 22 de mayo de 2017, 07:46 PM
 */

#include <cstdlib>
#include "SocketCliente.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    SocketCliente* conexion;
    conexion=new SocketCliente();
    conexion->conectar();
   // conexion->setMensaje("Hol servidor6");
    cout<<"Conexion con server"<<endl;
    while(1){
       string mensaje;
       cin >>mensaje;
       const char* msj=mensaje.c_str();
       conexion->setMensaje(msj);
     //conexion->setMensaje("Hola servidor6");
     
   
    }
  
    return 0;
}

