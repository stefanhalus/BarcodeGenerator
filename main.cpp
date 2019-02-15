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

#define SAMPLE_HTML_FILENAME  "sample.html"

void createSampleHtmlPage(const std::vector<std::string> &svgVector)
{
    std::fstream cod;
    
    cod.open(SAMPLE_HTML_FILENAME, std::ios::out);
    cod << "<!DOCTYPE html>" << std::endl;
    cod << "<html><head><meta charset=\"UTF-8\"></head>" << std::endl;
    cod << "<body bgcolor=\"grey\"><center>" << std::endl;

    for (auto svg : svgVector)
        cod << "\n<p>" << svg;
    
    cod << "</center></body></html>" << std::endl;
    cod.close();
}

int main(int argc, char ** argv)
{
    std::vector<std::string> svgVector;

    while (1) {
        std::cout << std::endl << "Enter product name (empty to terminate list): ";
        std::string productName;
        getline(std::cin, productName);
        
        if (productName.empty()) {
            std::cout << "line " << __LINE__ << std::endl;
            break;
        }

        if (productName == ";") // use ';' to have a barcode without label
            productName.clear();

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

        std::cin.clear();
        std::cin.ignore(100, '\n');

        std::string code13 = EAN13::appendChecksum(code3.c_str(), code9.c_str());
        
        std::string svg = EAN13::createSvg(productName, code13);
        svgVector.push_back(svg);
    }

    if (svgVector.size() > 0) {
        createSampleHtmlPage(svgVector);
        std::cout << " Sample file generated: " << SAMPLE_HTML_FILENAME << std::endl;
    }

	return EXIT_SUCCESS;
}
