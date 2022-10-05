/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:28:42 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/05 11:12:59 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	puterr_msg(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

int	free_info(t_info *info)
{
	int	i;

	if (info->no_path)
		free(info->no_path);
	if (info->so_path)
		free(info->so_path);
	if (info->we_path)
		free(info->we_path);
	if (info->ea_path)
		free(info->ea_path);
	i = -1;
	if (info->map)
		delete_dlist(info->map);
	return (0);
}

char	*gnl_scan(int fd, int flag)
{
	char	*tmp;

	tmp = get_next_line(fd);
	if (!ft_strncmp(tmp, "\n", 2))
	{
		if (!flag)
		{
			free(tmp);
			return (gnl_scan(fd, flag));
		}
		return (tmp);
	}
	if (!tmp || !tmp[0])
	{
		if (tmp)
			free(tmp);
		return (NULL);
	}
	tmp[ft_strlen(tmp) - 1] = '\0';
	return (tmp);
}
