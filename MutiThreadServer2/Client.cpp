/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Client.cpp
 * Author: cp
 * 
 * Created on 29 de mayo de 2017, 07:41 PM
 */

#include "Client.h"

using namespace std;

Client::Client() {
  this->name = (char *) malloc(MAX_NAME_LENGHT+1);
  
}

void Client::SetName(const char *name) {
  //Copies at most MAX_NAME_LENGHT + 1 (including '\0')
  snprintf(this->name, MAX_NAME_LENGHT+1, name);
}

void Client::SetId(int id) {
  this->id = id;
}
void Client::SetEdad(int edad){
    this->edad=edad;
}


