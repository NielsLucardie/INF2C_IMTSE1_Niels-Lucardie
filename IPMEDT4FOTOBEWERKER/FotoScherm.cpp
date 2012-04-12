/*
 * FotoScherm.cpp
 *
 *  Created on: Mar 5, 2012
 *      Author: Niels
 */

#include "FotoScherm.h"

FotoScherm::FotoScherm() : HttpConnection (this) {

	Font* font = new Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin(RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32 ,false, false);

	Label* label = new Label(0,0,0,0,NULL);
	label->setBackgroundColor(0xFF00CC);

	this->label1 = new Label(10,10,100,30, label, "blablablabla", 0, font);
	this->label1->setSkin(skin);

	MAHandle tekening = maCreatePlaceholder();
	maCreateDrawableImage(tekening, 200,200);

	maSetDrawTarget(tekening);

	maSetColor(0xFF6633);
	maFillRect(0,0,200,200);

	maSetColor(0xFFFF33);
	maDrawText(0,0,"mike is gek");

	maSetDrawTarget(HANDLE_SCREEN);

	Image* tekenVeld = new Image(0,50,200,200, label, false, false, tekening);
	tekenVeld->setSkin(skin);

	this->setMain(label);

	// maak verbinding eindigd in httpfinish event
	int res = this->create("http://www.knmi.nl/waarschuwingen_en_verwachtingen/", HTTP_GET);

	if(res < 0)
	{
		lprintfln("Unable to connect!");
	}
	else
	{
		lprintfln("Connected!");
		this->finish();
	}


}

FotoScherm::~FotoScherm() {
	// TODO Auto-generated destructor stub
}

void FotoScherm::pointerPressEvent( MAPoint2d p ){
	Point point;
	point.x = p.x;
	point.y = p.y;

	if(this->label1->contains(point)){
		this->label1->setSelected(true);
	}else{
		this->label1->setSelected(false);
	}
}


void  FotoScherm::httpFinished( HttpConnection *conn, int result){
	this->recv(this->data, CONNECTION_BUFFER_SIZE);

}

void  FotoScherm::connRecvFinished( Connection *conn, int result){

	lprintfln( this->data );

	if(result > 0){
		this->recv(this->data, CONNECTION_BUFFER_SIZE);
	}

}

void  FotoScherm::connReadFinished( Connection *conn, int result){

}

void  FotoScherm::connectFinished(Connection* conn, int result){

}




