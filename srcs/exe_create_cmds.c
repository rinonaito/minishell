/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_create_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:37:00 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/12 01:39:09 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//@func: count the number of parameters
int		count_num_params(t_tree *root)
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


//@func: create 2D char array from the given parameters
char	**create_cmds(t_tree *root)
{
	t_token		*temp;
	char		**cmd_args;
	int			num_param;
	int			i;

	//printf("### %s:begin ###\n", __func__);
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
			return (NULL);//return (free_tab(cmd_args));
		}
		i++;
		root->param = root->param->next;
	}
	cmd_args[num_param] = NULL;
	root->param = temp;
	//printf("### %s:end ###\n", __func__);
	return (cmd_args);
}
