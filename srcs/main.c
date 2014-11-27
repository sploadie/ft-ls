/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:13:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/11/27 17:30:24 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <stdio.h>

void	ls_perror(char *s)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(s);
}

int		isoption(char *str)
{
	if (!str || !(str[0] == '-' && str[1] != '\0'))
		return (0);
	return (1);
}

void	check_options(char *options)
{
	while (*options != '\0' && ft_strchr(OPTIONS, *options))
		options++;
	if (*options != '\0')
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(*options, 2);
		ft_putstr_fd("\nusage: ft_ls [-", 2);
		ft_putstr_fd(OPTIONS, 2);
		ft_putstr_fd("] [file ...]\n", 2);
		exit(1);
	}
}

void	ft_sort_string_array(char **string_array, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(string_array[j], string_array[j + 1]) > 0)
			{
				temp = string_array[j];
				string_array[j] = string_array[j + 1];
				string_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return ;
}

void	*check_malloc(void *ret)
{
	if (ret)
		return (ret);
	ls_perror(NULL);
	exit(1);
}

void	ft_strjoinfree(char **line, char *add)
{
	char	*to_free;

	to_free = *line;
	*line = ft_strjoin(*line, add);
	check_malloc(*line);
	free(to_free);
}

	//Split into files/dirs and options
	//Run through/set options
	//Throw error and exit if bad options

	//-l -R -a -r -t

	//-a : Include directory entries whose names begin with a dot (.).

	//-l : (The lowercase letter ``ell''.)  List in long format. (See below.)
	//		If the output is to a terminal, a total sum for all the file sizes is
	//		output on a line before the long listing.

	//-R : Recursively list subdirectories encountered.

	//-r : Reverse the order of the sort to get reverse lexicographical order or
	//		the oldest entries first (or largest files last, if combined with sort
	//		by size.)

	//-t : Sort by time modified (most recently modified first) before sorting the
	//		operands by lexicographical order.

// void	ls_files(char *options, t_arraylist *files)
// {

// }

// void	ls_dirs(char *options, t_arraylist *dirs)
// {

// }

// void	ls_gen(char *options, t_arraylist *stats)
// {
// 	//For arraylists
// 	t_arraylist	*dirs;
// 	t_arraylist	*files;
// 	//For iterator
// 	t_arlst_iter	*iter;
// 	int				iter_ret;
// 	//For printing
// 	size_t			max_filename;
// 	size_t			max_dirname;

// 	max_dirname = 0;
// 	max_filename = 0;
// 	(void)iter_ret;
// 	(void)iter;
// }

int		main(int argc, char **argv)
{
	int				i;
	char			*options;
	//To grab list at first
	char			**list;
	int				listsize;
	//Temporary DIR* holder
	struct stat		*temp_stat;
	//For arraylist
	t_arraylist		*stats;

	//Find options
	options = check_malloc(ft_strnew(0));
	i = 1;
	while (i < argc && isoption(argv[i]))
		ft_strjoinfree(&options, argv[i++] + 1);

	//Check if options are valid
	check_options(options);

	//Sort 'directories'
	list = argv + i;
	listsize = argc - i;
	ft_sort_string_array(list, listsize);

	//Open each 'directory'
	i = 0;
	temp_stat = NULL;
	while (i < listsize)
	{
		//When a 'directory' fails to open, write error
		if (stat(list[i], temp_stat) == -1)
			ls_perror(list[i]);
		else
		{
			stats = arraylist(temp_stat, listsize);
			break;
		}
		i++;
	}
	while (i < listsize)
	{
		//When a 'directory' fails to open, write error
		if (stat(list[i], temp_stat) == -1)
			ls_perror(list[i]);
		else
			stats->push(stats, temp_stat);
		i++;
	}

	//Pass to ls_gen
	// ls_gen(options, stats);
	return (0);
}
