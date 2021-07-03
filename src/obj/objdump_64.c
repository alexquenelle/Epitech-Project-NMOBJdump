/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.quenelle
** File description:
** objdump_64
*/

#include "objdump.h"

int get_flags(Elf64_Ehdr *elf, Elf64_Shdr *shdr, bool print)
{
    char *delim = "";

    int flags = (elf->e_type == ET_EXEC ? (EXEC_P | D_PAGED) : BFD_NO_FLAGS)
        | (elf->e_type == ET_DYN ? (DYNAMIC | D_PAGED) : BFD_NO_FLAGS)
        | (elf->e_type == ET_REL ? HAS_RELOC : BFD_NO_FLAGS);

    for (int i = 0; i < elf->e_shnum; i++) {
        if (shdr[i].sh_type == SHT_SYMTAB)
            flags = flags | HAS_SYMS;
    }
    if (print == false)
        return (flags);

    (flags & HAS_RELOC) ? printf("%sHAS_RELOC", delim) && (delim = ", ") : 0;
    (flags & EXEC_P) ? printf("%sEXEC_P", delim) && (delim = ", ") : 0;
    (flags & HAS_SYMS) ? printf("%sHAS_SYMS", delim) && (delim = ", ") : 0;
    (flags & DYNAMIC) ? printf("%sDYNAMIC", delim) && (delim = ", ") : 0;
    (flags & D_PAGED) ? printf("%sD_PAGED", delim) && (delim = ", ") : 0;
    printf("\n");

    return (flags);
}

void display_archi_adrr_flags(Elf64_Ehdr *elf, Elf64_Shdr *shdr,
                                    char *file_path, void *buf)
{
    char *strtab = NULL;
    shdr = buf + elf->e_shoff;
    strtab = buf + shdr[elf->e_shstrndx].sh_offset;
    int flags = get_flags(elf, shdr, false);

    printf("\n%s:     file format elf64-x86-64\n", file_path);
    if (elf->e_machine == EM_X86_64) {
        if (flags == 0){
            printf("architecture: i386:x86-64, flags 0x00000000:\n");
            get_flags(elf, shdr, true);
            printf("start adresse 0x0000000000000000\n\n");
        }
        else {
            printf("architecture: i386:x86-64, flags %010p:\n",flags);
            get_flags(elf, shdr, true);
            printf("start adresse %018p\n", elf->e_entry);
        }
        display_sections(elf, shdr, strtab);
    }
}

int get_space(void *buf, char *file_path)
{
    Elf64_Ehdr *elf = buf;
    Elf64_Shdr *shdr;
    
    if (buf != (void *)-1) {
        if (elf->e_ident[EI_CLASS] == ELFCLASS64)
            display_archi_adrr_flags(elf, shdr, file_path, buf);
        else if (elf->e_ident[EI_CLASS] == ELFCLASS32)
            launch_32(buf, file_path);
        else {
            fprintf(stderr, "\nObjdump: %s: file format not recognized",
                                                            file_path);
            return 84;
        }
    } else {
        fprintf(stderr, "\nObjdump: %s: file format not recognized",file_path);
        return 84;
    }
    return 0;
}

int objdump(char **file_path, int argc)
{
    void *buf;
    struct stat s;
    int fd = 0;
    int status = 0;

    for (int i = 1; i != argc; i++) {
        fd = open(file_path[i] ,O_RDONLY);
        if (fd != -1) {
            if (i > 1)
                printf("\n");
            fstat(fd, &s);
            buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
            status = get_space(buf, file_path[i]);
            close(fd);
        } else {
            fprintf(stderr, "objdump: '%s': No such file\n", file_path[i]);
            status = 84;
        }
    }
    return status;
}