/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:20:47 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/16 22:02:03 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdarg.h>
#include <unistd.h>
#include "libft/libft.h"
#include "ft_printf_utils.h"
#include "ft_printf.h"

static int	ft_putstr_format_fd(
	char *str, int fd, t_printf_format format)
{
	int		len;
	int		pad;
	int		r[2];

	if (format.specifier == 1)
		len = 1;
	else if (format.precision >= 0)
		len = ft_strnlen(str, format.precision);
	else
		len = ft_strlen(str);
	pad = ft_max(0, format.width - len);
	if (!(format.flags & FT_PRINTF_LJUST))
		r[0] = ft_putncharn_fd(' ', pad, fd);
	r[1] = write(fd, str, len);	
	if (format.flags & FT_PRINTF_LJUST)
		r[0] = ft_putncharn_fd(' ', pad, fd);
	if (r[0] < 0 || r[1] < 0)
		return (-1);
	return (r[0] + r[1]);
}

static char	*ft_getnumprefix(char s)
{
	if (s == 'x')
		return ("0x");
	else if (s == 'X')
		return ("0X");
	else if (s == 'o')
		return ("0");
	else if (s == 'b')
		return ("b");
	return ("");
}

static int	ft_putnbrcmn_format_fd(
	char *prefix, char *content, int fd, t_printf_format format)
{
	int	pad;
	int	zeros;
	int	r[4];
	int	len[2];
	
	len[0] = ft_strlen(prefix);
	len[1] = ft_strlen(content);
	zeros = ft_max(0, format.precision - len[1]);
	if (zeros > 0 && ft_strcmp(prefix, "0") == 0)
		--zeros;
	pad = ft_max(0, format.width - (len[0] + zeros + len[1]));
	if (format.flags & FT_PRINTF_0PAD && pad > 0 && format.precision < 0
		&& !(format.flags & FT_PRINTF_LJUST))
		ft_swapi(&pad, &zeros);
	if (!(format.flags & FT_PRINTF_LJUST))
		r[0] = ft_putncharn_fd(' ', pad, fd);
	r[1] = ft_putstrn_fd(prefix, fd);
	r[2] = ft_putncharn_fd('0', zeros, fd);
	r[3] = ft_putstrn_fd(content, fd);
	if (format.flags & FT_PRINTF_LJUST)
		r[0] = ft_putncharn_fd(' ', pad, fd);
	if (r[0] < 0 || r[1] < 0 || r[2] < 0 || r[3] < 0)
		return (-1);
	return (r[0] + r[1] + r[2] + r[3]);
}

static unsigned long long	ft_putunsigned_format_fd(
	t_ft_va_list *list, int fd, t_printf_format format)
{
	char				buf[128];
	unsigned long long	nbr;
	char				*prefix;
	char				*content;

	nbr = va_arg(list->args, unsigned int);	
	if (format.precision == 0 && nbr == 0)
		content = "";
	else if (format.specifier == 'x' || format.specifier == 'X')
		content = ft_ulltoa_base_buf(nbr, 16, buf, 128);
	else if (format.specifier == 'u')
		content = ft_ulltoa_base_buf(nbr, 10, buf, 128);
	else if (format.specifier == 'o')
		content = ft_ulltoa_base_buf(nbr, 8, buf, 128);
	else if (format.specifier == 'b')
		content = ft_ulltoa_base_buf(nbr, 2, buf, 128);
	prefix = "";
	if (format.flags & FT_PRINTF_ALT && nbr != 0)
		prefix = ft_getnumprefix(format.specifier);
	return ft_putnbrcmn_format_fd(prefix, content, fd, format);
}

static int	ft_putsigned_format_fd(
	t_ft_va_list *list, int fd, t_printf_format format)
{
	char		buf[128];
	long long	nbr;
	int			sign;
	char		*prefix;
	char		*content;

	nbr = va_arg(list->args, int);
	sign = 1;
	if (nbr < 0)
		sign = -1;		
	content = ft_ulltoa_base_buf(ft_absull(nbr), 10, buf, 128);
	prefix = "";
	if (sign < 0)
		prefix = "-";
	else if (format.flags & FT_PRINTF_SIGN)
		prefix = "+";
	else if (format.flags & FT_PRINTF_SPACE)
		prefix = " ";
	return ft_putnbrcmn_format_fd(prefix, content, fd, format);
}

int	ft_put_format_fd(int fd, t_printf_format format, t_ft_va_list *list)
{
	char	c;

	if (format.specifier == 'c')
	{
		c = (char) va_arg(list->args, int);
		return (ft_putstr_format_fd(&c, fd, format));
	}
	else if (format.specifier == 's')
		return (ft_putstr_format_fd(va_arg(list->args, char *), fd, format));
	else if (ft_isinset(format.specifier, "di"))
		return (ft_putsigned_format_fd(list, fd, format));
	else if (ft_isinset(format.specifier, "uxXb"))
		return (ft_putunsigned_format_fd(list, fd, format));
	else if (format.specifier == '%')
		return (ft_putcharn_fd('%', fd));
	return (-1);
}
