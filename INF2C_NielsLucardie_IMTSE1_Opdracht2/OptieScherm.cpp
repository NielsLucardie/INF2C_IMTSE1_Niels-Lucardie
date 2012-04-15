/*
 * OptieScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#include "OptieScherm.h"

OptieScherm::OptieScherm( Screen *parent ) : parent(parent)
{
	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//sla parent scherm op (FotoScherm) om de show() te kunnen aanroepen, zodat dit optiescherm weer gesloten wordt
	this->parent = parent;

	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	this->achtergrondLabel = new Label(0,0,0,0,NULL);

	//stel achtergrondkleur in
	this->achtergrondLabel->setBackgroundColor(0x0000FF);

	//maak rode knop
	this->roodLabel = new Label(10,10,100,30, achtergrondLabel, "Rood", 0, font);
	roodLabel->setSkin( skin );
	roodLabel->setPaddingLeft(10);
	roodLabel->setPaddingTop(5);
	this->kleurLabels.add( roodLabel );	//voeg toe aan vector

	//maak groene knop
	this->groenLabel = new Label(10,50,100,30, achtergrondLabel, "Groen", 0, font);
	groenLabel->setSkin( skin );
	groenLabel->setPaddingLeft(10);
	groenLabel->setPaddingTop(5);
	this->kleurLabels.add( groenLabel );//voeg toe aan vector

	//maak blauwe knop
	this->blauwLabel = new Label(10,90,100,30, achtergrondLabel, "Blauw", 0, font);
	blauwLabel->setSkin( skin );
	blauwLabel->setPaddingLeft(10);
	blauwLabel->setPaddingTop(5);
	this->kleurLabels.add( blauwLabel );//voeg toe aan vector

	//maak toepassen knop
	this->toepassenLabel = new Label(10,250,100,30, achtergrondLabel, "Toepassen", 0, font);
	toepassenLabel->setSkin( skin );
	toepassenLabel->setPaddingLeft(10);
	toepassenLabel->setPaddingTop(5);

	//alle editboxen (naam, grootte x, grootte y)
	Label* naamLabel = new Label(15, 130, 100, 20, achtergrondLabel, "Image naam: ", 0, font);
	naamLabel->setBackgroundColor(0x0000FF);
	this->naamBox = new EditBox(110, 130, 100, 20, achtergrondLabel, "", 0, font, true, true, 512);
	this->editBoxen.add( naamBox );//voeg toe aan vector

	Label* sizexLabel = new Label(15, 170, 100, 20, achtergrondLabel, "Image size X: ", 0, font);
	sizexLabel->setBackgroundColor(0x0000FF);
	this->sizexBox = new EditBox(110, 170, 100, 20, achtergrondLabel, "", 0, font, true, true, 64, EditBox::IM_NUMBERS);
	this->editBoxen.add( sizexBox );//voeg toe aan vector

	Label* sizeyLabel = new Label(15, 210, 100, 20, achtergrondLabel, "Image size Y: ", 0, font);
	sizeyLabel->setBackgroundColor(0x0000FF);
	this->sizeyBox = new EditBox(110, 210, 100, 20, achtergrondLabel, "", 0, font, true, true, 64, EditBox::IM_NUMBERS);
	this->editBoxen.add( sizeyBox );//voeg toe aan vector

	this->setMain( this->achtergrondLabel );

	//standaard kleur en standaard tekst (bij eerste aanroep)
	this->achtergrondKleur = 0x0000FF;
	this->naamBox->setCaption("Naamloos");
}

OptieScherm::~OptieScherm()
{
}

//geef ingestelde achtergrondkleur terug
int OptieScherm::getAchtergrondOptie()
{
	//return achtergrond kleur
	return this->achtergrondKleur;
}


//geef ingestelde imagetekst van de editbox terug
const BasicString<char> OptieScherm::getImagetekst()
{
	//verander editBox naar jouw editboxs
	return this->naamBox->getCaption(); //caption is de text in een editbox
}

//geef ingestelde image grootte terug
Point OptieScherm::getImagesizeOptie()
{
	this->imageSize.x = atoi(sizexBox->getCaption().c_str());
	this->imageSize.y = atoi(sizeyBox->getCaption().c_str());

	//return image size
	return this->imageSize;
}

void OptieScherm::keyPressEvent(int keyCode, int nativeCode)
{

}

//show() override de show() van de super klasse (Screen), omdat we bij showen eerst opties willen ophalen
void OptieScherm::show(){
	this->Screen::show();
}

void OptieScherm::pointerPressEvent(MAPoint2d point)
{

	Point p;
	p.x = point.x;
	p.y = point.y;

	//doorloop alle kleurlabels om selectie in te stellen
	Label* hetLabel;
	for(MAUtil::Vector<Label*>::iterator itr = kleurLabels.begin(); itr != kleurLabels.end(); itr++)
	{
		hetLabel = *itr;

		//kijk of label in het touch-punt valt
		if(hetLabel->contains(p)){
			hetLabel->setSelected(true);
			if(hetLabel->getCaption() == "Rood"){
				this->achtergrondKleur = 0xFF0000;
			}else if(hetLabel->getCaption() == "Groen"){
				this->achtergrondKleur = 0x00FF00;
			}else if(hetLabel->getCaption() == "Blauw"){
				this->achtergrondKleur = 0x0000FF;
			}
		}else{ //niet in touch punt? deselect!
			hetLabel->setSelected(false);
		}
	}

	//behandel de editbox bij selecteren (touch), verander de editBox naar je eigen editbox(en)
	EditBox* deBox;
	for(MAUtil::Vector<EditBox*>::iterator itr = editBoxen.begin(); itr != editBoxen.end(); itr++)
	{
		deBox = *itr;

		if(deBox->contains(p)){
			deBox->setSelected(true);
		}else{
			deBox->setSelected(false);
		}

	}

	if(toepassenLabel->contains(p)){
		parent->show();
	}

}

