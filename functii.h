/**
 * Created on: 3 dec. 2016
 * @author: Stefan Halus
 * @version: 1.0
 * @return Încară prototipul funcțiilor fonosite pentru efectuarea activităților programului.
 */

#ifndef FUNCTII_H_
#define FUNCTII_H_

#include <iostream>
#include <cstring>

#include <fstream>
using namespace std;

void barsInitialize(int b[]);
string numberFullFill(char[]);
int numberControlDigit(string);
void G(int, int[], int);
void L(int, int[], int);
void R(int, int[], int);
void barCodeDrawer(string, int[]);

#endif
/* FUNCTII_H_ */
