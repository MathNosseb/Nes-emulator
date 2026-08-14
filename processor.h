#pragma once
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>

typedef struct	nes_processeur
{
	char			A; //accumulateur
	char			X; //registre d index
	char			Y; //registre d index
	char			SP; //stack pointer
	char			P; //flags
	uint16_t		PC; //program pointer
	unsigned char	ram[2048]; //Ram
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
int			execute_instruction(uint8_t instruction, nes_6502 *processor);

