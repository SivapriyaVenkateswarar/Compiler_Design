Source code -> constituent pieces -> intermediate code

Syntax: Structure of the program

Semantics: What the program means

Lexical Analyzer: Converts complicated constructs like identifiers (sequence of characters) to a single unit called tokens.\
* Lexical Analyzer converts a group of characters into meaningful units called lexemes. (lexemes contains <token name, attribute value>
    - This token name: terminal
    - Attribute value: pointer to the symbol table.  

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
    - You list all its rules, and you choose one special nonterminal (called the start symbol) as the root of the grammar. That’s where parsing always begins.

* Derivations:
  - Start with the start symbol.
  - Look at your current string.
    - If you see a non-terminal in it,
    - then find a production rule where that non-terminal is on the LHS.
  - Replace that non-terminal with the RHS of the rule.
  - Keep repeating until no non-terminals remain (only terminals).

  - eg:
    - start with: (stmt) -> (expr)
    - now, we have a production rule : (expr) -> id
    - Replace (expr) in RHS
    - (stmt) -> id

-> Note: A production rule is a replacement rule in a grammar. (converts non-terminals to terminal strings)

  * Parsing:
    - A parser is the component of a compiler that checks whether a given input string can be generated from the grammar’s production rules,
    - and if not, it reports a syntax error.

  * Parse tree:
    -shows how the start symbol converts to terminal strings.
    * Components of a parse tree:
      - In a parse tree, the parent node represents a non-terminal and its children represent how that non-terminal is expanded.
      - Root → The root is labeled with the start symbol of the grammar.
      - Leaves → Each leaf is labeled with either a terminal symbol or ε (empty string).
      - Interior Nodes → Each interior node is labeled with a non-terminal symbol.
      - Production Rule Mapping →
        - If an interior node is labeled by a non-terminal A, and its children (from left to right) are labeled X₁, X₂, …, Xₙ,
        - then there must be a production rule:
           - A → X₁ X₂ … Xₙ
           - where each Xᵢ is either a terminal or non-terminal.
        - Special case: If the production is A → ε, then the node labeled A has a single child labeled ε.
        - Note -> the parse tree varies from input to input.
    * Associativity of operators:
      - When there are two operators on either side of an operand, how do we decide which operator to apply first?
      - Eg: 9+5+2
      - left associative: operand belongs to the left-most operator.
        - Eg: Arithmetic operators are usually left-associated:
          - (9+5)+2 or (9-5)-2
      - Right associative: operand belongs to the right-most operator.
        - eg: exponential or "=" in some languages.
        - a=b=c -> a=(b=c)
    * Precedence:
      - Lowest precedence: + and - (left-associative).
      - Higher precedence: * and / (left-associative).
      - Parentheses () can override precedence.
        
    * Difference between production and rules:
      - Production: a single rewriting instruction in the grammar.
      - Rules: collection of productions for the same nonterminal.
    * Syntax-Directed Translation:
      - Mapping the semantic actions to the grammar rules.
      - Semantic actions: what to do when that production is recognized.
      - Eg:
        Expr → Expr1 + Term  // Production
       { translate(Expr1);
         translate(Term);
         handle('+'); }  // Semantic action
      - Attribute: A quantity associated with the construct.
        - Eg:
            - Type information (eg: FLOAT, BOOL)
            - Intermediate code fragments (eg: instructions generated for an expression)
            - Memory locations (eg: address of a variable)
            - Values (eg: constant values)
        - Attributes are attached to the grammar symbols (Terminals, non-terminals) 
      - Syntax directed: Notation used for pointing the semantic actions to the production.
      - Working:
        - Parser (syntax analyzer) goes through the input program using the grammar (production rules).
        - Every time a production is applied, its attached semantic action is executed.
        - All these little fragments run in the order the parser applies the rules.
        - The combined effect of all those actions = the full translation
    - Postfix notation:
      ## Notation
  

