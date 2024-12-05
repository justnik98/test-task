#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include "utils.h"

int main() {
    // Настройка маски входных файлов
    std::string inputFileMask = ".txt";
    std::cout << "Enter the mask of the input files (for example, .txt): " << std::endl;;
    std::cin >> inputFileMask;

    // Настройка необходимости удалять входные файлы
    bool deleteInputFiles = false;
    std::cout << "Delete input files after modification? (yes/no): " << std::endl;;
    std::string deleteInputFilesString;
    std::cin >> deleteInputFilesString;
    if (deleteInputFilesString == "yes") {
        deleteInputFiles = true;
    }

    // Настройка пути для сохранения результирующих файлов
    std::string outputFilePath = "C:\\output\\";
    std::cout << "Enter the path to the resulting files: " << std::endl;
    std::cin >> outputFilePath;

    // Настройка действий при повторении имени выходного файла
    bool overwriteOutputFiles = true;
    std::cout << "Overwrite existing output files? (yes/no): " << std::endl;;
    std::string overwriteOutputFilesString;
    std::cin >> overwriteOutputFilesString;
    if (overwriteOutputFilesString == "no") {
        overwriteOutputFiles = false;
    }

    // Настройка работы по таймеру или разовый запуск
    bool runTimer = false;
    std::cout << "Run the program on a timer? (yes/no):" << std::endl;;
    std::string runTimerString;
    std::cin >> runTimerString;
    if (runTimerString == "yes") {
        runTimer = true;
    }

    // Настройка периодичности опроса наличия входного файла (таймер)
    int timerInterval = 10000; // 10 секунд
    std::cout << "Enter the polling interval for the presence of the input file (in milliseconds):" << std::endl;;
    int timerIntervalInt;
    std::cin >> timerIntervalInt;
    if (timerIntervalInt > 0) {
        timerInterval = timerIntervalInt;
    }

    // Настройка значения для бинарной операции
    std::vector<int8_t> mask(8);
    std::cout << "Enter the value for the binary operation (8 bytes):" << std::endl;;
    for (int i = 0; i < 8; ++i) {
        int8_t maskChar;
        std::cin >> maskChar;
        mask[i] = maskChar;
    }

    // Запуск
    std::vector<std::string> inputFileNames;
    std::vector<std::string> outputFileNames;

    // Цикл для обработки файлов
    while (true) {
        // Ожидаем появления входного файла
        std::cout << "Waiting for the input file...\n";
        std::string inputFileName;
        std::cout << "Enter the name of the input file:" << std::endl; ;
        std::cin >> inputFileName;

        // Добавляем имя входного файла в список
        inputFileNames.push_back(inputFileName);

        // Проверяем, есть ли входной файл
        std::ifstream file(inputFileName, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening the input file:" << inputFileName << std::endl;
            handleError("Error opening the input file");
        }

        // Читаем содержимое входного файла
        std::vector<char> fileContents = readFile(inputFileName);

        // Выполняем бинарную операцию XOR с заданным значением
        std::vector<int8_t> modifiedFileContents = modifyFile(fileContents, mask);

        // Записываем содержимое модифицированного файла
        std::string outputFileName = outputFilePath + inputFileName;
        if (overwriteOutputFiles) {
            outputFileNames.push_back(outputFileName);
            writeFile(outputFileName, modifiedFileContents);
        } else {
            std::cerr << "Error: The output file already exists: " << outputFileName << std::endl;
            handleError("Error: The output file already exists");
        }

        // Удаляем входной файл, если это необходимо
        if (deleteInputFiles) {
            std::remove(inputFileName.c_str());
        }

        // Если нужно, запускаем таймер для следующего опроса
        if (runTimer) {
            std::thread timerThread([timerInterval]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(timerInterval));
                main();
            });
            timerThread.detach();
        }

        // Ожидаем ввода для продолжения или завершения
        std::cout << "Continue? (yes/no): " << std::endl;;
        std::string continueString;
        std::cin >> continueString;
        if (continueString == "no") {
            break;
        }
    }

    return 0;
}
