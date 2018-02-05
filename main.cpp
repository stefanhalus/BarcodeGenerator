/**
 * Created on: 3 dec. 2016
 * @author: Stefan Halus
 * @version: 1.0
 */

#include "functii.h";
int b[95];
string produsNume;
string produsCod;
int main() {
	barsInitialize(b);
	char codDat[10];
	string codFinal;
	cout << "Introduceti datele produsului: " << endl << "Denumire: ";
	getline(cin, produsNume);
	cout << "Cod EAN (max. 9 cifre, fără spații): ";
	cin >> codDat;
	codFinal = numberFullFill(codDat);
	produsCod = codFinal;
	barCodeDrawer(codFinal, b);
	return 0;
}
