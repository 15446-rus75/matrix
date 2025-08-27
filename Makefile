CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
BOOST_ROOT = /mnt/c/Users/vlada/boost_1_89_0
BOOST_INCLUDE = -I$(BOOST_ROOT)
BOOST_LIB_DIR = -L$(BOOST_ROOT)/stage/lib

TEST_LDFLAGS = $(BOOST_LIB_DIR) -lboost_unit_test_framework -static

PROGRAM_SRCS = main.cpp
TEST_SRCS = test-matrix.cpp

PROGRAM = matrix_program
TEST_EXEC = matrix_tests

.PHONY: all clean test run

all: $(PROGRAM)

$(PROGRAM): $(PROGRAM_SRCS) matrix.hpp
	$(CXX) $(CXXFLAGS) $(BOOST_INCLUDE) $(PROGRAM_SRCS) -o $@

$(TEST_EXEC): $(TEST_SRCS) matrix.hpp
	$(CXX) $(CXXFLAGS) $(BOOST_INCLUDE) $(TEST_SRCS) -o $@ $(TEST_LDFLAGS)

test: $(TEST_EXEC)
	LD_LIBRARY_PATH=$(BOOST_ROOT)/stage/lib:$$LD_LIBRARY_PATH ./$(TEST_EXEC)

run: $(PROGRAM)
	@if [ -z "$(arg1)" ] || [ -z "$(arg2)" ]; then \
		echo "Usage: make run arg1=<param1> arg2=<param2>"; \
		exit 1; \
	fi
	./$(PROGRAM) $(arg1) $(arg2)

clean:
	rm -f $(PROGRAM) $(TEST_EXEC) *.o
