


#include "SocketCliente.h"

SocketCliente::SocketCliente() {
}

SocketCliente::SocketCliente(const SocketCliente& orig) {
}

SocketCliente::~SocketCliente() {
}
bool SocketCliente::conectar(){
    descriptor = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(descriptor < 0)
        return false;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = ntohs(30666);
    memset(&info.sin_zero,0,sizeof(info.sin_zero));

    if (connect(descriptor,(sockaddr*)&info,(socklen_t)sizeof(info))<0){
        return false;
    }
    pthread_t hilo;

    pthread_create(&hilo,0,SocketCliente::controlador,(void*)this);
    pthread_detach(hilo);
    
    //send(descriptor,"DN",strlen("DN"),0);

    return true;
}

void * SocketCliente::controlador(void*obj){
    Datos datos;
    SocketCliente *padre=(SocketCliente*)obj;

    while (true) {
        string mensaje;
        while (1) {
            char buffer[10] = {0};
            int bytes = recv(padre->descriptor,buffer,10,0);
            mensaje.append(buffer,bytes);
            if(bytes < 10)
                break;
        }
        cout<<mensaje;
        
        
        //descromprime json
        Json::Value root;
        Json::Reader reader;
        cout<< "estoo";
        bool parsingSuccessful = reader.parse( mensaje, root );     //parse process
        if( !parsingSuccessful ){
            cout<<"Error"<<endl;
        } else{
            string accion = root.get("Accion", "A Default Value if not exists" ).asString().c_str();
            cout<<"Accion "<<accion;

            if(accion == "S"){
                string table  = root.get("Tabla", "A Default Value if not exists" ).asString().c_str();
                int tabla = atoi(table.c_str());
                cout<<"Esti es tablka:"<<tabla;
                cout<<"json valido";
                long x = datos.crearTabla(tabla);
                //datos.agregarDatoColumna(tabla,x,1,"11010101011111101");
                //cout <<endl<< x<<endl;
                //cout<<endl<<"Dato recuperado del 'disco': "<<datos.recuperarCaracteres(1 + 64*x + 20480*(x-1) );
                
                    string retorno = to_string(x);
                    Json::Value fromScratch;
                    fromScratch["accion"] = "S";
                    fromScratch ["Indice"] = retorno;
                    fromScratch ["code"]  = "OK";
                    Json::StyledWriter writerr;
                    string out=writerr.write(fromScratch);
                    send(padre->descriptor,out.c_str(),strlen(out.c_str()),0);
                    cout<<out;
                
            }else if(accion == "GC"){
                string table  = root.get("Tabla", "A Default Value if not exists" ).asString().c_str();
                int tabla = atoi(table.c_str());
                string column = root.get("Columna", "A Default Value if not exists" ).asString().c_str();
                int columna = atoi(column.c_str());
                string dato = root.get("Dato", "A Default Value if not exists" ).asString().c_str();
                string index = root.get("Indice", "A Default Value if not exists" ).asString().c_str();
                int indice = atoi(index.c_str());
                
                cout<<tabla<<endl<<indice<<endl<<columna;
                cout<<"Indice: "<<indice;
                datos.eliminarDatoColumna(tabla,indice,columna);
                datos.agregarDatoColumna(tabla,indice,columna,dato);
                cout<<endl<<"Dato recuperado del 'disco': "<<datos.recuperarCaracteres(1 + 64*indice + 20480*(indice-1) );
            /*
                    string x = datos.recuperarCaracteres(1 + 64*indice + 20480*(indice-1) );
                    Json::Value fromScratch;
                    fromScratch["Accion"] = "GC";
                    fromScratch ["Tabla"] = table ;
                    fromScratch ["Columna"] = column;
                    fromScratch ["Dato"] = x;
                    fromScratch ["Indice"] = indice;
                    fromScratch ["code"] = "OK";
                    Json::StyledWriter writerr;
                    string out=writerr.write(fromScratch);
                    send(padre->descriptor,out.c_str(),strlen(out.c_str()),0);
                    cout<<out;*/
            }else if(accion == "EF"){
                string table  = root.get("Tabla", "A Default Value if not exists" ).asString().c_str();
                int tabla = atoi(table.c_str());
                string index = root.get("Indice", "A Default Value if not exists" ).asString().c_str();
                int indice = atoi(index.c_str());
                datos.EliminarFila(tabla,indice);
                
                    string x = datos.recuperarCaracteres(1 + 64*indice + 20480*(indice-1) );
                    Json::Value fromScratch;
                    fromScratch["Accion"] = "EF";
                    fromScratch ["Tabla"] = table ;
                    fromScratch ["Indice"] = indice;
                    fromScratch ["code"] = "OK";
                    Json::StyledWriter writerr;
                    string out=writerr.write(fromScratch);
                    send(padre->descriptor,out.c_str(),strlen(out.c_str()),0);
                    cout<<out;
            }else if(accion == "EDC"){
                string table  = root.get("Tabla", "A Default Value if not exists" ).asString().c_str();
                int tabla = atoi(table.c_str());
                string column = root.get("Columna", "A Default Value if not exists" ).asString().c_str();
                int columna = atoi(column.c_str());
                string index = root.get("Indice", "A Default Value if not exists" ).asString().c_str();
                int indice = atoi(index.c_str());
                datos.eliminarDatoColumna(tabla,indice,columna);
                cout<<endl<<"Dato recuperado del 'disco': "<<datos.recuperarCaracteres(1 + 64*indice + 20480*(indice-1) );
           
                    
                    Json::Value fromScratch;
                    fromScratch["Accion"] = "EDC";
                    fromScratch ["Tabla"] = table;
                    fromScratch["Indice"] = index;
                    fromScratch["Columna"] = column;
                    fromScratch["code"] = "OK";
                    Json::StyledWriter writerr;
                    string out=writerr.write(fromScratch);
                    send(padre->descriptor,out.c_str(),strlen(out.c_str()),0);
                    cout<<out;
                
            }
            
        }
        
        
        
        
        
        
        
        
        
        
        cout << mensaje << endl;
    }

    close(padre->descriptor);
    pthread_exit(NULL);


}
void SocketCliente::setMensaje(const char* msj){
    cout<<"Bytes enviados"<<send(descriptor,msj,strlen(msj),0)<<"  "<<msj<<endl;


}
