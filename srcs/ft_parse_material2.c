/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_material2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 18:54:03 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/09 12:22:28 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

void	ft_get_density(t_data *d, int *i, char **tab)
{
	d->mat[*i].ni = ft_atof(tab[1]);
}

void	ft_get_transparency(t_data *d, int *i, char **tab)
{
	d->mat[*i].d = ft_atof(tab[1]);
}
