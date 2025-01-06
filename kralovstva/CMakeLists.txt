add_executable(kralovstva)

target_sources(kralovstva PRIVATE budova.c hrac.c kralovstvo.c main.c armada.c) 
target_compile_options(kralovstva PRIVATE  "-std=c11")
target_compile_options(kralovstva  PRIVATE "-Wall" "-Wextra" "-Wpedantic")
