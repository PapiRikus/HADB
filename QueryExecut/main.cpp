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
#include "mythread.h"
#include "server.h"

using namespace std;

int main() {
  cout << "Running!" << endl;

  Server *s;
  s = new Server();

  //Main loop
  s->AcceptAndDispatch();

  return 0;
}

