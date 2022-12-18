#####################INPUTS#####################

#scr functions
MANDATORY_FILES =	main.c \
			cmd_utils.c \
			cmd_utils2.c \
			args_utils.c \
			pipex_exec.c

BONUS_FILES =	main_bonus.c \
			errors_bonus.c \
			malloc_pipes_bonus.c \
			cmd_utils_bonus.c \
			cmd_utils2_bonus.c \
			args_utils_bonus.c \
			pipex_exec_bonus.c

#static library's name
NAME =		pipex
B_NAME =	pipex_bonus

#directories
OBJPATH =			temps
MANDATORY_PATH =	sources
BONUS_PATH =		bonus
LIBFT_PATH =		./libft
LIBFT =				$(LIBFT_PATH)/libft.a

#header to libft.h
INCLUDE =	-I ./ -I $(LIBFT_PATH)

#compiling
CC =	gcc
FLAGS =	-Wall -Werror -Wextra -g3 -O3
GDB =	gdb
VAL =	valgrind --trace-children=yes --track-fds=yes --leak-check=full --track-origins=yes

# clean
RM =		-rm -f
RM_DIR =	rm -rf

#tranform into .o
OBJ_MANDATORY = $(MANDATORY_FILES:%.c=$(OBJPATH)/%.o)
OBJ_BONUS = $(BONUS_FILES:%.c=$(OBJPATH)/%.o)

#####################RULES#####################

#make
all: $(OBJPATH) $(NAME)

#make bonus
bonus: $(OBJPATH) $(B_NAME)

#make folder for temps
$(OBJPATH):
		@mkdir -p $(OBJPATH)

#make libft
$(LIBFT):
		@echo "Compiling Libft..."
		@make -C $(LIBFT_PATH)

#rule name - make pipex
$(NAME): $(LIBFT)  $(OBJ_MANDATORY)
		cc $(FLAGS) -o $(NAME) $(OBJ_MANDATORY) $(LIBFT)

#rule name - make pipex_bonus
$(B_NAME): $(LIBFT)  $(OBJ_BONUS)
		cc $(FLAGS) -o $(B_NAME) $(OBJ_BONUS) $(LIBFT)

#compile MANDATORY
$(OBJPATH)/%.o: $(MANDATORY_PATH)/%.c $(HEADER)
		cc $(FLAGS) -c $< -o $@ $(INCLUDE)

#compile BONUS
$(OBJPATH)/%.o: $(BONUS_PATH)/%.c $(HEADER)
		cc $(FLAGS) -c $< -o $@ $(INCLUDE)

#remove objects
clean:
		make clean -C $(LIBFT_PATH)
		$(RM) $(OBJ_MANDATORY) $(OBJ_BONUS)

#remove all
fclean: clean
		make fclean -C $(LIBFT_PATH)
		$(RM) $(NAME) $(B_NAME) $(RM_DIR) $(OBJPATH)

#clear all
re: fclean all

#avoids double inclusion
.PHONY: all clean fclean re bonus

git:
		git add .
		git commit -m "$(m)"
		git push
