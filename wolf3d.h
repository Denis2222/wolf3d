/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:02:25 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/21 01:35:02 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

# define WIDTH 1024
# define HEIGHT 840

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define MOVESPEED 0.1
# define ROTSPEED 0.1

# define CR cos(ROTSPEED)
# define SR sin(ROTSPEED)
# define C_R cos(-ROTSPEED)
# define S_R sin(-ROTSPEED)

typedef struct	s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct	s_map
{
	int			**wall;
	int			x;
	int			y;
}				t_map;

typedef struct	s_player
{
	t_coord		*pos;
	t_coord		*dir;
	t_coord		*plane;
}				t_player;

typedef struct	s_img
{
	int			width;
	int			height;
	char		*buffer;
}				t_img;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*imgpx;
	int			bpp;
	int			size_line;
	int			endian;
	t_map		*map;
	t_player	*player;
	t_img		*wall[8];
}				t_env;

typedef struct	s_raycast
{
	double		camerax;
	double		rayposx;
	double		rayposy;
	double		raydirx;
	double		raydiry;
	double		mapx;
	double		mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		stepx;
	double		stepy;
	double		perpwalldist;
	int			hit;
	int			side;
}				t_raycast;

typedef struct	s_ray
{
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			x;
	int			y;
	double		wallx;
	int			texx;
	int			texy;

	double		floorxwall;
	double		floorywall;
	double		distwall;
	double		distplayer;
	double		currentdist;
	double		weight;

	double		currentfloorx;
	double		currentfloory;

	int			floortexx;
	int			floortexy;
}				t_ray;

typedef struct	s_keyboard
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			sleft;
	int			sright;
}				t_keyboard;

void			setup_mlx(t_player *player, t_map *map);
int				key_press_hook(int keycode, t_env *e);
int				key_release_hook(int keycode, t_env *e);

int				expose_hook(t_env *e);

t_list			*read_file(char	*filepath);
t_map			*map_parse(t_list	*list);
void			map_print(t_map	*map);

t_player		*newplayer(double x, double y);
t_coord			*newcoord(double x, double y);
void			raycast(t_env *e);

void			draw_dot(t_env *e, int x, int y, int color);
int				rgb2i(int r, int g, int b);
int				getcolor(t_img *img, int x, int y, int fade);
void			drawbyside(t_env *e, t_raycast *rc, int x, int y);

void			texture_load(t_env *e);

#endif
