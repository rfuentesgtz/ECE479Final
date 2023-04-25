//
//  rankedListGenerator.cpp
//  FOODIE_Project2
//
//  Created by Isabel Dailey on 4/19/23.
//

#include "FOODIE_BAGGER.h"
#include <stdio.h>
#include "stdc++.h"
//#include "FreezerBag.h"

using namespace std;

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
    bool tooMany = false;
    string keepGoing, name, location;
    vector<int> frozen, normal, crushable; // Vectors for final values of certain items in an order
    vector<int> qty = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Vector for food item quantities
    vector<string> mediumFrozenItems = {};
    vector<string> mediumNormalItems = {};
    vector<string> largeFrozenItems = {};
    vector<string> largeNormalItems = {};
    vector<string> crushableItems = {};
    vector<string> smallItems = {};
    vector<string> itemsInNormalBag = {"", "", "", "", "", ""};
    vector<string> itemsInFrozenBag = {"", "", "", "", "", ""};
    
    // Take the order(s) and adjust the order if person has entered in one or more amounts of items that cause the total number of bags to be greater than 6.
    do{
        tooMany = false;
        cout << "What is your name?: ";
        cin >> name;
        cout << endl << "Where do you want your ordered delivered?: ";
        cin >> location;
        // Do this until the user has decided they don't want to add anymore items to their order
        do{
            cout << "\nOrder Number: " << orderNumber << endl;
            cout << "Items For Bagging: \t\t\t Quantity:" << endl;
            cout << "1. Eggs\t\t\t\t\t\t\t" << qty[1] << endl;
            cout << "2. Chocolate\t\t\t\t\t" << qty[2] << endl;
            cout << "3. Apples\t\t\t\t\t\t" << qty[3] << endl;
            cout << "4. Peanut Butter\t\t\t\t"<< qty[4] << endl;
            cout << "5. Jelly\t\t\t\t\t\t" << qty[5] << endl;
            cout << "6. Ice Cream\t\t\t\t\t" << qty[6] << endl;
            cout << "7. Chips\t\t\t\t\t\t" << qty[7] << endl;
            cout << "8. Cereal\t\t\t\t\t\t" << qty[8] << endl;
            cout << "9. Bread\t\t\t\t\t\t" << qty[9] << endl;
            cout << "10. Granola Bar\t\t\t\t\t" << qty[10] << endl;
            cout << "11. Watermelon\t\t\t\t\t" << qty[11] << endl;
            cout << "12. Protein Powder\t\t\t\t" << qty[12] << endl;
            cout << "13. Bag Of Potatoes\t\t\t\t" << qty[13] << endl;
            cout << "14. Bag Of Ice\t\t\t\t\t" << qty[14] << endl;
            cout << "15. Water Jug\t\t\t\t\t" << qty[15] << endl << endl;
            
            // Error Checking
            do{
                cout << "What items would you like? (Enter item number) ";
                cin >> item;
                if(item < 0){ cout << "Error: Please enter a number between 1 and 15" << endl; }
                if(item >= 16){ cout << "Error: Please enter a number between 1 and 15" << endl; }
            }while(item < 0 || item >= 16);
            
            // For checking that only an int is accpeted as input: https://stackoverflow.com/questions/49345728/how-to-cin-only-integers-in-c-without-disrupting-remaining-code
            do {
                cout << "How many of " << item << " would you like to add? ";
                if (cin >> itemQty){ break; }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }while(true);
        
            // Update the value of item quantity based on user's selection of item
            qty[item] = itemQty;
            
            cout << "Would you like to add more items? (y/n) ";
            cin >> keepGoing;
            cout << endl;
        } while(keepGoing != "n");

        // Split qty vector into the three category vectors -- frozen, normal, and crushable -- based on item number
        frozen = {qty[6], qty[14]};
        normal = {qty[2], qty[4], qty[5], qty[8], qty[10], qty[11], qty[12], qty[13], qty[15]};
        crushable = {qty[1], qty[3], qty[7], qty[9]};
        
        cout << "The total number of items to bag of each item type is: " << endl;
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
        cout << "\t" << crushable.at(1) << " Bags Of Apples" << endl;
        cout << "\t" << crushable.at(2) << " Bags of Chips" << endl;
        cout << "\t" << crushable.at(3) << " Loaves of Bread" << endl;
        
        // Now determine optimal bagging
        cout << "\nDetermining optimal bagging ... " << endl;
        
        // ################################################################ Rule Implentation ################################################################ //
        // Get sums of items ordered based on size, crushability, and food type
        numCrushableItemsRemaining = crushable.at(0) + crushable.at(1) + crushable.at(2) + crushable.at(3);
        numSmallItemsRemaining = normal.at(0) + normal.at(1) + normal.at(2);
        numMediumNormalItemsRemaining = normal.at(3) + normal.at(4);
        numMediumFrozenItemsRemaining = frozen.at(0);
        numLargeNormalItemsRemaining = normal.at(5) + normal.at(6) + normal.at(7) + normal.at(8);
        numLargeFrozenItemsRemaining = frozen.at(1);
        
        // Put names of items in separate vectors for printing later on
        // Crushable Items
        for(int i = 1; i <= crushable.at(0); i++){ crushableItems.push_back("Dozen Eggs"); }
        for(int i = 1; i <= crushable.at(1); i++){ crushableItems.push_back("Bag Of Apples"); }
        for(int i = 1; i <= crushable.at(2); i++){ crushableItems.push_back("Bag Of Chips"); }
        for(int i = 1; i <= crushable.at(3); i++){ crushableItems.push_back("Loaf Of Bread"); }
        
        // Small Items
        for(int i = 1; i <= normal.at(0); i++){ smallItems.push_back("Piece Of Chocolate"); }
        for(int i = 1; i <= normal.at(1); i++){ smallItems.push_back("Jar Of Peanut Butter"); }
        for(int i = 1; i <= normal.at(2); i++){ smallItems.push_back("Jar Of Jelly"); }
        
        // Medium Normal Items
        for(int i = 1; i <= normal.at(3); i++){ mediumNormalItems.push_back("Box Of Cereal"); }
        for(int i = 1; i <= normal.at(4); i++){ mediumNormalItems.push_back("Box Of Granola Bars"); }
        
        // Large Normal Items
        for(int i = 1; i <= normal.at(5); i++){ largeNormalItems.push_back("Watermelon"); }
        for(int i = 1; i <= normal.at(6); i++){ largeNormalItems.push_back("Container Of Protein Powder"); }
        for(int i = 1; i <= normal.at(7); i++){ largeNormalItems.push_back("Bag Of Potatoes"); }
        for(int i = 1; i <= normal.at(8); i++){ largeNormalItems.push_back("Water Jug"); }
        
        // Medium Frozen Items
        for(int i = 1; i <= frozen.at(0); i++){ mediumFrozenItems.push_back("Tub Of Ice Cream"); }
        
        // Large Frozen Items
        for(int i = 1; i <= frozen.at(1); i++){ largeFrozenItems.push_back("Bag Of Ice"); }
        
        // Resets the number of bags of each kind every time so that the number of bags is always 6 or less
        normalBagCount = 0;
        frozenBagCount = 0;
        itemsInFrozenBag = {"", "", "", "", "", ""};
        itemsInNormalBag = {"", "", "", "", "", ""};

        // Normal Bags:
        // Loop through sorting the various sized items into the appropriate number of paper bags in the correct order based on how many of each item of a category are left and by what rule applies
        while(numCrushableItemsRemaining + numLargeNormalItemsRemaining + numMediumNormalItemsRemaining + numSmallItemsRemaining > 0){
            cout << "Rule #1: Plan to start new paper bag " << normalBagCount << " as " << numCrushableItemsRemaining + numSmallItemsRemaining + numMediumNormalItemsRemaining + numLargeNormalItemsRemaining << " normal items remain (" << numCrushableItemsRemaining << " Crushable Item(s), " << numSmallItemsRemaining <<  " Small Item(s), " << numMediumNormalItemsRemaining << " Medium Item(s), " << numLargeNormalItemsRemaining << " Large Item(s))" << endl;
            normalBagCount++;
            spaceInNormalBag = 9;
            numCrushableItems = 0;
            numLargeNormalItems = 0;
            numMediumNormalItems = 0;
            numSmallItems = 0;
            
            // Check if a crushable item is left
            if(numCrushableItemsRemaining > 0){
                cout << "Rule #2: Plan to reserve space in paper bag for crushable item " << crushableItems.back() << endl;
                numCrushableItemsRemaining--;
                numCrushableItems++;
                spaceInNormalBag = spaceInNormalBag - 1;
            }
            // Check if a large normal item is left
            if(numLargeNormalItemsRemaining > 0 and spaceInNormalBag >= 3){
                cout << "Rule #3: Plan to put large item " << largeNormalItems.back() << " in paper bag " << normalBagCount << endl;
                numLargeNormalItemsRemaining--;
                numLargeNormalItems++;
                spaceInNormalBag = spaceInNormalBag - 3;
                
                // Store the name of the large normal item planned on being put into a bag into a vector to be used for printing it later
                itemsInNormalBag[normalBagCount] = "\n\t" + largeNormalItems.back() + " (Large Item)" + itemsInNormalBag[normalBagCount];
                largeNormalItems.pop_back(); // Delete item from order list to move on to the large medium normal item in the order
            }
            // Loop while any medium normal items left and room in bag to fit each
            while(numMediumNormalItemsRemaining > 0 and spaceInNormalBag >= 2){
                cout << "Rule #4: Plan to put medium item " << mediumNormalItems.back() << " in paper bag " << normalBagCount << endl;
                numMediumNormalItemsRemaining--;
                numMediumNormalItems++;
                spaceInNormalBag = spaceInNormalBag - 2;
                
                // Store the name of the medium normal item planned on being put into a bag into a vector to be used for printing it later
                itemsInNormalBag[normalBagCount] = "\n\t" + mediumNormalItems.back() + " (Medium Item)" + itemsInNormalBag[normalBagCount];
                mediumNormalItems.pop_back(); // Delete item from order list to move on to the next medium normal item in the order
            }
            // Loop while any small items are left and room in bag to fit each
            while(numSmallItemsRemaining > 0 and spaceInNormalBag >= 2){
                cout << "Rule #5: Plan to put small item " << smallItems.back() << " in paper bag " << normalBagCount << endl;
                numSmallItemsRemaining--;
                numSmallItems++;
                spaceInNormalBag = spaceInNormalBag - 2;
                
                // Store the name of the small item planned on being put into a bag into a vector to be used for printing it later
                itemsInNormalBag[normalBagCount] = "\n\t" + smallItems.back() + " (Small Item)" + itemsInNormalBag[normalBagCount];
                smallItems.pop_back(); // Delete item from order list to move on to the next small item in the order
            }
            // Check if a crushable item was reserved to be put into a bag
            if(numCrushableItems == 1){
                cout << "Rule #6: Plan to put crushable item " << crushableItems.back() << " on top of paper bag " << normalBagCount << endl;
                
                // Store the name of the crushable item planned on being put into a bag into a vector to be used for printing it later
                itemsInNormalBag[normalBagCount] = "\n\t" + crushableItems.back() + " (Crushable Item)" + itemsInNormalBag[normalBagCount];
                crushableItems.pop_back(); // Delete item from order list to move on to the next crushable item in the order
            }
            
            // Check if the number of paper bags has reached 6 and if there are any normal items left for bagging. If there are, then user needs to modify their order, as there are too many items in the order that can be distributed amongst 6 total bags
            if(normalBagCount == 6 && numCrushableItemsRemaining + numLargeNormalItemsRemaining + numMediumNormalItemsRemaining + numSmallItemsRemaining > 0){
                cout << "Rule #10: Order requires too many bags (6 bags limit), so please reduce your order" << endl << endl;
                tooMany = true;
                break;
            }
        } // end paper bag while loop
        
        // Frozen Bags:
        // Loop through sorting the various sized items into the appropriate number of freezer bags in the correct order based on how many of each item of a category are left and by what rule applies
        while(numMediumFrozenItemsRemaining + numLargeFrozenItemsRemaining > 0 && tooMany == false){
            frozenBagCount++;
            cout << "Rule #7: Plan to start new freezer bag " << frozenBagCount << " as " << numMediumFrozenItemsRemaining + numLargeFrozenItemsRemaining << " frozen items remain (" << numMediumFrozenItemsRemaining << " Medium Item(s), " << numLargeFrozenItemsRemaining << " Large Item(s))" << endl;
            spaceInFreezerBag = 7;
            numLargeFrozenItems = 0;
            numMediumFrozenItems = 0;
            numSmallItems = 0;
            // Loop while any large freezer items left and room in bag to fit each
            if(numLargeFrozenItemsRemaining > 0 and spaceInFreezerBag >= 3){
                cout << "Rule #8: Plan to put large frozen item " << largeFrozenItems.back() << " in freezer bag " << frozenBagCount << endl;
                numLargeFrozenItemsRemaining--;
                numLargeFrozenItems++;
                spaceInFreezerBag = spaceInFreezerBag - 3;
                
                // Store the name of the large frozen item planned on being put into a bag into a vector to be used for printing it later
                itemsInFrozenBag[frozenBagCount] = "\n\t" + largeFrozenItems.back() + " (Large Item)" + itemsInFrozenBag[frozenBagCount];
                largeFrozenItems.pop_back(); // Delete item from order list to move on to the next large frozen item in the order
            }
            // Loop while any medium freezer items left and room in bag to fit each
            while(numMediumFrozenItemsRemaining > 0 and spaceInFreezerBag >= 2){
                cout << "Rule #9: Plan to put medium frozen item " << mediumFrozenItems.back() << " in freezer bag " << frozenBagCount << endl;
                numMediumFrozenItemsRemaining--;
                numMediumFrozenItems++;
                spaceInFreezerBag = spaceInFreezerBag - 2;
                
                // Store the name of the medium frozen item planned on being put into a bag into a vector to be used for printing it later
                itemsInFrozenBag[frozenBagCount] = "\n\t" + mediumFrozenItems.back() + " (Medium Item)" + itemsInFrozenBag[frozenBagCount];
                mediumFrozenItems.pop_back(); // Delete item from order list to move on to the next medium frozen item in the order
            }
            
            // Check if both the sum of paper and frozen bags has reached 6 and if there are any frozen items left for bagging. If there are, then user needs to modify their order, as there are too many items in the order that can be distributed amongst 6 total bags
            if(normalBagCount + frozenBagCount == 6 && numLargeFrozenItemsRemaining + numMediumFrozenItemsRemaining > 0){
                cout << "Rule #10: Order requires too many bags (6 bags limit), so please reduce your order" << endl << endl;
                tooMany = true;
                break;
            }
        } // end frozen bags while loop
    }while(tooMany == true); // end outermost do while
    
    cout << "Rule #11: Place all items into the determined bags" << endl << endl;
    cout << "\n################################################################ Order Summary ################################################################" << endl;
    cout << "Order #" << orderNumber << endl;
    cout << "Name: " << name << endl;
    cout << "Delivery Location: " << location << endl;
    cout << "Total Bags Needed: " << normalBagCount + frozenBagCount << " (" << normalBagCount << " Paper Bags and " << frozenBagCount << " Freezer Bags)" << endl;
    // Display Normal Bags
    if(normalBagCount == 0){ cout << "No Normal Items Ordered" << endl; }
    else{
        for(int i = 1; i <= normalBagCount; i++){
            cout << "Filling Paper Bag " << i << " with: " << itemsInNormalBag[i] << endl;
        }
    }
    cout << endl;
    // Display Freezer Bags
    if(frozenBagCount == 0){ cout << "\tNo Frozen Items Ordered" << endl; }
    else{
        for(int i = 1; i <= frozenBagCount; i++){
            cout << "Filling Freezer Bag " << i << " with: " << itemsInFrozenBag[i] << endl;
        }
    }
    cout << "###############################################################################################################################################" << endl << endl;
} // end "FOODIE_BAGGER()
