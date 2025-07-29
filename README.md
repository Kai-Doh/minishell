<<<<<<< HEAD
=======
# minishell
Your shell should:
• Display a prompt when waiting for a new command.
• Have a working history.
• Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
• Use at most one global variable to indicate a received signal. Consider the
implications: this approach ensures that your signal handler will not access your
main data structures.
Be careful. This global variable must only store the signal number
and must not provide any additional information or access to data.
Therefore, using "norm" type structures in the global scope is
forbidden.
5
Minishell As beautiful as a shell
• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).
• Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
• Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).
• Implement the following redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.
• Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
• Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
• Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
• Your shell must implement the following built-in commands:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

# check for any memory leaks
 Use the command valgrind to check for any memory leaks, anything not related to readline because it has some leaks.


# evaluation

### ✅ Basic Commands: Absolute Path
- Execute a simple command with an absolute path like `/bin/ls` (no options).
- Global Variables:
  - Count how many are declared.
  - Why? To manage state like environment variables, current status code, etc.
  - Example: `$?` is needed to reflect the exit status of the last command — it's logical to store this in a global variable.
- Test an empty command.
- Test only spaces or tabs.
- Flags:
  - ❗ Use `crash` flag if anything crashes.
  - ⚠️ Use `incomplete work` flag if behavior is incorrect or unfinished.

### ✅ Commands with Arguments & History
- Execute a command like `/bin/ls file.txt` (no quotes).
- Try multiple commands and argument combinations:
  - `/bin/echo hello`
  - `/bin/cat file.txt`
  - `/bin/grep pattern file.txt`
- Use `echo $?` to check return values.
- Try failing commands like `/bin/ls doesnotexist`
- Try something like `expr $? + $?`
- Flags:
  - ❗ Use `crash` flag if anything crashes.
  - ⚠️ Use `incomplete work` flag if something is not working.

### ✅ Echo
- Run `echo`, `echo test`, `echo -n test`, `echo $USER`, etc.
- Repeat with different arguments.
- Flags:
  - ❗ Use `crash` flag if anything crashes.
  - ⚠️ Use `incomplete work` flag if something is not working.

### ✅ Exit
- Run `exit`, `exit 0`, `exit 42`, `exit 256`, etc.
- Relaunch minishell after each `exit`.
- Flags:
  - ❗ Use `crash` flag if anything crashes.
  - ⚠️ Use `incomplete work` flag if something is not working.

### ✅ Return Value of a Process
- Execute a command like `/bin/ls` or `/bin/ls filethatdoesntexist`, then run `echo $?`.
- Compare with bash behavior.
- Try arithmetic with return values: `expr $? + $?`
- Flags:
  - ❗ Use `crash` flag if anything crashes.
  - ⚠️ Use `incomplete work` flag if something is not working.

### ✅ Signals
- Ctrl+C at empty prompt → should print new prompt.
- Ctrl+\ at empty prompt → should do nothing.
- Ctrl+D at empty prompt → should quit minishell (then relaunch).
- Ctrl+C after typing → clears line, shows new prompt.
- Ctrl+D after typing → should do nothing.
- Ctrl+\ after typing → should quit minishell (then relaunch).
- Run a blocking command like `cat` or `grep` without args, then try:
  - Ctrl+C → should interrupt.
  - Ctrl+\ → should quit.
  - Ctrl+D → should send EOF.
- Repeat with different blocking commands.
- Flags:
  - ❗ Use `crash` flag if anything crashes.
  - ⚠️ Use `incomplete work` flag if something is not working.

### ✅ Double Quotes
- Run commands with double-quoted arguments including whitespace:
  - `echo "cat lol.c | cat > lol.c"`
- `$` should still be interpreted.
- Flags:
  - ❗ Use `crash` flag if anything crashes.
  - ⚠️ Use `incomplete work` flag if something is not working.

### ✅ Simple Quotes
- Use single quotes for arguments:
  - `echo '$USER'` → should print `$USER`
  - Try whitespaces, empty args, redirections inside quotes
- Nothing inside should be interpreted.
- Flags:
  - ❗ Use `crash` flag if anything crashes.
  - ⚠️ Use `incomplete work` flag if something is not working.

### ✅ Env
- Run `env` → should show current environment variables.

### ✅ Export
- Use `export VAR=value`
- Overwrite existing variables.
- Confirm with `env`.

### ✅ Unset
- Use `unset VAR`
- Confirm removal with `env`.

### ✅ cd
- Use `cd directory`, `cd ..`, `cd .`
- Confirm using `/bin/ls` or `pwd`
- Try invalid directories too.

### ✅ pwd
- Run `pwd` in various locations.

### ✅ Relative Path
- Run commands using relative paths like `./a.out`, `../bin/script.sh`
- Test deep nesting: `../../../some/path/to/exe`

### ✅ Environment Path
- Run commands like `ls`, `wc` without full path.
- `unset PATH` and check that commands don’t work.
- Set `PATH=dir1:dir2` and confirm search order.

### ✅ Redirection
- Use `<`, `>`, `>>` with different commands.
- Check for overwrite and append behavior.
- Try invalid redirection like multiple `>>`
- Use `<<` (heredoc) and test content.

### ✅ Pipes
- Use pipes like `cat file | grep test | wc`
- Try with failing command in pipe: `ls badfile | grep test`
- Combine pipes and redirection.

### ✅ Go Crazy & History
- Type command, press Ctrl+C, then Enter → buffer should be clean.
- Navigate through history with up/down arrows.
- Run invalid command like `asdkjasd` → should print error, not crash.
- Try very long commands with many arguments.

### ✅ Environment Variables
- Use `echo $USER`, `echo "$USER"`
- Confirm variable interpolation inside double quotes.
- Set or ensure `$USER` exists.
>>>>>>> 43b4f90 (test)

