/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ValidarConsulta.cpp
 * Author: cp
 * 
 * Created on 13 de junio de 2017, 05:26 PM
 */

#include <regex>

#include "ValidarConsulta.h"

   // regex select("SELECT\\s+(.*?)\\s*FROM\\s+(.*?)\\s*(WHERE\\s(.*?)\\s*)?;");
    //Este lo divide en 7 grupos donde si los 2 ultimos estan vacios es un where 
    regex selectjoinwhere("SELECT\\s+(.*?)\\s*FROM\\s+(.*?)\\s*(WHERE\\s(.*?)|JOIN\\s(.*?)\\s*ON(.*))?;(.*)");
    //divide en dos grupos 
    regex insert("INSERT INTO\\s+(.*?)\\s*VALUES\\s+\\((.*?)\\);(.*)");
    //Grupos 1 y 3 
    regex deletee("DELETE FROM\\s+(.*?)\\s*(WHERE\\s(.*?)\\s*)?;(.*)");
    //1 esta la tabla 2 esta el set y 4 esta el where
    regex update ("UPDATE\\s+(.*?)\\s*SET\\s+(.*?)\\s*(WHERE\\s(.*?)\\s*)?;(.*)");
    // 1 estan la tabla 
    regex dropTable("DROP TABLE\\s+(.*?)?;(.*)");
    //1 grupo son la tabla o tablas 
    regex createIndex("CREATE INDEX\\s+\\<(.*?)\\>?;(.*)");
    
    regex createTable("CREATE TABLE ([a-zA-Z0-9]+) \\(([a-zA-Z0-9]+( INT| BOOL| CHAR| STRING\\([0-9]+\\))+( REFERENCE\\([a-zA-Z0-9]+\\.[a-zA-Z0-9]+\\))?(,[a-zA-Z0-9]+ (INT|BOOL|CHAR|STRING\\([0-9]+\\))+( REFERENCE\\([a-zA-Z0-9]+\\.[a-zA-Z0-9]+\\))?)*)+(, PRIMARY KEY ([a-zA-Z]+))?\\)(.*)"); 
    string data="";
    string aux="";
    string data1 = "{";
    string antes="\"";
    string selectt="\"tipo\":\"S\"";
            //"\"nombre\":\"
    string medio="\":\"";
    string despues="\",";        
    string data2 = "\"}";
    string tabla="tabla";
    string accion="accion";
    string columna="columna";
    string tipo="tipo";
    string condicion="condicion";
    
//  
ValidarConsulta::ValidarConsulta() {
   // argumentos=new vector<>();
    
}

ValidarConsulta::ValidarConsulta(const ValidarConsulta& orig) {
}

ValidarConsulta::~ValidarConsulta() {
}

bool ValidarConsulta::ValidarSintaxis(string query){
    //string query="CREATE TABLE MATRICULA (IDCURSO INT REFERENCE(CURSO.ID), IDALUMNO INT E(ESTUDIANTES.ID))";
   //query="SELECT * FROM orders;";
    cout<<query<<"Este es el query que entra al validador"<<query;
   
    //string query ="SELECT ID, NOMBRE FROM ESTUDIANTES JOIN CURSOS ON ESTUDIANTES.ID = CURSOS.IDEST;";     
    //string query ="SELECT ID, NOMBRE FROM ESTUDIANTES WHERE ESTUDIANTES.ID = 1;";
    //string query="INSERT INTO test_table VALUES (1, 2, 'test');";
//    string query ="DELETE FROM students WHERE grade > 3.0;";
    //string query ="UPDATE students SET grade = 1.3 WHERE name = 'Max Mustermann';";
  //  string query ="DROP TABLE students;";
   // string query ="CREATE INDEX <students>;";
    //   std::string str("1231-12");
    
//    regex selectjoin("SELECT\\s+(.*?)\\s*FROM\\s+(.*?)\\s*(WHERE\\s(.*?)\\s*|JOIN\\s(.*?)\\s*)?;");
//    regex create("CREATE TABLE ([a-zA-Z0-9]+) \\(([a-zA-Z0-9]+( INT| BOOL| CHAR| STRING\\([0-9]+\\))+( REFERENCE\\([a-zA-Z0-9]+\\.[a-zA-Z0-9]+\\))?(,[a-zA-Z0-9]+ (INT|BOOL|CHAR|STRING\\([0-9]+\\))+( REFERENCE\\([a-zA-Z0-9]+\\.[a-zA-Z0-9]+\\))?)*)+(, PRIMARY KEY ([a-zA-Z]+))?\))"; // entire match will be 2 numbers
    //regex e("([[:w:]]+)@([[:w:]]+)\\.com");
    
    smatch m;
  //  cout<<"dsdfs"<<regex_match(query,selectjoin);
    
   // string a ="sdfsdfd@hotmail.com";
    
    //SELECT
    argumentos.clear();
     cout<<"otra vez query:"<<query<<regex_match(query,selectjoinwhere)<<endl;   
    if (regex_match(query,selectjoinwhere)){
        cout<<"Entro en el select";
        regex_search(query,m,selectjoinwhere);
        for (int i=0;i<m.size();i++){
            
            cout<<"DatosSelection:"<<m.str(i)<<endl;
            argumentos.push_back(m.str(i));
        }
        this->jsonString=jsonSelect(m);
        cout<<"Este es el jsonString:"<<jsonString<<endl;
        return true;
    }
    if (regex_match (query, insert)){
        regex_search(query,m,insert);        
           for (int i=0;i<m.size();i++){
            
            cout<<"Datos:"<<m.str(i)<<endl;
            argumentos.push_back(m.str(i));
        }
        return true;
    }
    if (regex_match (query,update)){
        regex_search(query,m,update);        
        for (int i=0;i<m.size();i++){
            
            cout<<"Datos:"<<m.str(i)<<endl;
            argumentos.push_back(m.str(i));
        }
        return true;
        
    }
    if (regex_match (query,deletee)){
        regex_search(query,m,deletee);        
           for (int i=0;i<m.size();i++){
            
            cout<<"Datos:"<<m.str(i)<<endl;
            argumentos.push_back(m.str(i));
        }
        return true;
        
    }
    if (regex_match (query,dropTable)){
        regex_search(query,m,dropTable);        
          for (int i=0;i<m.size();i++){
            
            cout<<"Datos:"<<m.str(i)<<endl;
            argumentos.push_back(m.str(i));
        }
        return true;
        
    }
    if(regex_match(query,createIndex)){
        regex_search(query,m,createIndex);        
        for (int i=0;i<m.size();i++){
            
            cout<<"Datos:"<<m.str(i)<<endl;
            argumentos.push_back(m.str(i));
        }
        return true;
    
    }
     if (regex_match(query,createTable)){}
   // std::regex_search(query,m,createIndex);        
        
    cout<<"Tamaño de los grupos"<<m.size()<<"si el 7 esta vacio:";
    for (int i=0;i<m.size();i++){
        cout<<"Datos falso:"<<m.str(i)<<endl;
            
    }
    return false;

}
string ValidarConsulta::jsonSelect(smatch m){
    Json::Value fromScratch;
    fromScratch[accion]="S";
    fromScratch [tabla]=m.str(2);
    fromScratch[columna]=m.str(1);
    string aux;
    if (m.str(4)=="WHERE"){
        aux=m.str(4);
    }
    if(m.str(6)=="JOIN"){
        aux=m.str(7);
        fromScratch["tablaJoin"]=m.str(8);
       
    }
    fromScratch[tipo]=aux;

    Json::StyledWriter writerr;
    string out=writerr.write(fromScratch);
        cout<<out;
        return out;
//    if(m.str(6)=="JOIN"){
//        data1.append("JOIN");
//        
//        data1.append(despues);
//
//        data1.append(antes);
//        aux=m.str(7);
//        data1.append("tablaJoin");
//        data1.append(medio);
//        data1.append(aux);
//        data1.append(despues);
//
//        data1.append(antes);
//        aux=m.str(8);
//        data1.append(condicion);
//        data1.append(medio);
//        data1.append(aux);
//        
//        
    
    //data1.append(data2);
    
    
    cout<<data1<<endl;
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( data1.c_str(), root );
    cout<<parsingSuccessful<<endl;
   
   // for (auto v:m)cout <<"Datos"<<v<<endl;
    
}



