#include "../../include/minishell.h"

void	print_node(t_node *node)
{
	if (node == NULL)
		return ;
	printf("%s", node->value);
	if (node->right != NULL)
		putchar(' ');
	print_node(node->right);
}

void	echo_command(t_node *commandNode)
{
	t_node	*argnode;
	int		newline;

	newline = 1;
	argnode = commandNode->left;
	while (argnode != NULL && strcmp(argnode->value, "-n") == 0)
	{
		newline = 0;
		argnode = argnode->right;
	}
	print_node(argnode);
	if (newline)
		putchar('\n');
}
