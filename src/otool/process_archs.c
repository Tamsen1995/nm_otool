#include "../../includes/nm.h"

/*
** offsets a pointer to
** the proper position to be outputted
** then just passes it back into the otool
** also prints out necessary information about the
** ranlib which is being treated
*/

void print_archs(uint32_t offset, char *ptr)
{
    struct ar_hdr *arch;
    char *name;

    arch = NULL;
    name = NULL;
    if (!offset || !ptr)
        fatal("Error in print_archs()");
    arch = (void *)ptr + offset;
    name = arch->ar_name;




    // offset the ptr

    // TODO : 
    // get the archive's name
        // to get to the archive's name I need to get
        // past the first '\n
        // There I can find the name of the archive
    



    ft_printf("\n%s\n", name); // TESTING

    // get the size of the special archive member
    // print the filename and the archive name
}

/*
** iterates through the list of offsets
** and passes the offset along with the file ptr
** onto print_archs
*/

void process_archs(char *ptr, t_ran_offset *list)
{
    t_ran_offset *tmp;

    tmp = list;
    if (!ptr || !list)
        fatal("Error inside of process_archs()");
    while (tmp)
    {
        print_archs(tmp->offset, ptr);
        tmp = tmp->next;
    }
}