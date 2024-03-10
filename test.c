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

int	strfchr(char *str, int(*f)(int), int inverted)
{
	int	k;

	k = -1;
	while (str[++k])
		if (f(str[k]) ^ inverted)
			return (k);
	return (k);
}

void	escape_quoted(char *str)
{
	int fk;
	int tk;

	int in;

	fk = 0;
	tk = 0;
	in = 0;
	while (str[fk])
	{
		if (str[fk] == '\"')
		{
			in = !in;
			fk++;
			continue ;
		}
		else
		{
			str[tk++] = str[fk++] + in * 128;
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

t_bst *bst;

void	expand_variables(char **str)
{
	t_strbuilder	*builder;
	int 			chr;
	int				k;

	chr = ft_strchri((*str), '$');
	k = 0;
	builder = ft_strbuilder_new();
	while (chr)
	{
		ft_strbuilder_addstr(builder, (*str) + k, chr);
		k += chr + 1;
		
		int ve = strfchr((*str) + k, w, 1);
		strend((*str) + k + ve);
		printf("Fetching %s: %s\n", (*str) + k, (char *)ft_bst_getvar(bst, (*str) + k));
		ft_strbuilder_addstr(builder, ft_bst_getvar(bst, (*str) + k), 0);
		strend((*str) + k + ve);
		k += ve;

		chr = ft_strchri((*str) + k, '$');
	}
	ft_strbuilder_addstr(builder, (*str) + k, 0);
	free(*str);
	*str = ft_strbuilder_build(builder);
	ft_strbuilder_free(&builder);
}

void	parse(char *line)
{
	printf("\nParsing : [%s]\n", line);
	expand_variables(&line);
	printf("After var expansion :\n[%s]\n", line);
	free(line);
}

int	main(int argc, char **argv)
{
	ft_bst_setvar(&bst, "ARG", "1 2 3   4");
	ft_bst_setvar(&bst, "SPACE", " ");
	ft_bst_setvar(&bst, "PIPE", "|");


	parse(ft_strdup("egrep $ARG < \"in .txt\" | cat >$NOT $ARG"));
	parse(ft_strdup("echo \"$PIPE$ARG\"\'$PIPE\'"));

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
