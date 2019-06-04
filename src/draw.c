/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:23:30 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/28 13:23:33 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			draw_wall(t_mlx *mlx, t_map *map, t_intersect *int_p, \
	SDL_Surface *tex)
{
	int				i;
	t_vector		p;
	int				y_tex;
	int				delta;
	unsigned int	c;

	int_p->wall_hei = (S_CELL / int_p->dist) * DIST_PP;
	i = 0;
	if ((p[1] = map->pp_cnt - int_p->wall_hei / 2) < 0)
		while (i++ < int_p->wall_hei && p[1] < 0)
			p[1]++;
	p[0] = int_p->s_x;
	delta = map->pp_cnt - SCR_HEI / 2;
	while (++i <= int_p->wall_hei && ++p[1] < SCR_HEI)
	{
		y_tex = ((int)(p[1] - delta) * 256 - SCR_HEI * 128 + \
		(int)int_p->wall_hei * 128) * 64 / (int)int_p->wall_hei / 256;
		if (int_p->side == 0)
			c = img_tex_col(mlx, tex, (int)int_p->int_pos[0] % 64, y_tex % 64);
		else
			c = img_tex_col(mlx, tex, (int)int_p->int_pos[1] % 64, y_tex % 64);
		img_pixel_put(mlx->sdl, p[0], p[1], shading(c, int_p->dist));
	}
	floor_cast(mlx, int_p, delta, p);
}

void			floor_cast(t_mlx *mlx, t_intersect *int_p, int del, t_vector p)
{
	t_vector		fl_w;
	double			curr_dist;
	double			weight;
	t_vector		fl_t;
	unsigned int	col;

	if (int_p->side == 0)
		fl_w = (t_vector){int_p->int_pos[0] / 64.0f, int_p->int_pos[1] / 64.0f};
	else
		fl_w = (t_vector){int_p->int_pos[0] / 64.0f, int_p->int_pos[1] / 64.0f};
	while (p[1] < SCR_HEI)
	{
		curr_dist = SCR_HEI / (2.0f * (p[1] - del) - SCR_HEI);
		weight = curr_dist / (int_p->dist / 64.0f);
		fl_t[0] = weight * fl_w[0] + (1.0 - weight) * \
		mlx->map->pl_pos[0] / 64.0f;
		fl_t[1] = weight * fl_w[1] + (1.0 - weight) * \
		mlx->map->pl_pos[1] / 64.0f;
		fl_t[0] = (int)(fl_t[0] * 64.0f) % S_CELL;
		fl_t[1] = (int)(fl_t[1] * 64.0f) % S_CELL;
		col = img_tex_col(mlx, mlx->tex[13], fl_t[0], fl_t[1]);
		col = (shading(col, curr_dist * 64) >> 1) & 8355711;
		img_pixel_put(mlx->sdl, p[0], p[1], col);
		p[1]++;
	}
}

void			skybox(t_mlx *mlx, SDL_Surface *tex)
{
	int		tex_x;
	int		tex_y;
	Uint32	*data;
	Uint32	*tex_ad;
	int		of_y;

	of_y = SCR_HEI / 2 - (mlx->map->pp_cnt - SCR_HEI / 2);
	tex_x = 0;
	data = mlx->sdl->pixels;
	tex_ad = (Uint32 *)tex->pixels;
	while (tex_x < mlx->sdl->scr_wid)
	{
		tex_y = 0;
		while (tex_y < mlx->map->pp_cnt)
		{
			ft_memcpy(data + tex_y * mlx->sdl->pitch + tex_x, \
			tex_ad + (((tex_y + of_y) % 675) * tex->pitch / sizeof(Uint32) + (((int)(tex_x + \
			mlx->map->vw_ang * 10)) % 1200)), sizeof(Uint32));
			tex_y++;
		}
		tex_x++;
	}
}

unsigned int	shading(unsigned int col, double dist)
{
	t_rgb	rgb;
	double	intencity;

	rgb = hex_to_rgb(col);
	if ((intencity = 150 / dist) > 1)
		intencity = 1;
	return (rgb_to_hex((float)rgb.r * intencity, (float)rgb.g * intencity, \
		(float)rgb.b * intencity));
}
