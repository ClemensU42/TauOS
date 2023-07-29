
target_sources(${BIN_NAME} PRIVATE
    idt.c
    idt.h
    stub_table.asm
)

add_subdirectory(exceptions)