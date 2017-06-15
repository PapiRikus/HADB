#include "XMLDocument.h"
#include <iostream>

// -----------------------------------------------------------------------------
// Class to Handle Errors
// -----------------------------------------------------------------------------

class XMLErrorHandler : public HandlerBase
{
  public:
    void fatalError(const SAXParseException &exc) {
        printf("Fatal parsing error at line %d\n", (int)exc.getLineNumber());
        exit(-1);
    }
};

// -----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------- 

XMLDocument::XMLDocument(const char* pFileName) {
 
    this->createParser();
    this->_parser->parse(pFileName);
    this->_document = this->_parser->adoptDocument();
    
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

XMLDocument::~XMLDocument() {   
    
    if(this->_document) {
        this->_document->release();
        XMLPlatformUtils::Terminate();
    }
    
}

// -----------------------------------------------------------------------------
// Reading XML Methods
// -----------------------------------------------------------------------------

/**
 * Function that checks if a table exists in the data base
 * 
 * @param pTableName - The name of the table
 * @return - True is the table exist | False is the table doesn't exist
 */
bool XMLDocument::existTable(std::string pTableName) {
    
    DOMNodeList* list = this->_document->getElementsByTagName(XMLString::transcode("table"));
    
    for(int i = 0; i < list->getLength(); i++) {
        
        DOMElement* element = dynamic_cast<DOMElement*>(list->item(i));
        
        if(XMLString::transcode(element->getAttribute(XMLString::transcode("name"))) == pTableName)
            return true;
        
    }
    
    return false;
    
}

/**
 * Function that checks if a column exists in any table in the data base
 * 
 * @param pTableName - The name of the table
 * @param pColumnTable - The name of the column
 * @return - True is the column exist in the table | False is the column doesn't exist in the table
 */
bool XMLDocument::existColumnInTable(std::string pTableName, std::string pColumnName) {
    
    DOMNodeList* tableList = this->_document->getElementsByTagName(XMLString::transcode("table"));
    
    for(int i = 0; i < tableList->getLength(); i++) {
        
        DOMElement* tableElement = dynamic_cast<DOMElement*>(tableList->item(i));
        
        if(XMLString::transcode(tableElement->getAttribute(XMLString::transcode("name"))) == pTableName) {
            
            DOMNodeList* columnsList = dynamic_cast<DOMElement*>(tableElement->getElementsByTagName(XMLString::transcode("columns"))->item(0))->getElementsByTagName(XMLString::transcode("column"));
            
            for(int j = 0; j < columnsList->getLength(); j++) {
                
                DOMElement* columnElement = dynamic_cast<DOMElement*>(columnsList->item(j));
                        
                if(XMLString::transcode(columnElement->getElementsByTagName(XMLString::transcode("name"))->item(0)->getTextContent()) == pColumnName)
                    return true;
                }
            
        }
          
    }
    
    return false;

}

/**
 * Function that gets the type of data that stored a column
 * 
 * @param pTableName - The name of the table
 * @param pColumnName - The name of the column
 * @return - The type of data stored in this column
 */
std::string XMLDocument::getDataTypeOfColumn(std::string pTableName, std::string pColumnName) {
    
    DOMNodeList* tableList = this->_document->getElementsByTagName(XMLString::transcode("table"));
    
    for(int i = 0; i < tableList->getLength(); i++) {
        
        DOMElement* tableElement = dynamic_cast<DOMElement*>(tableList->item(i));
        
        if(XMLString::transcode(tableElement->getAttribute(XMLString::transcode("name"))) == pTableName) {
            
            DOMNodeList* columnsList = dynamic_cast<DOMElement*>(tableElement->getElementsByTagName(XMLString::transcode("columns"))->item(0))->getElementsByTagName(XMLString::transcode("column"));
            
            for(int j = 0; j < columnsList->getLength(); j++) {
                
                DOMElement* columnElement = dynamic_cast<DOMElement*>(columnsList->item(j));
                        
                if(XMLString::transcode(columnElement->getElementsByTagName(XMLString::transcode("name"))->item(0)->getTextContent()) == pColumnName)
                    
                    return XMLString::transcode(columnElement->getElementsByTagName(XMLString::transcode("dataType"))->item(0)->getTextContent());
                    
                }
            
        }
          
    }
    
}

// -----------------------------------------------------------------------------
// Writing XML Methods
// -----------------------------------------------------------------------------

/**
 * Function that creates a new table in the data base
 * 
 * @param pTableName - The name of the table
 * @param pColumnName - The name of the column
 * @param pDataType - The data type that is saved
 * @param pBytes - The number of bytes needed
 */
void XMLDocument::createTable(std::string pTableName, std::string pColumnName, std::string pDataType, std::string pBytes) {
    
    DOMElement* dataBaseRoot = this->_document->getDocumentElement();
    
    DOMElement* newTable = this->_document->createElement(XMLString::transcode("table"));
    
    XMLCh* attributeName = XMLString::transcode("name");
    XMLCh* tableName = XMLString::transcode(pTableName.c_str());
    newTable->setAttribute(attributeName, tableName);
    
    DOMElement* columns = this->_document->createElement(XMLString::transcode("columns"));
    
    DOMElement* newColumn = this->_document->createElement(XMLString::transcode("column")); 
    
    XMLCh* columnName = XMLString::transcode(pColumnName.c_str());
    DOMElement* columnNameNode = this->_document->createElement(XMLString::transcode("name"));
    DOMText* columnNameText = this->_document->createTextNode(columnName);
    
    XMLCh* dataType = XMLString::transcode(pDataType.c_str());
    DOMElement* columnDataTypeNode = this->_document->createElement(XMLString::transcode("datType"));
    DOMText* columnDataTypeText = this->_document->createTextNode(dataType);
    
    XMLCh* bytes = XMLString::transcode(pBytes.c_str());
    DOMElement* columnBytesNode = this->_document->createElement(XMLString::transcode("bytes"));
    DOMText* columnBytesText = this->_document->createTextNode(bytes);
    
    dataBaseRoot->appendChild(newTable);
    
    newTable->appendChild(columns);
    
    columns->appendChild(newColumn);
    
    newColumn->appendChild(columnNameNode);
    columnNameNode->appendChild(columnNameText);
    
    newColumn->appendChild(columnDataTypeNode);
    columnDataTypeNode->appendChild(columnDataTypeText);
    
    newColumn->appendChild(columnBytesNode);
    columnBytesNode->appendChild(columnBytesText);

    this->writeInDocument();
     
}

/**
 * Function that creates a new column in a specific table in the data base
 * 
 * @param pTableName - The name of the table
 * @param pColumnName - The name of the column
 * @param pDataType - The data type that is saved
 * @param pBytes - The number of bytes needed
 */
void XMLDocument::createColumnInTable(std::string pTableName, std::string pColumnName, std::string pDataType, std::string pBytes) {
    
    DOMNodeList* tableList = this->_document->getElementsByTagName(XMLString::transcode("table"));
    
    for(int i = 0; i < tableList->getLength(); i++) {
        
        DOMElement* tableElement = dynamic_cast<DOMElement*>(tableList->item(i));
        
        if(XMLString::transcode(tableElement->getAttribute(XMLString::transcode("name"))) == pTableName) {
           
            DOMElement* columns =  dynamic_cast<DOMElement*>(tableElement->getElementsByTagName(XMLString::transcode("columns"))->item(0));
         
            DOMElement* newColumn = this->_document->createElement(XMLString::transcode("column")); 

            XMLCh* columnName = XMLString::transcode(pColumnName.c_str());
            DOMElement* columnNameNode = this->_document->createElement(XMLString::transcode("name"));
            DOMText* columnNameText = this->_document->createTextNode(columnName);
            
            XMLCh* dataType = XMLString::transcode(pDataType.c_str());
            DOMElement* columnDataTypeNode = this->_document->createElement(XMLString::transcode("datType"));
            DOMText* columnDataTypeText = this->_document->createTextNode(dataType);
    
            XMLCh* bytes = XMLString::transcode(pBytes.c_str());
            DOMElement* columnBytesNode = this->_document->createElement(XMLString::transcode("bytes"));
            DOMText* columnBytesText = this->_document->createTextNode(bytes);
            
            columnNameNode->appendChild(columnNameText);
            newColumn->appendChild(columnNameNode);
            
            columnDataTypeNode->appendChild(columnDataTypeText);
            newColumn->appendChild(columnDataTypeNode);
            
            columnBytesNode->appendChild(columnBytesText);
            newColumn->appendChild(columnBytesNode);
            
            columns->appendChild(newColumn);
            
            this->writeInDocument();
            
            break;
            
        }
                 
    }
    
}

/**
 * Function that writes and saves the new data in the XML file
 * 
 */
void XMLDocument::writeInDocument() {
   
  XMLCh* implementType = XMLString::transcode("LS");
  DOMImplementation* pImplement = DOMImplementationRegistry::getDOMImplementation(implementType);
     
  DOMLSSerializer* pSerializer = ((DOMImplementationLS*)pImplement)->createLSSerializer();
  
  DOMConfiguration* pDomConfiguration = pSerializer->getDomConfig();
  pDomConfiguration->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
  
  XMLFormatTarget* pTarget = new LocalFileFormatTarget("masterMetaData.xml");
  
  DOMLSOutput* pDomLsOutput = ((DOMImplementationLS*)pImplement)->createLSOutput();
  pDomLsOutput->setByteStream(pTarget);
  
  pSerializer->write(this->_document, pDomLsOutput);
    
}

// -----------------------------------------------------------------------------
// Deleting XML Methods
// -----------------------------------------------------------------------------

/**
 * Function that deletes a table from the data base
 * 
 * @param pTableName - The name of the table
 */
void XMLDocument::deleteTable(std::string pTableName) {
    
    DOMNodeList* tableList = this->_document->getElementsByTagName(XMLString::transcode("table"));
    
    for(int i = 0; i < tableList->getLength(); i++) {
        
        DOMElement* tableElement = dynamic_cast<DOMElement*>(tableList->item(i));
        
        if(XMLString::transcode(tableElement->getAttribute(XMLString::transcode("name"))) == pTableName) {
            
            this->_document->getDocumentElement()->removeChild(tableElement);
            this->writeInDocument();
            break;
        
        }
        
    }
    
}

/**
 * Function that deletes a column in a specific table from the data base
 * 
 * @param pTableName - The name of the table
 * @param pColumnName - The name of the column
 */
void XMLDocument::deleteColumnInTable(std::string pTableName, std::string pColumnName) {
 
    DOMNodeList* tableList = this->_document->getElementsByTagName(XMLString::transcode("table"));
    
    for(int i = 0; i < tableList->getLength(); i++) {
        
        DOMElement* tableElement = dynamic_cast<DOMElement*>(tableList->item(i));
        
        if(XMLString::transcode(tableElement->getAttribute(XMLString::transcode("name"))) == pTableName) {
            
            DOMElement* columns = dynamic_cast<DOMElement*>(tableElement->getElementsByTagName(XMLString::transcode("columns"))->item(0));
            DOMNodeList* columnsList = columns->getElementsByTagName(XMLString::transcode("column"));
            
            for(int j = 0; j < columnsList->getLength(); j++) {
                
                DOMElement* columnElement = dynamic_cast<DOMElement*>(columnsList->item(j));
                        
                if(XMLString::transcode(columnElement->getElementsByTagName(XMLString::transcode("name"))->item(0)->getTextContent()) == pColumnName) {
                    
                    columns->removeChild(columnElement);
                    this->writeInDocument();
                    break;
                
                }
                    
            }
            
        }
          
    }
    
}


// -----------------------------------------------------------------------------
// Other Methods
// -----------------------------------------------------------------------------

/**
 * Function that creates the necessary parser 
 * 
 */
void XMLDocument::createParser() {
    
    if (!this->_parser) {
        XMLPlatformUtils::Initialize();
        this->_parser = new XercesDOMParser();
        this->_errorHandler = (ErrorHandler*) new XMLErrorHandler();
        this->_parser->setErrorHandler(this->_errorHandler);
    }
    
}