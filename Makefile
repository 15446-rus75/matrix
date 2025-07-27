CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -I.
TEST_LDFLAGS = -lboost_unit_test_framework -static

PROGRAM_SRCS = main.cpp matrix.cpp
TEST_SRCS = test-main.cpp matrix.cpp

PROGRAM = matrix_program
TEST_EXEC = matrix_tests

.PHONY: all clean test run

all: $(PROGRAM)

$(PROGRAM): $(PROGRAM_SRCS) matrix.hpp
	$(CXX) $(CXXFLAGS) $(PROGRAM_SRCS) -o $@

$(TEST_EXEC): $(TEST_SRCS) matrix.hpp
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $@ $(TEST_LDFLAGS)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

run: $(PROGRAM)
	@if [ -z "$(arg1)" ] || [ -z "$(arg2)" ]; then \
		echo "Usage: make run arg1=<param1> arg2=<param2>"; \
		exit 1; \
	fi
	./$(PROGRAM) $(arg1) $(arg2)

clean:
	rm -f $(PROGRAM) $(TEST_EXEC) *.o
