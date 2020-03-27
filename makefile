CC = gcc
OBJS = ChessMoves.o ChessParser.o ChessArrayList.o  ChessGame.o play.o SPMiniMaxNode.o SPMiniMax.o main_aux.o SPWindow.o Widget.o BoxMessage.o SPSimpleMainWindow.o SPChessGUIManager.o main.o 

EXEC = chessprog
CC_COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

all: $(EXEC) $(OBJS)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
main.o: main.c graphics/SPChessGUIManager.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Widget.o: graphics/Widget.c graphics/Widget.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
BoxMessage.o: graphics/BoxMessage.c graphics/BoxMessage.h graphics/Widget.h 
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
SPChessGUIManager.o: graphics/SPChessGUIManager.c graphics/SPChessGUIManager.h graphics/SPSimpleMainWindow.h 
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
SPWindow.o: graphics/SPWindow.c graphics/SPWindow.h main_aux.h 
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
SPSimpleMainWindow.o: graphics/SPSimpleMainWindow.c graphics/SPSimpleMainWindow.h graphics/SPWindow.h  graphics/BoxMessage.h 
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessArrayList.o: ChessArrayList.c ChessArrayList.h Costa.h ChessMoves.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessGame.o: ChessGame.c ChessGame.h ChessParser.h ChessArrayList.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessMoves.o: ChessMoves.c ChessMoves.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessParser.o: ChessParser.c ChessParser.h Costa.h ChessMoves.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
main_aux.o: main_aux.c main_aux.h SPMiniMax.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPMiniMax.o: SPMiniMax.c SPMiniMax.h SPMiniMaxNode.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPMiniMaxNode.o: SPMiniMaxNode.c SPMiniMaxNode.h play.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c	
play.o: play.c play.h ChessGame.h
	$(CC) $(CC_COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c		
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)
