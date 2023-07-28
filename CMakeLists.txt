cmake_minimum_required(VERSION 3.16)

project(Tau LANGUAGES ASM CXX C)

set(ASM "")
set(LINKER_SCRIPT "${PROJECT_SOURCE_DIR}/linker.ld")


message(STATUS ${LINKER_SCRIPT})

set_source_files_properties(${ASM} PROPERTIES COMPILE_FLAGS "-m64")

set(BIN_NAME Tau_kernel)
set(IMAGE_NAME "${BIN_NAME}.img")
set(ISO_NAME Tau.iso)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-g -Wall -m64 -nostdlib -ffreestanding -fno-pie -fno-stack-check -mno-stack-arg-probe -fno-use-cxa-atexit -fno-builtin -fno-leading-underscore -fno-rtti -fno-exceptions -fno-stack-protector")
set(CMAKE_C_FLAGS "-g -Wall -m64 -nostdlib -ffreestanding -fno-pie -fno-stack-check -mno-stack-arg-probe -fno-builtin -fno-leading-underscore -fno-exceptions -fno-stack-protector")
set(CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT}")

add_executable(${BIN_NAME})
target_include_directories(${BIN_NAME} PUBLIC limine)

add_subdirectory(src)

# create kernel image
add_custom_command(TARGET ${BIN_NAME} POST_BUILD
    COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/iso_root/EFI/BOOT
    COMMAND cp -v ${CMAKE_BINARY_DIR}/${BIN_NAME} ${PROJECT_SOURCE_DIR}/limine.cfg ${PROJECT_SOURCE_DIR}/limine/limine-bios.sys ${PROJECT_SOURCE_DIR}/limine/limine-bios-cd.bin ${PROJECT_SOURCE_DIR}/limine/limine-uefi-cd.bin ${PROJECT_SOURCE_DIR}/iso_root/
    COMMAND cp -v ${PROJECT_SOURCE_DIR}/limine/BOOTX64.EFI ${PROJECT_SOURCE_DIR}/iso_root/EFI/BOOT
    COMMAND cp -v ${PROJECT_SOURCE_DIR}/limine/BOOTIA32.EFI ${PROJECT_SOURCE_DIR}/iso_root/EFI/BOOT
    COMMAND xorriso -as mkisofs -b limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label ${PROJECT_SOURCE_DIR}/iso_root -o ${ISO_NAME}
    COMMAND ${PROJECT_SOURCE_DIR}/limine/limine bios-install ${ISO_NAME}
    MAIN_DEPENDENCY ${BIN_NAME})