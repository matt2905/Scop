/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 17:35:06 by mmartin           #+#    #+#             */
/*   Updated: 2015/05/25 20:33:24 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_get_float(char *str, double f, float precision)
{
	int		k;
	int		len;
	double	save;
	double	tmp;

	k = 0;
	save = f;
	while (save > precision)
	{
		save /= 10;
		k++;
	}
	len = --k;
	while (k > 0)
	{
		f = ft_modf(f * 10, &tmp);
		*(str - k) = (int)tmp % 10 + '0';
		k--;
	}
	return (len);
}

static void		ft_convert(double n, char *str, int len, float precision)
{
	double	f;
	double	i;
	int		k;

	k = 0;
	str += len;
	f = ft_modf(n, &i);
	k = ft_get_float(str, f, precision);
	str = str - k - 1;
	*str = '.';
	str--;
	while (i > 0)
	{
		*str = (int)i % 10 + '0';
		i /= 10;
		str--;
	}
}

static int		ft_len(double n, float precision)
{
	int		j;
	double	f;
	double	tmp;
	double	i;

	f = ft_modf(n, &i);
	tmp = f;
	j = 1;
	while (i >= 10)
	{
		i /= 10;
		j++;
	}
	while (tmp > precision)
	{
		f = ft_modf(f * 10, &i);
		tmp /= 10;
		j++;
	}
	return (j);
}

char			*ft_ftoa(double n, float precision)
{
	char	*str;
	int		sign;
	size_t	len;

	sign = 0;
	len = 0;
	if (n < 0)
	{
		n *= -1;
		sign = 1;
		len++;
	}
	len += ft_len(n, precision);
	str = ft_strnew(len + 1);
	ft_convert(n, str, len, precision);
	if (sign)
		str[0] = '-';
	return (str);
}
