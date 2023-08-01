/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:55:24 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/20 16:15:21 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_export(char **cmd_args, t_env *head)
{
	size_t	i;

	i = 0;
	if (ft_strchr(cmd_args[i], '=') != NULL)
}
