//
// Karl Goeltner
// 917006087
// ECS 36C - 05/07/2020
//
// prime_factors.cc - Program that performs trivial prime
// factorization on a number and prints output based on
// specified operation: all, max, min, near.
//

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include "multiset.h"

// primeFactors - store all prime factors of a given number into multiset
Multiset<int> primeFactors(unsigned int number) {
  Multiset<int> mset;

  // If EVEN, store quantity of 2's
  while (number % 2 == 0) {
    mset.Insert(2);
    number /= 2;
  }

  // Now ODD, store remaining odd primes
  for (int i = 3; i <= sqrt(number); i += 2) {
    // Store as long as prime factor exists
    while (number % i == 0) {
      mset.Insert(i);
      number /= i;
    }
  }

  // If PRIME NUMBER remains
  if (number > 2)
    mset.Insert(number);

  // Check if number is a prime factor itself
  if (mset.Size() == 1) {
    std::cout << "No prime factors" << std::endl;
    exit(0);
  }

  return mset;
}

// printNoMatch - print no match if prime factor not found for near
void printNoMatch() {
  std::cout << "No match" << std::endl;
  exit(0);
}

// checkNear - error check before calling printNear to ensure argument validity
void checkNear(int argc, char *prime) {
  // Check that argument count is valid
  if (argc != 4) {
    std::cerr << "Command 'near' expects another argument: [+/-]prime"
      << std::endl;
    exit(1);
  }
  // Check to confirm that prime is valid
  if (!atoi(prime)) {
    std::cerr << "Invalid prime" << std::endl;
    exit(1);
  }
}

// printNear - prints exactly specified or near prime factor
void printNear(unsigned int number, char *prime) {
  Multiset<int> mset = primeFactors(number);
  char sign = prime[0];
  int val = atoi(prime);

  // If + sign
  if (sign == '+') {
    // Throw error if value DNE
    try {
      val = mset.Ceil(val + 1);
    } catch (const std::out_of_range &e) {
      printNoMatch();
    }
    std::cout << val << " (x" << mset.Count(val) << ")" << std::endl;
  // Else if - sign
  } else if (sign == '-') {
    // Throw error if value DNE
    try {
      val = mset.Floor(-(val + 1));
    } catch (const std::out_of_range &e) {
      printNoMatch();
    }
    std::cout << val << " (x" << mset.Count(val) << ")" << std::endl;
  // Else if prime factor ITSELF
  } else if (mset.Contains(val)) {
    std::cout << val << " (x" << mset.Count(val) << ")" << std::endl;
  // Otherwise, NO MATCH
  } else {
    printNoMatch();
  }
}

// printMin - prints minimum prime factor
void printMin(unsigned int number) {
  Multiset<int> mset = primeFactors(number);

  // Print out mimimum prime factor
  std::cout << mset.Min() << " (x" << mset.Count(mset.Min())
    << ")" << std::endl;
}

// printMax - prints maximum prime factor
void printMax(unsigned int number) {
  Multiset<int> mset = primeFactors(number);

  // Print out maximum prime factor
  std::cout << mset.Max() << " (x" << mset.Count(mset.Max())
    << ")" << std::endl;
}

// printAll - prints all the prime factors and their count in ascending order
void printAll(unsigned int number) {
  Multiset<int> mset = primeFactors(number);
  // Initialize to lowest prime factor
  int factor = mset.Min();
  int quantity = 0;

  // Loop until all unique prime factors are printed out
  for (unsigned int i = 0; i < mset.Size(); i++) {
    // Attain the next highest unique prime & quantity
    factor = mset.Ceil(factor);
    quantity = mset.Count(factor);

    std::cout << factor << " (x" << quantity << "), ";

    // Increment factor + 1 for Ceil
    // Increment i to next unique prime for size track
    factor++;
    i += quantity - 1;
  }

  std::cout << std::endl;
}

// Main method
int main(int argc, char *argv[]) {
  // ERROR: Make sure correct number of command-line arguments are present
  if (argc != 3 && argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <number> <command>"
      << " [<args>]" << std::endl;
    exit(1);
  }

  // ERROR: Check to confirm that number is valid & is NOT 0
  if (!atoi(argv[1]) && argv[1][0] != '0') {
    std::cerr << "Invalid number" << std::endl;
    exit(1);
  }

  // ERROR: Check if number is 0 or 1
  if (atoi(argv[1]) == 0 || atoi(argv[1]) == 1) {
    std::cout << "No prime factors" << std::endl;
    exit(0);
  }

  // Convert command to string to execute operand
  std::string command(argv[2]);

  // Execute the respective operation on number
  // Print ALL prime factors
  if (command == "all") {
    printAll(atoi(argv[1]));
  // Print MAX prime factor
  } else if (command == "max") {
    printMax(atoi(argv[1]));
  // Print MIN prime factor
  } else if (command == "min") {
    printMin(atoi(argv[1]));
  // Print nearest prime factor
  } else if (command == "near") {
    checkNear(argc, argv[3]);
    printNear(atoi(argv[1]), argv[3]);
  // ERROR: Invalid command
  } else {
    std::cerr << "Command '" << argv[2] << "' is invalid" << std::endl;
    std::cerr << "Possible commands are: all|min|max|near" << std::endl;
    exit(1);
  }
}
