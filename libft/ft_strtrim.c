/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:38:36 by yehyun            #+#    #+#             */
/*   Updated: 2022/09/13 15:49:32 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static void	make_temp(char *temp, char *s1, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '\0';
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start_trim;
	size_t	size;
	char	*temp;

	if (!s1 || !set)
		return (NULL);
	start_trim = 0;
	size = 0;
	while (count_set(s1[start_trim], set) == 1)
		start_trim++;
	if (!s1[start_trim])
	{
		temp = (char *)malloc(sizeof(char));
		temp[0] = '\0';
		return (temp);
	}
	while (s1[start_trim + size])
		size++;
	while (count_set(s1[start_trim + size - 1], set) == 1)
		size--;
	temp = (char *)malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	make_temp(temp, (char *)s1 + start_trim, size);
	return (temp);
}
