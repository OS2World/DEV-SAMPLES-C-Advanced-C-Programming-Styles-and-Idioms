/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

int main() {
   Employee *ted =
       new Employee(
         "ted", 2823763108
       );
   // . . . .
   ted->logTimeWorked(8);
   ted->printPaycheck();
   delete ted;
}
