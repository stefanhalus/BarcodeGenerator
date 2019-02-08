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

#include <string>
#include <fstream>
#include <vector>

#include "functii.h"

#define SAMPLE_HTML_FILENAME  "cod.html"

int b[95];

void createSampleHtmlPage(const std::vector<std::string> &svgVector)
{
    std::fstream cod;
    
    cod.open(SAMPLE_HTML_FILENAME, std::ios::out);
    cod << "<!DOCTYPE html>" << std::endl;
    cod << "<html><body><center>" << std::endl;
    
    for (auto svg : svgVector)
        cod << "\n<p>" << svg;
    
    cod << "</center></body></html>" << std::endl;
    cod.close();
}

int main(int argc, char ** argv)
{
    std::string productName;
    std::string productCode;
    std::vector<std::string> svgVector;

    EAN13::barsInitialize(b);

    std::cout << "Enter product name (can be empty): ";
    getline(std::cin, productName);

    std::cout << "Enter country code (3 digits): ";
    std::string countryCode;
    std::cin >> countryCode;
    if (countryCode.size() != 3)
        return EXIT_FAILURE;

    std::cout << "Enter EAN code (9 digits, no spaces): ";
    std::string codDat;
    std::cin >> codDat;
    if (codDat.size() != 9)
        return EXIT_FAILURE;

    std::string codFinal = EAN13::numberFullFill(countryCode.c_str(), codDat.c_str());
    productCode = codFinal;
    
    std::string svg = EAN13::createSvg(productName, productCode, codFinal, b);
    svgVector.push_back(svg);
    svgVector.push_back(svg);   // show it multiple times for demonstration purposes
    svgVector.push_back(svg);
    createSampleHtmlPage(svgVector);
    
    std::cout
    << productName << " EAN13 code " << productCode
    << " was generated and saved to file " << SAMPLE_HTML_FILENAME << std::endl;

	return EXIT_SUCCESS;
}
