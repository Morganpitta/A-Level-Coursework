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


CFLAGS = -lstdc++ -std=c++17 -Wall -fdiagnostics-color=always -Wdelete-non-virtual-dtor -I$(ROOT_DIR)/Include -I$(INCLUDE)

entities = entity.o tank.o obstacle.o bullet.o player.o

# ****************************************************
# Targets needed to bring the executable up to date

default: default_compile main.o
	$(CC) *.o -o ${ROOT_DIR}/.vscode/a.out $(CFLAGS)

exe: exe_compile static_compile main.o
	$(CC) *.o -o ${ROOT_DIR}/.vscode/a.exe $(CFLAGS)

clean:
	rm *.o ${ROOT_DIR}/.vscode/a.exe ${ROOT_DIR}/.vscode/a.out

exe_compile:
	$(eval CC = $(CCEXE) )

static_compile:
	$(eval CFLAGS += $(SFMLSTATICFLAGS) -O )

default_compile:
	$(eval CFLAGS += $(SFMLFLAGS) -g )

main.o: ${SRC}/main.c++ mainLoop.o
	$(CC) $(CFLAGS) -c ${SRC}/main.c++
	
mainLoop.o: ${SRC}/mainLoop.c++ battleZone.o
	$(CC) $(CFLAGS) -c ${SRC}/mainLoop.c++

battleZone.o: ${SRC}/battleZone.c++ ${INCLUDE}/battleZone.h++ renderer.o ${entities}
	$(CC) $(CFLAGS) -c ${SRC}/battleZone.c++

player.o: ${SRC}/Entity/player.c++ ${INCLUDE}/Entity/player.h++ entity.o
	$(CC) $(CFLAGS) -c ${SRC}/Entity/player.c++

bullet.o: ${SRC}/Entity/bullet.c++ ${INCLUDE}/Entity/bullet.h++ entity.o
	$(CC) $(CFLAGS) -c ${SRC}/Entity/bullet.c++

obstacle.o: ${SRC}/Entity/obstacle.c++ ${INCLUDE}/Entity/obstacle.h++ entity.o
	$(CC) $(CFLAGS) -c ${SRC}/Entity/obstacle.c++

tank.o: ${SRC}/Entity/tank.c++ ${INCLUDE}/Entity/tank.h++ entity.o
	$(CC) $(CFLAGS) -c ${SRC}/Entity/tank.c++

entity.o: ${SRC}/Entity/entity.c++ ${INCLUDE}/Entity/entity.h++ battleZone.o model3D.o collisionRect.o
	$(CC) $(CFLAGS) -c ${SRC}/Entity/entity.c++

collisionRect.o: ${SRC}/Entity/collisionRect.c++ ${INCLUDE}/Entity/collisionRect.h++ vector.o
	$(CC) $(CFLAGS) -c ${SRC}/Entity/collisionRect.c++

renderer.o: ${SRC}/Render/renderer.c++ ${INCLUDE}/Render/renderer.h++ model3D.o camera.o
	$(CC) $(CFLAGS) -c ${SRC}/Render/renderer.c++

model3D.o: ${SRC}/Render/model3D.c++ ${INCLUDE}/Render/model3D.h++ triangle.o line.o
	$(CC) $(CFLAGS) -c ${SRC}/Render/model3D.c++

triangle.o: ${SRC}/Render/triangle.c++ ${INCLUDE}/Render/triangle.h++
	$(CC) $(CFLAGS) -c ${SRC}/Render/triangle.c++

line.o: ${SRC}/Render/line.c++ ${INCLUDE}/Render/line.h++
	$(CC) $(CFLAGS) -c ${SRC}/Render/line.c++

camera.o: ${SRC}/Render/camera.c++ ${INCLUDE}/Render/camera.h++ vector.o
	$(CC) $(CFLAGS) -c ${SRC}/Render/camera.c++

vector.o: ${SRC}/vector.c++ ${INCLUDE}/vector.h++
	$(CC) $(CFLAGS) -c ${SRC}/vector.c++