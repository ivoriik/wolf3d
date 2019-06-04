/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_ev.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 21:53:36 by vbespalk          #+#    #+#             */
/*   Updated: 2019/01/28 21:53:41 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_SDL_EV_H
# define WOLF_SDL_EV_H

# include "wolf3d.h"

int	on_key_down(SDL_Keycode sum, t_mlx *e);
int	on_key_up(SDL_Keycode sum, t_mlx *e);
int	on_lbutton_down(int x, int y, t_mlx *e);
int	on_rbutton_down(int x, int y, t_mlx *e);
int	on_resize(Sint32 w, Sint32 h, t_mlx *e);
int	ft_on_exit(t_mlx *e);
int	on_mouse_wheel(Sint32 y, Uint32 dir, t_mlx *e);
int	on_mmotion(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel, t_mlx *e);

#endif
