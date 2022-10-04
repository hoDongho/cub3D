/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:35:42 by yehyun            #+#    #+#             */
/*   Updated: 2022/09/13 15:49:32 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	size;
	char	*str_join;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	size = len1 + len2;
	str_join = (char *)malloc(sizeof(char) * (size + 1));
	if (!str_join)
		return (NULL);
	while (len1--)
		*(str_join++) = *(s1++);
	while (len2--)
		*(str_join++) = *(s2++);
	*str_join = '\0';
	return (str_join - size);
}
