CC   = gcc -std=c99 -pedantic -Wall -Werror
OBJS = bin/scene.o bin/sphere.o bin/screen.o


ray: src/main.c $(OBJS)
	$(CC) -o ray src/main.c $(OBJS) -lSDL

try: ray
	./ray

bin/screen.o: src/screen.c src/screen.h src/scene.h src/sphere.h src/color.h src/vec3.h
	$(CC) -c -o bin/screen.o src/screen.c

bin/scene.o: src/scene.c src/scene.h src/sphere.h src/color.h src/vec3.h
	$(CC) -c -o bin/scene.o src/scene.c

bin/sphere.o: src/sphere.c src/sphere.h src/color.h src/vec3.h
	$(CC) -c -o bin/sphere.o src/sphere.c

