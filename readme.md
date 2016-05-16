#Nazkell Project - Simple function language interpreter

###requirements

- cmake >2.8

###compiling and testing
1. `mkdir build`

2. `cd build`

3. `cmake ..`

4. `make`

5. `./lexer_test`

###executing

1. `cd build`

2. `echo "<input>" | ./lnazkell` or `./nazkell <filename>`

###tokens

  id - identificator for each variable and function  
  op - operator, symbol representing type of specyfic action  
  boolean - represents true/false value  
  integer - represents numbers  
  special - represents symbols which are not operators like parentheses  
  reservedid - id of special words, in this case only in if statement  

###lexical conventions:
  [pattern] - optional  
  {pattern} - zero or more repetitions  
  pattern<pattern'> - elements from pattern but not from pattern'  
###syntax:
  program     = {token | whitespace} 'EOF'  
  whitespace  = whitesymbol {whitesymbol}  
  whitesymbol = newline | space | tab  
  tab         = horizontal tab  
  space       = a space  
  small       = 'a' | 'b' | ... | 'z'  
  large       = 'A' | 'B' | ... | 'Z'  
  digit       = '0' | '1' | ... | '9'  
  special     = '(' | ')' | ',' | '[' | ']' | '->' | '<-' | '..' | '::'  
  token       =	literal | special | op | reservedid  
  literal     = integer | boolean  
  boolean     = 'True' | 'False'  
  integer     = digit {digit}  
  id          = (small {small | large | digit})  
  funid       = (large {small | large | digit})  
  reservedid  = 'else' | 'if' | 'then'  
  op          = l1op | l2op | l3op | l4op | l5op | l6op | l7op |  
  l1op        = '** '  
  l2op        = '* ' | '\'  
  l3op        = '+' | '-'  
  l4op        = '|' | '&'  
  l5op        = '!'  
  l6op        = '>' | '<' | '<=' | '=>' | '=='  
  l7op        = '='  

  type        = 'Bool' | 'Int'  
  body        = {decl | def}  
  decl        = funid '::' type {'->' type} newline  
  def         = funid id {id} '=' {exp} {newline exp} newline  
  exp         = boolean | integer | ifstatement | id | funid {exp}  
                | ( exp ) | exp1 | list |  
  exp1        = id '=' exp2  
  exp2        = exp1 l6op exp2 | exp2  
  exp3        = exp2 l5op exp3 | exp3  
  exp4        = exp3 l4op exp4 | exp4  
  exp5        = exp4 l3op exp5 | exp5  
  exp6        = exp5 l2op exp6 | exp6  
  exp7        = exp6 l1op exp7 | exp7  
  exp8        = exp  

  ifstatement = 'if' cond 'then' exp ['else' exp]  
  list        = '['member {',' member}] | [comp] | [integer..[integer]']'  
  member      = exp<id | ifstatement>  
  const       = exp<boolean | list | ifstatement>  
  comp        = member{, member} '|' id '<-' list {',' id <- list}  
  cond        = boolean | id {exp} | exp  
  newline     = 'LF'  
