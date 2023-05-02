SRCS		=		main.c minishell_exec.c utils_signal.c file_process.c utils_list.c \
					list_initializer.c utils_modified.c utils_format.c spreader_utils.c \
					pipe_process.c spreader.c set_s_cmd.c fd_settings.c error_check.c \
					get_env.c exec_echo.c exec_export.c exec_cd.c

LIBFT		=		-I./libft

OBJS		=		$(SRCS:.c=.o)

NAME		=		minishell

CC			=		gcc

CFLAGS		=		

RM			=		rm -rf

all:		$(NAME) $(LIBFT)

$(LIBFT):
			make bonus -C ./libft

$(NAME):	$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) -lreadline $(OBJS) libft/libft.a  -o $(NAME) && ./$(NAME)

clean:
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re