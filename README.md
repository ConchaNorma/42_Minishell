# 42-Minishell
# First and foremost, standard library functions I am allowed to use.
Below is the list of the external functions / standard library functions that I am allowed to use, if I need any another function I must code it myself. Please see the man pages of these functions if you do not recognize them.

readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetflag, tgetnum, tgetstr, tgoto, tputs

# Expectations from the shell, what must this minimal shell do
1. It must implement the builtin shell functions

* echo with the option -n
* cd with only a relative or absolute path
* pwd with no options
* export with no options
* unset with no options
* env with no options or arguments
* exit with no options

2. Redirections

* < should redirect input
* > should redirect output
* << read input from the current source until a line containing only the delimiter is even.
* >> should redirect output in append mode.

3. Pipes

* | The output of each command in the pipeline is connected via a pipe to the input of the next command

4. Environment Variables ($ followed by characters ) should expand to their values.

5. $? should expand to the exit status of the most recently executed foreground pipeline

6. For some simplification, the shell must not interpret unclosed quotes or unspecified special characters like '\' or ';' etc

7. The shell must show a prompt waiting for next command, have a working history and must only use one global variable.

8. ctrl-C ctrl-D ctrl-\ should work like bash. When interactive:
* ctrl-C print a new prompt on a newline
* ctrl-D exit the shell.


# Understanding the scope of each builtin
## Quick recap of the builtin functions that we need to make
* echo with the option -n
* cd with only a relative or absolute path
* pwd without any options
* export without any options
* unset without any options
* env without any options and any arguments
* exit without any options

### cd function
cd can be used with these characters and the sequence matters.

* " . " - indicates the current folder.
* " .. " - indicates the parent folder.
* " ~ " - indicates the absolute path to the user.
* " / " - indicates separation between folders.

### " ~ " can only be entered as the first argument to cd

cd ~ (this is okay)
cd ./~ (this won't work)
cd dir/~ (this won't work)

### " / " it can be used as a separator between folders.

cd srcs/ (this is okay)
cd ../ (this is okay)
cd /srcs (this won't work)

Functions required to write cd function

getcwd - Get the current path\n
chrdir - if you put a path in chdir, it moves to that path

## Handling Quotes
Constraint as discussed over quote handling

' inhibit all interpretation of the following sequence of characters.
" inhibit all interpretation of the following sequence of characters expect for $

### Understanding Quotes and how they behave

* Double quotes must be closed whenever you open one.
* But if you open with a single quote and close with a single quote, any number of double quotation marks can be inserted between them.
* Similarly if you open with double quotes and close with double quotes, any number of single quotes can be inserted between them.

Valid quote handling for us includes
* " "
* " ' "
* ' '
* ' " '

Invalid quote handling for us includes
* "
* '
* " " '
* ' ' "
* ' " "
* " ' '
* ' ' '
* " " "

### Lets look at quotes between executable and variables

Valid quote handling includes:
* echo "abc"
* echo "a"bc
* echo "ab"c
* echo ""abc
* echo abc""
* ech"o" abc
* echo"" abc
* ""echo abc
* "echo" abc
* "echo""" abc

Invalid quote handling includes:
* echo" abc
* echo a"bc
* echo" a"bc
* echo" "abc
* ech"o "abc
* "echo abc"

## echo function

* Execute echo command with or without args
* Repeat with other arguments
* Restart the shell once done
* If there is conflict, use the conflict flag
* if something doesn't work, use the incomplete flag

## exit function
* Execute with or without args
* exit shell
* same use a conflict flag, incase of a conflict
* if something doesn't work, use a incomplete job flag

## env function
* display current env variables

## export function
* Export environment variables, create new ones and replace old ones
* export without options prints a list of env variables
* check with env

## unset function
* remove environment variables using unset
* check with result in env

# Other Basic information to be aware of

## Simple commands and global
* Shell must be good with simple commands, and commands like /bin/ls and no options
* Test for when empty command line is inserted.
* Test with inserting spaces and tabs at random points
* If something is colliding use a conflict flag
* If something doesn't work, use the incomplete flag.

## Arguments and History
* Must be able to execute simple commands with an absolute path such as /bin/ls with args. Without single and double quotes.
* Repeat with each command and argument
* Use relevant flags for conflict and incomplete.

## Return value of a process
* To mimic the working of $?, execute a simple command with an absolute path or any other command with args but without quotes and double quotes then execute echo $?
* Now try something similar as above but with single quotes and double quotes and check echo $? after that
* Try commands that will fail like bin/ls nonexitantfile and see the value of $?
* Maybe try $? + $?

## Signals
* ctrl-c : SIGINT
* ctrl-\ : SIGQUIT
* ctrl-c : Stop execution with an interrupt signal from the keyboard
* ctrl-\ : A stop signal from keyboard, which terminates the process and dumps the core.
	* Pressing ctrl-c at an empty prompt should create newline
	* If you hit ctrl-\ at the empty prompt, nothing should happen
	* Press ctrl-d at an empty prompt to close the shell
	* After writing a few things, press ctrl-c to show a new prompt line
	* After writing a few things, press ctrl-d, nothing happens
	* after writing a few things, press ctrl-\ to turn off the shell
	* Block ctrl-c, ctrl-d, ctrl-\ while cat or grep is running.
* Incase of conflict, use conflict and incase it doesn't work use the incomplete flag.

## Single Quotes
* Try an empty parameter
* Test with env variables, whitespace, pipes and redirects.
* '%USER' should print $USER

## Relative Path
* Repeat with multiple directories with complex relative paths
* Set $PATH to a multiple directory value(dir1:dir2) and check those directories in left to right order.
