/*
 * VisueelScherm.cpp
 *
 *  Created on: 11 mrt. 2012
 *      Author: acer
 */

#include "VisueelScherm.hpp"

VisueelScherm::VisueelScherm( WeerData* weerData )
{
	//sla de weerdata op in het attribuut
	this->weerData = weerData;

	//ken font en skin toe
	this->font = new Font(RES_FONT);
	this->skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een achtergrond label om alle andere widgets in op te slaan, en te tonen
	Label* achtergrond = new Label(0,0,0,0,NULL);
	achtergrond->setBackgroundColor(0x000000);

	//maak een listbox met update en textueelknop
	this->listBox = (ListBox*) achtergrond->getChildren()[0];

	//knop om data te updaten
	this->updateKnop = new Label(10,270,100,30, achtergrond, "Update", 0, font);
	this->updateKnop->setPaddingLeft(10);
	this->updateKnop->setPaddingTop(4);
	this->updateKnop->setSkin( this->skin );

	//knop om naar visueel te schakelen
	this->textueelKnop = new Label(130,270,100,30, achtergrond, "Textueel", 0, font);
	this->textueelKnop->setPaddingLeft(10);
	this->textueelKnop->setPaddingTop(4);
	this->textueelKnop->setSkin( this->skin );

	//label veld voor weer data, beslaat de rest van het scherm (zie onder)
	Label* weerDataLabel = new Label(10,10,220,30, achtergrond, "De weersvoorspelling (Visueel):", 0, font);
	//weerDataLabel->setSkin( this->skin );

	//staafdiagram

	//maak eerst een placeholder
	this->diagramTekening = maCreatePlaceholder();

	//laat de placeholder tekenbaar zijn
	maCreateDrawableImage( this->diagramTekening, EXTENT_X( maGetScrSize() ), EXTENT_Y( maGetScrSize() ) - 90 );

	//mak een nieuwe image met de placeholder
	this->diagramImage = new Image( 0, 30, EXTENT_X( maGetScrSize() ), EXTENT_Y( maGetScrSize() ) - 30, achtergrond, true, true, this->diagramTekening );

	this->setMain( achtergrond );

	//update labels met text, etc.
	this->update();
}


VisueelScherm::~VisueelScherm()
{
}


void VisueelScherm::update()
{
	//update waarden vam weerdata
	weerData->update();

	//stel draw target in op onze tekening
	maSetDrawTarget( this->diagramTekening );

	//teken een staaf diagram

	//legenda, teken blokje en text met zonneschijn, neerslag en temperatuur
	maSetColor(0xFFFF00);
	maFillRect(30,164,10,10);
	Label* zonLegenda = new Label(45,160,70,30, diagramImage, "Zonneschijn", 0, font);

	maSetColor(0x40E0D0);
	maFillRect(135,164,10,10);
	Label* neerslagLegenda = new Label(150,160,100,30, diagramImage, "Neerslag", 0, font);

	//labels voor precenten en dagen aanduiding
	Label* procentaanduiding = new Label(7,15,50,20, diagramImage, "100%", 0, font);
	Label* dagaanduiding = new Label(30,125,200,20, diagramImage, " Nu     Morgen  Overmorgen", 0, font);

	//teken 10-stap lijnen
	maSetColor(0xC0C0C0);
	maFillRect(20,120,200,1);

	maSetColor(0xC0C0C0);
	maFillRect(20,20,1,100);

	//teken de staven van zonneschijn, neerslag en minimum temperatuur
	maSetColor(0xFFFF00);
	maFillRect(30,120 - weerData->zonneschijn[0],20,weerData->zonneschijn[0]);

	maSetColor(0x40E0D0);
	maFillRect(50,120 - weerData->neerslag[0],20,weerData->neerslag[0]);

	maSetColor(0xFFFF00);
	maFillRect(95,120 - weerData->zonneschijn[1],20,weerData->zonneschijn[1]);

	maSetColor(0x40E0D0);
	maFillRect(115,120 - weerData->neerslag[1],20,weerData->neerslag[1]);

	maSetColor(0xFFFF00);
	maFillRect(165,120 - weerData->zonneschijn[2],20,weerData->zonneschijn[2]);

	maSetColor(0x40E0D0);
	maFillRect(185,120 - weerData->neerslag[2],20,weerData->neerslag[2]);



	//altijd draw target na tekenen teruggeven naar scherm!
	maSetDrawTarget( HANDLE_SCREEN );

	//update de image met de nieuwe tekening
	this->diagramImage->setResource( this->diagramTekening );
}



void VisueelScherm::setToggleScherm( Screen* toggleScherm )
{
	//switch naar andere scherm (textueel scherm)
	this->toggleScherm = toggleScherm;
}

void VisueelScherm::pointerPressEvent( MAPoint2d maPoint )
{
	Point point;
	point.x = maPoint.x;
	point.y = maPoint.y;

	//update knop is ingedrukt
	if( this->updateKnop->contains( point ) )
	{
		this->updateKnop->setSelected( true );
		this->update();
	}
	else
	{
		this->updateKnop->setSelected( false );
	}


	//textueel knop is ingedrukt
	if( this->textueelKnop->contains( point ) )
	{
		this->textueelKnop->setSelected( true );
		this->hide();
		this->toggleScherm->show();
	}
	else
	{
		this->textueelKnop->setSelected( false );
	}
}


