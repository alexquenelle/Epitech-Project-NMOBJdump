/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.quenelle
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <elf.h>
#include "flag.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* OBJDUMP X_64 */

int get_flags(Elf64_Ehdr *elf, Elf64_Shdr *shdr, bool print);
void display_sections(Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *strtab);
void display_archi_adrr_flags(Elf64_Ehdr *elf, Elf64_Shdr *shdr,
                                    char *file_path, void *buf);
void display_last_line(Elf64_Shdr *shdr, Elf64_Ehdr *elf, int i,
                                            char *char_sections);
int objdump (char **file_path, int argc);
void display_adrr(Elf64_Shdr *shdr, Elf64_Ehdr *elf);
int get_space(void *buf, char *file_path);
int display_line(int i, Elf64_Shdr *shdr, int i_char, char *char_sections);

/* OBJDUMP X_32 */

void launch_32(void *buf, char *file_path);

#endif /* !OBJDUMP_H_ */