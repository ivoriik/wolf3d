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

void	*thread_funct(void *ptr)
{
	t_thread		*th;
	int				i;
	double			dist;
	t_intersect		int_p;

	th = (t_thread *)ptr;
	i = th->s_pix;
	int_p.ang = DEG_TO_RAD(th->mlx->map->vw_ang - FOV / 2.0f) \
	+ i * DEG_TO_RAD(ANG_INC);
	int_p.e_x = th->e_pix;
	while (i < th->e_pix)
	{
		int_p.s_x = i;
		if (int_p.ang >= DEG_TO_RAD(360))
			int_p.ang -= (double)DEG_TO_RAD(360);
		if (int_p.ang < DEG_TO_RAD(0))
			int_p.ang += (double)DEG_TO_RAD(360);
		dist = find_wall(th->mlx, th->mlx->map, int_p);
		int_p.ang += DEG_TO_RAD(ANG_INC);
		i++;
	}
	return (NULL);
}

int		mult_threads(t_mlx *mlx)
{
	int			count;
	pthread_t	threads_id[NB_THREADS];
	t_thread	th[NB_THREADS];

	count = -1;
	while (++count < NB_THREADS)
		th[count].mlx = mlx;
	count = -1;
	while (++count < NB_THREADS)
	{
		th[count].s_pix = count * (int)((float)mlx->sdl->scr_wid / NB_THREADS + 0.5f);
		th[count].e_pix = th[count].s_pix + (int)((float)mlx->sdl->scr_wid / NB_THREADS + 0.5f);
		if (pthread_create((&(threads_id[count])), NULL, \
			thread_funct, &th[count]))
			ft_error("error creating thread\n");
	}
	count = -1;
	while (++count < NB_THREADS)
		if (pthread_join(threads_id[count], NULL))
			ft_error("error joining thread\n");
	return (0);
}
