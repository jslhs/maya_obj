%require "2.4.1"
%skeleton "lalr1.cc"
%defines "obj_parser.h"
%define namespace "utility"
%define parser_class_name "obj_parser"
%param { utility::obj_reader &reader }
%locations

%code requires
{
    #include "obj_file.h"
	namespace utility
	{
		class obj_reader;
	}
}

%code
{
    #include "obj_reader.h"
	static int yylex(utility::obj_parser::semantic_type *yylval, utility::obj_parser::location_type *yyloc, utility::obj_reader &reader);
}

%union
{
    int ival;
    float fval;
    std::string *sval;
    obj::vertex *v;
    obj::texture *vt;
    obj::normal *vn;
    obj::face *f;
    obj::object *obj;
    obj::indexed_vertex *iv;
    obj::material *mtl;
}

%token <ival> INTEGER
%token <fval> FLOAT
%token <sval> STRING
%token <sval> FILENAME
%token <sval> IDENTIFIER

%token <v> VERTEX
%token <vt> TEXTURE
%token <vn> NORMAL
%token SPACE_VERTEX
%token DEGREE
%token CURVE_SURFACE_TYPE
%token BASIS_MATRIX
%token STEP_SIZE
%token POINT
%token LINE
%token <f> FACE
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

%type <v> vertex_line;
%type <vn> normal_line;
%type <vt> texture_line
%type <f> face_line
%type <iv> vertex_group;
%type <obj> group_line;
%type <obj> object_line;
%type <fval> real;
%type <mtl> material_line;

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
    | MATERIAL_LIBRARY FILENAME
	| material_line { reader.add($1); }
	| vertex_line { reader.add($1); }
	| normal_line { reader.add($1); }
	| texture_line { reader.add($1); }
	| face_line { reader.add($1); }
	| group_line { reader.add($1); }
    | smooth_group_line
	| object_line { reader.add($1); }
	;

material_line:
	MATERIAL_NAME IDENTIFIER { $$ = new obj::material(); $$->name = *($2); }
	;

vertex_line:
	VERTEX real real real real { $$ = new obj::vertex(); }
	| VERTEX real real real { $$ = new obj::vertex(); }
	;

normal_line:
	NORMAL real real real { $$ = new obj::normal(); }
	;

texture_line:
	TEXTURE real real real { $$ = new obj::texture(); }
	| TEXTURE real real { $$ = new obj::texture(); }
	| TEXTURE real { $$ = new obj::texture(); }
	;

group_line:
	GROUP_NAME IDENTIFIER { $$ = new obj::object(); $$->name = *($2); }
    ;

smooth_group_line:
	SMOOTHING_GROUP IDENTIFIER { /*std::cout << "smoothing group: " << $2 << std::endl;*/ }
	| SMOOTHING_GROUP INTEGER { /*std::cout << "smoothing group: " << $2 << std::endl;*/ }
	;

vertex_group:
	INTEGER SLASH INTEGER SLASH INTEGER { $$ = new obj::indexed_vertex(); }
	| INTEGER SLASH SLASH INTEGER { $$ = new obj::indexed_vertex(); }
	;

face_line:
	FACE vertex_group vertex_group vertex_group vertex_group { $$ = new obj::face(); }
	| FACE vertex_group vertex_group vertex_group { $$ = new obj::face(); }
	;
object_line:
	OBJECT_NAME IDENTIFIER { $$ = new obj::object(); $$->name = *($2); }
	;

real:
	INTEGER { $$ = $1; }
	| FLOAT { $$ = $1; }
	;

%%


void utility::obj_parser::error(const utility::obj_parser::location_type &loc, const std::string &msg)
{
	reader.error(loc, msg);
}

static int yylex(utility::obj_parser::semantic_type *yylval, utility::obj_parser::location_type *yyloc, utility::obj_reader &reader)
{
	return reader.scanner().yylex(yylval, yyloc);
}

