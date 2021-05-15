BINS=bin/main bin/tests
INCLUDE=include/main

CC=g++
CFLAGS=-I $(INCLUDE) -march=native -O3
LDLIBS=
LDFLAGS=--ansi --pedantic -Wall --std=c++11

SRCS_main=$(wildcard src/main/**/*.cpp) $(wildcard src/main/*.cpp)
SRCS_tests=$(wildcard src/tests/**/*.cpp) $(wildcard src/tests/*.cpp)

OBJS_main=$(SRCS_main:src/%.cpp=obj/%.o)
OBJS_tests=$(SRCS_tests:src/%.cpp=obj/%.o)

# c'est un peu sale mais suffisant ; on pourrait aussi mettre tous les objets communs aux tests et au main dans un sous
# dossier "common" et ne laisser à la racine de src/main que les fichiers concernant l'exécution (donc pas modele etc)
OBJS_tests_excluded_from_main=obj/main/main.o


all: $(BINS)

bin/main: $(OBJS_main)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

bin/tests: $(OBJS_tests) $(filter-out $(OBJS_tests_excluded_from_main),$(OBJS_main))
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)


obj/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $^ $(CFLAGS) -D NDEBUG

obj/tests/%.o: src/tests/%.cpp
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $^ $(CFLAGS) -I include/tests -D MAP

clean:
	rm -rf bin/* obj/*

run: bin/main
	./bin/main

run_tests: bin/tests
	./bin/tests

dirs:
	mkdir -p bin/
	mkdir -p obj/
	mkdir -p lib/
	mkdir -p src/
	mkdir -p include/

.PHONY: clean run dirs all run_tests
