/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_unlink_heredoc_files.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:54:30 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/05 21:36:52 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_temp_files(t_token *temp_files)
{
	t_token	*temp;

	while (temp_files != NULL)
	{
		unlink(temp_files->token);
		temp = temp_files;
		free (temp_files->token);
		temp_files->token = NULL;
		free (temp_files);
		temp_files = temp->next;
	}
}
