# Minishell

Summary:
This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.
Version: 6

We have access to many functions:

-readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

What we do with those functions ?

Examples in file readline.c in the folder external_functions
- readline: Use to read a line from the terminal
- rl_clear_history: Clear the history of the last readline function called
- rl_on_new_line: Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline. 
- rl_replace_line: Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared. 
- rl_redisplay: Readline will call indirectly through this pointer to update the display with the current contents of the editing buffer.
- add_history: Readline will memorize the line used in parameter
	Source: https://tiswww.case.edu/php/chet/readline/readline.html
- getcwd for get current work directory: The getcwd() function copies an absolute pathname of the current working directory to the array pointed to by buf, which is of length size.
	Source: https://man7.org/linux/man-pages/man3/getcwd.3.html
- chdir for change directory: changes the current working directory of the calling process to the directory specified in path.
	Source: https://man7.org/linux/man-pages/man2/chdir.2.html
- getenv: searches for the environment string pointed to by name and returns the associated value to the string
	Source: https://man7.org/linux/man-pages/man3/getenv.3.html

- printf, malloc, free, perror, strerror and exit are knowned functions

Examples in file signal.c and sigaction.c in the folder external_functions
- signal: This function handle the signal and manage it how you want. Use sigaction instead
	Source: https://man7.org/linux/man-pages/man2/signal.2.html
- sigaction: The sigaction() system call is used to change the action taken by a process on receipt of a specific signal.
	Source: https://man7.org/linux/man-pages/man2/sigaction.2.html
- sigemptyset: Initializes the signal set given by set to empty, with all signals excluded from the set.
- sigaddset: Adds a signal to the set of signals already recorded in set.
	Sources: https://stackoverflow.com/questions/27227585/what-is-sigaddset-used-for
- kill: Send the signal in parameter
			
Examples in file open.c in the folder external_functions
- access: Check the accessibility to a pathname (file, directory) with differents flags (F_ok for file exists for example)
	Source: http://manpagesfr.free.fr/man/man2/access.2.html
- open: Open a file and return a file descriptor to use it
	Source: http://manpagesfr.free.fr/man/man2/open.2.html
- read: Read the fd n octets nd store it to a buffer
	Source: http://manpagesfr.free.fr/man/man2/read.2.html
- unlink: delete a name and possibly the file it refers to. Delete a file for short
	Source: https://linuxhint.com/unlink-system-call-in-c/
- close: Close the fd in parameter

Examples in file process.c in the folder external_functions
- fork: Create a new process (child) by duplicating the calling process (parent) and return an int PID (process ID) to identify the process
	Source: https://man7.org/linux/man-pages/man2/fork.2.html
- wait, waitpid, wait3, wait4: The wait() system call suspends execution of the calling thread until one of its children terminates.
	Source: https://man7.org/linux/man-pages/man2/wait.2.html
- pipe: pipe() creates a pipe, a unidirectional data channel that can be used for interprocess communication. The array pipefd is used to return two file descriptors referring to the ends of the pipe.
	Source: https://man7.org/linux/man-pages/man2/pipe.2.html
- dup, dup2: Duplicate a file descriptor, or replace a fd with an other already use like 0 for the stdin
	Source: https://man7.org/linux/man-pages/man2/dup.2.html
	
Examples in file stat.c in the folder external_functions
- stat, lstat, fstat: These functions return information about a file, in the buffer pointed to by statbuf.
	Source: https://man7.org/linux/man-pages/man2/lstat.2.html

Examples in file opendir.c in the folder external_functions
- opendir: The opendir() function opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream.  The stream is positioned at the first entry in the directory.
	Source: https://man7.org/linux/man-pages/man3/opendir.3.html
- readdir: The readdir() function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp.  It returns NULL on reaching the end of the directory stream or if an error occurred.
	Source: https://man7.org/linux/man-pages/man3/readdir.3.html
- closedir: The closedir() function closes the directory stream associated with dirp.
	Source: https://man7.org/linux/man-pages/man3/closedir.3.html

VOIR Pipex
- execve: execve() executes the program referred to by pathname.
	Source: https://man7.org/linux/man-pages/man2/execve.2.html

Missing functions: isatty, ttyname, ttyslot, ioctl, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs


How to implement Minishell

 > ls -la > test | wc > test2 > test3
t_list token_letter
####LLELLLE>ELLLLE|ELL>ELLLLLE>ELLLLL
####WWEWWWE>EWWWWE|EWWE>EWWWWWWWE>EWWWWWWW
t_list token_word
WORD
SPACE
WORD
SPACE
REDIRECTION_OUT
SPACE
WORD
SPACE
PIPE
SPACE
WORD


WORD
WORD
REDIRECTION_OUT
WORD
PIPE
WORD
REDIRECTION_OUT
WORD
REDIRECTION_OUT
WORD
NULL


t_list cmd

NEW MAILLON =
char **cmd[0]ls
          [1]-la

int fd_out = test (int ?)
int fd_in = 0
pid_t pid = NULL;
next = NEW MAILLON 2

NEW MAILLON 2
char **cmd [0]wc
int fd_out = dernier fd de ma liste avant pipe ou fin de liste
int fd_in = 0
pid_t pid = NULL;
next = NULL;

t_list tmp = cmd;

while (tmp != NULL)
{
    tmp->pid = fork()
    {
        execution classico classique
    }
    tmp = tmp->next;
}
tmp = cmd;
while (tmp != NULL)
{
    waitpid(tmp->pid);
    tmp = tmp->next;
}
