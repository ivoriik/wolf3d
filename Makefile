# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/28 17:25:30 by vbespalk          #+#    #+#              #
#    Updated: 2018/10/10 17:20:41 by vbespalk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	wolf3d

# source files
SRC =	bresenham.c\
		display.c\
		draw.c\
		events.c\
		free.c\
		init_sdl.c\
		init.c\
		key_hook.c\
		key.c\
		main.c\
		map.c\
		raycast.c\
		sdl_cleanup.c\
		textures.c\
		threads.c
		

# object files
OBJ		= $(addprefix $(OBJ_DIR),$(SRC:.c=.o))

# directories
SRC_DIR	= ./src/
INC_DIR	= ./inc/
OBJ_DIR	= ./obj/

# compilation flags
CFLAGS	= -Wextra -Werror -Wall
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
SDL_INK	=	-I frameworks/SDL2.framework/Headers/ \
			-I frameworks/SDL2_image.framework/Headers/\
			-I frameworks/SDL2_mixer.framework/Headers/\
			-I frameworks/SDL2_ttf.framework/Headers/
SDL_LNK	= 	-F ./frameworks -rpath ./frameworks -framework SDL2\
			-F ./frameworks -rpath ./frameworks -framework SDL2_image\
			-F ./frameworks -rpath ./frameworks -framework SDL2_mixer\
			-F ./frameworks -rpath ./frameworks -framework SDL2_ttf
else
	INC =
	LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
endif
# libft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I $(FT)
FT_LNK	= -L $(FT) -l ft

#rules
all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	$(CC) -I $(INC_DIR) $(CFLAGS) $(FT_INC) $(SDL_INK) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) $(SDL_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(FT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean
			
re:	fclean all