
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#include "Almacenamiento.h"
#include "SocketCliente.h"
using namespace std;



int main()
{
    Datos datos;
    SocketCliente* conexion;
    conexion=new SocketCliente();
    conexion->conectar();
    // conexion->setMensaje("Hol servidor6");
    cout<<"Conexion con server"<<endl;
    bool val = true;
    while(val){
        string mensaje;
        cin >>mensaje;
        const char* msj=mensaje.c_str();
        conexion->setMensaje(msj);
        //conexion->setMensaje("Hola servidor6");
    //val = false;
        
        
        //crear el json

        
    }




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
/*     datos.agregarDatoColumna(22, 14, 1, "11111");
   datos.agregarDatoColumna(22, 14, 1, "11111");
    datos.eliminarDatoColumna(22, 14, 1);
    cout<<endl<<"Dato recuperado del 'disco': "<<datos.recuperarCaracteres(1 + 64*14 + 20480*13 );

    long x = datos.crearTabla(22);
    datos.agregarDatoColumna(22,x,1,"11010101011111101");
    datos.eliminarDatoColumna(22,x,1);
    cout<<endl<<"Dato recuperado del 'disco': "<<datos.recuperarCaracteres(1 + 64*x + 20480*(x-1) );
*/
 //   cout<<endl<<datos.recuperarEntero(1);
 //   datos.agregarDatoColumna(22,1,1,"1010101010011110101101010101111");
 //   cout<<endl<<"esteee"<<datos.recuperarEntero(33);



   // datos.EliminarFila(21,1);
   // bool x = true;
    //datos.editar(65+2048*2-1, x);
   // cout<<endl<<"Dato recuperado del 'disco': "<<datos.recuperarCaracteres(1+64*2+20480);

    return 0;
}



