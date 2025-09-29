NAME    = libft.a

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar rcs
RM      = rm -f

FILES =  srcs/Libft/ft_memset \
         srcs/Libft/ft_bzero \
         srcs/Libft/ft_memcpy \
         srcs/Libft/ft_memmove \
         srcs/Libft/ft_memchr \
         srcs/Libft/ft_memcmp \
         srcs/Libft/ft_strlen \
         srcs/Libft/ft_strlcpy \
         srcs/Libft/ft_strlcat \
         srcs/Libft/ft_strchr \
         srcs/Libft/ft_strrchr \
         srcs/Libft/ft_strnstr \
         srcs/Libft/ft_strncmp \
         srcs/Libft/ft_atoi \
         srcs/Libft/ft_isalpha \
         srcs/Libft/ft_isdigit \
         srcs/Libft/ft_isalnum \
         srcs/Libft/ft_isascii \
         srcs/Libft/ft_isprint \
         srcs/Libft/ft_toupper \
         srcs/Libft/ft_tolower \
         srcs/Libft/ft_calloc \
         srcs/Libft/ft_strdup \
         srcs/Libft/ft_substr \
         srcs/Libft/ft_strtrim \
         srcs/Libft/ft_split \
         srcs/Libft/ft_itoa \
         srcs/Libft/ft_strmapi \
         srcs/Libft/ft_putchar_fd \
         srcs/Libft/ft_putstr_fd \
         srcs/Libft/ft_putendl_fd \
         srcs/Libft/ft_putnbr_fd \
         srcs/Libft/ft_striteri \
         srcs/Libft/ft_lstnew \
         srcs/Libft/ft_lstadd_front \
         srcs/Libft/ft_lstsize \
         srcs/Libft/ft_lstlast \
         srcs/Libft/ft_lstadd_back \
         srcs/Libft/ft_lstdelone \
         srcs/Libft/ft_lstclear \
         srcs/Libft/ft_lstiter \
         srcs/Libft/ft_strjoin_nofree \

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I includes -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re