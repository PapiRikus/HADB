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

#include "server.h"
#include "HuffmanCompresor.h"
#include "ValidarConsulta.h"
#include "SocketCliente.h"

using namespace std;

//Actually allocate clients
vector<Client> Server::clients;
HuffmanCompresor* hoffman;
ValidarConsulta* validar;
SocketCliente* socketCli;
Server::Server() {
    validar =new ValidarConsulta();
    bool vv =validar->ValidarSintaxis("SELECT * FROM orders;");
    cout<<vv<<endl;
    hoffman=new HuffmanCompresor();
    string a=hoffman->compress("sdfsdfsdfsdfsf");
    for (int i=0;i<validar->argumentos.size();i++){
        cout<<"Argumentos:"<<validar->argumentos[i]<<endl;
    
    }
    socketCli=new SocketCliente();
    socketCli->conectar();
    socketCli->setMensaje("QE");
    cout<<hoffman->decompress(a)<<endl;
  //Initialize static mutex from MyThread
  MyThread::InitMutex();

  //For setsock opt (REUSEADDR)
  int yes = 1;

  //Init serverSock and start listen()'ing
  serverSock = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serverAddr, 0, sizeof(sockaddr_in));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(PORT);

  //Avoid bind error if the socket was not close()'d last time;
  setsockopt(serverSock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));

  if(bind(serverSock, (struct sockaddr *) &serverAddr, sizeof(sockaddr_in)) < 0)
    cerr << "Failed to bind";

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
       ValidarConsulta* validarr=new ValidarConsulta();
    //Before adding the new client, calculate its id. (Now we have the lock)
    c->SetId(Server::clients.size());
    sprintf(buffer, "Client %d", c->id);
    c->SetName(buffer);
    cout<<"Nombre:"<<c->name<<endl;
    
    //c->SetEdad(13);
    cout << "Adding client with id: " << c->id << endl;
    Server::clients.push_back(*c);

  MyThread::UnlockMutex((const char *) c->name);
//SELECT * FROM orders;
  while(1) {
    memset(buffer, 0, sizeof buffer);
    n = recv(c->sock, buffer, sizeof buffer, 0);
    string strr(buffer); 
    snprintf(message, sizeof message, "<%s>: %s", c->name, buffer);
     bool vv =validarr->ValidarSintaxis(strr);
     cout<<"QUE es sdfd:"<<vv;
     //socketCli->setMensaje(buffer);
    //Client disconnected?
    if(n == 0) {
      cout << "Client " << c->name << " diconnected" << endl;
      close(c->sock);
      
      //Remove client in Static clients <vector> (Critical section!)
      MyThread::LockMutex((const char *) c->name);
        index = Server::FindClientIndex(c);
        cout << "Erasing user in position " <<index<<" whose name id is: " 
	  << Server::clients[index].id << endl;
        Server::clients.erase(Server::clients.begin() + index);
        
        cout<<c->edad<<endl;
      MyThread::UnlockMutex((const char *) c->name);

      break;
    }
    else if(n < 0) {
      cerr << "Error while receiving message from client: " << c->name << endl;
    }
    else {
        if (vv==false){
          MyThread::LockMutex("'SendToAll()'");
         
          //snprintf(message, sizeof message, "%s", c->name,"Invalid SQL Statmetment");      
          index = Server::FindClientIndex(c);
          strncat(message, "Invalid SQL Statment", sizeof message);
         // strcpy(message,"Invalid SQL Statment");
          cout<<"Esto va a mandar a el mismo:"<<message<<endl;
          n = send(Server::clients[index].sock, message, strlen(message), 0);
          cout << n << " bytes sent." << endl;
          
  
        //Release the lock  
        MyThread::UnlockMutex("'SendToAll()'");
      }else{
            
             MyThread::LockMutex("'SendToAll()'");
          //snprintf(message, sizeof message, "%s", c->name,"Invalid SQL Statmetment");      
          index = Server::FindClientIndex(c);
         // strcpy(message,"Invalid SQL Statment");
          n = send(Server::clients[index].sock, message, strlen(message), 0);
          
  
        //Release the lock  
            for(int i=0;i<validarr->argumentos.size();i++){
               strncat(message, validarr->argumentos[i].c_str(), sizeof message);
               n = send(Server::clients[index].sock, message, strlen(message), 0);
            }
          MyThread::UnlockMutex("'SendToAll()'");
        
      }
      //Message received. Send to all clients.
       cout<<"esto"<<endl;
     
      cout << "Will send to all: " << message << endl;
      //Server::SendToAll(message);
    }
  }

  //End thread
  return NULL;
}

void Server::SendToAll(char *message) {
  int n;

  //Acquire the lock
  MyThread::LockMutex("'SendToAll()'");
    for(size_t i=0; i<clients.size(); i++) {
      n = send(Server::clients[i].sock, message, strlen(message), 0);
      cout << n << " bytes sent." << endl;
    }
  
  //Release the lock  
  MyThread::UnlockMutex("'SendToAll()'");
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