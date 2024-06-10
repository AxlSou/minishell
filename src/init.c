/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:38:09 by tanselmo          #+#    #+#             */
/*   Updated: 2024/06/10 18:05:36 by tanselmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_msh(char **envp, t_msh *msh)
{
	msh->env = get_env(envp);
	msh->cmd = NULL;
	msh->tokens = NULL;
	msh->fd_in = 0;
	msh->fd_out = 0;
	msh->flag = 0;
}

void	get_line(t_msh *msh)
{
	msh->line = readline(W"Min"RST RED"ish"RST W"ell% "RST);
	while (msh->line)
	{
		add_history(msh->line);
		if (msh->line[0] == '\0')
		{
			free(msh->line);
			msh->line = readline(W"Min"RST RED"ish"RST W"ell% "RST);
		}
		else
		{
			msh->tokens = set_tokens(msh->line);
			if (check_tokens(&msh->tokens))
			{
				if (get_cmd(msh))
				{
					printf("funciona todo correctamente\n");
				}
			}
			free_msh(msh);
			msh->line = readline(W"Min"RST RED"ish"RST W"ell% "RST);
		}
	}
}
