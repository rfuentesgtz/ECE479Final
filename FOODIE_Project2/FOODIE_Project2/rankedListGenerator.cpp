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
     0. Eggs
     1. Chocolate
     2. Apples
     3. Peanut Butter
     4. Jelly
     
     5. Ice Cream
     6. Chips
     7. Cereal
     8. Bread
     9. Granola Bar
     
     10. Watermelon
     11. Protein Powder
     12. Bag Of Potatoes
     13. Bag Of Ice
     14. Water Jug
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

// Function for determining the max number of freezer bags needed
int numFreezerBag(vector<int> freezerBag){
    int numFreezerBags = 1;
    
    if(freezerBag.at(0) == 0 && freezerBag.at(1) == 0){ numFreezerBags = 0; }
    
    // Max Ice Cream tub per bag is 2 and Max Bag Of Ice is 1
    if(freezerBag.at(0) > 2 && freezerBag.at(0) <= 8){ numFreezerBags = freezerBag.at(0)/2; }
   
    // Max Bag Of Ice per bag is 1
    if(freezerBag.at(1) > 1 && freezerBag.at(1) <= 4){ numFreezerBags = freezerBag.at(1); }
        
    return numFreezerBags;
}

void FOODIE_BAGGER(int orderNumber){
    int item;
    int itemQty = 0;
    int frozenBagCount = 0;
    int normalBagCount = 0;
    int spaceInNormalBag = 0;
    int spaceInFreezerBag = 0;
    int numCrushableItems = 0;
    int numCrushableItemsRemaining = 0;
    int numSmallItems = 0;
    int numSmallItemsRemaining = 0;
    int numLargeNormalItems = 0;
    int numLargeNormalItemsRemaining = 0;
    int numLargeFrozenItems = 0;
    int numLargeFrozenItemsRemaining = 0;
    int numMediumNormalItems = 0;
    int numMediumNormalItemsRemaining = 0;
    int numMediumFrozenItems = 0;
    int numMediumFrozenItemsRemaining = 0;
    vector<int> frozen, normal, crushable; // Vectors for final values of certain items in an order
    vector<int> frozenBag, normalBag;
    string keepGoing;
    vector<int> qty = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Vector for food item quantities
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
        
        // Error Checking
        do{
            cout << "What items would you like? (Enter item number) ";
            cin >> item;
            if(item < 0){ cout << "Error: Please enter a number between 1 and 15" << endl; }
            if(item >= 16){ cout << "Error: Please enter a number between 1 and 15" << endl; }
        } while(item < 0 || item >= 16);
        
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
        
        // Now determine optimal bagging
        cout << "Determining optimal bagging ... " << endl;
        
        // ################################################################ Rule Implentation ################################################################ //
        // Get sums of items ordered based on size, crushability, and food type
        numCrushableItemsRemaining = crushable.at(0) + crushable.at(1) + crushable.at(2) + crushable.at(3);
        numSmallItemsRemaining = normal.at(0) + normal.at(1) + normal.at(2);
        numMediumNormalItemsRemaining = normal.at(3) + normal.at(4);
        numMediumFrozenItemsRemaining = frozen.at(0);
        numLargeNormalItemsRemaining = normal.at(5) + normal.at(6) + normal.at(7) + normal.at(8);
        numLargeFrozenItemsRemaining = frozen.at(1);
        
        // Normal Bags:
        while(numCrushableItemsRemaining + numLargeNormalItemsRemaining + numMediumNormalItemsRemaining + numSmallItemsRemaining >  0){
            normalBagCount++;
            //if(normalBagCount > 4){ cout << "Too many normal bags (max is 4)" << endl; break; }
            cout << "Rule #11: Start new bag " << normalBagCount << " as " << numCrushableItemsRemaining + numSmallItemsRemaining + numMediumNormalItemsRemaining + numLargeNormalItemsRemaining << " normal items remain (" << numCrushableItemsRemaining << " Crushable Item(s), " << numSmallItemsRemaining <<  " Small Item(s), " << numMediumNormalItemsRemaining << " Medium Item(s), " << numLargeNormalItemsRemaining << " Large Item(s))" << endl;
            spaceInNormalBag = 9;
            numCrushableItems = 0;
            numLargeNormalItems = 0;
            numMediumNormalItems = 0;
            numSmallItems = 0;
            if(numLargeNormalItemsRemaining > 0 and spaceInNormalBag >= 3){
                //print Rule #: Put large item ? in bag #
                numLargeNormalItemsRemaining--;
                numLargeNormalItems++;
                spaceInNormalBag = spaceInNormalBag - 3;
            }
            while(numMediumNormalItemsRemaining > 0 and spaceInNormalBag >= 2){
                //print Rule #: Put medium item ? in bag #
                numMediumNormalItemsRemaining--;
                numMediumNormalItems++;
                spaceInNormalBag = spaceInNormalBag - 2;
            }
            while(numSmallItemsRemaining > 0 and spaceInNormalBag >= 2){
                //print Rule #: Put medium item ? in bag #
                numSmallItemsRemaining--;
                numSmallItems++;
                spaceInNormalBag = spaceInNormalBag - 2;
            }
            //print Rule #: Fragile on top
            if(numCrushableItemsRemaining > 0){
                //print Rule #: Will put fragile item ? in top of bag #
                //cout << "Rule #8: If there is a small item and its crushable, add item to current bag and start a new bag" << endl;
                numCrushableItemsRemaining--;
                numCrushableItems++;
                spaceInNormalBag = spaceInNormalBag - 1;
            }
            //print reg bag # contents (top to bottom):
            if (numLargeNormalItems > 0){
                cout << "Number Of Large Items (Normal) = " << numLargeNormalItems << endl;
                //normalBag.insert(normalBag.begin() + 3, numLargeNormalItems);
            }
            if (numMediumNormalItems > 0){
                cout << "Number Of Medium Items (Normal) = " << numMediumNormalItems << endl;
                //normalBag.insert(normalBag.begin() + 2, numMediumNormalItems);
            }
            if (numSmallItems > 0){
                cout << "Number Of Small Items = " << numSmallItems << endl;
                //normalBag.insert(normalBag.begin() + 1, numSmallItems);
            }
            if (numCrushableItems > 0){
                cout << "Number Of Crushable Items = " << numCrushableItems << endl;
                //normalBag.insert(normalBag.begin() + 0, numCrushableItems);
            }
        }
    
        // Frozen Bags:
        while(numMediumFrozenItemsRemaining + numLargeFrozenItemsRemaining >  0){
            frozenBagCount++;
            //if(frozenBagCount > 4){ cout << "Too many frozen bags (max is 4)" << endl; break; }
            cout << "Rule #1: Start new bag " << frozenBagCount << " as " << numMediumFrozenItemsRemaining + numLargeFrozenItemsRemaining << " frozen items remain (" << numMediumFrozenItemsRemaining << " Medium Item(s), " << numLargeFrozenItemsRemaining << " Large Item(s))" << endl;
            spaceInFreezerBag = 7;
            numLargeFrozenItems = 0;
            numMediumFrozenItems = 0;
            numSmallItems = 0;
            if(numLargeFrozenItemsRemaining > 0 and spaceInFreezerBag >= 3){
                //print Rule #: Put large item ? in bag #
                numLargeFrozenItemsRemaining--;
                numLargeFrozenItems++;
                spaceInFreezerBag = spaceInFreezerBag - 3;
                //cout << "Total Bag Points Available After Large (Freezer): " << spaceInFreezerBag << endl << endl;
            }
            while(numMediumFrozenItemsRemaining > 0 and spaceInFreezerBag >= 2){
                //print Rule #: Put medium item ? in bag #
                numMediumFrozenItemsRemaining--;
                numMediumFrozenItems++;
                spaceInFreezerBag = spaceInFreezerBag - 2;
            }
            //print freezer bag # contents (top to bottom):
            if (numLargeFrozenItems > 0){
                cout << "Number Of Large Items (Frozen) = " << numLargeFrozenItems << endl;
                //normalBag.insert(normalBag.begin() + 3, numLargeNormalItems);
            }
            if (numMediumFrozenItems > 0){
                cout << "Number Of Medium Items (Frozen) = " << numMediumFrozenItems << endl;
                //normalBag.insert(normalBag.begin() + 2, numMediumNormalItems);
            }
        }
        
        cout << "################################################################ Order Summary ################################################################" << endl;
        cout << "Total Bags Needed For Order # " << orderNumber << ": " << normalBagCount + frozenBagCount << " (" << normalBagCount << " Normal Bags and " << frozenBagCount << " Freezer Bags)" << endl;
        // Display Normal Bags
        cout << "Normal Bags: " << endl;
        if(normalBagCount == 0){ cout << "\tNo Normal Items Ordered" << endl; }
        else{
            for(int i = 0; i < normalBagCount; i++){
                cout << "\tItems In Bag " << (i + 1) << " (C -> S -> M -> L): " << numCrushableItems << " " << numSmallItems << " " << numMediumNormalItems << " " << numLargeNormalItems << endl;
            }
        }
        cout << endl;
        // Display Freezer Bags
        cout << "Freezer Bags: " << endl;
        if(frozenBagCount == 0){ cout << "\tNo Frozen Items Ordered" << endl; }
        else{
            for(int i = 0; i < frozenBagCount; i++){
                cout << "\tItems In Bag " << (i + 1) << " (M -> L): " << numMediumFrozenItems << " " << numLargeFrozenItems << endl;
            }
        }
        
        cout << "###############################################################################################################################################" << endl;
        
    } // end keepGoing == 'n' if
} // end "FOODIE_BAGGER()
