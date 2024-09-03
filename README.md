# 42_minishell

```sudo apt search readline``` 搜索readline安装包

```sudo apt-get install lib32readline8``` 安装readline

```sudo apt-get install libreadline-dev``` 安装readline可调用的文件夹，没有的话无法调用 include<readline/readline.>

# Unix shell’s working process

**1-Lexical Analysis (Lexer): Tokenizes the input.**

transfer input string to token(some manageable pieces, like keywords, operators, identifiers), need to do:

    -check quotes, closed is valid (follow subject)

    -get token: 
        
        keyword, operators(| > <), literals, like strings number.
    	
    -check special characters, |, > <, ;(no need), " '

**2-Parsing (Parser): Builds an abstract syntax tree from the tokens.**

analyze tokens to create an abstract syntax tree(AST), need to do:

    -check syntax: first is not special character, after redirection not be redir or pipes

    -Expansion: Expands variables and command substitutions.
    
    -parse token to AST:
        command parse, include parameter and redirection
    
        parse pipe
    
        parse redirection to AST

**3-Execution: Executes the commands as represented by the AST.**

    execute cmd follow AST, command, pipeline, redirection

and

    **Input/Output Management: Handles user input and command output.**

**4-others**

    Environment Management: Manages environment variables. (set, get, update)
    
    Error Handling: Deals with syntax and runtime errors.
