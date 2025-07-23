#include "minishell.h"

int	command_dispatch(t_commande *cmd_list, char **env)
{
	if (!cmd_list || !cmd_list->args || !cmd_list->args[0])
		return (0);

	identify_cmd_type(cmd_list);
	if(!cmd_list->next)
	{
		if (cmd_list->type == CMD_BUILTIN)
			//exec builtin(cmd_list)
		else if (cmd_list->type == CMD_SIMPLE)
			exec_cmd(cmd_list, env);
		else if (cmd_list->type == CMD_ABSOLUTE)
			// exec absolute cmd
		else if (cmd_list->type == CMD_RELATIVE)
			// exec RELATIVE cmd
		else
			//??
	}
}

int	exec_singe_cmd(t_commande *cmd_list, char **env, int i)
{
	char	*cmd_path;

	if (!cmd_list || !cmd_list->args)
		return (1);
	cmd_path = create_full_path(cmd_list, i);
	if (!cmd_path)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(cmd_list->args[0], 2);
		ft_putstr_fd(CMD_NOT_FOUND"\n", 2); // ajouter l'input de l'user "xx: command not found"
		return (127);
	}
	execve(cmd_path, cmd_list->args[i], env);
	perror(cmd_list->args[0]);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

int	exec_pipeline(t_commande *cmd_list, char **env)
{
 // a faire
}

int	execute(t_commande *cmd_list, char	**env)
{
	if (!cmd_list->args)
		return (0);
	if (cmd_list->args->next == NULL)
		return(exec_cmd(cmd_list, env), 0);
	else if(cmd_list->args->next != NULL)
		return (exec_cmd(cmd_list, env), 0);
	return (0);
}