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
   // long x = datos.crearTabla(22);
    //cout<<" paralasfas " << x;

   // datos.EliminarFila(22, x-1);
    datos.agregarDatoColumna(22, 14, 1, "11111");
    cout<<endl<<"Dato recuperado del 'disco': "<<datos.recuperarCaracteres(1 + 64*14 + 20480*13 );

    long x = datos.crearTabla(22);
    datos.agregarDatoColumna(22,x,1,"11010101011111101");
    cout<<endl<<"Dato recuperado del 'disco': "<<datos.recuperarCaracteres(1 + 64*x + 20480*(x-1) );

    cout<<endl<<datos.recuperarEntero(1);
    datos.agregarDatoColumna(22,1,1,"1010101010011110101101010101111");
    cout<<endl<<"esteee"<<datos.recuperarEntero(33);



   // datos.EliminarFila(21,1);
   // bool x = true;
    //datos.editar(65+2048*2-1, x);
    cout<<endl<<"Dato recuperado del 'disco': "<<datos.recuperarCaracteres(1+64*2+20480);

    return 0;
}



