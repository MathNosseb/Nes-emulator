#include <unistd.h>
#include <fcntl.h>

struct	nes_processeur
{
	char			A; //accumulateur
	char			X; //registre d index
	char			Y; //registre d index
	char			SP; //stack pointer
	char			P; //flag
	short int		PC; //program pointer
	unsigned char	ram[2048]; //Ram
}

int	main(int argc, char **argv)
{
	//charger la rom et lire les instructions
	(if (argc < 2))
		return (1);
}
