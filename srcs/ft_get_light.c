/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 18:57:13 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/09 12:22:04 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

void	ft_get_light_calc(t_data *d, int *i, char **tab)
{
	int		j;

	j = ft_atoi(tab[1]);
	j++;
	d->mat[*i].illum = NULL;
}
