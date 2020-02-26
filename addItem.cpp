/*
luja shrestha
k687e787
Final Project

Intro:
This is the for owner so he or she can modify the menu and add the item and price.
*/




#include <iostream>
#include <vector>
#include <iomanip>
#include "Item.h"
#include <fstream>
using namespace std;

// This program is used to add an item to the menu stored the file

void PrintOptions(){
	cout<<"---------------------My restaurant ----------------------------------"<<endl;
	cout<<"A - Add a particular Breakfast/Lunch/Dinner Item"<<endl;
	cout<<"B - Add a common Item to menu"<<endl;
	cout<<"E - Prdouble Whole Menu"<<endl;
	cout<<"F - Exit"<<endl;
}

void Input(string &name, double &price){
	cout<<"Enter new Item name (without spaces):"<<endl;
    getline(cin,name);
	cout<<"Enter Price of Item (doubleeger):"<<endl;
	cin>>price;
}

void printTypeChoices(){
	cout<<"1 - Add an Item as BreakfastItem"<<endl;
	cout<<"2 - Add an Item as Lunch Item"<<endl;
	cout<<"3 - Add an Item as Dinner Item"<<endl;
}
// use throw in this function
void AddItem(vector<Item> &bF, vector<Item> &Lunch, vector<Item> &Dinner){
	printTypeChoices();
	double choice;
//	double flag = 0;
	cin>>choice;
	string name;
	double price;
	Input(name, price);
	if(choice ==1 ){
		Item item(name, price, breakfast);
		bF.push_back(item);
		return;
	}
	else if(choice == 2){
		Item item(name, price, lunch);
		Lunch.push_back(item);
		return;
	}
	else if(choice == 3){
		Item item(name, price, dinner);
		Dinner.push_back(item);
		return;
	}
	//  throw wrong input given
}

void AddItem(vector<Item> &All){
	string name;
	double price;
	Input(name, price);
	Item item(name, price);
	All.push_back(item);
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

void writeVec(ofstream &menuFile, vector<Item> &vec){
	for(double i=0;i<vec.size();i++){
		menuFile<<vec[i].getType()<<" "<<vec[i].getName()<<" "<<vec[i].getPrice()<<"\n";
	}
}

void writeToFile(ofstream &menuFile, vector<Item> &bF, vector<Item> &Lunch, vector<Item> &Dinner, vector<Item> &All){
	double total = bF.size() + Lunch.size() + Dinner.size() + All.size();
	menuFile<<total<<"\n";
	writeVec(menuFile,bF);
	writeVec(menuFile,Lunch);
	writeVec(menuFile,Dinner);
	writeVec(menuFile,All);
}

int main(){
	cout<<"Reading menu from the file menu.txt............."<<endl;
	vector<Item> bF;
	vector<Item> Lunch;
	vector<Item> Dinner;
	vector<Item> All;

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
		cout<<"Exception occured in reading the file"<<endl;
		return 0;
	}

	double flag = 0;
	while(1){
		PrintOptions();
		cout<<"\nEnter Your Choice - ";
		char ch;
		cin >> ch;
		switch(ch){
			case 'A':
				AddItem(bF, Lunch, Dinner);
				break;
			case 'B':
				AddItem(All);
				break;
			case 'E':
				PrintMenu(bF, Lunch, Dinner, All);
				break;
			case 'F':
				flag = 1;
				break;
			default:
				cout<<"Invalid Option -- Please choose the correct Choice"<<endl;
		}
		if(flag == 1){
			cout<<"Exiting"<<endl;
			break;
		}
	}

	// Writes the overall menu to menu.txt and updates it whenever new item is added
	ofstream menuFile2;
	menuFile2.open("menu.txt");
	writeToFile(menuFile2, bF, Lunch, Dinner, All);
	menuFile2.close();
	return 0;
}
