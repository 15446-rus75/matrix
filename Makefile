CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TESTFLAGS = -lboost_unit_test_framework -DBOOST_TEST_DYN_LINK

SRC = main.cpp matrix.cpp
TEST_SRC = test-main.cpp matrix.cpp
HEADERS = matrix.hpp

TARGET = matrix
TEST_TARGET = matrix-tests

.PHONY: all test clean

all: $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

$(TEST_TARGET): $(TEST_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_TARGET) $(TESTFLAGS)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o
