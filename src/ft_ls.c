/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:16:18 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/22 11:51:52 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
/*
static DIR				**open_dirs(char **path)
{
	size_t nb_path;
	DIR **dirs;
	DIR *cur_dir;
	size_t i;
	int cp_d;

	nb_path = 0;
	i = 0;
	cp_d = 0;
	cur_dir = NULL;
	nb_path = size_tab(path);
	dirs = (DIR **)malloc(sizeof(DIR *) * nb_path);
	while (i < nb_path)
	{
		cur_dir = opendir(path[i]);
		if (!cur_dir)
			catch_error(1, path[i]);
		else
			dirs[cp_d++] = cur_dir;
		i++;
	}
	return (dirs);
}
*/
static DIR				**open_dirs(char **path)
{
	size_t nb_path;
	DIR **dirs;
	DIR *cur_dir;
	size_t i;
	int cp_d;

	nb_path = 0;
	i = 0;
	cp_d = 0;
	cur_dir = NULL;
	nb_path = size_tab(path);
	dirs = (DIR **)malloc(sizeof(DIR *) * nb_path);
	while (i < nb_path)
	{
		cur_dir = opendir(path[i]);
		if (!cur_dir)
			catch_error(1, path[i]);
		else
			dirs[cp_d++] = cur_dir;
		i++;
	}
	return (dirs);
}

static void				check_params(char *params)
{
	char	*supported_params;
	int		i;

	i = 0;
	supported_params = ft_strdup("la");
	while (params[i] != 0)
	{
		if (!ft_strchr(supported_params, params[i]))
			error_params(supported_params, params[i]);
		i++;
	}
	free(supported_params);
}

//static struct dirent	**list_dir()

int						ft_ls(char *params, char **path)
{
	struct	dirent **items;
	DIR		**cur_dir;
	//struct stat *ret;
	int		i;

	cur_dir = NULL;
	items = NULL;
	i = 0;
	if (params)
		check_params(params);
	if (!path)
	{
		cur_dir = (DIR **)malloc(sizeof(DIR *));
		items = (struct dirent **)malloc(sizeof(struct dirent*));
		*cur_dir = opendir(".");
		while ((*items = readdir(*cur_dir)) && *items != NULL)
		{
			printf("%hu : %d  %s\n", (*items)->d_reclen, (*items)->d_type, (*items)->d_name);
		}
	}
	else
	{
		cur_dir = open_dirs(path);
	}
	return (1);

}
