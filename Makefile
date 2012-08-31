hra: main.o player.o list.o
	gcc -o hra main.o player.o list.o -lallegro -lallegro_image

main.o: main.c player.h list.h
	gcc -c main.c

player.o: player.c
	gcc -c player.c

list.o: list.c list.h
	gcc -c list.c
