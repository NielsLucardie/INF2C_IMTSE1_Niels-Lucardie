/*
 * OptieScherm.h
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#ifndef OPTIESCHERM_H_
#define OPTIESCHERM_H_


#include <MAUTIL/Moblet.h>
#include <MAUI/Screen.h>
#include <MAUI/Label.h>
#include <MAUI/EditBox.h>
#include <MAUI/ListBox.h>
#include <MAUI/Layout.h>
#include "Util.h"

#include "mastdlib.h"

#include <MAUTIL/Vector.h>

#include "conprint.h"

#include "MAHeaders.h"


using namespace MAUtil;
using namespace MAUI;


class OptieScherm : public Screen, WidgetListener
{
private:

	//todo: voeg editboxen en waardes toe die opgeslagen moeten worden
	Layout* mainLayout;
	ListBox* listBox;
	Widget *softKeys;

	Screen *parent;

	Vector<Label*> kleurLabels;
	Vector<EditBox*> editBoxen;

	Label* roodLabel;
	Label* groenLabel;
	Label* blauwLabel;

	Label* achtergrondLabel;

	int achtergrondKleur;

	EditBox* naamBox;
	EditBox* sizexBox;
	EditBox* sizeyBox;

	Label* toepassenLabel;

	Point imageSize;

public:
	OptieScherm( Screen *parent );
	virtual ~OptieScherm();

	void keyPressEvent(int keyCode, int nativeCode);
	void pointerPressEvent(MAPoint2d point);

	int getAchtergrondOptie();
	Point getImagesizeOptie();
	const BasicString<char>getImagetekst(); //geeft text van editbox terug
	void show();
};

#endif /* OPTIESCHERM_H_ */
