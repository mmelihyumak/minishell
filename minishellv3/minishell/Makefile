GREEN			=	"\033[0;32m"
BLUE			=	"\033[0;36m"
END				=	"\033[0;0m"

SRCS		=		main.c minishell_exec.c utils_signal.c file_process.c utils_list.c \
					list_initializer.c utils_modified.c utils_format.c spreader_utils.c \
					pipe_process.c spreader.c set_s_cmd.c fd_settings.c error_check.c \
					get_env.c exec_echo.c exec_export.c exec_cd.c  heredoc_settings.c \
					exec_unset.c
					

LIBFT		=		-I./libft

OBJS		=		$(SRCS:.c=.o)

NAME		=		minishell

CC			=		gcc -g

CFLAGS		=		-I./lib/readline/include

LDFLAGS 	= 		-L./lib/readline/lib -lreadline

RM			=		rm -rf

LIB 		= 		./lib/.minishell

all:	$(LIB)	$(NAME) $(LIBFT)

$(LIBFT):
			@echo $(GREEN) "Creating LIBFT..."$(END)
			@make bonus -C ./libft

$(NAME):	$(OBJS) $(LIBFT)
				@echo $(BLUE) "Creating minishell..."$(END)
				@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -lreadline -o $(NAME)
				@echo $(GREEN) "Minishell created."$(END)

$(LIB):
	@make -C ./lib

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@$(RM) $(OBJS)
				@make clean -C ./libft
				@echo $(BLUE) "Removing objects..."$(END)

fclean:		clean
				@echo $(BLUE) "Removing minishell..."$(END)
				@$(RM) $(NAME)
			@echo $(BLUE) "Removing libft.a..."$(END)
			@make fclean -C libft

ffclean:
		@make fclean
		@make fclean -C ./lib

re:			fclean all

.PHONY:		all clean fclean re