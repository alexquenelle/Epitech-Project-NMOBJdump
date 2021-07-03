/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.quenelle
** File description:
** sections
*/

#include "objdump.h"

void display_sections(Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *strtab)
{
    for (int inc = 1; inc < elf->e_shnum; inc++) {
        printf("\nContents of section %s: ", &strtab[shdr[inc].sh_name]);
        display_adrr(&shdr[inc], elf);
    }
}

void display_last_line(Elf64_Shdr *shdr, Elf64_Ehdr *elf, int i,
                                            char *char_sections)
{
    short diff = (i % 16);

    if (shdr->sh_size % 16)
        for (short i = 0; i < ((16-diff)*2+(16-diff)/4) + 2; printf(" "), ++i);
    else {
        printf("  ");
        diff = !diff ? 16 : diff;
    }

    for (i -= diff; i < shdr->sh_size; i++) {
        if (isprint(char_sections[i]))
            printf("%c", char_sections[i]);
        else
            printf(".");
    }
}

void print_to_get_space(int i, char *char_sections)
{
    if (i % 4 == 0)
        printf(" ");
    printf("%02x", (unsigned char) char_sections[i]);
}

int display_line(int i, Elf64_Shdr *shdr, int i_char, char *char_sections)
{
    uint64_t test = shdr->sh_addr;

    for (i = 0; i != shdr->sh_size; i++) {
        if (i % 16 == 0) {
            printf("  ");
            if (i != 0){
                for (; i_char != shdr->sh_size;) {
                    if (isprint(char_sections[i_char]))
                        printf("%c", char_sections[i_char]);
                    else
                        printf(".");
                    i_char++;
                    if (i_char % 16 == 0 && i_char != 0)
                        break;
                }
            }
            printf("\n %04lx", test + i);
        }
        print_to_get_space(i, char_sections);
    }
    return i;
}

void display_adrr(Elf64_Shdr *shdr, Elf64_Ehdr *elf)
{
    int i = 0;
    int i_char = 0;
    char *char_sections = ((char *) elf) + shdr->sh_offset;

    i = display_line(i, shdr, i_char, char_sections);
    display_last_line(shdr, elf, i, char_sections);
}