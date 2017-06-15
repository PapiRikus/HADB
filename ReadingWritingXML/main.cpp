#include <iostream>
#include "XMLDocument.h"

using namespace std;

int main(int argc, char** argv) {
    
    XMLDocument* doc = new XMLDocument("masterMetaData.xml");
    
    //doc->createTable("Personas", "Nombre", "string", "4");
    
    //doc->createColumnInTable("Personas", "Apellido", "string", "4");
    
    //doc->deleteColumnInTable("Personas", "Apellido");
    
    //doc->deleteTable("Personas");

    return 0;
}

