#include <iostream>
#include <fstream>
#include <sstream>
#include "XMLDocument.h"
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
}*/
string toString(char* c){
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
}
int main(){
    XMLDocument *xmldoc = new XMLDocument("m.xml");
    xmldoc->createTable("Personas","Nombre","string","10");
    //setData("Hola", "Mundo");
    return 0;
}
