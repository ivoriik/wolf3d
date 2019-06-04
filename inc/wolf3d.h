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
#  include "SDL_syswm.h"

/*
**	LINUX
*/

# else

#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>

# endif

//# include "../minilibx/mlx.h"
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <time.h>

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
# define MAP_WID		200.0f
# define MAP_HEI		150.0f
# define FOV			60
# define VW_ANG			0
# define S_CELL			64
# define DIST_PP		1039
# define ANG_INC		0.05f
# define OFSET			32
# define PL_SIZ			8
# define VW_SIZ			24
# define MAZE_WALL		8092539
# define MAZE_POS		10824234
# define MAZE_VIE		16163988
# define TEX_SIZ		15
# define MOVE_SP		6
# define SIDE_SP		4
# define TURN_SP		4
# define LKUP_SP		20
# define KEYPRESS		2
# define KEYRELEASE		3
# define KEYEXIT		17
# define MOUSE			6
# define MOUSEMASK		(1L<<6)
# define KEYPRESSMASK	(1L<<0)
# define KEYRELEASEMASK	(1L<<1)
# define KEYEXITMASK	(1L << 17)
# define NB_THREADS		4
# define IN_RANGE(x, left, right) ((x >= left) && (x <= right))
# define DEG_TO_RAD(x) ((x) * M_PI / 180.0f)
# define RAD_TO_DEG(x) ((x) * 180.0f / M_PI)
# define SCREEN_FPS		60

static const char	*tex_path[TEX_SIZ] = {"textures/stone_n.png",
										"textures/stone_e.png",
										"textures/stone_s.png",
										"textures/stone_w.png",
										"textures/metal_n.png",
										"textures/metal_e.png",
										"textures/metal_s.png",
										"textures/metal_w.png",
										"textures/build_n.png",
										"textures/build_e.png",
										"textures/build_s.png",
										"textures/build_w.png",
										"textures/sky.png",
										"textures/floor.png"};

typedef double		t_vector __attribute__((vector_size(sizeof(double)*2)));

typedef uint8_t	t_byte;

typedef enum	e_bool
{
	false,
	true
}				t_bool;

typedef union	u_color
{
	Uint32			val;
	t_byte			argb[4];
}				t_color;

typedef struct		s_map
{
	unsigned int	hei;
	unsigned int	wid;
	unsigned int	**grid;
	int				pos[2];
	t_vector		pl_mpos[2];
	t_vector		pl_pos;
	t_vector		m_koef;
	double			vw_ang;
	int				pp_cnt;
}					t_map;

typedef struct		s_texture
{
	void			*ptr;
	char			*data;
	int				bpp;
	int				s_line;
	int				endian;
	int				width;
	int				height;
	SDL_Surface		*surface;
}					t_texture;

typedef struct 		s_sdl
{
	int				scr_wid;
	int				scr_hei;
	SDL_Window		*window;
	SDL_Texture		*map;
	SDL_Texture		*screen;
	SDL_Renderer	*renderer;
	Uint32			*pixels;
	SDL_PixelFormat	*format;
	int				pitch;
	int				event_loop;
	SDL_Rect		scr_cont;
	SDL_Rect		map_cont;
	//
	void			*img_ptr;
	char			*img_add;
	void			*map_ptr;
	char			*map_add;
	int				s_line;
	int				maps_line;
}					t_sdl;

typedef struct		s_mlx
{
	t_sdl			*sdl;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_add;
	void			*map_ptr;
	char			*map_add;
	int				bpp;
	int				s_line;
	int				maps_line;
	int				endian;
	int				xy[2];
	t_map			*map;
	int				forw;
	int				back;
	int				up;
	int				down;
	int				left;
	int				right;
	int				lside;
	int				rside;
	int				collision;
//	t_texture		*tex[TEX_SIZ];
	SDL_Surface		*tex[TEX_SIZ];
	int				textured;
	int				init;
}					t_mlx;


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
	int				s_x;
	int				e_x;
	double			ang;
	double			dist;
	double			wall_hei;
	int				tex;
	int				side;
}					t_intersect;

typedef struct		s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_rgb;

typedef	struct		s_thread
{
	int				s_pix;
	int				e_pix;
	t_mlx			*mlx;
}					t_thread;

//typedef struct 		s_time
//{
//	Uint32			stime;
//	Uint32
//};
/*
** PARSE MAP FILE
*/
int					init_map(int fd, t_map *map);
/*
** DRAWING MAP
*/
void				draw_map(t_mlx *mlx, t_map *map);
void				map_rays(t_mlx *mlx, t_map *map, t_intersect *intersect);
/*
** RAYCAST ALGO
*/
void				cast_ray(t_mlx *mlx, t_map *map);
double				find_wall(t_mlx *mlx, t_map *map, t_intersect int_p);
/*
** DRAW
*/
void				skybox(t_mlx *mlx, SDL_Surface *tex);
void				draw_wall(t_mlx *mlx, t_map *map, t_intersect *int_p, \
	SDL_Surface *tex);
void				floor_cast(t_mlx *mlx, t_intersect *int_p, int draw_end, \
	t_vector p);
/*
** MLX / DISPLAY STAFF
*/
int					put_to_window(t_mlx *ptr);
unsigned int		rgb_to_hex(unsigned int red, unsigned int green, \
	unsigned int blue);
t_rgb				hex_to_rgb(unsigned int hex);
//void				img_pixel_put(t_mlx *m, t_vector p, unsigned int col, \
//	int flag);
void				img_pixel_put(t_sdl *sdl, int x, int y, unsigned int color);
unsigned int		img_tex_col(t_mlx *m, SDL_Surface *tex, int x_t, int y_t);
int					exit_x(void *mlx);
int					bresenham(t_mlx *m, t_vector *p0, unsigned int col, int fl);
/*
** KEYS
*/
int					hook_keydown(int k, void *mlx);
int					key_press(int k, void *mlx);
int					key_release(int k, void *mlx);
int					mouse_hook(int x, int y, void *mlx);
int					move(t_mlx *mlx, t_map *map);
int					step(t_map *map, t_vector mov, int flag);
int					rotate(t_mlx *mlx, t_map *map, int flag);
void				reset(t_mlx *mlx, t_map *map);
/*
** TEXTURES
*/
int					load_textures(t_mlx *mlx);
unsigned int		shading(unsigned int col, double dist);
void				free_textures(t_mlx *mlx);
/*
** DIF STAFF
*/
void				is_sound(t_mlx *mlx);
/*
** THREADS
*/
int					mult_threads(t_mlx *mlx);
/*
** FREE MEM
*/
void				del_content(void *content, size_t size);
void				split_del(char ***ptr, void (*f)(void **));
void				clear_mem(char ***mem, int nb);
int					clear_grid(unsigned int ***mem, int nb, char *err);
/*
** SDL INITIALIZING
*/
int					sdl_init(t_sdl *sdl);
int					sdl_error(char *message);
int					sdl_img_error(char *message);
void				on_sdl_close(char *fmt, ...);
int					get_format_data(t_sdl *sdl);
void				cleanup_sdl_texture(SDL_Texture **tex);
void				cleanup_sdl_surface(SDL_Surface **surf);
/*
** EVENTS
*/
int					event_handler(t_mlx *e, uint32_t *btn_id);
#endif
