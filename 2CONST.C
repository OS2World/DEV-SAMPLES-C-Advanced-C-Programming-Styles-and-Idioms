/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

static const int SIZE1 = 10;

class C {
	static const int SIZE2;
	char vec1[SIZE1];
//	char vec2[SIZE2];
};

const int C::SIZE2 = 10;
