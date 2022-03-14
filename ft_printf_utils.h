/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:03:46 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/14 20:23:08 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# define FT_PRINTF_FLAGS "-+ #0"
# define FT_PRINTF_SPECS "cs"

enum e_printf_flag
{
	FT_PRINTF_LJUST = 0x01,
	FT_PRINTF_SIGN = 0x02,
	FT_PRINTF_SPACE = 0x04,
	FT_PRINTF_ALT = 0x08,
	FT_PRINTF_LPAD = 0x10,
};

typedef struct s_printf_format
{
	int		flags;
	int		width;
	int		precision;
	char	specifier;
	char	valid;
}	t_printf_format;

int				ft_put_format_fd(int fd, t_printf_format format);
t_printf_format	ft_scan_format(char **pos, char **passed);

#endif
