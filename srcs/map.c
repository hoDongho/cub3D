/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:49:15 by yehyun            #+#    #+#             */
/*   Updated: 2022/09/27 10:04:57 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_space(t_dlist *map, int index)
{
	if (map->prev && map->prev->width >= index
		&& (map->prev->line[index] != ' ' && map->prev->line[index] != '1'))
		return (ERROR);
	if (map->line[index + 1]
		&& (map->line[index + 1] != ' ' && map->line[index + 1] != '1'))
		return (ERROR);
	if (map->next && map->next->width >= index
		&& (map->next->line[index] != ' ' && map->next->line[index] != '1'))
		return (ERROR);
	if (index && map->line[index - 1]
		&& (map->line[index - 1] != ' ' && map->line[index - 1] != '1'))
		return (ERROR);
	return (0);
}

static int	check_elem(char now, int *flag)
{
	if (now != '1' && now != '0' && now != ' '
		&& now != 'N' && now != 'S' && now != 'E' && now != 'W')
		return (ERROR);
	if ((now == 'N' || now == 'S' || now == 'E' || now == 'W'))
	{
		if (!(*flag) && ++(*flag))
			return (0);
		else if (*flag)
			return (ERROR);
	}
	return (0);
}

static int	check_updown(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] != '1' && line[i] != ' ')
			return (ERROR);
	return (0);
}

static int	check_map(t_dlist *now, int start_flag)
{
	int	i;

	if (check_updown(now->line) == ERROR)
		return (ERROR);
	now = now->next;
	while (now->next)
	{
		if ((now->line[0] != ' ' && now->line[0] != '1')
			|| (now->line[now->width - 1] != ' '
				&& now->line[now->width - 1] != '1'))
			return (ERROR);
		i = -1;
		while (now->line[++i])
		{
			if (now->line[i] == ' ' && check_space(now, i) == ERROR)
				return (ERROR);
			else if (now->line[i] != ' '
				&& check_elem(now->line[i], &start_flag) == ERROR)
				return (ERROR);
		}
		now = now->next;
	}
	if (!start_flag || check_updown(now->line) == ERROR)
		return (ERROR);
	return (0);
}

int	check_and_make_map(t_info *info, int fd)
{
	char	*tmp;
	int		cnt;

	cnt = 0;
	while (++cnt)
	{
		tmp = gnl_scan(fd, 1);
		if (!tmp)
			break ;
		add_list(&info->map, tmp, cnt);
	}
	if (check_map(info->map, 0) == ERROR)
	{
		delete_dlist(info->map);
		return (puterr_msg("map error!"));
	}
	return (0);
}
