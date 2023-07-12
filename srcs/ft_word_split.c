/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_work_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:19:01 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/12 14:02:25 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	*ft_consume_ifs(char **old, char *ifs)
{
	char	*start;
	if (ft_strchr(ifs, ' ') != NULL)
		start = ft_skip_char(*old, ' ');
	if (ft_strchr(ifs, '\t') != NULL)
		start = ft_skip_char(*old, '\t');

}

void	ft_check_ifs(t_tree *root)
{
	char	*ifs;
	char	*new;

	ifs = getenv(IFS);
	if (IFS == NULL)
		ifs = " \t\n";
	while (root->param != NULL)
	{
		consumed = ft_consume_ifs(&(root->param->token), ifs);
		printf("root->param = %s\n", root->param->token);
		root->param = root->param->next;
	}
}

void	ft_word_split(t_tree *root)
{
	if (root == NULL)
		return ;
	ft_word_split(root->l_leaf);
	ft_check_ifs(root);
}
