CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a
SRCS =
BONUS_SRCS = 
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
INCS = 
INCS_DIR = ./

all: $(NAME)

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS_DIR)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(BONUS_OBJS)
	ar r $(NAME) $(BONUS_OBJS)

.PHONY: all clean fclean re bonus
