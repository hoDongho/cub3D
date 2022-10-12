/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:53:18 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/12 12:17:03 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_door_to_img(t_info *info, t_ray *ray, t_draw *draw, int x)
{
	int	s_tmp;
	int	e_tmp;

	s_tmp = draw->start;
	e_tmp = draw->end;
	if (info->door != 0 && ray->hit == -1)
	{
		draw->start -= info->door;
		draw->end -= info->door;
		info->door++;
		if (draw->start <= 0 || draw->end <= s_tmp || info->door >= 2147483647)
		{
			draw->start = s_tmp;
			draw->end = e_tmp;
			move_door(info);
			info->door = 0;
			printf("start %d end %d\n", draw->start, draw->end);
		}
	}
	while (draw->start < draw->end)
	{
		if (draw->start < s_tmp)
		{
			draw->start++;
			continue;
		}
		draw->tex_y = (int)draw->tex_pos & (P_HEIGHT - 1);
		draw->tex_pos += draw->step;
		draw->color = info->texture[draw->tex_num]
		[P_HEIGHT * draw->tex_y + draw->tex_x];
		if (ray->side == 1)
			draw->color = (draw->color >> 1) & 8355711;
		info->buff[draw->start][x] = draw->color;
		draw->start++;
	}
	return (0);
}

int	check_door(t_dlist *now, int i)
{
	if (now->line[i - 1] == '1' && now->line[i + 1] == '1')
		return (0);
	if (now->next->line[i] == '1' && now->prev->line[i] == '1')
		return (0);
	return (puterr_msg("map error!"));
}

void	change_target(t_dlist *list, int x, int y)
{
	t_dlist	*tmp;
	int		i;

	tmp = list;
	i = 0;
	while (tmp->height != y)
		tmp = tmp->next;
	while (i != x)
		i++;
	if (tmp->line[x] == 'C')
		tmp->line[x] = 'o';
	else if (tmp->line[x] == 'o')
		tmp->line[x] = 'O';
	else if (tmp->line[x] == 'O')
		tmp->line[x] = 'c';
	else if (tmp->line[x] == 'c')
		tmp->line[x] = 'C';
}

int	move_door(t_info *info)
{

	if (info->door == 0)
		info->door = 1;
	if (info->dir_y < 0 && (info->dir_x < 1 || info->dir_x > -1))
		change_target(info->map, (int)info->p_x, (int)info->p_y - 1);
	else if (info->dir_y > 0 && (info->dir_x < 1 || info->dir_x > -1))
		change_target(info->map, (int)info->p_x, (int)info->p_y + 1);
	if (info->dir_x < 0 && (info->dir_y < 1 || info->dir_y > -1))
		change_target(info->map, (int)info->p_x - 1, (int)info->p_y);
	else if (info->dir_x > 0 && (info->dir_y < 1 || info->dir_y > -1))
		change_target(info->map, (int)info->p_x + 1, (int)info->p_y);
	return (0);
}
