/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:13:10 by yehyun            #+#    #+#             */
/*   Updated: 2022/09/27 10:04:54 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_file(char *filename)
{
	int		fd;
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (ext == NULL)
		return (puterr_msg("wrong file!"));
	if (ft_strncmp(ext, ".cub", 5))
		return (puterr_msg("wrong file!"));
	fd = ft_access(filename, C_OPEN);
	if (fd == ERROR)
		return (puterr_msg("file doesn't open!"));
	return (fd);
}

static int	sort_basic(t_info *info, char *tmp)
{
	if (info->ea_path && info->no_path && info->so_path && info->we_path
		&& info->floor_color && info->ceiling_color)
		return (1);
	if (!ft_strncmp(tmp, "NO", 2)
		&& info->no_path == NULL && (tmp[2] == ' ' || tmp[2] == '\t'))
		info->no_path = tmp;
	else if (!ft_strncmp(tmp, "SO", 2)
		&& info->so_path == NULL && (tmp[2] == ' ' || tmp[2] == '\t'))
		info->so_path = tmp;
	else if (!ft_strncmp(tmp, "WE", 2)
		&& info->we_path == NULL && (tmp[2] == ' ' || tmp[2] == '\t'))
		info->we_path = tmp;
	else if (!ft_strncmp(tmp, "EA", 2)
		&& info->ea_path == NULL && (tmp[2] == ' ' || tmp[2] == '\t'))
		info->ea_path = tmp;
	else if (!ft_strncmp(tmp, "F", 1)
		&& info->floor_color == NULL && (tmp[1] == ' ' || tmp[1] == '\t'))
		info->floor_color = tmp;
	else if (!ft_strncmp(tmp, "C", 1)
		&& info->ceiling_color == NULL && (tmp[1] == ' ' || tmp[1] == '\t'))
		info->ceiling_color = tmp;
	else
		return (-1);
	return (0);
}

static int	check_basic(t_info *info, int fd)
{
	char	*tmp;
	int		check;

	check = 0;
	while (!check)
	{
		tmp = gnl_scan(fd, 0);
		check = sort_basic(info, tmp);
	}
	if (check == -1 && !free_info(info))
		return (puterr_msg("invalid basic info"));
	add_list(&info->map, tmp, 0);
	if ((ft_access(ft_strchr(info->no_path, '.'), C_CLOSE) == ERROR
			|| ft_access(ft_strchr(info->no_path, '.'), C_CLOSE) == ERROR
			|| ft_access(ft_strchr(info->no_path, '.'), C_CLOSE) == ERROR
			|| ft_access(ft_strchr(info->no_path, '.'), C_CLOSE) == ERROR
			|| check_rgb(info->floor_color, 0) == ERROR
			|| check_rgb(info->ceiling_color, 0) == ERROR)
		&& !free_info(info))
		return (puterr_msg("invalid basic info"));
	return (0);
}

int	parsing_map(t_info *info, char *filename)
{
	int	fd;

	fd = check_file(filename);
	if (fd == ERROR)
		return (ERROR);
	if (check_basic(info, fd) == ERROR && !close(fd))
		return (ERROR);
	cali_info(info);
	if (check_and_make_map(info, fd) == ERROR && !close(fd))
		return (ERROR);
	close(fd);
	return (0);
}
