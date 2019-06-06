/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:45:21 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/27 13:45:22 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	thread_funct(void *ptr)
{
	t_thread		*th;
	int				i;
	t_intersect		int_p;

	th = (t_thread *)ptr;
	i = th->pix;
	while (i < SCR_WID)
	{
		int_p.s_x = i;
		int_p.ang = DEG_TO_RAD(th->e->map->vw_ang - FOV)
			+ i * DEG_TO_RAD(ANG_INC);
		if (int_p.ang >= DEG_TO_RAD(360))
			int_p.ang -= DEG_TO_RAD(360);
		else if (int_p.ang < DEG_TO_RAD(0))
			int_p.ang += DEG_TO_RAD(360);
		skybox(th->e, th->e->tex[12], i);
		find_wall(th->e, th->e->map, int_p);
		int_p.ang += DEG_TO_RAD(ANG_INC);
		i += NB_THREADS;
	}
	return (0);
}

int		mult_threads(t_env *e)
{
	int			count;
	SDL_Thread	*threads_id[NB_THREADS];
	int			threadReturnValue;
	t_thread	th[NB_THREADS];

	count = -1;
	while (++count < NB_THREADS)
	{
		th[count].pix = count;
		th[count].e = e;
		if (!(threads_id[count] = SDL_CreateThread(thread_funct,
				NULL, &th[count])))
			ft_error(SDL_GetError());
	}
	count = -1;
	threadReturnValue = 0;
	while (++count < NB_THREADS)
	{
		SDL_WaitThread(threads_id[count], &threadReturnValue);
			if (threadReturnValue)
				ft_error(SDL_GetError());
	}
	return (0);
}
