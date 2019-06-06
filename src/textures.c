/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:59:34 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/25 17:59:36 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static const char	*g_tex_path[TEX_SIZ] =
{
	"media/textures/stone_n.png",
	"media/textures/stone_e.png",
	"media/textures/stone_s.png",
	"media/textures/stone_w.png",
	"media/textures/metal_n.png",
	"media/textures/metal_e.png",
	"media/textures/metal_s.png",
	"media/textures/metal_w.png",
	"media/textures/build_n.png",
	"media/textures/build_e.png",
	"media/textures/build_s.png",
	"media/textures/build_w.png",
	"media/textures/sky.png",
	"media/textures/floor.png"
};

void		free_textures(t_env *e)
{
	int i;

	i = 0;
	while (i < TEX_SIZ && e->tex[i])
	{
		cleanup_sdl_surface(&e->tex[i]);
		i++;
	}
}

int			load_textures(t_env *e)
{
	SDL_Surface	*t;
	int			i;

	i = 0;
	while (i < TEX_SIZ && g_tex_path[i])
	{
		if (!(t = IMG_Load(g_tex_path[i])))
		{
			sdl_img_error(ON_ERR "load textures");
			return (0);
		}
		e->tex[i] = SDL_ConvertSurface(t, e->sdl->format, 0);
		e->tex[i]->pitch /= sizeof(Uint32);
		cleanup_sdl_surface(&t);
		++i;
	}
	e->tex[i] = NULL;
	return (1);
}

int			load_music(t_env *e)
{
	e->sound = Mix_LoadWAV(SOUND);
	if (!e->sound)
		return (sdl_error(ON_ERR "load music", Mix_GetError));
	Mix_Volume(-1, MIX_MAX_VOLUME / 2);
	return (0);
}
