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