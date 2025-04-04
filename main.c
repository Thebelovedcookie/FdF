/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:40:51 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/28 16:38:49 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *data, t_liste p1, t_liste p2)
{
	t_line	l;

	if (p1.pixx == p2.pixx && p1.pixy == p2.pixy)
		return ;
	l.deltax = p2.pixx - p1.pixx;
	l.deltay = p2.pixy - p1.pixy;
	l.pixels = sqrt((l.deltax * l.deltax) + (l.deltay * l.deltay));
	l.deltax /= l.pixels;
	l.deltay /= l.pixels;
	l.pixx = (double) p1.pixx + (data->s_x / 2);
	l.pixy = (double) p1.pixy;
	help_draw_line(data, p1, p2, l);
}

void	help_draw_line(t_data *data, t_liste p1, t_liste p2, t_line l)
{
	int	pix;

	pix = l.pixels;
	while (l.pixels)
	{
		if (p1.p > p2.p)
		{
			p2.color -= (p2.color - p1.color) / pix;
			my_mlx_pixel_put(&data->st_img, l.pixx, l.pixy, p2.color);
		}
		else
		{
			p1.color -= (p1.color - p2.color) / pix;
			my_mlx_pixel_put(&data->st_img, l.pixx, l.pixy, p1.color);
		}
		l.pixx += l.deltax;
		l.pixy += l.deltay;
		--l.pixels;
	}
}

int	render(t_data *data)
{
	t_liste	*current;
	t_liste	*prec;

	prec = *(data->list);
	current = prec->next;
	while (current)
	{
		if (prec->l == current->l)
			draw_line(data, *prec, *current);
		current = current->next;
		prec = prec->next;
	}
	prec = *(data->list);
	current = prec->next;
	while (current)
	{
		while (current->l == prec->l)
			current = current->next;
		draw_line(data, *prec, *current);
		current = current->next;
		prec = prec->next;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->st_img.img, 0, 0);
	return (0);
}

/*	converti les coordonnées du schema en coordonnées de pixel 
	en utilisant la formule : Px * vecteur(a,b) + Py * vecteur(-a,b), 
	a partir de ce point on trouve les 3 prochain de la tuile*/	
void	convert_point(t_data *data)
{
	t_liste	*f;
	t_vec3	t;

	t.a = 100.;
	f = *(data->list);
	while (f)
	{
		t.b = t.a * 0.8;
		t.c = t.b * 0.18;
		while (f)
		{
			f->pixx = (f->c * t.a) + (f->l * (-t.a));
			f->pixy = (f->c * t.b) + (f->l * (t.b)) - (f->p * t.c);
			if (t.a > 2 && (f->pixx > data->s_x / 2 || f->pixx < -data->s_x / 2
					|| f->pixy > (data->s_y - 50) || f->pixy < (-50)))
				break ;
			if (f->color == 0)
				f->color = create_trgb(0, 255, 255, 255) - (62280 * f->p / 10);
			f = f->next;
			if (!f)
				return ;
		}
		t.a -= 0.6;
		f = *(data->list);
	}
}

int	main(int argc, char **argv)
{
	t_data	img;
	int		fd;

	if (argc == 2)
	{
		fd = go_open(argv[1]);
		if (fd == -1)
		{
			ft_printf("permission denied\n");
			exit(EXIT_FAILURE);
		}
		init_img(&img);
		creat_map(fd, &img);
		init_settings(&img);
		check(&img);
	}
	else
		ft_printf("No enough argument");
	return (0);
}
