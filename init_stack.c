/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:40:45 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/28 15:14:05 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parsing(t_liste **bl, char *str, int time)
{
	char	**splitted;
	int		i;
	t_step	info;
	char	**tempo;

	i = 0;
	tempo = NULL;
	splitted = ft_split(str, ' ');
	while (splitted[i] != NULL)
	{
		tempo = ft_split(splitted[i], ',');
		info.profondeur = ft_atoi(tempo[0]);
		if (tempo[1])
			info.color = ft_atoi_base(tempo[1], "0123456789ABCDEF");
		else
			info.color = 0;
		info.ligne = time;
		info.colonne = i;
		get_free(tempo);
		get_nodded(bl, info);
		i++;
	}
	get_free(splitted);
	splitted = NULL;
}

void	get_nodded(t_liste **bl, t_step info)
{
	t_liste	*tmp;

	if (!(*bl))
	{
		*bl = add_node();
		tmp = *bl;
	}
	else
	{
		tmp = *bl;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = add_node();
		tmp = tmp->next;
	}
	tmp->p = info.profondeur;
	tmp->c = info.colonne;
	tmp->l = info.ligne;
	tmp->color = info.color;
	tmp->next = NULL;
}

void	get_free(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	splitted = NULL;
}

void	free_list(t_liste **bl)
{
	t_liste	*tmp;

	tmp = *bl;
	while (tmp)
	{
		*bl = tmp->next;
		free(tmp);
		tmp = *bl;
	}
	free(bl);
}

t_liste	*add_node(void)
{
	t_liste	*new;

	new = malloc(sizeof(t_liste));
	if (!new)
		return (NULL);
	new->p = 0;
	new->c = 0;
	new->l = 0;
	new->pixx = 0;
	new->pixy = 0;
	new->color = 0;
	new->next = NULL;
	return (new);
}
