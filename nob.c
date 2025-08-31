#include <string.h>

#define NOB_IMPLEMENTATION
#include "nob.h/nob.h"

#define ISO         "rori_i386.iso"

#define SRC_DIR     "./src"
#define BUILD_DIR   "./build"

const char* KERNEL_MODULE_ASM[] = {
    "boot",

    "arch/i386/asm/gdt_stub",
    "arch/i386/asm/exception_stub",
    "arch/i386/asm/timer_stub",
};

const char* KERNEL_DIRECTORY[] = {
    "arch",
    "arch/i386",
    "arch/i386/asm",
    "driver",
    "driver/fb",
};

const char* KERNEL_MODULE_C[] = {
    "kernel",

    "driver/fb/fb",

    "arch/i386/cpu",
    "arch/i386/io",
    "arch/i386/serial",
    "arch/i386/memory",
    "arch/i386/gdt",
    "arch/i386/idt",
    "arch/i386/exception",
    "arch/i386/timer",
    "arch/i386/interrupt",
};

int build_bootloader();

int main(int argc, char** argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    nob_mkdir_if_not_exists(BUILD_DIR);

    const char* program = nob_shift_args(&argc, &argv);
    const char* run = NULL;
    if (argc >= 1) {
        run = nob_shift_args(&argc, &argv);
    }

    // TODO: Refactor this
    Nob_File_Paths objs = {0};
    Nob_Procs procs = {0};
    Nob_Cmd cmd = {0};

    const char* elf = nob_temp_sprintf("%s/kernel.elf", BUILD_DIR);

    // Create directory
    for (size_t i = 0; i < NOB_ARRAY_LEN(KERNEL_DIRECTORY); i++) {
        const char* dir = nob_temp_sprintf("%s/%s", BUILD_DIR, KERNEL_DIRECTORY[i]);
        nob_mkdir_if_not_exists(dir);
    }

    // Build ASM code
    for (size_t i = 0; i < NOB_ARRAY_LEN(KERNEL_MODULE_ASM); i++) {
        cmd.count = 0;

        const char* src = nob_temp_sprintf("%s/%s.asm", SRC_DIR, KERNEL_MODULE_ASM[i]);
        const char* dst_obj = nob_temp_sprintf("%s/%s.o", BUILD_DIR, KERNEL_MODULE_ASM[i]);
        nob_da_append(&objs, dst_obj);
        if (nob_needs_rebuild(dst_obj, &src, 1)) {
            nob_cmd_append(&cmd, "fasm", src, dst_obj);
            if (!nob_cmd_run(&cmd, .async = &procs, .max_procs = 4)) return 1;
        }
    }

    // if (!nob_procs_wait(procs)) return 1;

    // Build C Code
    for (size_t i = 0; i < NOB_ARRAY_LEN(KERNEL_MODULE_C); i++) {
        cmd.count = 0;

        const char* src = nob_temp_sprintf("%s/%s.c", SRC_DIR, KERNEL_MODULE_C[i]);
        const char* dst_obj = nob_temp_sprintf("%s/%s.o", BUILD_DIR, KERNEL_MODULE_C[i]);
        nob_da_append(&objs, dst_obj);
        if (nob_needs_rebuild(dst_obj, &src, 1)) {
            nob_cmd_append(&cmd, 
                "gcc", 
                "-m32", 
                "-ffreestanding", 
                "-fno-stack-protector", 
                "-fno-pie", 
                "-fno-pic", 
                "-fno-builtin", 
                "-c", 
                src
            );
            nob_cmd_append(&cmd, "-Wextra", "-Wall");
            nob_cmd_append(&cmd, "-o", dst_obj);
            if (!nob_cmd_run(&cmd, .async = &procs, .max_procs = 4)) return 1;
        }
    }

    if (!nob_procs_wait(procs)) return 1;

    // Link it
    cmd.count = 0;
    if (nob_needs_rebuild(elf, objs.items, objs.count)) {
        nob_cmd_append(&cmd, "ld", "-m", "elf_i386", "-T", "linker.ld", "-o", elf);
        for (size_t i = 0; i < objs.count; i++) {
            const char* obj = objs.items[i];
            nob_cmd_append(&cmd, obj);
        }
        if (!nob_cmd_run(&cmd)) return 1;

        if (!nob_copy_file(elf, "./iso/boot/kernel.elf")) return 1;
    }

    // Make ISO
    const char* iso = nob_temp_sprintf("%s/%s", BUILD_DIR, ISO);
    if (nob_needs_rebuild(iso, &elf, 1)) {
        nob_copy_file(elf, elf);
        cmd.count = 0;
        nob_cmd_append(&cmd, "grub-mkrescue", "-o", iso, "iso");
        if (!nob_cmd_run(&cmd)) return 1;
    }

    if (run == NULL) return 0;

    cmd.count = 0;
    if (strcmp(run, "run") == 0) {
        nob_cmd_append(&cmd, "qemu-system-i386", "-m", "512M", "-cdrom", iso, "-serial", "stdio", "--no-reboot");
        if (!nob_cmd_run(&cmd)) return 1;
    }
    return 0;
}

