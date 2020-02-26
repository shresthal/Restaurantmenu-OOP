/*
luja shrestha
k687e787
Final Project

intro : it has item class item
private: name, price , type

constructor:
1. accept name and Price
2. accept name , Price , type

function:
1.setname
2.setPrice
3.setType



*/


#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;



enum type{
	breakfast = 1,
	lunch = 2,
	dinner = 3,
	All = 4
};

class Item{
	private:
		string itemName;
		double price;
		enum type typ;

	public:
		Item(string name, double price);
		Item(string n, double p, enum type typ);
		void setPrice(double price);
		void setName(string newName);
		void setType(enum type typ);
		double getPrice();
		string getName();
		double getType();
};
