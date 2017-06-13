/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyThread.h
 * Author: cp
 *
 * Created on 29 de mayo de 2017, 07:41 PM
 */

#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>

#include <cstdlib>

using namespace std;

class MyThread {
  public:
    pthread_t tid;

  private:
    static pthread_mutex_t mutex;

  public:
    MyThread();
    int Create(void *Callback, void *args);
    int Join();

    static int InitMutex();
    static int LockMutex(const char *identifier);
    static int UnlockMutex(const char *identifier);
};


#endif /* MYTHREAD_H */

