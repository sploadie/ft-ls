/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 09:33:48 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/09 16:24:43 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	getacl(char *name)
{
	acl_t		facl;
	acl_entry_t	ae;

	facl = acl_get_link_np(name, ACL_TYPE_EXTENDED);
	if (facl && (acl_get_entry(facl, ACL_FIRST_ENTRY, &ae) == -1))
	{
		acl_free(facl);
		return (0);
	}
	if (facl != NULL)
	{
		acl_free(facl);
		return (1);
	}
	acl_free(facl);
	return (0);
}

static void	ls_set_rights(char *str, int mode)
{
	(mode & S_IRUSR) ? str[1] = 'r' : (void)str;
	(mode & S_IWUSR) ? str[2] = 'w' : (void)str;
	(mode & S_IXUSR) ? str[3] = 'x' : (void)str;
	if (mode & S_ISUID)
		str[3] = ((mode & S_IXUSR) ? 's' : 'S');
	(mode & S_IRGRP) ? str[4] = 'r' : (void)str;
	(mode & S_IWGRP) ? str[5] = 'w' : (void)str;
	(mode & S_IXGRP) ? str[6] = 'x' : (void)str;
	if (mode & S_ISGID)
		str[6] = ((mode & S_IXGRP) ? 's' : 'S');
	(mode & S_IROTH) ? str[7] = 'r' : (void)str;
	(mode & S_IWOTH) ? str[8] = 'w' : (void)str;
	(mode & S_IXOTH) ? str[9] = 'x' : (void)str;
	if (mode & S_ISVTX)
		str[9] = ((str[9] == '-') ? 'T' : 't');
}

static void	ls_print_permissions(int mode, char *link, char *path)
{
	char		str[11];

	ft_strcpy(str, "----------  ");
	(S_ISDIR(mode)) ? str[0] = 'd' : (void)str;
	(S_ISLNK(mode)) ? str[0] = 'l' : (void)str;
	(link) ? str[0] = 'l' : (void)str;
	(S_ISSOCK(mode)) ? str[0] = 's' : (void)str;
	(S_ISFIFO(mode)) ? str[0] = 'p' : (void)str;
	(S_ISCHR(mode)) ? str[0] = 'c' : (void)str;
	(S_ISBLK(mode)) ? str[0] = 'b' : (void)str;
	ls_set_rights(str, mode);
	if ((!link && listxattr(path, NULL, 0, 0) > 0) ||
		(link && listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0))
		str[10] = '@';
	(getacl(path)) ? str[10] = '+' : (void)str;
	ft_putstr(str);
}

static void	ls_print_time(time_t *clock)
{
	write(1, 4 + ctime(clock), 7);
	if (*clock > time(NULL))
		write(1, 19 + ctime(clock), 5);
	else if (*clock > (time(NULL) - ((2599000 + 43200 - 25000) * 6)))
		write(1, 11 + ctime(clock), 5);
	else
		write(1, 19 + ctime(clock), 5);
	write(1, " ", 1);
}

static void	ls_print_size(t_l_info *info, t_stat *stats)
{
	if (S_ISCHR(stats->st_mode) || S_ISBLK(stats->st_mode))
	{
		ls_print_left(ft_itoa(major(stats->st_rdev)), info->major_spacing + 1);
		write(1, ", ", 2);
		ls_print_sp_left(ft_itoa(minor(stats->st_rdev)), info->minor_spacing);
	}
	else
		ls_print_sp_left(ft_itoa(stats->st_size), info->size_spacing);
}

void		ls_print_l(t_filedir *fldr)
{
	t_l_info	*info;

	info = get_set_l_info(NULL);
	ls_print_permissions(fldr->stats->st_mode, fldr->link, fldr->path);
	ls_print_sp_left(ft_itoa(fldr->stats->st_nlink), info->link_spacing);
	ls_print_sp_right(uid_to_name(fldr->stats->st_uid), info->user_spacing);
	ls_print_sp_right(gid_to_name(fldr->stats->st_gid), info->group_spacing);
	ls_print_size(info, fldr->stats);
	ls_print_time(&fldr->stats->st_mtime);
	if (!getpwuid(fldr->stats->st_uid) && getgrgid(fldr->stats->st_gid))
		ft_putstr(fldr->path);
	else
		ft_putstr(fldr->name);
	if (fldr->link != NULL)
	{
		write(1, " -> ", 4);
		ft_putstr(fldr->link);
	}
	write(1, "\n", 1);
}
