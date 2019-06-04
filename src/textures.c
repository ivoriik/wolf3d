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

void		destroy_texture(t_mlx *mlx, t_texture *tex)
{
	if (tex != NULL)
	{
		if (tex->ptr != NULL)
			SDL_FreeSurface(tex->ptr);
		ft_memdel((void **)&tex);
	}
}

void		free_textures(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < TEX_SIZ && mlx->tex[i])
	{
		SDL_FreeSurface(mlx->tex[i]);
		i++;
	}
}

int			load_textures(t_mlx *mlx)
{
	SDL_Surface	*t;
	int			i;

	i = 0;
	while (i < TEX_SIZ && tex_path[i])
	{
		if (!(t = IMG_Load(tex_path[i])))
		{
			sdl_img_error(ON_ERR "load textures");
			return (0);
		}
		mlx->tex[i] = SDL_ConvertSurface(t, mlx->sdl->format, 0);
		SDL_FreeSurface(t);
		++i;
	}
	mlx->tex[i] = NULL;
	return (1);
}
