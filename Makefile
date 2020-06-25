# Karl Goeltner
# 917006087
# ECS 36C - 05/07/2020
CXX = g++
CXXFLAGS += -std=c++11 -Wall -Werror

all: test_multiset prime_factors

# PROGRAM COMPILATION

test_multiset: test_multiset.o multiset.h
	$(CXX) $(CXXFLAGS) test_multiset.cc -o test_multiset -pthread -lgtest

prime_factors: prime_factors.o multiset.h
	$(CXX) $(CXXFLAGS) prime_factors.cc -o prime_factors

# STYLE CHECK

lint_test_multiset:
	/home/cs36cjp/public/cpplint/cpplint test_multiset.cc

lint_multiset:
	/home/cs36cjp/public/cpplint/cpplint multiset.h

lint_prime:
	/home/cs36cjp/public/cpplint/cpplint prime_factors.cc

clean:
	rm -f test_multiset prime_factors *.o
