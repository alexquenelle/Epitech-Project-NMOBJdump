/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-nmobjdump-alexandre.quenelle
** File description:
** main
*/

#include "objdump.h"

int main(int argc, char** argv)
{
    char *file_path = NULL;
    char *default_args[] = {"objdump", "a.out"};

    if (argc == 1)
    {
        argv = default_args;
        argc++;
    }

    return (objdump(argv, argc));
}