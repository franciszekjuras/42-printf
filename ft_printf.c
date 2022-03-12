/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 09:58:09 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/12 20:31:27 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "ft_printf_utils.h"

static ssize_t wcheck(ssize_t write_ret, int *err)
{
	if (write_ret < 0)
		*err = -1;
	return (write_ret);
}

int	ft_fprintf(int fd, const char *fstr)
{
	const char		*pos;
	const char		*passed;
	ssize_t			count;
	int				write_err;
	t_printf_format	format;

	count = 0;
	write_err = 0;
	pos = fstr;
	format = ft_next_format(&pos, &passed);
	while (format.valid)
	{
		count += wcheck(write(fd, fstr, passed - fstr), &write_err);
		count += wcheck(ft_put_format_fd(fd, format), &write_err);
		fstr = pos;
		format = ft_next_format(&pos, &passed);
	}
	count += wcheck(write(fd, fstr, passed - fstr), &write_err);
	if (write_err)
		return (-1);
	return (count);
}
