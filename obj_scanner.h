#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL int utility::obj_scanner::yylex()

#include <vector>
#include <string>
#include <fstream>
#include "obj_parser.h"

namespace utility
{
	class obj_scanner
		: public yyFlexLexer
	{
	public:
		obj_scanner() { yylineno = 1; }
		obj_scanner(const std::string &filename)
			: yyFlexLexer(&_fs, nullptr)
			, _filename(filename)
		{
			yylineno = 1;
			_fs.open(filename);
			if(_fs.fail()) std::cout << "unable to open file: " << filename << std::endl;
		}

		~obj_scanner() {}	
		int yylex(obj_parser::semantic_type *lval, obj_parser::location_type *loc)
		{
			yylval = lval;
			yyloc = loc;
			return yylex();
		}

		const std::string &filename() const
		{
			return _filename;
		}

	private:
		int yylex();
		std::string _filename;	
		std::ifstream _fs;
		obj_parser::semantic_type *yylval;
		obj_parser::location_type *yyloc;
		std::vector<std::string *> _strings;
	};
}
