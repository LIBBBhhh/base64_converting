
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>


std::string EncodeFileToBase64(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return "";
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    std::string content = oss.str();

    std::string encoded;
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    size_t in_len = content.size();
    size_t i = 0;

    while (in_len - i >= 3) {
        unsigned char char1 = content[i++];
        unsigned char char2 = content[i++];
        unsigned char char3 = content[i++];

        encoded += base64_chars[char1 >> 2];
        encoded += base64_chars[((char1 & 3) << 4) + (char2 >> 4)];
        encoded += base64_chars[((char2 & 15) << 2) + (char3 >> 6)];
        encoded += base64_chars[char3 & 63];
    }

    if (in_len - i == 2) {
        unsigned char char1 = content[i++];
        unsigned char char2 = content[i++];
        encoded += base64_chars[char1 >> 2];
        encoded += base64_chars[((char1 & 3) << 4) + (char2 >> 4)];
        encoded += base64_chars[(char2 & 15) << 2];
        encoded += "=";
    }
    else if (in_len - i == 1) {
        unsigned char char1 = content[i++];
        encoded += base64_chars[char1 >> 2];
        encoded += base64_chars[(char1 & 3) << 4];
        encoded += "==";
    }

    return encoded;
}

int main() {
    
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    std::string base64Data = EncodeFileToBase64(filename);

    if (!base64Data.empty()) {
        std::ofstream output("BASE64_OUT.txt");
        output << base64Data;
        output.close();
        std::cout << "JOB DONE!" << std::endl;
    }
    else {
        printf("Cnt create errr 0x1\n");
        
    }
    return 0;
}