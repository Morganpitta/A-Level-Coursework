ROOT_DIR := ../../..
SRC = ../src
INCLUDE = ../include


CC = g++
CCEXE = g++
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
SFMLSTATICFLAGS = -DSFML_STATIC -static -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-network-s -lsfml-system-s

ifeq ($(shell uname), Linux)
	CCEXE = /usr/bin/x86_64-w64-mingw32-g++-posix
	SFMLSTATICFLAGS += -DFLAC__NO_DLL -U__STRICT_ANSI__ -I/home/mtpittaway/SFML/include -L/home/mtpittaway/SFML/lib -lopenal32 -lFLAC -lvorbisenc -lvorbisfile -lvorbis -logg -lws2_32 -lfreetype -lopengl32 -lwinmm -lgdi32 -lpthread
else
	SFMLDEPENDENCIES = -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lws2_32 -lfreetype -lopengl32 -lwinmm -lgdi32
	SFMLFLAGS += $(SFMLDEPENDENCIES)
	SFMLSTATICFLAGS += $(SFMLDEPENDENCIES)
endif


CFLAGS = -std=c++17 -Wall -fdiagnostics-color=always -g -I$(ROOT_DIR)/Include -I$(INCLUDE)

render = camera.o renderer.o
entities = pathFinding.o entity.o enemy.o bullet.o

# ****************************************************
# Targets needed to bring the executable up to date

default: default_compile main.o
	$(CC) *.o -o ${ROOT_DIR}/.vscode/a.out $(CFLAGS)

exe: static_compile main.o
	$(CCEXE) *.o -o ${ROOT_DIR}/.vscode/a.exe $(CFLAGS)

clean:
	rm *.o ${ROOT_DIR}/.vscode/a.exe ${ROOT_DIR}/.vscode/a.out

static_compile:
	$(eval CFLAGS += $(SFMLSTATICFLAGS) )

default_compile:
	$(eval CFLAGS += $(SFMLFLAGS) )

main.o: ${SRC}/main.c++ mazeWars.o
	$(CC) $(CFLAGS) -c ${SRC}/main.c++

mazeWars.o: ${SRC}/mazeWars.c++ ${INCLUDE}/mazeWars.h++ mazeGenerator.o ${render} ${entities}
	$(CC) $(CFLAGS) -c ${SRC}/mazeWars.c++

mazeGrid.o: ${SRC}/mazeGrid.c++ ${INCLUDE}/mazeGrid.h++ direction.o
	$(CC) $(CFLAGS) -c ${SRC}/mazeGrid.c++

mazeGenerator.o: ${SRC}/mazeGenerator.c++ ${INCLUDE}/mazeGenerator.h++ mazeGrid.o
	$(CC) $(CFLAGS) -c ${SRC}/mazeGenerator.c++

direction.o: ${SRC}/direction.c++ ${INCLUDE}/direction.h++
	$(CC) $(CFLAGS) -c ${SRC}/direction.c++


camera.o: ${SRC}/camera.c++ ${INCLUDE}/camera.h++ direction.o
	$(CC) $(CFLAGS) -c ${SRC}/camera.c++
	
renderer.o: ${SRC}/renderer.c++ ${INCLUDE}/renderer.h++ camera.o
	$(CC) $(CFLAGS) -c ${SRC}/renderer.c++
 
bullet.o: ${SRC}/Entity/bullet.c++ ${INCLUDE}/Entity/bullet.h++ entity.o
	$(CC) $(CFLAGS) -c ${SRC}/Entity/bullet.c++

enemy.o: ${SRC}/Entity/enemy.c++ ${INCLUDE}/Entity/enemy.h++ entity.o
	$(CC) $(CFLAGS) -c ${SRC}/Entity/enemy.c++

entity.o: ${SRC}/Entity/entity.c++ ${INCLUDE}/Entity/entity.h++
	$(CC) $(CFLAGS) -c ${SRC}/Entity/entity.c++

pathFinding.o: ${SRC}/Entity/pathFinding.c++ ${INCLUDE}/Entity/pathFinding.h++ direction.o entity.o
	$(CC) $(CFLAGS) -c ${SRC}/Entity/pathFinding.c++