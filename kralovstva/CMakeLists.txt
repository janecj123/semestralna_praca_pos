add_executable(subojKralovstiev)

target_sources(subojKralovstiev PRIVATE budova.c hrac.c kralovstvo.c main.c armada.c zdielane_data.c zdielane_nazvy.c zdielane_buffere.c shm.c hra.c server.c) 
target_compile_options(subojKralovstiev PRIVATE  "-std=c11")
target_compile_options(subojKralovstiev  PRIVATE "-Wall" "-Wextra" "-Wpedantic")
target_compile_definitions(subojKralovstiev PRIVATE _XOPEN_SOURCE=500)
