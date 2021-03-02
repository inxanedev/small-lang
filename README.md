# small-lang
C++ interpreter for a for-fun language - SmallLang.
# specification
SmallLang is a very small language with variables and uses jumps and labels as the control flow.

It's an interpreted language, and this repository is the source code of the interpreter.

These are all the instructions available:

    set <variable: text> <value: text/number>
    L sets the specified variable
    print <variable: text>
    L prints the contents of the specified variable
    print_text <message: text>
    L prints the specified text, you don't enclose it in quotes
    newline
    L prints a newline to the console
    add/sub/mul/div <variable: text> <value: number>
    L applies the operation to the variable, throws exception if variable isn't of type number
    addv/subv/mulv/divv <variable: text> <variable 2: text>
    L same as above but not taking in a number as the second value but another variable
    LABEL <label name: text>
    L creates new label at the line the instruction is on
    jump <label name: text>
    L jumps to specified label unconditionally
    jump_eq <label name: text> <variable: text> <value: str/num>
    L jumps to the specified label if the variable's contents is the same as value
    jump_neq <label name: text> <variable: text> <value: str/num>
    L same as jump_eq but jumps if NOT equal
    jump_eqv <label name: text> <variable: text> <variable 2: text>
    L jumps to the specified label if both of the variables are equal
    jump_neqv <label name: text> <variable: text> <variable 2: text>
    L same as jump_eqv but jumps if NOT equal
    unset <variable: text>
    L removes a variable from memory
    input_str <variable: text>
    L asks the user for a line of text and saves it into the variable specified
    input_num <variable: text>
    L asks the user for a number and saves it into the variable specified

