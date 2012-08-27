hra: main.o
	gcc -o hra main.o -lallegro

main.o: main.c
	gcc -c main.c
