#include <iostream>
#include <fstream>
#include <sstream>
#include "XMLDocument.h"
#include "ArbolBmas.h"
#include "NodoProducto.h"
#include "Server.h"

using namespace std;
int node = 0;
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
}*/
int main(int argc, char** argv){
    
    //ArbolBmas arbolb = new ArbolBmas();
    
    setNode("Mundo");
    Server *s = new Server();
    s->AcceptAndDispatch();
    
    
    //std::cout << doc->existTable("Estudiantes") << std::endl;
    
    //doc->createTable("Personas", "Nombre", "string", "4");
    
    //doc->createColumnInTable("Personas", "Apellido", "string", "4");
    
    //doc->deleteColumnInTable("Personas", "Apellido");
    
    //doc->deleteTable("Vehiculos");
    
    return 0;
}
