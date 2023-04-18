//
//  main.cpp
//  FOODIE_Project
//
//  Created by Isabel Dailey on 4/18/23.
//

#include "rankedListGenerator.h"
#include "stdc++.h"

int main(){
    int orderNumber = 1;
    string yesNo;
    // Part B
    do{
        cout << "Would you like to make a new order? (y/n) ";
        cin >> yesNo;
        if(yesNo == "y"){ FOODIE_BAGGER(orderNumber++); }
    
        cout << "Hope this works!" << endl;
        // Hi
        // HI2
        cout << "Part A here or separate program? " << endl;
        
        cout << "--------------------------------------" << endl;
        cout << "Continue? (y/n) ";
        cin >> yesNo;
    } while(yesNo == "y");

    return 0;
}
