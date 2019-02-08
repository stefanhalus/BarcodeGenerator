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
    std::vector<std::string> svgVector;

    std::cout << "Enter product name (can be empty): ";
    std::string productName;
    getline(std::cin, productName);

    std::cout << "Enter country code (3 digits): ";
    std::string code3;
    std::cin >> code3;
    if (code3.size() != 3)
        return EXIT_FAILURE;

    std::cout << "Enter EAN code (9 digits, no spaces): ";
    std::string code9;
    std::cin >> code9;
    if (code9.size() != 9)
        return EXIT_FAILURE;

    std::string code13 = EAN13::appendChecksum(code3.c_str(), code9.c_str());
    
    std::string svg = EAN13::createSvg(productName, code13);
    svgVector.push_back(svg);
    svgVector.push_back(svg);   // show it multiple times for demonstration purposes
    svgVector.push_back(svg);
    createSampleHtmlPage(svgVector);
    
    std::cout
    << productName << " EAN13 code " << code13
    << " was generated and saved to file " << SAMPLE_HTML_FILENAME << std::endl;

	return EXIT_SUCCESS;
}
