//
//  main.cpp
//  BarcodeGenerator
//
//  ©ywesee GmbH -- all rights reserved
//  License GPLv3.0 -- see License File
//  Modified by Alex Bettarini on 7 Feb 2019
//

/**
 * Created on: 3 dec. 2016
 * @author: Stefan Halus
 * @version: 1.0
 */

#include <fstream>

#include "functii.h"

int b[95];
std::string productName("unnamed");
std::string productCode;

void createSampleHtmlPage(const std::string &svg)
{
    std::fstream cod;
    
    cod.open("cod.html", std::ios::out);
    cod << "<!DOCTYPE html>" << std::endl;
    cod << "<html><body><center>" << std::endl;
    
    cod << svg;
    
    cod << "</center></body></html>" << std::endl;
    cod.close();
    
    std::cout << std::endl << std::endl
    << productName << ", cod " << productCode
    << " was generated and saved." << std::endl;
}

int main(int argc, char ** argv)
{
	barsInitialize(b);

    std::cout << "Enter product name: ";
    getline(std::cin, productName);

    std::cout << "Country code (3 digits): ";
    char countryCode[4];
    std::cin >> countryCode;

    std::cout << "Code EAN (9 digits, no spaces): ";
    char codDat[10];
    std::cin >> codDat;

    std::string codFinal = numberFullFill(countryCode, codDat);
    productCode = codFinal;
    
    std::string svg = createSvg(codFinal, b);
    createSampleHtmlPage(svg);

	return EXIT_SUCCESS;
}
