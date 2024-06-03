/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:36:46 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/03 18:36:50 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_remove(char *str, char *del, t_file *file)
{
	int		len1;
	int		len2;
	char	*part2;
	char	*temp;
	char	*result;
	int		original_len;

	original_len = ft_strlen(str);
	len1 = file->place;
	if (file->ignore)
		part2 = str + len1 + 1;
	else
		part2 = ft_strnstr(str + len1, del, ft_strlen(str)) + ft_strlen(del);
	temp = part2;
	len2 = 0;
	while (*temp)
	{
		len2++;
		temp++;
	}
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_memcpy(result, str, len1);
	ft_memcpy(result + len1, part2, len2);
	result[len1 + len2] = '\0';
	free(str);
	file = file->next;
	while (file)
	{
		file->place = file->place + len1 + len2 - original_len;
		file = file->next;
	}
	return (result);
}
