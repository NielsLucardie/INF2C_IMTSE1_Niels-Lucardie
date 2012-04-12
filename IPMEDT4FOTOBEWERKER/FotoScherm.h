/*
 * FotoScherm.h
 *
 *  Created on: Mar 5, 2012
 *      Author: Niels
 */

#include <MAUI/Screen.h>
#include <MAUI/Label.h>
#include <MAUI/Font.h>
#include <MAUI/Image.h>
#include <MAUtil/Connection.h>
#include <conprint.h>

#include "MAHeaders.h"

#define CONNECTION_BUFFER_SIZE 1024

using namespace MAUI;
using namespace MAUtil;

#ifndef FOTOSCHERM_H_
#define FOTOSCHERM_H_

class FotoScherm : public Screen, public HttpConnection, public HttpConnectionListener {
private:
	Label* label1;
	char data[CONNECTION_BUFFER_SIZE];
public:
	FotoScherm();
	virtual ~FotoScherm();
	void pointerPressEvent( MAPoint2d p );

	void httpFinished( HttpConnection *conn, int result);
	void connRecvFinished( Connection *conn, int result);
	void connReadFinished( Connection *conn, int result);
	void connectFinished(Connection* conn, int result);

};

#endif /* FOTOSCHERM_H_ */
