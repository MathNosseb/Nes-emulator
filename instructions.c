#include "processor.h"

void    recalculate_zero(uint8_t value, nes_6502 *processor)
{
    if (value == 0)
        processor->P |= 0b0000010;
    else
        processor->P &= 0b1111101;
}

void    recalculate_negativ(uint8_t value, nes_6502 *processor)
{
    //si le 7eme bit est a 1
    //0b10000000 -> ca
    if ((value & 0b10000000) == 0b10000000)
        processor->P |= 0b10000000;
    else
        processor->P &= 0b01111111;
}

int    execute_instruction(uint8_t instruction, nes_6502 *processor, char *filename)
{
    uint8_t low = get_byte(filename, translate_adr(processor->PC + 1));
    uint8_t high = get_byte(filename, translate_adr(processor->PC + 2));
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
    case 0xA2:
        //https://www.nesdev.org/wiki/Instruction_reference#LDX
        
        processor->X = low;
        recalculate_zero(processor->X, processor);
        recalculate_negativ(processor->X, processor);
        processor->PC+=2;
        break;
    case 0x8E:
        //https://www.nesdev.org/wiki/Instruction_reference#STX
        processor->ram[low | (high << 8)] = processor->X;
        processor->PC += 3;
        break;
    case 0xAD:
        //https://www.nesdev.org/wiki/Instruction_reference#LDA
        processor->A = processor->ram[low | (high << 8)];
        recalculate_zero(processor->A, processor);
        recalculate_negativ(processor->A, processor);
        processor->PC += 3;
        break;
    case 0x10:
        //https://www.nesdev.org/wiki/Instruction_reference#BPL
        if ((processor->P & 0b10000000) == 0b00000000)
        {
            //si N est a 0
            processor->PC += 2 + (int8_t)low;
            printf("jump to %d\n", (int8_t)low);
        }
        else
        {
            processor->PC += 2;
        }
        break;
    case 0xCA:
        //https://www.nesdev.org/wiki/Instruction_reference#DEX
        processor->X--;
        recalculate_zero(processor->X, processor);
        recalculate_negativ(processor->X, processor);
        processor->PC++;
        break;
    case 0x9A:
        //https://www.nesdev.org/wiki/Instruction_reference#TXS
        processor->SP = processor->X;
        processor->PC++;
        break;
    default:
        printf("Instruction %X non reconnue\n", instruction);
        return (1);
    }
    printf("Instruction %X done\n", instruction);
    return (0);
}