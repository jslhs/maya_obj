%require "2.4.1"
%skeleton "lalr1.cc"
%defines "obj_parser.h"
%define namespace "utility"
%define parser_class_name "obj_parser"
%parse-param { utility::obj_reader &reader }
%lex-param { utility::obj_reader &reader }
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
    obj::ivertex *iv;
    obj::material *mtl;
	obj::vec3 *color;
	obj::tex_map *tex;
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


%token NEWMTL
%token AMBIENT_COLOR
%token DIFFUSE_COLOR
%token SPECULAR_COLOR
%token ILLUM
%token NS
%token BUMP_MAP
%token BUMP
%token DISSOLVE
%token AMBIENT_MAP
%token DIFFUSE_MAP
%token SPECULAR_MAP
%token SPECULAR_N_MAP
%token MAP_OPACITY
%token ALPHA_MAP
%token DISP_MAP
%token DECAL_MAP
%token REFL_MAP
%token BLEND_U
%token BLEND_V
%token BOOST
%token MODIFY_MAP
%token ORIGIN
%token SCALE
%token TURBULENCE
%token TEX_RES
%token CLAMP
%token BUMP_MUL
%token IMF_CHANNEL
%token TYPE

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

%type <mtl> newmtl_line;
%type <color> ambient_line;
%type <color> diffuse_line;
%type <color> specular_line;
%type <fval> specular_n_line;
%type <fval> dissolve_line;
%type <ival> illum_line;
%type <tex> ambient_map_line;
%type <tex> diffuse_map_line;
%type <tex> specular_map_line;
%type <tex> specular_n_map_line;
%type <tex> bump_map_line;
%type <tex> dissolve_map_line;
%type <tex> disp_map_line;
%type <tex> decal_map_line;
%type <tex> refl_map_line;


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
    | MATERIAL_LIBRARY FILENAME { reader.parse_mtl(*$2); }
	| material_line
	| vertex_line { reader.add($1); }
	| normal_line { reader.add($1); }
	| texture_line { reader.add($1); }
	| face_line { reader.add($1); }
	| group_line { reader.add($1); }
    | smooth_group_line
	| object_line { reader.add($1); }
	| newmtl_line { reader.add($1); }	
	;

material_line:
	MATERIAL_NAME IDENTIFIER { reader.set_mtl_name(*$2); }
	;

vertex_line:
	VERTEX real real real real { $$ = new obj::vertex($2, $3, $4, $5); }
	| VERTEX real real real { $$ = new obj::vertex($2, $3, $4); }
	;

normal_line:
	NORMAL real real real { $$ = new obj::normal($2, $3, $4); }
	;

texture_line:
	TEXTURE real real real { $$ = new obj::texture($2, $3, $4); }
	| TEXTURE real real { $$ = new obj::texture($2, $3); }
	| TEXTURE real { $$ = new obj::texture($2); }
	;

group_line:
	GROUP_NAME IDENTIFIER { $$ = new obj::object(*$2); }
    ;

smooth_group_line:
	SMOOTHING_GROUP IDENTIFIER { /*std::cout << "smoothing group: " << $2 << std::endl;*/ }
	| SMOOTHING_GROUP INTEGER { /*std::cout << "smoothing group: " << $2 << std::endl;*/ }
	;

vertex_group:
	INTEGER SLASH INTEGER SLASH INTEGER { $$ = new obj::ivertex($1, $3, $5); }
	| INTEGER SLASH SLASH INTEGER { $$ = new obj::ivertex($1, $4); }
	;

face_line:
	FACE vertex_group vertex_group vertex_group vertex_group { $$ = new obj::face($2, $3, $4, $5); }
	| FACE vertex_group vertex_group vertex_group { $$ = new obj::face($2, $3, $4); }
	;
object_line:
	OBJECT_NAME IDENTIFIER { $$ = new obj::object(*$2); }
	;

real:
	INTEGER { $$ = $1; }
	| FLOAT { $$ = $1; }
	;

newmtl_line:
	NEWMTL IDENTIFIER { $$ = new obj::material(*$2); }
	;

ambient_line:
	AMBIENT_COLOR real real real { $$ = new obj::vec3($2, $3, $4); }
	;
diffuse_line:
	DIFFUSE_COLOR real real real { $$ = new obj::vec3($2, $3, $4); }
	;
specular_line:
	SPECULAR_COLOR real real real { $$ = new obj::vec3($2, $3, $4); }
	;
dissolve_line:
	DISSOLVE real { $$ = $2; }
	;
specular_n_line:
	NS real { $$ = $2; }
	;
ambient_map_line:
	AMBIENT_MAP FILENAME { $$ = new obj::tex_map(); }
	;
diffuse_map_line:
	DIFFUSE_MAP FILENAME { $$ = new obj::tex_map(); }
	;
specular_map_line:
	SPECULAR_MAP FILENAME { $$ = new obj::tex_map(); }
	;
specular_n_map_line:
	SPECULAR_N_MAP FILENAME { $$ = new obj::tex_map(); }
	;
bump_map_line:
	BUMP_MAP FILENAME { $$ = new obj::tex_map(); }
	;
dissolve_map_line:
	DISSOLVE_MAP FILENAME { $$ = new obj::tex_map(); }
	;
refl_map_line:
	REFL_MAP FILENAME { $$ = new obj::tex_map(); } 
%%


void utility::obj_parser::error(const utility::obj_parser::location_type &loc, const std::string &msg)
{
	reader.error(loc, msg);
}

static int yylex(utility::obj_parser::semantic_type *yylval, utility::obj_parser::location_type *yyloc, utility::obj_reader &reader)
{
	return reader.scanner().yylex(yylval, yyloc);
}

