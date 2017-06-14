#include "Almacenamiento.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
using namespace std;

// Funciones auxiliares:
int Menu();
long LeeNumero();



// Clase Datos, almacena y trata los datos.






int main()
{
    Datos datos;
    //bool x = true;
   // datos.Guardar(x);
    long a = 1;
    bool p ;//= true;
    datos.Recupera(a,p);
    if(p){
        cout<<"recupero";
    }
    datos.crearTabla(21);

    cout<<endl<<datos.recuperarEntero(1);
    datos.agregarColumna(21);

    return 0;
}



