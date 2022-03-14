/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:20:47 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/14 20:27:33 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <limits.h>
#include "ft_printf_utils.h"
#include <stdio.h>

void	ft_print_t_printf_format(t_printf_format format)
{
	dprintf(2, "t_printf_format:\n"
		"flags: %x\n"
		"width: %d\n"
		"prcsn: %d\n"
		"spcfr: %c\n"
		"valid: %d\n",
		format.flags, format.width, format.precision,
		format.specifier, format.valid);
}

int	ft_put_format_fd(int fd, t_printf_format format)
{
	if (format.specifier == 'c')
		return (ft_putcharn_fd('a', fd));
	if (format.specifier == 's')
		return (ft_putstrn_fd("some string", fd));
	if (format.specifier == '%')
		return (ft_putcharn_fd('%', fd));	
	return (-1);
}

static int ft_scan_flags(char **pos)
{
	const char	*crr;
	int			flagidx;
	int			flags;

	crr = *pos;
	flags = 0;
	flagidx = ft_idxinset(*crr, FT_PRINTF_FLAGS);
	while (flagidx >= 0)
	{
		flags |= (1 << flagidx);
		crr++;
		flagidx = ft_idxinset(*crr, FT_PRINTF_FLAGS);
	}
	*pos = (char *) crr;
	return (flags);
}

void	ft_parse_format(t_printf_format *format, char **pos)
{
	int err;
	int tmp;

	format->flags = ft_scan_flags(pos);	
	err = -1;
	if (ft_isdigit(**pos))
		tmp = ft_strtonum(pos, 0, INT_MAX, &err);
	if (!err)
		format->width = tmp;
	err = -1;
	if (**pos == '.')
	{
		if (ft_isdigit(*(++(*pos))))
			tmp = ft_strtonum(pos, 0, INT_MAX, &err);
		else
			format->precision = 0;
		if (!err)
			format->precision = tmp;
	}
	if (**pos == '%' || ft_isinset(**pos, FT_PRINTF_SPECS))
	{
		format->specifier = *((*pos)++);
		format->valid = 1;
	}
	ft_print_t_printf_format(*format);
}

t_printf_format	ft_scan_format(char **pos, char **passed)
{
	t_printf_format format;

	format.valid = 0;
	format.width = -1;
	format.precision = -1;
	while (!format.valid)
	{
		while (**pos != '\0' && **pos != '%')
			(*pos)++;
		*passed = (char *) *pos;
		if (**pos == '\0')
			return (format);
		(*pos)++;
		ft_parse_format(&format, pos);
	}
	return (format);
}
