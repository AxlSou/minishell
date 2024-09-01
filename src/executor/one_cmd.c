#include "../../includes/minishell.h"

static char	*find_cmd(char **path, char *cmd)
{
	int	i;
	char	*cmd_joined;
	char	*aux;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	while (path[i])
	{
		aux = ft_strjoin(path[i], "/");
		cmd_joined = ft_strjoin(aux, cmd);
		if (access(cmd_joined, F_OK | X_OK) == 0)
		{
			free(aux);
			return (cmd_joined);
		}
		free(aux);
		free(cmd_joined);
		i++;
	}
	return (NULL);
}

void	one_cmd(t_msh *msh, char **env, t_cmd *cmd)
{
	// int		fd_in;
	// int		fd_out;
	char	*cmd_and_path;

	cmd_and_path = find_cmd(env, cmd->argv[0]);
	if (!cmd_and_path)
	{
		error_msh("Minishell: Command not found", msh, 127);
		return ;
	}
	if (msh->cmd->fd_in != 0)
		dup2(msh->cmd->fd_in, STDIN_FILENO);
	if (msh->cmd->fd_out != 1)
		dup2(msh->cmd->fd_out, STDOUT_FILENO);
	execve(cmd_and_path, msh->cmd->argv, msh->envp);
	free(cmd_and_path);
}
