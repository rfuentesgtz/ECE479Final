//
//  rankedListGenerator.cpp
//  FOODIE_Project2
//
//  Created by Isabel Dailey on 4/19/23.
//

#include "rankedListGenerator.h"
#include <stdio.h>
#include "stdc++.h"
//#include "FreezerBag.h"

typedef std::vector<int> vec_t;
typedef std::map<int, vec_t> map_t;

using namespace std;
/* Functions needed for Rule Implementation */
// Function for determining the totalBagPoints
int bagPoints(int item, int itemQty){
    int totalBagPoints = 0;
    /* Food Item References:
     1. Eggs
     2. Chocolate
     3. Apples
     4. Peanut Butter
     5. Jelly
     
     6. Ice Cream
     7. Chips
     8. Cereal
     9. Bread
     10. Granola Bar
     
     11. Watermelon
     12. Protein Powder
     13. Bag Of Potatoes
     14. Bag Of Ice
     15. Water Jug
     */
    // Small Items worth 1 point
    if(item == 1 || item == 2 || item == 3 || item == 4 || item == 5){ totalBagPoints = 1 * itemQty; }
    
    // Medium Items worth 2 points
    if(item == 6 || item == 7 || item == 8 || item == 9 || item == 10){ totalBagPoints = 2 * itemQty; }
    
    // Large Items worth 3 points
    if(item == 11 || item == 12 || item == 13 || item == 14 || item == 15){ totalBagPoints = 3 * itemQty; }
    
    return totalBagPoints;
}

// Function to check if totalBagPoints has exceeded bag point limit for the frozen food items (7 points max)
bool maxBagPointsFrozen(int totalBagPoints){
    bool reachedMax = false;
    
    if(totalBagPoints > 7){ reachedMax = true; }
    
    else{ reachedMax = false; }
    
    return reachedMax;
}

// Function to check if totalBagPoints has exceeded bag point limit for the normal food items (9 points max)
bool maxBagPointsNormal(int totalBagPoints){
    bool reachedMax = false;
    
    if(totalBagPoints > 9){ reachedMax = true; }
    
    else{ reachedMax = false; }
    
    return reachedMax;
}

// Function to check if bag has reached its max capacity if totalBagPoints has not reached 7 or 9 (depending on if the items in order are frozen or normal)
bool maxBagCapacity(bool reachedMax, int totalPoints){
    bool bagFull = false;
    if(reachedMax == true){ bagFull = true; }
    
    else{ bagFull = false; }
    
    return bagFull;
}

// Rule Implementation:
// ## Rule #1: If food item is frozen, then put it in frozen item bag ## //
vector<int> rule1(vector<int> frozen){
    vector<int> freezerBag;

    freezerBag.insert(freezerBag.begin(), frozen.at(0));
    freezerBag.insert(freezerBag.begin() + 1, frozen.at(1));
    
    return freezerBag;
}

// Function for determining the max number of freezer bags needed
int numFreezerBag(vector<int> freezerBag){
    int numFreezerBags = 1;
    
    // Max Ice Cream tub per bag is 2 and Max Bag Of Ice is 1
    if(freezerBag.at(0) > 2 && freezerBag.at(0) <= 8){ numFreezerBags = freezerBag.at(0)/2; }
   
    // Max Bag Of Ice per bag is 1
    if(freezerBag.at(1) > 1 && freezerBag.at(1) <= 4){ numFreezerBags = freezerBag.at(1); }
        
    return numFreezerBags;
}

// Function to split the items into the appropriate bags (frozen items)
vector<vector<int>> bagFrozenItems(int numFreezerBags, vector<int> freezerBag){
    vector<vector<int>> frozenBags;
    vector<int> frozenBag1, frozenBag2, frozenBag3, frozenBag4;

    // Medium Items
    // Handling simple cases (1 bag case)
    if(freezerBag.at(0) == 0){ frozenBag1.insert(frozenBag1.begin(), 0); }
    if(freezerBag.at(0) == 1){ frozenBag1.insert(frozenBag1.begin(), 1); }
    if(freezerBag.at(0) == 2){ frozenBag1.insert(frozenBag1.begin(), 2); }
        
    // If number of medium items is not 0, 1, or 2, then items need to carry over into next bag
    switch(freezerBag.at(0)){
            // 2 bag case
        case 3:
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 1);
            break;
        case 4:
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 2);
            break;
            
            // 3 bag case
        case 5:
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 2);
            frozenBag3.insert(frozenBag3.begin(), 1);
            break;
        case 6:
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 2);
            frozenBag3.insert(frozenBag3.begin(), 2);
            break;
            
            // 4 bag case
        case 7:
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 2);
            frozenBag3.insert(frozenBag3.begin(), 2);
            frozenBag3.insert(frozenBag4.begin(), 1);
            break;
            
        case 8:
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 2);
            frozenBag3.insert(frozenBag3.begin(), 2);
            frozenBag3.insert(frozenBag4.begin(), 2);
            break;
    }
    
    // Large Items
    // Handling simple cases (1 bag case)
    if(freezerBag.at(1) == 0){ frozenBag1.insert(frozenBag1.begin(), 0); }
    if(freezerBag.at(1) == 1){ frozenBag1.insert(frozenBag1.begin(), 1); }
    
    // If number of large items is not 0, 1, or 2, then items need to carry over into next bag
    if(freezerBag.at(1) == 2){ // 2 bag case
        frozenBag1.insert(frozenBag1.begin() + 1, 1);
        frozenBag2.insert(frozenBag2.begin() + 1, 1);
    }
    
    if(freezerBag.at(1) == 3){ // 3 bag case
        frozenBag1.insert(frozenBag1.begin() + 1, 1);
        frozenBag2.insert(frozenBag2.begin() + 1, 1);
        frozenBag3.insert(frozenBag3.begin() + 1, 1);
    }
    
    if(freezerBag.at(0) == 4){ // 4 bag case
        frozenBag1.insert(frozenBag1.begin() + 1, 1);
        frozenBag2.insert(frozenBag2.begin() + 1, 1);
        frozenBag3.insert(frozenBag3.begin() + 1, 1);
        frozenBag3.insert(frozenBag4.begin() + 1, 1);
    }
    
    cout << frozenBag1.at(0) << " " << frozenBag1.at(1) << endl;
    cout << frozenBag2.at(0) << " " << frozenBag2.at(1) << endl;
    cout << frozenBag3.at(0) << " " << frozenBag3.at(1) << endl;
    cout << frozenBag4.at(0) << " " << frozenBag4.at(1) << endl;
    
    frozenBags.insert(frozenBags.begin() + 0, frozenBag1);
    frozenBags.insert(frozenBags.begin() + 1, frozenBag2);
    frozenBags.insert(frozenBags.begin() + 2, frozenBag3);
    frozenBags.insert(frozenBags.begin() + 3, frozenBag4);
    
    if(numFreezerBags == 1){ frozenBags.insert(frozenBags.begin() + 0, frozenBag1); }
    if(numFreezerBags == 2){
        frozenBags.insert(frozenBags.begin() + 0, frozenBag1);
        frozenBags.insert(frozenBags.begin() + 1, frozenBag2);
    }
    if(numFreezerBags == 3){
        frozenBags.insert(frozenBags.begin() + 0, frozenBag1);
        frozenBags.insert(frozenBags.begin() + 1, frozenBag2);
        frozenBags.insert(frozenBags.begin() + 2, frozenBag3);
    }
    if(numFreezerBags == 4){
        frozenBags.insert(frozenBags.begin() + 0, frozenBag1);
        frozenBags.insert(frozenBags.begin() + 1, frozenBag2);
        frozenBags.insert(frozenBags.begin() + 2, frozenBag3);
        frozenBags.insert(frozenBags.begin() + 2, frozenBag3);
    }
    
    return frozenBags;
}

void FOODIE_BAGGER(int orderNumber){
    int item;
    int itemQty = 0;
    int freezerBagCount = 0;
    int normalBagCount = 0;
    int totalBagPoints = 0;
    int numSmallItems = 0;
    int numMediumItems = 0;
    int numLargeItems = 0;
    vector<int> normalBag;
    vector<int> freezerBag;
    vector<vector<int>> frozenBags;
    string keepGoing;
    vector<int> qty = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Vector for food item quantities
    vector<int> frozen, normal, crushable; // Vectors for final values of certain items
    // Vectors for food items with their numbers (this is a reference; these will never be used)
    vector<string> frozenItems = {"5 Ice Cream", "13 Bag Of Ice"};
    vector<string> normalItems = {"1 Chocolate", "3 Peanut Butter", "4 Jelly", "7 Cereal", "9 Granola Bar", "10 Watermelon", "11 Protein Powder", "12 Bag Of Potatoes", "14 Water Jug"};
    vector<string> crushableItems = {"0 Eggs", "2 Apples","6 Chips", "8 Bread"};
    
    do{
        cout << "Order Number: " << orderNumber << endl;
        cout << "Items For Bagging: \t\t\t Quantity:" << endl;
        cout << "0. Eggs\t\t\t\t\t\t\t" << qty[0] << endl;
        cout << "1. Chocolate\t\t\t\t\t" << qty[1] << endl;
        cout << "2. Apples\t\t\t\t\t\t" << qty[2] << endl;
        cout << "3. Peanut Butter\t\t\t\t"<< qty[3] << endl;
        cout << "4. Jelly\t\t\t\t\t\t" << qty[4] << endl;
        cout << "5. Ice Cream\t\t\t\t\t" << qty[5] << endl;
        cout << "6. Chips\t\t\t\t\t\t" << qty[6] << endl;
        cout << "7. Cereal\t\t\t\t\t\t" << qty[7] << endl;
        cout << "8. Bread\t\t\t\t\t\t" << qty[8] << endl;
        cout << "9. Granola Bar\t\t\t\t\t" << qty[9] << endl;
        cout << "10. Watermelon\t\t\t\t\t" << qty[10] << endl;
        cout << "11. Protein Powder\t\t\t\t" << qty[11] << endl;
        cout << "12. Bag Of Potatoes\t\t\t\t" << qty[12] << endl;
        cout << "13. Bag Of Ice\t\t\t\t\t" << qty[13] << endl;
        cout << "14. Water Jug\t\t\t\t\t" << qty[14] << endl << endl;
        
        do{
            cout << "What items would you like? (Enter item number) ";
            cin >> item;
            if(item == 0){ cout << "Error: Please enter a number between 1 and 15" << endl; }
            if(item >= 16){ cout << "Error: Please enter a number between 1 and 15" << endl; }
        } while(item == 0 || item >= 16);
        
        cout << "How many of " << item << " would you like to add? ";
        cin >> itemQty;
        
        // Update the value of item quantity based on user's selection of item
        qty[item] = itemQty;
        
        cout << "Would you like to add more items? (y/n) ";
        cin >> keepGoing;
        cout << endl;
    } while(keepGoing != "n");
    
    if(keepGoing == "n"){
        // Display the items and the quantity of each item the user chose
        cout << "Total Items For Bagging: " << endl;
        cout << "0. Eggs\t\t\t\t\t\t\t" << qty[0] << endl;
        cout << "1. Chocolate\t\t\t\t\t" << qty[1] << endl;
        cout << "2. Apples\t\t\t\t\t\t" << qty[2] << endl;
        cout << "3. Peanut Butter\t\t\t\t"<< qty[3] << endl;
        cout << "4. Jelly\t\t\t\t\t\t" << qty[4] << endl;
        cout << "5. Ice Cream\t\t\t\t\t" << qty[5] << endl;
        cout << "6. Chips\t\t\t\t\t\t" << qty[6] << endl;
        cout << "7. Cereal\t\t\t\t\t\t" << qty[7] << endl;
        cout << "8. Bread\t\t\t\t\t\t" << qty[8] << endl;
        cout << "9. Granola Bar\t\t\t\t\t" << qty[9] << endl;
        cout << "10. Watermelon\t\t\t\t\t" << qty[10] << endl;
        cout << "11. Protein Powder\t\t\t\t" << qty[11] << endl;
        cout << "12. Bag Of Potatoes\t\t\t\t" << qty[12] << endl;
        cout << "13. Bag Of Ice\t\t\t\t\t" << qty[13] << endl;
        cout << "14. Water Jug\t\t\t\t\t" << qty[14] << endl << endl;
        
        // Split qty vector into the three category vectors -- frozen, normal, and crushable -- based on item number
        frozen = {qty.at(5), qty.at(13)};
        normal = {qty.at(1), qty.at(3), qty.at(4), qty.at(7), qty.at(9), qty.at(10), qty.at(11), qty.at(12), qty.at(14)};
        crushable = {qty.at(0), qty.at(2), qty.at(6), qty.at(8)};
        
        cout << "The total number of items bag of each item type is: " << endl;
        cout << "Frozen: " << endl;
        cout << "\t" << frozen.at(0) << " Tubs of Ice Cream" << endl;
        cout << "\t" << frozen.at(1) << " Bags of Ice" << endl;
        
        cout << "Normal: " << endl;
        cout << "\t" << normal.at(0) << " Pieces of Chocolate" << endl;
        cout << "\t" << normal.at(1) << " Jars of Peanut Butter" << endl;
        cout << "\t" << normal.at(2) << " Jars of Jelly" << endl;
        cout << "\t" << normal.at(3) << " Boxes of Cereal" << endl;
        cout << "\t" << normal.at(4) << " Boxes of Granola Bars" << endl;
        cout << "\t" << normal.at(5) << " Watermelons" << endl;
        cout << "\t" << normal.at(6) << " Containers of Protein Powder" << endl;
        cout << "\t" << normal.at(7) << " Bags Of Potatoes" << endl;
        cout << "\t" << normal.at(8) << " Water Jugs" << endl;
        
        cout << "Crushable: " << endl;
        cout << "\t" << crushable.at(0) << " Dozen Eggs" << endl;
        cout << "\t" << crushable.at(1) << " Bunches of Apples" << endl;
        cout << "\t" << crushable.at(2) << " Bags of Chips" << endl;
        cout << "\t" << crushable.at(3) << " Loaves of Bread" << endl;
        
        // Now bag the items
        cout << "Determining optimal bagging ... " << endl;
        // Rule Implementation
        // Rule #1
        freezerBag = rule1(frozen);
        
        cout << "Before Item Limit: " << freezerBag.at(0) << " " << freezerBag.at(1) << endl;
        
        if(freezerBag.at(0) > 8){
            cout << "Max number of medium items reached" << endl;
            freezerBag.at(0) = 8;
        }
        
        else{ freezerBag.at(0) = freezerBag.at(0); }
        
        if(freezerBag.at(1) > 4){
            cout << "Max number of large items reached" << endl;
            freezerBag.at(1) = 4;
        }
        
        else{ freezerBag.at(1) = freezerBag.at(1); }
        
        cout << "After Item Limit: " << freezerBag.at(0) << " " << freezerBag.at(1) << endl;
        
        freezerBagCount = numFreezerBag(freezerBag); 
        
        cout << "Freezer Bags Required: " << freezerBagCount << endl;
        
        frozenBags = bagFrozenItems(freezerBagCount, freezerBag);
        
        /*
        cout << frozenBags.at(0) << endl;
        cout << frozenBags.at(1) << endl;
        cout << frozenBags.at(2) << endl;
        cout << frozenBags.at(3) << endl;
        */
        /*
        totalBagPoints = bagPoints(item, itemQty);
        cout << "Total Bag Points: " << totalBagPoints << endl;
        */
        
        
    }
    
}
