/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ValidarConsulta.h
 * Author: cp
 *
 * Created on 13 de junio de 2017, 05:26 PM
 */

#ifndef VALIDARCONSULTA_H
#define VALIDARCONSULTA_H

#include <vector>
#include <cstdlib>

#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#include <regex>

using namespace std;
class ValidarConsulta {
public:
    ValidarConsulta();
    ValidarConsulta(const ValidarConsulta& orig);
    virtual ~ValidarConsulta();
    bool ValidarSintaxis(string consulta);
    vector<string>argumentos;
    string jsonString;
    string jsonSelect(std::smatch);  
    string jsonCreateTable(std::smatch);  
   
private:
    bool consulta;
};

#endif /* VALIDARCONSULTA_H */

