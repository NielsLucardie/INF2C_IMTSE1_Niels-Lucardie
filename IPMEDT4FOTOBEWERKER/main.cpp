#include <MAUtil/Moblet.h>
#include <MAUI/Label.h>
#include "FotoBewerker.h"

using namespace MAUtil;
using namespace MAUI;


/**
 * Entry point of the program. The MAMain function
 * needs to be declared as extern "C".
 */
extern "C" int MAMain()
{
	Moblet::run(new FotoBewerker());
	return 0;
}
