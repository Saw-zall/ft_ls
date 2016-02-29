/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:45:47 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/29 10:12:07 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toolkit.h"
#include "ft_ls.h"
#include "libft.h"
#include "t_dir_content.h"
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>

void	realloc_dirent(struct dirent ***props, size_t size)
{
	struct dirent	**new;
	int				size_tab;
	int				i;

	new = NULL;
	size_tab = 0;
	if (*props)
		while ((*props)[size_tab] != 0)
		{
			size_tab++;
		}
	new = (struct dirent **)malloc(sizeof(struct dirent *) *
			(size_tab + size + 1));
	if (!new)
	{
		sleep(10);
	}
	new[size_tab + size] = NULL;
	i = -1;
	while (++i < size_tab)
		new[i] = (*props)[i];
	free(*props);
	*props = new;
}

char	*ft_join_paths(char *path, char *filename)
{
	char *tmp;
	char *ret;

	tmp = ft_strjoin(path, filename);
	ret = ft_strjoin(tmp, "/");
	free(tmp);
	return (ret);
}

int		is_exec_file(mode_t mode)
{
	if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH)
		return (1);
	return (0);
}

int		is_archive_file(char *filename)
{
	if (ft_strstr(filename, ".tar"))
		return (1);
	else if (ft_strstr(filename, ".zip"))
		return (1);
	else if (ft_strstr(filename, ".deb"))
		return (1);
	else if (ft_strstr(filename, ".rpm"))
		return (1);
	else
		return (0);
}

void	realloc_dir(DIR ***dirs, size_t size)
{
	DIR				**new;
	int				size_tab;
	int				i;

	new = NULL;
	size_tab = 0;
	if (*dirs)
		while ((*dirs)[size_tab] != 0)
		{
			size_tab++;
		}
	new = (DIR **)malloc(sizeof(DIR *) *
			(size_tab + size + 1));
	new[size_tab + size] = NULL;
	i = -1;
	if (dirs)
		while (++i < size_tab)
			new[i] = (*dirs)[i];
	free(*dirs);
	*dirs = new;
}

int		is_meta_dir(char *dir_name)
{
	if (ft_strcmp(dir_name, ".") != 0
			&& ft_strcmp(dir_name, "..") != 0)
		return (0);
	return (1);
}
