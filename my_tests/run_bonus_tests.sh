#!/bin/bash

script_dir=$(dirname $(realpath "$0"))
parent_dir=$(dirname "$script_dir")

echo "Compiling..."
make re -C ${parent_dir}
make clean -C ${parent_dir}
cc -Wall -Wextra -Werror ${script_dir}/test_main.c ${script_dir}/bonus_tests.c \
    -L${parent_dir} -lftprintf \
    -L${parent_dir}/libft/ -lft \
    -I${parent_dir} -I${parent_dir}/libft/ \
    -o bonus
echo ""
echo "Testing..."
valgrind --leak-check=full -q ./bonus "printf" > reference_out.txt
valgrind --leak-check=full -q ./bonus "ft_printf" > test_out.txt
diff -u --text reference_out.txt test_out.txt
echo ""
echo "Cleaning..."
rm -rf ./bonus reference_out.txt test_out.txt
