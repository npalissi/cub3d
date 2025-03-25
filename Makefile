# Compiler and flags
NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
LDFLAGS = -Wl,-rpath=./MacroLibX -L./MacroLibX -lmlx -lSDL2 -lm
DIR_LIB     =   lib

LIBFT_DIR   =  $(DIR_LIB)/libft
LIBFT_LIB   := $(LIBFT_DIR)/libft.a
# Source directories and files
SRCS_DIRS   = src src/parsing src/get_data
SRCS        = $(foreach dir,$(SRCS_DIRS),$(wildcard $(dir)/*.c))

# Verify sources exist
ifeq ($(SRCS),)
    $(error "No .c files found in $(SRCS_DIRS)")
endif

# Objects
OBJS_DIR    = obj
OBJS        = $(SRCS:src/%.c=$(OBJS_DIR)/%.o)

# Includes
INCLUDES    = -I./includes -I./MacroLibX

# Main rule
all: $(NAME)

$(NAME): $(OBJS) 
	@make -C lib/libft
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) lib/libft/libft.a -o $(NAME)

# Rule to compile .c files to .o files
$(OBJS_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: src/parsing/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: src/get_data/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	rm -rf $(OBJS_DIR)
	make clean -C lib/libft

fclean: clean
	rm -f $(NAME)
	make fclean -C lib/libft

re: fclean all
	make re -C lib/libft
.PHONY: all clean fclean re