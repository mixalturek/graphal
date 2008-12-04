/*
 *      lexan.cpp
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

#include <stdexcept>
#include <cmath>
#include "lexan.hpp"
#include "lexaniteratorstring.hpp"
#include "lexaniteratorfile.hpp"
#include "logger.hpp"


/////////////////////////////////////////////////////////////////////////////
////

Lexan::Lexan(const string& source, bool filename)
	: BaseObject(),
	m_source(),
	m_defines(),
	m_int(0),
	m_float(0.0f),
	m_string("")
{
	if(filename)
		m_source.push(new LexanIteratorFile(source));
	else
		m_source.push(new LexanIteratorString("init", source));
}

Lexan::~Lexan(void)
{
	while(!m_source.empty())
	{
		delete m_source.top();
		m_source.pop();
	}
}


/////////////////////////////////////////////////////////////////////////////
////

LEXTOKEN Lexan::checkKeyword(void)
{
	// Check keywords
	if(m_string == "function")
		return LEX_FUNCTION;
	if(m_string == "return")
		return LEX_RETURN;
	if(m_string == "if")
		return LEX_IF;
	if(m_string == "else")
		return LEX_ELSE;
	if(m_string == "while")
		return LEX_WHILE;
	if(m_string == "for")
		return LEX_FOR;
	if(m_string == "foreach")
		return LEX_FOREACH;
	if(m_string == "break")
		return LEX_BREAK;
	if(m_string == "continue")
		return LEX_CONTINUE;
	if(m_string == "null")
		return LEX_NULL;
	if(m_string == "true")
		return LEX_TRUE;
	if(m_string == "false")
		return LEX_FALSE;

	// Check include and define
	if(m_string == "include")
	{
		parseInclude();
		return nextToken();
	}
	if(m_string == "define")
	{
		parseDefine();
		return nextToken();
	}

	// Try to expand a macro
	if(expandMacro())
		return nextToken();

	// The string is variable or function name
	return LEX_NAME;
}


bool Lexan::expandMacro(void)
{
	// TODO: test this function
	map<string, string>::iterator it = m_defines.find(m_string);

    if(it != m_defines.end())
    {
#ifdef DEBUG
		DBG << getSource() << _(":") << getPos() << _(" Expanding macro: ") << it->first << endl;
#endif // DEBUG
		m_source.push(new LexanIteratorString(it->first, it->second));
		return true;// Macro expanded
    }

    return false;// It wasn't a macro
}


/////////////////////////////////////////////////////////////////////////////
//// State machine states

enum LEXSTATE
{
	ST_DEFAULT,         // default, begin

	ST_CPP_COMMENT,     // //
	ST_C_COMMENT,       // /.*
	ST_C_COMMENT_END,   // *./

	ST_NAME,            // identifier

	ST_STRING,          // "
	ST_STRING_ESC,      // \.
	ST_STRING_ESC_HEX,  // \x
	ST_STRING_ESC_HEX_1,// \xA
	ST_STRING_ESC_OCT,  // \12
	ST_STRING_ESC_OCT_1,// \123

	ST_INT,             // 5
	ST_INT_ZERO,        // 0
	ST_INT_OCT,         // 02
	ST_INT_HEX,         // 0xffe
	ST_FLOAT,           // 0.58
	ST_EXP_SIGN,        // 15e-
	ST_EXP,             // 15e4
	ST_DOT,             // .

	ST_OP_ASSIGN,       // =
	ST_OP_NOT,          // !
	ST_OP_LESS,         // <
	ST_OP_GREATER,      // >
	ST_OP_PLUS,         // +
	ST_OP_MINUS,        // -
	ST_OP_MULT,         // *
	ST_OP_DIV,          // /
	ST_OP_MOD,          // %
	ST_OP_AND,          // &&
	ST_OP_OR            // ||
};


/////////////////////////////////////////////////////////////////////////////
////

LEXTOKEN Lexan::nextToken(void)
{
	int c;
	LEXSTATE state = ST_DEFAULT;

	float float_dms = 0.1;	// Multiplier of float number (after point)
	int exp = 0;		// Exponent
	int exp_sign = 1;	// 1 or -1


	while(true)
	{
		if(m_source.empty())
			return LEX_EOF;
		else
			c = m_source.top()->get();

		switch(state)
		{
		case ST_DEFAULT:
			if(isspace(c))
				break;
			if(isalpha(c) || c == '_')
			{
				state = ST_NAME;
				m_string = c;
				break;
			}
			if(c == '0')
			{
				state = ST_INT_ZERO;
				m_int = 0;
				break;
			}
			if(c >= '1' && c <= '9')// != 0, this is not OCT number!
			{
				state = ST_INT;
				m_int = c - '0';
				break;
			}

			if(c == ',')
				return LEX_COMMA;
			if(c == ';')
				return LEX_SEMICOLON;
			if(c == '(')
				return LEX_LPA;
			if(c == ')')
				return LEX_RPA;
			if(c == '{')
				return LEX_LVA;
			if(c == '}')
				return LEX_RVA;
			if(c == '[')
				return LEX_LSA;
			if(c == ']')
				return LEX_RSA;

			if(c == '=')
			{
				state = ST_OP_ASSIGN;
				break;
			}
			if(c == '+')
			{
				state = ST_OP_PLUS;
				break;
			}
			if(c == '-')
			{
				state = ST_OP_MINUS;
				break;
			}
			if(c == '*')
			{
				state = ST_OP_MULT;
				break;
			}
			if(c == '/')
			{
				state = ST_OP_DIV;
				break;
			}
			if(c == '%')
			{
				state = ST_OP_MOD;
				break;
			}
			if(c == '.')
			{
				state = ST_DOT;
				break;
			}
			if(c == '<')
			{
				state = ST_OP_LESS;
				break;
			}
			if(c == '>')
			{
				state = ST_OP_GREATER;
				break;
			}
			if(c == '!')
			{
				state = ST_OP_NOT;
				break;
			}
			if(c == '&')
			{
				state = ST_OP_AND;
				break;
			}
			if(c == '|')
			{
				state = ST_OP_OR;
				break;
			}

			if(c == '"')
			{
				state = ST_STRING;
				m_string.clear();
				break;
			}

			if(c == EOF)		// End of file
			{
				delete m_source.top();
				m_source.pop();
				// state = ST_DEFAULT;// We are here
				break;
			}

			ERROR << getSource() << _(":") << getPos()
				<< _(" Unexpected character: '")
				<< (char)c << "' (ascii " << c << ")" << endl;

			return LEX_ERROR;

		case ST_CPP_COMMENT:		// //
			if(c == '\n')
			{
				state = ST_DEFAULT;
				break;
			}
			if(c == EOF)		// End of file
			{
				delete m_source.top();
				m_source.pop();
				state = ST_DEFAULT;
				break;
			}

			// Stay in this state
			break;

		case ST_C_COMMENT:		// /*
			if(c == '*')
			{
				state = ST_C_COMMENT_END;
				break;
			}
			if(c == '\n')
			{
				break;
			}
			if(c == EOF)
			{
				ERROR << getSource() << _(":") << getPos()
					<< _(" Unexpected end of source: unterminated /* c-style */ comment")
					<< endl;

				delete m_source.top();
				m_source.pop();
				state = ST_DEFAULT;

				return LEX_ERROR;
			}

			// Stay in this state
			break;

		case ST_C_COMMENT_END:		// */
			if(c == '/')
			{
				state = ST_DEFAULT;
				break;
			}
			if(c == '*')// /****something*like*this*****/
			{
				// Stay in this state
				break;
			}
			if(c == '\n')
			{
				// Stay in this state
				break;
			}
			if(c == EOF)
			{
				ERROR << getSource() << _(":") << getPos()
					<< _(" Unexpected end of source: unterminated /* c-style */ comment")
					<< endl;

				delete m_source.top();
				m_source.pop();
				state = ST_DEFAULT;

				return LEX_ERROR;
			}

			// Everything else
			state = ST_C_COMMENT;
			break;

		case ST_NAME:			// identifier
			if(isalnum(c) || c == '_')
			{
				// Stay in this state
				m_string += c;
				break;
			}

			unget();
			return checkKeyword();

		case ST_STRING:			// "
			if(c == '\\')// Escape character
			{
				state = ST_STRING_ESC;
				break;
			}
			if(c == '"')// End of string
			{
				return LEX_STRING;
			}
			if(c == '\n')
			{
				ERROR << getSource() << _(":") << getPos()
					<< _(" Unexpected end of line: unterminated \"string\" constant")
					<< endl;
				return LEX_ERROR;
			}
			if(c == EOF)
			{
				ERROR << getSource() << _(":") << getPos()
					<< _(" Unexpected end of source: unterminated \"string\" constant")
					<< endl;

				delete m_source.top();
				m_source.pop();
				state = ST_DEFAULT;

				return LEX_ERROR;
			}

			// Stay in this state
			m_string += c;
			break;

		case ST_STRING_ESC:		// \escape
			if(c == 'a')// \a - Alert (Bell)
			{
				m_string += '\a';
				state = ST_STRING;
				break;
			}
			if(c == 'b')// \b - Backspace
			{
				m_string += '\b';
				state = ST_STRING;
				break;
			}
			if(c == 'f')// \f - Formfeed
			{
				m_string += '\f';
				state = ST_STRING;
				break;
			}
			if(c == 'n')// \n - Newline
			{
				m_string += '\n';
				state = ST_STRING;
				break;
			}
			if(c == 'r')// \r - Carriage return
			{
				m_string += '\r';
				state = ST_STRING;
				break;
			}
			if(c == 't')// \t - Horizontal tab
			{
				m_string += '\t';
				state = ST_STRING;
				break;
			}
			if(c == 'v')// \v - Vertical tab
			{
				m_string += '\v';
				state = ST_STRING;
				break;
			}
			if(c == 'x')// \xHH - HEX
			{
				m_int = 0;
				state = ST_STRING_ESC_HEX;
				break;
			}
			if(c >= '0' && c <= '7')// \000 - OCT
			{
				m_int = c - '0';
				state = ST_STRING_ESC_OCT;
				break;
			}
			if(c == '\\')// \\ Backslash
			{
				m_string += '\\';
				state = ST_STRING;
				break;
			}
			if(c == '\'')// \' Single quote
			{
				m_string += '\'';
				state = ST_STRING;
				break;
			}
			if(c == '\"')// \" Double quote
			{
				m_string += '\"';
				state = ST_STRING;
				break;
			}
			if(c == '\r')// Trash MS Windows \r
			{
				WARN << getSource() << _(":") << getPos()
					<< _(" Detected \\r character (CR, 13 in ascii) in string escape sequence after backslash. This would be without problem if you want to use multiline string here and your script uses CR-LF style of line ending (common for text editors under MS Windows)")
					<< endl;

				// Stay in this state and hope \n will continue
				break;
			}
			if(c == '\n')// Multiline string
			{
				state = ST_STRING;
				break;
			}
			if(c == EOF)
			{
				ERROR << getSource() << _(":") << getPos()
					<< _(" Unexpected end of source: unterminated \"string\" constant")
					<< endl;

				delete m_source.top();
				m_source.pop();
				state = ST_DEFAULT;

				return LEX_ERROR;
			}

			WARN << getSource() << _(":") << getPos()
				<< _(" Unrecognized escape sequence in \"string\" constant: '")
				<< (char)c << "' (ascii " << c << ")" << endl;

			m_string += '\\';
			m_string += c;
			state = ST_STRING;
			break;

		case ST_STRING_ESC_HEX:		// \xA
			if(isdigit(c))
			{
				m_int = c - '0';
				state = ST_STRING_ESC_HEX_1;
				break;
			}
			c = tolower(c);
			if(c >= 'a' && c <= 'f')
			{
				m_int = 10 + c - 'a';
				state = ST_STRING_ESC_HEX_1;
				break;
			}
			if(c == EOF)
			{
				ERROR << getSource() << _(":") << getPos()
					<< _(" Unexpected end of source: unterminated \"string\" constant")
					<< endl;

				delete m_source.top();
				m_source.pop();
				state = ST_DEFAULT;

				return LEX_ERROR;
			}

			WARN << getSource() << _(":") << getPos()
				<< _(" Character is not valid in \"string\" HEX escape sequence context: '")
				<< (char)c << "' (ascii " << c << ")" << endl;

			m_string += "\\x";
			unget();
			state = ST_STRING;
			break;

		case ST_STRING_ESC_HEX_1:	// \xAB
			if(isdigit(c))
			{
				m_int <<= 4;
				m_int += c - '0';
				m_string += m_int;
				state = ST_STRING;
				break;
			}
			c = tolower(c);
			if(c >= 'a' && c <= 'f')
			{
				m_int <<= 4;
				m_int += 10 + c - 'a';
				m_string += m_int;
				state = ST_STRING;
				break;
			}
			if(c == EOF)
			{
				ERROR << getSource() << _(":") << getPos()
					<< _(" Unexpected end of source: unterminated \"string\" constant")
					<< endl;

				delete m_source.top();
				m_source.pop();
				state = ST_DEFAULT;

				return LEX_ERROR;
			}

			WARN << getSource() << _(":") << getPos()
				<< _(" Character is not valid in \"string\" HEX escape sequence context: '")
				<< (char)c << "' (ascii " << c << ")" << endl;

			m_string += "\\x";
			m_string += (m_int < 10) ? '0' + m_int : 'a' + m_int - 10;// TODO: lower/upper
			unget();
			state = ST_STRING;
			break;

		case ST_STRING_ESC_OCT:		// \12
			if(c >= '0' && c <= '7')
			{
				m_int <<= 3;
				m_int += c - '0';
				state = ST_STRING_ESC_OCT_1;
				break;
			}
			if(c == EOF)
			{
				ERROR << getSource() << _(":") << getPos()
					<< _(" Unexpected end of source: unterminated \"string\" constant")
					<< endl;

				delete m_source.top();
				m_source.pop();
				state = ST_DEFAULT;

				return LEX_ERROR;
			}

			WARN << getSource() << _(":") << getPos()
				<< _(" Character is not valid in \"string\" OCT escape sequence context: '")
				<< (char)c << "' (ascii " << c << ")" << endl;

			m_string += '\\';
			m_string += '0' + m_int;
			unget();
			state = ST_STRING;
			break;

		case ST_STRING_ESC_OCT_1:	// \123
			if(c >= '0' && c <= '7')
			{
				m_int <<= 3;
				m_int += c - '0';

				if(m_int > 255)
				{
					WARN << getSource() << _(":") << getPos()
						<< _(" The value of \"string\" OCT escape sequence is too big ( > 0377)")
						<< endl;

					m_string += '\\';
					m_string += '0' + (m_int>>6);
					m_string += '0' + (m_int>>3)%8;
					m_string += '0' + m_int%8;
				}
				else
				{
					m_string += m_int;
				}

				state = ST_STRING;
				break;
			}
			if(c == EOF)
			{
				ERROR << getSource() << _(":") << getPos()
					<< _(" Unexpected end of source: unterminated \"string\" constant")
					<< endl;

				delete m_source.top();
				m_source.pop();
				state = ST_DEFAULT;

				return LEX_ERROR;
			}

			WARN << getSource() << _(":") << getPos()
				<< _(" Character is not valid in \"string\" OCT escape sequence context: '")
				<< (char)c << "' (ascii " << c << ")" << endl;

			m_string += '\\';
			m_string += '0' + (m_int>>3);
			m_string += '0' + m_int%8;
			unget();
			state = ST_STRING;
			break;

		case ST_INT:			// 5
			if(isdigit(c))
			{
				// Stay in this state
				m_int *= 10;
				m_int += c - '0';
				break;
			}
			if(c == '.')
			{
				m_float = m_int;
				state = ST_FLOAT;
				break;
			}
			if(tolower(c) == 'e')
			{
				m_float = m_int;
				state = ST_EXP_SIGN;
				break;
			}

			unget();
			return LEX_INT;

		case ST_INT_ZERO:		// 0
			if(c >= '0' && c <= '7')
			{
				m_int = c - '0';
				state = ST_INT_OCT;
				break;
			}
			if(c >= '8' && c <= '9')
			{
				ERROR << getSource() << _(":") << getPos()
					<< _(" This number is not valid in \"string\" OCT escape sequence context: '")
					<< (char)c << "' (ascii " << c << ")" << endl;

				return LEX_ERROR;
			}
			if(c == '.')
			{
				m_float = 0.0f;
				state = ST_FLOAT;
				break;
			}
			if(tolower(c) == 'x')
			{
				m_int = 0;
				state = ST_INT_HEX;
				break;
			}

			m_int = 0;
			unget();
			return LEX_INT;

		case ST_INT_OCT:		// 02
			if(c >= '0' && c <= '7')
			{
				m_int <<= 3;
				m_int += c - '0';
				break;
			}
			if(c >= '8' && c <= '9')
			{
				ERROR << getSource() << _(":") << getPos()
					<< _(" This number is not valid in \"string\" OCT escape sequence context: '")
					<< (char)c << "' (ascii " << c << ")" << endl;
				return LEX_ERROR;
			}

			unget();
			return LEX_INT;

		case ST_INT_HEX:		// 0xffe
			if(isdigit(c))
			{
				m_int <<= 4;
				m_int += c - '0';
				break;
			}
			c = tolower(c);
			if(c >= 'a' && c <= 'f')
			{
				m_int <<= 4;
				m_int += 10 + c - 'a';
				break;
			}

			unget();
			return LEX_INT;

		case ST_FLOAT:			// 0.6
			if(isdigit(c))
			{
				m_float += (c - '0') * float_dms;
				float_dms /= 10.0f;
				break;
			}
			if(tolower(c) == 'e')
			{
				state = ST_EXP_SIGN;
				break;
			}

			unget();
			return LEX_FLOAT;

		case ST_EXP_SIGN:		// 15e-
			if(isdigit(c))
			{
				exp = c - '0';
				state = ST_EXP;
				break;
			}
			if(c == '-')
			{
				exp_sign = -1;
				state = ST_EXP;
				break;
			}
			if(c == '+')
			{
				exp_sign = 1;
				state = ST_EXP;
				break;
			}
			break;

		case ST_EXP:			// 15e4
			if(isdigit(c))
			{
				exp *= 10;
				exp += c - '0';
				break;
			}

			unget();
			m_float *= pow(10.0, exp * exp_sign);
			return LEX_FLOAT;

		case ST_OP_ASSIGN:		// =
			if(c == '=')
				return LEX_OP_EQUAL;

			unget();
			return LEX_OP_ASSIGN;

		case ST_OP_LESS:		// <
			if(c == '=')
				return LEX_OP_LESS_EQ;

			unget();
			return LEX_OP_LESS;

		case ST_OP_NOT:
			if(c == '=')
				return LEX_OP_NOT_EQ;

			unget();
			return LEX_OP_NOT;

		case ST_OP_GREATER:		// >
			if(c == '=')
				return LEX_OP_GREATER_EQ;

			unget();
			return LEX_OP_GREATER;

		case ST_OP_PLUS:		// +
			if(c == '=')
				return LEX_OP_PLUS_AS;
			if(c == '+')
				return LEX_OP_PLUS_PLUS;

			unget();
			return LEX_OP_PLUS;

		case ST_OP_MINUS:		// -
			if(c == '=')
				return LEX_OP_MINUS_AS;
			if(c == '-')
				return LEX_OP_MINUS_MINUS;

			unget();
			return LEX_OP_MINUS;

		case ST_OP_MULT:		// *
			if(c == '=')
				return LEX_OP_MULT_AS;

			unget();
			return LEX_OP_MULT;

		case ST_OP_DIV:			// /
			if(c == '=')
			{
				return LEX_OP_DIV_AS;
			}
			if(c == '/')
			{
				state = ST_CPP_COMMENT;
				break;
			}
			if(c == '*')
			{
				state = ST_C_COMMENT;
				break;
			}

			unget();
			return LEX_OP_DIV;

		case ST_OP_MOD:
			if(c == '=')
				return LEX_OP_MOD_AS;

			unget();
			return LEX_OP_MOD;

		case ST_DOT:
			if(isdigit(c))
			{
				m_float = (c - '0') * float_dms;
				float_dms /= 10.0f;
				state = ST_FLOAT;
				break;
			}

			unget();
			return LEX_DOT;

		case ST_OP_AND:
			if(c == '&')
				return LEX_OP_AND;

			unget();
			ERROR << getSource() << _(":") << getPos()
				<< _(" Unexpected character, this is not operator &&: '")
				<< (char)c << "' (ascii " << c << ")" << endl;
			return LEX_ERROR;

		case ST_OP_OR:
			if(c == '|')
				return LEX_OP_OR;

			unget();
			ERROR << getSource() << _(":") << getPos()
				<< _(" Unexpected character, this is not operator ||: '")
				<< (char)c << "' (ascii " << c << ")" << endl;

			return LEX_ERROR;

		default:
			THROW(runtime_error(_(" Undefined state, this should never happen.")));
			break;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void Lexan::parseInclude(void)
{
	// include("filename");
	// include word already processed!

	if(nextToken() != LEX_LPA)
	{
		ERROR << getSource() << _(":") << getPos()
			<< _(" Left parenthesis '(' expected") << endl;
		THROW(runtime_error(_("Syntax of include statement: include(\"filename\");")));
	}

	if(nextToken() != LEX_STRING)
	{
		ERROR << getSource() << _(":") << getPos()
			<< _(" \"String\" constant expected") << endl;
		THROW(runtime_error(_("Syntax of include statement: include(\"filename\");")));
	}

	string filename(getString());

	if(nextToken() != LEX_RPA)
	{
		ERROR << getSource() << _(":") << getPos()
			<< _(" Right parenthesis ')' expected") << endl;
		THROW(runtime_error(_("Syntax of include statement: include(\"filename\");")));
	}

	if(nextToken() != LEX_SEMICOLON)
	{
		ERROR << getSource() << _(":") << getPos()
			<< _(" Semicolon ';' expected") << endl;
		THROW(runtime_error(_("Syntax of include statement: include(\"filename\");")));
	}

#ifdef DEBUG
	DBG << getSource() << _(":") << getPos() << _( " Including file: ") << filename << endl;
#endif // DEBUG

	m_source.push(new LexanIteratorFile(filename));
}

void Lexan::parseDefine(void)
{
	// define("name", "value");
	// define word already processed!

	if(nextToken() != LEX_LPA)
	{
		ERROR << getSource() << _(":") << getPos()
			<< _(" Left parenthesis '(' expected") << endl;
		THROW(runtime_error(_("Syntax of include statement: include(\"filename\");")));
	}

	if(nextToken() != LEX_STRING)
	{
		ERROR << getSource() << _(":") << getPos()
			<< _(" \"String\" constant expected") << endl;
		THROW(runtime_error(_("Syntax of include statement: include(\"filename\");")));
	}

	string name(getString());

	if(nextToken() != LEX_COMMA)
	{
		ERROR << getSource() << _(":") << getPos()
			<< _(" Comma ',' expected") << endl;
		THROW(runtime_error(_("Syntax of include statement: include(\"filename\");")));
	}

	if(nextToken() != LEX_STRING)
	{
		ERROR << getSource() << _(":") << getPos()
			<< _(" \"String\" constant expected") << endl;
		THROW(runtime_error(_("Syntax of include statement: include(\"filename\");")));
	}

	string value(getString());

	if(nextToken() != LEX_RPA)
	{
		ERROR << getSource() << _(":") << getPos()
			<< _(" Right parenthesis ')' expected") << endl;
		THROW(runtime_error(_("Syntax of include statement: include(\"filename\");")));
	}

	if(nextToken() != LEX_SEMICOLON)
	{
		ERROR << getSource() << _(":") << getPos()
			<< _(" Semicolon ';' expected") << endl;
		THROW(runtime_error(_("Syntax of include statement: include(\"filename\");")));
	}

#ifdef DEBUG
	DBG << getSource() << _(":") << getPos() << _( "Defining macro: ") << name << endl;
#endif // DEBUG

	// TODO: test this
	pair< map<string, string>::iterator, bool > ret;

	ret = m_defines.insert(pair<string,string>(name, value));
	if(ret.second == false)
	{
		WARN << getSource() << _(":") << getPos()
			<< _(" Redefining macro: ") << name << endl;
	}
}


/////////////////////////////////////////////////////////////////////////////
////

string Lexan::getTokenName(LEXTOKEN token)
{
	static string table[] =
	{
		"LEX_EOF",		// End of file
		"LEX_ERROR",		// Error

		"LEX_FUNCTION",		// function
		"LEX_RETURN",		// return
		"LEX_IF",			// if
		"LEX_ELSE",		// else
		"LEX_WHILE",		// while
		"LEX_FOR",		// for
		"LEX_FOREACH",		// foreach
		"LEX_BREAK",		// break
		"LEX_CONTINUE",		// continue
		"LEX_NULL",		// null
		"LEX_TRUE",		// true
		"LEX_FALSE",		// false

		"LEX_LVA",		// {		vinculum
		"LEX_RVA",		// }
		"LEX_LPA",		// (		parenthesis
		"LEX_RPA",		// )
		"LEX_LSA",		// [		square bracket
		"LEX_RSA",		// ]
		"LEX_COMMA",		// ,
		"LEX_SEMICOLON",		// ;
		"LEX_DOT",		// .

		"LEX_OP_ASSIGN",		// =
		"LEX_OP_EQUAL",		// ==
		"LEX_OP_NOT_EQ",		// !=
		"LEX_OP_LESS",		// <
		"LEX_OP_LESS_EQ",		// <=
		"LEX_OP_GREATER",		// >
		"LEX_OP_GREATER_EQ",	// >=
		"LEX_OP_PLUS",		// +
		"LEX_OP_PLUS_AS",		// +=
		"LEX_OP_PLUS_PLUS",	// ++
		"LEX_OP_MINUS",		// -
		"LEX_OP_MINUS_AS",	// -=
		"LEX_OP_MINUS_MINUS",	// --
		"LEX_OP_MULT",		// *
		"LEX_OP_MULT_AS",		// *=
		"LEX_OP_DIV",		// /
		"LEX_OP_DIV_AS",		// /=
		"LEX_OP_MOD",		// %
		"LEX_OP_MOD_AS",		// %=
		"LEX_OP_NOT",		// !
		"LEX_OP_AND",		// &&
		"LEX_OP_OR",		// ||

		"LEX_INT",		// 58		+ int
		"LEX_FLOAT",		// 0.58		+ float
		"LEX_STRING",		// "str",'str'	+ string
		"LEX_NAME"		// identifier	+ string
	};

	return table[token];
}
