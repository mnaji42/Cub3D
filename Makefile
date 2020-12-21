# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/14 15:59:14 by soel-kar          #+#    #+#              #
#    Updated: 2019/11/17 11:52:07 by mnaji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

FLAGS = -Wall -Wextra -Werror

SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/
MINLBX_DIR = ./minilibx_macos/
LIBBMP_DIR = ./libbmp/

SRC_FILES = main.c parsing.c cub3d_utils.c print_error.c window.c create_image.c move.c draw.c parsing_stock.c sprite.c
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
MINLBX	= $(addprefix $(MINLBX_DIR), libmlx.a)

LNK  = -L $(LIBFT_DIR) -lft -L $(LIBBMP_DIR) -lbmp -L $(MINLBX_DIR) \
			-lmlx -framework OpenGL -framework AppKit

all: $(OBJ) $(LIBFT) $(MINLBX) $(LIBBMP_DIR) $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@gcc $(FLAGS) -I $(MINLBX_DIR) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)
$(MINLBX):
	@make -C $(MINLBX_DIR)

$(NAME): $(OBJ)
	@gcc $(OBJ) $(LNK) -lm -o $(NAME)
	@echo "\033[32m$(NAME) generated!\033[0m"

clean:
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MINLBX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re obj
