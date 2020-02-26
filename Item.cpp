/*
luja shrestha
k687e787
Final Project

*/

#include "Item.h"

Item::Item(string name, double price){
	this->itemName = name;
	this->price = price;
	this->typ = All;

}

Item::Item(string name, double price, enum type typ){
	this->itemName = name;
	this->price = price;
	this->typ = typ;
}

void Item::setPrice(double price){
	this->price = price;
}

void Item::setName(string newName){
	this->itemName = newName;
}

void Item::setType(enum type typ){
	this->typ = typ;
}

double Item::getPrice(){
	return this->price;
}

string Item::getName(){
	return this->itemName;
}

double Item::getType(){
	return this->typ;
}
