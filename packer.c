#include "processor.h"

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
	nes_6502	nes;
	int			status;
	uint8_t		current;

	//charger la rom et lire les instructions
	if (argc < 2)
		return (1);
	low = (unsigned char)get_byte(argv[1], translate_adr(0xFFFC));
	high = (unsigned char)get_byte(argv[1], translate_adr(0xFFFD));
	nes.PC  = low | (high << 8);
	status = 0;
	while (!status)
	{
		current = get_byte(argv[1], translate_adr(nes.PC));
		status = execute_instruction(current, &nes);
	}
}
