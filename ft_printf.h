/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:03:46 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/19 16:26:11 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

typedef struct s_ft_va_list
{
	va_list	args;
}	t_ft_va_list;

int	ft_dprintf(int fd, const char *fstr, ...);
int	ft_printf(const char *fstr, ...);
int	ft_vdprintf(int fd, const char *fstr, t_ft_va_list *list);

#endif