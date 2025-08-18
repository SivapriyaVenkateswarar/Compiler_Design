Source code -> constituent pieces -> intermediate code

Syntax: Structure of the program

Semantics: What the program means

Lexical Analyzer: Converts complicated constructs like identifiers (sequence of characters) to a single unit called tokens.

Two kinds of intermediate code generation:
-
* Syntax tree:
  - Produced by parser
  - loop name as root-> right side with body of loop -> left side with condition of statement.
* Three-code address:
  - converted by parser after the syntax tree. 
  - At most one operation per instruction (Comparison, binary operation, computation)

  Syntax definition
  -
  

