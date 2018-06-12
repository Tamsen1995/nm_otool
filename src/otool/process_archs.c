#include "../../includes/nm.h"

/*
** Gets the individual names of the ranlibs
** out of an archive
*/

char *get_object_name(char *archive_name)
{
    char *ret;
    char *object_name;

    ret = NULL;
    object_name = NULL;
    object_name = ft_strstr(archive_name, "\n");
    if (object_name[0] == '\n')
        ret = object_name + 1;
    return (ret);
}

char *make_object_name(char *filename, char *object_name)
{
    char *ret;

    ret = NULL;
    if (!filename || !object_name)
        return (filename);
    ret = ft_strnew(ft_strlen(filename) + ft_strlen(object_name) + 2);
    ret = ft_strcat(ret, filename);
    ret = ft_strcat(ret, "(");
    ret = ft_strcat(ret, object_name);
    ret = ft_strcat(ret, ")");
    return (ret);
}

/*
** offsets a pointer to
** the proper position to be outputted
** then just passes it back into the otool
** also prints out necessary information about the
** ranlib which is being treated
*/

void print_archs(uint32_t offset, char *ptr, char *filename)
{
    struct ar_hdr *arch;
    char *name;
    char *object_name;
    int after_slash_size;

    arch = NULL;
    name = NULL;
    object_name = NULL;
    if (!offset || !ptr)
        fatal("Error in print_archs()");
    arch = (void *)ptr + offset;
    name = arch->ar_name;
    object_name = get_object_name(name);
    after_slash_size = get_archive_size(arch->ar_name);
    filename = make_object_name(filename, object_name);
    ft_otool((void *)arch + sizeof(*arch) + after_slash_size, filename);
}

/*
** iterates through the list of offsets
** and passes the offset along with the file ptr
** onto print_archs
*/

void process_archs(char *ptr, t_ran_offset *list, char *filename)
{
    t_ran_offset *tmp;

    tmp = list;
    if (!ptr || !list)
        fatal("Error inside of process_archs()");
    while (tmp)
    {
        print_archs(tmp->offset, ptr, filename);
        tmp = tmp->next;
    }
}