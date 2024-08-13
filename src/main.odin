package hdRaiden

//@(extra_linker_flags="python311.lib hboost_python311-mt-x64.lib tbb.lib libpxr_tf.lib libpxr_sdf.lib libpxr_hd.lib libpxr_hf.lib libpxr_arch.lib libpxr_gf.lib libpxr_cameraUtil.lib libpxr_vt.lib libpxr_usdRender.lib msvcrt.lib")

//foreign import cpp_module "../buildHoudini/cpp_module.lib"
//foreign cpp_module {
//	print_test_cpp :: proc () ---
//}

import "core:fmt"
import "base:runtime"

@export @(linkage="strong")
from_odin :: proc "c" () {
  context = runtime.default_context()
  runtime._startup_runtime()  // This should be in some sort of Odin Init function
  fmt.println("from_odin__$@")

//  print_test_cpp()
}


odin_cleanup :: proc "c" () {
  context = runtime.default_context()
  runtime._cleanup_runtime()
}
