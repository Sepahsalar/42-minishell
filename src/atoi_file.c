/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:03:14 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/03 13:02:28 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_atoi_file	atoi_file_helper(char **input, int place, int def)
{
	t_atoi_file	af;

	af.str = *input;
	af.flag = 0;
	af.res = 0;
	af.place = place;
	if (af.place)
		af.place--;
	else
	{
		af.res = def;
		af.flag = 1;
		return (af);
	}
	if ((af.place >= 0 && af.str[af.place] == '>' && def == 1)
		|| (af.str[af.place] == '<' && def == 0))
		af.place--;
	if (af.str[af.place] == ' ')
	{
		af.flag = 1;
		af.res = def;
	}
	return (af);
}

static void	atoi_file_remove(char **input, t_atoi_file	af, char *part, int len)
{
	char	*new;
	char	*temp_str;

	new = malloc(len + ft_strlen(part) + 1);
	//protection
	new[len + ft_strlen(part)] = '\0';
	ft_memcpy(new, af.str, len);
	ft_memcpy(new + len, part, ft_strlen(part));
	temp_str = *input;
	*input = new;
	free(temp_str);
}

long	atoi_file(char **input, int place, int def)
{
	long		a;
	t_atoi_file	af;
	int			len;
	char		*part2;

	a = 0;
	af = atoi_file_helper(input, place, def);
	if (af.flag == 1)
		return (af.res);
	part2 = af.str + af.place + 1;
	while (af.place >= 0 && af.str[af.place] >= '0' && af.str[af.place] <= '9')
		af.place--;
	if (af.place != -1 && af.str[af.place] != ' ')
		return (def);
	len = af.place + 1;
	af.place++;
	while (af.str[af.place] >= '0' && af.str[af.place] <= '9')
	{
		a = a * 10 + (af.str[af.place] - '0');
		af.place++;
	}
	atoi_file_remove(input, af, part2, len);
	return (a);
}
