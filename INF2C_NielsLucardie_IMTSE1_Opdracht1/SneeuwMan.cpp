/*
 * SneeuwMan.cpp
 *
 *  Created on: Feb 28, 2012
 *      Author: Niels
 */
#include "SneeuwMan.hpp"
#include <conprint.h>
#include <ma.h>
#include <mastdlib.h>

//constructor voor de sneeuwman
SneeuwMan::SneeuwMan(int positionX, int positionY, bool crazy) {
	this->positionY = positionY;
	this->positionX = positionX;

	this->crazyMode = crazy;
}

//sneeuwman bewegen
void SneeuwMan::move( int direction ){
	this->positionX = this->positionX + direction;
}

//sneeuwman tekenen (met ogen, knopen, etc.)
void SneeuwMan::draw(){

	if(this->crazyMode){
		maSetColor(rand() % 999999 + 1);
	}else{
		maSetColor(0xffffff);
	}
	maFillRect((this->positionX + 12), positionY - 125, 50, 50);
	maFillRect(this->positionX, positionY - 75, 75, 75);

	if(this->crazyMode){
		maSetColor(rand() % 999999 + 1);
	}else{
		maSetColor(0x000000);
	}
	maFillRect((this->positionX + 20), positionY - 115, 5, 5);
	maFillRect((this->positionX + 50), positionY - 115, 5, 5);

	maFillRect((this->positionX + 25), positionY - 85, 25, 5);

	maFillRect((this->positionX + 35), positionY - 65, 5, 5);
	maFillRect((this->positionX + 35), positionY - 55, 5, 5);
	maFillRect((this->positionX + 35), positionY - 45, 5, 5);
	maFillRect((this->positionX + 35), positionY - 35, 5, 5);
	maFillRect((this->positionX + 35), positionY - 25, 5, 5);

	if(this->crazyMode){
		maSetColor(rand() % 999999 + 1);
	}else{
		maSetColor(0xFF6633);
	}
	maFillRect((this->positionX + 32), positionY - 110, 10, 20);

	if(this->crazyMode){
		maSetColor(rand() % 999999 + 1);
	}else{
		maSetColor(0x000000);
	}
	maFillRect(this->positionX, positionY - 125, 75, 5);
	maFillRect(this->positionX + 25, positionY - 150, 25, 25);

	if(this->crazyMode){
		maSetColor(rand() % 999999 + 1);
	}else{
		maSetColor(0xB88A00);
	}
	maFillRect((this->positionX + 75), positionY - 70, 35, 5);
	maFillRect((this->positionX - 35), positionY - 70, 35, 5);
}

//extra functie crazymode (random kleuren)
void SneeuwMan::setCrazy(bool crazy){
	this->crazyMode = crazy;
}
