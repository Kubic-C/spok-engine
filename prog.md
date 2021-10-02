## writing out types, file structure, etc.

this file is reminder for me

# NAMING:

all naming of functions, varibles, and files should be snake case.
all naming of preproccesser things(#define) should be screaming snake case

all struct types end in _s, e.g. struct foo_s;
all typedef types end in _tt, e.g. int foo_tt, typedef struct {} boo_tt;

# FUNCTION NAMING

if the functions is oriented around some type, then name as so:
```C
typedef struct {
  // some data
} foo_tt;

void foo_new(...);
void foo_do_something(...);
void foo_set_something(...); // only do if a peice of data requires more then one line to set
void foo_free(...): 
```

# FILE/FOLDER ORGANIZATION:
folders:
- physics: files relating to the physics engine
- graphics: files relating to GFX(rendering) engine
- core: definitions of spoks primary functions(spok_run, spok_run), and global
varibles

notice that in each folder there is a file called cmain.h(core), gmain.h(gfx),
pmain.h(physics), and you will also notice this happens with other files names (core/body.h, 
graphics/body.h, etc.) These files in each folder describes some part of a/an (abstract) concept,
this is a design pattern! 

preproccessor statements stay at top of the file
then typedefs, structs, enums follow
then functions

all enums and structues go in components.h

PUBLIC API FILES go in the ./src/spok/ folder 