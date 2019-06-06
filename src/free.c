/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:16:33 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/29 14:16:35 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		del_content(void *content, size_t size)
{
	if (size && content)
		ft_memdel(&content);
}

void		clear_mem(char ***mem, int nb)
{
	while (--nb >= 0)
		ft_memdel((void **)&(*mem)[nb]);
	ft_memdel((void **)(mem));
}

void		split_del(char ***ptr, void (*f)(void **))
{
	char **s;

	s = *ptr;
	if (s == NULL || f == NULL)
		return ;
	while (*s)
		f((void **)s++);
	f((void **)ptr);
}

int			clear_grid(unsigned int ***mem, size_t nb, char *err)
{
	size_t i;

	i = 0;
	while (i < nb && (*mem)[i])
		ft_memdel((void **)&(*mem)[i++]);
	ft_memdel((void **)(mem));
	if (err != NULL)
		return (ft_perror(err));
	return (0);
}

int			ft_on_exit(t_env *e)
{
	on_sdl_close("wrtcf", &e->sdl->window, &e->sdl->renderer,
				 &e->sdl->screen, &(e->sound), &(e->sdl->text_font));
	free_textures(e);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return (0);
}