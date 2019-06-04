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

	if (!(surface[0] = SDL_CreateRGBSurface(0, sdl->scr_wid, sdl->scr_hei, 32,
										 RMASK, GMASK, BMASK, AMASK)))
	{
		sdl_error(ON_ERR "get_format_data");
		exit(-1);
	}
	sdl->pitch = surface[0]->pitch / sizeof(Uint32);
	sdl->format = (SDL_PixelFormat *)malloc(sizeof(SDL_PixelFormat));
	ft_memcpy(sdl->format, surface[0]->format, sizeof(SDL_PixelFormat));
	SDL_FreeSurface(surface[0]);
	return (0);
}

int		sdl_init(t_sdl *sdl)
{
	Uint32				flags[3];

	flags[0] = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	flags[1] = SDL_RENDERER_ACCELERATED;
	flags[2] = IMG_INIT_JPG | IMG_INIT_PNG;
	sdl->scr_wid = SCR_WID;
	sdl->scr_hei = SCR_HEI;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return (sdl_error(ON_ERR "sdl_init"));
	if (!IMG_Init(flags[2]))
		return (sdl_img_error(ON_ERR "sdl_init"));
	if (!(sdl->window = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_UNDEFINED,
										 SDL_WINDOWPOS_UNDEFINED, SCR_WID, SCR_HEI, flags[0])))
		return (sdl_error(ON_ERR "sdl_init"));
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->window, -1, flags[1])))
		return (sdl_error(ON_ERR "sdl_init"));
	if (!(sdl->screen = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
										  SDL_TEXTUREACCESS_STATIC, sdl->scr_wid, sdl->scr_hei)))
		return (sdl_error(ON_ERR "sdl_init"));
	get_format_data(sdl);
	sdl->pixels = (Uint32 *)ft_smemalloc(sizeof(Uint32) *
										 sdl->scr_hei * sdl->scr_wid, "sdl_init");
	sdl->scr_cont = (SDL_Rect){0, 0, sdl->scr_wid, sdl->scr_hei};
//	printf("SDL_HINT_RENDER_VSYNC %i\n", SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"));
	return (0);
}

int		sdl_error(char *message)
{
	if (message)
		ft_putendl(message);
	ft_putstr("SDL Error: ");
	ft_putendl(SDL_GetError());
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
