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
		media.c\
		raycast.c\
		sdl_cleanup.c\
		threads.c
		
CC =	gcc
# compilation flags
CFLAGS	=	-Wextra -Werror -Wall -O2
# external libraries
LDFLAGS =	$(LIBSDL) -lm $(FT_LNK)
# object files
OBJ		= $(addprefix $(OBJ_DIR),$(SRC:.c=.o))
# directories
SRC_DIR	= ./src/
INC_DIR	= ./inc/
OBJ_DIR	= ./obj/
# libft library
FT		= ./libft/
FT_INC	= -I $(FT)
FT_LNK	= -L $(FT) -lft

ifeq ($(shell uname -s), Darwin)
SDL_INK	=	-I frameworks/SDL2.framework/Headers/ \
			-I frameworks/SDL2_image.framework/Headers/\
			-I frameworks/SDL2_mixer.framework/Headers/\
			-I frameworks/SDL2_ttf.framework/Headers/
LIBSDL	=	-F ./frameworks -rpath ./frameworks -framework SDL2\
			-F ./frameworks -rpath ./frameworks -framework SDL2_image\
			-F ./frameworks -rpath ./frameworks -framework SDL2_mixer\
			-F ./frameworks -rpath ./frameworks -framework SDL2_ttf
INCLDS =	$(INC_DIR) $(FT_INC) $(SDL_INK)
endif
ifeq ($(shell uname -s), Linux)
LIBSDL =	-lSDL2_mixer -lSDL2_image -lSDL2_ttf -lSDL2
INCLDS =	$(INC_DIR) $(FT_INC)
endif

.PHONY: all obj $(NAME) clean fclean

all: obj 
	@$(MAKE) -C $(FT)
	@$(MAKE) name

obj:
	mkdir -p $(OBJ_DIR)

name: $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	$(CC) -I $(INCLDS) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(FT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean
			
re:	fclean all