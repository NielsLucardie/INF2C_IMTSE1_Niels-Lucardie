/*
 * SneeuwLandschap.cpp
 *
 *  Created on: 8 feb. 2012
 *      Author: acer
 */

#include "SneeuwLandschap.hpp"
#include "SneeuwMan.hpp"
#include "SneeuwVlok.hpp"
#include <MAUtil/Vector.h>
#include <conprint.h>


//globale variabelen voor breedte en hoogte van het scherm en de sneeuwman
int screenWidth;
int screenHeight;
SneeuwMan* sneeuwMan;


//constructor
SneeuwLandschap::SneeuwLandschap()
{
	this->crazyMode = false;

	//sla schermgrootte op in globale variabelen
	MAExtent screenSize = maGetScrSize();
	screenWidth = EXTENT_X( screenSize );
	screenHeight = EXTENT_Y( screenSize );

	//stel sneeuwhoogte in (vanaf bodem)
	this->sneeuwHoogte = 30;

	//maak een nieuwe sneeuwman
	sneeuwMan = new SneeuwMan( screenWidth / 2, screenHeight - this->sneeuwHoogte, crazyMode );
}


//wordt aangeroepen als er input is (druk op de toets, touch van scherm)
void SneeuwLandschap::run( MAEvent event )
{
	//als er een key is ingetoetst
	if( event.type == EVENT_TYPE_KEY_PRESSED )
	{
		//pak de key code
		int key = maGetKeys();

		//kijk voor linkertoets
		if( key == MAKB_LEFT || event.key == MAK_MENU )
			this->sneeuwMan->move( -6 );	//beweeg sneeuwman -6 pixels

		//kijk voor rechtertoets
		if( key == MAKB_RIGHT || event.key == MAK_SEARCH )
			this->sneeuwMan->move( 6 );		//beweeg sneeuwman 6 pixels

		//kijk voor back toets voor het invoeren van crazymode (random kleuren)
		if( event.key == MAK_BACK){
			if(this->crazyMode){
				this->crazyMode = false;
			}else{
				this->crazyMode = true;
			}
		}
	}

	//voeg een sneeuwvlok toe
	int RandomLoc = rand() % screenWidth  + 1;
	SneeuwVlok* sneeuwVlok = new SneeuwVlok( RandomLoc, 0, crazyMode );
	this->sneeuwVlokArray.add(sneeuwVlok);

	//laat alle sneeuwvlokken vallen
	SneeuwVlok* vlok;
	for(MAUtil::Vector<SneeuwVlok*>::iterator itr = sneeuwVlokArray.begin(); itr != sneeuwVlokArray.end(); itr++)
	{
		vlok = *itr;
	    vlok->fall(screenHeight - this->sneeuwHoogte);
	    if(vlok->isDead()){
	    	int RandomLoc = rand() % screenWidth  + 1;
	    	sneeuwVlokArray.remove(itr);
	    	delete vlok;
	    }
	}
}


//wordt elke "tick" aangeroepen om het winterlandschap, sneeuwman en sneeuwvlokken te tekenen
void SneeuwLandschap::draw()
{
	//kleur de lucht blauw
	if(this->crazyMode){
		maSetColor(rand() % 999999 + 1);
	}else{
		maSetColor(0x0055ff);
	}
	maFillRect( 0, 0, screenWidth, screenHeight );

	//maak sneeuw op de grond, a.d.h.v. sneeuwHoogte
	if(this->crazyMode){
		maSetColor(rand() % 999999 + 1);
	}else{
		maSetColor(0xffffff);
	}
	maFillRect( 0, screenHeight - this->sneeuwHoogte, screenWidth, this->sneeuwHoogte );

	//teken de sneeuwman
	this->sneeuwMan->setCrazy(this->crazyMode);
	this->sneeuwMan->draw();

	//teken alle sneeuwvlokken
	SneeuwVlok* vlok;
	for(MAUtil::Vector<SneeuwVlok*>::iterator itr = sneeuwVlokArray.begin();
	itr != sneeuwVlokArray.end();
	itr++)
	{
		vlok = *itr;
		vlok->setCrazy(this->crazyMode);
	    vlok->draw();
	}
}


