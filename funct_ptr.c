/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:40:36 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/25 20:39:58 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, t_data *param)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(param->mlx_ptr, param->st_img.img);
		mlx_destroy_window(param->mlx_ptr, param->win_ptr);
		mlx_destroy_display(param->mlx_ptr);
		free(param->mlx_ptr);
		free_list(param->list);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	close_cross(t_data *param)
{
	mlx_destroy_image(param->mlx_ptr, param->st_img.img);
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	mlx_destroy_display(param->mlx_ptr);
	free(param->mlx_ptr);
	free_list(param->list);
	exit(EXIT_SUCCESS);
}
