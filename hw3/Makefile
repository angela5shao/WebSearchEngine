# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/alisttest $(BIN_DIR)/.dirstamp
	./$(BIN_DIR)/alisttest
# $^ is an auto variable that means "all dependencies",
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
$(BIN_DIR)/alistint.o: alistint.h alistint.cpp $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c alistint.cpp -o $(BIN_DIR)/alistint.o 

$(BIN_DIR)/alisttest: alisttest.cpp $(BIN_DIR)/alistint.o 
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean alisttest
clean:
	rm -rf $(BIN_DIR)

tests: $(BIN_DIR)/alisttest
	-@$(BIN_DIR)/alisttest
	-@echo "--- All Tested!---"