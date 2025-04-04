/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:40:31 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/27 20:12:37 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include <math.h>

//x && y point de commencement, width et height hauteur et largeur

typedef struct s_vec3
{
	double	a;
	double	b;
	double	c;
}				t_vec3;

typedef struct s_line
{
	double	deltax;
	double	deltay;
	double	pixx;
	double	pixy;
	int		pixels;
}				t_line;

typedef struct s_step
{
	int	profondeur;
	int	colonne;
	int	ligne;
	int	color;
}			t_step;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;

}			t_img;

typedef struct s_listing
{
	int					p;
	int					c;
	int					l;
	double				pixx;
	double				pixy;
	int					color;
	struct s_listing	*next;
}			t_liste;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			s_x;
	int			s_y;
	t_liste		**list;
	t_img		st_img;
}			t_data;

//color
int		create_trgb(int t, int r, int g, int b);

//main 
void	convert_point(t_data *data);
int		render(t_data *data);
void	draw_line(t_data *data, t_liste p1, t_liste p2);
int		get_color(int profondeur);
void	help_draw_line(t_data *data, t_liste p1, t_liste p2, t_line l);
//window
void	init_settings(t_data *new);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	init_img(t_data *img);
void	check(t_data *img);

//init_stack
void	parsing(t_liste **bl, char *str, int time);
void	get_free(char **splitted);
void	get_nodded(t_liste **bl, t_step info);
t_liste	*add_node(void);
void	free_list(t_liste **bl);

//function
int		key_press(int keycode, t_data *param);
int		close_cross(t_data *param);

//get_filename
int		go_open(char *file_name);
void	creat_map(int fd, t_data *data);

#endif
