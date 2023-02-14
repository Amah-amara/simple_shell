#ifndef HDETAILS
#define HDETAILS

#include "shell.h"

#define exit_h1 "\texit usage: exit N\n\tExit the shell.\n\n"
#define exit_h2 "\tExits the shell with a status of N.  If N is omitted,"
#define exit_h3 "\tthe exit status\n\t    is that of the last command executed.\n"
#define exit_h (exit_h1 exit_h2 exit_h3)

#define alias_h1 "\talias usage: alias [KEY][=VALUE] \n\tAllows\t"
#define alias_h2 "aliases to be set for quicker shell usage. \n\tAlias with no\t"
#define alias_h3 "KEY VALUE prints a list of aliases. \n\tAlias with KEY prints\t"
#define alias_h4 "the alias match for that key. \n\tAlias with KEY VALUE sets"
#define alias_h5 "or overwrites the KEY with new VALUE.\n"
#define alias_h (alias_h1 alias_h2 alias_h2 alias_h3 alias_h4 alias_h5)

#define unset_h1 "\tunsetenv usage: unsetenv VARIABLE:\n"
#define unset_h unset_h1 "Remove an envirornment variable.\n"


#define set_h1 "\tsetenv usage: setenv VARIABLE VALUE\n"
#define set_h2 "\tInitialize a new environment variable, or modify an"
#define set_h set_h1 set_h2 "existing one.\n"


#define history_h1 "\thistory usage: history\n\t"
#define history_h history_h1 "Display the history list with line numbers.\n"


#define help_h "\thelp usage: help COMMAND\n    Display helpful info about builtins\n"


#define env_h "env usage: env\n    Prints out the current envirornment.\n"

#define cd_h "cd usage: cd DIR\n    Change the current directory to DIR.\n"

#define ghelp1 "\talias\thelp \n"
#define ghelp2 "\tcd\thistory\n"
#define ghelp3 "\tenv\tset\n"
#define ghelp4 "\texit\tunset\n"
#define ghelp (ghelp1 ghelp2 ghelp3 ghelp4)

#endif
