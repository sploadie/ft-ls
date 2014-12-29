/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_l_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 09:47:54 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/29 13:35:10 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static unsigned int	digitc(unsigned int n)
{
	int		count;
	long	tens;

	count = 1;
	tens = 10;
	while (n >= tens)
	{
		tens = tens * 10;
		count++;
	}
	return (count);
}

static void			extract_l_info(t_l_info *info, t_filedir *filedir)
{
	unsigned int	temp;

	info->block_mem_total += filedir->stats->st_blocks;
	temp = digitc(filedir->stats->st_nlink);
	if (info->link_spacing < temp)
		info->link_spacing = temp;
	temp = ft_strlen(uid_to_name(filedir->stats->st_uid));
	if (info->user_spacing < temp)
		info->user_spacing = temp;
	temp = ft_strlen(gid_to_name(filedir->stats->st_gid));
	if (info->group_spacing < temp)
		info->group_spacing = temp;
	temp = digitc(filedir->stats->st_size);
	if (info->size_spacing < temp)
		info->size_spacing = temp;
}

void				ls_l_prepare(char *options, t_arraylist *filedirs)
{
	t_l_info		*neoinfo;
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;
	unsigned int	file_count;

	neoinfo = check_malloc(malloc(sizeof(t_l_info)));
	ft_bzero(neoinfo, sizeof(t_l_info));
	file_count = 0;
	iter = arlst_iter(filedirs);
	iter_ret = 1;
	while (iter_ret)
	{
		temp_filedir = iter->pip(iter, &iter_ret);
		if (show_entry(options, temp_filedir->name) && ++file_count)
			extract_l_info(neoinfo, temp_filedir);
	}
	free(iter);
	get_set_l_info(neoinfo);
	if (neoinfo->block_mem_total || file_count)
	{
		write(1, "total ", 6);
		ft_putnbr(neoinfo->block_mem_total);
		write(1, "\n", 1);
	}
}
