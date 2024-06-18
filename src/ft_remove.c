/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:36:46 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/18 15:42:42 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_remove(char *str, char *del, t_file *file)
{
	int		len;
	char	*part2;
	char	*result;
	int		original_len;

	original_len = ft_strlen(str);
	len = file->place;
	part2 = ft_strnstr(str + len, del, ft_strlen(str)) + ft_strlen(del);
	result = malloc((len + ft_strlen(part2) + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_memcpy(result, str, len);
	ft_memcpy(result + len, part2, ft_strlen(part2));
	result[len + ft_strlen(part2)] = '\0';
	// // if (str)
	// 	free(str);
	file = file->next;
	while (file)
	{
		file->place = file->place + len + ft_strlen(part2) - original_len;
		file = file->next;
	}
	return (result);
}
