package hdRaiden


@(require)
import "core:fmt"
//import gl "vendor:OpenGL"
//import "vendor:glfw"


glClearColor : proc "c" (f32, f32, f32, f32)
@(export)
odin_glClearColor :: proc "c" (func_ptr: type_of(glClearColor)) {
	glClearColor = func_ptr
}

glClear : proc "c" (u32)
@(export)
odin_glClear :: proc "c" (func_ptr: type_of(glClear)) {
	glClear = func_ptr
}
