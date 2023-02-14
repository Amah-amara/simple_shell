#include "shell.h"

/**
 * xpnd_sign - expand command signs
 * @str: string to be used
 * @stat: last exit staatus
*/

void xpnd_sign(char **str, int stat)
{

	char *pid = itoa(getpid()), *stats = itoa(stat);

	if (**str != '\n')
		find_n_rep(str, "$$", pid), find_n_rep(str, "$?", stats);

	free(pid), free(stats);
}

/**
 * xpnd_str - expand shell variables
 * @str: string containging variables
 * @childstat: the last exit status of the child process
 *
 * Return: 0 on sucess and -1 on error
 */

int xpnd_str(char **str, int childstat)
{
	char *var = _malloc(2), *tmp = NULL, *rep = NULL, *_str = NULL;
	int i = 0, j = 0;

	xpnd_sign(str, childstat);
	var[0] = 'k', var[1] = '\0';
	while (*(*str + i))
	{
		if (*(*str + i) == '$' && *str + i + 1)
		{
			if (*(*str + i + 1) != '$' && *(*str + i + 1) != '?')
			{
				j = 0;
				while (*(*str + i + j) != ' ' && *(*str + i + j))
				{
					var = _realloc(var, _strlen(var) + 16);
					*(var + j) = *(*str + i + j), *(var + j + 1) = '\0';
					if (!(*str + i + j + 1))
						break;
					j++;
				}
				tmp = _malloc(_strlen(var)), _strcpy(tmp, var + 1), rep = _getenv(tmp);
				if (rep)
					find_n_rep(str, var, rep);
				free(var), free(tmp);
				var = (char *)_malloc(2), var[0] = ' ', var[1] = '\0', tmp = NULL;
			}
		}
		i++;
	}
	_str = *str;
	while (*_str)
	{
		if (*_str == '#')
			break;
		_str++;
	}
	if (**str != '\n')
		*_str = '\0';
	free(var);
	return (0);
}

/**
 * xpnd_alias - expand aliases inside a string
 * @str:string to be manipulated
 * @head: first node
 */

void xpnd_alias(char **str, alias *head)
{

	while (head)
	{
		find_n_rep(str, head->key, head->value);
		head = head->next;
	}
}
