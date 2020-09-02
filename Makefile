.SILENT:
all: clean main main2 main3 main4 main5 main6 main7

main: obj/image.o obj/images_data.o obj/support_for_main.o
	gcc src/main.c obj/image.o obj/images_data.o obj/support_for_main.o -o main -lm

main2: obj/image.o obj/images_data.o obj/support_for_main.o
	gcc src/main2.c obj/image.o obj/images_data.o obj/support_for_main.o -o main2 -lm

main3: obj/image.o obj/images_data.o obj/support_for_main.o
	gcc src/main3.c obj/image.o obj/images_data.o obj/support_for_main.o -o main3 -lm

main4: obj/image.o obj/images_data.o obj/support_for_main.o
	gcc src/main4.c obj/image.o obj/images_data.o obj/support_for_main.o -o main4 -lm

main5: obj/image.o obj/images_data.o obj/support_for_main.o
	gcc src/main5.c obj/image.o obj/images_data.o obj/support_for_main.o -o main5 -lm

main6: obj/image.o obj/images_data.o obj/support_for_main.o
	gcc src/main6.c obj/image.o obj/images_data.o obj/support_for_main.o -o main6 -lm

main7: obj/image.o obj/images_data.o obj/support_for_main.o
	gcc src/main7.c obj/image.o obj/images_data.o obj/support_for_main.o -o main7 -lm

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
	