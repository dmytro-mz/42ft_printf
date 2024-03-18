#include <stdio.h>
#include "ft_printf.h"

void run_tests(int (*f)());

int main(int ac, char *av[])
{
    void *func;
    if (ac == 2)
    {
        if (strcmp(av[1], "printf"))
            func = &printf;
        else if (strcmp(av[1], "ft_printf"))
            func = &ft_printf;
        else
        {
            printf("ERROR: Wrong function name \"%s\".", av[1]);
            return 0;
        }
        run_tests(func);
    }
    else
        printf("ERROR: Provide function name.");
    return 0;
}
