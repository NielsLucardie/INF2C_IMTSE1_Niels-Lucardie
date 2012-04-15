/*
 * FotoScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#include "FotoScherm.h"

int screenWidth;
int screenHeight;

FotoScherm::FotoScherm()
{
	//het optiescherm
	this->optieScherm = new OptieScherm( this );

	//bepaal grootte van het scherm
	MAExtent screenSize = maGetScrSize();
	screenWidth = EXTENT_X( screenSize );
	screenHeight = EXTENT_Y( screenSize );

	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	this->standaardFont = new Font(RES_FONT);

	//maak een label die andere widgets straks bevat, (en een achtergrondkleur heeft) <--- wordt meegegeven door optiescherm!!!!
	this->achtergrondLabel = new Label(0,0,0,0,NULL);
	//this->achtergrondLabel->setBackgroundColor(0x0000FF); //<--- wordt meegegeven door optiescherm!!!!

	//maak een plaatje (laden uit de resource file res.lst) en voeg label als parent toe
	this->image = new Image((screenWidth / 2) - (screenWidth / 2) / 2,(screenHeight / 2) - (screenHeight / 2) / 2,screenWidth / 2,screenHeight / 2,achtergrondLabel,false,false,RES_IMAGE );

	//maak tekst bij het plaatje met een label
	this->imageTekst = new Label(this->image->getPosition().x,this->image->getPosition().y + this->image->getHeight(),screenWidth / 2,20, achtergrondLabel, "Rare Foto", 0, standaardFont);
	this->imageTekst->setBackgroundColor(0x0000FF);
	this->imageTekst->setPaddingLeft(0);

	//stel dit scherm in als het main scherm, met achtergrondlabel als de basis widget
	this->setMain( this->achtergrondLabel );
}

//destructor
FotoScherm::~FotoScherm()
{

}


//show() override de show() van de super klasse (Screen), omdat we bij showen eerst opties willen ophalen
void FotoScherm::show()
{
	//roep de show() van de superklasse (Screen) aan
	this->Screen::show();

	//haal informatie achtergrondkleur op van optiescherm
	this->achtergrondLabel->setBackgroundColor( this->optieScherm->getAchtergrondOptie() );
	this->imageTekst->setBackgroundColor(this->optieScherm->getAchtergrondOptie());

	//haal informatie imagetekst op van optiescherm
	this->imageTekst->setCaption( this->optieScherm->getImagetekst() );

	//haal informatie (image size) op van optiescherm
	if(this->optieScherm->getImagesizeOptie().x > 0 && this->optieScherm->getImagesizeOptie().x < screenWidth - 20){
		this->image->setWidth(this->optieScherm->getImagesizeOptie().x);
		this->image->setPosition((screenWidth / 2) - this->optieScherm->getImagesizeOptie().x / 2, this->image->getPosition().y);
	}
	if(this->optieScherm->getImagesizeOptie().y > 0 && this->optieScherm->getImagesizeOptie().y < screenHeight - 20){
		this->image->setHeight(this->optieScherm->getImagesizeOptie().y);
		this->image->setPosition(this->image->getPosition().x, (screenHeight / 2) - this->optieScherm->getImagesizeOptie().y / 2);
	}
	this->imageTekst->setPosition(this->image->getPosition().x,this->image->getPosition().y + this->image->getHeight());
}



//afvangen invoer
void FotoScherm::keyPressEvent(int keyCode, int nativeCode)
{
	//bij indrukken van de MAK_FIRE toets, laat optiescherm zien
	switch(keyCode) {
			case MAK_FIRE:
				this->optieScherm->show();
				break;
	}

}

void FotoScherm::pointerPressEvent(MAPoint2d point)
{
	//bij touch, laat optiescherm zien
	this->optieScherm->show();
}


