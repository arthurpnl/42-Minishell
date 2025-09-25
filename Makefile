# Nom du programme
NAME = minishell

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Wno-unused-parameter
INCLUDES = -I includes -I Libft/includes

# Bibliothèques
LIBS = -lreadline -L Libft -lft

# Structure des dossiers
SRC_DIR = src
PARSING_DIR = $(SRC_DIR)/parsing
EXEC_DIR = $(SRC_DIR)/exec
BUILTIN_DIR = $(EXEC_DIR)/builtin
OBJ_DIR = obj

# Sources
SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(PARSING_DIR)/*.c) \
       $(wildcard $(EXEC_DIR)/*.c) \
       $(wildcard $(BUILTIN_DIR)/*.c)

# Objets
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Création des dossiers d'objets si nécessaire
$(shell mkdir -p $(OBJ_DIR)/$(SRC_DIR) \
                 $(OBJ_DIR)/$(PARSING_DIR) \
                 $(OBJ_DIR)/$(EXEC_DIR) \
                 $(OBJ_DIR)/$(BUILTIN_DIR))

# Règle principale
all: libft $(NAME)

# Compile le programme
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

# Compilation des fichiers .c en .o
$(OBJ_DIR)/%.o: %.c includes/minishell.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile Libft
libft:
	$(MAKE) -C Libft

# Nettoyage des objets
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C Libft clean

# Nettoyage complet
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C Libft fclean

# Recompilation complète
re: fclean all

# Règle pratique pour exécuter
run: all
	./$(NAME)

# Pour tester avec valgrind
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

# Pour debugger avec gdb
debug: all
	gdb ./$(NAME)

.PHONY: all clean fclean re run valgrind debug libft
