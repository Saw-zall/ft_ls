/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:18:25 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/04 14:38:07 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define TYPE_DEVICE 2 
# define TYPE_DIR    4 
# define TYPE_FILE   8 
# define TYPE_LINK_S 10

#include "libft.h"
#include "catch_errors.h"
#include "toolkit.h"
#include <dirent.h>

int		ft_ls(char *params, char **entity);
void	get_args(int ac, char **av, char **ret_params, char ***ret_paths);
void	check_params(char *params);
#endif
