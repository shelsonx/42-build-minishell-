NAME =					minishell
 
LIBFT = 				${LIBFT_PATH}/libft.a 
LIBFT_PATH = 			libs/libft

SOURCES_FILES =			main.c
SOURCES_FILES +=		prompt/prompt.c
OBJECTS_FILES =			${SOURCES_FILES:.c=.o}
INCLUDES_PATH =			includes
SOURCES_PATH =			sources
OBJECTS_PATH =			objects

SOURCES =				$(addprefix ${SOURCES_PATH}/, ${SOURCES_FILES})
OBJECTS =				$(addprefix ${OBJECTS_PATH}/, ${OBJECTS_FILES})
HEADER =				${INCLUDES_PATH}/minishell.h

REMOVE =				rm -rf
CC =					@cc -g3 -Wall -Wextra -Werror

all:					${NAME}

${NAME}:				${OBJECTS_PATH} ${OBJECTS} ${LIBFT} 
						@${CC} ${OBJECTS} ${LIBFT} \
						-o ${NAME}
						@echo "$(GREEN)$(NAME) created$(DEFAULT)"

${OBJECTS_PATH}:
						@mkdir -p $@

${OBJECTS_PATH}/%.o:	${SOURCES_PATH}/%.c ${HEADER} Makefile | ${OBJECTS_PATH}
						@${CC} -c $< -o $@

${LIBFT}:
						@${MAKE} -C ${LIBFT_PATH} 

clean:
						@$(MAKE) -C $(LIBFT_PATH) clean
						@${REMOVE} ${OBJECTS_PATH}
						@echo "$(YELLOW)object files deleted$(DEFAULT)"

fclean:					clean
						@$(MAKE) -C $(LIBFT_PATH) fclean
						@${REMOVE} ${NAME}
						@echo "$(RED)all deleted$(DEFAULT)"

re:						fclean all

.PHONY:					all clean fclean re run vg

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m