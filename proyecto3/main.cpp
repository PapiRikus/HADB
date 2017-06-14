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
   //datos.crearTabla(21);

    cout<<endl<<datos.recuperarEntero(1);
    //datos.agregarDatoColumna(21,1,2,"1010101010011110101101010101111");
    cout<<endl<<"esteee"<<datos.recuperarEntero(33);
    datos.EliminarFila(21,1);
   // bool x = true;
    //datos.editar(65+2048*2-1, x);
    cout<<endl<<"Dato recuperado del 'disco': "<<datos.recuperarCaracteres(65+2048);

    return 0;
}



