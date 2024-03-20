#include "ft_printf.h"
#include <stdint.h>
#include <stdio.h>

// int main() {
//     unsigned int max_value = (unsigned int)-1;
//     printf("Maximum possible value for uintptr_t: %lu\n", max_value);
//     return (0);
// }

int	main(void)
{
	printf("Original:\n");
	printf("%#020x", 0);
	printf("\nMine:\n");
	ft_printf("%#020x", 0);
}
