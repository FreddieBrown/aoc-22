CXX=clang++
CFLAGS=-g -std=c++20 -Wno-unused-function -Wno-unknown-warning-option -o main

main: src/*.cpp
			$(CXX) src/*.cpp $(CFLAGS) -o main

day1: 
	make main
	./main day1
day2: 
	make main
	./main day2
day3: 
	make main
	./main day3
day4: 
	make main
	./main day4
day5: 
	make main
	./main day5
day6: 
	make main
	./main day6

clean:
			rm -rf main
