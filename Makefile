PRESENTATION	=	" \e[32m*******************************************************\033[0m\n"\
					"\e[32m*                                                     *\033[0m\n"\
					"\e[32m*        ___  ____       _     _          _ _         *\033[0m\n"\
					"\e[32m*        |  \/  (_)     (_)   | |        | | |        *\033[0m\n"\
					"\e[32m*        | .  . |_ _ __  _ ___| |__   ___| | |        *\033[0m\n"\
					"\e[32m*        | |\/| | | '_ \| / __| '_ \ / _ \ | |        *\033[0m\n"\
					"\e[32m*        | |  | | | | | | \__ \ | | |  __/ | |        *\033[0m\n"\
					"\e[32m*        \_|  |_/_|_| |_|_|___/_| |_|\___|_|_|        *\033[0m\n"\
					"\e[32m*                                                     *\033[0m\n"\
					"\e[32m*                                                     *\033[0m\n"\
					"\e[32m* By: David ASLI && Romane LESEUR                     *\033[0m\n"\
					"\e[32m*******************************************************\033[0m\n"

PRESENTATION2	=	" \e[32m*********************************************************************************\033[0m\n"\
					"\e[32m*                                                                               *\033[0m\n"\
					"\e[32m*        ____    ____   _             _          __             __   __         *\033[0m\n"\
					"\e[32m*       |_   \  /   _| (_)           (_)        [  |           [  | [  |        *\033[0m\n"\
					"\e[32m*         |   \/   |   __   _ .--.   __   .--.   | |--.  .---.  | |  | |        *\033[0m\n"\
					'\e[32m*         | |\\  /| |  [  | [ `.-. | [  | ( (`\\]  | .-. |/ /__\\\\ | |  | |        *\033[0m\n'\
					"\e[32m*        _| |_\/_| |_  | |  | | | |  | |  \`'.'.  | | | || \__., | |  | |        *\033[0m\n"\
					"\e[32m*       |_____||_____|[___][___||__][___][\\__) )[___]|__]'.__.'[___][___]       *\033[0m\n"\
					"\e[32m*                                                                               *\033[0m\n"\
					"\e[32m*                                                                               *\033[0m\n"\
					"\e[32m* By: David ASLI && Romane LESEUR                                               *\033[0m\n"\
					"\e[32m*********************************************************************************\033[0m\n"


####### VARIABLES #######

SRCS_PATH	=	./srcs/
OBJS_PATH	=	./objs/
FILES		=	main.c			\
				lexing.c		\
				parsing.c		\
				manage_lists.c	\
				utils.c
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
				@${CC} ${CFLAGS} -c -I${HEADER_PATH} $< -o $@

${NAME}:			${OBJS}
				@echo ${PRESENTATION2} 
#@make -C libft
				@${CC} ${CFLAGS} -o ${NAME} ${OBJS} -lreadline
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
