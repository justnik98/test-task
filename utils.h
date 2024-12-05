#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <string>
#include <vector>

std::vector<char> readFile(const std::string &filePath);

void writeFile(const std::string &filePath, const std::vector<int8_t> &fileContents);

std::vector<int8_t> modifyFile(const std::vector<char> &fileContents, const std::vector<int8_t> &mask);

void handleError(const std::string &message);
#endif //UTILS_H
