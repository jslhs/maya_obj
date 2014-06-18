%require "2.4.1"
%skeleton "lalr1.cc"
%defines "obj_parser.h"
%define namespace "utility"
%define parser_class_name "obj_parser"
%param { utility::obj_reader &reader }
%locations

%code requires
{
	namespace utility
	{
		class obj_reader;
	}
}

%code
{
	static int yylex(utility::obj_parser::semantic_type *yylval, utility::obj_parser::location_type *yyloc, utility::obj_reader &reader);
}

%union
{
    int ival;
    float fval;
    std::string *sval;
}

%token <ival> INTEGER
%token <rval> FLOAT
%token <sval> STRING
%token <sval> FILENAME
%token <sval> IDENTIFIER

%token VERTEX
%token TEXTURE
%token NORMAL
%token SPACE_VERTEX
%token DEGREE
%token CURVE_SURFACE_TYPE
%token BASIS_MATRIX
%token STEP_SIZE
%token POINT
%token LINE
%token FACE
%token CURVE
%token CURVE_2D
%token SURFACE
%token PARAMETER
%token OUTER_TRIMMING_LOOP
%token INNER_TRIMMING_LOOP
%token SPECIAL_CURVE
%token SPECIAL_POINT
%token END
%token CONNECT
%token GROUP_NAME
%token SMOOTHING_GROUP
%token MERGING_GROUP
%token OBJECT_NAME
%token BEVEL_INTERPOLATION
%token COLOR_INTERPOLATION
%token DISSOLVE_INTERPOLATION
%token LOD
%token MATERIAL_NAME
%token MATERIAL_LIBRARY
%token SHADOW_CASTING
%token RAY_TRACING
%token CURVE_APPROX_TECH
%token SURFACE_APPROX_TECH
%token COMMENT
%left SLASH
%left BACK_SLASH



%%

obj_file:
	lines
	;

lines:
	lines line
	| line
	;

line:
	COMMENT
	| material_line
	| vertex_line
	| normal_line
	| texture_line
	| face_line
	| group_line
	| object_line
	;

material_line:
	MATERIAL_LIBRARY FILENAME
	| MATERIAL_NAME IDENTIFIER
	;

vertex_line:
	VERTEX real real real real
	| VERTEX real real real
	;

normal_line:
	NORMAL real real real
	;

texture_line:
	TEXTURE real real real
	| TEXTURE real real
	| TEXTURE real
	;

group_line:
	GROUP_NAME IDENTIFIER { /*std::cout << "group: " << $2 << std::endl;*/ }
	| SMOOTHING_GROUP IDENTIFIER { /*std::cout << "smoothing group: " << $2 << std::endl;*/ }
	| SMOOTHING_GROUP INTEGER { /*std::cout << "smoothing group: " << $2 << std::endl;*/ }
	;

vertex_group:
	INTEGER SLASH INTEGER SLASH INTEGER
	| INTEGER SLASH SLASH INTEGER
	;

face_line:
	FACE vertex_group vertex_group vertex_group vertex_group
	| FACE vertex_group vertex_group vertex_group
	;
object_line:
	OBJECT_NAME IDENTIFIER
	;

real:
	INTEGER 
	| FLOAT
	;

%%

#include "obj_reader.h"

void utility::obj_parser::error(const utility::obj_parser::location_type &loc, const std::string &msg)
{
	reader.error(loc, msg);
}

static int yylex(utility::obj_parser::semantic_type *yylval, utility::obj_parser::location_type *yyloc, utility::obj_reader &reader)
{
	return reader.yylex(yylval, yyloc);
}

