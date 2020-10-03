#ifndef __SETUPS_H_
#define __SETUPS_H_

#include "includes.h"

static void __setup_hashmaps(void) {
    typedef_names = new_hashmap();
    enum_constants = new_hashmap();
    object_names = new_hashmap();
}

static void __setup_initial_object(void) {
    string *obj = new_string("");
    string_add_str(obj, "#ifndef __OBJECT_H_\n");
    string_add_str(obj, "#define __OBJECT_H_\n\n");
    string_add_str(obj, "#include <assert.h>\n");
    string_add_str(obj, "#include <ctype.h>\n");
    string_add_str(obj, "#include <errno.h>\n");
    string_add_str(obj, "#include <float.h>\n");
    string_add_str(obj, "#include <limits.h>\n");
    string_add_str(obj, "#include <locale.h>\n");
    string_add_str(obj, "#include <math.h>\n");
    string_add_str(obj, "#include <setjmp.h>\n");
    string_add_str(obj, "#include <signal.h>\n");
    string_add_str(obj, "#include <stdarg.h>\n");
    string_add_str(obj, "#include <stddef.h>\n");
    string_add_str(obj, "#include <stdio.h>\n");
    string_add_str(obj, "#include <stdlib.h>\n");
    string_add_str(obj, "#include <string.h>\n");
    string_add_str(obj, "#include <time.h>\n");
    string_add_str(obj, "/** @param bool -> A 'big' enough size to hold both 1 and 0 **/\n");
    string_add_str(obj, "typedef unsigned char bool;\n");
    string_add_str(obj, "#define true 1\n");
    string_add_str(obj, "#define false 0\n\n");
    string_add_str(obj, "struct Object {\n");
    string_add_str(obj, "    struct Class *class;\n");
    string_add_str(obj, "};\n");
    string_add_str(obj, "struct Class {\n");
    string_add_str(obj, "    struct Object _;\n");
    string_add_str(obj, "    char *name;\n");
    string_add_str(obj, "    struct Class *super;\n");
    string_add_str(obj, "    size_t size;\n");
    string_add_str(obj, "    void *(*ctor)(void *self, va_list *app);\n");
    string_add_str(obj, "    void *(*dtor)(void *self);\n");
    string_add_str(obj, "    bool (*differ)(void *self, void *other);\n");
    string_add_str(obj, "    bool (*puto)(void *self, FILE *fd);\n");

    string_add_str(obj, "    void *(*class)(void *self);\n");
    string_add_str(obj, "    void *(*superclass)(void *self);\n");
    string_add_str(obj, "    char *(*to_string)(void *self);\n");
    string_add_str(obj, "};\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "void *Object;\n");
    string_add_str(obj, "void *Class;\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static void *classOf(void *_self) {\n");
    string_add_str(obj, "    struct Object *self = _self;\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(_self && self && self->class);\n");
    string_add_str(obj, "    return self->class;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static size_t sizeOf(void *_self) {\n");
    string_add_str(obj, "    struct Class *class = classOf(_self);\n");
    string_add_str(obj, "    return class->size;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static void *super(void *_self) {\n");
    string_add_str(obj, "    struct Class *self = _self;\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(_self && self && self->super);\n");
    string_add_str(obj, "    return self->super;\n");
    string_add_str(obj, "}\n");

    string_add_str(obj, "static bool is_a(void *_self, void *class) {\n");
    string_add_str(obj, "    return _self && classOf(_self) == class;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "static bool is_of(void *_self, void *class) {\n");
    string_add_str(obj, "    if(_self) {\n");
    string_add_str(obj, "        struct Class *myClass = classOf(_self);\n");
    string_add_str(obj, "        if(class != Object) {\n");
    string_add_str(obj, "            while(myClass != class)\n");
    string_add_str(obj, "                if(myClass != Object)\n");
    string_add_str(obj, "                    myClass = super(myClass);\n");
    string_add_str(obj, "                else\n");
    string_add_str(obj, "                    return false;\n");
    string_add_str(obj, "        }\n");
    string_add_str(obj, "        return true;\n");
    string_add_str(obj, "    }\n");
    string_add_str(obj, "    return false;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "static void *cast(void *_self, void *class) {\n");
    string_add_str(obj, "    assert(is_of(_self, class));\n");
    string_add_str(obj, "    return (void*)_self;\n");
    string_add_str(obj, "}\n");

    string_add_str(obj, "\n");
    string_add_str(obj, "void *zircon_ctor(void *_self, va_list *app) {\n");
    string_add_str(obj, "    void *result;\n");
    string_add_str(obj, "    struct Class *class = classOf(_self);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(class->ctor);\n");
    string_add_str(obj, "    result = class->ctor(_self, app);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "void *zircon_super_ctor(void *_class, void *_self, va_list *app) {\n");
    string_add_str(obj, "    void *result;\n");
    string_add_str(obj, "    struct Class *superclass = super(_class);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(_self && superclass->ctor);\n");
    string_add_str(obj, "    result = superclass->ctor(_self, app);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "void *zircon_dtor(void *_self) {\n");
    string_add_str(obj, "    void *result;\n");
    string_add_str(obj, "    struct Class *class = classOf(_self);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(class->dtor);\n");
    string_add_str(obj, "    result = class->dtor(_self);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "void *zircon_super_dtor(void *_class, void *_self) {\n");
    string_add_str(obj, "    void *result;\n");
    string_add_str(obj, "    struct Class *superclass = super(_class);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(_self && superclass->dtor);\n");
    string_add_str(obj, "    result = superclass->dtor(_self);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "bool zircon_differ(void *_self, void *other) {\n");
    string_add_str(obj, "    bool result;\n");
    string_add_str(obj, "    struct Class *class = classOf(_self);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(class->differ);\n");
    string_add_str(obj, "    result = class->differ(_self, other);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "bool zircon_super_differ(void *_class, void *_self, void *other) {\n");
    string_add_str(obj, "    bool result;\n");
    string_add_str(obj, "    struct Class *superclass = super(_class);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(_self && superclass->differ);\n");
    string_add_str(obj, "    result = superclass->differ(_self, other);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "bool zircon_puto(void *_self, FILE *fd) {\n");
    string_add_str(obj, "    bool result;\n");
    string_add_str(obj, "    struct Class *class = classOf(_self);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(class->puto);\n");
    string_add_str(obj, "    result = class->puto(_self, fd);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "bool zircon_super_puto(void *_class, void *_self, FILE *fd) {\n");
    string_add_str(obj, "    bool result;\n");
    string_add_str(obj, "    struct Class *superclass = super(_class);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(_self && superclass->puto);\n");
    string_add_str(obj, "    result = superclass->puto(_self, fd);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "void *zircon_class(void *_self) {\n");
    string_add_str(obj, "    void *result;\n");
    string_add_str(obj, "    struct Class *class = classOf(_self);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(class->class);\n");
    string_add_str(obj, "    result = class->class(_self);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "void *zircon_super_class(void *_class, void *_self) {\n");
    string_add_str(obj, "    void *result;\n");
    string_add_str(obj, "    struct Class *superclass = super(_class);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(_self && superclass->class);\n");
    string_add_str(obj, "    result = superclass->class(_self);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "void *zircon_superclass(void *_self) {\n");
    string_add_str(obj, "    void *result;\n");
    string_add_str(obj, "    struct Class *class = classOf(_self);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(class->superclass);\n");
    string_add_str(obj, "    result = class->superclass(_self);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "void *zircon_super_superclass(void *_class, void *_self) {\n");
    string_add_str(obj, "    void *result;\n");
    string_add_str(obj, "    struct Class *superclass = super(_class);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(_self && superclass->superclass);\n");
    string_add_str(obj, "    result = superclass->superclass(_self);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "char *zircon_to_string(void *_self) {\n");
    string_add_str(obj, "    char *result;\n");
    string_add_str(obj, "    struct Class *class = classOf(_self);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(class->to_string);\n");
    string_add_str(obj, "    result = class->to_string(_self);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "char *zircon_super_to_string(void *_class, void *_self) {\n");
    string_add_str(obj, "    char *result;\n");
    string_add_str(obj, "    struct Class *superclass = super(_class);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(_self && superclass->to_string);\n");
    string_add_str(obj, "    result = superclass->to_string(_self);\n");
    string_add_str(obj, "    return result;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static void *Object_ctor(void *_self, va_list *app) {\n");
    string_add_str(obj, "    return _self;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static void *Object_dtor(void *_self) {\n");
    string_add_str(obj, "    return _self;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static bool Object_differ(void *_self, void *other) {\n");
    string_add_str(obj, "    return _self != other;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static bool Object_puto(void *_self, FILE *fd) {\n");
    string_add_str(obj, "    struct Class *self = classOf(_self);\n");
    string_add_str(obj, "    return fprintf(fd, \"%s at %p\\n\", self->name, _self);\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static void *Object_class(void *_self) {\n");
    string_add_str(obj, "    struct Class *self = classOf(_self);\n");
    string_add_str(obj, "    return self;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static void *Object_superclass(void *_self) {\n");
    string_add_str(obj, "    struct Class *superclass = super(_self);\n");
    string_add_str(obj, "    return superclass;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static char *Object_to_string(void *_self) {\n");
    string_add_str(obj, "    struct Class *self = classOf(_self);\n");
    string_add_str(obj, "    char *buf = (char*)malloc(sizeof(char) * 1024);\n");
    string_add_str(obj, "    sprintf(buf, \"@%s\", self->name);\n");
    string_add_str(obj, "    return buf;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static void *Class_ctor(void *_self, va_list *app) {\n");
    string_add_str(obj, "    struct Class *self = _self;\n");
    string_add_str(obj, "    size_t offset = offsetof(struct Class, ctor);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    self->name = va_arg(*app, char*);\n");
    string_add_str(obj, "    self->super = va_arg(*app, struct Class*);\n");
    string_add_str(obj, "    self->size = va_arg(*app, size_t);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    assert(self->super);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    memcpy((char*)self + offset, (char*)self->super + offset, sizeOf(self->super) - offset);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    typedef void (*voidf) ();\n");
    string_add_str(obj, "    voidf selector;\n");
    string_add_str(obj, "#ifdef va_copy\n");
    string_add_str(obj, "    va_list ap;\n");
    string_add_str(obj, "    va_copy(ap, *app);\n");
    string_add_str(obj, "#else\n");
    string_add_str(obj, "    va_list ap = *app;\n");
    string_add_str(obj, "#endif\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    while((selector = va_arg(ap, voidf))) {\n");
    string_add_str(obj, "        voidf method = va_arg(ap, voidf);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "        if(selector == (voidf)zircon_ctor)\n");
    string_add_str(obj, "            *(voidf*)&self->ctor = method;\n");
    string_add_str(obj, "        else if(selector == (voidf)zircon_dtor)\n");
    string_add_str(obj, "            *(voidf*)&self->dtor = method;\n");
    string_add_str(obj, "        else if(selector == (voidf)zircon_differ)\n");
    string_add_str(obj, "            *(voidf*)&self->differ = method;\n");
    string_add_str(obj, "        else if(selector == (voidf)zircon_puto)\n");
    string_add_str(obj, "            *(voidf*)&self->puto = method;\n");
    string_add_str(obj, "        else if(selector == (voidf)zircon_class)\n");
    string_add_str(obj, "            *(voidf*)&self->class = method;\n");
    string_add_str(obj, "        else if(selector == (voidf)zircon_superclass)\n");
    string_add_str(obj, "            *(voidf*)&self->superclass = method;\n");
    string_add_str(obj, "        else if(selector == (voidf)zircon_to_string)\n");
    string_add_str(obj, "            *(voidf*)&self->to_string = method;\n");
    string_add_str(obj, "    }\n");
    string_add_str(obj, "#ifdef va_copy\n");
    string_add_str(obj, "    va_end(ap);\n");
    string_add_str(obj, "#endif\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    return self;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static void *Class_dtor(void *_self) {\n");
    string_add_str(obj, "    struct Class *self = _self;\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    fprintf(stderr, \"%s: cannot destroy class\\n\", self->name);\n");
    string_add_str(obj, "    return 0;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static void *zircon_new(void *_class, ...) {\n");
    string_add_str(obj, "    struct Class *class = _class;\n");
    string_add_str(obj, "    assert(class && class->size);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    struct Object *object;\n");
    string_add_str(obj, "    va_list ap;\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    object = (struct Object*)calloc(1, class->size);\n");
    string_add_str(obj, "    assert(object);\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "    object->class = class;\n");
    string_add_str(obj, "    va_start(ap, _class);\n");
    string_add_str(obj, "        object = zircon_ctor(object, &ap);\n");
    string_add_str(obj, "    va_end(ap);\n");
    string_add_str(obj, "    return object;\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static void zircon_defer(void *_self) {\n");
    string_add_str(obj, "    if(_self) free(zircon_dtor(_self));\n");
    string_add_str(obj, "}\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "static struct Class object [] = {\n");
    string_add_str(obj, "    {\n");
    string_add_str(obj, "        { object + 1 },\n");
    string_add_str(obj, "        \"Object\",\n");
    string_add_str(obj, "        object,\n");
    string_add_str(obj, "        sizeof(struct Object),\n");
    string_add_str(obj, "        Object_ctor,\n");
    string_add_str(obj, "        Object_dtor,\n");
    string_add_str(obj, "        Object_differ,\n");
    string_add_str(obj, "        Object_puto,\n");
    string_add_str(obj, "        Object_class,\n");
    string_add_str(obj, "        Object_superclass,\n");
    string_add_str(obj, "        Object_to_string\n");
    string_add_str(obj, "    },\n");
    string_add_str(obj, "    {\n");
    string_add_str(obj, "        { object + 1 },\n");
    string_add_str(obj, "        \"Class\",\n");
    string_add_str(obj, "        object,\n");
    string_add_str(obj, "        sizeof(struct Class),\n");
    string_add_str(obj, "        Class_ctor,\n");
    string_add_str(obj, "        Class_dtor,\n");
    string_add_str(obj, "        Object_differ,\n");
    string_add_str(obj, "        Object_puto,\n");
    string_add_str(obj, "        Object_class,\n");
    string_add_str(obj, "        Object_superclass,\n");
    string_add_str(obj, "        Object_to_string\n");
    string_add_str(obj, "    }\n");
    string_add_str(obj, "};\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "void *Object = object;\n");
    string_add_str(obj, "void *Class = object + 1;\n");
    string_add_str(obj, "\n");
    string_add_str(obj, "#endif\n");

    /*********************************/
    FILE *fp = fopen("Object.h", "w");
    fprintf(fp, "%s", string_get(obj));
    fclose(fp);
    /*********************************/
}

static void *write_init_calls(void *o) {
    /* If the node is `Object` we dont need to initialize it */
    if(string_equals(new_string(o), new_string("Object"))) return NULL;

    string_add_str(init_calls, "    __init_");
    string_add_str(init_calls, o);
    string_add_str(init_calls, "();\n");
}
static void __setup_init_objects(void) {
    string_add_str(init_calls, "void __setup_objects(void) {\n");
    hashmap_map(object_list_for_main, (lambda)write_init_calls, KEYS);
    string_add_str(init_calls, "}\n");
}

#endif