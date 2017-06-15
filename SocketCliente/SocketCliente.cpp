/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SocketCliente.cpp
 * Author: cp
 * 
 * Created on 22 de mayo de 2017, 08:14 PM
 */
#include "SocketCliente.h"

SocketCliente::SocketCliente() {
}

SocketCliente::SocketCliente(const SocketCliente& orig) {
}

SocketCliente::~SocketCliente() {
}
bool SocketCliente::conectar(){
    descriptor = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(descriptor < 0)
        return false;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr("192.168.1.132");
    info.sin_port = ntohs(30667);
    memset(&info.sin_zero,0,sizeof(info.sin_zero));
    
    if (connect(descriptor,(sockaddr*)&info,(socklen_t)sizeof(info))<0){
        return false;
    }
    
    pthread_t hilo;
    
    pthread_create(&hilo,0,SocketCliente::controlador,(void*)this);
    pthread_detach(hilo);
    setMensaje("QE");
    
    return true;
}

void * SocketCliente::controlador(void*obj){
    SocketCliente *padre=(SocketCliente*)obj;
    
    while (true) {
        string mensaje;
        while (1) {
            char buffer[10] = {0};
            int bytes = recv(padre->descriptor,buffer,10,0);
            mensaje.append(buffer,bytes);
            if(bytes < 10)
                break;
        }
        cout << mensaje << endl;
        
        SocketCliente::mensajee=(mensaje);
//        this->mensajee=mensaje;
    }
    
    close(padre->descriptor);
    pthread_exit(NULL);
    
    
}
void SocketCliente::setMensaje(const char* msj){
    cout<<"Bytes enviados"<<send(descriptor,msj,strlen(msj),0)<<"  "<<msj<<endl;
     
    
}

    
    
    
    


