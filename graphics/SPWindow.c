#include <stdlib.h>
#include "SPWindow.h"

void destroyWindow(SPWindow* src){
	if(!src)
		return;
	if (src==NULL)
		return;

	spFiarGameDestroy(src->theGame);
	destroyAction(src->theAction);
	src->destroyWindow(src);
}
