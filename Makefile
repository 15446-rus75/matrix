CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wno-sign-compare
BOOST_ROOT = /mnt/c/Users/vlada/boost_1_89_0
BOOST_INCLUDE = -I$(BOOST_ROOT)
BOOST_LIB_DIR = -L$(BOOST_ROOT)/stage/lib

TEST_LDFLAGS = $(BOOST_LIB_DIR) -lboost_unit_test_framework -static

PROGRAM_SRCS = main.cpp
VECTOR_TEST_SRCS = test-vector.cpp
MATRIX_TEST_SRCS = test-matrix.cpp

PROGRAM = matrix_program
VECTOR_TEST_EXEC = vector_tests
MATRIX_TEST_EXEC = matrix_tests

.PHONY: all clean test test-vector test-matrix run

all: $(PROGRAM)

$(PROGRAM): $(PROGRAM_SRCS) matrix.hpp vector.hpp
	$(CXX) $(CXXFLAGS) $(BOOST_INCLUDE) $(PROGRAM_SRCS) -o $@

$(VECTOR_TEST_EXEC): $(VECTOR_TEST_SRCS) vector.hpp
	$(CXX) $(CXXFLAGS) $(BOOST_INCLUDE) $(VECTOR_TEST_SRCS) -o $@ $(TEST_LDFLAGS)

$(MATRIX_TEST_EXEC): $(MATRIX_TEST_SRCS) matrix.hpp vector.hpp
	$(CXX) $(CXXFLAGS) $(BOOST_INCLUDE) $(MATRIX_TEST_SRCS) -o $@ $(TEST_LDFLAGS)

test: test-vector test-matrix

test-vector: $(VECTOR_TEST_EXEC)
	LD_LIBRARY_PATH=$(BOOST_ROOT)/stage/lib:$$LD_LIBRARY_PATH ./$(VECTOR_TEST_EXEC)

test-matrix: $(MATRIX_TEST_EXEC)
	LD_LIBRARY_PATH=$(BOOST_ROOT)/stage/lib:$$LD_LIBRARY_PATH ./$(MATRIX_TEST_EXEC)

run: $(PROGRAM)
	@if [ -z "$(arg1)" ] || [ -z "$(arg2)" ]; then \
		echo "Usage: make run arg1=<param1> arg2=<param2>"; \
		exit 1; \
	fi
	./$(PROGRAM) $(arg1) $(arg2)

clean:
	rm -f $(PROGRAM) $(VECTOR_TEST_EXEC) $(MATRIX_TEST_EXEC) *.o
