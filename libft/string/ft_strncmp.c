/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:36:33 by hmorand           #+#    #+#             */
/*   Updated: 2024/04/26 11:36:33 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i] || s2[i])
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("Identical strings: %d\n", ft_strncmp("Hello", "Hello", 5));
	printf("s1 bigger than s2: %d\n", ft_strncmp("hello", "Hello", 5));
	printf("s1 smaller than s2: %d\n", ft_strncmp("Hello", "hello", 5));
	printf("s1 longer than s2: %d\n", ft_strncmp("hello", "hell", 5));
	printf("s1 shorter than s2: %d\n", ft_strncmp("hell", "hello", 5));
	printf("Difference right after n: %d\n", ft_strncmp("hello", "hell", 4));
	printf("Difference way after n: %d\n",
	 ft_strncmp("hello world", "hello", 5));
	printf("Weird test from francinette: %u",
	ft_strncmp("test\200", "test\0", 6));
}

 */
