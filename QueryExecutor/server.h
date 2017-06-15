/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Server.h
 * Author: cp
 *
 * Created on 29 de mayo de 2017, 07:42 PM
 */

#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>

#include "mythread.h"

#include "Client.h"
#define PORT 30666


using namespace std;

class Server {

  private:
    static vector<Client> clients;
    static Client* MasterEngine; 
    //Socket stuff
    int serverSock, clientSock;
    struct sockaddr_in serverAddr, clientAddr;
    char buff[256];

  public:
    Server();
    void AcceptAndDispatch();
    static void * HandleClient(void *args);

  private:
    static void ListClients();
    static void SendToAll(char *message);
    static int FindClientIndex(Client *c); 
};

#endif /* SERVER_H */

