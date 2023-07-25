###############################################################################
#                     ██████╗ ██╗██████╗ ███████╗██╗  ██╗                     #       
#                     ██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝	              #
#                     ██████╔╝██║██████╔╝█████╗   ╚███╔╝ 	              #
#                     ██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ 	              #
#                     ██║     ██║██║     ███████╗██╔╝ ██╗	              #
#                     ╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝	              #
###############################################################################

.SILENT: # Deixas de exibir as mensagens de execucao no terminal.
NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

###############################################################################
#				MAKEFILE RULES	                              #
###############################################################################

FILES = ./utils/ft_split.c ./utils/utils.c ./utils/utils2.c ./utils/path.c main.c
OBJ = $(FILES:.c=.o)

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}


###############################################################################
#				MAKEFILE COLORS				      #
###############################################################################

CLR_RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

###############################################################################
#				MAKEFILE COMMANDS	    		      #
###############################################################################

all: $(NAME)

$(NAME): $(OBJ) 
		@echo "$(PURPLE)\n===================================="
		@echo "██████╗ ██╗██████╗ ███████╗██╗  ██╗"
		@echo "██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
		@echo "██████╔╝██║██████╔╝█████╗   ╚███╔╝"
		@echo "██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗"
		@echo "██║     ██║██║     ███████╗██╔╝ ██╗"
		@echo "╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝"
		@echo "====================================\n$(CLR_RESET)"
		@echo "$(GREEN)Compiling of $(RED)$(NAME)...$(CLR_RESET)"
		@touch infile
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo "$(RED)$(NAME) $(GREEN)is ready!$(CLR_RESET)\n"
		@echo "$(PURPLE)====================================$(CLR_RESET)"

clean:
		@rm -f $(OBJ)
		@echo "$(RED)$(NAME) object $(GREEN)files have been deleted.$(CLR_RESET)\n"

fclean: clean
		@rm -f $(NAME)
		@rm -f outfile infile
		@echo "$(RED)$(NAME) $(GREEN)has been deleted.$(CLR_RESET)\n"

re: fclean all
	@echo "$(RED)$(NAME) $(GREEN)has been recompiled.$(CLR_RESET)\n"
	@echo "$(PURPLE)====================================$(CLR_RESET)"

.PHONY: all clean fclean re
