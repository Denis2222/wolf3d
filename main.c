/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:03:39 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/22 16:04:01 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	main(void)
{
	t_map		*map;
	t_list		*list;
	t_player	*player;

	setbuf(stdout, NULL);
	list = read_file("./map/lvl1.w3d");
	map = map_parse(ft_lstrev(list));
	player = newplayer(2, 2);
	setup_mlx(player, map);
	return (0);
}
