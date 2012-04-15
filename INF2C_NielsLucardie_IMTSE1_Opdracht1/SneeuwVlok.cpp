/*
 * SneeuwVlok.cpp
 *
 *  Created on: Feb 28, 2012
 *      Author: Niels
 */

#include <mastdlib.h>
#include "SneeuwVlok.hpp"
#include <ma.h>
#include <conprint.h>

//Constructor voor sneeuwvlok
SneeuwVlok::SneeuwVlok(int positionX, int positionY, bool crazy) {
	this->positionY = positionY;
	this->positionX = positionX;
	this->dead = false;
	this->size = rand() % 10 + 1;
	this->crazyMode = crazy;
}

//sneeuwvlok tekenen
void SneeuwVlok::draw(){
	if(this->crazyMode){
		maSetColor(rand() % 999999 + 1);
	}else{
		maSetColor(0xffffff);
	}
	maFillRect(this->positionX, positionY, this->size, this->size);
	maFillRect(this->positionX, positionY, this->size, this->size);
}

//sneeuwvlok vallen
void SneeuwVlok::fall( int groundLevel ){
	this->positionY = this->positionY + 1;
	if(this->positionY >= groundLevel){
		this->dead = true;
	}
}

//sneeuwvlok is dood status teruggeven
bool SneeuwVlok::isDead(){
	return this->dead;
}

//extra crazy mode (random kleuren).
void SneeuwVlok::setCrazy(bool crazy){
	this->crazyMode = crazy;
}


