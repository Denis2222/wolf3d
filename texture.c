/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 20:00:50 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/20 21:07:51 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	texture_load(t_env *e)
{
	int		width;
	int		height;

	e->wall[0] = mlx_xpm_file_to_image(e->mlx,"gfx/wall_brown.xpm", &width, &height);
	e->wall[1] = mlx_xpm_file_to_image(e->mlx,"gfx/blue_brick.xpm", &width, &height);
	e->wall[2] = mlx_xpm_file_to_image(e->mlx,"gfx/blue_brick2.xpm", &width, &height);
	e->wall[3] = mlx_xpm_file_to_image(e->mlx,"gfx/blue_brick3.xpm", &width, &height);
	e->wall[4] = mlx_xpm_file_to_image(e->mlx,"gfx/blue_brick_hi.xpm", &width, &height);
}
