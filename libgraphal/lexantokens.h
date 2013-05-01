/*
 * Copyright 2008 Michal Turek
 *
 * This file is part of Graphal library.
 * http://graphal.sourceforge.net/
 *
 * Graphal library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Graphal library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LEXANTOKENS_HPP
#define LEXANTOKENS_HPP

#include "node.h"
#include "nodeblock.h"
#include "parser.h"

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


#endif
