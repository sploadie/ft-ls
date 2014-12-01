/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:13:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/01 12:24:10 by tgauvrit         ###   ########.fr       */
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
	//For iterator
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;

	//Print recieved filedirs (current dir)
	ls_print(options, filedirs);
	//Set dir iterator
	dirs = ls_dirs(filedirs);
	iter = arlst_iter(dirs);
	//For option -r, make iter->pip = iter->pop
	if (ft_strchr(options, 'r'))
		iter->pip = iter->pop;
	//Then, for each dir in filedirs:
	iter_ret = 1;
	while (iter_ret)
	{
		temp_filedir = iter->pip(iter, &iter_ret);
		//Print "\n[dirname]:\n"
		write(1, "\n\n", 2);
		ft_putstr(temp_filedir->name);
		write(1, ":\n", 2);
		//Recurse ls_buckle with filedirs from ls_gen_filedirs
		ls_buckle(options, ls_gen_filedirs(temp_filedir->dir));
	}
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
	if (!listsize)
	{
		//If none skip to ls_buckle with filedirs from ls_gen_filedirs of '.'//FIXME
	}
	else
	{
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
	}
	if (!ft_strchr(options, 'R'))
		ls_print(options, filedirs);//If no -R, print and you're done!
	else
		ls_buckle(options, filedirs);//Otherwise, pass to ls_buckle
	return (0);
}
