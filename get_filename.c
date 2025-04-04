/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:03:36 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/28 14:44:40 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	go_open(char *file_name)
{
	int	fd;

	if (ft_strnstr(file_name, ".fdf", ft_strlen(file_name)))
	{
		fd = open(file_name, O_RDONLY);
		if (fd < 0)
			return (-1);
		return (fd);
	}
	return (-1);
}

void	creat_map(int fd, t_data *data)
{
	char	*tmp;
	int		time;

	time = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		parsing(data->list, tmp, time);
		free(tmp);
		time++;
	}
}
