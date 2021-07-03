/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.quenelle
** File description:
** main
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "objdump.h"

int get_space(void *buf, char *file_path)
{
    Elf64_Ehdr *elf = buf;
    Elf64_Shdr *shdr;
    
    if (buf == (void *)-1) {
        if (elf->e_ident[EI_CLASS] != ELFCLASS64 &&
            elf->e_ident[EI_CLASS] != ELFCLASS32) {
            fprintf(stderr, "m: %s: file format not recognized\n", file_path);
            return 84;
        }
    } else {
        fprintf(stderr, "m: %s: file format not recognized\n",file_path);
        return 84;
    }
    return 0;
}

int nm(char **file_path, int argc)
{
    void *buf;
    struct stat s;
    int fd = 0;
    int status = 0;

    for (int i = 1; i != argc; i++) {
        fd = open(file_path[i] ,O_RDONLY);
        if (fd != -1) {
            fstat(fd, &s);
            buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
            status = get_space(buf, file_path[i]);
            close(fd);
        } else {
            fprintf(stderr, "nm: '%s': No such file\n", file_path[i]);
            status = 84;
        }
    }
    return status;
}

int main(int argc, char** argv)
{
    char *file_path = NULL;
    char *default_args[] = {"nm", "a.out"};

    if (argc == 1)
    {
        argv = default_args;
        argc++;
    }

    return (nm(argv, argc));
}