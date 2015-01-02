/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:13:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 14:26:00 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	low_main(char *options, t_filedir *tmp_fldr)
{
	t_arraylist		*filedirs;

	if (!tmp_fldr)
		exit(0);
	if (S_ISDIR(tmp_fldr->stats->st_mode) || ls_isdir(tmp_fldr->path))
	{
		filedirs = ls_gen_filedirs(options, tmp_fldr);
		del_filedir(tmp_fldr);
	}
	else
	{
		filedirs = check_malloc(arraylist(tmp_fldr, 1));
		if (ft_strchr(options, 'l'))
			*(ft_strchr(options, 'l')) = 'F';
	}
	if (ft_strchr(options, 'R'))
		ls_buckle(options, filedirs);
	else
		ls_print(options, filedirs);
}

t_arraylist	*filedirs_from_list(int listsize, char **list)
{
	int				i;
	t_filedir		*tmp_fldr;
	t_arraylist		*filedirs;

	ft_sort_string_array(list, listsize);
	i = 0;
	filedirs = NULL;
	while (i < listsize)
	{
		if ((tmp_fldr = filedir(list[i])) != NULL)
		{
			if (!filedirs)
				filedirs = check_malloc(arraylist(tmp_fldr, listsize));
			else
				filedirs->push(filedirs, tmp_fldr);
		}
		i++;
	}
	return (filedirs);
}

int			main(int listsize, char **list)
{
	int				i;
	char			*options;
	t_filedir		*tmp_fldr;
	t_arraylist		*filedirs;

	options = check_malloc(ft_strnew(0));
	i = 1;
	while (i < listsize && isoption(list[i]))
		ft_strjoinfree(&options, list[i++] + 1);
	if (i < listsize && ft_strcmp(list[i], "--") == 0)
		i++;
	check_options(options);
	list = list + i;
	listsize = listsize - i;
	if (listsize <= 1)
	{
		if (listsize < 1)
			tmp_fldr = filedir(".");
		else
			tmp_fldr = filedir(*list);
		low_main(options, tmp_fldr);
	}
	else if ((filedirs = filedirs_from_list(listsize, list)) != NULL)
		ls_first(options, filedirs);
	return (0);
}
