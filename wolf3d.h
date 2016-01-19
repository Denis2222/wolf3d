/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:02:25 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/19 22:06:22 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

# define WIDTH 1024
# define HEIGHT 800

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

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
	t_img		*wall;
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

void			setup_mlx(t_player *player, t_map *map);
int				key_hook(int keycode, t_env *e);
int				expose_hook(t_env *e);

t_list			*read_file(char	*filepath);
t_map			*map_parse(t_list	*list);
void			map_print(t_map	*map);

t_player		*newplayer(double x, double y);
t_coord			*newcoord(double x, double y);
void			raycast(t_env *e);

void			draw_dot(t_env *e, int x, int y, int color);

#endif
