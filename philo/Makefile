NAME		:=	philo
LIST_SRCS	:=	actions.c init.c main.c parse.c \
				threads.c utils.c monitor.c

DIR_SRCS	:=	srcs
DIR_OBJS	:=	objs
DIR_INCS	:=	incs

SRCS		:=	$(addprefix $(DIR_SRCS)/,$(LIST_SRCS))
OBJS		:=	$(addprefix $(DIR_OBJS)/,$(LIST_SRCS:.c=.o))

INCS		:=	$(addprefix $(DIR_INCS)/,$(LIST_SRCS:.c=.h))
DEPS		:=	$(SRCS:.c=.d)

CC			:=	cc
CFLAGS		:=	-MMD -MP -Wall -Wextra -Werror

ERASE		:=	\033[2K\r
PINK		:=	\033[35m
BLUE		:=	\033[34m
GREEN		:=	\033[32m
END			:=	\033[0m

-include $(DEPS)

all: $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -I $(DIR_INCS) -c $< -o $@
#@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

$(NAME): $(DIR_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -I $(DIR_INCS) -o $(NAME) $(OBJS)
#	printf "$(ERASE)$(GREEN)$@ made\n$(END)"

clean:
	rm -rf $(DIR_OBJS)
#@printf "$(PINK)remove obj dir\n$(END)"

fclean: clean
	rm -f $(NAME)
#@printf "$(PINK)remove philo\n$(END)"

re: fclean all

leak: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -g -fsanitize=thread"

.PHONY: all clean fclean re leak
