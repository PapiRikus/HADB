#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <string>
#include <stdio.h>

#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

using namespace std;
using namespace xercesc;

class XMLDocument {
    
    private:
        //Attributes
        DOMDocument* _document;
        XercesDOMParser* _parser;
        ErrorHandler* _errorHandler;
        
        //Methods
        void createParser();
        void writeInDocument();
        
    public:
        XMLDocument(const char* pFileName);
        ~XMLDocument();
        
        //Reading methods
        bool existTable(std::string);
        bool existColumnInTable(std::string, std::string);
        std::string getDataTypeOfColumn(std::string, std::string);
        
        //Writing methods
        void createTable(std::string, std::string, std::string, std::string);
        void createColumnInTable(std::string, std::string, std::string, std::string);
        
        //Deleting methods
        void deleteTable(std::string);
        void deleteColumnInTable(std::string, std::string);

};


#endif /* XMLDOCUMENT_H */

