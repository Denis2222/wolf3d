/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 18:02:08 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/19 18:42:50 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_player *newplayer(double x, double y)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->pos = newcoord(x, y);
	player->dir = newcoord(1, 0);
	player->plane = newcoord(0, 0.66);
	return (player);
}
