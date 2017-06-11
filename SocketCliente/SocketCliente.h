/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SocketCliente.h
 * Author: cp
 *
 * Created on 22 de mayo de 2017, 08:14 PM
 */

#ifndef SOCKETCLIENTE_H
#define SOCKETCLIENTE_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
//#include<qt5/QtCore/QObject>
using namespace std;


class SocketCliente {
public:
    SocketCliente();
    SocketCliente(const SocketCliente& orig);
    virtual ~SocketCliente();
    bool conectar();
    void setMensaje(const char *msj);
private:
    int descriptor;
    sockaddr_in info;
    bool crear_Socket;
    static void *controlador(void*obj);
    
};

#endif /* SOCKETCLIENTE_H */

