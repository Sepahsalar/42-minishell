/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:01:19 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 13:12:23 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_atol	atol_exit_helper(char *str)
{
	t_atol	res;

	res.i = 0;
	res.sign = 1;
	res.num = 0;
	res.is_error = 0;
	while (str[res.i])
	{
		if (!(ft_isdigit(str[res.i]) || str[0] == '-' || str[0] == '+'))
		{
			res.is_error = 1;
			return (res);
		}
		res.i++;
	}
	res.i = 0;
	if (str[res.i] == '-' || str[res.i] == '+')
	{
		if (str[res.i] == '-')
			res.sign *= -1;
		res.i++;
	}
	return (res);
}

t_atol	atol_exit(char *str)
{
	long	a;
	t_atol	res;

	res.i = 0;
	res.sign = 1;
	res.num = 0;
	res.is_error = 0;
	a = 0;
	res = atol_exit_helper(str);
	while (str[res.i] >= '0' && str[res.i] <= '9')
	{
		a = a * 10 + (str[res.i] - '0');
		if (a < 0)
		{
			res.is_error = 1;
			return (res);
		}
		res.i++;
	}
	res.num = res.sign * a;
	return (res);
}
