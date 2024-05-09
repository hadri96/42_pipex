/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:54:12 by hmorand           #+#    #+#             */
/*   Updated: 2024/05/08 13:54:12 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putchar(int fd, char c, int *i)
{
	int	err;

	err = write(fd, &c, 1);
	if (err == -1)
		*i -= 10000;
	else
		*i += 1;
}

void	ft_putstr(int fd, char *str, int *i)
{
	int	j;

	j = 0;
	if (!str)
	{
		ft_putstr(fd, "(null)", i);
		return ;
	}
	while (str[j])
		ft_putchar(fd, str[j++], i);
}
