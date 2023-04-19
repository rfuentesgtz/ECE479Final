//
//  rankedListGenerator.h
//  FOODIE_Project2
//
//  Created by Isabel Dailey on 4/19/23.
//
#ifndef RANKEDLISTGENERATOR_H // To make sure you don't declare the function more than once by including the header multiple times.
#define RANKEDLISTGENERATOR_H

#include <iostream>
#include "stdc++.h"
#include <fstream>

using namespace std;

int bagPoints(int item, int itemQty);
int numFreezerBag(vector<int> freezerBag);

bool maxBagPointsFrozen(int totalBagPoints);
bool maxBagCapacity(bool reachedMax, int totalPoints);

vector<int> rule1(vector<int> frozen);

void FOODIE_BAGGER(int orderNumber);

#endif
