/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:37:15 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/11 16:17:12 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dlist	*create_list(void)
{
	t_dlist	*new;

	new = ft_calloc(1, sizeof (t_dlist));
	return (new);
}

void	add_list(t_dlist **list, char *line, int height)
{
	t_dlist	*new;
	t_dlist	*curr;

	curr = *list;
	if (*list == NULL)
	{
		*list = create_list();
		(*list)->line = line;
		(*list)->height = height;
		(*list)->width = ft_strlen(line);
		return ;
	}
	while (curr->next)
		curr = curr->next;
	new = create_list();
	new->line = line;
	new->height = height;
	new->width = ft_strlen(line);
	curr->next = new;
	new->next = NULL;
	new->prev = curr;
}

void	delete_dlist(t_dlist *list)
{
	t_dlist	*curr;
	t_dlist	*tmp;

	curr = list;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->line);
		free(tmp);
	}
}

int	find_target(t_dlist *list, int x, int y)
{
	t_dlist	*tmp;
	int		i;

	tmp = list;
	i = 0;
	while (tmp->height != y)
		tmp = tmp->next;
	while (i != x)
		i++;
	if (tmp->line[x] == '1' || tmp->line[x] == 'C')
		return (tmp->line[x]);
	return (0);
}
