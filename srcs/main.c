/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:13:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/11/30 14:05:34 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <stdio.h>

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
	t_stat			*temp_stat;
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
	stats = NULL;
	temp_stat = NULL;
	while (i < listsize)
	{
		//When a 'directory' fails to open, write error
		if (stat(list[i], temp_stat) == -1)
			ls_perror(list[i]);
		else if (!stats)
			stats = arraylist(temp_stat, listsize);
		else
			stats->push(stats, temp_stat);
		i++;
	}

	//Pass to ls_gen
	// ls_gen(options, stats);
	return (0);
}
