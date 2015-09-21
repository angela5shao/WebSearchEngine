# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

# $^ is an auto variable that means "all dependencies",
#   which are test.cpp and $(BIN_DIR)/fib.o in this case
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
$(BIN_DIR)/listTest: alisttest.cpp $(BIN_DIR)/alistint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/alistint.o: alistint.h alistint.cpp
	$(CC) $(CPPFLAGS) alistint.cpp -o $(BIN_DIR)/alistint.o

.PHONY: tests
clean:
	rm -rf $(BIN_DIR)

tests: $(BIN_DIR)/listTest
	-@$(BIN_DIR)/listTest
	-@echo "--- All Tested!---"