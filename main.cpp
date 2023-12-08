#include <iostream>
#include <vector>
#include <fstream>

void Decode8086(const std::vector<unsigned char> &binData) {
    for (int i = 0; i < binData.size(); ++i) {
        // extract each opcode and decode it
        // using a switch-statement to translate from bin opcode to corresponding
        // mnemonics.
        std::cout << "Byte" << i << ", " << "Opcode: " << std::hex << static_cast<int>(binData[i]) << std::endl;
    }
}

void decodeInstruction(uint8_t* opcode) {
    std::cout << "opcode :" << std::hex << opcode << std::endl;
    switch (*opcode) {
        case 0x00:
            std::cout << "NOP - No Operation" << std::endl;
            break;
        case 0x89:
            std::cout << "MOV AX, " << std::hex << static_cast<int>(opcode[1]) + (opcode[2] << 8) << std::endl;
            break;
            // Add more cases for different opcodes and instructions
        default:
            std::cout << "Unknown instruction" << std::endl;
    }
}

void ReadFile(std::basic_ifstream<char>& newFile){
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(newFile), {});

    size_t bufferSize = buffer.size();
    uint8_t* opcodeStream = buffer.data();

    for (size_t i = 0; i < bufferSize; ++i) {
        std::cout << "Decoding opcode " << i << ": ";
        decodeInstruction(&opcodeStream[i]);

        // Skip to the next instruction (size of instruction varies)
        // You might need to implement a proper disassembly algorithm
        // that accurately determines the size of each instruction
        // This is a very simplified example assuming instructions are fixed-size
        i += 2; // For example, increment by 2 bytes for MOV instruction
    }
}

int main(int argc, char *argv[]) {

    if (argc !=2) {
        std::cout << "usage: " << argv[0] << " <file_name>" << std::endl;
        return -1;
    }

    std::ifstream file(argv[1], std::ios::binary);

    if (file.is_open()) {
        std::vector<unsigned char> binData(std::istreambuf_iterator<char>(file), {});
        file.close();

        Decode8086(binData);
    } else {
        std::cout << "unable to open file" << std::endl;
    }
    return 0;
}