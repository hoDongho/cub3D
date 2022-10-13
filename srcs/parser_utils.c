/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:46:02 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/13 15:25:19 by yehyun           ###   ########seoul.kr  */
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

int	check_rgb(char *rgb, int i, int ret)
{
	char	**spl;
	int		index;
	int		check;

	while (!ft_isdigit(rgb[i]))
		i++;
	spl = ft_split(&rgb[i], ',');
	if (!spl)
		puterr_msg("rgb split error!");
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

	tmp = info->cub.no;
	info->cub.no = ft_strdup(ft_strchr(info->cub.no, '.'));
	free(tmp);
	tmp = info->cub.so;
	info->cub.so = ft_strdup(ft_strchr(info->cub.so, '.'));
	free(tmp);
	tmp = info->cub.we;
	info->cub.we = ft_strdup(ft_strchr(info->cub.we, '.'));
	free(tmp);
	tmp = info->cub.ea;
	info->cub.ea = ft_strdup(ft_strchr(info->cub.ea, '.'));
	free(tmp);
	tmp = info->cub.floor;
	while (!ft_isdigit(*tmp))
		tmp++;
	ft_strlcpy(info->cub.floor, tmp, ft_strlen(tmp) + 1);
	tmp = info->cub.ceiling;
	while (!ft_isdigit(*tmp))
		tmp++;
	ft_strlcpy(info->cub.ceiling, tmp, ft_strlen(tmp) + 1);
}
