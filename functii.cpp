//
//  functii.cpp
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
 * @return Loading application Header
 */

#include <sstream>

#include "functii.h"

#define N_LINES         95
#define DIGIT_SPACING   7   // each digit is seven lines apart


namespace EAN13
{
    static uint8_t b[N_LINES];   // vertical lines in the image

    // To indirectly encode the first digit
    static bool parities[10][6] = {
        {0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 1, 1}, {0, 0, 1, 1, 0, 1}, {0, 0, 1, 1, 1, 0}, {0, 1, 0, 0, 1, 1},
        {0, 1, 1, 0, 0, 1}, {0, 1, 1, 1, 0, 0}, {0, 1, 0, 1, 0, 1}, {0, 1, 0, 1, 1, 0}, {0, 1, 1, 0, 1, 0}
    };

    /**
 * @author: Stefan Halus
 * @version: 1.0
 * @return Completes the 9-digit string in the code with the previous missing digits, replaced by 7
 * @param codDat[] User-entered Code
 */
std::string appendChecksum(const char countryCode[], const char codDat[])
{
    int n = strlen(codDat);
    int i = 0;
    char sirSapte[9] = "";
    
	while (codDat[i] >= '0' && codDat[i] <= '9')
		i++;

    if (i != n)
		std::cerr << "Error code: " << codDat << std::endl;

    // Patch missing digits with 7. Why ?
    if (n < 9) {
		int j;
		for (j = 0; j < 9 - n; j++)
            sirSapte[j] = '7';

        sirSapte[j] = '\0';
	}

    char ean13[13];
    strcpy(ean13, countryCode);
	strcat(ean13, sirSapte);
	strcat(ean13, codDat);

    int checkSum = calculateChecksum(ean13);
	ean13[12] = checkSum + '0';

    return ean13;
}

/**
 * @author: Stefan Halus
 * @version: 1.0
 * @return Generates the EAN13 checksum digit
 * @param  ean12 is the string value of the code entered
 */
int calculateChecksum(const std::string ean13)
{
    int evens = 0;
    int odds = 0;

    for (int i = 0; i < 12; i = i + 2) {
		evens += ean13[i] - '0';
		odds  += ean13[i + 1] - '0';
	}

    int S = evens + 3 * odds;
	int checkSum = 10 - S % 10;
    if (checkSum == 10)
        checkSum = 0;
    
	return checkSum;
}

/**
 * Generates the bit string required for the bar code, group G (even)
 * @param valoare is the value or figure to convert
 * @param b[] Matrix with written bits
 * @param poz The starting bit of the attribution
 */
void G(const int valoare,
       const int poz)
{
	switch ((valoare - '0')) {
	case 0: // 0100111
		b[poz + 1] = b[poz + 4] = b[poz + 5] = b[poz + 6] = 1;
		break;
	case 1: // 0110011
		b[poz + 1] = b[poz + 2] = b[poz + 5] = b[poz + 6] = 1;
		break;
	case 2: //0011011
		b[poz + 2] = b[poz + 3] = b[poz + 5] = b[poz + 6] = 1;
		break;
	case 3: //0100001
		b[poz + 1] = b[poz + 6] = 1;
		break;
	case 4: //0011101
		b[poz + 2] = b[poz + 3] = b[poz + 4] = b[poz + 6] = 1;
		break;
	case 5: // 0111001
		b[poz + 1] = b[poz + 2] = b[poz + 3] = b[poz + 6] = 1;
		break;
	case 6: //0000101
		b[poz + 4] = b[poz + 6] = 1;
		break;
	case 7: //  0010001
		b[poz + 2] = b[poz + 6] = 1;
		break;
	case 8: //  0001001
		b[poz + 3] = b[poz + 6] = 1;
		break;
	case 9: // 0010111
		b[poz + 2] = b[poz + 4] = b[poz + 5] = b[poz + 6] = 1;
		break;
	}
}

/**
 * Generates the bit string required for the bar code, group L (odd)
 * @param Value is the value or figure to convert
 * @param b[] Matrix with written bits
 * @param poz The starting bit of the attribution
 */
void L(const int valoare,
       const int poz)
{
	switch ((valoare - '0')) {
	case 0: // 0001101
		b[poz + 3] = b[poz + 4] = b[poz + 6] = 1;
		break;
	case 1: // 0011001
		b[poz + 2] = b[poz + 3] = b[poz + 6] = 1;
		break;
	case 2: // 0010011
		b[poz + 2] = b[poz + 5] = b[poz + 6] = 1;
		break;
	case 3: // 0111101
		b[poz + 1] = b[poz + 2] = b[poz + 3] = b[poz + 4] = b[poz + 6] = 1;
		break;
	case 4: // 0100011
		b[poz + 1] = b[poz + 5] = b[poz + 6] = 1;
		break;
	case 5: // 0110001
		b[poz + 1] = b[poz + 2] = b[poz + 6] = 1;
		break;
	case 6: // 0101111
		b[poz + 1] = b[poz + 3] = b[poz + 4] = b[poz + 5] = b[poz + 6] = 1;
		break;
	case 7: // 0111011
		b[poz + 1] = b[poz + 2] = b[poz + 3] = b[poz + 5] = b[poz + 6] = 1;
		break;
	case 8: // 0110111
		b[poz + 1] = b[poz + 2] = b[poz + 4] = b[poz + 5] = b[poz + 6] = 1;
		break;
	case 9: // 0001011
		b[poz + 3] = b[poz + 5] = b[poz + 6] = 1;
		break;
	}
}

/**
 * Generates the bit string required for the bar code, pattern R
 * @param valoare este valoarea sau cifra de convertit
 * @param b[] matricea cu biții scriși
 * @param poz bitul de start de la care se face atribuirea
 */
void R(const int valoare,
       const int poz)
{
	switch ((valoare - '0')) {
	case 0: //		1110010
		b[poz] = b[poz + 1] = b[poz + 2] = b[poz + 5] = 1;
		break;
	case 1: //		1100110
		b[poz] = b[poz + 1] = b[poz + 4] = b[poz + 5] = 1;
		break;
	case 2: //		1101100
		b[poz] = b[poz + 1] = b[poz + 3] = b[poz + 4] = 1;
		break;
	case 3: //		1000010
		b[poz] = b[poz + 5] = 1;
		break;
	case 4: //		1011100
		b[poz] = b[poz + 2] = b[poz + 3] = b[poz + 4] = 1;
		break;
	case 5: //		1001110
		b[poz] = b[poz + 3] = b[poz + 4] = b[poz + 5] = 1;
		break;
	case 6: //		1010000
		b[poz] = b[poz + 2] = 1;
		break;
	case 7: //		1000100
		b[poz] = b[poz + 4] = 1;
		break;
	case 8: //		1001000
		b[poz] = b[poz + 3] = 1;
		break;
	case 9: //		1110100
		b[poz] = b[poz + 1] = b[poz + 2] = b[poz + 4] = 1;
		break;
	}
}

/**
 * @author: Stefan Halus
 * @version: 1.0
 * @return Generates HTML + SVG code that represents the barcode and related explanatory texts
 * @param nean13 represents the final bar code, including the amount of control
 */
std::string createSvg(const std::string &productName,
                      const std::string &productCode)
{
    for (int i = 0; i < N_LINES; i++)
        b[i] = 0;

    // lead
    b[0] = b[2] = 1;
	b[1] = 0;

    uint8_t start = productCode[0] - '0';

    for (int i = 0; i < 6; i++)
        if (parities[start][i])
            G(productCode[1 + i], 3 + i * DIGIT_SPACING);
        else
            L(productCode[1 + i], 3 + i * DIGIT_SPACING);

    // separator
    b[45] = b[47] = b[49] = 0;
	b[46] = b[48] = 1;

    for (int i = 0; i < 6; i++)
		R(productCode[7 + i], 50 + i * DIGIT_SPACING);

    // trail
    b[92] = b[94] = 1;
	b[93] = 0;

    std::ostringstream cod;
	cod << "<svg height=\"70\" width=\"200\">" << std::endl;
    
    if (!productName.empty())
        cod << "<text x=\"104\" y=\"16\" letter-spacing=\"2\" text-anchor=\"middle\">"
			<< productName << "</text>" << std::endl;

    int pozx = 10, y2;
	for (int i = 0; i < N_LINES; i++) {
		if (b[i] == 1) {
			if (i == 0 || i == 2 || i == 46 || i == 48 || i == 92 || i == 94) {
				y2 = 65;
			} else {
				y2 = 50;
			}
			cod << "<line x1=\"" << pozx << "\" y1=\"20\" x2=\"" << pozx
					<< "\" y2=\"" << y2
					<< "\" style=\"stroke:rgb(0,0,0); stroke-width:2\" />"
					<< std::endl;
		}
		pozx += 2;
	}

    // Show numeric value of code under the bars
    cod << "<text x=\"-1\" y=\"64\">" << productCode[0] << "</text>" << std::endl;
	cod << "<text x=\"21\" y=\"64\" letter-spacing=\"5\">" << productCode[1]
			<< productCode[2] << productCode[3] << productCode[4] << productCode[5]
			<< productCode[6] << "</text>" << std::endl;
	cod << "<text x=\"113\" y=\"64\" letter-spacing=\"5\">" << productCode[7]
			<< productCode[8] << productCode[9] << productCode[10] << productCode[11]
			<< productCode[12] << "</text>" << std::endl;

    cod << "</svg>";

    return cod.str();
}

}
