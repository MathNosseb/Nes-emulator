#pragma once
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>

typedef struct	nes_processeur
{
	uint8_t			A; //accumulateur
	uint8_t			X; //registre d index
	uint8_t			Y; //registre d index
	uint8_t			SP; //stack pointer
	uint8_t			P; //flags
	uint16_t		PC; //program pointer
	uint8_t	ram[2048]; //Ram
}	nes_6502;

/*
P = NV-BDIZC
    ││ │││││
    ││ ││││└─ C Carry
    ││ │││└── Z Zero
    ││ ││└─── I Interrupt Disable
    ││ │└──── D Decimal
    ││ └───── B Break
    │└─────── V Overflow
    └──────── N Negative
*/

uint32_t	translate_adr(uint32_t adr);
uint8_t     get_byte(char *filemame, unsigned int addr);
int			execute_instruction(uint8_t instruction, nes_6502 *processor, char *filename);

