/*
 * Name: Van Hua
 * Order Member Function Definitions
 * Course: CSI218 (Spring 2020)
 * Date: May 14, 2020
 * Description: Order member function definitions.
 */

#include <iostream>
#include <iomanip> 
#include "order.h"
using namespace std;

// Product member function definitions.

// Constructors

Order::Order(){  // default constructor
	orderNum = 0;
	name = "";
	address = "";
	phoneNum = "";
	timeRecieved = 0;
	itemOrdered = "";
	price = 0.0;
}

Order::Order(const int &newOrderNum, string newName, string newAddress, string newPhoneNum, int newTimeRecieved, string newItemOrdered, double newPrice){
	set(newOrderNum,
		newName,
		newAddress,
		newPhoneNum,
		newTimeRecieved,
		newItemOrdered,
		newPrice);
}

// Accessors

int Order::getTimeRecieved() const{
	return timeRecieved;
}

void Order::output() const{
	cout << "---------------Order Receipt---------------" << endl;
	cout << "Order number: " << orderNum << endl
		 << "Customer name: " << name << endl
		 << "Address: " << address << endl
		 << "Phone number: " << phoneNum << endl
		 << "Time want to recieve order: " << timeRecieved << "h" << endl
		 << "Items ordered: " << itemOrdered << endl
		 << "Total pay: $" << price << endl;
	
}

double Order::totalPay(double price) const{
	return price;
}

// Mutators

void Order::set(const int &newOrderNum,
	string newName,
	string newAddress,
	string newPhoneNum,
	int newTimeRecieved,
	string newItemOrdered,
	double newPrice)
{
	setPrice(newPrice);  // Check if valid
	orderNum = newOrderNum;
	name = newName;
	address = newAddress;
	phoneNum = newPhoneNum;
	timeRecieved = newTimeRecieved;
	itemOrdered = newItemOrdered;
}


void Order::setPrice(double newPrice){
	if (newPrice <= 0.0){
		cerr << "Order price must be positive." << endl;
		return;
	}

	price = newPrice;
}

//Overloaded operators to compare each order.
bool operator >(const Order &order1, const Order &order2){
	return order1.getTimeRecieved() > order2.getTimeRecieved();
}
