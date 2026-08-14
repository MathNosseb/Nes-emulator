#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>

uint32_t	translate_adr(uint32_t adr);

typedef struct	nes_processeur
{
	char			A; //accumulateur
	char			X; //registre d index
	char			Y; //registre d index
	char			SP; //stack pointer
	char			P; //flag
	uint16_t		PC; //program pointer
	unsigned char	ram[2048]; //Ram
}	nes_6502;

uint8_t	get_byte(char *filemame, unsigned int addr)
{
	int				fd;
	uint8_t			c;
	unsigned int	i;

	fd = open(filemame, O_RDONLY);
	if (fd == -1)
		return (fd);
	i = 0;
	while (read(fd, &c, 1) && i < addr)
		i++;
	close(fd);
	return (c);
}

int	main(int argc, char **argv)
{
	uint8_t		low;
	uint8_t		high;
	uint16_t	startPC;

	//charger la rom et lire les instructions
	if (argc < 2)
		return (1);
	low = (unsigned char)get_byte(argv[1], translate_adr(0xFFFC));
	high = (unsigned char)get_byte(argv[1], translate_adr(0xFFFD));
	startPC = low | (high << 8);
	printf("%X", startPC);
}
