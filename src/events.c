/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <vbespalk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:52:24 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/22 15:56:34 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_events.h"

int			event_handler(t_env *e)
{
	SDL_Event			event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
			event.key.keysym.sym == SDLK_ESCAPE))
			e->sdl->event_loop = 0;
		else if (event.type == SDL_KEYDOWN)
			on_key_down(event.key.keysym.sym, e);
		else if (event.type == SDL_KEYUP)
			on_key_up(event.key.keysym.sym, e);
		else
			return (0);
	}
	return (1);
}
