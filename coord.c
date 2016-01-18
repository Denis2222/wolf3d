/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 18:08:42 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/18 18:43:18 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_coord	*newcoord(double x, double y)
{
	t_coord *coord;

	coord = malloc(sizeof(t_coord));
	coord->x = x;
	coord->y = y;
	return (coord);
}
