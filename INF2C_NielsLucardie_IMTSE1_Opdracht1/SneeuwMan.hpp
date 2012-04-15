/*
 * SneeuwMan.hpp
 *
 *  Created on: 8 feb. 2012
 *      Author: acer
 */

#ifndef SNEEUWMAN_HPP_
#define SNEEUWMAN_HPP_


//bevat teken functies
#include <ma.h>


//de klasse SneeuwMan
class SneeuwMan
{
private:
	int positionX;	//x positie van sneeuwman
	int positionY;	//y positie van sneeuwman

	bool crazyMode;	//Extra modus voor flitsende sneeuwman

public:
	//constructor
	SneeuwMan( int positionX, int positionY, bool crazy );

	//beweeg de sneeuwman in de richting "direcion", negatief getal is links, positief is rechts
	void move( int direction );

	//tekent een sneeuwman
	void draw();

	void setCrazy(bool crazy);
};


#endif /* SNEEUWMAN_HPP_ */
