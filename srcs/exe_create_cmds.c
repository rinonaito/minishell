/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_create_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:37:00 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/16 18:30:57 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//@func: free cmd_args used for executing commands
static char	**free_args(char ***argv)
{
	char	**p;
	int		i;

	if (!argv)
		return (NULL);
	p = *argv;
	i = 0;
	while (p[i])
	{
		free(p[i]);
		p[i] = NULL;
		i++;
	}
	p = NULL;
	return (NULL);
}

//@func: count the number of parameters
static int		count_num_params(t_tree *root)
{
	int			num;
	t_token		*temp;

	temp = root->param;
	num = 0;
	while (root->param && root->param->type != TK_PIPE)
	{
		num++;
		root->param = root->param->next;
	}
	root->param = temp;
	return (num);
}

//prob. segf here when a space is entered
//@func: create 2D char array from the given parameters
char	**create_cmds(t_tree *root)
{
	t_token		*temp;
	char		**cmd_args;
	int			num_param;
	int			i;

	temp = root->param;
	num_param = count_num_params(root); //printf("num_param:%d\n", num_param);
	cmd_args = malloc(sizeof(char *) * (num_param + 1));
	if (!cmd_args)
		return (NULL);
	//
	i = 0;
	while (root->param && root->param->type != TK_PIPE)
	{
		cmd_args[i] = ft_strndup(root->param->token, ft_strlen(root->param->token));
		if (!cmd_args[i])
		{
			printf("!cmd_args[i]\n");
			return (free_args(&cmd_args));
		}
		i++;
		root->param = root->param->next;
	}
	cmd_args[num_param] = NULL;
	root->param = temp;
	return (cmd_args);
}
