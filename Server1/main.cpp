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
    std::string query= "SELECT * FROM t WHERE a BETWEEN 1 and 'c';";
    
  // parse a given query
  hsql::SQLParserResult result;
  hsql::SQLParser::parseSQLString(query, &result);

  // check whether the parsing was successful

  if (result.isValid()) {
    printf("Parsed successfully!\n");
    printf("Number of statements: %lu\n", result.size());
    const hsql::SQLStatement* statement=result.getStatement(0);
    
    
    if (statement->type()==hsql::kStmtSelect) {
    //     cout<<"si es un select"<<endl;
        const hsql::SelectStatement* select = (const hsql::SelectStatement*) statement;
        //cout<<"Deberia decir nombre "<<select->selectList[0].data()->getName();
  //      cout<<"Deberia decir nombre "<<select->fromTable->getName();
     }
    for (uint i = 0; i < result.size(); ++i) {
      // Print a statement summary.
    //  hsql::printStatementInfo(result.getStatement(i));
      
    //  cout<<result.getStatement(i)->type()<<endl;
    }   
    
    
    } else {
    fprintf(stderr, "Given string is not a valid SQL query.\n");
    fprintf(stderr, "%s (L%d:%d)\n",
            result.errorMsg(),
            result.errorLine(),
            result.errorColumn());
    cout<< "Esto es errormsj"<<result.errorMsg()<<endl;
   // return -1;
    }
  
    
    
    
    
    
    
   server = new SocketServer;
   regex integer("^(INSERT INTO|UPDATE|SELECT|WITH|DELETE)(?:[^;']|(?:'[^']+'))+;\\s*$");
	
   pthread_t hiloServer;
  
   pthread_create(&hiloServer,0,serverRun,NULL);
   pthread_detach(hiloServer);

   while (1) {
       string mensaje="SELECT Patatas FROM t,a,b WHERE a BETWEEN 1 and 'c';";
       cin >> mensaje;
       server->setMensaje(mensaje.c_str());
   }
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

   delete server;
   
    //std::string str;
   // std::string s = "Boost Libraries";
  //  boost::regex expr{"\\w+\\s\\w+"};
    
    return 0;
}

