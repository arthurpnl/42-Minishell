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
		else
			//exec cmd_list, envp
	}
}

int	exec_cmd(t_commande *cmd_list, char **env)
{
	char	*cmd_path;

	if (!cmd_list || !cmd_list->args)
		return (1);
	if (cmd_list->args[0][0] == '/')
	{
		if (access(cmd_list->args[0], X_OK) == 0)
			cmd_path = ft_strdup(cmd_list->args[0]);
	}
	else
	{

	}
}

int	exec_pipeline(t_commande *cmd_list, char **env)
{

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