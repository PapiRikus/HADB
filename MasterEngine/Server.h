/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Server.h
 * Author: aaronsolera
 *
 * Created on 15 de junio de 2017, 07:41 AM
 */

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>

#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>

#include "mythread.h"
#include "HuffmanCompresor.h"
#include "Client.h"
#define PORT 30667

using namespace std;

class JSON{
private:
    Json::Value json;
    Json::Reader r;
public:
    JSON(){
    }
    ~JSON(){
        delete(&json);
        delete(&r);
    }
    void add(string key, string data){
        this->json[key] = data;
    }
    Json::Value data(){
        return this->json;
    }
    string getData(string key){
        return this->json.get(key, "That value does not exists" ).asString();
    }
    string show(){
        Json::StyledWriter w;
        cout << w.write(this->json) << endl;
        return w.write(this->json);
    }
};

class Server {
  private:
    HuffmanCompresor* hoffman;
    static vector<Client> clients;
    //Socket stuff
    int serverSock, clientSock;
    struct sockaddr_in serverAddr, clientAddr;
    char buff[256];
  public:
    Server();
    void AcceptAndDispatch();
    static void *HandleClient(void *args);
    static void Send(int diskN, string json);
    static string Listen();
  private:
    static string toString(char* c);
    static void ListClients();
    static void SendToPair(int diskN, string json);
    static int FindClientIndex(Client *c); 
};


#endif /* SERVER_H */

