#include "processor.h"

uint16_t	read_rom(uint16_t adr, nes_6502 *processor)
{
	//prend l adresse cpu attendu par le cpu et la transforme
	//en adresse dans la rom, le code commence a 0X8000 -> 0X10 Dans la rom
    //0x8000 ram = 0x10 rom
	int				fd;
	uint8_t			c;
	unsigned int	i;

	adr = (adr - 0x8000) + 0x10;
	fd = open(processor->rom, O_RDONLY);
	if (fd == -1)
		return (fd);
	i = 0;
	while (read(fd, &c, 1) && i < adr)
		i++;
	close(fd);
	return (c);
}

void	write_ram(uint16_t adr, uint8_t val, nes_6502 *processor, nes_ppu *ppu)
{
	if (adr >= 0x8000)
	{
		printf("\033[31mImpossible d'ecrire dans la rom\n");
		return ;
	}
	if (adr >= 0x0 && adr <= 0x1FFF)
	{
		processor->ram[adr & 0x07FF] = val;
		return ;
	}
	if (adr >= 0x2000 && adr <= 0x2007)
	{
		printf("\033[33mtentative ecriture PPU a l adresse 0x%X, ", adr);
		if (adr == 0x2000)
			ppu->ctrl = val;
		if (adr == 0x2001)
			ppu->mask = val;
		if (adr == 0x2002)
			ppu->status = val;
		if (adr == 0x2003)
			ppu->OAMaddr = val;
	}
}

uint8_t	read_ram(uint16_t adr, nes_6502 *processor, nes_ppu *ppu)
{
	if (adr >= 0x8000)
		return (read_rom(adr, processor));
	if (adr >= 0x0 && adr <= 0x1FFF)
	{
		return ((processor->ram[adr & 0x07FF]));
	}
	if (adr >= 0x2000 && adr <= 0x2007)
	{
		if (adr == 0x2000)
			return (ppu->ctrl);
		if (adr == 0x2001)
			return (ppu->mask);
		if (adr == 0x2002)
			return (ppu->status);
		if (adr == 0x2003)
			return (ppu->OAMaddr);
		printf("\033[33mtentative lecture PPU a l adresse non map 0x%X, ", adr);
		return (0); //pas de ppu
	}
	printf("\033[31mbad address %X return 0 value, ", adr);
	return (0);
}