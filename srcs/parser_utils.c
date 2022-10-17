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

int	parse_rgb(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
			continue ;
		}
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (ERROR);
		if (str[i] == ',')
			cnt++;
		i++;
	}
	if (cnt != 2)
		return (ERROR);
	return (0);
}

int	check_rgb(char *rgb)
{
	char	**spl;
	int		index;
	int		check;
	int		ret;

	ret = 0;
	index = -1;
	if (parse_rgb(rgb + 1) == ERROR)
		return (ERROR);
	spl = ft_split(rgb + 1, ',');
	if (!spl)
		puterr_msg("rgb split error!");
	while (spl[++index])
	{
		check = ft_atoi(spl[index]);
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
	tmp = info->cub.floor + 1;
	ft_strlcpy(info->cub.floor, tmp, ft_strlen(tmp) + 1);
	tmp = info->cub.ceiling + 1;
	ft_strlcpy(info->cub.ceiling, tmp, ft_strlen(tmp) + 1);
}
