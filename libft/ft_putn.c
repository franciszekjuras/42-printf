/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:44:58 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/12 14:56:33 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putcharn_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstrn_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	return (write(fd, s, len));
}

int	ft_putendln_fd(char *s, int fd)
{
	int r1;
	int r2;

	r1 = ft_putstrn_fd(s, fd);
	r2 = write(fd, "\n", 1);
	if (r1 < 0 || r2 < 0)
		return (-1);
	return (r1 + r2);
}

int	ft_putnbrn_fd(int n, int fd)
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
	return (ft_putstrn_fd(buf + i, fd));
}
