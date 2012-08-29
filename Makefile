hra: main.o player.o
	gcc -o hra main.o player.o -lallegro -lallegro_image

main.o: main.c
	gcc -c main.c

player.o: player.c
	gcc -c player.c
