CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

NAME = libftprintf.a
SRCS = ft_printf.c \
./print_single_format/skip_single_format.c \
./print_single_format/parse_format_config.c \
./print_single_format/utils/do_on_space_pading.c \
./print_single_format/utils/pad_zeros.c \
./print_single_format/utils/ft_utobase.c \
./print_single_format/print_per_conv/print_ptr_conv.c \
./print_single_format/print_per_conv/print_str_conv.c \
./print_single_format/print_per_conv/print_uint_conv.c \
./print_single_format/print_per_conv/print_lhex_conv.c \
./print_single_format/print_per_conv/print_int_conv.c \
./print_single_format/print_per_conv/print_char_conv.c \
./print_single_format/print_per_conv/print_pct_conv.c \
./print_single_format/print_per_conv/print_uhex_conv.c \
./print_single_format/print_single_format.c
OBJS = $(SRCS:.c=.o)
INCS = ./ft_printf.h ./libft/libft.h ./print_single_format/print_single_format.h
INCS_DIR = $(dir $(INCS))
INC_FLAGS = $(addprefix -I, $(INCS_DIR))
LIB_FLAGS = -L./libft/ -lft

all: $(NAME)

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(LIB_FLAGS) $< -o $@ 

$(NAME): libft $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

libft:
	$(MAKE) -C ./libft

.PHONY: all clean fclean re bonus libft
