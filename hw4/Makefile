# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/search $(BIN_DIR)/.dirstamp
	./$(BIN_DIR)/search data/index.txt
	
# $^ is an auto variable that means "all dependencies",
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files

$(BIN_DIR)/webpage.o: webpage.h webpage.cpp $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c webpage.cpp -o $(BIN_DIR)/webpage.o 

$(BIN_DIR)/myset.o: myset.h myset.cpp $(BIN_DIR)/webpage.o $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c myset.cpp -o $(BIN_DIR)/myset.o 

$(BIN_DIR)/pageparserMD.o: pageparser.h pageparserMD.h pageparserMD.cpp $(BIN_DIR)/myset.o $(BIN_DIR)/pageparserMD.o 
	$(CC) $(CPPFLAGS) -c pageparserMD.cpp -o $(BIN_DIR)/pageparserMD.o 

$(BIN_DIR)/searcheng.o: $(BIN_DIR)/webpage.o $(BIN_DIR)/myset.o $(BIN_DIR)/pageparserMD.o searcheng.h searcheng.cpp $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c searcheng.cpp -o $(BIN_DIR)/searcheng.o 

$(BIN_DIR)/search: $(BIN_DIR)/myset.o $(BIN_DIR)/webpage.o $(BIN_DIR)/pageparserMD.o $(BIN_DIR)/searcheng.o search.cpp
	$(CC) $(CPPFLAGS) $^ -o $(BIN_DIR)/search


$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean alisttest
clean:
	rm -rf $(BIN_DIR)
