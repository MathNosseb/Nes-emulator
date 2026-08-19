#include "processor.h"

int	main(int argc, char **argv)
{
	uint8_t		low;
	uint8_t		high;
	nes_6502	nes;
	nes_ppu		ppu;
	int			status;
	uint8_t		current;

	//charger la rom et lire les instructions
	if (argc < 2)
		return (1);
	ppu.status = 0b10000000;//vblank
	nes.rom = argv[1];
	low = read_ram(0xFFFC, &nes, &ppu);
	high = read_ram(0xFFFD, &nes, &ppu);
	nes.PC  = low | (high << 8);
	status = 0;
	while (!status)
	{
		current = read_ram(nes.PC, &nes, &ppu);
		status = execute_instruction(current, &nes, &ppu);
	}
}
