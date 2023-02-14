#include "shell.h"

/**
 * _chdir - change current directory
 * @path: new path
 * Return: 0 on sucess and 1 on failure
 */

int _chdir(char *path)
{
	int status;
	char *currentdir = _getenv("PWD"), *buf = NULL, *cdir, *msg;
	char *smn;
	size_t size = 0;

	if (!path || !_strcmp(path, "~"))
		status = chdir(_getenv("HOME"));
	else if (!_strcmp(path, "-"))
		status = chdir(_getenv("OLDPWD"));
	else
		status = chdir(path);
	if (status < 0)
	{
		errno = -3;
		msg = _malloc(_strlen("No such file or directory ") + _strlen(path) + 4);
		_strcpy(msg, "No such file or directory ");
		smn = _malloc(_strlen("cd: "));
		_strcpy(smn, "cd: ");
		_strcat(smn, path);
		print_error(smn, NULL, msg);
		free(msg);
		return (-1);
	}

	_setenv("OLDPWD", currentdir, 1);
	cdir = getcwd(buf, size);
	_setenv("PWD", cdir, 1);
	free(buf), free(cdir);
	return (0);
}

/**
 * runscript - run a file if executable
 * @name: filename
 * Return: 0 on sucess and -1 on faliure
 */

int runscript(char *name)
{
	char *path = NULL, *currentdir = NULL;
	int fd, i, cmdlen;
	size_t len = 0;
	char *input, **cmds, *errmsg, **cmds2;
	alias *head = NULL;

	if (name[0] != '.' && name[0] != '~' && name[0] != '/')
	{
		currentdir = _getenv("PWD");
		path = _malloc(_strlen(currentdir) + _strlen(name) + 4);
		_strcpy(path, currentdir);
		_strcat(path, "/");
		_strcat(path, name);
	}
	else
		path = name;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		errno = -3;
		errmsg = _malloc(_strlen("Permission denied ") + _strlen(name) + 4);
		_strcpy(errmsg, "Permission denied ");
		print_error(name, NULL, errmsg);
		free(errmsg);
		free(path);
		return (127);
	}
	free(path);

	get_input(&input, &len, &cmds, fd), find_n_rep(&(cmds[0]), "\n", ";");
	parse_args(cmds[0], ";", &cmds2, 0), free(input), free_pp(cmds);

	i = 0, cmdlen = _arlen(cmds2);
	while (i < cmdlen)
		exec_cmd(cmds2, i, &head), i++;
	free_pp(cmds2);
	return (0);
}

/**
 * execute - execute a process with a child
 * @tmp: pointer to pointer of child
 * Return: 0 on sucess and faliure number on failure
 */

int execute(char **tmp)
{
	struct stat cmdinfo;
	char *fpath = NULL;
	int exitstat = 0;

	if (!tmp)
		return (exitstat);
	fpath = get_file_path(tmp[0]);
	if (stat(fpath, &cmdinfo) == 0 && cmdinfo.st_mode & S_IXUSR)
		exitstat = execve(fpath, tmp, environ);
	else
	{
		exitstat = 127;
		errno = -4;
		print_error(tmp[0], NULL, "not found");
	}
	free(fpath);
	return (exitstat);
}
