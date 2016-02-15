/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:49:04 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/15 16:44:05 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "option_l.h"

static t_foo	*t_foo_new(char *str)
{
	t_foo *new;

	new = (t_foo *)malloc(sizeof(t_foo));
	if (new)
	{
		new->str = ft_strdup(str);
		new->next = NULL;
	}
	return (new);
}

static void		t_foo_push(t_foo **first, t_foo *new)
{
	t_foo *index;

	index = *first;
	if (!index)
		*first = new;
	else
	{
		while (index->next)
			index = index->next;
		index->next = new;
	}
}

static t_foo	*get_rights(mode_t mode)
{
	char *rights;

	rights = NULL;
	if (S_ISDIR(mode))
		rights = ft_strdup("d");
	else if (S_ISCHR(mode))
		rights = ft_strdup("c");
	else if (S_ISFIFO(mode))
		rights = ft_strdup("P");
	else if (S_ISLNK(mode))
		rights = ft_strdup("l");
	else if (S_ISSOCK(mode))
		rights = ft_strdup("s");
	else if (S_ISBLK(mode))
		rights = ft_strdup("b");
	else if (S_ISREG(mode))
		rights = ft_strdup("-");
	rights = ft_strjoin(rights, ((mode & S_IRUSR) ? "r" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IWUSR) ? "w" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IXUSR) ? "x" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IRGRP) ? "r" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IWGRP) ? "w" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IXGRP) ? "x" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IROTH) ? "r" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IWOTH) ? "w" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IXOTH) ? "x" : "-"));
	return (t_foo_new(rights));
}

static	int		count_elems(t_dir_item *item)
{
	int i;
	DIR	*cur_dir;

	i = 0;
	cur_dir = opendir(ft_strjoin(item->path, item->item_name));
	if (cur_dir)
		while (readdir(cur_dir))
			i++;
	else
		return (1);
	if (cur_dir)
		closedir(cur_dir);
	return (i);
}

/*
   ft_putstr(rights);
   i = count_elems(item);
   ft_putnbr(i);
   ft_putstr(getpwuid(item->prop.st_uid)->pw_name);
   ft_putstr(getgrgid(item->prop.st_gid)->gr_name);
   ft_putnbr(item->prop.st_size);
   ft_putstr(date[1]);
   ft_putstr(date[2]);
   */

static t_foo	*get_date(t_dir_item *item)
{
	char	**tmp;
	t_foo	*date;

	date = NULL;
	tmp = ft_strsplit(ctime(&item->prop.st_mtimespec.tv_sec), ' ');
	t_foo_push(&date, t_foo_new(tmp[1]));
	t_foo_push(&date, t_foo_new(tmp[2]));
	t_foo_push(&date, t_foo_new(ft_strsub(tmp[3], 0, 5)));
	ft_freetab(tmp);
	return (date);
}

static t_foo	*print_list_item(t_dir_item *item, int *total)
{
	t_foo	*line;
	int		i;

	i = 0;
	line = NULL;
	t_foo_push(&line, get_rights(item->prop.st_mode));
	t_foo_push(&line, t_foo_new(ft_itoa(count_elems(item))));
	t_foo_push(&line, t_foo_new(getpwuid(item->prop.st_uid)->pw_name));
	t_foo_push(&line, t_foo_new(getgrgid(item->prop.st_gid)->gr_name));
	t_foo_push(&line, t_foo_new(ft_itoa(item->prop.st_size)));
	t_foo_push(&line, get_date(item));
	t_foo_push(&line, t_foo_new(item->item_name));
	*(total) += (int)(item->prop.st_blocks);
	return (line);
}

static int		*max_size_elem(t_list *container)
{
	int		*spaces;
	t_foo	*index;
	int		i;
	size_t	cur;

	spaces = (int *)malloc(sizeof(int) * 10);
	ft_bzero(spaces, sizeof(int) * 10);
	i = 0;
	cur = 0;
	index = NULL;
	while (container)
	{
		index = container->content;
		i = 0;
		while (index)
		{
			cur = ft_strlen(index->str);
			if (spaces[i] <= (int)cur)
				spaces[i] = cur;
			index = index->next;
			i++;
		}
		container = container->next;
	}
	return (spaces);
}

void			print_ls_l(t_dir_item *items, char *params)
{
	int		*spaces;
	int		total;
	int		a;
	t_list	*container;
	t_foo	*index;

	container = NULL;
	total = 0;
	a = 0;
	if (ft_strchr(params, 'a'))
		a = 1;
	while (items)
	{
		if ((items->item_name[0] == '.' && a)
				|| items->item_name[0] != '.')
			ft_lstpush(&container,
					ft_lstnew(print_list_item(items, &total), sizeof(t_foo)));
		items = items->next;
	}
	ft_putstr("total ");
	ft_putnbr((total % 512));
	ft_putchar('\n');
	spaces = max_size_elem(container);
	index = NULL;
	while (container)
	{
		a = 0;
		index = container->content;
		while (index)
		{
			if (index->next && a != 0 && a != 2 && a != 3 && a != 5 && a != 7)
				ft_print_rep(' ', (spaces[a] - ft_strlen(index->str)));
			ft_putstr(index->str);
			if (index->next && a != 0 && a != 1 && a != 4 && a != 6)
				ft_print_rep(' ', (spaces[a] - ft_strlen(index->str)));
			if (index->next)
				ft_putchar(' ');
			index = index->next;
			a++;
		}
		container = container->next;
		ft_putchar('\n');
	}
}
