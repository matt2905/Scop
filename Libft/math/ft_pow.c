/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/01 19:07:37 by mmartin           #+#    #+#             */
/*   Updated: 2015/04/05 12:36:25 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		ft_pow(double base, int exp)
{
	int		flag;
	double	result;

	flag = 0;
	result = 1;
	if (exp < 0)
	{
		exp *= -1;
		flag = 1;
	}
	while (exp)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		base *= base;
	}
	return ((flag ? 1 / result : result));
}
