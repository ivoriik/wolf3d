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

void			draw_wall(t_env *e, t_map *map, t_intersect *int_p,
					SDL_Surface *tex)
{
	int				i;
	t_vector		p;
	int				y_tex;
	int				delta;
	unsigned int	c;

	int_p->wall_hei = (S_CELL / int_p->dist) * DIST_PP;
	p = (t_vector){int_p->s_x, map->pp_cnt - int_p->wall_hei / 2};
	i = 0;
	if (p[1] < 0)
	{
		i = -(int)p[1];
		p[1] = 0;
	}
	delta = map->pp_cnt - SCR_HEI / 2;
	while (i++ <= int_p->wall_hei && p[1] < SCR_HEI)
	{
		y_tex = ((int)(p[1] - delta) * 256 - SCR_HEI * 128 +
				(int)int_p->wall_hei * 128) * 64 / (int)int_p->wall_hei / 256;
		c = int_p->side == 0 ? img_tex_col(tex, (int)int_p->int_pos[0] % 64,
			y_tex % 64) : img_tex_col(tex, (int)int_p->int_pos[1] % 64,
			y_tex % 64);
		img_pixel_put(e->sdl->pixels, (t_ivec){(int)p[0], (int)p[1]},
				(t_ivec){SCR_WID, SCR_HEI}, shading(c, int_p->dist));
		++p[1];
	}
	floor_cast(e, int_p, delta, p);
}

void			floor_cast(t_env *e, t_intersect *int_p, int del, t_vector p)
{
	t_vector		fl_w;
	double			curr_dist;
	double			weight;
	t_vector		fl_t;
	unsigned int	col;

	fl_w = (t_vector){int_p->int_pos[0] / 64.f, int_p->int_pos[1] / 64.f};
	fl_t = (t_vector){FLT_MIN, FLT_MIN};
	while (p[1] < SCR_HEI)
	{
		curr_dist = SCR_HEI / (2.0f * (p[1] - del) - SCR_HEI);
		weight = curr_dist / (int_p->dist / 64.0f);
		fl_t[0] = weight * fl_w[0] + (1.0 - weight) *
				e->map->pl_pos[0] / 64.0f;
		fl_t[1] = weight * fl_w[1] + (1.0 - weight) *
				e->map->pl_pos[1] / 64.0f;
		fl_t[0] = (int)(fl_t[0] * 64.0f) % S_CELL;
		fl_t[1] = (int)(fl_t[1] * 64.0f) % S_CELL;
		col = img_tex_col(e->tex[13], (int)fl_t[0], (int)fl_t[1]);
		col = (shading(col, curr_dist * 64) >> 1) & 8355711;
		img_pixel_put(e->sdl->pixels, (t_ivec){(int)p[0], (int)p[1]},
					(t_ivec){SCR_WID, SCR_HEI}, col);
		++p[1];
	}
}

void			skybox(t_env *e, SDL_Surface *tex, int x)
{
	int		tex_xy[2];
	Uint32	*data;
	Uint32	*tex_ad;
	int		of_y;

	of_y = (int)(SCR_HEI * 0.5 - (e->map->pp_cnt - SCR_HEI * 0.5));
	data = e->sdl->pixels;
	tex_ad = (Uint32 *)tex->pixels;
	tex_xy[0] = x;
	tex_xy[1] = 0;
	x = ((int)(x + e->map->vw_ang * 10)) % 1200;
	while (tex_xy[1] < e->map->pp_cnt)
	{
		ft_memcpy(data + tex_xy[1] * SCR_WID + tex_xy[0], tex_ad + (((tex_xy[1] +
			of_y) % 675) * tex->pitch + x), sizeof(Uint32));
		++tex_xy[1];
	}
}

unsigned int	shading(unsigned int col, double dist)
{
	t_color	rgb;
	double	intensity;

	rgb.val = col;
	if ((intensity = 150.0 / dist) > 1)
		intensity = 1;
	rgb.argb[0] = (t_byte)(rgb.argb[0] * intensity);
	rgb.argb[1] = (t_byte)(rgb.argb[1] * intensity);
	rgb.argb[2] = (t_byte)(rgb.argb[2] * intensity);
	rgb.argb[3] = (t_byte)(rgb.argb[3] * intensity);
	return (rgb.val);
}
