/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 09:33:48 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/31 19:56:11 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ls_print_permissions(int mode, char *link)
{
	char		str[11];

	ft_strcpy(str, "----------");//    Default=no perms

	if (S_ISDIR(mode))	str[0] = 'd';//Directory
	if (S_ISLNK(mode))	str[0] = 'l';//Link
	if (link)			str[0] = 'l';//Link
	if (S_ISSOCK(mode))	str[0] = 's';//Socket
	if (S_ISFIFO(mode))	str[0] = 'p';//FIFO
	if (S_ISCHR(mode))	str[0] = 'c';//Char devices
	if (S_ISBLK(mode))	str[0] = 'b';//Block device

	if (mode & S_IRUSR)	str[1] = 'r';//3 bits for user
	if (mode & S_IWUSR)	str[2] = 'w';
	if (mode & S_IXUSR)	str[3] = 'x';

	if (mode & S_IRGRP)	str[4] = 'r';//3 bits for group
	if (mode & S_IWGRP)	str[5] = 'w';
	if (mode & S_IXGRP)	str[6] = 'x';

	if (mode & S_IROTH)	str[7] = 'r';//3 bits for other
	if (mode & S_IWOTH)	str[8] = 'w';
	if (mode & S_IXOTH)	str[9] = 'x';

    ft_putstr(str);
}

void	ls_print_time(time_t *clock)
{
	write(1, 4+ctime(clock), 7);
	if (*clock > time(NULL))
		write(1, 19+ctime(clock), 5);
	else if (*clock > (time(NULL) - ((2599000 + 43200 - 25000) * 6)))//2592000//2678400
		write(1, 11+ctime(clock), 5);
	else
		write(1, 19+ctime(clock), 5);
}

void	ls_print_spaced_left(char *str, size_t space)
{
	size_t	size;

	size = ft_strlen(str);
	while (space > size)
	{
		write(1, " ", 1);
		space--;
	}
	write(1, str, space);
}

void	ls_print_spaced_right(char *str, size_t space)
{
	size_t	size;

	size = ft_strlen(str);
	if (space < size)
		write(1, str, space);
	else
		write(1, str, size);
	while (space > size)
	{
		write(1, " ", 1);
		space--;
	}
}

void	ls_print_l(t_filedir *filedir)
{
	t_l_info	*info;

	info = get_set_l_info(NULL);
	ls_print_permissions(filedir->stats->st_mode, filedir->link);
	if (!filedir->link && listxattr(filedir->path, NULL, 0, 0) > 0)
		write(1, "@", 1);
	else if (filedir->link && listxattr(filedir->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		write(1, "@", 1);
	else
		write(1, " ", 1);//Add @ and + thing here! Still need '+' !
	write(1, " ", 1);
	ls_print_spaced_left(ft_itoa(filedir->stats->st_nlink), info->link_spacing);
	write(1, " ", 1);
	ls_print_spaced_right(uid_to_name(filedir->stats->st_uid), info->user_spacing);
	write(1, "  ", 2);
	ls_print_spaced_right(gid_to_name(filedir->stats->st_gid), info->group_spacing);
	write(1, "  ", 2);
	ls_print_spaced_left(ft_itoa(filedir->stats->st_size), info->size_spacing);
	// write(1, "  ", 1);//FIXME//DEBUG
	// ls_print_spaced_left(ft_itoa(filedir->stats->st_blocks), 5);//FIXME//DEBUG
	write(1, " ", 1);
	ls_print_time(&filedir->stats->st_mtime);
	write(1, " ", 1);
	if (!getpwuid(filedir->stats->st_uid) && getgrgid(filedir->stats->st_gid))
		ft_putstr(filedir->path);
	else
		ft_putstr(filedir->name);
	if (filedir->link != NULL)
	{
		write(1, " -> ", 4);
		ft_putstr(filedir->link);
	}
	write(1, "\n", 1);
}
