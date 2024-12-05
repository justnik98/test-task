#include "utils.h"

#include <iostream>
#include <fstream>
#include "utils.h"

#include <cstdint>


// Функция определения размера файла
std::ifstream::pos_type filesize(const std::string& filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

// Функция для чтения содержимого файла
std::vector<char> readFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error on opening file: " << filePath << std::endl;
        return {};
    }

    std::vector<char> fileContents;
    fileContents.resize(filesize(filePath));
    file.read(reinterpret_cast<char*>(&fileContents[0]), fileContents.size());
    file.close();

    return fileContents;
}

// Функция для записи содержимого файла
void writeFile(const std::string& filePath, const std::vector<int8_t>& fileContents) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error on opening file: " << filePath << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&fileContents[0]), fileContents.size());
    file.close();
}

// Функция для выполнения бинарной операции XOR с заданным значением
std::vector<int8_t> modifyFile(const std::vector<char>& fileContents, const std::vector<int8_t>& mask) {
    std::vector<int8_t> modifiedFileContents;
    modifiedFileContents.resize(fileContents.size());

    for (size_t i = 0; i < fileContents.size(); ++i) {
        modifiedFileContents[i] = mask[i % mask.size()] ^ static_cast<int8_t>( fileContents[i]);
    }

    return modifiedFileContents;
}

// Функция для обработки ошибок
void handleError(const std::string& message) {
    std::cerr << message << std::endl;
    exit(1);
}