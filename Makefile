CXX = g++
CXXFLAGS = -g --std=c++20 -Wall

all: game game_set tests

game_set: card.o main_set.o
	${CXX} ${CXXFLAGS} card.o main_set.o -o game_set

game: card_list.o main.o card.o
	${CXX} ${CXXFLAGS} card_list.o main.o card.o -o game

# Split tests target into build and run
tests: tests_build tests_run

tests_build: card.o card_list.o tests.o
	${CXX} ${CXXFLAGS} card.o card_list.o tests.o -o tests

tests_run: tests_build
	./tests

main_set.o: main_set.cpp card.h
	${CXX} ${CXXFLAGS} main_set.cpp -c

main.o: main.cpp card_list.h card.h
	${CXX} ${CXXFLAGS} main.cpp -c

tests.o: tests.cpp card.h card_list.h
	${CXX} ${CXXFLAGS} tests.cpp -c

card_list.o: card_list.cpp card_list.h card.h
	${CXX} ${CXXFLAGS} card_list.cpp -c

card.o: card.cpp card.h
	${CXX} ${CXXFLAGS} card.cpp -c

clean:
	rm -f game_set game tests *.o