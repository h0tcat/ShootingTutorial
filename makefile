CC = g++
PKGCONFIG = `pkg-config --cflags --libs sdl2 --static` `pkg-config --cflags --libs SDL2_image` `pkg-config --cflags --libs SDL2_mixer --static`

PGNAME = ShootingGame
OBJS = main.o ShootingGame.o

$(PGNAME): $(OBJS)
	$(CC) -o $@ $^ -std=c++11 $(PKGCONFIG)
.cpp.o:
	$(CC) -c -o $@ $< -std=c++11 $(PKGCONFIG)	

PHONY: clean
clean:
	rm -f $(PGNAME) $(OBJS)
