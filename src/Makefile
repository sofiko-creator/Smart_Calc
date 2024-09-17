CC = g++ 
CFLAGS = -Wall -Wextra -Werror -std=c++17
OS := $(shell uname -s)
MYFLAGS = -lgtest -lgtest_main -lpthread #-lrt -lsubunit

ifeq ($(OS),Linux)
	CFLAGS+=-D LINUX
	OPEN_CMD = xdg-open
else
	ifeq ($(OS),Darwin)
		CFLAGS+=-D MAC
		OPEN_CMD = open
	endif
endif

all: tests gcov_report

dvi:
	$(OPEN_CMD) Doc.md

uninstall:
	rm -rf build

install: clean 
	mkdir build
	cd build && qmake ../SmartCalc && make

run_calc: 
	./build/SmartCalc

dist: install uninstall
	rm -rf dist-marquita-smartcalc.tar.gz    
	tar -czf dist-marquita-smartcalc.tar.gz *

tests: model/calc_model.cpp test_calculate/test.cpp 
	mkdir -p test_files
	$(CC) $^ -o test_files/$@ $(CFLAGS) $(MYFLAGS) --coverage
	./test_files/tests

gcov_report: tests
	./test_files/tests
	gcovr --html-details test_files/gcov_result.html
	$(OPEN_CMD) test_files/gcov_result.html

check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n --style=Google controller/*.cpp
	clang-format -n --style=Google controller/*.h
	clang-format -n --style=Google model/*.cpp
	clang-format -n --style=Google model/*.h
	clang-format -n --style=Google SmartCalc/*.cpp
	clang-format -n --style=Google SmartCalc/*.h

clean:
	rm -rf *.o *.gcda *.a *.html *.gcno *.css .clang-format build 
	rm -f test
	rm -rf *.tar.gz
	rm -rf SmartCalc/*.o
	rm -rf controller/*.o
	rm -rf model/*.o
	rm -rf test_files

rebuild: clean all
