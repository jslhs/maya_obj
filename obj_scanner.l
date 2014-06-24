%{
#include "obj_scanner.h"

#include <iostream>
#include <string>
#include <vector>

%}

%option batch yylineno yyclass="obj_scanner" noyywrap c++ nounistd

white_space     [ \t]*
digit           [0-9]
alpha           [a-zA-Z_]
alpha_num       ({alpha}|{digit})
comment         "#".*\n
i               {digit}+
integer         -?{i}
exponent        [eE][+-]?{digit}+
identifier      {alpha_num}+
filename        [a-zA-Z\.\-_0-9\(\)\?]+
string          \"([^"\n]|\"\")+\"
bad_string      \"([^"\n]|\"\")+
ffloat           (-?{i}\.{i}?|{i}?\.{i}){exponent}?
ifloat          -?{i}{exponent}
float           ({ifloat}|{ffloat})
real			({i}|{float})
rpath           [a-z0-9]([a-z0-9-]*[a-z0-9])?(/[a-z0-9]([a-z0-9-]*[a-z0-9])?)*
path			[a-zA-Z\.\-_0-9\\~\:]+
%%

v               return(obj_parser::token::VERTEX);
vt              return(obj_parser::token::TEXTURE);
vn              return(obj_parser::token::NORMAL);
vp              return(obj_parser::token::SPACE_VERTEX);
cstype          return(obj_parser::token::CURVE_SURFACE_TYPE);
deg             return(obj_parser::token::DEGREE);
bmat            return(obj_parser::token::BASIS_MATRIX);
step            return(obj_parser::token::STEP_SIZE);
p               return(obj_parser::token::POINT);
l               return(obj_parser::token::LINE);
f               return(obj_parser::token::FACE);
curv            return(obj_parser::token::CURVE);
curv2           return(obj_parser::token::CURVE_2D);
surf            return(obj_parser::token::SURFACE);
parm            return(obj_parser::token::PARAMETER);
trim            return(obj_parser::token::OUTER_TRIMMING_LOOP);
hole            return(obj_parser::token::INNER_TRIMMING_LOOP);
scrv            return(obj_parser::token::SPECIAL_CURVE);
sp              return(obj_parser::token::SPECIAL_POINT);
end             return(obj_parser::token::END);
con             return(obj_parser::token::CONNECT);
g               return(obj_parser::token::GROUP_NAME);
s               return(obj_parser::token::SMOOTHING_GROUP);
mg              return(obj_parser::token::MERGING_GROUP);
o               return(obj_parser::token::OBJECT_NAME);
bevel           return(obj_parser::token::BEVEL_INTERPOLATION);
c_interp        return(obj_parser::token::COLOR_INTERPOLATION);
d_interp        return(obj_parser::token::DISSOLVE_INTERPOLATION);
lod             return(obj_parser::token::LOD);
usemtl          return(obj_parser::token::MATERIAL_NAME);
mtllib          return(obj_parser::token::MATERIAL_LIBRARY);
shadow_obj      return(obj_parser::token::SHADOW_CASTING);
trace_obj       return(obj_parser::token::RAY_TRACING);
ctech           return(obj_parser::token::CURVE_APPROX_TECH);
stech           return(obj_parser::token::SURFACE_APPROX_TECH);

newmtl			return(obj_parser::token::NEWMTL);
Ka              return(obj_parser::token::KA);
Kd              return(obj_parser::token::KD);
Ks              return(obj_parser::token::KS);
Ke				return(obj_parser::token::KE);
Km              return(obj_parser::token::KM);
Ns              return(obj_parser::token::NS);
illum           return(obj_parser::token::ILLUM);
d               return(obj_parser::token::D);
map_[kK][aA]    return(obj_parser::token::MAP_KA);
map_[kK][dD]    return(obj_parser::token::MAP_KD);
map_[kK][sS]    return(obj_parser::token::MAP_KS);
map_Ns          return(obj_parser::token::MAP_NS);
map_d           return(obj_parser::token::MAP_D);
map_bump        return(obj_parser::token::MAP_BUMP);
bump            return(obj_parser::token::BUMP);
map_opacity		return(obj_parser::token::MAP_OPACITY);
-type           return(obj_parser::token::TYPE);
on              return(obj_parser::token::ON);
off             return(obj_parser::token::OFF);
refl            return(obj_parser::token::REFL);
Tf				return(obj_parser::token::TF);
Tr				return(obj_parser::token::TR);
Ni				return(obj_parser::token::NI);


"/"             return(obj_parser::token::SLASH);
"\\\n"			{ yyloc->lines(); }	
\n              { yyloc->lines(); }
{white_space}   
{comment}       { yyloc->lines(); /*std::cout << yytext;*/ return(obj_parser::token::COMMENT); }
{integer}       { yylval->ival = atoi(yytext); return(obj_parser::token::INTEGER); }
{float}         { yylval->fval = atof(yytext); return(obj_parser::token::FLOAT); }
{string}        { yylval->sval = new std::string(yytext); _strings.push_back(yylval->sval); return(obj_parser::token::STRING); }
{identifier}    { yylval->sval = new std::string(yytext); _strings.push_back(yylval->sval); return(obj_parser::token::IDENTIFIER); }
{filename}      { yylval->sval = new std::string(yytext); _strings.push_back(yylval->sval); return(obj_parser::token::FILENAME); }
{path}			{ yylval->sval = new std::string(yytext); _strings.push_back(yylval->sval); return(obj_parser::token::PATH); }

 /* "\\"			return(BACK_SLASH); */

%%





