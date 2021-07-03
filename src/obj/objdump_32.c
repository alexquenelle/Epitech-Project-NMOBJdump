/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.quenelle
** File description:
** objdump_32
*/

#include "objdump.h"

void launch_32(void *buf, char *file_path)
{
    Elf32_Ehdr *elf;
    Elf32_Shdr *shdr;
    char *strtab = NULL;

    printf("\n%s:     file format elf32-i386\n", file_path);
}