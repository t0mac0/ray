CC   = gcc -std=c99 -pedantic -Wall -Werror
OBJS = bin/scene.o bin/sphere.o bin/screen.o bin/twister.o
HDRS = src/*.h

ray: src/main.c $(OBJS)
	$(CC) -o ray src/main.c $(OBJS) -lSDL

try: ray
	./ray

bin/screen.o: src/screen.c $(HDRS)
	$(CC) -c -o bin/screen.o src/screen.c

bin/scene.o: src/scene.c $(HDRS)
	$(CC) -c -o bin/scene.o src/scene.c

bin/sphere.o: src/sphere.c $(HDRS)
	$(CC) -c -o bin/sphere.o src/sphere.c

bin/twister.o: src/twister.c src/twister.h
	$(CC) -c -o bin/twister.o src/twister.c

