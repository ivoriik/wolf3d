/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:35:53 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/28 12:09:58 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//int		exit_x(void *mlx)
//{
//	t_mlx *m;
//
//	m = (t_mlx *)mlx;
//	mlx_destroy_image(m->mlx_ptr, m->img_ptr);
//	free_textures(m);
//	clear_grid(&m->map->grid, m->map->hei, NULL);
//	system("killall afplay 2&>/dev/null >/dev/null");
//	exit(0);
//	return (0);
//}

int		key_press(SDL_Keycode k, void *mlx)
{
	t_mlx *ptr;

	ptr = (t_mlx *)mlx;
	if (k == SDLK_w)
		ptr->forw = 1;
	if (k == SDLK_s)
		ptr->back = 1;
	if (k == SDLK_d)
		ptr->rside = 1;
	if (k == SDLK_a)
		ptr->lside = 1;
	if (k == SDLK_UP)
		ptr->up = 1;
	if (k == SDLK_DOWN)
		ptr->down = 1;
	if (k == SDLK_LEFT)
		ptr->left = 1;
	if (k == SDLK_RIGHT)
		ptr->right = 1;
//	if (k == 6)
//		reset(ptr, ptr->map);
	printf("PRESS\n");
	return (1);
}

int		key_release(SDL_Keycode k, void *mlx)
{
	t_mlx *ptr;
	printf("RELEASE\n");
	ptr = (t_mlx *)mlx;
	if (k == SDLK_w)
		ptr->forw = 0;
	if (k == SDLK_s)
		ptr->back = 0;
	if (k == SDLK_d)
		ptr->rside = 0;
	if (k == SDLK_a)
		ptr->lside = 0;
	if (k == SDLK_UP)
		ptr->up = 0;
	if (k == SDLK_DOWN)
		ptr->down = 0;
	if (k == SDLK_LEFT)
		ptr->left = 0;
	if (k == SDLK_RIGHT)
		ptr->right = 0;
	return (1);
}

int		mouse_hook(int x, int y, void *mlx)
{
//	t_mlx *ptr;
//
//	ptr = (t_mlx *)mlx;
//	if (ptr->xy[0] < x && x - ptr->xy[0] > 2)
//		rotate(ptr, ptr->map, 1);
//	if (ptr->xy[0] > x && ptr->xy[0] - x > 2)
//		rotate(ptr, ptr->map, 2);
//	else if (ptr->xy[1] < y && y - ptr->xy[1] > 2)
//		rotate(ptr, ptr->map, 4);
//	else if (ptr->xy[1] > y && ptr->xy[1] - y > 2)
//		rotate(ptr, ptr->map, 3);
//	ptr->init = 0;
//	ptr->xy[0] = x;
//	ptr->xy[1] = y;
	return (0);
}
