NAME		:=	philo
LIST_SRCS	:=	actions.c init.c main.c parse.c que.c \
				threads.c utils.c monitor.c print.c

DIR_SRCS	:=	srcs
DIR_OBJS	:=	objs
DIR_INCS	:=	incs

SRCS		:=	$(addprefix $(DIR_SRCS)/,$(LIST_SRCS))
OBJS		:=	$(addprefix $(DIR_OBJS)/,$(LIST_SRCS:.c=.o))

CC			:=	cc
CFLAGS		:=	-MMD -Wall -Wextra -Werror -g

all: $(NAME)

-include $(DIR_OBJS)/*.d

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	$(CC) $(CFLAGS) -I $(DIR_INCS) -c $< -o $@

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

$(NAME): $(DIR_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -I $(DIR_INCS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(DIR_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

thread: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -g -fsanitize=thread"

leak: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -g -fsanitize=address"

.PHONY: all clean fclean re leak
