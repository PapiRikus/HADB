/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: cp
 *
 * Created on 29 de mayo de 2017, 07:34 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include "mythread.h"
#include "server.h"
#include "HuffmanCompresor.h"

using namespace std;
#include <iostream>
#include <fstream>
using namespace std;

void setNode(string node){
    string info = "";
    ofstream file("nodes.data", ios::out | ios::binary);
    info.append("(");
    info.append(node);
    info.append(")");
    file.write(info.c_str(), info.size());
}
string toString(char* c){
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    return s;
}
/* Está malo -> c mamut
void setData(string node,string data){
    string info = "";
    fstream file("nodes.data",ios::in | ios::binary);
    char c, t;
    file.seekg(0, ios::end);
    int lon = file.tellg();
    for(int i; i<lon; i++){
       file.seekg(i, ios::beg);
       file.get(c);
       if(c == '('){
           int k = i+1;
           string temp = "";
           while(t != ')'){
                temp.append(toString(t));
                file.seekg(k, ios::beg);
                file.get(t);
                k++;
           }
           cout << temp <<"="<< node <<endl;
           file.close();
           fstream file("nodes.data",ios::out | ios::binary);
           if(temp == node){
               file.seekp(k, ios::beg);
               info.append("<");
               info.append(node);
               info.append(">");
               info.append(data);
               cout << "Writing: " << info << endl;
               file<<info.c_str();
           }
           file.close();
       }
    }
}
*/
int main(){
    setNode("Pocha");
    //setData("Pocha","MSCDLABKPEP");
    cout << "Running!" << endl;
    Server *s;
    s = new Server();
    s->AcceptAndDispatch();
    return 0;
}

