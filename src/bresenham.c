/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 12:55:29 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/28 12:55:31 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	bresenham_x(t_env *e, t_bresenham *br, unsigned int col)
{
	if (br->p0[0] > br->p[0])
		ft_swap(&br->p0, &br->p, sizeof(t_vector));
	while (br->p0[0] <= br->p[0])
	{
		img_pixel_put(e->sdl->map_pixels, (t_ivec){(int)br->p0[0],
			(int)br->p0[1]}, (t_ivec){MAP_WID, MAP_HEI}, col);
		if (br->error < 0)
			br->error = br->error + 2 * br->dl[1];
		else
		{
			(br->p[1] > br->p0[1]) ? (br->p0[1])++ : (br->p0[1])--;
			br->error = br->error + 2 * br->dl[1] - 2 * br->dl[0];
		}
		(br->p0[0])++;
	}
}

static void	bresenham_y(t_env *e, t_bresenham *br, unsigned int col)
{
	if (br->p0[1] > br->p[1])
		ft_swap(&br->p0, &br->p, sizeof(t_vector));
	while (br->p0[1] <= br->p[1])
	{
		img_pixel_put(e->sdl->map_pixels, (t_ivec){(int)br->p0[0],
			(int)br->p0[1]}, (t_ivec){MAP_WID, MAP_HEI}, col);
		if (br->error < 0)
			br->error = br->error + 2 * br->dl[0];
		else
		{
			(br->p[0] > br->p0[0]) ? (br->p0[0])++ : (br->p0[0])--;
			br->error = br->error + 2 * br->dl[0] - 2 * br->dl[1];
		}
		(br->p0[1])++;
	}
}

static void	bresenham_xy(t_env *e, t_bresenham *br, unsigned int col)
{
	if (br->p0[0] > br->p[0] && br->p0[1] <= br->p[1])
		while (br->p0[1] <= br->p[1])
		{
			img_pixel_put(e->sdl->map_pixels, (t_ivec){(int)br->p0[0],
			(int)br->p0[1]}, (t_ivec){MAP_WID, MAP_HEI}, col);
			br->p0[0]--;
			br->p0[1]++;
		}
	else if (br->p0[0] <= br->p[0] && br->p0[1] > br->p[1])
		while (br->p0[0] <= br->p[0])
		{
			img_pixel_put(e->sdl->map_pixels, (t_ivec){(int)br->p0[0],
			(int)br->p0[1]}, (t_ivec){MAP_WID, MAP_HEI}, col);
			(br->p0[0])++;
			(br->p0[1])--;
		}
	else
		while (br->p0[0] <= br->p[0] && br->p0[1] <= br->p[1])
		{
			img_pixel_put(e->sdl->map_pixels, (t_ivec){(int)br->p0[0],
			(int)br->p0[1]}, (t_ivec){MAP_WID, MAP_HEI}, col);
			(br->p0[0])++;
			(br->p0[1])++;
		}
}

int		bresenham(t_env *e, t_vector *p, unsigned int col)
{
	t_bresenham br;

	br.dl[0] = fabs(p[1][0] - p[0][0]);
	br.dl[1] = fabs(p[1][1] - p[0][1]);
	br.error = 2 * br.dl[1] - br.dl[0];
	br.p0 = p[0];
	br.p = p[1];
	if (fabs(br.p[0] - br.p0[0]) > fabs(br.p[1] - br.p0[1]))
		bresenham_x(e, &br, col);
	else if (fabs(br.p[0] - br.p0[0]) < fabs(br.p[1] - br.p0[1]))
	{
		br.error = 2 * br.dl[0] - br.dl[1];
		bresenham_y(e, &br, col);
	}
	else
	{
		if (br.p0[0] > br.p[0] && br.p0[1] > br.p[1])
			ft_swap(&br.p0, &br.p, sizeof(t_vector));
		bresenham_xy(e, &br, col);
	}
	return (1);
}
