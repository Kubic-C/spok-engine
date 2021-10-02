add_library(spok-engine STATIC "dummy.c" "components.c")

target_link_libraries(spok-engine PUBLIC glfw glad cglm flecs)

target_sources(spok-engine PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/public/spok/_include.h" "${CMAKE_CURRENT_SOURCE_DIR}/public/spok/spok.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/public/spok/gfx.h"   "${CMAKE_CURRENT_SOURCE_DIR}/public/spok/components.h")

target_sources(spok-engine PRIVATE
  "utility/utils.h"
  "utility/file.h" "utility/file.c")
  
target_sources(spok-engine PRIVATE 
  "core/body.h" "core/body.c"
  "core/state.h" "core/state.c" 
  "core/cmain.h" "core/cmain.c"
  "core/spok.c" "core/_include.c")
    
target_sources(spok-engine PRIVATE
  "physics/physics.c"
  "physics/body.h" "physics/body.c"
  "physics/components.h" "physics/components.c" 
  "physics/pmain.h" "physics/pmain.c"
  "physics/body.h" "physics/body.c")
    
target_sources(spok-engine PRIVATE
  "graphics/gfx.c"
  "graphics/body.h" "graphics/body.c"
  "graphics/shader.h" "graphics/shader.c"
  "graphics/render.h" "graphics/render.c"
  "graphics/gmain.h" "graphics/gmain.c")
 
target_include_directories(spok-engine PUBLIC "public")
target_include_directories(spok-engine PRIVATE "./")