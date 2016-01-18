/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:05:36 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/18 17:21:58 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_list	*read_file(char *filepath)
{
	t_list	*list;
	t_list	*l;
	char	*line;
	int		fd;

	list = NULL;
	if ((fd = open(filepath, O_RDONLY)))
	{
		while (get_next_line(fd, &line) > 0)
		{
			l = ft_lstnew(line, sizeof(char) * ft_strlen(line) + 1);
			ft_lstadd(&list, l);
			free(line);
		}
		if (list)
			return (list);
	}
	ft_putstr("no map or not readable");
	exit(EXIT_FAILURE);
}
