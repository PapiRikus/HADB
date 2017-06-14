/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: cp
 *
 * Created on 22 de mayo de 2017, 07:01 PM
 */

#include <cstdlib>
#include "socketServer.h"
//#include <boost/regex.hpp>
#include <regex>
#include <iostream>
#include "hsql/SQLParser.h"
#include "hsql/util/sqlhelper.h"

/*
 * 
 */

SocketServer *server;
void * serverRun(void *)
{
    try{
        server->run();
    }catch(string ex)
    {
        cout << ex;
    }

   pthread_exit(NULL);
}

int main(int argc, char** argv) {
 
    
//  std::string query = "CREATE TABLE MATRICULA (IDCURSO INT ,REFERENCE(CURSO.ID), IDALUMNO INT)";
    //std::string query= "SELECT * FROM t WHERE a BETWEEN 1 and 'c';";
//string query="CREATE TABLE MATRICULA (IDCURSO INT REFERENCE(CURSO.ID), IDALUMNO INT (ESTUDIANTES.ID))";
//string query="SELECT * FROM orders;";
//string query ="SELECT ID, NOMBRE FROM ESTUDIANTES JOIN CURSOS ON ESTUDIANTES.ID = CURSOS.IDEST;";     
string query ="SELECT ID, NOMBRE FROM ESTUDIANTES WHERE ESTUDIANTES.ID = 1;";
    //string query="INSERT INTO test_table VALUES (1, 2, 'test');";
//    string query ="DELETE FROM students WHERE grade > 3.0;";
    //string query ="UPDATE students SET grade = 1.3 WHERE name = 'Max Mustermann';";
  //  string query ="DROP TABLE students;";
   // string query ="CREATE INDEX <students>;";
    //   std::string str("1231-12");
    regex integer("^(INSERT INTO|CREATE TABLE|UPDATE|SELECT|WITH|DELETE)(?:[^;']|(?:'[^']+'))([a-zA-Z0-9])+\\s*$");
    
    regex create("CREATE TABLE ([a-zA-Z0-9]+) \\(([a-zA-Z0-9]+( INT| BOOL| CHAR| STRING\\([0-9]+\\))+( REFERENCE\\([a-zA-Z0-9]+\\.[a-zA-Z0-9]+\\))?(,[a-zA-Z0-9]+ (INT|BOOL|CHAR|STRING\\([0-9]+\\))+( REFERENCE\\([a-zA-Z0-9]+\\.[a-zA-Z0-9]+\\))?)*)+(, PRIMARY KEY ([a-zA-Z]+))?\\)");
    
    regex select("SELECT\\s+(.*?)\\s*FROM\\s+(.*?)\\s*(WHERE\\s(.*?)\\s*)?;");
    //Este lo divide en 7 grupos donde si los 2 ultimos estan vacios es un where 
    regex selectjoinwhere("SELECT\\s+(.*?)\\s*FROM\\s+(.*?)\\s*(WHERE\\s(.*?)|JOIN\\s(.*?)\\s*ON(.*))?;");
    //divide en dos grupos 
    regex insert("INSERT INTO\\s+(.*?)\\s*VALUES\\s+\\((.*?)\\)");
    //Grupos 1 y 3 
    regex deletee("DELETE FROM\\s+(.*?)\\s*(WHERE\\s(.*?)\\s*)?;");
    //1 esta la tabla 2 esta el set y 4 esta el where
    regex update ("UPDATE\\s+(.*?)\\s*SET\\s+(.*?)\\s*(WHERE\\s(.*?)\\s*)?;");
    // 1 estan la tabla 
    regex dropTable("DROP TABLE\\s+(.*?)?;");
    //1 grupo son la tabla o tablas 
    regex createIndex("CREATE INDEX\\s+\\<(.*?)\\>?;");
    
//    regex selectjoin("SELECT\\s+(.*?)\\s*FROM\\s+(.*?)\\s*(WHERE\\s(.*?)\\s*|JOIN\\s(.*?)\\s*)?;");
//    regex create("CREATE TABLE ([a-zA-Z0-9]+) \\(([a-zA-Z0-9]+( INT| BOOL| CHAR| STRING\\([0-9]+\\))+( REFERENCE\\([a-zA-Z0-9]+\\.[a-zA-Z0-9]+\\))?(,[a-zA-Z0-9]+ (INT|BOOL|CHAR|STRING\\([0-9]+\\))+( REFERENCE\\([a-zA-Z0-9]+\\.[a-zA-Z0-9]+\\))?)*)+(, PRIMARY KEY ([a-zA-Z]+))?\))"; // entire match will be 2 numbers
    //regex e("([[:w:]]+)@([[:w:]]+)\\.com");
    
    std::smatch m;
  //  cout<<"dsdfs"<<regex_match(query,selectjoin);
    string a ="sdfsdfd@hotmail.com";
    if (regex_match(query,selectjoinwhere)){
        cout<<"es verdad"<<endl;
    }
    std::regex_search(query,m,selectjoinwhere);        
        
    cout<<"Tamaño de los grupos"<<m.size()<<"si el 7 esta vacio:"<<endl;
    //td::string data4 = "{\"nombre\":\"Rober\"}";
    string data="";
    string aux="";
    string data1 = "{";
    string antes="\"";
            //"\"nombre\":\"
    string medio="\":\"";
    string despues="\",";        
    string data2 = "\"}";
    string tabla="tabla";
    string columna="columna";
    data1.append(data);
    data1.append(antes);
    aux=m.str(1);
    data1.append(tabla);
    data1.append(medio);
    data1.append(aux);
    data1.append(despues);
    
    data1.append(antes);
    aux=m.str(2);
    data1.append(columna);
    data1.append(medio);
    data1.append(aux);
    
    data1.append(data2);
    
    cout<<data1<<endl;
    
   //server = new SocketServer;
   //regex integer("^(INSERT INTO|UPDATE|SELECT|WITH|DELETE)(?:[^;']|(?:'[^']+'))+;\\s*$");
//	
//   pthread_t hiloServer;
//  
//   pthread_create(&hiloServer,0,serverRun,NULL);
//   pthread_detach(hiloServer);
//
//   while (1) {
//       string mensaje="SELECT Patatas FROM t,a,b WHERE a BETWEEN 1 and 'c';";
//       cin >> mensaje;
//       server->setMensaje(mensaje.c_str());
//   }
       //smatch m;
       //if(regex_search(mensaje,m,integer)){
        //for (int i=0;i<m.size();i++){
         //   cout<<m[i].str()<<endl;
       // }      
//           
//       }else {
//            cout<<"no";
//        }
//        std::string str("1231-12");
//        std::regex r("^(....)-(..)"); // entire match will be 2 numbers
//        std::smatch m;
//        std::regex_search(str, m, r);
//        for(auto v: m) std::cout << v << std::endl;
//    }

   //delete server;
   
    //std::string str;
   // std::string s = "Boost Libraries";
  //  boost::regex expr{"\\w+\\s\\w+"};
    
    return 0;
}

