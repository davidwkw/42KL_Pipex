SRCS =	pipex.c \
		utils.c \

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -I. -fsanitize=address

LIBFTDIR = libft

LIBFT = $(LIBFTDIR)/libft.a

NAME = pipex

all : $(NAME)

$(LIBFT) :
	@make -C $(LIBFTDIR) all

$(NAME) : $(OBJS) $(LIBFT)
	@echo "Creating $(NAME).."
	@$(CC) $(CFLAGS) -o $@ $^

bonus : $(NAME)

clean :
	@echo "Cleaning all .o files.."
	@make -C $(LIBFTDIR) clean
	@rm -f $(OBJS)

fclean : clean
	@echo "Cleaning $(NAME)"
	@make -C $(LIBFTDIR) fclean
	@rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
