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


CFLAGS = -std=c++17 -Wall -fdiagnostics-color=always -I$(ROOT_DIR)/Include -I$(INCLUDE)


# ****************************************************
# Targets needed to bring the executable up to date

default: default_compile main.o
	$(CC) *.o -o ${ROOT_DIR}/.vscode/a.out $(CFLAGS)

exe: static_compile main.o
	$(CCEXE) *.o -o ${ROOT_DIR}/.vscode/a.exe $(CFLAGS)

clean:
	rm *.o ${ROOT_DIR}/.vscode/a.exe ${ROOT_DIR}/.vscode/a.out

static_compile:
	$(eval CFLAGS += $(SFMLSTATICFLAGS) -O )

default_compile:
	$(eval CFLAGS += $(SFMLFLAGS) -g )

main.o: ${SRC}/main.c++ camera.o
	$(CC) $(CFLAGS) -c ${SRC}/main.c++

camera.o: ${SRC}/camera.c++ ${INCLUDE}/camera.h++ vector.o
	$(CC) $(CFLAGS) -c ${SRC}/camera.c++

vector.o: ${SRC}/vector.c++ ${INCLUDE}/vector.h++
	$(CC) $(CFLAGS) -c ${SRC}/vector.c++