/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:19:19 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/17 19:19:21 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_events.h"

/*
** on_quit(): destroy_all_data, exit;
*/

int		ft_on_exit(t_env *e)
{
	e->sdl->event_loop = 0;
	on_sdl_close("wrtc", &e->sdl->window, &e->sdl->renderer,
			&e->sdl->screen, &(e->sound));
	system("leaks wolf");
	return (0);
}
