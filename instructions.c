#include "processor.h"

int    execute_instruction(uint8_t instruction, nes_6502 *processor)
{
    switch (instruction)
    {
    case 0xD8:
        //https://www.nesdev.org/wiki/Instruction_reference#CLD
        processor->P &= 0b11110111; //reset bit D
        processor->PC++;
        break;
    case 0x78:
        //https://www.nesdev.org/wiki/Instruction_reference#SEI
        processor->P |= 0b00000100; //I passe a 1
        processor->PC++;
        break;
    default:
        printf("Instruction %X non reconnue\n", instruction);
        return (1);
    }
    printf("Instruction %X done\n", instruction);
    return (0);
}