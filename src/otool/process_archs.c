#include "../../includes/nm.h"

/*
** Gets the individual names of the ranlibs
** out of an archive
*/

    // TODO : 
    // get the archive's name
        // to get to the archive's name I need to get
        // past the first '\n
        // There I can find the name of the archive
char *get_object_name(char *archive_name)
{

    char *ret;
    char *object_name;

    ret = NULL;
    object_name = NULL;
    object_name = ft_strstr(archive_name, "\n");
    if (object_name[0] == '\n')
        ft_printf("Test successful");


    return (ret);

}



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
    char *object_name;

    arch = NULL;
    name = NULL;
    object_name = NULL;
    if (!offset || !ptr)
        fatal("Error in print_archs()");
    arch = (void *)ptr + offset;
    name = arch->ar_name;





    // offset the ptr

/////////////

    object_name = get_object_name(name);



///////

    // TODO : get the size of the special archive member
        // I am talking about the same size which I've
        // also already extracted in the go_archive
        // with the get_archive_size function


    // TODO : 
        // print the filename and the archive name


    // *ptr /////// ar_hdr arch //////////////////////////////
	// the archive can be found an offset after the initial pointer
	// then past the archive header plus the special size which can be found
	// with the get get after slash function is where the pointer located which 
	// we want to give back to the otool



    //ft_printf("\n-> %s <-\n", name); // TESTING0.

    
  
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