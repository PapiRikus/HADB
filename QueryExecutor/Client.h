/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Client.h
 * Author: cp
 *
 * Created on 29 de mayo de 2017, 07:41 PM
 */

#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>

#include <cstdio>
#include <cstdlib>

#define MAX_NAME_LENGHT 20

using namespace std;

class Client {
  public:
    char *name;
    int id;

    //Socket stuff
    int sock;

    int edad;
    
  public:
    Client();
    void SetName(const char *name);
    void SetId(int id);
    void SetEdad(int edad);
};

#endif /* CLIENT_H */

