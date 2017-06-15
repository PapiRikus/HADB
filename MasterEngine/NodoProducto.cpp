/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodoProducto.cpp
 * Author: aaronsolera
 * 
 * Created on 15 de junio de 2017, 07:26 AM
 */

#include "NodoProducto.h"


// Constructor
NodoProducto::NodoProducto(){
    Codigo      = 0;
    Precio      = 0;
    Descripcion = "";
}
// Constructor
NodoProducto::NodoProducto(int cod, int pres, std::string des){
    Codigo      = cod;
    Precio      = pres;
    Descripcion = des;
}

