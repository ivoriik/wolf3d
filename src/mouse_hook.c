/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:15:26 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/17 19:15:27 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_events.h"

//int		on_mouse_wheel(Sint32 y, Uint32 dir, t_mlx *e)
//{
//	Uint32	sum;
//
//	if (dir == SDL_MOUSEWHEEL_NORMAL)
//		sum = (y > 0) ? SDLK_z : SDLK_x;
//	else
//		sum = (y < 0) ? SDLK_z : SDLK_x;
//	e->selected ? e->selected->ft_scale(sum, e->selected,
//										&(e->selected->transform), &(e->selected->inverse)) :
//	return (1);
//}
//
//int		on_lbutton_down(int x, int y, t_mlx *e)
//{
//	if (x >= e->sdl->rt_wid || y >= e->sdl->scr_hei)
//		return (0);
//	if (e->pix_obj[y * e->sdl->scr_wid + x])
//		e->selected = (e->pix_obj)[y * e->sdl->scr_wid + x];
//	else
//		e->selected = NULL;
//	return (0);
//}
//
//int		on_rbutton_down(int x, int y, t_mlx *e)
//{
//	(void)x;
//	(void)y;
//	e->selected = NULL;
//	return (0);
//}

int		on_mmotion(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel, t_mlx *e)
{
//	printf("on_motion %i %i; %i %i\n", x, y, xrel, yrel);
	if (x > e->sdl->scr_wid || y > e->sdl->scr_hei)
		return (0);
	if (xrel > 1)
	{
		e->right = 1;
		e->left = 0;
	}
	else if (xrel < -1)
	{
		e->left = 1;
		e->right = 0;
	}
	else
	{
		e->left = 0;
		e->right = 0;
	}
	if (yrel > 1)
	{
		e->down = 1;
		e->up = 0;
	}
	else if (yrel < -1)
	{
		e->up = 1;
		e->down = 0;
	}
	else
	{
		e->up = 0;
		e->down = 0;
	}
	e->init = 0;
	return (1);
}