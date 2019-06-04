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

void	bresenham_x(t_mlx *mlx, t_bresenham *br, unsigned int col, int flag)
{
	if (br->p0[0] > br->p[0])
		ft_swap(&br->p0, &br->p, sizeof(t_vector));
	while (br->p0[0] <= br->p[0])
	{
		img_pixel_put(mlx->sdl, br->p0[0], br->p0[1], col);
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

void	bresenham_y(t_mlx *mlx, t_bresenham *br, unsigned int col, int flag)
{
	if (br->p0[1] > br->p[1])
		ft_swap(&br->p0, &br->p, sizeof(t_vector));
	while (br->p0[1] <= br->p[1])
	{
		img_pixel_put(mlx->sdl, br->p0[0], br->p0[1], col);
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

void	bresenham_xy(t_mlx *mlx, t_bresenham *br, unsigned int col, int flag)
{
	if (br->p0[0] > br->p[0] && br->p0[1] <= br->p[1])
		while (br->p0[1] <= br->p[1])
		{
			img_pixel_put(mlx->sdl, br->p0[0], br->p0[1], col);
			br->p0[0]--;
			br->p0[1]++;
		}
	else if (br->p0[0] <= br->p[0] && br->p0[1] > br->p[1])
		while (br->p0[0] <= br->p[0])
		{
			img_pixel_put(mlx->sdl, br->p0[0], br->p0[1], col);
			(br->p0[0])++;
			(br->p0[1])--;
		}
	else
		while (br->p0[0] <= br->p[0] && br->p0[1] <= br->p[1])
		{
			img_pixel_put(mlx->sdl, br->p0[0], br->p0[1], col);
			(br->p0[0])++;
			(br->p0[1])++;
		}
}

int		bresenham(t_mlx *mlx, t_vector *p, unsigned int col, int flag)
{
	t_bresenham br;

	br.dl[0] = fabs(p[1][0] - p[0][0]);
	br.dl[1] = fabs(p[1][1] - p[0][1]);
	br.error = 2 * br.dl[1] - br.dl[0];
	br.p0 = p[0];
	br.p = p[1];
	if (fabs(br.p[0] - br.p0[0]) > fabs(br.p[1] - br.p0[1]))
		bresenham_x(mlx, &br, col, flag);
	else if (fabs(br.p[0] - br.p0[0]) < fabs(br.p[1] - br.p0[1]))
	{
		br.error = 2 * br.dl[0] - br.dl[1];
		bresenham_y(mlx, &br, col, flag);
	}
	else
	{
		if (br.p0[0] > br.p[0] && br.p0[1] > br.p[1])
			ft_swap(&br.p0, &br.p, sizeof(t_vector));
		bresenham_xy(mlx, &br, col, flag);
	}
	return (1);
}
