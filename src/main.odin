package hdRaiden

import "base:runtime"
import "core:c"
import "core:fmt"
import gl "vendor:OpenGL"


@(export)
odin_render :: proc "c" (buffer: [^]f16, width, height: c.int) {
	context = runtime.default_context()

	for y in 0 ..< height {
		for x in 0 ..< width {
			buffer[(y * width + x) * 4 + 0] = f16(x) / f16(width)
			buffer[(y * width + x) * 4 + 1] = f16(y) / f16(height)
			buffer[(y * width + x) * 4 + 2] = f16(0.5)
			buffer[(y * width + x) * 4 + 3] = f16(1)
		}
	}

}

@(export)
odin_clear :: proc "c" () {
	glClearColor(.5, .2, .1, 0.5)
	glClear(gl.COLOR_BUFFER_BIT)
}


@(export)
odin_init :: proc "c" () {
	context = runtime.default_context()
	runtime._startup_runtime()
	fmt.println("Odin Init")

}


@(export)
odin_cleanup :: proc "c" () {
	context = runtime.default_context()
	runtime._cleanup_runtime()
	fmt.println("Odin Cleanup")

	//opengl_cleanup()
}


/*
TODO
 - Try supporting drawTarget sprim, might be able to aviod copying pixels from GPU to CPU and back.
const TfTokenVector HdStRenderDelegate::SUPPORTED_SPRIM_TYPES = { HdPrimTypeTokens->drawTarget }

*/
