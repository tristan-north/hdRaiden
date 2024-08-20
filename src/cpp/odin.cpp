#include "odin.h"

void gl_funcptr_setup() {
    odin_glClearColor(glClearColor);
    odin_glClear(glClear);
}