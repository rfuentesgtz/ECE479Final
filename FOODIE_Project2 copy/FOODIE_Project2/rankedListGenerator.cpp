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
    int totalBagPoints = 0;
    int numCrushableItems = 0;
    int numSmallItems = 0;
    int newNumSmallItems = 0;
    int numMediumItems = 0;
    int newNumMediumItems = 0;
    int numLargeItems = 0;
    int newNumLargeItems = 0;
    int itemsToReturn = 0;
    vector<int> frozen, normal, crushable, crush; // Vectors for final values of certain items in an order
    vector<int> normalBag, normalBag1, normalBag2, normalBag3, normalBag4;
    vector<int> frozenBag1, frozenBag2, frozenBag3, frozenBag4;
    vector<int> small, medium, large;
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
// Frozen Food
        // Rule #1
        cout << "Frozen Bag(s): " << endl;
        cout << "--- Applying Rule #1: If food is frozen, put it in freezer bag ---" << endl;
        cout << "Before Item Limit: " << frozen.at(0) << " " << frozen.at(1) << endl;
        
        if(frozen.at(0) > 8){
            cout << "Max number of medium items reached" << endl;
            frozen.at(0) = 8;
            cout << "After Item Limit: " << frozen.at(0) << " " << frozen.at(1) << endl;
        }
        
        else{ frozen.at(0) = frozen.at(0); }
        
        if(frozen.at(1) > 4){
            cout << "Max number of large items reached" << endl;
            frozen.at(1) = 4;
            cout << "After Item Limit: " << frozen.at(0) << " " << frozen.at(1) << endl;
        }
        
        else{ frozen.at(1) = frozen.at(1); }
        
        frozenBagCount = numFreezerBag(frozen); 
        
        cout << "Freezer Bags Required: " << frozenBagCount << endl;
        
        // Rule #4
        cout << "--- Applying Rule #4: Bag medium items if not crushable ---" << endl;
        // Bagging frozen items typical cases
        // Medium Items
        if(frozen.at(0) == 0){
            frozenBag1.insert(frozenBag1.begin(), 0);
            frozenBag2.insert(frozenBag2.begin(), 0);
            frozenBag3.insert(frozenBag3.begin(), 0);
            frozenBag4.insert(frozenBag4.begin(), 0);
        }
        
        if(frozen.at(0) == 1){
            frozenBag1.insert(frozenBag1.begin(), 1);
            frozenBag2.insert(frozenBag2.begin(), 0);
            frozenBag3.insert(frozenBag3.begin(), 0);
            frozenBag4.insert(frozenBag4.begin(), 0);
        }
        
        if(frozen.at(0) == 2){
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 0);
            frozenBag3.insert(frozenBag3.begin(), 0);
            frozenBag4.insert(frozenBag4.begin(), 0);
        }
        
        if(frozen.at(0) == 3){
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 1);
            frozenBag3.insert(frozenBag3.begin(), 0);
            frozenBag4.insert(frozenBag4.begin(), 0);
        }
        
        if(frozen.at(0) == 4){
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 2);
            frozenBag3.insert(frozenBag3.begin(), 0);
            frozenBag4.insert(frozenBag4.begin(), 0);
        }
        
        if(frozen.at(0) == 5){
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 2);
            frozenBag3.insert(frozenBag3.begin(), 1);
            frozenBag4.insert(frozenBag4.begin(), 0);
        }
        
        if(frozen.at(0) == 6){
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 2);
            frozenBag3.insert(frozenBag3.begin(), 2);
            frozenBag4.insert(frozenBag4.begin(), 0);
        }
        
        if(frozen.at(0) == 7){
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 2);
            frozenBag3.insert(frozenBag3.begin(), 2);
            frozenBag4.insert(frozenBag4.begin(), 1);
        }
        
        if(frozen.at(0) == 8){
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 2);
            frozenBag3.insert(frozenBag3.begin(), 2);
            frozenBag4.insert(frozenBag4.begin(), 2);
        }
        
        // Large Items
        if(frozen.at(1) == 0){
            frozenBag1.insert(frozenBag1.begin() + 1, 0);
            frozenBag2.insert(frozenBag2.begin() + 1, 0);
            frozenBag3.insert(frozenBag3.begin() + 1, 0);
            frozenBag4.insert(frozenBag4.begin() + 1, 0);
        }
        
        // Rule #2
        cout << "--- Applying Rule #2: If step is bag large items and there is large item, add this item to the bag ---" << endl;
        
        if(frozen.at(1) == 1){
            frozenBag1.insert(frozenBag1.begin() + 1, 1);
            frozenBag2.insert(frozenBag2.begin() + 1, 0);
            frozenBag3.insert(frozenBag3.begin() + 1, 0);
            frozenBag4.insert(frozenBag4.begin() + 1, 0);
        }
        
        if(frozen.at(1) == 2){
            frozenBag1.insert(frozenBag1.begin() + 1, 1);
            frozenBag2.insert(frozenBag2.begin() + 1, 1);
            frozenBag3.insert(frozenBag3.begin() + 1, 0);
            frozenBag4.insert(frozenBag4.begin() + 1, 0);
        }
        
        if(frozen.at(1) == 3){
            frozenBag1.insert(frozenBag1.begin() + 1, 1);
            frozenBag2.insert(frozenBag2.begin() + 1, 1);
            frozenBag3.insert(frozenBag3.begin() + 1, 1);
            frozenBag4.insert(frozenBag4.begin() + 1, 0);
        }
        
        if(frozen.at(1) == 4){
            frozenBag1.insert(frozenBag1.begin() + 1, 1);
            frozenBag2.insert(frozenBag2.begin() + 1, 1);
            frozenBag3.insert(frozenBag3.begin() + 1, 1);
            frozenBag4.insert(frozenBag4.begin() + 1, 1);
        }
        
        // Optimal Bagging cases if there is 0 large items and medium items
        if(frozen.at(0) == 1 && frozen.at(1) == 0){
            frozenBag1.insert(frozenBag1.begin(), 1);
            frozenBag2.insert(frozenBag2.begin(), 0);
            frozenBag3.insert(frozenBag3.begin(), 0);
            frozenBag4.insert(frozenBag4.begin(), 0);
        }
        
        if(frozen.at(0) == 2 && frozen.at(1) == 0){
            frozenBag1.insert(frozenBag1.begin(), 2);
            frozenBag2.insert(frozenBag2.begin(), 0);
            frozenBag3.insert(frozenBag3.begin(), 0);
            frozenBag4.insert(frozenBag4.begin(), 0);
        }
        
        if(frozen.at(0) == 3 && frozen.at(1) == 0){
            frozenBag1.insert(frozenBag1.begin(), 3);
            frozenBag2.insert(frozenBag2.begin(), 0);
            frozenBag3.insert(frozenBag3.begin(), 0);
            frozenBag4.insert(frozenBag4.begin(), 0);
        }
        
        // Rule #3
        cout << "--- Applying Rule #3: If step is bag large items and there is no more large items, stop bagging ---" << endl;
        cout << "Normal Bag(s): " << endl;
        
        // Split noncrushable items into small, medium, and large categories
        crush.insert(crush.begin() + 0, crushable.at(0));
        crush.insert(crush.begin() + 1, crushable.at(1));
        crush.insert(crush.begin() + 2, crushable.at(2));
        crush.insert(crush.begin() + 3, crushable.at(3));
        
        small.insert(small.begin() + 0, normal.at(0));
        small.insert(small.begin() + 1, normal.at(1));
        small.insert(small.begin() + 2, normal.at(2));
            
        medium.insert(medium.begin() + 0, normal.at(3));
        medium.insert(medium.begin() + 1, normal.at(4));
            
        large.insert(large.begin() + 0, normal.at(5));
        large.insert(large.begin() + 1, normal.at(6));
        large.insert(large.begin() + 2, normal.at(7));
        large.insert(large.begin() + 3, normal.at(8));
            
        cout << "Crushable: " << crush.at(0) << " " << crush.at(1) << " " << crush.at(2) << " " << crush.at(3) << endl;
        cout << "Small: " << small.at(0) << " " << small.at(1) << " " << small.at(2) << endl;
        cout << "Medium: " << medium.at(0) << " " << medium.at(1) << endl;
        cout << "Large: " << large.at(0) << " " << large.at(1) << " " << large.at(2) << " " << large.at(3) << endl;
            
        // Rule #2
        cout << "--- Applying Rule #2: If step is bag large items and there is large item, add this item to the bag ---" << endl;
        // Sum total of each food item size
        numCrushableItems = crush.at(0) + crush.at(1) + crush.at(2) + crush.at(3);
        numSmallItems = small.at(0) + small.at(1) + small.at(2);
        numMediumItems = medium.at(0) + medium.at(1);
        numLargeItems = large.at(0) + large.at(1) + large.at(2) + large.at(3);
            
        //cout << numCrushableItems << ", " << numSmallItems << ", " << numMediumItems << ", " << numLargeItems << endl;
        // Insert corresponding sum into appropriate slot
        normalBag.insert(normalBag.begin() + 0, numCrushableItems);
        normalBag.insert(normalBag.begin() + 1, numSmallItems);
        normalBag.insert(normalBag.begin() + 2, numMediumItems);
        normalBag.insert(normalBag.begin() + 3, numLargeItems);
            
        cout << normalBag.at(0) << " " << normalBag.at(1) << " " << normalBag.at(2) << " " << normalBag.at(3) << endl;
        
        // If any large items ordered exceed the sum of 4, exit program and tell them
        if(normalBag.at(3) > 4){
            
        }
        
        

        // TODO:
        // ######################################################################################################################################### //
            
            // ################################################################ Displaying The Bag(s) ################################################################ //
            // Displaying the appropriate number of bags and items in each bag
            cout << endl << "################################################################ Bag(s) Summary ################################################################" << endl;
            
            // Frozen Bags
            cout << "Frozen: " << endl;
            cout << "\tItems In Frozen Bag 1 (M -> L): " << frozenBag1.at(0) << " Tub(s) Of Ice Cream, " << frozenBag1.at(1) << " Bag(s) Of Ice" << endl;
            cout << "\tItems In Frozen Bag 2 (M -> L): " << frozenBag2.at(0) << " Tub(s) Of Ice Cream, " << frozenBag2.at(1) << " Bag(s) Of Ice" << endl;
            cout << "\tItems In Frozen Bag 3 (M -> L): " << frozenBag3.at(0) << " Tub(s) Of Ice Cream, " << frozenBag3.at(1) << " Bag(s) Of Ice" << endl;
            cout << "\tItems In Frozen Bag 4 (M -> L): " << frozenBag4.at(0) << " Tub(s) Of Ice Cream, " << frozenBag4.at(1) << " Bag(s) Of Ice" << endl;
            
            // Normal Bags
            cout << "Normal: " << endl;
            cout << "\tItems In Normal Bag 1 (C -> S -> M -> L): " << endl;
            cout << "\tItems In Normal Bag 2 (C -> S -> M -> L): " << endl;
            cout << "\tItems In Normal Bag 3 (C -> S -> M -> L): " << endl;
            cout << "\tItems In Normal Bag 4 (C -> S -> M -> L): " << endl;
            
            cout << endl << "#########################################################################################################################################" << endl;

            // ######################################################################################################################################### //
    } // end "if keep going == 'n'
} // end "FOODIE_BAGGER()
