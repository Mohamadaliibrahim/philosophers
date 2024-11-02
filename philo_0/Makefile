CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC = srcs/philo.c \
	  srcs/philo_utils.c \
	  srcs/ft_atoi.c \
	  srcs/init_philo.c

OBJ = $(SRC:.c=.o)
NAME = philo
LIBDIR = ft_printf
LIB = $(LIBDIR)/libftprintf.a

all: $(LIB) $(NAME) 

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -I includes -c $< -o $@

$(LIB):
	$(MAKE) -C $(LIBDIR) all

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re