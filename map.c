/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:10:55 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/20 18:56:12 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_map	*map_parse(t_list *list)
{
	t_map	*map;
	char	**tab;
	int		x;
	int		y;

	map = (t_map*)malloc(sizeof(t_map));
	if (list && map && !(y = 0))
	{
		map->y = ft_lstlen(list);
		map->wall = (int**)malloc(sizeof(int*) * map->y);
		while (list && (x = -1))
		{
			tab = ft_strsplit(list->content, ' ');
			free(list->content);
			map->x = ft_tablen(tab);
			map->wall[y] = (int*)malloc(sizeof(int) * map->x);
			while (++x < map->x)
			{
				map->wall[y][x] = ft_atoi(tab[x]);
				free(tab[x]);
			}
			list = list->next;
			y++;
		}
	}
	return (map);
}

void	map_print(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			ft_putnbr(map->wall[y][x]);
			ft_putchar(' ');
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}
