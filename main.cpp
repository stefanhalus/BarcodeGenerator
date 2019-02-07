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

#include "functii.h"

// https://en.m.wikipedia.org/wiki/List_of_GS1_country_codes
//#define COUNTRY_CODE   "594"    // Romania
#define COUNTRY_CODE   "768"    // Switzerland

int b[95];
std::string productName("unnamed");
std::string productCode;

int main()
{
	barsInitialize(b);

#if 0
	std::cout << "Enter product data: " << std::endl << "Name: ";
	getline(std::cin, productName);
#endif

#if 0
    std::cout << "Cod EAN (max. 9 cifre, no spaces): ";
    char codDat[10];
    std::cin >> codDat;

    std::string codFinal = numberFullFill(COUNTRY_CODE, codDat);
    productCode = codFinal;
    barCodeDrawer(codFinal, b);
#else
    std::cout << __LINE__ << " ESOMEPRAZOL " << numberFullFill(COUNTRY_CODE, "065553001") << std::endl;
    std::cout << __LINE__ << " ESOMEPRAZOL " << numberFullFill(COUNTRY_CODE, "065553002") << std::endl;
    std::cout << __LINE__ << " ESOMEPRAZOL " << numberFullFill(COUNTRY_CODE, "065553004") << std::endl;
    std::cout << __LINE__ << " ESOMEPRAZOL " << numberFullFill(COUNTRY_CODE, "065553010") << std::endl;

    std::cout << __LINE__ << " ESOMEPRAZOL " << numberFullFill(COUNTRY_CODE, "062358003") << std::endl;
#endif

	return EXIT_SUCCESS;
}