##
## EPITECH PROJECT, 2021
## B-PSU-400-BDX-4-1-nmobjdump-alexandre.quenelle
## File description:
## Makefile
##

SRC_NM		=	src/nm/main.c			\

SRC_OBJ		=	src/obj/main.c			\
				src/obj/objdump_64.c	\
				src/obj/sections.c		\
				src/obj/objdump_32.c	\

BUILDDIR	=	obj_nm

OBJ_NM		=	$(SRC_NM:%.c=$(BUILDDIR)/%.o)

OBJ_OBJ		=	$(SRC_OBJ:%.c=$(BUILDDIR)/%.o)

NAME_NM		=	my_nm

NAME_OBJ	=	my_objdump

CC			=	gcc

LD			=	$(CC)

CFLAGS		=	-I./src/include

LDFLAGS		=

all:		$(NAME_NM) $(NAME_OBJ)

nm:			$(NAME_NM)

objdump:	$(NAME_OBJ)

$(NAME_NM):	$(OBJ_NM)
	$(LINK.o) $^ $(LDLIBS) $(OUTPUT_OPTION)

$(NAME_OBJ):	$(OBJ_OBJ)
	$(LINK.o) $^ $(LDLIBS) $(OUTPUT_OPTION)

clean:
	rm -rf $(BUILDDIR)
	rm -f *.gc*

fclean: clean
	rm -f $(NAME_NM)
	rm -f $(NAME_OBJ)

re:	fclean all

.SECONDEXPANSION:
$(BUILDDIR)/%.o : override CFLAGS += -MT $@ -MMD -MP -MF $(@:.o=.d)
$(BUILDDIR)/%.o : %.c | $$(@D)/.
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(BUILDDIR)/.:
	mkdir $@

$(BUILDDIR)%/.:
	mkdir -p $@

.PRECIOUS:	$(BUILDDIR)/. $(BUILDDIR)%/.

.PHONY: all re clean fclean

-include $(OBJ_NM:.o=.d) $(OBJ_OBJ:.o=.d)