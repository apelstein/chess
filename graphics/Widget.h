#ifndef WIDGET_H_
#define WIDGET_H_
#include <SDL.h>
#include <SDL_video.h>


typedef enum simple_b_e{
	BUTTON_PUSHED,
	BUTTON_NONE
}SP_BUTTON;

typedef struct widget_t Widget;
struct widget_t {
	void (*drawWidget)(Widget*);
	SP_BUTTON (*handleEvent)(Widget*, SDL_Event*);
	void (*destroyWidget)(Widget*);
	void* data;
	char* images[3];

};




typedef struct simplebutton_t SimpleButton;
struct simplebutton_t{
	SDL_Texture* buttonTexture;
	SDL_Renderer* windowRenderer;
	SDL_Rect* location;
};

SDL_Rect* spCopyRect(SDL_Rect* src);


//You need a create function:
Widget* createSimpleButton(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* image);

//You need this function in order to destroy all data Associate with a button:
void destroySimpleButton(Widget*);

SP_BUTTON handleSimpleButtonEvenet(Widget* src, SDL_Event* event);
SP_BUTTON handlePieceButtonEvenet(Widget* src, SDL_Event* event);
void drawSimpleButton(Widget* src);

void changeDoubleButton(Widget* src, int imageIndex);

Widget* createDoubleButton(SDL_Renderer* windowRender, SDL_Rect* location,
		 char* image0,  char* image1);
Widget* createTripleHOTButton(SDL_Renderer* windowRender, SDL_Rect* location,
		 char* image0,  char* image1,char* image2);
//This function would be usefull for NULL safe desetroy
void destroyWidget(Widget* src);

Widget* createPieceButton(SDL_Renderer* windowRender, SDL_Rect* location,
		const char* image);
#endif
