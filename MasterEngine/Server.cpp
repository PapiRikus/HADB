/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Server.cpp
 * Author: cp
 * 
 * Created on 29 de mayo de 2017, 07:42 PM
 */
#include "Server.h"

using namespace std;

//Actually allocate clients
vector<Client> Server::clients;
XMLDocument* xmldoc=new XMLDocument("masterMetaData.xml");

Server::Server() 
{
    hoffman = new HuffmanCompresor();
//    xmldoc = new XMLDocument("masterMetaData.xml");
    //Initialize static mutex from MyThread
    MyThread::InitMutex();
    //For setsock opt (REUSEADDR)
    int yes = 1;
    JSON *json = new JSON();
    //Init serverSock and start listen()'ing
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, 0, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    
    //Avoid bind error if the socket was not close()'d last time;
    setsockopt(serverSock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
    if(bind(serverSock, (struct sockaddr *) &serverAddr, sizeof(sockaddr_in)) < 0){
        cerr << "Failed to bind";
    }
    listen(serverSock, 5);
}

/*
	AcceptAndDispatch();

	Main loop:
		Blocks at accept(), until a new connection arrives.
		When it happens, create a new thread to handle the new client.
*/
void Server::AcceptAndDispatch() {
  
  Client *c;
  MyThread *t;

  socklen_t cliSize = sizeof(sockaddr_in);

  while(1) {

          c = new Client();
	  t = new MyThread();

	  //Blocks here;
          c->sock = accept(serverSock, (struct sockaddr *) &clientAddr, &cliSize);

	  if(c->sock < 0) {
	    cerr << "Error on accept";
	  }
	  else {
	    t->Create((void *) Server::HandleClient, c);
	  }
    }
}

//Static
void *Server::HandleClient(void *args) {
  //Pointer to accept()'ed Client
  Client *c = (Client *) args;
  char buffer[256-25], message[256];
  int index;
  int n;
 
  //Add client in Static clients <vector> (Critical section!)
  MyThread::LockMutex((const char *) c->name);
    //Before adding the new client, calculate its id. (Now we have the lock)
    c->SetId(Server::clients.size());
    c->SetEdad(13);
    cout << "Adding client with id: " << c->id << endl;
    Server::clients.push_back(*c);
  MyThread::UnlockMutex((const char *) c->name);

  while(1) {
    memset(buffer, 0, sizeof buffer);
    cout << "Inicio" << endl;
    n = recv(c->sock, buffer, sizeof buffer, 0);
    c->SetName(buffer);
    //Client disconnected?
    if(n == 0) {
      cout << "Client " << c->name << " diconnected" << endl;
      close(c->sock);
      //Remove client in Static clients <vector> (Critical section!)
      MyThread::LockMutex((const char *) c->name);
      index = Server::FindClientIndex(c);
      cout << "Erasing user in position " << index << " whose name id is: " << Server::clients[index].id << endl;
      Server::clients.erase(Server::clients.begin() + index);
      MyThread::UnlockMutex((const char *) c->name);
      
      break;
    }
    else if(n < 0) {
      cerr << "Error while receiving message from client: " << c->name << endl;
    }
    else {
      //Message received. Send to all clients.
      snprintf(message, sizeof message, "<%s>: %s", c->name, buffer); 
      JSON *json = new JSON();
      json->setValue(buffer);
      Server::processQuery(json);
      Server::SendToPair(c->id,json);
    }
  }
  //End thread
  return NULL;
}

void Server::processQuery(JSON *json){
    if(json->getData("soy")=="QE"){
        cout <<"QE detected"<<endl;
        if(json->getData("accion")=="C"){
            cout << "Action create table" <<endl;
            xmldoc->createTable(json->getData("tabla"),json->getData("columna"),json->getData("tipo"),json->getData("size"));
        }
    }
}
string Server::toString(char* c){
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    return s;
}

void Server::Send(int diskN, JSON *json) {
  int n = 0;
  //Acquire the lock
  MyThread::LockMutex("'Send()'");
  if(diskN < clients.size()){
    n = send(Server::clients[diskN].sock, json->show().c_str() , strlen(json->show().c_str()), 0);
  }else{
    cout << "Error: the client doesn't exits." << endl;
  }
  cout << n << " bytes sent." << endl;
  //Release the lock  
  MyThread::UnlockMutex("'Send()'");
}

void Server::SendToPair(int diskN, JSON *json) {
  int n;
  //Acquire the lock
  MyThread::LockMutex("'SendToPair()'");
  if(json->getData("soy")=="DN" & diskN+1 < clients.size()){
    n = send(Server::clients[diskN+1].sock, json->show().c_str() , strlen(json->show().c_str()), 0);   
  }
  
  cout << n << " bytes sent." << endl;
  //Release the lock  
  MyThread::UnlockMutex("'SendToPair()'");
}

void Server::ListClients() {
  for(size_t i=0; i<clients.size(); i++) {
    cout << clients.at(i).name << endl;
  }
}


/*
  Should be called when vector<Client> clients is locked!
*/
int Server::FindClientIndex(Client *c) {
  for(size_t i=0; i<clients.size(); i++) {
    if((Server::clients[i].id) == c->id) return (int) i;
  }
  cerr << "Client id not found." << endl;
  return -1;
}

