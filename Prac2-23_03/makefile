#add all the files that you need to the files makefile variable below as a space seperated list
files = 

main: main.cpp shader.cpp
	g++ -g shader.cpp $(files) main.cpp -lglfw -pthread -lGLEW -ldl -lGL -o main

clean:
	rm -f *.o main

run:
	./main
val:
	valgrind ./main

all:
	make clean
	make
	make run


zip:
	make clean
	make
	zip u24594522.zip *.h *.cpp makefile *.glsl
