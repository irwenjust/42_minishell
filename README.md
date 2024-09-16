Some commands need handle:   

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

Some doubts:   
1. handle if there have some arguments in pwd   
2. handle if there don't have any argument in unset    
