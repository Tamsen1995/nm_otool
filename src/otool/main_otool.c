#include "../../includes/nm.h"

// TODO : Put this in the libft

/*
** man strchr
*/

char *ft_strchr(char *s, int c)
{
	char *ret;

	ret = NULL;
	if (!s)
		return (NULL);
	ret = s;
	while (*ret)
	{
		if (*ret == c)
			return (ret);
		ret++;
	}
	return (NULL);
}

/*
** looks for the size of the first special archive member
** this archive member holds file's name's size in the name itself
** the actual name is right after the struct
*/
int get_archive_size(char *name)
{
	int ret;
	char *size_in_arname;

	ret = 0;
	size_in_arname = ft_strchr(name, '/') + 1;
	ret = ft_atoi(size_in_arname);
	return (ret);
}

/*
** handles the archive case
*/

void go_archive(char *ptr)
{
	struct ar_hdr *arch;
	struct ranlib *ran;
	int after_slash_size;
	char *ranlib_size;
	int ran_size;

	ran = NULL; // TESTING
	arch = (void *)ptr + SARMAG;
	after_slash_size = get_archive_size(arch->ar_name);
	// in order to get to the first ranlib we need to find
	// whats after the magic number, the ar header, and the special archive member's size (which could be 0 in the case of its absence) + 4. 4 because the wordsize is 4 bytes long
	ran = (void *)ptr + SARMAG + sizeof(*arch) + 4;
	// the ranlibs's size will be right after the magic number, the ar header, and the special archive member's size
	ranlib_size = (void *)ptr + SARMAG + sizeof(*arch);

	// get the size of the ranlib

	// divide it by the size of a ranlib struct to get the number of ranlibs

	//


	exit(0); // TESTING
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
** checking for the magic number
** and redirecting the flow into the proper
** case
*/

void ft_otool(char *ptr)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		make_sec_list(ptr, TRUE);
	else if (magic_number == MH_MAGIC)
		make_sec_list(ptr, FALSE);
	else if (ft_strncmp(ptr, ARMAG, SARMAG) == 0)
		go_archive(ptr);
}

/*
** opens the file and scans it into memory
** then passes it on into the otool flow
*/

int main(int ac, char **av)
{
	int fd;
	char *ptr;
	struct stat buf;

	if (ac != 2)
		fatal("Please give me an argument !\n");
	if ((fd = open(av[1], O_RDONLY)) < 0)
		fatal("open");
	if (fd != -1 && (fstat(fd, &buf) == -1))
		fatal("fstat in the main");
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		fatal("mmap");
	ft_otool(ptr); // This is where we enter the main flow of the nm
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}