NAME=sky
CC = cc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	$(CC) -o $(NAME) $(OBJS)

$(NAME): $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re