#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "libft.h"

int w(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

int W(int c)
{
	return !w(c);
}

int	o(int c)
{
	return c == '>' || c == '<' || c == '|';
}

int	s(int c)
{
	return (c == ' ' || c == '\t');
}

void	escape_quoted(char *str)
{
	int fk;
	int tk;
	int in;
	int	esc;

	fk = 0;
	tk = 0;
	in = 0;
	while (str[fk])
	{
		if (in == 0 && str[fk] == '\"' && ++fk)
			in = 2;
		else if (in == 0 && str[fk] == '\'' && ++fk)
			in = 1;
		else if (in == 1 && str[fk] == '\'' && ++fk)
			in = 0;
		else if (in == 2 && str[fk] == '\"' && ++fk)
			in = 0;
		else
		{
			if (str[fk] >= 0)
				str[tk++] = str[fk++] - (!!in * 128);
			else
				str[tk++] = str[fk++];
			if (fk > tk)
				str[fk - 1] = 0;
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

int		count_(char *str, char c, int len)
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

void	strnesc(char *str, int len)
{
	if (!str || !*str)
		return ;
	if (len > 0)
		while (--len >= 0)
			*str++ -= 128;
	else
		strnesc(str, ft_strlen(str));
}

t_bst *bst;

void	expand_variables(char **str)
{
	t_strbuilder	*builder;
	int 			chr;
	int				k;
	char			*temp;
	int m = 0;

	builder = ft_strbuilder_new();
	k = 0;
	chr = ft_strchri((*str), '$');
	while (chr > -1)
	{
		if (chr > 0)
			ft_strbuilder_addstr(builder, (*str) + k, chr);
		k += chr + 1;
	
		if (count_(*str, '\'', k) % 2 == 0)
		{
			char *ve = ft_strchrf((*str) + k, w, 1);
			if (!ve)
				ve = (*str) + ft_strlen(*str);
			strend(ve);
			temp = ft_bst_getvar(bst, (*str) + k);
			if (temp && *temp)
			{
				temp = ft_strdup(temp);
				strnesc(temp, 0);
				ft_strbuilder_addstr(builder, temp, 0);
				free(temp);
			}
			strend(ve);
			k += ve - (*str) - k;
		}
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
	int	k;
	char ** commands;
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

	//split avec fonction plutot que char
	parse(ft_strdup("egrep $ARGS$ARG < \t  \"in .txt\" | cat>$NOT $ARG"));
	parse(ft_strdup("echo \"$PIPE\"\'$PIPE\'"));
	parse(ft_strdup("echo \"$PIPE\" \'$PIPE\'"));
	parse(ft_strdup("echo \"$PIPE|\"|\'|$PIPE\'"));
	parse(ft_strdup("cat $CMD\"a b\""));
	parse(ft_strdup("echo $SPACE$EMPTY$SPACE$NOT$SPACE."));
	parse(ft_strdup("echo nothing>out"));

	ft_bst_free(&bst);
	return 0;
}

// https://unix.stackexchange.com/questions/234755/command-line-processing-tokens-and-metacharacters
//  This is not a very good explanation. A token is a sequence of characters
//  that forms a word or punctuation sign. Characters like < and | are part of
//  tokens too. You may call them metacharacters but this is not useful
//  terminology. The basic rules are:

// Whitespace is not part of a token and separates tokens.
// A token is made up of ordinary characters, or of operator
// characters ()<>&|;, but not both. For example, foo<@a&>b consists
// of the tokens foo (ordinary), < (operator), @a (ordinary),
// &> (operator) and b.
// Then there are additional rules about quoting: special characters
// lose their meaning if they're quotes, with different rules depending
// on the type of quote. For example, foo'&&'bar\|qux is a single token
// with the character sequence foo&&bar|qux.
