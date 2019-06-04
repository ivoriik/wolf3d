/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:39:16 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/12 17:39:36 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		get_pos(t_vector *n_pos, double ang, int side)
{
	t_vector	s_pos;

	s_pos = *n_pos;
	if (side && IN_RANGE(RAD_TO_DEG(ang), 0, 180))
	{
		(*n_pos)[1] = (int)(s_pos[1] / S_CELL) * S_CELL;
		(*n_pos)[0] = s_pos[0] + (s_pos[1] - (*n_pos)[1]--) / tan(ang);
	}
	else if (side && !IN_RANGE(RAD_TO_DEG(ang), 0, 180))
	{
		(*n_pos)[1] = (int)(s_pos[1] / S_CELL) * S_CELL + S_CELL;
		(*n_pos)[0] = s_pos[0] + (s_pos[1] - (*n_pos)[1]) / tan(ang);
	}
	else if (!side && IN_RANGE(RAD_TO_DEG(ang), 90, 270))
	{
		(*n_pos)[0] = (int)(s_pos[0] / S_CELL) * S_CELL;
		(*n_pos)[1] = s_pos[1] + (s_pos[0] - (*n_pos)[0]--) * tan(ang);
	}
	else if (!side && !IN_RANGE(RAD_TO_DEG(ang), 90, 270))
	{
		(*n_pos)[0] = (int)(s_pos[0] / S_CELL) * S_CELL + S_CELL;
		(*n_pos)[1] = s_pos[1] + (s_pos[0] - (*n_pos)[0]) * tan(ang);
	}
}

t_intersect	horiz_int(t_vector n_pos, t_vector st, t_intersect int_p, t_map *m)
{
	get_pos(&n_pos, int_p.ang, 1);
	st[1] = IN_RANGE(RAD_TO_DEG(int_p.ang), 0, 180) ? -S_CELL : S_CELL;
	while (IN_RANGE((n_pos[1] / S_CELL), 0, m->hei - 1) && IN_RANGE(n_pos[0] \
		/ S_CELL, 0, m->wid - 1))
	{
		if (((int_p.tex = m->grid[(int)(n_pos[1] / S_CELL)][(int)(n_pos[0] \
			/ S_CELL)])) != 0)
		{
			int_p.int_pos = n_pos;
			int_p.tex--;
			int_p.dist = (RAD_TO_DEG(int_p.ang) == 90 || RAD_TO_DEG(int_p.ang) \
			== 270) ? fabs((m->pl_pos[1] - n_pos[1]) / sin(int_p.ang)) : \
			fabs((n_pos[0] - m->pl_pos[0]) / cos(int_p.ang));
			return (int_p);
		}
		n_pos += st;
	}
	int_p.dist = INFINITY;
	return (int_p);
}

t_intersect	vertic_int(t_vector n_pos, t_vector st, t_intersect int_p, t_map *m)
{
	get_pos(&n_pos, int_p.ang, 0);
	st[0] = IN_RANGE(RAD_TO_DEG(int_p.ang), 90, 270) ? -S_CELL : S_CELL;
	while (IN_RANGE(n_pos[1] / S_CELL, 0, m->hei - 1) && IN_RANGE(n_pos[0] \
		/ S_CELL, 0, m->wid - 1))
	{
		if ((int_p.tex = m->grid[(int)(n_pos[1] / S_CELL)][(int)(n_pos[0] \
			/ S_CELL)]) != 0)
		{
			int_p.int_pos = n_pos;
			--int_p.tex;
			if (RAD_TO_DEG(int_p.ang) == 0 || RAD_TO_DEG(int_p.ang) == 180)
				int_p.dist = fabs((m->pl_pos[0] - n_pos[0]) / cos(int_p.ang));
			else
				int_p.dist = fabs((m->pl_pos[1] - n_pos[1]) / sin(int_p.ang));
			return (int_p);
		}
		n_pos += st;
	}
	int_p.dist = INFINITY;
	return (int_p);
}

t_vector	calc_step(double ang)
{
	t_vector		step;
	double			tana;

	tana = tan(ang);
	if (IN_RANGE(RAD_TO_DEG(ang), 90, 270))
	{
		if ((step[0] = S_CELL / tana) > 0)
			step[0] = -step[0];
	}
	else
	{
		if ((step[0] = S_CELL / tana) < 0)
			step[0] = -step[0];
	}
	if (IN_RANGE(RAD_TO_DEG(ang), 180, 360))
	{
		if ((step[1] = S_CELL * tana) < 0)
			step[1] = -step[1];
	}
	else
	{
		if ((step[1] = S_CELL * tana) > 0)
			step[1] = -step[1];
	}
	return (step);
}

double		find_wall(t_mlx *mlx, t_map *map, t_intersect int_p)
{
	t_intersect		x_inters;
	t_intersect		y_inters;
	t_texture		*tex;

	x_inters = horiz_int(map->pl_pos, calc_step(int_p.ang), int_p, map);
	y_inters = vertic_int(map->pl_pos, calc_step(int_p.ang), int_p, map);
	if (x_inters.dist < y_inters.dist)
	{
		int_p = x_inters;
		int_p.side = 0;
		tex = IN_RANGE(RAD_TO_DEG(int_p.ang), 0, 180) ? mlx->tex[(int_p.tex \
		* 4)] : mlx->tex[(int_p.tex * 4 + 2)];
	}
	else
	{
		int_p = y_inters;
		int_p.side = 1;
		tex = IN_RANGE(RAD_TO_DEG(int_p.ang), 90, 270) ? \
		mlx->tex[(int_p.tex * 4 + 1)] : mlx->tex[(int_p.tex * 4 + 3)];
	}
	int_p.dist *= cos(fabs(DEG_TO_RAD(map->vw_ang) - int_p.ang));
	draw_wall(mlx, map, &int_p, tex);
	map_rays(mlx, map, &int_p);
	return (1);
}
