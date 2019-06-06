/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:31:41 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/10 18:32:12 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		get_format_data(t_sdl *sdl)
{
	SDL_Surface	*surface[0];

	if (!(surface[0] = SDL_CreateRGBSurface(0, SCR_WID, SCR_HEI, 32,
		RMASK, GMASK, BMASK, AMASK)))
	{
		sdl_error(ON_ERR "get_format_data", SDL_GetError);
		exit(-1);
	}
	sdl->format = (SDL_PixelFormat *)malloc(sizeof(SDL_PixelFormat));
	ft_memcpy(sdl->format, surface[0]->format, sizeof(SDL_PixelFormat));
	SDL_FreeSurface(surface[0]);
	return (0);
}

int		sdl_init(t_sdl *sdl)
{
	Uint32				flags[3];

	flags[0] = SDL_WINDOW_SHOWN;
	flags[1] = SDL_RENDERER_ACCELERATED;
	flags[2] = IMG_INIT_JPG | IMG_INIT_PNG;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS |
		SDL_INIT_AUDIO) < 0)
		return (sdl_error(ON_ERR "sdl_init", SDL_GetError));
	if (IMG_Init(flags[2]) < 0)
		return (sdl_error(ON_ERR "sdl_init", IMG_GetError));
	if (TTF_Init() < 0)
		return (sdl_error(ON_ERR "sdl_init", TTF_GetError));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 8192) < 0)
		return (sdl_error(ON_ERR "sdl_init", Mix_GetError));
	if (!(sdl->window = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCR_WID, SCR_HEI, flags[0])))
		return (sdl_error(ON_ERR "sdl_init", SDL_GetError));
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->window, -1, flags[1])))
		return (sdl_error(ON_ERR "sdl_init", SDL_GetError));
	if (!(sdl->screen = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STATIC, SCR_WID, SCR_HEI)))
		return (sdl_error(ON_ERR "sdl_init", SDL_GetError));
	if (!(sdl->map = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STATIC, MAP_WID, MAP_HEI)))
		return (sdl_error(ON_ERR "sdl_init", SDL_GetError));
	get_format_data(sdl);
	sdl->pixels = (Uint32 *)ft_smemalloc(sizeof(Uint32) *
					SCR_HEI * SCR_WID, "sdl_init");
	sdl->map_pixels = (Uint32 *)ft_smemalloc(sizeof(Uint32) *
					MAP_HEI * MAP_WID, "sdl_init");
	sdl->map_rectn = (SDL_Rect){0, 0, MAP_WID, MAP_HEI};
	sdl->text_rectn = (SDL_Rect){FPS_X, FPS_Y, FPS_WID, FPS_HEI};
	sdl->text_color = (SDL_Color){123, 123, 123, 255};
	sdl->text_font = TTF_OpenFont(FPS_FONT, 25);
	sdl->event_loop = 1;
	return (0);
}

int		sdl_error(char *message, const char (*sdl_error()))
{
	if (message)
		ft_putendl(message);
	ft_putstr("SDL Error: ");
	ft_putendl(sdl_error());
	return (-1);
}

int		sdl_img_error(char *message)
{
	if (message)
		ft_putendl(message);
	ft_putstr("SDL_Image Error: ");
	ft_putendl(IMG_GetError());
	return (-1);
}
