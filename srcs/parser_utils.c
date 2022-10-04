/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:46:02 by yehyun            #+#    #+#             */
/*   Updated: 2022/09/26 15:45:48 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_access(char *filename, int flag)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == ERROR)
		return (ERROR);
	if (flag == C_OPEN)
		return (fd);
	close(fd);
	return (0);
}

int	check_rgb(char *rgb, int i)
{
	char	**spl;
	int		index;
	int		check;
	int		ret;

	while (!ft_isdigit(rgb[i]))
		i++;
	spl = ft_split(&rgb[i], ',');
	ret = 0;
	index = -1;
	while (spl[++index])
	{
		check = ft_atoi(spl[index]);
		if (!check && spl[index][0] != '0')
			ret = ERROR;
		if (check < 0 || check > 255)
			ret = ERROR;
	}
	if (index != 3)
		ret = ERROR;
	while (index--)
		free(spl[index]);
	free(spl);
	return (ret);
}

void	cali_info(t_info *info)
{
	char	*tmp;

	tmp = info->no_path;
	info->no_path = ft_strdup(ft_strchr(info->no_path, '.'));
	free(tmp);
	tmp = info->so_path;
	info->so_path = ft_strdup(ft_strchr(info->so_path, '.'));
	free(tmp);
	tmp = info->we_path;
	info->we_path = ft_strdup(ft_strchr(info->we_path, '.'));
	free(tmp);
	tmp = info->ea_path;
	info->ea_path = ft_strdup(ft_strchr(info->ea_path, '.'));
	free(tmp);
	tmp = info->floor_color;
	while (!ft_isdigit(*tmp))
		tmp++;
	ft_strlcpy(info->floor_color, tmp, ft_strlen(tmp) + 1);
	tmp = info->ceiling_color;
	while (!ft_isdigit(*tmp))
		tmp++;
	ft_strlcpy(info->ceiling_color, tmp, ft_strlen(tmp) + 1);
}
