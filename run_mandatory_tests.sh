#!/bin/bash


echo "Compiling..."
cc -Wall -Wextra -Werror test_main.c mandatory_tests.c -L./ -lftprintf -o mandatory
echo ""
echo "Testing..."
valgrind --leak-check=full -q ./mandatory "printf" > reference_out.txt
valgrind --leak-check=full -q ./mandatory "ft_printf" > test_out.txt
diff reference_out.txt test_out.txt
echo ""
echo "Cleaning..."
rm -rf ./mandatory reference_out.txt test_out.txt