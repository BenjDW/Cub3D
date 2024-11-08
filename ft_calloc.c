/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:09:24 by bde-wits          #+#    #+#             */
/*   Updated: 2024/11/08 10:18:07 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stddef.h>
#include <stdlib.h>

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	if (nmemb > 4294967295 || size > 4294967295)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	str = (void *)malloc(nmemb * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, nmemb * size);
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*sp;

	sp = (char *)s;
	i = 0;
	while (i != n)
	{
		sp[i] = 0;
		i++;
	}
}
