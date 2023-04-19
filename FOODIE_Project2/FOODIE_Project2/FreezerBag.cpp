//
//  FreezerBag.cpp
//  FOODIE_Project2
//
//  Created by Isabel Dailey on 4/20/23.
//

#include "FreezerBag.h"
#include "stdc++.h"
using namespace std;

class FreezerBag{
    public:
    vector<int> currentBag;
    FreezerBag();
    typedef map<int, vector<int>> newBag; // map<# of bags, # items of a type in a bag>
};
