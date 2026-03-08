make:
	g++ -std=c++11 -Wall -Werror -g main.cpp -o main

clean:
	rm *.o main -f

run: main
	./main

zip:
	zip matrix.zip *.cpp .h

rz:
	rm -f matrix.zip

unzip:
	if [ -f "Student Files.zip" ]; then \
		unzip -o "Student Files.zip"; \
	else \
		echo "Student Files.zip not found"; \
	fi