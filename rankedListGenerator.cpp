//
//  rankedListGenerator.cpp
//  FOODIE_Project
//
//  Created by Isabel Dailey on 4/18/23.
//

#include "rankedListGenerator.h"
#include <stdio.h>

using namespace std;

void FOODIE_BAGGER(int orderNumber){
    int item;
    int itemQty = 0;
    string keepGoing;
    //ofstream frozenItems, normalItems;
    vector<int> qty = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Vector for food item quantities
    vector<int> frozen, normal, crushable; // Vectors for final values of certain items
    // Vectors for food items with their numbers
    vector<string> frozenItems = {"5 Ice Cream", "13 Bag Of Ice"};
    vector<string> normalItems = {"1 Chocolate", "3 Peanut Butter", "4 Jelly", "7 Cereal", "9 Granola Bar", "10 Watermelon", "11 Protein Powder", "12 Bag Of Potatoes", "14 Water Jug"};
    vector<string> crushableItems = {"0 Eggs", "2 Apples","6 Chips", "8 Bread"};
   
    // Open frozenItems.txt and normalItems.txt for writing and appending data
    //frozenItems.open("/Users/isabel/OneDrive/ECE 479/Final Project/ItemSorter/ItemSorter/frozenItems.txt", ios_base::out);
    //frozenItems.open("/Users/isabel/OneDrive/ECE 479/Final Project/ItemSorter/ItemSorter/frozenItems.txt", ios_base::app);
    
    //normalItems.open("/Users/isabel/OneDrive/ECE 479/Final Project/ItemSorter/ItemSorter/normalItems.txt", ios_base::out);
    //normalItems.open("/Users/isabel/OneDrive/ECE 479/Final Project/ItemSorter/ItemSorter/normalItems.txt", ios_base::app);
    
    do{
        cout << "Order Number: " << orderNumber << endl;
        cout << "Items For Bagging: \t\t\t Quantity:" << endl;
        cout << "1. Eggs\t\t\t\t\t\t\t" << qty[0] << endl;
        cout << "2. Chocolate\t\t\t\t\t" << qty[1] << endl;
        cout << "3. Apples\t\t\t\t\t\t" << qty[2] << endl;
        cout << "4. Peanut Butter\t\t\t\t"<< qty[3] << endl;
        cout << "5. Jelly\t\t\t\t\t\t" << qty[4] << endl;
        cout << "6. Ice Cream\t\t\t\t\t" << qty[5] << endl;
        cout << "7. Chips\t\t\t\t\t\t" << qty[6] << endl;
        cout << "8. Cereal\t\t\t\t\t\t" << qty[7] << endl;
        cout << "9. Bread\t\t\t\t\t\t" << qty[8] << endl;
        cout << "10. Granola Bar\t\t\t\t\t" << qty[9] << endl;
        cout << "11. Watermelon\t\t\t\t\t" << qty[10] << endl;
        cout << "12. Protein Powder\t\t\t\t" << qty[11] << endl;
        cout << "13. Bag Of Potatoes\t\t\t\t" << qty[12] << endl;
        cout << "14. Bag Of Ice\t\t\t\t\t" << qty[13] << endl;
        cout << "15. Water Jug\t\t\t\t\t" << qty[14] << endl << endl;
        
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
        cout << "1. Eggs\t\t\t\t\t\t\t" << qty[0] << endl;
        cout << "2. Chocolate\t\t\t\t\t" << qty[1] << endl;
        cout << "3. Apples\t\t\t\t\t\t" << qty[2] << endl;
        cout << "4. Peanut Butter\t\t\t\t"<< qty[3] << endl;
        cout << "5. Jelly\t\t\t\t\t\t" << qty[4] << endl;
        cout << "6. Ice Cream\t\t\t\t\t" << qty[5] << endl;
        cout << "7. Chips\t\t\t\t\t\t" << qty[6] << endl;
        cout << "8. Cereal\t\t\t\t\t\t" << qty[7] << endl;
        cout << "9. Bread\t\t\t\t\t\t" << qty[8] << endl;
        cout << "10. Granola Bar\t\t\t\t\t" << qty[9] << endl;
        cout << "11. Watermelon\t\t\t\t\t" << qty[10] << endl;
        cout << "12. Protein Powder\t\t\t\t" << qty[11] << endl;
        cout << "13. Bag Of Potatoes\t\t\t\t" << qty[12] << endl;
        cout << "14. Bag Of Ice\t\t\t\t\t" << qty[13] << endl;
        cout << "15. Water Jug\t\t\t\t\t" << qty[14] << endl << endl;
        
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
        cout << "\t" << crushable.at(0) << " Dozen of Eggs" << endl;
        cout << "\t" << crushable.at(1) << " Bunches of Apples" << endl;
        cout << "\t" << crushable.at(2) << " Bags of Chips" << endl;
        cout << "\t" << crushable.at(3) << " Loaves of Bread" << endl;
        
        // Now bag the items
        cout << "Determining optimal bagging ... " << endl;
        // Rule Implementation
        // ## Rule #1: If food item is frozen, then put it in frozen item bag ## //
        
    }

  
}
