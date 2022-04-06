SRCS	=	$(addprefix srcs/, main.c)

OBJS	=	${SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra

RM		=	rm -rf

LIBFT	=	libft

NAME	=	minishell

all:	${NAME}

%.o:	%.c
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
	@echo   "\e[32m*******************************************************\033[0m"
	@echo   "\e[32m*                                                     *\033[0m"
	@echo   "\e[32m*               Project: Minishell                    *\033[0m"
	@echo   "\e[32m*                                                     *\033[0m"
	@echo   "\e[32m*By: David ASLI && Romane LESEUR                      *\033[0m"
	@echo   "\e[32m*******************************************************\033[0m"
	@make -C libft
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS}
	@echo "\e[32m"Compilation success"\033[0m"

clean:
	@${RM} ${OBJS}
	@echo "\e[35m"Object files deleted"\033[0m"

fclean:	clean
	@${RM} ${NAME}
	@echo "\e[35m"Executable deleted"\033[0m"

re:	fclean all

.PHONY:	clean fclean re	
