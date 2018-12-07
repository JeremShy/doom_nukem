#include <editor.h>
#include <png.h>

void	create_leaf(struct s_tree *node, struct s_length_code code)
{
	struct	s_tree			*new;

	if (code.length == 0)
	{
		node->l = NULL;
		node->r = NULL;
		node->symbol = code.symbol;
		return ;
	}
	if (code.code & (1 << (code.length - 1)))
	{
		code.length--;
		if (node->r)
				new = node->r;
		else
		{
			new = malloc(sizeof(struct s_tree));
			new->l = NULL;
			new->r = NULL;
			node->r = new;
		}
		create_leaf(new, code); 
	}
	else
	{
		code.length--;
		if (node->l)
				new = node->l;
		else
		{
			new = malloc(sizeof(struct s_tree));
			new->l = NULL;
			new->r = NULL;
			node->l = new;
		}
		create_leaf(new, code); 
	}
}

struct s_tree	*create_tree(struct s_length_code *codes, size_t s)
{
	size_t					i;
	struct	s_tree			*tree;

	i = 0;
	tree = malloc(sizeof(struct s_tree));
	tree->l = NULL;
	tree->r = NULL;
	while (i < s)
	{
		if (codes[i].length != 0)
		{
			create_leaf(tree, codes[i]);
		}
		i++;
	}
	return (tree);
}
