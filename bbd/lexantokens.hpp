/*
 *      lexantokens.hpp
 *
 *      Copyright 2008 Michal Turek <http://woq.nipax.cz/>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#ifndef LEXANTOKENS_HPP
#define LEXANTOKENS_HPP

enum LEXTOKEN
{
	LEX_EOF = 0,        // End of file
	LEX_ERROR,          // Error

	LEX_FUNCTION,       // function
	LEX_RETURN,         // return
	LEX_IF,             // if
	LEX_ELSE,           // else
	LEX_WHILE,          // while
	LEX_FOR,            // for
	LEX_FOREACH,        // foreach
	LEX_BREAK,          // break
	LEX_CONTINUE,       // continue
	LEX_NULL,           // null
	LEX_TRUE,           // true
	LEX_FALSE,          // false

	LEX_LVA,            // {  vinculum
	LEX_RVA,            // }
	LEX_LPA,            // (  parenthesis
	LEX_RPA,            // )
	LEX_LSA,            // [  square bracket
	LEX_RSA,            // ]
	LEX_COMMA,          // ,
	LEX_SEMICOLON,      // ;
	LEX_DOT,            // .

	LEX_OP_ASSIGN,      // =
	LEX_OP_EQUAL,       // ==
	LEX_OP_NOT_EQ,      // !=
	LEX_OP_LESS,        // <
	LEX_OP_LESS_EQ,     // <=
	LEX_OP_GREATER,     // >
	LEX_OP_GREATER_EQ,  // >=
	LEX_OP_PLUS,        // +
	LEX_OP_PLUS_AS,     // +=
	LEX_OP_PLUS_PLUS,   // ++
	LEX_OP_MINUS,       // -
	LEX_OP_MINUS_AS,    // -=
	LEX_OP_MINUS_MINUS, // --
	LEX_OP_MULT,        // *
	LEX_OP_MULT_AS,	    // *=
	LEX_OP_DIV,         // /
	LEX_OP_DIV_AS,      // /=
	LEX_OP_MOD,         // %
	LEX_OP_MOD_AS,      // %=
	LEX_OP_NOT,         // !
	LEX_OP_AND,         // &&
	LEX_OP_OR,          // ||

	LEX_INT,            // 58 + int
	LEX_FLOAT,          // 0.58 + float
	LEX_STRING,         // "str"/'str' + string
	LEX_NAME            // identifier + string
};

#endif
