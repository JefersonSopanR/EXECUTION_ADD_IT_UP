NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra -Werror -I.

RM = rm -rf

# Directories for different parts of the project
TOKENIZATION_DIR = ./tokenization/
CREATION_AST_DIR = ./creation_ast/
BUTCHER_DIR = ./butcher/

# Source files for each part
TOKENIZATION = $(addprefix $(TOKENIZATION_DIR), \
      tokenization.c free_tokens.c ft_identify_token_type.c\
      ft_identify_redirections.c token_lists.c)

CREATION_AST = $(addprefix $(CREATION_AST_DIR), \
      ft_checker_is.c ft_create_ast.c ft_create_lists.c\
      ft_free_stuff.c ft_get_something.c utilities.c)

BUTCHER = $(addprefix $(BUTCHER_DIR), \
      execute_command.c setup_files.c\
      start_execution.c)

# All source files
SRC = main.c ft_printout.c ft_duplicate_envp.c $(TOKENIZATION) $(CREATION_AST) $(BUTCHER)

# Object files
OBJ = $(SRC:.c=.o)

# Library
LIBFT = libft/libft.a

.PHONY: all bonus clean fclean re

# Default target
all: $(LIBFT) $(NAME)

# Build the library
$(LIBFT):
	@make -C libft

# Link the final executable
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -Llibft -lft -o $(NAME)

# Compile source files to object files
%.o: %.c $(LIBFT)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@$(RM) $(OBJ)
	@make clean -C libft

# Clean object files and the executable
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

# Rebuild everything
re: fclean all