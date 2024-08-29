# 42_minishell

# Unix shell’s working process

**1-Lexical Analysis (Lexer): Tokenizes the input.**

transfer input string to token(some manageable pieces, like keywords, operators, identifiers), need to do:

    -keyword, operators(| > <), literals, like strings number.
    	
    -handling quotes, ensure tokens include space and quotes can be handle
    	
    -check special characters, |, > <, ;


**2-Parsing (Parser): Builds an abstract syntax tree from the tokens.**

analyze tokens to create an abstract syntax tree(AST), need to do:

    -command parse, include parameter and redirection
    
    -parse pipe
    
    -parse redirection to AST
    
    -check syntax and command structure

also need to do during parsing:

    **Expansion: Expands variables and command substitutions.**

**3-Execution: Executes the commands as represented by the AST.**

    execute cmd follow AST, command, pipeline, redirection

and

    **Input/Output Management: Handles user input and command output.**

**4-others**

    Environment Management: Manages environment variables. (set, get, update)
    
    Error Handling: Deals with syntax and runtime errors.
