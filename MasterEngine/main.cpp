#include <iostream>
#include <fstream>
#include <sstream>
#include "XMLDocument.h"
#include "ArbolBmas.h"
#include "NodoProducto.h"
#include "Server.h"

using namespace std;
int node = 0;
/*void setData(string key,string data){
    string DN = "DN-", info = "", numNodo = node;
    DN.append(numNodo);
    DN.append(".data");
    ofstream file(DN, ios::out | ios::binary);
    info.append(key);
    info.append(":");
    info.append(info);
    info.append(".");
    file.write(info.c_str(), info.size());
}
string toString(char* c){
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
}*/
int main(int argc, char** argv){
    //ArbolBmas arbolb = new ArbolBmas();
    Server *s = new Server();
    s->AcceptAndDispatch();
    //setData("Hola", "Mundo");
    return 0;
}
