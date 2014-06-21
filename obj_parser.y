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
%token KA
%token KD
%token KS
%token ILLUM
%token NS
%token MAP_BUMP
%token BUMP
%token D
%token <tex> MAP_KA
%token <tex> MAP_KD
%token <tex> MAP_KS
%token <tex> MAP_NS
%token <tex> MAP_OPACITY
%token <tex> MAP_D
%token <tex> DISP
%token <tex> DECAL
%token <tex> REFL
%token BLENDU
%token BLENDV
%token BOOST
%token MM
%token O
%token SCALE
%token TURBULENCE
%token TEX_RES
%token CLAMP
%token BUMP_MUL
%token IMFCHAN
%token TYPE
%token ON
%token OFF

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
	obj_file_lines
	;

obj_file_lines:
	obj_file_lines obj_file_line
	| obj_file_line
	;

obj_file_line:
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
    
    /* mtl file lines */
    | newmtl_line { reader.add($1); }	
	| ambient_line
    | diffuse_line
    | specular_line
    | specular_n_line
    | dissolve_line
    | illum_line
    | ambient_map_line
    | diffuse_map_line
    | specular_map_line
    | specular_n_map_line
    | bump_map_line
    | dissolve_map_line
    | disp_map_line
    | decal_map_line
    | refl_map_line
    ;

material_line:
	MATERIAL_NAME IDENTIFIER { reader.set_mtl_name($2); }
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
	GROUP_NAME IDENTIFIER { $$ = new obj::object($2); }
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
	OBJECT_NAME IDENTIFIER { $$ = new obj::object($2); }
	;

real:
	INTEGER { $$ = $1; }
	| FLOAT { $$ = $1; }
	;

newmtl_line:
	NEWMTL IDENTIFIER { $$ = new obj::material($2); }
	;
ambient_line:
	KA real real real { $$ = new obj::vec3($2, $3, $4); }
	;
diffuse_line:
	KD real real real { $$ = new obj::vec3($2, $3, $4); }
	;
specular_line:
	KS real real real { $$ = new obj::vec3($2, $3, $4); }
	;
dissolve_line:
	D real { $$ = $2; }
	;
specular_n_line:
	NS real { $$ = $2; }
	;
illum_line:
    ILLUM INTEGER { $$ = $2; }
    ;
ambient_map_line:
    MAP_KA
	| MAP_KA FILENAME { $$ = new obj::tex_map($2); }
	;
diffuse_map_line:
    MAP_KD
	| MAP_KD FILENAME { $$ = new obj::tex_map($2); }
	;
specular_map_line:
	MAP_KS
    | MAP_KS FILENAME { $$ = new obj::tex_map($2); }
	;
specular_n_map_line:
	MAP_NS FILENAME { $$ = new obj::tex_map($2); }
	;
bump_map_line:
    MAP_BUMP
	| BUMP
    | MAP_BUMP FILENAME { $$ = new obj::tex_map($2); }
    | BUMP FILENAME { $$ = new obj::tex_map($2); }
	;
dissolve_map_line:
	MAP_D
    | MAP_OPACITY
    | MAP_D FILENAME { $$ = new obj::tex_map($2); }
	| MAP_OPACITY FILENAME { $$ = new obj::tex_map($2); }
    ;
decal_map_line:
    DECAL
    | DECAL FILENAME { $$ = new obj::tex_map($2); }
    ;
disp_map_line:
    DISP
    | DISP FILENAME { $$ = new obj::tex_map($2); }
    ;
refl_map_line:
	REFL
    | REFL FILENAME { $$ = new obj::tex_map($2); } 
%%


void utility::obj_parser::error(const utility::obj_parser::location_type &loc, const std::string &msg)
{
	reader.error(loc, msg);
}

static int yylex(utility::obj_parser::semantic_type *yylval, utility::obj_parser::location_type *yyloc, utility::obj_reader &reader)
{
	return reader.scanner().yylex(yylval, yyloc);
}

