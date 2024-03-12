#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "libft.h"

int	w(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

void	strnesc(char *str, int len)
{
	if (!str || !*str || len < 0)
		return ;
	if (len > 0)
		while (--len >= 0)
			str[len] -= (str[len] >= 0) * 128;
	else
		strnesc(str, ft_strlen(str));
}

void	escape_quoted(char *str)
{
	static char	*quotes = "\'\"";
	char		*next;
	int			fk;

	fk = -1;
	while (str[++fk])
	{
		if (ft_strchr(quotes, str[fk]))
		{
			next = ft_strchr(str + fk + 1, str[fk]);
			if (!next)
			{
				printf("Error ! missing quote %c %s\n", str[fk], str + fk + 1);
				return ;
			}
			ft_strlcpy(str + fk, str + fk + 1, ft_strlen(str + fk));
			ft_strlcpy(next - 1, next, ft_strlen(next) + 1);
			strnesc(str + fk, next - str - fk - 1);
			fk = next - str - 2;
		}
	}
}

void	unescape(char *str)
{
	while (*str)
	{
		if (*str < 0)
			*str += 128;
		str++;
	}
}

int		strcount(char *str, char c, int len)
{
	int	out;

	out = 0;
	while (--len >= 0)
		out += str[len] == c;
	return (out);
}

void	strend(char *str)
{
	static char	c = 0;
	char		temp;

	temp = c;
	c = *str;
	*str = temp;
}


t_bst *bst;

void	add_var(t_strbuilder *builder, char *str, int *at)
{
	char	*temp;
	char	*ve;

	if (strcount(str, '\'', *at) % 2 == 0)
	{
		ve = ft_strchrf(str + *at, w, 1);
		if (!ve)
			ve = str + ft_strlen(str);
		strend(ve);
		temp = ft_bst_getvar(bst, str + *at);
		if (temp && *temp)
		{
			temp = ft_strdup(temp);
			strnesc(temp, 0);
			ft_strbuilder_addstr(builder, temp, 0);
			free(temp);
		}
		strend(ve);
		*at += ve - str - *at;
	}
	else
		ft_strbuilder_addchar(builder, '$');
}

void	expand_variables(char **str)
{
	t_strbuilder	*builder;
	int 			chr;
	int				k;
	char			*temp;
	char			*ve;

	builder = ft_strbuilder_new();
	k = 0;
	chr = ft_strchri((*str), '$');
	while (chr > -1)
	{
		if (chr > 0)
			ft_strbuilder_addstr(builder, (*str) + k, chr);
		k += chr + 1;
		add_var(builder, *str, &k);
		chr = ft_strchri((*str) + k, '$');
	}
	ft_strbuilder_addstr(builder, (*str) + k, 0);
	free(*str);
	*str = ft_strbuilder_build(builder);
	ft_strbuilder_free(&builder);
}

#include "tokenise.h"

void	parse(char *line)
{
	int		k;
	char	**commands;
	t_list	*t;
	t_list	*tok;

	printf("%s\n", line);
	expand_variables(&line);
	escape_quoted(line);
	commands = ft_split(line, '|');
	k = -1;
	while (commands[++k])
	{
		tok = tokenise(commands[k]);
		t = tok;
		printf("\t");
		while (t)
		{
			unescape(((t_token *)t->content)->str);
			printf("[%s] ", ((t_token *)t->content)->str);
			t = t->next;
		}
		printf("\n");
		ft_lstclear(&tok, free_token);
	}
	printf("\n");
	ft_strarrfree(commands);
	free(line);
}

int	main(int argc, char **argv)
{
	ft_bst_setvar(&bst, "ARG", "1 2");
	ft_bst_setvar(&bst, "SPACE", " ");
	ft_bst_setvar(&bst, "EMPTY", "");
	ft_bst_setvar(&bst, "PIPE", "|");
	ft_bst_setvar(&bst, "CMD", "\"t .txt\"");

	parse(ft_strdup("ABCDEF\"0123\"ABC\"0\"B\"1\"D"));
	parse(ft_strdup("egrep $ARGS$ARG < \t  \"in .txt\" | cat>$NOT $ARG"));
	parse(ft_strdup("echo \"$PIPE\"\'$PIPE\'\"Another\"$SPACE One"));
	parse(ft_strdup("echo \"$PIPE\" \'$PIPE\'"));
	parse(ft_strdup("echo \"$PIPE|\"|\'|$PIPE\'"));
	parse(ft_strdup("cat $CMD\"a b\""));
	parse(ft_strdup("echo $SPACE$EMPTY$SPACE$NOT$SPACE."));
	parse(ft_strdup("echo nothing>out"));

	ft_bst_free(&bst);
	return 0;
}
