/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <vbespalk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:35:53 by vbespalk          #+#    #+#             */
/*   Updated: 2019/04/27 16:29:19 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_events.h"

int			on_key_down(SDL_Keycode sum, t_env *e)
{
	if (sum == SDLK_w)
		e->keys[W_FWRD] = true;
	if (sum == SDLK_s)
		e->keys[W_BACK] = true;
	if (sum == SDLK_d)
		e->keys[W_RSIDE] = true;
	if (sum == SDLK_a)
		e->keys[W_LSIDE] = true;
	if (sum == SDLK_UP)
		e->keys[W_UP] = true;
	if (sum == SDLK_DOWN)
		e->keys[W_DOWN] = true;
	if (sum == SDLK_LEFT)
		e->keys[W_LEFT] = true;
	if (sum == SDLK_RIGHT)
		e->keys[W_RIGHT] = true;
	if (sum == SDLK_r)
		reset(e->map);
	return (1);
}

int			on_key_up(SDL_Keycode sum, t_env *e)
{
	if (sum == SDLK_w)
		e->keys[W_FWRD] = false;
	if (sum == SDLK_s)
		e->keys[W_BACK] = false;
	if (sum == SDLK_d)
		e->keys[W_RSIDE] = false;
	if (sum == SDLK_a)
		e->keys[W_LSIDE] = false;
	if (sum == SDLK_UP)
		e->keys[W_UP] = false;
	if (sum == SDLK_DOWN)
		e->keys[W_DOWN] = false;
	if (sum == SDLK_LEFT)
		e->keys[W_LEFT] = false;
	if (sum == SDLK_RIGHT)
		e->keys[W_RIGHT] = false;
	return (1);
}
