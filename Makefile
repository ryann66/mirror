CC=gcc
CXX=g++
CFLAGS=
DFLAGS=-g -Og
BFLAGS=-O2
LFLAGS=
LIBS=-lGL -lGLU -lglut

debug: override CFLAGS+=$(DFLAGS)
debug: all

build: override CFLAGS+=$(BFLAGS)
build: all

all: mirror

mirror: mirror.o Button.o GameScene.o MenuElement.o MenuScene.o utils.o Window.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)

Button.o: Button.cc Button.hh MenuElement.hh Vector2.hh Window.hh Scene.hh utils.hh colors.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

GameScene.o: GameScene.cc GameScene.hh Scene.hh Level.hh Vector2.hh GameComponent.hh Window.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

MenuElement.o: MenuElement.cc MenuElement.hh Vector2.hh Window.hh Scene.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

MenuScene.o: MenuScene.cc Window.hh Scene.hh Vector2.hh MenuScene.hh Button.hh MenuElement.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

mirror.o: mirror.cc Window.hh Scene.hh Vector2.hh MenuScene.hh Button.hh MenuElement.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

utils.o: utils.cc utils.hh Window.hh Scene.hh Vector2.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

Window.o: Window.cc Window.hh Scene.hh Vector2.hh
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	/bin/rm -f *.o mirror
