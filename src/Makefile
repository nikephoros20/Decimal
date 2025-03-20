CC = gcc -Wall -Wextra -Werror -std=c11 -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
LIBS = -lcheck
LINUX = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
HEADERS = s21_decimal.h s21_math.h
SOURCES = $(wildcard *.c)
SRC = s21_decimal.c s21_math.c

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SRC))
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
endif
ifeq ($(OS), Darwin)
 CC += -D OS_MAC
endif

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@

all: clean s21_decimal.a test gcov_report

s21_decimal.a: $(OBJ_LIBRARY)
	ar rcs s21_decimal.a $(OBJ_LIBRARY)
	ranlib s21_decimal.a
	rm -rf *.o

test: s21_decimal.a tests.c
ifeq ($(OS), Darwin)
	$(CC) tests.c s21_decimal.a -o test.out $(LIBS) -lm
else
	$(CC) tests.c s21_decimal.a -o test.out $(LIBS) $(LINUX)
endif
	./test.out

# gcov_report: clean_test
# ifeq ($(OS), Darwin)
# 	$(CC) $(GCOVFLAGS) tests.c ${SRC} -o test.out $(LIBS) -lm
# else
# 	$(CC) $(GCOVFLAGS) tests.c ${SRC} -o test.out $(LIBS) $(LINUX)
# endif
# 	./test.out
# 	lcov -t "stest" -o s21_test.info -c -d .
# 	genhtml -o report s21_test.info
# ifeq ($(OS), Linux)
# 	links ./report/index.html
# else
# 	open -a safari ./report/index.html
# endif

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(SOURCES) $(HEADERS)
	rm -rf .clang-format

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(SOURCES) $(HEADERS)
	rm -rf .clang-format

rebuild: clean all

clean:
	rm -f *.o *.a *.gcno *.gcda *.info a/*.out *.gcov *.out
	rm -rf test ./report *.dSYM */*.dSYM

clean_test:
	rm -rf *.gcda *.gcno *.info test report



# cd 

# cd goinfre

# git clone https://github.com/Homebrew/brew homebrew

# eval "$(/opt/goinfre/vannadri/homebrew/bin/brew shellenv)"
# brew update --force --quiet            

# brew install lcov    

# cd
