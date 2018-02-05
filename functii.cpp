/**
 * Created on: 3 dec. 2016
 * @author: Stefan Halus
 * @version: 1.0
 * @return Se încarcă headerul aplicației
 */

#include "functii.h";
/**
 * @author: Stefan Halus
 * @version: 1.0
 * @return Inițializează toți biții din matricea codului de bare cu 0.
 * @param b[] încarcă variabila globală
 */
void barsInitialize(int b[]) {
	for (int i = 0; i < 96; i++) {
		b[i] = 0;
	}
}
/**
 * @author: Stefan Halus
 * @version: 1.0
 * @return Completează șirul de 9 cifre din cod cu cifrele lipsă precedente, înlocuite cu 7
 * @param codDat[] codul introdus de utilizator
 */
string numberFullFill(char codDat[]) {
	int lungime = strlen(codDat), i = 0;
	char sirSapte[9] = "", codRO[] = "594", ean13[13];
	while (codDat[i] >= '0' && codDat[i] <= '9')
		i++;
	if (i != lungime) {
		cout << "Cod eronat: " << codDat << endl;
	}
	if (lungime < 9) {
		int j;
		for (j = 0; j < 9 - lungime; j++)
			sirSapte[j] = '7';
		sirSapte[j] = '\0';
	}
	strcpy(ean13, codRO);
	strcat(ean13, sirSapte);
	strcat(ean13, codDat);
	int checkSum = numberControlDigit(ean13);
	ean13[12] = checkSum + '0';
	numberControlDigit(ean13);
	return ean13;
}
/**
 * @author: Stefan Halus
 * @version: 1.0
 * @return Generează suma de control a codului EAN13
 * @param  ean12 este valoarea string a codului introdus
 */
int numberControlDigit(string ean13) {
	int nean13[13], s1 = 0, s2 = 0, S = 0, checkSum = 0;
	for (int j = 0; j < 12; j++)
		nean13[j] = ean13[j] - '0';
	for (int i = 0; i < 12; i = i + 2) {
		s1 = s1 + nean13[i];
		s2 = s2 + nean13[i + 1];
	}
	S = s1 + 3 * s2;
	checkSum = 10 - S % 10;
	return checkSum;
}
/**
 * @author: Stefan Halus
 * @version: 1.0
 * @return Generează șirul de biți necesar pentru codul de bare, grupa G
 * @param valoare este valoarea sau cifra de convertit
 * @param b[] matricea cu biții scriși
 * @param poz bitul de start de la care se face atribuirea
 */
void G(int valoare, int b[], int poz) {
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
 * @author: Stefan Halus
 * @version: 1.0
  * @return Generează șirul de biți necesar pentru codul de bare, grupa L
 * @param valoare este valoarea sau cifra de convertit
 * @param b[] matricea cu biții scriși
 * @param poz bitul de start de la care se face atribuirea
 */
void L(int valoare, int b[], int poz) {
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
 * @author: Stefan Halus
 * @version: 1.0
  * @return Generează șirul de biți necesar pentru codul de bare, grupa R
 * @param valoare este valoarea sau cifra de convertit
 * @param b[] matricea cu biții scriși
 * @param poz bitul de start de la care se face atribuirea
 */
void R(int valoare, int b[], int poz) {
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
 * @return Generează codul HTML + SVG care reprezintă codul de bare și textele explicative asociate
 * @param nean13 reprezintă codul de bare final, inclusiv suma de control
 * @param b[] matricea cu biții corespunzători codului de bare
 */
void barCodeDrawer(string nean13, int b[]) {
	fstream cod;
	extern string produsNume;
	extern string produsCod;
	b[0] = b[2] = 1;
	b[1] = 0;
	L(nean13[1], b, 3);
	G(nean13[2], b, 10);
	G(nean13[3], b, 17);
	L(nean13[4], b, 24);
	L(nean13[5], b, 31);
	G(nean13[6], b, 38);
	b[45] = b[47] = b[49] = 0;
	b[46] = b[48] = 1;
	for (int i = 0; i < 6; i++)
		R(nean13[7 + i], b, 50 + i * 7);
	b[92] = b[94] = 1;
	b[93] = 0;
	cod.open("cod.html", ios::out);
	cod << "<!DOCTYPE html>" << endl;
	cod << "<html><body><center>" << endl;
	cod << "<svg height=\"70\" width=\"200\">" << endl;
	cod
			<< "<text x=\"104\" y=\"16\" letter-spacing=\"2\" text-anchor=\"middle\">"
			<< produsNume << "</text>" << endl;
	int pozx = 10, y2;
	for (int i = 0; i < 95; i++) {
		if (b[i] == 1) {
			if (i == 0 || i == 2 || i == 46 || i == 48 || i == 92 || i == 94) {
				y2 = 65;
			} else {
				y2 = 50;
			}
			cod << "<line x1=\"" << pozx << "\" y1=\"20\" x2=\"" << pozx
					<< "\" y2=\"" << y2
					<< "\" style=\"stroke:rgb(0,0,0); stroke-width:2\" />"
					<< endl;
		}
		pozx = pozx + 2;
	}
	cod << "<text x=\"-1\" y=\"64\">" << produsCod[0] << "</text>" << endl;
	cod << "<text x=\"21\" y=\"64\" letter-spacing=\"5\">" << produsCod[1]
			<< produsCod[2] << produsCod[3] << produsCod[4] << produsCod[5]
			<< produsCod[6] << "</text>" << endl;
	cod << "<text x=\"113\" y=\"64\" letter-spacing=\"5\">" << produsCod[7]
			<< produsCod[8] << produsCod[9] << produsCod[10] << produsCod[11]
			<< produsCod[12] << "</text>" << endl;
	cod << "</svg>" << endl;
	cod << "</center></body></html>" << endl;
	cod.close();
	cout << endl << endl << produsNume << ", cod " << produsCod
			<< " a fost generat și salvat." << endl;
}
