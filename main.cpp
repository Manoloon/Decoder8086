#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>

void decodeInstruction(uint8_t *opcode, std::ofstream &outFile) {
    //std::cout << "opcode : " << std::hex << static_cast<int>(*opcode) << std::endl;
    switch (*opcode) {
        case 0x88:
            switch (*(opcode + 1)) {
                case 0xe5:
                    outFile << "mov ch, ah" << std::endl;
                    break;
                case 0xc8:
                    outFile << "mov al, cl" << std::endl;
                    break;
                case 0xed:
                    outFile << "mov ch, ch" << std::endl;
                    break;
            }
            break;
        case 0x89:
            switch (*(opcode + 1)) {
                case 0xd9:
                    outFile << "mov cx, bx" << std::endl;
                    break;
                case 0xda:
                    outFile << "mov dx, bx" << std::endl;
                    break;
                case 0xde:
                    outFile << "mov si, bx" << std::endl;
                    break;
                case 0xfb:
                    outFile << "mov bx, di" << std::endl;
                    break;
                case 0xc3:
                    outFile << "mov bx, ax" << std::endl;
                    break;
                case 0xf3:
                    outFile << "mov bx, si" << std::endl;
                    break;
                case 0xfc:
                    outFile << "mov sp, di" << std::endl;
                    break;
                case 0xc5:
                    outFile << "mov bp, ax" << std::endl;
                    break;
            }
            break;
        default:
            outFile << "Unknown instruction" << std::endl;
    }
}

void ReadFile(std::basic_ifstream<char> &newFile, std::ofstream &outFile) {
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(newFile), {});

    size_t bufferSize = buffer.size();
    uint8_t *opcodeStream = buffer.data();
    for (size_t i = 0; i < bufferSize; ++i) {
        decodeInstruction(&opcodeStream[i], outFile);

        // Skip to the next instruction (size of instruction varies)
        // You might need to implement a proper disassembly algorithm
        // that accurately determines the size of each instruction
        // This is a very simplified example assuming instructions are fixed-size
        i++; // For example, increment by 2 bytes for MOV instruction
    }
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " <file_name>" << std::endl;
        return -1;
    }
    std::ifstream file(argv[1], std::ios::binary);
    std::ofstream outFile(argv[2]);
    //std::ofstream outFile("Output.asm");
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