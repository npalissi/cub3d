# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 16:10:21 by edubois-          #+#    #+#              #
#    Updated: 2025/07/02 22:05:15 by npalissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
NAME_BONUS        = cub3Bonus

CC          = cc

CFLAGS      =  -g

LDFLAGS     = -Wl,-rpath=./lib/MacroLibX -L./lib/MacroLibX -lmlx -lSDL2 -lm -o3 -ofast

DIR_LIB     = lib

PRINTF_DIR  := $(DIR_LIB)/printf_fd
PRINTF_LIB  := $(PRINTF_DIR)/libftprintf.a

GNL_DIR  := $(DIR_LIB)/gnl
GNL_LIB  := $(GNL_DIR)/gnl.a

LIBFT_DIR   = $(DIR_LIB)/libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

SRCS_BONUS = \
	srcs_bonus/main.c \
	srcs_bonus/get_data/get_map.c\
	srcs_bonus/parsing/parse_map.c\
	srcs_bonus/parsing/parsing_utils.c\
	srcs_bonus/get_data/get_textures.c\
	srcs_bonus/get_data/get_colors.c\
	srcs_bonus/parsing/parse_colors.c\
	srcs_bonus/utils/print_utils.c\
	srcs_bonus/parsing/parse_params.c\
	srcs_bonus/player/player.c\
	srcs_bonus/player/player_move.c\
	srcs_bonus/player/player_utils.c\
	srcs_bonus/raycasting/init.c\
	srcs_bonus/raycasting/lighting.c\
	srcs_bonus/raycasting/raycasting.c\
	srcs_bonus/raycasting/render_utils.c\
	srcs_bonus/raycasting/render.c\
	srcs_bonus/raycasting/game.c\
	srcs_bonus/raycasting/minimap.c\
	srcs_bonus/raycasting/fps.c\

SRCS = \
	srcs/main.c \
	srcs/utils/print_utils.c \
	srcs/raycasting/init.c \
	srcs/raycasting/game.c \
	srcs/raycasting/raycasting.c \
	srcs/raycasting/render.c \
	srcs/player/player.c \
	srcs/player/player_move.c \
	srcs/player/player_utils.c \
	srcs/parsing/parse_map.c \
	srcs/parsing/parse_colors.c \
	srcs/parsing/parse_params.c \
	srcs/parsing/parsing_utils.c \
	srcs/get_data/get_map.c \
	srcs/get_data/get_textures.c \
	srcs/get_data/get_colors.c \


OBJS_DIR = obj
OBJS_BONUS_DIR = obj_bonus
OBJS = $(SRCS:srcs/%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:srcs_bonus/%.c=$(OBJS_BONUS_DIR)/%.o)

INCLUDES = -I./includes -I./lib/MacroLibX

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[1;34mCompiling libraries...\033[0m"
	@echo "\033[1;33mCompiling libft...\033[0m"
	@make -s -C $(LIBFT_DIR)
	@echo "\033[1;33mCompiling print_fd...\033[0m"
	@make -s -C $(PRINTF_DIR)
	@echo "\033[1;33mCompiling get_next_line...\033[0m"
	@make -s -C $(GNL_DIR)
	@echo "\033[1;33mCompiling MacroLibX...\033[0m"
	@make -s -C lib/MacroLibX -j16
	@echo "\033[1;34mLinking executable...\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT_LIB) $(PRINTF_LIB) $(GNL_LIB) -o $(NAME)
	@echo "\033[1;32mCompilation finished successfully!\033[0m"
	@sleep 0.7
	@echo 
	@echo "\033[1;34mCleaning terminal...\033[0m"
	@sleep 0.8;
	@clear

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@echo "\033[1;34mCompiling libraries for bonus...\033[0m"
	@echo "\033[1;33mCompiling libft...\033[0m"
	@make -s -C $(LIBFT_DIR)
	@echo "\033[1;33mCompiling print_fd...\033[0m"
	@make -s -C $(PRINTF_DIR)
	@echo "\033[1;33mCompiling get_next_line...\033[0m"
	@make -s -C $(GNL_DIR)
	@echo "\033[1;33mCompiling MacroLibX...\033[0m"
	@make -s -C lib/MacroLibX -j16
	@echo "\033[1;34mLinking bonus executable...\033[0m"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LDFLAGS) $(LIBFT_LIB) $(PRINTF_LIB) $(GNL_LIB) -o $(NAME_BONUS)
	@echo "\033[1;32mBonus compilation finished successfully!\033[0m"

# Compilation des fichiers .o pour la version normale
$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@printf "[\033[1;33mCompiling\033[0m] %-30s" "$<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ && echo " \033[1;32m[OK]\033[0m" || echo " \033[1;31m[FAIL]\033[0m"

# Compilation des fichiers .o pour la version bonus
$(OBJS_BONUS_DIR)/%.o: srcs_bonus/%.c
	@mkdir -p $(dir $@)
	@printf "[\033[1;33mCompiling\033[0m] %-30s" "$<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ && echo " \033[1;32m[OK]\033[0m" || echo " \033[1;31m[FAIL]\033[0m"

clean:
	@rm -rf $(OBJS_DIR) $(OBJS_BONUS_DIR)
	@make -s clean -C $(LIBFT_DIR)
	@make -s clean -C $(PRINTF_DIR)
	@make -s clean -C $(GNL_DIR)
	@make -s clean -C lib/MacroLibX
	@echo "\033[1;34mCleaned all object files.\033[0m"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@make -s fclean -C $(LIBFT_DIR)
	@make -s fclean -C $(PRINTF_DIR)
	@make -s fclean -C $(GNL_DIR)
	@make -s fclean -C lib/MacroLibX
	@echo "\033[1;34mFull clean done.\033[0m"

re: fclean all

.PHONY: all bonus clean fclean re