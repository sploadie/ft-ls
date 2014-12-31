/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:13:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/31 20:01:49 by tgauvrit         ###   ########.fr       */
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
	t_filedir		*temp_filedir;

	// ft_putendl("Hm...");//FIXME//DEBUG//GDB
	// ft_putnbr(filedirs->size(filedirs));//FIXME//DEBUG//GDB
	iter = arlst_iter(filedirs);
	iter_ret = 1;
	while (iter_ret > 0)
	{
		temp_filedir = iter->pop(iter, &iter_ret);
		if (temp_filedir != NULL)
		{
			// ft_putstr("Deleting: ");//FIXME//DEBUG//GDB
			// ft_putendl(temp_filedir->name);//FIXME//DEBUG//GDB
			del_filedir(temp_filedir);
		}
	}
	free(iter);
	// ft_putendl("Poof.");//FIXME//DEBUG//GDB
	filedirs->del(filedirs);
	// ft_putendl("Nope.");//FIXME//DEBUG//GDB
}

int			ls_filedir_cmp(t_filedir *fd1, t_filedir *fd2)
{
	// if (!fd1 || !fd2)//FIXME//DEBUG
	// 	ft_putendl("BOOM!");//FIXME//DEBUG
	// ft_putstr(fd1->path);//FIXME//DEBUG
	// ft_putstr(" =?= ");//FIXME//DEBUG
	// write(1, fd2->name, 9);//FIXME//DEBUG//GDB
	// ft_putendl(" <>");//FIXME//DEBUG//GDB
	return (ft_strcmp(fd1->name, fd2->name));
}

int			ls_filedir_t_cmp(t_filedir *fd1, t_filedir *fd2)
{
	if (fd1->stats->st_mtime < fd2->stats->st_mtime)
		return (1);
	else if (fd1->stats->st_mtime == fd2->stats->st_mtime)
		return (ft_strcmp(fd1->name, fd2->name));
	else
		return (0);
}

t_arraylist	*ls_dirs(char *options, t_arraylist *filedirs)
{
	t_arraylist		*dirs;
	//For iterator
	DIR				*temp_dir;
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
		// (void)options;
		if (!S_ISDIR(temp_filedir->stats->st_mode))
		{
			if (!(temp_dir = opendir(temp_filedir->path)))
				continue;
			closedir(temp_dir);
			if (ft_strchr(options, 'l'))
				continue;
		}
		if (!dirs)
			dirs = check_malloc(arraylist(temp_filedir, filedirs->size(filedirs)));
		else
			dirs->push(dirs, temp_filedir);//Should check malloc here too...
	}
	free(iter);
	//Return collected directories
	return (dirs);
}

t_arraylist	*ls_files(t_arraylist *filedirs)
{
	t_arraylist		*files;
	//For iterator
	DIR				*temp_dir;
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
		if (!(temp_dir = opendir(temp_filedir->path)))
		{
			if (!files)
				files = check_malloc(arraylist(temp_filedir, filedirs->size(filedirs)));
			else
				files->push(files, temp_filedir);//Should check malloc here too...
		}
		else
			closedir(temp_dir);
	}
	free(iter);
	//Return collected directories
	return (files);
}

t_arraylist	*ls_gen_filedirs(char *options, t_filedir *origin_filedir)
{
	t_arraylist		*filedirs;
	DIR				*curr_dir;
	t_dirent		*dir_entry;
	char			*root;
	char			*full_path;

	curr_dir = opendir(origin_filedir->path);
	if (!curr_dir)
	{
		ls_perror(origin_filedir->name);
		return (NULL);
	}
	root = ft_strjoin(origin_filedir->path, "/");
	//Get filedirs
	filedirs = NULL;
	while ((dir_entry = readdir(curr_dir)) != NULL)
	{
		// ft_putendl(dir_entry->d_name);//FIXME//DEBUG//GDB
		full_path = ft_strjoin(root, dir_entry->d_name);
		if (!filedirs)
			filedirs = check_malloc(arraylist(filedir(full_path), DIR_BUF));
		else
			filedirs->push(filedirs, filedir(full_path));//Check malloc here too...
		// ft_putendl("(X)(.)(.)(.)");//FIXME//DEBUG//GDB
		free(full_path);
		// ft_putendl("(.)(X)(.)(.)");//FIXME//DEBUG//GDB
	}
	closedir(curr_dir);
	// ft_putendl("(.)(.)(X)(.)");//FIXME//DEBUG//GDB
	if (ft_strchr(options, 't'))
		filedirs->sort(filedirs, ls_filedir_t_cmp);
	else
		filedirs->sort(filedirs, ls_filedir_cmp);
	// ft_putendl("(.)(.)(.)(X)");//FIXME//DEBUG//GDB
	free(root);
	// ft_putendl("=========================");//FIXME//DEBUG//GDB
	return (filedirs);
}

void	ls_print(char *options, t_arraylist *filedirs)//man 4 tty
{
	//For iterator
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;

	// ft_putendl("@-->");//FIXME//DEBUG
	if (!filedirs)
		return ;
	if (ft_strchr(options, 'l') || ft_strchr(options, 'F'))
		ls_l_prepare(options, filedirs);
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
		{
			if (ft_strchr(options, 'l'))
				ls_print_l(temp_filedir);
			else
				ft_putendl(temp_filedir->name);
		}
	}
	free(iter);
	// ft_putendl("<--@");//FIXME//DEBUG
}

void		ls_loop(char *options, t_arraylist *filedirs, char dots)
{
	//For looping
	t_arraylist		*dirs;
	//For iterator
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;

	// ft_putendl("@-->");//FIXME//DEBUG
	//If no files where found in this dir, do nothing~
	if (!filedirs)
		return ;
	//Set dir iterator
	dirs = ls_dirs(options, filedirs);
	//No dirs, no iterate!
	if (!dirs)
	{
		// ft_putendl("No dirs!");//FIXME//DEBUG//GDB
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
			if (!ft_strchr(options, '^'))
				write(1, "\n", 1);
			else
				*(ft_strchr(options, '^')) = '\0';
			ft_putstr(temp_filedir->path);
			write(1, ":\n", 2);
			//Recurse ls_buckle with filedirs from ls_gen_filedirs
			ls_buckle(options, ls_gen_filedirs(options, temp_filedir));
		}
		else if (ft_strchr(options, 'R'))
			ls_loop(options, ls_gen_filedirs(options, temp_filedir), 0);
	}
	free(iter);
	// ft_putendl("Dirs!");//FIXME//DEBUG//GDB
	dirs->del(dirs);
	// ft_putendl("Filedirs!");//FIXME//DEBUG//GDB
	del_filedir_arlst(filedirs);//THIS NEEDS TO BE FIXED!!!
	// ft_putendl("<--@");//FIXME//DEBUG
}

void		ls_buckle(char *options, t_arraylist *filedirs)
{
	// ft_putendl("$-->");//FIXME//DEBUG
	//If no files where found in this dir, do nothing~
	if (!filedirs)
		return ;
	//Print recieved filedirs (current dir)
	ls_print(options, filedirs);
	//Send to loop to loop through dirs
	if (ft_strchr(options, 'R'))
		ls_loop(options, filedirs, 0);
	// ft_putendl("<--$");//FIXME//DEBUG
}

void		ls_first(char *options, t_arraylist *filedirs)
{
	t_arraylist	*files;
	char		*do_l;

	files = ls_files(filedirs);
	if (files)
	{
		do_l = ft_strchr(options, 'l');
		if (do_l)
			*do_l = 'F';
		ls_print(options, files);
		if (filedirs->size(filedirs) > files->size(files))
			write(1, "\n", 1);
		files->del(files);
	}
	ft_strjoinfree(&options, "^");
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
	DIR				*temp_dir;
	t_filedir		*temp_filedir;
	//For arraylist
	t_arraylist		*filedirs;

	// ft_putendl(argv[0]);//FIXME//DEBUG
	// time_t	six_months_ago;//FIXME//DEBUG
	// six_months_ago = time(NULL) - ((2599000 + 43200 - 15000) * 6);//FIXME//DEBUG
	// write(1, ctime(&six_months_ago), 25);//FIXME//DEBUG
	// write(1, "\n", 1);//FIXME//DEBUG
	// if (opendir("./my_ls_test/f1"))//FIXME//DEBUG
	// 	ft_putstr_fd("You!", 2);//FIXME//DEBUG
	// ft_putstr_fd(readdir(opendir("./.git/refs/heads"))->d_name, 2);//FIXME//DEBUG

	// ft_putchar('@');//FIXME//DEBUG
	//Find options
	options = check_malloc(ft_strnew(0));
	i = 1;
	while (i < argc && isoption(argv[i]))
		ft_strjoinfree(&options, argv[i++] + 1);

	if (i < argc && ft_strcmp(argv[i], "--") == 0)
		i++;

	// ft_putchar('@');//FIXME//DEBUG
	//Check if options are valid
	check_options(options);

	// ft_putchar('@');//FIXME//DEBUG
	//Get filedir names
	list = argv + i;
	listsize = argc - i;
	if (listsize < 1)
	{
		// ft_putchar('$');//FIXME//DEBUG
		//If none skip to ls_buckle with filedirs from ls_gen_filedirs of '.'
		temp_filedir = filedir(".");
		//Bad filename? End of the line.
		if (!temp_filedir)
			return (0);
		// ft_putchar('#');//FIXME//DEBUG
		filedirs = ls_gen_filedirs(options, temp_filedir);
		// ft_putchar('#');//FIXME//DEBUG
		//Delete temporary filedir
		del_filedir(temp_filedir);
		//Move on
		if (ft_strchr(options, 'R'))
			ls_buckle(options, filedirs);
		else
			ls_print(options, filedirs);
	}
	else if (listsize == 1)
	{
		// ft_putchar('$');//FIXME//DEBUG
		//If none skip to ls_buckle with filedirs from ls_gen_filedirs of '.'
		temp_filedir = filedir(*list);
		//Bad filename? End of the line.
		if (!temp_filedir)
			return (0);
		// ft_putchar('$');//FIXME//DEBUG
		if (S_ISDIR(temp_filedir->stats->st_mode))
		{
			filedirs = ls_gen_filedirs(options, temp_filedir);
			//Delete temporary filedir
			del_filedir(temp_filedir);
		}
		else if ((temp_dir = opendir(temp_filedir->path)))
		{
			closedir(temp_dir);
			filedirs = ls_gen_filedirs(options, temp_filedir);
			//Delete temporary filedir
			del_filedir(temp_filedir);
		}
		else
		{
			filedirs = check_malloc(arraylist(temp_filedir, 1));
			if (ft_strchr(options, 'l'))
				*(ft_strchr(options, 'l')) = 'F';
		}
		// ft_putchar('$');//FIXME//DEBUG 
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
			if ((temp_filedir = filedir(list[i])) != NULL)
			{
				if (!filedirs)
					filedirs = check_malloc(arraylist(temp_filedir, listsize));
				else
					filedirs->push(filedirs, temp_filedir);//Check malloc here too...
			}
			i++;
		}
		//Move on
		if (filedirs != NULL)
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
