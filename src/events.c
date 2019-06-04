/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:52:24 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/22 15:56:34 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_events.h"

//t_bool		check_if_holdable(const uint32_t btn_id)
//{
//	return ((btn_id >= SCREENSHOT && btn_id <= CAMERA_MODE) ||
//			btn_id == SKYBOX ||
//			(btn_id >= COLOR && btn_id <= TEX_6) ||
//			(btn_id >= DELETE_OBJ && btn_id <= REACT_NEGATIVE));
//}

//static int	event_handler_buttons(t_mlx *e, SDL_Event *event, uint32_t *btn_id,
//									SDL_bool *mouse_pressed)
//{
//	static t_vector		v = {0, 0, 0, 0};
//
//	if (*mouse_pressed || event->type == SDL_MOUSEBUTTONDOWN)
//	{
//		if (!*mouse_pressed)
//			v = (t_vector){event->button.x, event->button.y, 0, 0};
//		*mouse_pressed = SDL_TRUE;
//		if (event->button.button == SDL_BUTTON_LEFT)
//			return (on_lbutton_down(event->button.x, event->button.y, e));
//		if (event->button.button == SDL_BUTTON_RIGHT)
//			return (on_rbutton_down(event->button.x, event->button.y, e));
//	}
//	else
//		return (0);
//	*btn_id = 0;
//	return (0);
//}

int			event_handler(t_mlx *e, uint32_t *btn_id)
{
	SDL_Event			event;
	static SDL_bool		mouse_pressed = SDL_FALSE;


	if (SDL_PollEvent(&event))
	{
//		if (event.type == SDL_MOUSEBUTTONUP)
//			mouse_pressed = 0;
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
			event.key.keysym.sym == SDLK_ESCAPE))
			(ft_on_exit(e));
		else if (event.type == SDL_KEYDOWN)
			(on_key_down(event.key.keysym.sym, e));
		else if (event.type == SDL_KEYUP)
			(on_key_up(event.key.keysym.sym, e));
		else if (event.type == SDL_WINDOWEVENT &&
				 event.window.event == SDL_WINDOWEVENT_RESIZED)
			(on_resize(event.window.data1, event.window.data2, e));
		else if (event.type == SDL_MOUSEMOTION)
		{
			(on_mmotion(event.motion.x, event.motion.y,
							   event.motion.xrel, event.motion.yrel, e));
		}
//		else
//			return (event_handler_buttons(e, &event, btn_id, &mouse_pressed));
	}
	return (0);
}
