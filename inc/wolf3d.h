/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:27:21 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/10 17:29:48 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

/*
**	MACOSX
*/

# if defined(__MACH__) && defined(__APPLE__)

#  include "SDL.h"
#  include "SDL_image.h"
#  include "SDL_mixer.h"
#  include "SDL_ttf.h"

/*
**	LINUX
*/

# else

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_mixer.h>
# include <SDL2/SDL_ttf.h>

# endif

# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <stdarg.h>

# if SDL_BYTEORDER == SDL_BIG_ENDIAN

#  define RMASK			0xff000000U
#  define GMASK			0x00ff0000U
#  define BMASK			0x0000ff00U
#  define AMASK			0x000000ffU
#  define SWAP32(X)		(X)

# else

#  define RMASK			0x000000ffU
#  define GMASK			0x0000ff00U
#  define BMASK			0x00ff0000U
#  define AMASK			0xff000000U
#  define SWAP32(X)		SDL_Swap32(X)

# endif

# define ON_ERR 		"Fatal error at "
# define ON_WARN 		"Warning at "

# define SCR_WID		1200
# define SCR_HEI		800
# define MAP_WID		200
# define MAP_HEI		150
# define FPS_WID		150
# define FPS_HEI		28
# define FPS_X			SCR_WID - FPS_WID - 10
# define FPS_Y			5
# define FOV			30
# define VW_ANG			0
# define S_CELL			64
# define DIST_PP		1038
# define ANG_INC		0.05f
# define OFSET			32
# define PL_SIZ			8
# define VW_SIZ			24
# define MAZE_WALL		SWAP32(0x7B7B7B00)
# define MAZE_WALP		SWAP32(0x47474700)
# define MAZE_POS		SWAP32(0xA52A2A00)
# define MAZE_VIE		SWAP32(0xF6A49400)
# define TEX_SIZ		15
# define MOVE_SP		4
# define SIDE_SP		2
# define TURN_SP		2
# define LKUP_SP		15
# define NB_THREADS		8
# define IN_RANGE(x, left, right) ((x >= left) && (x <= right))
# define DEG_TO_RAD(x) ((x) * M_PI / 180.0f)
# define RAD_TO_DEG(x) ((x) * 180.0f / M_PI)
# define SCREEN_FPS		16
# define SOUND			"media/sideshoe.wav"
# define FPS_FONT		"media/fonts/suissnord/suissnord.otf"
enum {
						W_FWRD = 0,
						W_BACK,
						W_LSIDE,
						W_RSIDE,
						W_UP,
						W_DOWN,
						W_LEFT,
						W_RIGHT,
						W_RESET,
						W_KEYS
};

typedef double		t_vector __attribute__((vector_size(sizeof(double)*2)));
typedef int			t_ivec __attribute__((vector_size(sizeof(int)*2)));

typedef uint8_t		t_byte;

typedef enum		e_bool
{
	false,
	true
}					t_bool;

typedef union		u_color
{
	Uint32			val;
	t_byte			argb[4];
}					t_color;

typedef struct		s_map
{
	t_vector		pl_mpos[2];
	t_vector		pl_pos;
	t_vector		m_koef;
	double			vw_ang;
	size_t			hei;
	size_t			wid;
	int				pp_cnt;
	int				pos[2];
	unsigned int	**grid;
}					t_map;

typedef struct 		s_sdl
{
	SDL_Rect		map_rectn;
	SDL_Rect		text_rectn;
	SDL_Color		text_color;
	int				event_loop;
	SDL_Window		*window;
	SDL_Texture		*map;
	SDL_Texture		*screen;
	SDL_Texture		*text;
	SDL_Surface		*text_surf;
	TTF_Font		*text_font;
	char 			*fps;
	SDL_Renderer	*renderer;
	Uint32			*pixels;
	Uint32			*map_pixels;
	SDL_PixelFormat	*format;
}					t_sdl;

typedef struct		s_env
{
	t_bool			keys[W_KEYS];
	SDL_Surface		*tex[TEX_SIZ];
	Mix_Chunk		*sound;
	t_sdl			*sdl;
	t_map			*map;
}					t_env;


typedef struct		s_bresenham
{
	t_vector		p0;
	t_vector		p;
	t_vector		dl;
	double			error;
}					t_bresenham;

typedef struct		s_intersect
{
	t_vector		int_pos;
	t_vector		pl_mpos[2];
	double			ang;
	double			dist;
	double			wall_hei;
	int				s_x;
	int				tex;
	int				side;
}					t_intersect;

typedef	struct		s_thread
{
	t_env			*e;
	int				pix;
}					t_thread;

/*
** PARSE MAP FILE
*/
int					init_map(int fd, t_map *map);
/*
** DRAWING MAP
*/
void				draw_map(t_env *e, t_map *map);
void				map_rays(t_env *e, t_map *map, t_intersect *intersect);
/*
** RAYCAST ALGO
*/
double				find_wall(t_env *e, t_map *map, t_intersect int_p);
/*
** DRAW
*/
void				skybox(t_env *e, SDL_Surface *tex, int x);
void				draw_wall(t_env *e, t_map *map, t_intersect *int_p, \
	SDL_Surface *tex);
void				floor_cast(t_env *e, t_intersect *int_p, int draw_end, \
	t_vector p);
/*
** DISPLAY STAFF
*/
void				img_pixel_put(Uint32 *pixels, t_ivec pnt,
								  t_ivec max_pnt, unsigned int color);
unsigned int		img_tex_col(SDL_Surface *tex, int x_tex, int y_tex);
int					bresenham(t_env *m, t_vector *p0, unsigned int col);
/*
** KEYS
*/
int					move(t_env *e, t_map *map);
int					step(t_map *map, t_vector mov, int flag);
int					rotate(t_env *e, t_map *map);
void				reset(t_map *map);
/*
** TEXTURES
*/
int					load_textures(t_env *e);
unsigned int		shading(unsigned int col, double dist);
void				free_textures(t_env *e);
/*
** THREADS
*/
int					mult_threads(t_env *e);
/*
** FREE MEM
*/
void				del_content(void *content, size_t size);
void				clear_mem(char ***mem, int nb);
int					clear_grid(unsigned int ***mem, size_t nb, char *err);
/*
** SDL INITIALIZING
*/
int					sdl_init(t_sdl *sdl);
int					sdl_error(char *message, const char(*sdl_error()));
int					sdl_img_error(char *message);
void				on_sdl_close(char *fmt, ...);
int					get_format_data(t_sdl *sdl);
void				cleanup_sdl_texture(SDL_Texture **tex);
void				cleanup_sdl_surface(SDL_Surface **surf);
uint32_t			sdl_draw_screen(t_env *e, t_sdl *sdl, int fps);
int					load_music(t_env *e);
void				main_loop(t_env *e, t_sdl *sdl);
/*
** EVENTS
*/
int					event_handler(t_env *e);
#endif
