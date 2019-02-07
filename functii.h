//
//  functii.h
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
 * @return Încară prototipul funcțiilor fonosite pentru efectuarea activităților programului.
 */

#ifndef FUNCTII_H_
#define FUNCTII_H_

#include <iostream>
#include <cstring>

#include <fstream>

void barsInitialize(int b[]);
std::string numberFullFill(const char[], const char[]);
int numberControlDigit(std::string);
void G(int, int[], int);
void L(int, int[], int);
void R(int, int[], int);
void barCodeDrawer(std::string, int[]);

#endif
/* FUNCTII_H_ */
