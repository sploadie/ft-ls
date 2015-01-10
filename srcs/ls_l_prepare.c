/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_l_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 09:47:54 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/10 09:33:09 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static unsigned int	ls_size_size(t_l_info *info, t_stat *stats)
{
	unsigned int	temp_minor;
	unsigned int	temp_major;

	if (S_ISCHR(stats->st_mode) || S_ISBLK(stats->st_mode))
	{
		temp_minor = digitc(minor(stats->st_rdev));
		if (info->minor_spacing < temp_minor)
			info->minor_spacing = temp_minor;
		temp_major = digitc(major(stats->st_rdev));
		if (info->major_spacing < temp_major)
			info->major_spacing = temp_major;
		return (temp_minor + temp_major + 4);
	}
	return (digitc(stats->st_size));
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
	temp = ls_size_size(info, filedir->stats);
	if (info->size_spacing < temp)
		info->size_spacing = temp;
}

static void			ls_print_total(int total)
{
	write(1, "total ", 6);
	ft_putnbr(total);
	write(1, "\n", 1);
}

static t_l_info		*ls_get_info(void)
{
	t_l_info		*neoinfo;

	if (!get_set_l_info(NULL))
	{
		neoinfo = check_malloc(malloc(sizeof(t_l_info)));
		get_set_l_info(neoinfo);
	}
	else
		neoinfo = get_set_l_info(NULL);
	return (neoinfo);
}

void				ls_l_prepare(char *options, t_arraylist *filedirs)
{
	t_l_info		*neoinfo;
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;
	unsigned int	file_count;

	neoinfo = ls_get_info();
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
	if ((neoinfo->block_mem_total || file_count) && !ft_strchr(options, 'F'))
		ls_print_total(neoinfo->block_mem_total);
	if (ft_strchr(options, 'F'))
		*(ft_strchr(options, 'F')) = 'l';
}
