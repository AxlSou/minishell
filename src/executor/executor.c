#include "../../includes/minishell.h"

static int	is_builtin(t_msh *msh, t_cmd *cmd)
{
	if (!ft_strncmp("cd", cmd->argv[0], 3))
		return (cd(msh), 0);
	if (!ft_strncmp("echo", cmd->argv[0], 5))
		return (ft_echo(msh, msh->cmd->fd_out), 0);
	if (!ft_strncmp("export", cmd->argv[0], 7))
		return (export(msh), 0);
	if (!ft_strncmp("unset", cmd->argv[0], 6))
		return (0);
	if (!ft_strncmp("pwd", cmd->argv[0], 4))
		return (ft_pwd(msh), 0);
	if (!ft_strncmp("exit", cmd->argv[0], 5))
		return (ft_exit(msh), 0);
	if (!ft_strncmp("env", cmd->argv[0], 4))
		return (ft_env(msh), 0);
	return (1);
}

void	one_cmd_handler(t_msh *msh)
{
	pid_t	pid;

	if (msh->cmd->error == 1)
		return ; /* Not finished */
	if (is_builtin(msh, msh->cmd) == 0)
		return ;
	pid = fork();
	if (pid < 0)
		error_msh("Error creating pid", msh, 0); /* Test return */
	if (pid == 0)
	{
		one_cmd(msh, msh->path, msh->cmd);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
}

void	executor(t_msh *msh)
{
	g_signal = 1;
	msh->path = get_path(msh);
	if (!msh->path)
		error_msh("Path not found", msh, 130);
	else if (msh->cmd_len == 1)
		one_cmd_handler(msh);
	else
		multiple_cmds(msh);
	g_signal = 0;
}
