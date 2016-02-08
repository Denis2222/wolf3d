/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 13:56:29 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/22 15:40:09 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_sprites(t_env *e)
{
	e->sprite[0] = (t_sprite){3.5, 3.5, 0};
	e->sprite[1] = (t_sprite){6.5, 12.5, 1};
	e->sprite[2] = (t_sprite){4.3, 8.3, 1};
	e->sprite[3] = (t_sprite){2.5, 2.5, 1};
	e->sprite[4] = (t_sprite){4.5, 9.5, 1};
	e->sprite[5] = (t_sprite){4.5, 6.5, 1};
	e->sprite[6] = (t_sprite){3.5, 6.5, 1};
	e->sprite[7] = (t_sprite){29.5, 5, 1};
	e->sprite[8] = (t_sprite){30.5, 1.5, 0};
	e->sprite[9] = (t_sprite){22.5, 1.5, 0};
	e->sprite[10] = (t_sprite){22.5, 17.5, 0};
	e->sprite[11] = (t_sprite){30.5, 17.5, 0};
	e->sprite[12] = (t_sprite){8.5, 6.5, 2};
}
