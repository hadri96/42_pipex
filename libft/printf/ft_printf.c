/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:59:28 by hmorand           #+#    #+#             */
/*   Updated: 2024/05/08 13:59:31 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	print_arg(int fd, char type, va_list elements, int *i)
{
	if (type == 'c')
		ft_putchar(fd, va_arg(elements, int), i);
	else if (type == 's')
		ft_putstr(fd, va_arg(elements, char *), i);
	else if (type == 'p')
		ft_putptr(fd, va_arg(elements, void *), i);
	else if (type == 'd' || type == 'i')
		ft_putnbr(fd, va_arg(elements, int), i);
	else if (type == 'u')
		ft_putunnbr(fd, va_arg(elements, unsigned int), i);
	else if (type == 'x')
		ft_puthex_low(fd, va_arg(elements, unsigned int), i);
	else if (type == 'X')
		ft_puthex_up(fd, va_arg(elements, unsigned int), i);
	else if (type == '%')
		ft_putchar(fd, '%', i);
}

int	ft_printf(int fd, const char *str, ...)
{
	int		i;
	int		j;
	int		err;
	va_list	elements;

	va_start(elements, str);
	i = 0;
	j = 0;
	err = 0;
	while (str[j])
	{
		if (str[j] == '%')
			print_arg(fd, str[++j], elements, &i);
		else
			ft_putchar(fd, str[j], &i);
		j++;
		if (err > i)
			return (-1);
		else
			err = i;
	}
	va_end(elements);
	return (i);
}
