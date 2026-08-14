#include <stdint.h>

uint32_t	translate_adr(uint32_t adr)
{
	//prend l adresse cpu attendu par le cpu et la transforme
	//en adresse dans la rom, le code commence a 0X8000 -> 0X10 Dans la rom
    //0x8000 ram = 0x10 rom
	return ((adr - 0x8000) + 0x10);
}
