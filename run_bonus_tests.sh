#!/bin/bash


echo "Compiling..."
cc -Wall -Wextra -Werror test_main.c bonus_tests.c -L./ -lftprintf -o bonus
echo ""
echo "Testing..."
valgrind --leak-check=full -q ./bonus "printf" > reference_out.txt
valgrind --leak-check=full -q ./bonus "ft_printf" > test_out.txt
diff reference_out.txt test_out.txt
echo ""
echo "Cleaning..."
rm -rf ./bonus reference_out.txt test_out.txt