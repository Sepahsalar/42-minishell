/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:35:54 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/05 10:40:27 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*p;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	p = (char *)malloc(ft_strlen(src) + 1);
	if (!p)
		return (0);
	while (src[i])
	{
		p[i] = ((char *)src)[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
