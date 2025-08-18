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

-> Note: A construct is simply a syntactic unit or structure in a programming language. (example: expression, statement, loops, etc)

Syntax definition
-
* Grammar:
  - used to define the syntax of a programming language.
  - Describes Hierarchical structure of the program: CFG converts to parser tree.
  * Components of a CFG:
    - stmt -> if (expr) stmt else stmt
    - Terminal symbols: lexical/elementary symbols of the statement (if, and parentheses in this example)
    - Non-terminal symbols: set of terminal units representing a statement. (stmt, expr)
    - production: Consists of a non-terminal on the left side, referred to as the head, and a sequence of terminals/non-terminals on the right side called the body.
      - Production also represents the construct -> written form of construct.
      
      

