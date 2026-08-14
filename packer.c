#include <unistd.h>
#include <fcntl.h>

typedef struct	nes_processeur
{
	char			A; //accumulateur
	char			X; //registre d index
	char			Y; //registre d index
	char			SP; //stack pointer
	char			P; //flag
	short int		PC; //program pointer
	unsigned char	ram[2048]; //Ram
}	nes_6502;

int	main(int argc, char **argv)
{
	int	fd;
	//charger la rom et lire les instructions
	if (argc < 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	
	close(fd);
}
