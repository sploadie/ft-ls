/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:13:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/03 20:26:28 by tgauvrit         ###   ########.fr       */
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

void		del_filedir_arlst(t_arraylist *filedirs)
{
	//For iterator
	t_arlst_iter	*iter;
	int				iter_ret;

	iter = arlst_iter(filedirs);
	iter_ret = 1;
	while (iter_ret > 0)
	{
		del_filedir(iter->pop(iter, &iter_ret));
	}
	free(iter);
	filedirs->del(filedirs);
}

int			ls_filedir_cmp(t_filedir *fd1, t_filedir *fd2)
{
	return (ft_strcmp(fd1->name, fd2->name));
}

t_arraylist	*ls_dirs(t_arraylist *filedirs)
{
	t_arraylist		*dirs;
	//For iterator
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;

	iter = arlst_iter(filedirs);
	dirs = NULL;
	//Collect dirs
	iter_ret = 1;
	while (iter_ret > 0)
	{
		temp_filedir = iter->pip(iter, &iter_ret);
		// ft_putstr("./my_ls_test/f1");//FIXME//DEBUG
		// ft_putstr(temp_filedir->path);//FIXME//DEBUG
		// if (opendir(temp_filedir->path) == NULL)//FIXME//DEBUG
		// if (opendir("./my_ls_test/f1") == NULL)//FIXME//DEBUG
		// if (S_ISDIR(temp_filedir->stats->st_mode))//FIXME//DEBUG
		// {//FIXME//DEBUG
			// ft_putendl(" isn't dir.");//FIXME//DEBUG
			// if (opendir(".") == NULL)
				// ft_putendl("SO ISN'T '.'???");//FIXME//DEBUG
		// }//FIXME//DEBUG
		// else//FIXME//DEBUG
		// {//FIXME//DEBUG
			// ft_putendl(" should be dir!");//FIXME//DEBUG
		// }//FIXME//DEBUG
		if (S_ISDIR(temp_filedir->stats->st_mode))
		{
			if (!dirs)
				dirs = check_malloc(arraylist(temp_filedir, filedirs->size(filedirs)));
			else
				dirs->push(dirs, temp_filedir);//Should check malloc here too...
		}
	}
	free(iter);
	//Return collected directories
	return (dirs);
}

t_arraylist	*ls_files(t_arraylist *filedirs)
{
	t_arraylist		*files;
	//For iterator
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;

	iter = arlst_iter(filedirs);
	files = NULL;
	//Collect files
	iter_ret = 1;
	while (iter_ret > 0)
	{
		temp_filedir = iter->pip(iter, &iter_ret);
		if (!S_ISDIR(temp_filedir->stats->st_mode))
		{
			if (!files)
				files = check_malloc(arraylist(temp_filedir, filedirs->size(filedirs)));
			else
				files->push(files, temp_filedir);//Should check malloc here too...
		}
	}
	free(iter);
	//Return collected directories
	return (files);
}

int		isdots(char *name)
{
	if (!ft_strcmp(".", name) || !ft_strcmp("..", name))
		return (1);
	return (0);
}

t_arraylist	*ls_gen_filedirs(t_filedir *origin_filedir)
{
	t_arraylist		*filedirs;
	DIR				*curr_dir;
	t_dirent		*dir_entry;
	char			*root;
	char			*full_path;

	curr_dir = opendir(origin_filedir->path);
	root = ft_strjoin(origin_filedir->path, "/");
	//Get filedirs
	filedirs = NULL;
	while ((dir_entry = readdir(curr_dir)))
	{
		// ft_putendl(dir_entry->d_name);//FIXME//DEBUG
		full_path = ft_strjoin(root, dir_entry->d_name);
		if (!filedirs)
			filedirs = check_malloc(arraylist(filedir(full_path), DIR_BUF));
		else
			filedirs->push(filedirs, filedir(full_path));//Check malloc here too...
		free(full_path);
	}
	closedir(curr_dir);
	filedirs->sort(filedirs, ls_filedir_cmp);
	free(root);
	// ft_putendl("=========================");//FIXME//DEBUG
	return (filedirs);
}

// void	ls_l_lines(t_arraylist *filedirs)
// {
// 	;
// }

int		show_entry(char *options, char *name)
{
	if (*name != '.')
		return (1);
	if (ft_strchr(options, 'a'))
		return (1);
	if (ft_strchr(options, 'A') && !isdots(name))
		return (1);
	return (0);
}

void	ls_print(char *options, t_arraylist *filedirs)//man 4 tty
{
	//For iterator
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;

	if (!filedirs)
		return ;
	iter = arlst_iter(filedirs);
	//For option -r, make iter->pip = iter->pop
	if (ft_strchr(options, 'r'))
		iter->pip = iter->pop;
	//Then, for each dir in filedirs:
	iter_ret = 1;
	while (iter_ret)
	{
		temp_filedir = iter->pip(iter, &iter_ret);
		//Check options for print or nay;
		if (show_entry(options, temp_filedir->name))
			ft_putendl(temp_filedir->name);

	}
	free(iter);
}

// //ORIGINAL
// void		ls_buckle(char *options, t_arraylist *filedirs)
// {
// 	//For looping
// 	t_arraylist		*dirs;
// 	//For iterator
// 	t_arlst_iter	*iter;
// 	int				iter_ret;
// 	t_filedir		*temp_filedir;

// 	//If no files where found in this dir, do nothing~
// 	if (!filedirs)
// 		return ;
// 	//Print recieved filedirs (current dir)
// 	ls_print(options, filedirs);
// 	//Set dir iterator
// 	dirs = ls_dirs(filedirs);
// 	iter = arlst_iter(dirs);
// 	//For option -r, make iter->pip = iter->pop
// 	if (ft_strchr(options, 'r'))
// 		iter->pip = iter->pop;
// 	//Then, for each dir in filedirs:
// 	iter_ret = 1;
// 	while (iter_ret)
// 	{
// 		temp_filedir = iter->pip(iter, &iter_ret);
// 		//Skip '.' and '..'
// 		if (isdots(temp_filedir->name))
// 			continue;
// 		//Print "\n[dirname]:\n"
// 		write(1, "\n", 1);
// 		ft_putstr(temp_filedir->name);
// 		write(1, ":\n", 2);
// 		//Recurse ls_buckle with filedirs from ls_gen_filedirs
// 		ls_buckle(options, ls_gen_filedirs(temp_filedir));
// 	}
// 	free(iter);
	// del_filedir_arlst(filedirs);
// 	// del_arraylist(dirs);//MAKE THIS//FIXME
// }

void		ls_loop(char *options, t_arraylist *filedirs, char dots)
{
	//For looping
	t_arraylist		*dirs;
	//For iterator
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;

	//If no files where found in this dir, do nothing~
	if (!filedirs)
		return ;
	//Set dir iterator
	dirs = ls_dirs(filedirs);
	//No dirs, no iterate!
	if (!dirs)
	{
		ft_putendl("No dirs!");//FIXME//DEBUG
		return ;
	}
	iter = arlst_iter(dirs);
	//For option -r, make iter->pip = iter->pop
	if (ft_strchr(options, 'r'))
		iter->pip = iter->pop;
	//Then, for each dir in filedirs:
	iter_ret = 1;
	while (iter_ret)
	{
		temp_filedir = iter->pip(iter, &iter_ret);
		//Skip '.' and '..'
		if (isdots(temp_filedir->name) && !dots)
			continue;
		if (show_entry(options, temp_filedir->name) || isdots(temp_filedir->name))
		{
			//Print "\n[dirname]:\n"
			write(1, "\n", 1);
			ft_putstr(temp_filedir->path);
			write(1, ":\n", 2);
			//Recurse ls_buckle with filedirs from ls_gen_filedirs
			ls_buckle(options, ls_gen_filedirs(temp_filedir));
		}
		else if (ft_strchr(options, 'R'))
			ls_loop(options, ls_gen_filedirs(temp_filedir), 0);
	}
	free(iter);
	del_filedir_arlst(filedirs);
}

void		ls_buckle(char *options, t_arraylist *filedirs)
{
	//If no files where found in this dir, do nothing~
	if (!filedirs)
		return ;
	//Print recieved filedirs (current dir)
	ls_print(options, filedirs);
	//Send to loop to loop through dirs
	if (ft_strchr(options, 'R'))
		ls_loop(options, filedirs, 0);
}

void		ls_first(char *options, t_arraylist *filedirs)
{
	t_arraylist	*files;

	files = ls_files(filedirs);
	ls_print(options, files);
	del_filedir_arlst(files);
	ls_loop(options, filedirs, 1);
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

	// ft_putendl(argv[0]);//FIXME//DEBUG
	// if (opendir("./my_ls_test/f1"))//FIXME//DEBUG
	// 	ft_putstr_fd("You!", 2);//FIXME//DEBUG
	// ft_putstr_fd(readdir(opendir("./.git/refs/heads"))->d_name, 2);//FIXME//DEBUG

	// ft_putchar('@');//FIXME//DEBUG
	//Find options
	options = check_malloc(ft_strnew(0));
	i = 1;
	while (i < argc && isoption(argv[i]))
		ft_strjoinfree(&options, argv[i++] + 1);

	// ft_putchar('@');//FIXME//DEBUG
	//Check if options are valid
	check_options(options);

	// ft_putchar('@');//FIXME//DEBUG
	//Get filedir names
	list = argv + i;
	listsize = argc - i;
	if (listsize < 2)
	{
		// ft_putchar('$');//FIXME//DEBUG
		//If none skip to ls_buckle with filedirs from ls_gen_filedirs of '.'
		if (listsize)
			temp_filedir = filedir(*list);
		else
			temp_filedir = filedir(".");
		//Bad filename? End of the line.
		if (!temp_filedir)
			return (0);
		// ft_putchar('$');//FIXME//DEBUG
		filedirs = ls_gen_filedirs(temp_filedir);
		// ft_putchar('$');//FIXME//DEBUG 
		//Delete temporary filedir
		del_filedir(temp_filedir);
		//Move on
		if (ft_strchr(options, 'R'))
			ls_buckle(options, filedirs);
		else
			ls_print(options, filedirs);
	}
	else
	{
		// ft_putchar('&');//FIXME//DEBUG
		//Sort filedir names
		ft_sort_string_array(list, listsize);

		// ft_putchar('&');//FIXME//DEBUG
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
		//Move on
		ls_first(options, filedirs);
	}
	// ft_putchar('@');//FIXME//DEBUG

	//Much to do:
	// ls -1R ~/my_ls_test
	// ls -1R ~/my_ls_test ~/my_ls_test/a
	// ls -1R ~/my_ls_test ~/my_ls_test/f1

	// del_filedir_arlst(filedirs);
	return (0);
}
