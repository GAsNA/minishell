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

OBJ_DIR        =    objs
INC_DIR        =    headers
SRC_DIR        =    $(shell find srcs -type d)
LIB            =    -lreadline

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

# --  Redirection in OBJS  -- #
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

SRCS			=	main.c					\
					main_utils.c			\
					l_env.c					\
					l_env_utils.c			\
					ft_pwd.c				\
					ft_cd.c					\
					cd_utils.c				\
					env.c env2.c			\
					ft_echo.c				\
					ft_env.c				\
					ft_unset.c				\
					ft_exit.c				\
					ft_exit_error.c			\
					ft_export.c				\
					ft_export_utils.c		\
					utils.c					\
					path.c					\
					exec.c					\
					exec_utils.c			\
					close_exec.c			\
					child.c					\
					signals.c				\
					signals_utils.c			\
					free.c					\
					garbage.c				\
					ft_gsplit.c				\
					ft_strgdup.c			\
					ft_strgjoin.c			\
					ft_subgstr.c			\
					checks_before_all.c		\
					lexing.c				\
					regroup.c				\
					parsing.c				\
					parsing_utils.c			\
					last_splits.c			\
					last_quotes.c			\
					calcul_divide_cmd.c		\
					get_check_fd.c			\
					expand.c				\
					expand_utils.c			\
					heredoc.c				\
					heredoc_utils.c			\
					print_error.c			\
					manage_lists_lexing.c	\
					manage_lists_regroup.c	\
					manage_lists_cmd.c		\
					manage_lists_lenv.c

HEADER_PATH		=	./headers/

CC				=	clang
CFLAGS			=	-Wall -Werror -Wextra -g3
RM				=	rm -rf

LIBFT			=	libft

NAME			=	minishell


####### COMMANDS #######

all:				${NAME}

$(OBJ_DIR)/%.o: %.c
					@mkdir -p ./objs/
					$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

${NAME}:		${OBJS}
				@echo ${PRESENTATION2}
				@make -C srcs/libft
				@${CC} ${CFLAGS} -o ${NAME} ${OBJS} srcs/libft/libft.a -lreadline
				@echo "\e[32m"Compilation success"\033[0m"

v:				${NAME}
				valgrind --leak-check=full --show-leak-kinds=all --suppressions=leak_suppress ./minishell			

clean:
				@${RM} ${OBJ_DIR}
				@echo "\e[35m"Object files deleted"\033[0m"

fclean:				clean
				@make fclean -C srcs/libft
				@${RM} ${NAME}
				@echo "\e[35m"Executable deleted"\033[0m"

re:					fclean all

david:
				@cat srcs/david.txt
