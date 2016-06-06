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
  reservedid  = 'else' | 'if' | 'then' | 'return' 
  op          = l1op | l2op | l3op | l4op | l5op | l6op | l7op |  
  l1op        = '** '  
  l2op        = '* ' | '\'  
  l3op        = '+' | '-'  
  l4op        = '|' | '&'   
  l5op        = '>' | '<' | '<=' | '=>' | '=='  
  l6op        = '='  
  type        = 'Bool' | 'Int' | 'List'
  newline     = 'LF'  
  
  body        = {decl | def}  
  decl        = funid '::' type {'->' type} newline  
  def         = funid id {id} '=' exp newline {exp newline} newline
  exp         = boolean | integer | ifstatement | id | funid '(' {exp} ')' 
                | ( exp ) | exp1 | list 
  exp1        = id l6op exp2 | exp2   
  exp2        = exp2 l5op exp3 | exp3  
  exp3        = exp3 l4op exp4 | exp4  
  exp4        = exp4 l3op exp5 | exp5  
  exp5        = exp5 l2op exp6 | exp6  
  exp6        = exp6 l1op exp7 | exp7 
  exp7        = exp
  ifstatement = 'if' exp newline 'then' newline exp {newline exp} [ newline 'else' newline exp] 'fi' 
  list        = '['{exp}']' | '['comp']' | '['exp..[exp]']'   
  comp        = exp {',' exp} '|' id '<-' (list | id | funid {exp})  {',' id <- (list | id) | funid {exp}}

  
