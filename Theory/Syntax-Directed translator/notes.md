* Source code -> constituent pieces -> intermediate code
* Syntax: Structure of the program
* Semantics: What the program means

Lexical Analyzer: 
* converts groups sequences of characters (identifiers, keywords, operators, etc.) into meaningful units called lexemes, each of which is represented as a single token in the form <token name, attribute value>.
    - Token name: terminal symbol
    - Attribute value: pointer to the symbol table.  

Two kinds of intermediate code generation:
-
* Syntax tree:
  - Produced by parser
  - Example representation for loops:  loop name as root-> right side with body of loop -> left side with condition of statement.
* Three-code address:
  - converted by parser after the syntax tree. 
  - At most one operation per instruction (Comparison, binary operation, computation)

-> Note: A construct is simply a syntactic unit or structure in a programming language. (example: expression, statement, loops, etc)

Syntax definition
-
* Grammar:
  - set of rules to define the syntax of a programming language.
  - Describes Hierarchical structure of the program: CFG converts to parser tree.
  - ex:
  <pre> stmt → if (expr) stmt else stmt
    expr → expr + expr | id  </pre>

  * Components of a CFG:
    - stmt -> if (expr) stmt else stmt
    - Terminal symbols: lexical/elementary symbols of the statement (if, and parentheses in this example)
    - Non-terminal symbols: set of terminal units representing a statement. (stmt, expr)
    - production: Consists of a non-terminal on the left side, referred to as the head, and a sequence of terminals/non-terminals on the right side called the body.
      - Production describes how a programming construct (Assignment, Conditional statements, loops, etc) is written using terminals and non-terminals.
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
    - now, if we have a production rule : (expr) -> id
    - Replace (expr) in RHS
    - (stmt) -> id

-> Note: A production rule is a replacement rule in a grammar. (converts non-terminals to terminal strings)

  * Parsing:
    - A parser is the component of a compiler that checks whether a given input string can be generated from the grammar’s production rules,
    - and if not, it reports a syntax error.

  * Parse tree:
    -shows how the start symbol converts to terminal strings.
    * Components of a parse tree:
      - In a parse tree, the parent node represents a non-terminal and its children represent how that non-terminal is expanded. (Parent -> whole, children -> parts of the whole)
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
      - Quantities can be associated with programming constructs using grammars.
        - Eg:
            - Type information (eg: FLOAT, BOOL)
            - Intermediate code fragments (eg: instructions generated for an expression)
            - Memory locations (eg: address of a variable)
            - Values (eg: constant values)
        - Attributes are attached to the grammar symbols (Terminals, non-terminals) 
      - Syntax directed: Notation used for pointing the semantic actions to the production.
        - A syntax-directed definition (SDD) consists of:
          - A set of attributes for each grammar symbol.
          - A set of semantic rules for each production that define how attributes are computed.
      - Working:
        - Parser (syntax analyzer) goes through the input program using the grammar (production rules).
        - Every time a production is applied, its attached semantic action is executed.
        - All these little fragments run in the order the parser applies the rules.
        - The combined effect of all those actions = the full translation
    - Postfix notation:
      - Rules:
        - If E is variable/constant → postfix(E) = E
        - If E = E₁ op E₂ → postfix(E) = postfix(E₁) postfix(E₂) op
        - If E = (E₁) → postfix(E) = postfix(E₁)
      - Working:
        - Scan left to right
            - When you see an operator, take required operands from its left
            - Apply operator, replace expression with result
            - Repeat until finished
      - Synthesized attributes:
        - Attribute evaluation process:
          - Construct a parse tree for the given input string.
          - Apply the semantic rules to compute attribute values at each node.
          - Use the notation X.a to denote the value of attribute a of grammar symbol X at a node.
        - Annotated Parse Tree: A parse tree with attributes evaluated is called an annotated parse tree.
        - Synthesized Attribute: If we can derive the attribute of a Node in the parse tree only with their children nodes. (Term → id)
          - eg: expr -> expr1 + term : expr's attirbute is synthesized.
          - can be evaluated bottom-up
        - Inherited Attribute: Node evaluated from parents and siblings
          - eg: int c, Decl (parent) → DataType id (child)
          - Uses a Top-down approach.
      - Simple Syntax Directed Definition:
        - A syntax-directed definition (SDD) is called simple if it follows a straightforward translation process.
        - The translation of a nonterminal on the left-hand side of a production is:
           - The concatenation of the translations of the symbols on the right-hand side.
           - The concatenation happens in the same order as the symbols appear in the production.
           - You can also add extra strings (like operators, punctuation, or formatting) in between.
        - eg: PostFix:
          - expr.t = expr1 || term || '+'  -> concatenation of all these terms will give expr, thus simple SDD.
      - Tree Traversal:
        - Tree Traversal is used for evaluating attributes.
        - For synthesized attributes, any bottom-up traversal is sufficient.
        - For inherited attributes, ordering is trickier because they may need values from the parent or siblings.
      - syntax-directed translation:
        - SDD only allows calculating the attributes while respecting dependencies.
        - SDT attaches the program fragment to the grammar production to define an order of execution.
        - For Parse tree representation of action:
          - A semantic action is represented as an extra child connected by a dashed line.
          - The action node has no children, so it executes immediately when reached.

-> Note:
- Lexer = “word detector” → turns letters into meaningful words (tokens).
- Parser = “grammar checker” → ensures the sentence (sequence of tokens) is grammatically correct.
    
## Parsing:
The parser takes the token stream from the lexer.
It checks if the tokens conform to the grammar rules.
If the tokens fit the grammar, parsing succeeds (the compiler can translate/execute the code).
If the tokens violate the grammar, the parser reports a syntax error.

- How does the parser check if the token stream matches the predefined grammar rules?
    - Conceptually, it builds a tree structure:
        - Root = start symbol of the grammar
        - Internal nodes = non-terminals
        - Leaves = tokens (terminals) from the lexer
    - Even if the parser doesn’t physically build the tree, it’s still tracing this structure in its logic.
      
### Top-Down vs Bottom-Up Parsers

- **Top-Down Parsing:**  
  - Construction starts at the root and proceeds towards the leaves.  
  - Popular and more efficient to build.  
- **Bottom-Up Parsing:**  
  - Construction starts at the leaves and proceeds towards the root.  
  - Can handle a larger class of grammars and translation schemes.  

#### Top-down parsing 
builds a parse tree **from the root to the leaves**. 
Key terms:
- **Lookahead symbol:** The current terminal in the input being scanned, used to select the appropriate production. Initially, it is the leftmost terminal of the input string.  
- **ε-production:** A production that represents an **empty string**, used when no other production matches.  
- **Non-terminal node:** A node in the parse tree labeled with a non-terminal symbol.  
- **Terminal node:** A node in the parse tree labeled with a terminal symbol.

##### Steps:

1. **Start at the root**  
   - Label the root with the **start symbol** (e.g., `stmt`).
2. **Expand a non-terminal node in tree**  
   - At node `N` labeled with non-terminal `A`:  
     - Select a production for `A` using the lookahead symbol.  
     - Create children for each symbol in the production body.
3. **Move to the next node**  
   - Typically the **leftmost unexpanded non-terminal** in the tree.
4. **Match terminals of the tree with lookahead in the input**  
   - If the current node is a **terminal** and matches the lookahead, advance in both the input and the parse tree.  
   - Update the lookahead to the next terminal in the input.
5. **Repeat**  
   - Continue until the parse tree fully generates the input string. (Uses backtracking).

### Predictive Parsing

**Definition:**  
Predictive parsing is a **top-down parsing method** that uses a **lookahead symbol** to decide which production of a nonterminal to apply, **without backtracking**.

#### Lookahead Symbol
- The next input terminal being scanned.  
- Used to proactively select the correct production.
  
#### FIRST Set
- The set of terminals that can appear at the start of strings** derived from a production.  
- Computed recursively for nonterminals.  
- Guides the parser to choose the production whose FIRST set contains the lookahead.

#### Key Characteristics
- **Deterministic:** One lookahead symbol is sufficient.  
- **No backtracking required.**  
- Grammar must be **LL(1)**:  
  - No overlapping FIRST sets  
  - No left recursion  
- Can handle ε-productions carefully using FOLLOW sets if needed.

#### How It Works (Stepwise)
1. Start with the start symbol at the root of the parse tree.  
2. Expand nonterminals using the production whose FIRST set contains the lookahead.  
3. Match terminals with the lookahead symbol and advance input.  
4. Repeat until the entire input is parsed and the parse tree is complete.

#### Difference from General Top-Down Parsing
- **General top-down:** Lookahead is used only to check matches; may require backtracking.  
- **Predictive parsing:** Lookahead directs the parser, no guessing; FIRST sets ensure unique choices.

Note:
- An ε-production is a grammar rule that allows a nonterminal to produce an empty string (do nothing).
- If no other production matches the lookahead, the parser can apply the ε-production as a default.

### Characteristics of a Predictive Parser

- For each nonterminal A, the parser:
  - Selects a production using the lookahead symbol based on FIRST sets
  - Executes the production body step by step:
    - If the symbol is a terminal → it must match the lookahead → consume input
    - If the symbol is a nonterminal → recursively call its parsing function
    - If a mismatch occurs → report a syntax error
- Requires FIRST sets to be disjoint to avoid backtracking
- Uses a single lookahead symbol to make parsing decisions
- Works only with LL(1) grammars

### What is a Translation Scheme?

- A translation scheme is a grammar with embedded semantic actions. (Grammar+action)
- Semantic actions specify what computation or translation should happen during parsing

note:
- User code: 3 + 4
- Grammar: matches it as expr → expr + term
- Semantic action: { expr.value = expr1.value + term.value } → actually performs the addition

### Syntax-Directed Translation with a Predictive Parser
- A predictive parser can be extended to perform translation while parsing
- Semantic actions are executed in the order specified in the production rules

### Steps to Build a Syntax-Directed Translator
1. Start with a context-free grammar
2. Construct a predictive parser from the grammar
3. Add semantic actions to form a translation scheme
4. Insert semantic actions into the parser code:
   - If an action appears after a grammar symbol X → place it after processing X
   - If an action appears at the beginning of a production → place it before parsing that production
5. Perform parsing and translation simultaneously

### Left Recursion
#### 1. Problem: Left Recursion

- A grammar is **left-recursive** if a nonterminal appears as the first symbol in its own production:

A → A α | β

- α = some sequence  
- β = base case  

**Example:**

E → E + T | T

- **Problem:** Predictive parsers (LL(1), recursive descent) loop infinitely:

E → E + T → E + T + T → ...


- **Cause:** The parser calls itself before consuming input.

#### 2. Solution: Remove Left Recursion

- **General transformation:**

A → A α | β becomes:

A → β R
R → α R | ε

Where:  
- β = base case (does not start with A)  
- α = recursive part  
- R = new helper nonterminal  
- ε = empty string (stops recursion)

#### 3. Example: `E → E + T | T`

**Step 1:** Identify parts  

A = E
α = + T
β = T

**Step 2:** Apply transformation

E → T R
R → + T R | ε


#### 4. Intuition of R

- `E → T R`  
  - `T` = first term  
  - `R` = optional repeated `+ T` blocks  

- `R → + T R | ε`  
  - `+ T R` = “add another term and repeat if needed”  
  - `ε` = “stop adding terms”  

**Visual analogy:**

- `E = T` → first term  
- `R = + T + T + T ...` (optional repetition)

## Translator:

- In compilers, a translator is a program that converts one form of input into another form. 
- A syntax-directed translator follows grammar rules and uses semantic actions to produce output while parsing.
- Ex: converting rules to postfix.
  - Input expression: 3+4
  -  <pre>
      expr → expr + term { print('+') }
      expr → term
      term → 3 { print('3') }
      term → 4 { print('4') }
    </pre>
- Here, print means produce output as part of translation.

## Abstract Syntax Tree (AST)
A tree-like data structure used in **compilers/interpreters** to represent the **semantic structure** (meaning) of a program.

### Structure
- **Interior nodes:** Operators or constructs (e.g., `+`, `-`, `if`, `while`)  
- **Children nodes:** Operands or subcomponents of the operator  

**Example:** Expression `9 - 5 + 2`

<pre>
             -
           /   \
          9     +
              /   \
             5     2
</pre>

- **Root:** `+` (last operator applied)  
- **Left subtree:** `9 - 5` (evaluated first)  
- **Right child:** `2`  
- Reflects **left-to-right evaluation** for operators with the same precedence.

## Why AST is Useful
- Simplifies **semantic actions**: Translation schemes operate on AST instead of full parse tree  
- Removes unnecessary grammar details: helper nodes like `expr`, `term` are removed  
- Closer to **actual computation**: matches operator precedence and subexpression evaluation  

### Applications

| Stage                   | Use of AST                                               |
| ----------------------- | -------------------------------------------------------- |
| Semantic Analysis       | Type checking, symbol table attachment, scope resolution |
| Code Generation         | Translate AST into intermediate/final code               |
| Optimization            | Simplify expressions, remove redundancies                |
| Interpreter Execution   | Walk AST to execute code directly                        |
| Static Analysis         | Linters, security tools analyze AST structure            |
| Program Transformations | Refactoring, transpilers, automated code edits           |

## Statement
> “A good translation scheme should have a grammar whose parse trees are close to ASTs.”
**Meaning:**
- Grammar should be designed so that the parse tree already resembles the AST  
- Makes **semantic actions** (like generating postfix or 3-address code) easier and cleaner  
- Reduces the need for heavy **AST transformations** after parsing
