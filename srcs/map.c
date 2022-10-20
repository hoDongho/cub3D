/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:49:15 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/20 14:35:33 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_space(t_dlist *map, int index)
{
	if (map->prev && map->prev->width >= index
		&& (map->prev->line[index] != ' ' && map->prev->line[index] != '1'))
		return (puterr_msg("map error!"));
	if (map->line[index + 1]
		&& (map->line[index + 1] != ' ' && map->line[index + 1] != '1'))
		return (puterr_msg("map error!"));
	if (map->next && map->next->width >= index
		&& (map->next->line[index] != ' ' && map->next->line[index] != '1'))
		return (puterr_msg("map error!"));
	if (index && map->line[index - 1]
		&& (map->line[index - 1] != ' ' && map->line[index - 1] != '1'))
		return (puterr_msg("map error!"));
	return (0);
}

static int	check_elem(t_info *info, t_dlist *now, int i, int *flag)
{
	if (now->line[i] != '1' && now->line[i] != '0' && now->line[i] != 'X'
		&& now->line[i] != 'N' && now->line[i] != 'S' && now->line[i] != 'K'
		&& now->line[i] != 'E' && now->line[i] != 'W' && now->line[i] != 'C')
		return (puterr_msg("map error!"));
	if ((now->line[i] == 'N' || now->line[i] == 'S'
			|| now->line[i] == 'E' || now->line[i] == 'W'))
	{
		if (!(*flag) && ++(*flag))
		{
			info->p_x = (double)i + 0.5;
			info->p_y = (double)now->height + 0.5;
			info->start_dir = now->line[i];
			now->line[i] = '0';
			return (0);
		}
		else if (*flag)
			return (puterr_msg("map error!"));
	}
	if (now->line[i] == '0' && (!now->prev->line[i] || !now->next->line[i]))
		puterr_msg("map error!");
	return (0);
}

static int	check_up_down(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (puterr_msg("map error!"));
		i++;
	}
	return (0);
}

static int	check_map(t_info *info, t_dlist *now, int start_flag)
{
	int	i;

	check_up_down(now->line);
	now = now->next;
	while (now->next)
	{
		if ((now->line[0] != ' ' && now->line[0] != '1')
			|| (now->line[now->width - 1] != ' '
				&& now->line[now->width - 1] != '1'))
			return (puterr_msg("map error!"));
		i = -1;
		while (now->line[++i])
		{
			if (now->line[i] == ' ')
				check_space(now, i);
			else if (now->line[i] == 'C')
				check_door(now, i);
			else if (now->line[i] != ' ')
				check_elem(info, now, i, &start_flag);
		}
		now = now->next;
	}
	if (!start_flag || check_up_down(now->line))
		return (puterr_msg("map error!"));
	return (0);
}

int	check_and_make_map(t_info *info, int fd)
{
	char	*tmp;
	t_dlist	*now;
	int		cnt;

	cnt = 0;
	while (++cnt)
	{
		tmp = gnl_scan(fd, 1);
		if (!tmp)
			break ;
		add_list(&info->map, tmp, cnt);
	}
	now = info->map;
	check_map(info, now, 0);
	if (!count_elem(info->map, 'X'))
		puterr_msg("map error!");
	return (0);
}
