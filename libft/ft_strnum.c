/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:07:34 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/12 09:27:25 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_ll(const char *np, int i, int s, int base)
{
	int	r;

	i--;
	r = 0;
	while (i >= 0)
	{
		r += s * (np[i] - '0');
		s *= base;
		i--;
	}
	return (r);
}

int	ft_atoi(const char *np)
{
	int	s;
	int	i;

	while (ft_isspace(*np))
		np++;
	s = 1;
	if (*np == '-')
		s = -1;
	if (*np == '-' || *np == '+')
		np++;
	i = 0;
	while (ft_isdigit(np[i]))
		i++;
	return (ft_atoi_ll(np, i, s, 10));
}

char	*ft_itoa(int n)
{
	char			buf[20];
	unsigned int	un;
	int				i;

	un = ft_absu(n);
	i = 20 - 1;
	buf[i--] = 0;
	while (un != 0)
	{
		buf[i--] = '0' + un % 10;
		un /= 10;
	}
	if (n == 0)
		buf[i--] = '0';
	else if (n < 0)
		buf[i--] = '-';
	i++;
	return (ft_strdup(buf + i));
}
