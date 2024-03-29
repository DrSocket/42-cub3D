/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucisanc <lucisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 22:50:21 by lucisanc          #+#    #+#             */
/*   Updated: 2021/03/01 15:34:27 by lucisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	numberblank(char *str)
{
	int index;

	index = 0;
	while (str[index] == '\t' || str[index] == '\r'
	|| str[index] == '\v' || str[index] == ' ')
		index++;
	return (index);
}

int	strlentoblank(char *str)
{
	int index;

	index = 0;
	while (str[index] != ' ' && str[index])
		index++;
	return (index);
}

int	strlentoend(char *str)
{
	int index;

	index = 0;
	while (str[index] != '\n' && str[index])
		index++;
	return (index);
}

int	is_space(char c)
{
	if (c == '\t' || c == ' ' || c == '\0' || c == '\n')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int min;
	int nb;

	nb = 0;
	min = 0;
	while (*str && ((*str >= '\t' && *str <= '\r') || *str == ' '))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			min++;
		str++;
	}
	while (*str && (*str <= '9' && *str >= '0'))
	{
		nb = nb * 10 + (*str - 48);
		str++;
	}
	return ((min % 2 == 0) ? nb : -nb);
}
