SRCS := array/ft_arraydupe.c\
		array/ft_arraylen.c\
		array/ft_free_tab.c\
		array/ft_split.c\
		char/ft_isalnum.c\
		char/ft_isalpha.c\
		char/ft_isascii.c\
		char/ft_isdigit.c\
		char/ft_isprint.c\
		char/ft_issign.c\
		char/ft_iswhitespace.c\
		lst/ft_lstadd_back_bonus.c\
		lst/ft_lstadd_front_bonus.c\
		lst/ft_lstclear_bonus.c\
		lst/ft_lstdelone_bonus.c\
		lst/ft_lstlast_bonus.c\
		lst/ft_lstnew_bonus.c\
		lst/ft_lstsize_bonus.c\
		memory/ft_bzero.c\
		memory/ft_calloc.c\
		memory/ft_memchr.c\
		memory/ft_memcmp.c\
		memory/ft_memcpy.c\
		memory/ft_memmove.c\
		memory/ft_memset.c\
		put/ft_putchar_fd.c\
		put/ft_putendl_fd.c\
		put/ft_putnbr_fd.c\
		put/ft_putstr_fd.c\
		string/ft_atoi.c\
		string/ft_buildstr.c\
		string/ft_itoa.c\
		string/ft_strapp.c\
		string/ft_strchr.c\
		string/ft_strcmp.c\
		string/ft_strdup.c\
		string/ft_striteri.c\
		string/ft_strjoin.c\
		string/ft_strjoinfree.c\
		string/ft_strlcat.c\
		string/ft_strlcpy.c\
		string/ft_strlen.c\
		string/ft_strmapi.c\
		string/ft_strncmp.c\
		string/ft_strnstr.c\
		string/ft_strrchr.c\
		string/ft_strtrim.c\
		string/ft_substr.c\
		string/ft_tolower.c\
		destructor_handler/ft_deshandler.c

CC := cc
CFLAGS := -Wall -Wextra -Werror
OBJS := $(SRCS:.c=.o)

NAME := libft.a

all: $(NAME)

# Créer la bibliothèque statique
$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)

# Compiler les fichiers objets
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all fclean bonus re