/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 20:00:50 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/22 15:55:17 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	texture_sprite_load(t_env *e)
{
	int	width;
	int	height;

	e->spr[0] = mlx_xpm_file_to_image(e->mlx,
			"gfx/sprite1.xpm", &width, &height);
	e->spr[1] = mlx_xpm_file_to_image(e->mlx,
			"gfx/barrel.xpm", &width, &height);
	e->spr[2] = mlx_xpm_file_to_image(e->mlx,
			"gfx/lustre.xpm", &width, &height);
	e->spr[3] = mlx_xpm_file_to_image(e->mlx,
			"gfx/guns.xpm", &width, &height);
	e->hud[0] = (t_hud){WIDTH / 2 - width / 6,
		HEIGHT - height, width / 3, height, 3, 0, 3};
}

void	texture_load(t_env *e)
{
	int		width;
	int		height;

	e->wall[0] = mlx_xpm_file_to_image(e->mlx,
			"gfx/floor.xpm", &width, &height);
	e->wall[1] = mlx_xpm_file_to_image(e->mlx,
			"gfx/ceil.xpm", &width, &height);
	e->wall[2] = mlx_xpm_file_to_image(e->mlx,
			"gfx/blue_brick.xpm", &width, &height);
	e->wall[3] = mlx_xpm_file_to_image(e->mlx,
			"gfx/blue_brick2.xpm", &width, &height);
	e->wall[4] = mlx_xpm_file_to_image(e->mlx,
			"gfx/blue_brick3.xpm", &width, &height);
	e->wall[5] = mlx_xpm_file_to_image(e->mlx,
			"gfx/blue_brick_hi.xpm", &width, &height);
	e->wall[6] = mlx_xpm_file_to_image(e->mlx,
			"gfx/wall_brown.xpm", &width, &height);
	e->wall[7] = mlx_xpm_file_to_image(e->mlx,
			"gfx/wall_red1.xpm", &width, &height);
	e->wall[8] = mlx_xpm_file_to_image(e->mlx,
			"gfx/wall_red2.xpm", &width, &height);
	e->wall[9] = mlx_xpm_file_to_image(e->mlx,
			"gfx/wall_red_door.xpm", &width, &height);
	texture_sprite_load(e);
}
