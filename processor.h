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
	uint8_t	        ram[2048]; //Ram
    int8_t          *rom;
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
typedef struct nes_graphics
{
    //common registers
    uint8_t     ctrl; // $2000
    uint8_t     mask; //$2001
    uint8_t     status; //$2002
    uint8_t     OAMaddr; //$2003
}   nes_ppu;

uint8_t 	read_ram(uint16_t adr, nes_6502 *processor, nes_ppu *ppu);
void        write_ram(uint16_t adr, uint8_t val, nes_6502 *processor, nes_ppu *ppu);
int			execute_instruction(uint8_t instruction, nes_6502 *processor, nes_ppu *ppu);

