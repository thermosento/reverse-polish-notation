#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "./Deque.h"

#define MAX_LINE_LENGTH 100

// Function prototypes
int gcd(int a, int b);
void print_rational(int num, int denom);
rat_num reduce_rational(int num, int denom);

int main() {
  char* input = NULL;
  size_t buf_size = 0;
  int num1;
  Deque* the_deque = Deque_Allocate();
  if (the_deque == NULL) {
    return EXIT_FAILURE;
  }

  while (1) {
    ssize_t len = getline(&input, &buf_size, stdin);
    if (len == -1) {
      break;
    }

    if (len > 0 && input[len - 1] == '\n')
      input[len - 1] = '\0';

    if (sscanf(input, "%d", &num1) == 1) {
      rat_num new_num = reduce_rational(num1, 1);
      Deque_Push_Back(the_deque, new_num);
      print_rational(new_num.numerator, new_num.denominator);
    } else {
      // Convert input to lowercase for case-insensitive comparison
      for (int i = 0; input[i]; i++)
        input[i] = tolower((unsigned char)input[i]);

      // Perform the operations
      if (strcmp(input, "+") == 0) {
        if (Deque_Size(the_deque) < 2) {
          printf("STACK ERROR\n");
          return EXIT_FAILURE;
        }
        rat_num num2, num1;
        Deque_Pop_Back(the_deque, &num2);
        Deque_Pop_Back(the_deque, &num1);

        // Sum the two fractions
        int result_num = num1.numerator * num2.denominator +
                         num2.numerator * num1.denominator;
        int result_denom = num1.denominator * num2.denominator;
        rat_num result = reduce_rational(result_num, result_denom);
        Deque_Push_Back(the_deque, result);
        print_rational(result.numerator, result.denominator);
      } else if (strcmp(input, "-") == 0) {
        if (Deque_Size(the_deque) < 2) {
          printf("STACK ERROR\n");
          return EXIT_FAILURE;
        }
        rat_num num2, num1;
        Deque_Pop_Back(the_deque, &num2);
        Deque_Pop_Back(the_deque, &num1);

        // Subtract the two fractions
        int result_num = num1.numerator * num2.denominator -
                         num2.numerator * num1.denominator;
        int result_denom = num1.denominator * num2.denominator;
        rat_num result = reduce_rational(result_num, result_denom);
        Deque_Push_Back(the_deque, result);
        print_rational(result.numerator, result.denominator);
      } else if (strcmp(input, "*") == 0) {
        if (Deque_Size(the_deque) < 2) {
          printf("STACK ERROR\n");
          return EXIT_FAILURE;
        }
        rat_num num2, num1;
        Deque_Pop_Back(the_deque, &num2);
        Deque_Pop_Back(the_deque, &num1);

        // Multiply the two fractions
        int result_num = num1.numerator * num2.numerator;
        int result_denom = num1.denominator * num2.denominator;
        rat_num result = reduce_rational(result_num, result_denom);
        Deque_Push_Back(the_deque, result);
        print_rational(result.numerator, result.denominator);
      } else if (strcmp(input, "/") == 0) {
        if (Deque_Size(the_deque) < 2) {
          printf("STACK ERROR\n");
          return EXIT_FAILURE;
        }
        rat_num num2, num1;
        Deque_Pop_Back(the_deque, &num2);
        Deque_Pop_Back(the_deque, &num1);

        if (num2.numerator == 0) {
          printf("DIVIDE BY ZERO\n");
          return EXIT_FAILURE;
        }

        // Divide the fractions
        int result_num = num1.numerator * num2.denominator;
        int result_denom = num1.denominator * num2.numerator;
        rat_num result = reduce_rational(result_num, result_denom);
        Deque_Push_Back(the_deque, result);
        print_rational(result.numerator, result.denominator);
      } else if (strcmp(input, "dup") == 0) {
        if (Deque_Size(the_deque) < 1) {
          printf("STACK ERROR\n");
          return EXIT_FAILURE;
        }
        rat_num num;
        Deque_Peek_Back(the_deque, &num);
        Deque_Push_Back(the_deque, num);
        print_rational(num.numerator, num.denominator);
      } else if (strcmp(input, "swap") == 0) {
        if (Deque_Size(the_deque) < 2) {
          printf("STACK ERROR\n");
          return EXIT_FAILURE;
        }
        rat_num num2, num1;
        Deque_Pop_Back(the_deque, &num2);
        Deque_Pop_Back(the_deque, &num1);
        Deque_Push_Back(the_deque, num2);
        Deque_Push_Back(the_deque, num1);
        print_rational(num1.numerator, num1.denominator);
      } else if (strcmp(input, "drop") == 0) {
        if (Deque_Size(the_deque) < 1) {
          printf("STACK ERROR\n");
          return EXIT_FAILURE;
        }
        rat_num dropped;
        Deque_Pop_Back(the_deque, &dropped);
        if (Deque_Size(the_deque) > 0) {
          rat_num current_back;
          Deque_Peek_Back(the_deque, &current_back);
          print_rational(current_back.numerator, current_back.denominator);
        }
      } else if (strcmp(input, "clear") == 0) {
        // Clear all elements from the deque without freeing the deque itself
        while (Deque_Size(the_deque) > 0) {
          rat_num temp;
          Deque_Pop_Back(the_deque, &temp);
        }
      } else if (strcmp(input, "quit") == 0) {
        break;
      } else {
        printf("Unknown command\n");
      }
    }

    // Reset input buffer for next iteration
    free(input);
    input = NULL;
    buf_size = 0;
  }

  // Free resources before exiting
  if (input != NULL) {
    free(input);
  }
  Deque_Free(the_deque);
  return EXIT_SUCCESS;
}

// Euclidean algorithm to find GCD
int gcd(int a, int b) {
  if (b == 0) {
    return (a < 0) ? -a : a;  // Return absolute value of a
  }
  while (b != 0) {
    int tmp = b;
    b = a % b;
    a = tmp;
  }
  return (a < 0) ? -a : a;  // Return absolute value of a
}

// Print rational number in reduced form
void print_rational(int num, int denom) {
  rat_num reduced = reduce_rational(num, denom);
  printf("%d/%d\n", reduced.numerator, reduced.denominator);
}

// Reduce rational number to simplest form
rat_num reduce_rational(int num, int denom) {
  if (denom == 0) {
    fprintf(stderr, "Error: Denominator cannot be zero\n");
    exit(EXIT_FAILURE);
  }
  int divisor = gcd(num, denom);
  num /= divisor;
  denom /= divisor;

  if (denom < 0) {
    num = -num;
    denom = -denom;
  }

  return (rat_num){num, denom};
}