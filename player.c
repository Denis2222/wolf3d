/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 18:02:08 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/20 18:30:34 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		d2r(double d)
{
	return (M_PI * d / 180);
}

void		fixproplane(t_player *p, double fov)
{
	double	fx;
	double	fy;
	double	px;
	double	py;

	fx = p->dir->x;
	fy = p->dir->y;
	px = (int)(fx * cos(d2r(90)) - fy * sin(d2r(90)));
	py = (int)(fx * sin(d2r(90)) + fy * cos(d2r(90)));
	p->plane = newcoord(fov * px, fov * py);
}

t_player	*newplayer(double x, double y)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->pos = newcoord(x, y);
	player->dir = newcoord(0, 1);
	fixproplane(player, 0.66);
	return (player);
}
