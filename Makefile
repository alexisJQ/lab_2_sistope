.SILENT:
all: clean bin/main bin/main2 bin/main3

bin/main: obj/image.o obj/images_data.o obj/support_for_main.o
	gcc src/main.c obj/image.o obj/images_data.o obj/support_for_main.o -o main -lm

bin/main2: obj/image.o obj/images_data.o obj/support_for_main.o
	gcc src/main2.c obj/image.o obj/images_data.o obj/support_for_main.o -o main2 -lm

bin/main3: obj/image.o obj/images_data.o obj/support_for_main.o
	gcc src/main3.c obj/image.o obj/images_data.o obj/support_for_main.o -o main3 -lm

obj/image.o: 
	gcc -c -Iinclude src/image.c -o obj/image.o

obj/support_for_main.o: 
	gcc -c -Iinclude src/support_for_main.c -o obj/support_for_main.o

obj/images_data.o: 
	gcc -c -Iinclude src/images_data.c -o obj/images_data.o

.PHONY: clean

clean:
	rm -f obj/*.o
	rm -f *output.jpg
	rm -f main*
	