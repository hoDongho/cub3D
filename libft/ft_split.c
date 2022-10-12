/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:43:59 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/12 10:34:53 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*splcpy(char *s, char c, int *point)
{
	int		i;
	int		size;
	char	*temp;

	size = 0;
	while (s[size] != c && s[size])
		size++;
	temp = (char *)malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	*point += size;
	return (temp);
}

static int	count_split(const char *s, char c)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			cnt++;
		}
		else
			i++;
	}
	return (cnt);
}

static void	free_arr(char **str, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(str[i]);
		i++;
	}
}

char	**ft_split(const char *s, char c)
{
	int		cnt;
	int		point;
	int		i;
	char	**ret_spl;

	if (!s)
		return (NULL);
	cnt = count_split(s, c);
	ret_spl = (char **)ft_calloc(cnt + 1, sizeof(char *));
	if (!ret_spl)
		return (NULL);
	point = 0;
	i = -1;
	while (++i < cnt)
	{
		while (s[point] == c)
			point++;
		ret_spl[i] = splcpy((char *)s + point, c, &point);
		if (ret_spl[i] == NULL && i)
		{
			free_arr(ret_spl, i);
			free(ret_spl);
		}
	}
	return (ret_spl);
}
