//
//  main.cpp
//  FOODIE_Project2
//
//  Created by Isabel Dailey on 4/19/23.
//

#include "rankedListGenerator.h"
#include "stdc++.h"
using namespace std;

int main(){
    int orderNumber = 1;
    string yesNo;
    // Part B
    do{
        cout << "Would you like to make a new order? (y/n) ";
        cin >> yesNo;
        if(yesNo == "y"){ FOODIE_BAGGER(orderNumber++); }
    
        cout << "Continue? (y/n) ";
        cout << "\n--------------------------------------" << endl;

        cin >> yesNo;
    } while(yesNo == "y");

    return 0;
}
