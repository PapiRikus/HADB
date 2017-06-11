/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lista.h
 * Author: Diversas fuentes
 *
 * Created on 28 de mayo de 2017, 10:31 PM
 */
#include<iostream>
using std::endl;
using std::cout;
#include<cstdlib>
#if !defined Nodo_h
#define Nodo_h
//***********************************************************************
//***********************CLASE NODO**************************************
//***********************************************************************
template<class t_dato>
class Nodo
{
	t_dato dato;
	Nodo *sig;
	
	public:
	Nodo() { sig = NULL; }
	Nodo(t_dato dato);
	t_dato elemento() { return dato; }
	Nodo *siguiente() { return sig; }
	void setElemento(t_dato dato) { /*this->dato = dato;*/ }
	void insertar(Nodo *elemento) { sig = elemento; }
};


template<class t_dato>
Nodo<t_dato>::Nodo(t_dato dato)
{
	this->dato = dato;
	sig = NULL;
}

#endif

//***********************************************************************
//************************CLASE LISTA************************************
//***********************************************************************
#if !defined Lista_h
#define Lista_h

template<class t_dato>
class Lista
{
	Nodo<t_dato> *lista;
	int size;

	public:
	
	Lista() { lista = NULL; size = 0; }
	Lista(t_dato dato);
	void anadir(int nceldas);
	int esVacia() { return (lista == NULL); }
	void insertar(t_dato dato);
	t_dato recuperar(int index);
	void poner(t_dato dato, int index);
	void eliminar(int index);
	long length() { return size; }
	~Lista();
};

#endif

template<class t_dato>
Lista<t_dato>::Lista(t_dato dato)
{
	lista = new Nodo<t_dato>(dato);
	size++;
}
//Reserva espacio en la lista para tantos elementos
//como indique el parametro nceldas, y acutaliza la 
//variable size
template<class t_dato>
void Lista<t_dato>::anadir(int nceldas)
{
	Nodo<t_dato> *temp;
	int i = 0;

	if(esVacia())
	{//si la lista esta vacia inserto el nodo vacio en la primera posicion
		Nodo<t_dato> *nodo = new Nodo<t_dato>();
		lista = nodo;
		i++;
		size++;
	}
	for(; i<nceldas; i++)
	{
		Nodo<t_dato> *nodo = new Nodo<t_dato>();
		temp = lista;
		//como la lista no esta vacia avanzo hasta la ultima posicion e inserto el nodo vacio
		while(temp->siguiente())
			temp = temp->siguiente();
		temp->insertar(nodo);
		size++;
	}
}

template<class t_dato>
void Lista<t_dato>::insertar(t_dato dato)
{
	cout << "insertando" << "endl";
	Nodo<t_dato> *nodo = new Nodo<t_dato>(dato);
	Nodo<t_dato> *temp = lista;
	
	if(esVacia())
	{
		cout << "Lista Vacia" << endl;
		lista = nodo;
	}
	else
	{
		while(temp->siguiente())
			temp = temp->siguiente();
		temp->insertar(nodo);
	}
	size++;
}

template<class t_dato>
t_dato Lista<t_dato>::recuperar(int index)
{
	int i=0;
	Nodo<t_dato> *nodo = lista;
	
	if(!esVacia())
	{
		if(size < index)
		{
			cout << "ERROR: accediendo a la lista: indice buscado superior al tamano de la misma";
			exit(1);
		}
		while((i<index) && (nodo))
		{			
			nodo = nodo->siguiente();
			i++;
		}
		return (nodo->elemento());
	
	}
	cout << "lista vacia" << endl;
	exit(1);
}

template<class t_dato>
void Lista<t_dato>::eliminar(int index)
{
	int i=0;
	Nodo<t_dato> *nodo = lista,*ante=lista;

	if(!esVacia())	
	{
		if(index == 0)		
			lista = lista->siguiente();		
		while((i<index) && (nodo))
		{
			ante = nodo;
			nodo = nodo->siguiente();
		}
		if(nodo)
			ante->insertar(nodo->siguiente());
		delete(nodo);
		size--;
	}
}

template<class t_dato>
Lista<t_dato>::~Lista()
{
	while(!esVacia())	
		eliminar(0);
	size = 0;
}
