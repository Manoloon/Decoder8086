
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <bitset>
#include "Instructions8080.h"

void ReadFile(std::basic_ifstream<char>& newFile, std::ofstream& outFile);
void Disassemble(const uint8_t* opCode, std::ofstream& outFile);
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cout << "usage: " << argv[0] << " <file_name>" << std::endl;
        return -1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    std::ofstream outFile(argv[2]);

    std::cout << "Decoding instructions from file : "<< argv[1] << std::endl << "And results are output in file: " << argv[2] << std::endl;
    outFile << "bits 16" << std::endl << std::endl;

    if (file.is_open() && outFile.is_open()) {
        ReadFile(file, outFile);
        file.close();
        outFile.close();
    } else {
        std::cout << "unable to open file" << std::endl;
    }
    return 0;
}

void ReadFile(std::basic_ifstream<char>& newFile, std::ofstream& outFile)
{
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(newFile),{});

    size_t bufferSize = buffer.size();
    uint8_t* opCodeStream = buffer.data();

    for(size_t i = 0;i < bufferSize; ++i)
    {
        Disassemble(&opCodeStream[i],outFile);
        i++;
    }
}

void Disassemble(const uint8_t* opCode, std::ofstream& outFile)
{
    std::cout << "opcode : " << std::hex << static_cast<int>(*opCode) <<"x"<< std::hex << static_cast<int>(*(opCode+1)) << std::endl;
    std::cout << "opcode binary : " << std::bitset<8>{static_cast<unsigned>(*opCode) };
    std::cout << " : " << std::bitset<8>{static_cast<unsigned>(*(opCode+1)) } << std::endl;
    FInst8080 Instructions;

    switch (*(opCode+1))
    {
    default:
        std::cout << "unknown instruction : " << std::hex << static_cast<int>(*opCode) <<"x"<< std::hex << static_cast<int>(*(opCode+1)) << std::endl;
        outFile << "unknown instruction : " << std::hex << static_cast<int>(*opCode) <<"x"<< std::hex << static_cast<int>(*(opCode+1)) << std::endl;
        break;
    }
}