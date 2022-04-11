PRESENTATION	=	" \e[32m*******************************************************\033[0m\n"\
					"\e[32m*                                                     *\033[0m\n"\
					"\e[32m*               Project: Minishell                    *\033[0m\n"\
					"\e[32m*                                                     *\033[0m\n"\
					"\e[32m* By: David ASLI && Romane LESEUR                     *\033[0m\n"\
					"\e[32m*******************************************************\033[0m\n"


####### VARIABLES #######

SRCS_PATH	=	./srcs/
OBJS_PATH	=	./objs/
FILES		=	main.c
SRCS		=	$(addprefix ${SRCS_PATH}, ${FILES})
OBJS		=	$(addprefix ${OBJS_PATH}, ${FILES:.c=.o})

HEADER_PATH	=	./headers/
HEADER		=	$(addprefix ${HEADER_PATH}, minishell.h)

CC			=	clang
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf

LIBFT		=	libft

NAME		=	minishell


####### COMMANDS #######

all:				${NAME}

${OBJS_PATH}%.o:	${SRCS_PATH}%.c
				@mkdir -p ${dir $@}
				@${CC} ${CFLAGS} -c $< -o $@

${NAME}:			${OBJS}
				@echo ${PRESENTATION} 
				@make -C libft
				@${CC} ${CFLAGS} -o ${NAME} ${OBJS}
				@echo "\e[32m"Compilation success"\033[0m"

clean:
				@${RM} ${OBJS_PATH}
				@echo "\e[35m"Object files deleted"\033[0m"

fclean:				clean
				@${RM} ${NAME}
				@echo "\e[35m"Executable deleted"\033[0m"

re:					fclean all

david:
				@cat srcs/david.txt

.PHONY:			all clean fclean re
