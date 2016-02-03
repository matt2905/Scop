/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_material3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 16:59:39 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/03 16:20:34 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

void	ft_get_map_ka(t_data *d, int *i, char **tab)
{
	d->mat[*i].map_ka = ft_strdup(tab[1]);
}

void	ft_get_map_kd(t_data *d, int *i, char **tab)
{
	d->mat[*i].map_kd = ft_strdup(tab[1]);
}

void	ft_get_map_ks(t_data *d, int *i, char **tab)
{
	d->mat[*i].map_ks = ft_strdup(tab[1]);
}

void	ft_get_map_ns(t_data *d, int *i, char **tab)
{
	d->mat[*i].map_ns = ft_strdup(tab[1]);
}

void	ft_get_map_d(t_data *d, int *i, char **tab)
{
	d->mat[*i].map_d = ft_strdup(tab[1]);
}
