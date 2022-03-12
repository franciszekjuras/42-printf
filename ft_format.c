/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:20:47 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/12 20:27:43 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "ft_printf_utils.h"

int	ft_put_format_fd(int fd, t_printf_format format)
{
	if (format.specifier == 'c')
		ft_putchar_fd('a', fd);
	else if (format.specifier == 's')
		ft_putstr_fd("some string", fd);
	return (0);
}

static int ft_scan_flags(const char **pos)
{
	const char	*crr;
	int			flagidx;
	int			flags;

	crr = *pos;
	flags = 0;
	flagidx = ft_idxinset(*crr, FT_PRINTF_FLAGS);
	while (flagidx > 0)
	{
		flags |= (1 << flagidx);
		crr++;
		flagidx = ft_idxinset(*crr, FT_PRINTF_FLAGS);
	}
	*pos = crr;
	return (flags);
}

t_printf_format	ft_scan_format(const char **pos, const char **passed)
{
	t_printf_format format;

	format.valid = 0;
	while (**pos != '\0' && **pos != '%')
		(*pos)++;
	*passed = *pos;
	if (**pos != '%')
		return (format);
	(*pos)++;
	format.flags = ft_scan_flags(pos);
	if (!ft_isinset(**pos, FT_PRINTF_SPECS))
		return (format);
	format.specifier = **pos;
	(*pos)++;
	format.valid = 1;
	return (format);
}

t_printf_format	ft_next_format(const char **pos, const char **passed)
{
	t_printf_format	format;

	format = ft_scan_format(pos, passed);
	while (**pos != '\0' && !format.valid)
		format = ft_scan_format(pos, passed);
	return (format);
}
