/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:47:42 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/27 13:00:18 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_settings(t_data *new)
{
	new->mlx_ptr = mlx_init();
	if (!new->mlx_ptr)
		return ;
	mlx_get_screen_size(new->mlx_ptr, &new->s_x, &new->s_y);
	new->win_ptr = mlx_new_window(new->mlx_ptr, new->s_x,
			new->s_y, "FdF");
	if (!new->win_ptr)
		return ;
	new->st_img.img = mlx_new_image(new->mlx_ptr, new->s_x, new->s_y);
	new->st_img.addr = mlx_get_data_addr(new->st_img.img, &new->st_img.bpp,
			&new->st_img.line_len, &new->st_img.endian);
	convert_point(new);
	mlx_hook(new->win_ptr, 2, 1L << 0, key_press, new);
	mlx_hook(new->win_ptr, 17, 1L << 2, close_cross, new);
	mlx_loop_hook(new->mlx_ptr, render, new);
	mlx_loop(new->mlx_ptr);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x > 1920 || x < 0 || y > 1080 || y < 0)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_img(t_data *img)
{
	img->list = malloc(1 * sizeof(t_liste *));
	if (!img->list)
		exit(EXIT_FAILURE);
	*(img->list) = NULL;
}

void	check(t_data *img)
{
	if (!img->mlx_ptr)
		exit(EXIT_FAILURE);
	if (!img->win_ptr)
	{
		mlx_destroy_display(img->mlx_ptr);
		exit(EXIT_FAILURE);
	}
	return ;
}
