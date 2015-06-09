/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 17:52:40 by mmartin           #+#    #+#             */
/*   Updated: 2015/05/25 18:55:16 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_separe_value(double value, double *partint, t_modf *fp, int mask)
{
	double			tmp;
	unsigned long	mant;

	tmp = value;
	if (mask >= 32)
	{
		fp->part_frac = 0;
		mask -= 32;
		mant = (fp->part_int >> 0) & 0xfffff;
		mant &= ~((1 << mask) - 1);
		fp->part_int = (fp->part_int & ~(0xfffff << 0))
			| ((mant & 0xfffff) << 0);
	}
	else
	{
		mant = fp->part_frac;
		mant &= ~((1 << mask) - 1);
		fp->part_frac = mant;
	}
	value = *(double *)fp;
	*partint = value;
	return (tmp - value);
}

double		ft_modf(double value, double *part_int)
{
	t_modf	*fp;
	int		exp;
	int		mask;

	fp = (t_modf *)&value;
	exp = (fp->part_int >> 20) & 0x7ff;
	exp -= 1023;
	if (exp < 0)
	{
		*part_int = 0;
		return (value);
	}
	mask = 52 - exp;
	if (mask <= 0)
	{
		*part_int = value;
		return (0);
	}
	return (ft_separe_value(value, part_int, fp, mask));
}
