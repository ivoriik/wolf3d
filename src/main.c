/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:31:41 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/10 17:32:12 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "sdl_events.h"

static char *fps_to_str(char **str_fps, int fps)
{
	char *tmp;

	*str_fps = ft_itoa(fps);
	tmp = ft_strjoin("FPS: ", *str_fps);
	free(*str_fps);
	*str_fps = ft_strjoin(tmp, "/60");
	free(tmp);
	return (*str_fps);
}

uint32_t	sdl_draw_screen(t_env *e, t_sdl *sdl, int fps)
{
	ft_memset(sdl->map_pixels, MAZE_WALP, sizeof(Uint32) * MAP_WID * MAP_HEI);
	mult_threads(e);
	draw_map(e, e->map);
	SDL_UpdateTexture(
			sdl->screen, NULL, sdl->pixels, SCR_WID * sizeof(Uint32));
	SDL_UpdateTexture(
			sdl->map, NULL, sdl->map_pixels, MAP_WID * sizeof(Uint32));
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->screen, NULL, NULL);
	SDL_RenderCopy(sdl->renderer, sdl->map, NULL, &sdl->map_rectn);
	if (sdl->text_font && (sdl->text_surf = TTF_RenderText_Solid(sdl->text_font,
			fps_to_str(&sdl->fps, fps), sdl->text_color)))
	{
		sdl->text = SDL_CreateTextureFromSurface(sdl->renderer, sdl->text_surf);
		SDL_RenderCopy(sdl->renderer, sdl->text, NULL, &sdl->text_rectn);
		on_sdl_close("st", &sdl->text_surf, &sdl->text_surf);
		free(sdl->fps);
	}
	SDL_RenderPresent(sdl->renderer);
	return (0);
}

void		main_loop(t_env *e, t_sdl *sdl)
{
	Uint32		time[2];
	Uint32		cntd_frames;
	Uint32		frame_ticks;

	SDL_ShowCursor(SDL_DISABLE);
	sdl_draw_screen(e, e->sdl, 0);
	time[0] = SDL_GetTicks();
	cntd_frames = 0;
	while (sdl->event_loop)
	{
		time[1] = SDL_GetTicks();
		if (!event_handler(e))
			continue ;
		if (move(e, e->map))
			Mix_Playing(-1) == 0 ? Mix_PlayChannel(-1, e->sound, 0) : 1;
		else
			Mix_HaltChannel(-1);
		rotate(e, e->map);
		sdl_draw_screen(e, e->sdl, (int)(cntd_frames /
				((SDL_GetTicks() - time[0]) / 1000.f) + 0.5f));
		frame_ticks = SDL_GetTicks() - time[1];
		if (frame_ticks < SCREEN_FPS)
			SDL_Delay(SCREEN_FPS - frame_ticks);
		++cntd_frames;
	}
}

int			main(int argc, char **argv)
{
	t_env	e;
	t_sdl	sdl;
	t_map	map;
	int		fd;

	if (argc != 2)
		ft_usage("wolf3d map\n");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error(NULL);
	ft_bzero(&map, sizeof(t_map));
	ft_bzero(&sdl, sizeof(t_sdl));
	ft_bzero(&e, sizeof(t_env));
	if (init_map(fd, &map) || sdl_init(&sdl))
		exit(-1);
	e.sdl = &sdl;
	e.map = &map;
	if (!(load_textures(&e)))
		exit(-1);
	load_music(&e);
	main_loop(&e, &sdl);
	ft_on_exit(&e);
	return (0);
}
