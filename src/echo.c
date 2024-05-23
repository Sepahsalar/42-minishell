#include "../include/minishell.h"

t_env_pack	run_echo(t_cmd *cmd)
{
	t_env_pack	env_pack;
	char		**arg;
	int			index;
	char		c;

	env_pack = init_env_pack(cmd);
	arg = cmd->args;
	index = 1;
	c = '\n';
	if (same(arg[1], "-n"))
	{
		index = 2;
		c = '\0';
	}
	while (arg[index])
	{
		printf("%s", arg[index]);
		if (arg[index + 1])
			printf(" ");
		index++;
	}
	printf("%c", c);
	env_pack.original_env = export_original(cmd->original_env, 0);
	return (env_pack);
}
