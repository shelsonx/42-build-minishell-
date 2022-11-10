NAME			= minishell
LIBFT			= libft.a

CC 				= cc
CF 				= -g -Wall -Wextra -Werror
CFI 			= -I $(INCLUDE)
CREADLINE		= -lreadline

LIBFT_PATH 		= ./libs/libft/
SRC_PATH 		= ./sources/
OBJ_PATH		= ./obj/
INCLUDE 		= ./includes/

SRC				= main.c\
				  prompt.c\
				  exec.c pipe.c paths.c\
				  utils_pipes.c\
				  signals.c\

VPATH 			:= $(SRC_PATH)\
				$(SRC_PATH)prompt\
				$(SRC_PATH)execute\
				$(SRC_PATH)utils\

OBJ				= $(addprefix $(OBJ_PATH), $(notdir $(SRC:.c=.o)))

RM 				= rm -rf

$(OBJ_PATH)%.o: %.c
				mkdir -p $(OBJ_PATH)
				$(CC) $(CF) $(CFI) -c $< -o $@

$(NAME):		$(OBJ)
				make -C $(LIBFT_PATH) $(LIBFT)
				$(CC) -g $(CF) -I $(INCLUDE) -o $(NAME) $(OBJ) -L $(LIBFT_PATH) -lft $(CREADLINE)
				@echo "$(GREEN)$(NAME) created$(DEFAULT)"

all:			$(NAME)

re:				fclean all

clean:
				make -C $(LIBFT_PATH) clean
				$(RM) $(OBJ) $(OBJDIR)
				@echo "$(YELLOW)object files deleted$(DEFAULT)"

fclean:			clean
				make -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)
				@echo "$(RED)all deleted$(DEFAULT)"

install:		
				sudo apt-get install -y libreadline-dev valgrind

leak:							
				valgrind --suppressions=readline.supp --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

.PHONY:			all clean fclean re bonus rebonus

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m