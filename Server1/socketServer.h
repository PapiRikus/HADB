/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   socketServer.h
 * Author: cp
 *
 * Created on 22 de mayo de 2017, 07:07 PM
 */

#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>


using namespace std;

struct dataSocket{
    int descriptor;
    sockaddr_in info;
};

class SocketServer
{
public:
    SocketServer();
    void run();
    void setMensaje(const char *msn);
private:
    int descriptor;
    sockaddr_in info;
    bool crear_Socket();
    bool ligar_kernel();
    static void * controladorCliente(void *obj);
    vector<int> clientes;
};

#endif // SOCKETSERVER_H
