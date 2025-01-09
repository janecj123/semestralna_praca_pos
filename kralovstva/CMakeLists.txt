add_executable(kralovstva)

target_sources(kralovstva PRIVATE budova.c hrac.c kralovstvo.c main.c armada.c zdielane_data.c zdielane_nazvy.c zdielane_buffere.c shm.c hra.c) 
target_compile_options(kralovstva PRIVATE  "-std=c11")
target_compile_options(kralovstva  PRIVATE "-Wall" "-Wextra" "-Wpedantic")
target_compile_definitions(kralovstva PRIVATE _XOPEN_SOURCE=500)
