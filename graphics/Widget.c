#include <stdio.h>
#include <stdlib.h>
#include "Widget.h"

SDL_Rect* spCopyRect(SDL_Rect* src){
	if(src == NULL){
		return NULL;
	}
	SDL_Rect* res = malloc(sizeof(SDL_Rect));
	if(res==NULL){
		return NULL;
	}
	res->h = src->h;
	res->w = src->w;
	res->x = src->x;
	res->y = src->y;
	return res;
}

Widget* createDoubleButton(SDL_Renderer* windowRender, SDL_Rect* location,
		 char* images0,  char* image1){
	Widget* res=createSimpleButton(windowRender,location,images0);
	res->images[0]=images0;
	res->images[1]=image1;

	return res;
}

Widget* createTripleHOTButton(SDL_Renderer* windowRender, SDL_Rect* location,
		 char* images0,  char* image1, char* image2){
	Widget* res=createSimpleButton(windowRender,location,images0);
	res->images[0]=images0;
	res->images[1]=image1;
	res->images[2]=image2;
	return res;
}
Widget* createPieceButton(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* image){
	Widget* res=createSimpleButton(windowRender,location,image);
	res->handleEvent=handlePieceButtonEvenet;
	return res;

}

//You need a create function:
Widget* createSimpleButton(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* image) {
	if (windowRender == NULL || location == NULL  ) {
		return NULL ;
	}
	//Allocate data
	Widget* res = (Widget*) malloc(sizeof(Widget));
	SimpleButton* data = (SimpleButton*) malloc(sizeof(SimpleButton));
		//printf("line 41 before load\n");fflush(stdout);
		SDL_Surface* loadingSurface = SDL_LoadBMP(image); //We use the surface as a temp var;
//		if(loadingSurface==NULL)
		//printf("line 43 after load\n");fflush(stdout);
		//We use SetColorKey to make texture background transparent
		//This function will make the magenta background transparent
		if(strcmp(image,"./graphics/images/game/green.bmp")==0){
			SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 32, 192, 64));
		}
		else{
			SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 34, 177, 76));
		}

		SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(windowRender,
				loadingSurface);


		if (res == NULL || data == NULL || loadingSurface == NULL
				|| buttonTexture == NULL) {
			printf("line 50 something is null\n");fflush(stdout);
			free(res);
			free(data);
			SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
			SDL_DestroyTexture(buttonTexture); ////It is safe to pass NULL
			return NULL ;
		}
		SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created

		data->buttonTexture = buttonTexture;

	data->location = spCopyRect(location);
	data->windowRenderer = windowRender;
	res->destroyWidget = destroySimpleButton;
	res->drawWidget = drawSimpleButton;
	res->handleEvent = handleSimpleButtonEvenet;
	res->data = data;
	return res;
}

//You need this function in order to destroy all data Associate with a button:
void destroySimpleButton(Widget* src) {
	if (src == NULL ) {
		return;
	}
	SimpleButton* castData = (SimpleButton*) src->data;
	free(castData->location);
	if(castData->buttonTexture!=NULL)
		SDL_DestroyTexture(castData->buttonTexture);
	free(castData);
	free(src);
}

SP_BUTTON handlePieceButtonEvenet(Widget* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {

		return BUTTON_NONE; //Better to return an error value
	}
	SDL_Point point;
	SimpleButton* castData = (SimpleButton*) src->data;
	if (event->type == SDL_MOUSEBUTTONDOWN) {

		point.x = event->button.x;
		point.y = event->button.y;
//		printf("line 89 <%d,%d>,<%d,%d>\n width=%d, h=%d\n",point.x,point.y,castData->location->x,castData->location->y,castData->location->w,castData->location->h);fflush(stdout);
//		printf("line 89 %d\n",SDL_PointInRect(&point, castData->location));fflush(stdout);
		if (SDL_PointInRect(&point, castData->location)) {
//			printf("line 91 \n");fflush(stdout);
			return BUTTON_PUSHED;
		}
		else{
//			printf("line 96 button none\n");fflush(stdout);
			return BUTTON_NONE;
		}
	}

	return BUTTON_NONE;

}

SP_BUTTON handleSimpleButtonEvenet(Widget* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {

		return BUTTON_NONE; //Better to return an error value
	}


	SimpleButton* castData = (SimpleButton*) src->data;
	if (event->type == SDL_MOUSEBUTTONUP) {
		SDL_Point point;
		point.x = event->button.x;
		point.y = event->button.y;
//		printf("line 169 <%d,%d>,<%d,%d>\n width=%d, h=%d\n",point.x,point.y,castData->location->x,castData->location->y,castData->location->w,castData->location->h);fflush(stdout);
		//printf("line 170 %d\n",SDL_PointInRect(&point, castData->location));fflush(stdout);
		if (SDL_PointInRect(&point, castData->location)) {
//			printf("line 91 \n");fflush(stdout);
			return BUTTON_PUSHED;
		}
		else{
//			printf("line 96 button none\n");fflush(stdout);
			return BUTTON_NONE;
		}
	}
	else {
		return BUTTON_NONE;
	}
//	return BUTTON_NONE;
}

void drawSimpleButton(Widget* src) {
	if (src == NULL ) {
		printf("line 120 ooooooo\n");fflush(stdout);
		return;
	}
	//printf("line 122 before 1 draw\n");fflush(stdout);
	SimpleButton* castData = (SimpleButton*) src->data;
	SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,
			castData->location);
	//printf("line 125 after 1 widget draw\n");fflush(stdout);
}

void changeDoubleButton(Widget* src, int imageIndex){
	if (src == NULL ) {
		return;
	}
//	if(imageIndex==2) {
//		printf("line 203 imageindex=%d\n",2);fflush(stdout);
//	}
	SimpleButton* castData = (SimpleButton*) src->data;
	SDL_Surface* loadingSurface = SDL_LoadBMP(src->images[imageIndex]); //We use the surface as a temp var;
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 32, 192, 64));
	SDL_Texture* buttonTexture =SDL_CreateTextureFromSurface(castData->windowRenderer,
				loadingSurface);
	castData->buttonTexture= buttonTexture;
//	SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,
//			castData->location);
}


void destroyWidget(Widget* src) {//Making NULL Safe Destroy
	if (src == NULL ) {
		return;
	}
	src->destroyWidget(src);
}
