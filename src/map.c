/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:35:31 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/12 17:35:51 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fill_map(t_mlx *mlx, int *z, t_vector *koef, unsigned int color)
{
	int				count_i;
	t_vector		p[2];

//	color = mlx_get_color_value(mlx->mlx_ptr, color);
	count_i = -1;
	p[0][0] = z[1];
	p[0][1] = z[0];
	while (++count_i < (*koef)[0])
	{
		p[1] = p[0];
		p[1][0] = p[1][0] + (*koef)[1];
		bresenham(mlx, &p[0], color, 0);
		p[0][1] += 1;
	}
}

void	fill_pos(t_mlx *mlx, t_vector *pos, double angle)
{
	int				count_i;
	t_vector		p[2];
	unsigned int	color;

//	color = mlx_get_color_value(mlx->mlx_ptr, MAZE_POS);
	count_i = -1;
	p[0] = (t_vector){pos[0][0] - PL_SIZ / 2.0f, pos[0][1] - PL_SIZ / 2.0f};
	while (++count_i < PL_SIZ)
	{
		p[1] = p[0];
		p[1][0] = p[1][0] + PL_SIZ;
		bresenham(mlx, &p[0], color, 0);
		p[0][1] += 1;
	}
	pos[1][0] = pos[0][0] + VW_SIZ * cos(angle);
	pos[1][1] = pos[0][1] - VW_SIZ * sin(angle);
	bresenham(mlx, &mlx->map->pl_mpos[0], color, 0);
}

void	draw_map(t_mlx *mlx, t_map *map)
{
	int				i;
	int				j;
	int				z[2];
	unsigned int	col;

	i = -1;
//	col = mlx_get_color_value(mlx->mlx_ptr, MAZE_WALL);
	while (++i < (int)map->hei)
	{
		j = -1;
		while (++j < (int)map->wid)
			if (map->grid[i][j])
			{
				z[0] = i * map->m_koef[0];
				z[1] = j * map->m_koef[1];
				fill_map(mlx, &z[0], &map->m_koef, col);
			}
	}
	fill_pos(mlx, &(map->pl_mpos[0]), DEG_TO_RAD(map->vw_ang));
}

void	map_rays(t_mlx *mlx, t_map *map, t_intersect *intersect)
{
	unsigned int	col;

	intersect->pl_mpos[0][0] = map->pl_mpos[0][0];
	intersect->pl_mpos[0][1] = map->pl_mpos[0][1];
	intersect->pl_mpos[1][0] = intersect->int_pos[0] \
	/ (float)S_CELL * map->m_koef[1];
	intersect->pl_mpos[1][1] = intersect->int_pos[1] \
	/ (float)S_CELL * map->m_koef[0];
//	col = mlx_get_color_value(mlx->mlx_ptr, MAZE_VIE);
	bresenham(mlx, &(intersect->pl_mpos[0]), col, 0);
}
