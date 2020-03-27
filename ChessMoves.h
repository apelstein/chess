#ifndef CHESSMOVES_H_
#define CHESSMOVES_H_


typedef struct coord{
	unsigned int x;
	unsigned int y;
} coord;

typedef struct move{
	coord* curr_coord;
	coord* next_coord;
//	char pawn_promotion;
} move;

typedef struct action{
	char curr_piece;
	char next_piece;
	move* moovit;
} action;

typedef struct linked_coord{
	coord* sourceCoord;
	coord* destinationCoord;

	struct linked_coord* next;
}coordElem;

coord* createCoord(int x, int y);

coord* copyCoord(coord* src);

move* createMove(coord* curr_coord, coord* next_coord);

action* createAction(char curr_piece, char next_piece, move* moovit);

int destroyCoord(coord* src);

int destroyMove(move* src);

int destroyAction (action* src);

int actionComparator (action* src, action* target);

int coordComparator(coord* src, coord* target);

int moveComparator(move* src, move* target);

int moveComparatorFrom2Coord(coord* src ,coord* dest, move* targetMove);

int coordEquals(coord* coord1, coord* coord2);

coordElem* createElem(coord* srcCoordinates, coord* destCoordinates);

void destroyCEList(coordElem* src);

void freeOneCE(coordElem* src);

void PrintTheList(coordElem* ce);

void PrintThecoordfromElement(coordElem* ce);

void PrintTheCoord(coord* crd);

void PrintTheMove(move* m);

coordElem* createElemFrom2Ints(coord* srcCoordinates, int x,int y);

coordElem* createElemFromCopiedCoord(coord* srcCoordinates, coord* destCoordinates);

coordElem* addElements(coordElem* src, coordElem* new);

coordElem* findLastElem(coordElem* src);

void PruningTheFirst(coordElem* ce);

int isCoordInList(coordElem* src, coord* point);

void decreaseKey(coord* src, int x_addition, int y_addition);

coord* InvalidCoord();

int mallocError(void* pointer, char* msg);

#endif /* CHESSMOVES_H_ */
