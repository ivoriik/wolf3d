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

int		move(t_env *e, t_map *map)
{
	t_vector	mov;
	double		ang;
	int			is_mov;
	int			is_rot;

	is_mov = 0;
	is_rot = 0;
	ang = (e->keys[W_FWRD] || e->keys[W_BACK]) ?
			(map->vw_ang) : (map->vw_ang - 90);
	mov[0] = cos(DEG_TO_RAD(ang)) * ((e->keys[W_FWRD] || e->keys[W_BACK]) \
		? MOVE_SP : SIDE_SP);
	mov[1] = -sin(DEG_TO_RAD(ang)) * ((e->keys[W_FWRD] || e->keys[W_BACK]) \
		? MOVE_SP : SIDE_SP);
	if (e->keys[W_FWRD] || e->keys[W_LSIDE])
		is_mov = step(map, mov, 1);
	if (e->keys[W_BACK] || e->keys[W_RSIDE])
		is_mov = step(map, mov, 0);
//	e->collision = !(is_mov);
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

int		rotate(t_env *e, t_map *map)
{
	if (e->keys[W_RIGHT])
		if ((map->vw_ang += TURN_SP) > 360)
			map->vw_ang -= 360;
	if (e->keys[W_LEFT])
		if ((map->vw_ang -= TURN_SP) < 0)
			map->vw_ang += 360;
	if (e->keys[W_UP])
	{
		if (map->pp_cnt + LKUP_SP > SCR_HEI)
			return (e->keys[W_RIGHT] || e->keys[W_LEFT]);
		map->pp_cnt += LKUP_SP;
	}
	if (e->keys[W_DOWN])
	{
		if (map->pp_cnt - LKUP_SP < 0)
			return (e->keys[W_RIGHT] || e->keys[W_LEFT]);
		map->pp_cnt -= LKUP_SP;
	}
	return (1);
}

void	reset(t_map *map)
{
	map->vw_ang = VW_ANG;
	map->pl_pos[0] = map->pos[1] * S_CELL + OFSET;
	map->pl_pos[1] = map->pos[0] * S_CELL + OFSET;
	map->pl_mpos[0][0] = map->pl_pos[0] / (float)S_CELL * map->m_koef[1];
	map->pl_mpos[0][1] = map->pl_pos[1] / (float)S_CELL * map->m_koef[0];
	map->pp_cnt = SCR_HEI / 2;
}
