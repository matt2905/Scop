/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_material.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 18:45:52 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/09 12:40:11 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

void	ft_new_material(t_data *d, int *i, char **tab)
{
	t_mat	*save;

	*i += 1;
	d->nb_mat++;
	save = (t_mat *)ft_memalloc(sizeof(*save) * (d->nb_mat + 1));
	if (d->mat)
	{
		ft_memcpy(save, d->mat, sizeof(*d->mat) * *i);
		ft_memdel((void **)&d->mat);
	}
	save[*i].name = ft_strdup(tab[1]);
	d->mat = save;
}

void	ft_get_specular_exp(t_data *d, int *i, char **tab)
{
	d->mat[*i].ns = ft_atof(tab[1]);
}

void	ft_get_ambient(t_data *d, int *i, char **tab)
{
	t_color		ka;

	ka.r = ft_atof(tab[1]);
	ka.g = ft_atof(tab[2]);
	ka.b = ft_atof(tab[3]);
	d->mat[*i].ka = ka;
}

void	ft_get_diffuse(t_data *d, int *i, char **tab)
{
	t_color		kd;

	kd.r = ft_atof(tab[1]);
	kd.g = ft_atof(tab[2]);
	kd.b = ft_atof(tab[3]);
	d->mat[*i].kd = kd;
}

void	ft_get_specular(t_data *d, int *i, char **tab)
{
	t_color		ks;

	ks.r = ft_atof(tab[1]);
	ks.g = ft_atof(tab[2]);
	ks.b = ft_atof(tab[3]);
	d->mat[*i].ks = ks;
}
