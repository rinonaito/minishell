/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:24 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/18 16:35:24 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int    builtin_echo(char **cmd_args)
{
    bool    new_line;
    int   	i;

	printf(">%s\n", __func__);
    new_line = true;
	if (!cmd_args || !cmd_args[0])
		return (0);
	i = 1;
    while (cmd_args[i])
    {
		//printf("\ni:%d,[%s]\n", i, cmd_args[i]);
		if (i == 1 && ft_strequ(cmd_args[1], "-n"))
		{
        	new_line = false;
			i++;
			continue ;
		}
        printf("%s", cmd_args[i]);
        if (cmd_args[i + 1])
			printf(" ");
		i++;
    }
    if (new_line)
        printf("\n");
    return (0);
}
//*/

/*
int main(int argc, char **argv)
{
	t_token *list;
	t_token *store;
	t_token *temp;
	char	str[] = "hello";
	char	ok[] = "ok";
	int		i;

	list = malloc(sizeof(t_token));
	store = list;
	temp = list;
	i = 5;
	while (i--)
	{
		printf("i:%d\n", i);
		list->word = str;
		list->next = malloc(sizeof(t_token));
		if (!list->next)
			break ;
		list = list->next;
		list->next = NULL;
	}
	list->word = ok;
	printf("====\n");
	//list->next = NULL;
	//while (store)// && i++ < 4)
	while (store)//i++ < 4)
	{
		printf("i:%d,%p,[%s]\n", i, store, store->word);
		//printf("i:%d,%p ", i, store);
		//printf("[%s]\n", store->word);
		store = store->next;
		if (!store)
			printf("store null\n");
		//printf("*\n");
	}
	
	if (argc == 1)
		return (1);		
	printf("###\n");
	builtin_echo(temp);	
	
	return (0);	
}
*/
