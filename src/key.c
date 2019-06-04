/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:26:37 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 17:26:39 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	is_sound(t_mlx *mlx)
{
	static time_t	prev;
	time_t			curr;
	static int		new;

	curr = time(&curr);
	if (mlx->collision)
		;
	if ((!mlx->forw && !mlx->back && !mlx->rside && !mlx->lside))
	{
		new = 1;
		;
	}
	if ((mlx->forw || mlx->back || mlx->rside || mlx->lside) \
		&& (difftime(curr, prev) > 18.6f || new))
	{
		;
		new = 0;
		prev = curr;
	}
}

int		move(t_mlx *mlx, t_map *map)
{
	t_vector	mov;
	double		ang;
	int			is_mov;
	int			is_rot;

	is_mov = 0;
	is_rot = 0;
	ang = (mlx->forw || mlx->back) ? (map->vw_ang) : (map->vw_ang - 90);
	mov[0] = cos(DEG_TO_RAD(ang)) * ((mlx->forw || mlx->back) \
		? MOVE_SP : SIDE_SP);
	mov[1] = -sin(DEG_TO_RAD(ang)) * ((mlx->forw || mlx->back) \
		? MOVE_SP : SIDE_SP);
	if (mlx->left || mlx->right || mlx->up || mlx->down)
		is_rot = rotate(mlx, map, 0);
	if (mlx->forw || mlx->rside)
		is_mov = step(map, mov, 1);
	if (mlx->back || mlx->lside)
		is_mov = step(map, mov, 0);
	mlx->collision = !(is_mov);
	return (is_mov || is_rot);
}

int		step(t_map *map, t_vector mov, int flag)
{
	t_vector	pos_pr;

	pos_pr = map->pl_pos;
	if (flag)
	{
		if ((map->grid)[(int)(map->pl_pos[1] / 64)]\
			[(int)((map->pl_pos[0] + 2 * mov[0]) / 64)] == 0)
			map->pl_pos[0] += mov[0];
		if ((map->grid)[(int)((map->pl_pos[1] + 2 * mov[1]) / 64)]\
			[(int)(map->pl_pos[0] / 64)] == 0)
			map->pl_pos[1] += mov[1];
	}
	else
	{
		if ((map->grid)[(int)(map->pl_pos[1] / 64)]\
			[(int)((map->pl_pos[0] - 2 * mov[0]) / 64)] == 0)
			map->pl_pos[0] -= mov[0];
		if ((map->grid)[(int)((map->pl_pos[1] - 2 * mov[1]) / 64)]\
			[(int)(map->pl_pos[0] / 64)] == 0)
			map->pl_pos[1] -= mov[1];
	}
	return (pos_pr[0] != map->pl_pos[0] || pos_pr[1] != map->pl_pos[1]);
}

int		rotate(t_mlx *mlx, t_map *map, int flag)
{
	if (mlx->right || flag == 1)
		if ((map->vw_ang += TURN_SP) > 360)
			map->vw_ang -= 360;
	if (mlx->left || flag == 2)
		if ((map->vw_ang -= TURN_SP) < 0)
			map->vw_ang += 360;
	if (mlx->up || flag == 3)
	{
		if (map->pp_cnt + LKUP_SP > SCR_HEI)
			return (mlx->right || mlx->left);
		map->pp_cnt += LKUP_SP;
	}
	if (mlx->down || flag == 4)
	{
		if (map->pp_cnt - LKUP_SP < 0)
			return (mlx->right || mlx->left);
		map->pp_cnt -= LKUP_SP;
	}
	return (1);
}

void	reset(t_mlx *mlx, t_map *map)
{
	mlx->init = 0;
	map->vw_ang = VW_ANG;
	map->pl_pos[0] = map->pos[1] * S_CELL + OFSET;
	map->pl_pos[1] = map->pos[0] * S_CELL + OFSET;
	map->pl_mpos[0][0] = map->pl_pos[0] / (float)S_CELL * map->m_koef[1];
	map->pl_mpos[0][1] = map->pl_pos[1] / (float)S_CELL * map->m_koef[0];
	map->pp_cnt = SCR_HEI / 2;
}
