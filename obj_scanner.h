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
		obj_scanner()
			: yyloc(nullptr)
			, yylval(nullptr)
		{ 
			yylineno = 1; 
		}

		obj_scanner(const std::string &filename)
			: _fs(new std::ifstream(filename))
			, yyFlexLexer(nullptr, nullptr)
			, _filename(filename)
		{
			yylineno = 1;
			yyin = _fs;
			//_fs.open(filename);
			if(_fs->fail()) std::cout << "unable to open file: " << filename << std::endl;
		}

		~obj_scanner() {}	
		int yylex(obj_parser::semantic_type *lval, obj_parser::location_type *loc)
		{
			yylval = lval;
			yyloc = loc;
			if(!yyloc->begin.filename) 
				yyloc->begin.filename = yyloc->end.filename = &_filename;
			return yylex();
		}

		void scan(const std::string &filename)
		{
			_filename = filename;
			_fs = new std::ifstream(filename);
			if(_fs->fail())
			{
				std::cout << "unable to open material library: " << filename << std::endl;
			}
			if(yyloc) yyloc->initialize(&_filename);
			yyrestart(_fs);
		}

		void scan(std::istream *is, std::string *fn = nullptr)
		{
			if(fn) _filename = *fn;
			yyrestart(is);
		}

		const std::string &filename() const
		{
			return _filename;
		}

	private:
		int yylex();
		std::string _filename;	
		std::ifstream *_fs;
		obj_parser::semantic_type *yylval;
		obj_parser::location_type *yyloc;
		std::vector<std::string *> _strings;
	};
}
