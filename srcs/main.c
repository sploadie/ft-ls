/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:13:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/11/30 18:00:26 by tgauvrit         ###   ########.fr       */
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

t_arraylist	*ls_dirs(t_arraylist *filedirs)
{
	t_arraylist		*dirs;
	//For iterator
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;
	//For printing
	size_t			max_name;

	max_dirname = 0;
	max_filename = 0;
	dirs = NULL;
	files = NULL;
	iter_ret = 1;
	while (iter_ret > 0)
	{
		temp_filedir = 
	}
	(void)iter_ret;
	(void)iter;
	//Get filedirs
	return (filedirs);
}

t_arraylist	*ls_gen_filedirs(DIR *dir)
{
	t_arraylist		*filedirs;

	//Get filedirs
	return (filedirs);
}

void	ls_l_lines(t_arraylist *filedirs)
{
	;
}

void	ls_print(t_arraylist *filedirs, char *options)
{
	//  For option -r, make iter->pip = iter->pop
	;//man 4 tty
}

void		ls_buckle(char *options, t_arraylist *filedirs)
{
	//For looping
	t_arraylist		*dirs;

	//Print recieved filedirs (current dir)
	//Then, for each dir in filedirs
	//  Print "\n[dirname]:\n"
	//  Recurse ls_buckle with filedirs from ls_gen_filedirs
	//  For option -r, make iter->pip = iter->pop
}

int			main(int argc, char **argv)
{
	int				i;
	char			*options;
	//To grab list at first
	char			**list;
	int				listsize;
	//Temporary DIR* holder
	t_filedir		*temp_filedir;
	//For arraylist
	t_arraylist		*filedirs;

	//DEV//FIXME
	// ft_putstr(argv[0]);//FIXME
	// ft_putchar('\n');//FIXME
	//DEV//FIXME

	//Find options
	options = check_malloc(ft_strnew(0));
	i = 1;
	while (i < argc && isoption(argv[i]))
		ft_strjoinfree(&options, argv[i++] + 1);

	//Check if options are valid
	check_options(options);

	//Get filedir names
	list = argv + i;
	listsize = argc - i;
	//If none skip to ls_buckle with filedirs from ls_gen_filedirs of '.'//FIXME

	//Sort filedir names
	ft_sort_string_array(list, listsize);

	//Open each 'directory'
	i = 0;
	filedirs = NULL;
	while (i < listsize)
	{
		//When a 'directory' fails to open, write error
		if ((temp_filedir = filedir(list[i])))
		{
			if (!filedirs)
				filedirs = check_malloc(arraylist(temp_filedir, listsize));
			else
				filedirs->push(filedirs, temp_filedir);//Check malloc here too...
		}
		i++;
	}

	//Pass to ls_gen
	ls_buckle(options, filedirs);
	return (0);
}
