# 42_Minishell  
This project is trying to create our shell terminal similar than bash.  
The project grade is 100/100.  

## **Authorship**

- [**yingzhan11**](https://github.com/yingzhan11) **- yzhan**  
- [**irwenjust**](https://github.com/irwenjust) **- likong**  

## **Mandatory part**  
Here are some of the features our Minishell handles:  
- A prompt with the current path;
- A command history;
- Lexer and parser save in the ast tree;
- Same format error message with bash;
- Builtin commands: echo, cd, pwd, export, unset, env and exit;
- local variable;
- Multiple redirection/heredoc;
- Multiple pipe;
- Environment variable and $ sign;
- Signal with ctrl+C, ctrl+D and ctrl+\\;

## **Implementation**  
<table align=center>
	<thead>
		<tr>
			<th>File Name</th>
			<th>Functionality</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><strong>libft/</strong> </td>
			<td>Contains standard libft project and some of the added tools function</td>
		</tr>
		<tr>
			<td><strong>srcs/</strong> </td>
			<td>Contains all the source files</td>
		</tr>
		<tr>
			<td><strong>srcs/builtins/</strong> </td>
			<td>Contains all the builtin commands</td>
		</tr>
		<tr>
			<td><strong>srcs/execution/</strong> </td>
			<td>For execution part. Include execution, pipe and redirection</td>
		</tr>
		<tr>
			<td><strong>srcs/pre_handler/</strong> </td>
			<td>Prehandle the command. Include lexer, token, expander and parser</td>
		</tr>
		<tr>
			<td><strong>srcs/signal/</strong> </td>
			<td>signal handle for default, child process and here_doc</td>
		</tr>
		<tr>
			<td><strong>srcs/tools/</strong> </td>
			<td>All of general tool functions</td>
		</tr>
		<tr>
			<td><strong>interface.c</strong> </td>
			<td>Central Control function/file</td>
		</tr>
		<tr>
			<td><strong>main.c</strong> </td>
			<td>main and initialize struct</td>
		</tr>
	</tbody>
</table>

## **Compilation**  

To compile this project you should run `make` in the terminal.    
To run the program needs to follow this:   
```sh  
$ ./minishell  
```

## **Some tips**  
- We use this tester to check our minishell: https://github.com/LucasKuhn/minishell_tester;
<!--- Firstly, too many things could be discussed and handled. That is also one reason for this readme file update delay(or just I'm lazy :thinking:);-->
- Some details we try to handle:
  1) check single && double quotes and expand command when prehandle command
  2) replace the environment variable in echo command (like "echo $HOME"). And, of course with single/&double quotes
  3) cd command with the same operation as bash if the bash folder doesn't exist
  4) exit could return the correct status value whatever overflow, alpha or multiple arguments (if number > longlong it should same error message as alpha)
  5) local variables could be saved to wait for export. Also handle some error cases, like first character is number (1a=1), '-' in the name (a-1=1) or empty name (=1)
  6) also, if all of the commands are local variables, just save it
  7) correctly handle the redirection. Like different behaviour in (cat <infile1 <infile2 <infile3 >outfile) and (cat <infile1 infile4 <infile2 infile5 <infile3 infile6 \>outfile)
  8) the "minishell:" word could show in correct time when the output shows an error message
  9) the command word and redirection order will not influence commands run (grep abc <infile >outfile == <infile grep \>outfile abc)
  10) the signal's exit status has been saved
- We still have not handled some details. If you are interested please try:
  1) multiple local variables in multiple pipes should do nothing (we will record first local variable and output others as error)
  2) multiple here_doc in multiple pipes should open->record->close each of here_doc and put content to correct outfile (we will output to all of outfile every time) (cat <<? >outfile1 | cat <<? >outfile2 | cat <<? >outfile3)
  3) In some cases our exit will not show the "exit" word (just need to add one print, but I forget it before evaluation) and if the first argument is not pure numbers the minishell should exit even there have more arguments, not just show an error message (exit abc 123)
  4) Probably have more crazy tests cannot pass as we are minishell
<!--
<infile   
<infile cat > outfile   

For ignore command which not include command inside pipe range   
<infile | grep "here" > outfile   
<infile grep "here" | > outfile   

Some bugs log: 
1. incorrect commands should be output   (fixed)   
2. if only $, should print $ also  (fixed)   
3. after builltin there should update exit status  
4. should update the env each time (special in builtin function)  
5. unset should has at least 2 arguments (with unset itself)  (fixed)  
6. after delete PATH, some builtin function should be useful still(echo,
cd, pwd, exit, export, unset), env should not work.   
7. keyword "minishell:" shouldn't show any time. (still need consider when command is $ and the variable is from env, if the value is file or directory, should add 'minishell: ')   
8. when print $ in echo it has been ignore    
9. when use '=' in commands part, if the string start by number or there have
'-' in the left side, it should be the error. and the message should be care. Like in normal command it just cannot find command but it is "not a valid identifier" when use export, like export 123=456 (BE CAREFUL!!!!!!!!! IN EXPORT ERROR THERE WILL SHOW 'BASH:' ALSO. FK)   (fixed part of this. can handle if - or number when use export and '=' cannot be the first place) (BUT HAVE MORE ISSUES HERE. IF WRITE '=SOMTHING' THE ERROR MESSAGE WILL SHOW SEVERAL TIMES NOT ONLY ONE TIME)  
10. handle $ when it is on the first position for command  (can handle only doller sign and doesn't exist command/div command. The regular things(from env) still needs to adjust. probably from general error message handle)   
11. Didn't handle this case: $EMPTY echo hi

Some doubts:   
1. handle if there have some arguments in pwd   
2. handle if there don't have any argument in unset    

local variable should be check only
-->
