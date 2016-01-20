/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 23:23:52 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/18 23:27:20 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		rgb2i(int r, int g, int b)
{
	int	color;

	color = 256 * 256 * r;
	color += 256 * g;
	color += b;
	return (color);
}

void	draw_dot(t_env *e, int x, int y, int color)
{
	char	b;
	char	g;
	char	r;
	int		i;

	b = color % 256;
	g = (color / 256) % 256;
	r = (color / 256 / 256) % 256;
	i = (e->size_line * y) + (x * (e->bpp / 8));
	e->imgpx[i] = b;
	e->imgpx[i + 1] = g;
	e->imgpx[i + 2] = r;
}

int		getcolor(t_img *img, int x, int y, int fade)
{
	int	color;
	int	c;

	fade /= 8;
	c = (y * img->width + x) * 4;
	color = img->buffer[c];
	color += img->buffer[c + 1] * 256;
	color += img->buffer[c + 2] * 256 * 256;
	while (fade--)
		color = ((color >> 1) & 8355711);
	return (color);
}
