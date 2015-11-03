# ExtendedCal
<1>  the improvement compared with the assignment one:

  a. I added the comments for the key part of the code line to make the programming more readable
  
  b. I accepted the suggestion to give a longer name for types.
  
<2> the difference between the two assignment:

  a. the order I built up the project is from AST to Lexer to Parser to Main. AST create the basic element we will use in the following step,
  Lexer part is for creating tokens, Parser is to build AST tree, Main is to finish input and output.

  b. the first one is easier(just need to deal with the number from 0 to 9), so I do not use tokens(intead, use strings) to do the implementation. But as with a extended calculator,
  using tokens can make your implementation step clearer and easier to control.
  
  c. as to a big specific change about the basic class, I think, is to add unary class to make the expression like: -7 become possible
