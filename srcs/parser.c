/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:13:10 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/13 15:24:17 by yehyun           ###   ########seoul.kr  */
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
	if (info->cub.ea && info->cub.no && info->cub.so && info->cub.we
		&& info->cub.floor && info->cub.ceiling)
		return (1);
	if (!ft_strncmp(tmp, "NO", 2)
		&& info->cub.no == NULL && (tmp[2] == ' ' || tmp[2] == '\t'))
		info->cub.no = tmp;
	else if (!ft_strncmp(tmp, "SO", 2)
		&& info->cub.so == NULL && (tmp[2] == ' ' || tmp[2] == '\t'))
		info->cub.so = tmp;
	else if (!ft_strncmp(tmp, "WE", 2)
		&& info->cub.we == NULL && (tmp[2] == ' ' || tmp[2] == '\t'))
		info->cub.we = tmp;
	else if (!ft_strncmp(tmp, "EA", 2)
		&& info->cub.ea == NULL && (tmp[2] == ' ' || tmp[2] == '\t'))
		info->cub.ea = tmp;
	else if (!ft_strncmp(tmp, "F", 1)
		&& info->cub.floor == NULL && (tmp[1] == ' ' || tmp[1] == '\t'))
		info->cub.floor = tmp;
	else if (!ft_strncmp(tmp, "C", 1)
		&& info->cub.ceiling == NULL && (tmp[1] == ' ' || tmp[1] == '\t'))
		info->cub.ceiling = tmp;
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
	if (check == -1)
		return (puterr_msg("invalid basic info"));
	if ((ft_access(ft_strchr(info->cub.no, '.'), C_CLOSE) == ERROR
			|| ft_access(ft_strchr(info->cub.so, '.'), C_CLOSE) == ERROR
			|| ft_access(ft_strchr(info->cub.ea, '.'), C_CLOSE) == ERROR
			|| ft_access(ft_strchr(info->cub.we, '.'), C_CLOSE) == ERROR
			|| check_rgb(info->cub.floor) == ERROR
			|| check_rgb(info->cub.ceiling) == ERROR))
		return (puterr_msg("invalid basic info"));
	add_list(&info->map, tmp, 0);
	return (0);
}

int	parsing_map(t_info *info, char *filename)
{
	int	fd;

	fd = check_file(filename);
	check_basic(info, fd);
	cali_info(info);
	check_and_make_map(info, fd);
	close(fd);
	return (0);
}
