/*
luja shrestha
k687e787
Final Project

Introduction:
My project is about small restaurant with can order, add the item and print total amout at last.

1. It display restaurant name
2. It ask customer name
3. It give choice to star ordering, print menu and exit.
4. If you start ordering, it will provide option print menu, add item, print order and check out
you can add the item from menu which should be same as menu name.
5. if you choose checkout it will give you all order item with total.

*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>


#include "Item.h"
using namespace std;

namespace Restaurant{
	string name = "O12 Restaurant";
	string printName(){
		return name;
	}
}

namespace Customer{
	string name;
	void setName(){
		cout<<"Enter customer's name : ";
		getline(cin,name);
		cout<<endl;
	}
	string printName(){
		return name;
	}
}

void PrintOptions(){
	cout<<"A - Start Giving order"<<endl;
	cout<<"B - Print Whole Menu"<<endl;
	cout<<"E - Exit"<<endl;
}

void printChoices(){
	cout<<"A - Print the Menu"<<endl;
	cout<<"B - Add Item to the order"<<endl;
	cout<<"C - Print the Order"<<endl;
	cout<<"D - checkOut"<<endl;
}

void PrintItems(vector<Item> &vec){
	for(double i=0;i<vec.size();i++){
		cout<<left<<std::setw(30)<<vec[i].getName();
		cout<<right<<std::setw(5)<<vec[i].getPrice()<<endl;
	}
}

void PrintMenu(vector<Item> &bF, vector<Item> &Lunch, vector<Item> &Dinner, vector<Item> &All){
	if(bF.size() != 0){
		cout<<"\n--------------------Breakfast Menu--------------------------"<<endl;
		PrintItems(bF);
	}
	if(Lunch.size() != 0){
		cout<<"\n--------------------Lunch Menu--------------------------"<<endl;
		PrintItems(Lunch);
	}
	if(Dinner.size() != 0){
		cout<<"\n--------------------Dinner Menu--------------------------"<<endl;
		PrintItems(Dinner);
	}
	if(All.size()!=0){
		cout<<"\n--------------------Common Menu--------------------------"<<endl;
		PrintItems(All);
	}
	cout<<endl;
}

void printOrder(vector<Item> &order){
	if(order.size() == 0){
		cout<<"You have not ordered yet"<<endl;
		return ;
	}
	PrintItems(order);
	double total = 0;
	for(double i=0;i<order.size();i++)
		total += order[i].getPrice();
	cout<<"Total  = "<< "$"<< total <<endl;
	cout<<"Total with tax = "<< "$"<<((total*0.075) + total)<<endl;
}

bool search_Add(vector<Item> &vec, vector<Item> &order, string itemName){
	bool find = false;
	for(double i=0;i<vec.size();i++){
		if(vec[i].getName().compare(itemName) == 0){
			order.push_back(vec[i]);
			find = true;
			break;
		}
	}
	return find;
}

void AddItem(vector<Item> &order, vector<Item> &bF, vector<Item> &Lunch, vector<Item> &Dinner, vector<Item> &All){
	string itemName;
	cout<<"Enter name of the item you want to order: ";
	cin>>itemName;
	if(search_Add(bF, order, itemName))
		return;
	if(search_Add(Lunch, order, itemName))
		return;
	if(search_Add(Dinner, order, itemName))
		return;
	if(search_Add(All, order, itemName))
		return;
	throw string("Item_Not_Found");

}

void StartGivingOrder(vector<Item> &order, vector<Item> &bF, vector<Item> &Lunch, vector<Item> &Dinner, vector<Item> &All){
	double flag = 0;
	while(1){
		printChoices();
		cout<<"\nEnter Your Choice - ";
		char ch;
		cin>>ch;
		switch(ch){
			case 'B':
				try{
					AddItem(order, bF, Lunch, Dinner, All);
				}catch(string s){
					cout<<s<<endl;
				}
				break;
			case 'D':
				flag = 1;
				break;
			case 'C':
				printOrder(order);
				break;
			case 'A':
				PrintMenu(bF, Lunch, Dinner, All);
				break;
			default:
				cout<<"Invalid Option -- Please choose the correct Choice"<<endl;
		}
		if(flag == 1)
			break;
	}
	cout<<Customer::printName()<<" your final Order is - "<<endl;
	printOrder(order);
}

void ReadFromFile(ifstream &menuFile, vector<Item> &bF, vector<Item> &Lunch, vector<Item> &Dinner, vector<Item> &All){
	double type, price;
	string name;
	double total = 0;
	menuFile >> total;
	while(total--){
		menuFile>>type>>name>>price;
		if(type == 1){
			Item item(name, price, breakfast);
			bF.push_back(item);
		}
		else if(type == 2){
			Item item(name, price, lunch);
			Lunch.push_back(item);
		}
		else if (type == 3){
			Item item(name, price, lunch);
			Dinner.push_back(item);
		}
		else{
			Item item(name, price, lunch);
			All.push_back(item);
		}
	}
}

int main(){
	cout<<"Reading menu from the file menu.txt............."<<endl;
	vector<Item> bF;
	vector<Item> Lunch;
	vector<Item> Dinner;
	vector<Item> All;
	vector<Item> order;

	ifstream menuFile;
	try{
		menuFile.open("menu.txt");
	}
	catch(...){
		cout<<"File with name menu.txt does not exist"<<endl;
		return 0;
	}

	try{
		ReadFromFile(menuFile, bF, Lunch, Dinner, All);
		menuFile.close();
	}
	catch(...){
		cout<<"Exception Occured in reading the file"<<endl;
	}

	cout<< "-------------------- Welcome at "<<Restaurant::printName()<<" -------------------------------------"<<endl;
	cout <<"                        Phone no. : 316-344-3232                            "                         <<endl;
	cout <<"                           wichita,kansas                          "                                 <<endl;
	Customer::setName();
	double flag = 0;
	while(1){
		PrintOptions();
		cout<<"\nEnter Your Choice - ";
		char ch;
		cin>>ch;
		switch(ch){
			case 'A':
				StartGivingOrder(order,bF, Lunch, Dinner, All);
				flag = 1;
				break;
			case 'B':
				PrintMenu(bF, Lunch, Dinner, All);
				break;
			case 'E':
				flag = 2;
				break;
			default:
				cout<<"Invalid Option -- Please choose the correct Choice"<<endl;
		}
		if(flag != 0){
			break;
		}
	}

	if(flag == 2)
		cout<<"Exiting"<<endl;
	else
		cout<<"Thank You "<< Customer::printName()<<" for Ordering at "<<Restaurant::printName()<<endl;
	return 0;
}
