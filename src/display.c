/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:19:29 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/21 16:11:31 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			img_pixel_put(Uint32 *pixels, t_ivec pnt,
					t_ivec max_pnt, unsigned int color)
{
	if (!(pnt[0] >= 0 && pnt[0] < max_pnt[0] && pnt[1] >= 0 &&
		pnt[1] < max_pnt[1]))
		return ;
	pixels[(int)(pnt[1] * max_pnt[0] + pnt[0])] = color;
}

unsigned int	img_tex_col(SDL_Surface *tex, int x_tex, int y_tex)
{
	Uint32			*tex_data;
	unsigned int	color;

	y_tex = y_tex < 0 ? -y_tex : y_tex;
	x_tex = x_tex < 0 ? -x_tex : x_tex;
	if (y_tex >= 64)
		y_tex %= 64;
	if (x_tex >= 64)
		y_tex %= 64;
	tex_data = (Uint32 *)tex->pixels + y_tex *
			tex->pitch + x_tex;
	ft_memcpy(&color, tex_data, sizeof(Uint32));
	return (color);
}
