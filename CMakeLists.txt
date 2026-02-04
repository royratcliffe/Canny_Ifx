cmake_minimum_required(VERSION 3.10)
project(Canny_Ifx C)

add_library(Canny_Ifx)
target_include_directories(Canny_Ifx PUBLIC Inc)
target_sources(Canny_Ifx PRIVATE
    Src/Ifx_Cpu.c
    Src/Ifx_Can.c
    Src/core_event.c
    Src/event_group.c
    Src/compare_float.c
)
target_link_libraries(Canny_Ifx
    ConfigurationsAndLibraries
)
