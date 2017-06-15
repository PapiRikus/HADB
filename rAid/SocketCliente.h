#ifndef PROYECTO3_SOCKETCLIENTE_H
#define PROYECTO3_SOCKETCLIENTE_H


#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
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
#include "Almacenamiento.h"
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


#endif //PROYECTO3_SOCKETCLIENTE_H

