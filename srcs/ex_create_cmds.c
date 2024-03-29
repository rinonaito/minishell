/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_create_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:37:00 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/05 23:54:04 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//@func: free cmd_args used for executing commands
char	**free_args(char **argv)
{
	char	**p;
	int		i;

	if (!argv)
		return (NULL);
	p = argv;
	i = 0;
	while (p[i])
	{
		free(p[i]);
		p[i] = NULL;
		i++;
	}
	free(argv);
	argv = NULL;
	return (NULL);
}

//@func: count the number of parameters
static int	count_num_params(t_tree *root)
{
	int			num;
	t_token		*temp;

	temp = root->param;
	num = 0;
	while (root->param != NULL && root->param->type != TK_PIPE)
	{
		if (root->param->type != TK_WORD)
			root->param = root->param->next->next;
		else
		{
			root->param = root->param->next;
			num ++;
		}
	}
	root->param = temp;
	return (num);
}

static void	for_word_token(char **cmd_args, int *i, t_token **param)
{
	cmd_args[*i] = ft_strdup((*param)->token);
	if (cmd_args[*i] == NULL)
		ft_perror("malloc");
	(*param) = (*param)->next;
	(*i)++;
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
	num_param = count_num_params(root);
	cmd_args = malloc(sizeof(char *) * (num_param + 1));
	if (!cmd_args)
		return (NULL);
	i = 0;
	while (root->param != NULL && root->param->type != TK_PIPE)
	{
		if (root->param->type != TK_WORD)
			root->param = root->param->next->next;
		else
			for_word_token(cmd_args, &i, &(root->param));
	}
	cmd_args[i] = NULL;
	root->param = temp;
	return (cmd_args);
}
