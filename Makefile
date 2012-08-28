hra: main.o
	gcc -o hra main.o -lallegro -lallegro_image

main.o: main.c
	gcc -c main.c
