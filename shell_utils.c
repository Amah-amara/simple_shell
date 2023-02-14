#include "shell.h"

/**
 * get_file_path - get PATH
 * @name: name of command
 * Return: a full path of name or name it self on failure
 */

char *get_file_path(char *name)
{
	char *PATH = _getenv("PATH"), *fpath = NULL;
	char *tokenized = _strtok(PATH, ":", 0);
	struct stat fileinfo;

	if (!name)
		return (NULL);
	if (*name == '/' || *name == '.')
	{
		fpath = _malloc(_strlen(name) * sizeof(char) + 1);
		_strcpy(fpath, name);
		return (fpath);
	}
	while (tokenized)
	{
		fpath = _malloc((_strlen(tokenized) + _strlen(name) + 1) * sizeof(char) + 1);
		_strcpy(fpath, tokenized);
		_strcat(fpath, "/");
		_strcat(fpath, name);
		if (!stat(fpath, &fileinfo))
			return (fpath);
		free(fpath);
		tokenized = _strtok(NULL, ":", 0);
	}
	fpath = _malloc(_strlen(name) * sizeof(char) + 1);
	_strcpy(fpath, name);
	return (fpath);
}

/**
 * parse_args - handle arguments
 * @cmd: tokenized string with arguments
 * @del: delimeter
 * @args: argument vector
 * @mod: delimeter method 0-character 1-string
 *
 * Return: none
 */

void parse_args(char *cmd, const char *del, char ***args, int mod)
{
	char *tokenized = NULL, **tmp;
	int index = 0, i;

	*args = NULL;
	tokenized = _strtok(cmd, del, mod);
	while (tokenized != NULL)
	{
		tmp = (char **)_malloc((_arlen(*args) +  2) * sizeof(char *));
		if (!*args)
			*args = tmp;
		else
		{
			i = 0;
			while ((*args)[i])
			{
				tmp[i] = _strdup((*args)[i]);
				i++;
			}
			free_pp(*args);
			*args = tmp;
		}
		(*args)[index] = NULL;
		trim_spaces(&((*args)[index]), tokenized);
		(*args)[index + 1] = NULL;
		tokenized = _strtok(NULL, del, mod);
		index++;
	}
}

/**
 * get_input - gets input from the cli
 * @input: pointer to input string
 * @inputlen: pointer to input len
 * @cmds: pointer to array of arguments
 * @fd: file discriptor
 *
 * Return: lenght of input
 */

int get_input(char **input, size_t *inputlen, char ***cmds, int fd)
{
	int len;

	if (isatty(0) && !fd)
		write(1, "$ ", 2);
	len = _getline(input, inputlen, fd);
	if (len == -1)
	{
		free(*input);
		write(1, "\n", 1);
		exit(0);
	}
	(*input)[len - 1] = '\0';
	parse_args(*input, ";", cmds, 0);
	return (len - 1);
}
