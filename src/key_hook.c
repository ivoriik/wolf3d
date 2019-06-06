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
	else if (sum == SDLK_s)
		e->keys[W_BACK] = true;
	else if (sum == SDLK_d)
		e->keys[W_RSIDE] = true;
	else if (sum == SDLK_a)
		e->keys[W_LSIDE] = true;
	else if (sum == SDLK_UP)
		e->keys[W_UP] = true;
	else if (sum == SDLK_DOWN)
		e->keys[W_DOWN] = true;
	else if (sum == SDLK_LEFT)
		e->keys[W_LEFT] = true;
	else if (sum == SDLK_RIGHT)
		e->keys[W_RIGHT] = true;
	else if (sum == SDLK_r)
		reset(e->map);
	else if (sum == SDLK_EQUALS)
			e->sdl->volume = MINV(e->sdl->volume * VOL_COEF, 128.f);
	else if (sum == SDLK_MINUS)
			e->sdl->volume = MAXV(e->sdl->volume / VOL_COEF, 0.5f);
	Mix_Volume(-1, (int)e->sdl->volume);
	return (1);
}

int			on_key_up(SDL_Keycode sum, t_env *e)
{
	if (sum == SDLK_w)
		e->keys[W_FWRD] = false;
	else if (sum == SDLK_s)
		e->keys[W_BACK] = false;
	else if (sum == SDLK_d)
		e->keys[W_RSIDE] = false;
	else if (sum == SDLK_a)
		e->keys[W_LSIDE] = false;
	else if (sum == SDLK_UP)
		e->keys[W_UP] = false;
	else if (sum == SDLK_DOWN)
		e->keys[W_DOWN] = false;
	else if (sum == SDLK_LEFT)
		e->keys[W_LEFT] = false;
	else if (sum == SDLK_RIGHT)
		e->keys[W_RIGHT] = false;
	return (1);
}
