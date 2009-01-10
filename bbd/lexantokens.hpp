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

#include "node.hpp"
#include "nodeblock.hpp"
#include "parser.hpp"

#define LEX_EOF 0
#define LEX_OP_PLUS '+'
#define LEX_OP_MINUS '-'

#define LEX_OP_MULT '*'
#define LEX_OP_DIV '/'
#define LEX_OP_MOD '%'

#define LEX_LVA '{'
#define LEX_RVA '}'
#define LEX_LPA '('
#define LEX_RPA ')'
#define LEX_LSA '['
#define LEX_RSA ']'
#define LEX_COMMA ','
#define LEX_SEMICOLON ';'
#define LEX_DOT '.'

#define LEX_OP_NOT '!'
#define LEX_OP_LESS '<'
#define LEX_OP_GREATER '>'

#define LEX_OP_ASSIGN '='

#define LEX_QUESTIONMARK '?'
#define LEX_COLON ':'


typedef int LEXTOKEN;

/*
enum LEXTOKEN
{
	LEX_EOF = 0,        // End of file
	LEX_ERROR,          // Error

	LEX_INCLUDE,        // include
	LEX_DEFINE,         // define
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
	EQ_OP,       // ==
	NE_OP,      // !=
	LEX_OP_LESS,        // <
	LE_OP,     // <=
	LEX_OP_GREATER,     // >
	GE_OP,  // >=
	LEX_OP_PLUS,        // +
	ADD_ASSIGN,     // +=
	INC_OP,   // ++
	LEX_OP_MINUS,       // -
	SUB_ASSIGN,    // -=
	DEC_OP, // --
	LEX_OP_MULT,        // *
	MUL_ASSIGN,     // *=
	LEX_OP_DIV,         // /
	DIV_ASSIGN,      // /=
	LEX_OP_MOD,         // %
	MOD_ASSIGN,      // %=
	LEX_OP_NOT,         // !
	AND_OP,         // &&
	OR_OP,          // ||

	LEX_INT,            // 58 + int
	LEX_FLOAT,          // 0.58 + float
	LEX_STRING,         // "str"/'str' + string
	LEX_NAME            // identifier + string
};
*/
#endif
