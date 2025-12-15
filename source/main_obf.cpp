#include <windows.h>
#include <iostream>
#include <filesystem>
#include <string>

#include "obfusheader.h"

namespace fs = std::filesystem;

int main() {
    // 1 системный вызов через WinAPI (достаточно для лабы)
    DWORD pid = GetCurrentProcessId();

    // Важно: OBF("...") используем прямо в выводе (как в README obfusheader.h)
    std::cout << OBF("Lab #3 - Obfuscation\n");
    std::cout << OBF("Performed by: GOFMAN N.A. and AKSENOV V.V.\n");
    std::cout << OBF("PID: ") << pid << "\n\n";

    char userProfile[MAX_PATH]{0};

    // Обфусцируем строку имени переменной окружения
    DWORD n = GetEnvironmentVariableA(OBF("USERPROFILE"), userProfile, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) {
        std::cerr << OBF("Failed to get USERPROFILE\n");
        return 1;
    }

    // Обфусцируем "\\Documents" и префиксы вывода
    std::string docs = std::string(userProfile) + OBF("\\Documents");
    std::cout << OBF("Listing: ") << docs << "\n\n";

    try {
        for (const auto& entry : fs::directory_iterator(docs)) {
            std::cout << (entry.is_directory() ? OBF("[DIR]  ") : OBF("[FILE] "))
                      << entry.path().filename().string() << "\n";
        }
    } catch (const std::exception&) {
        // (e.what() не выводим, чтобы не светить лишние строки)
        std::cerr << OBF("Error reading directory\n");
        return 1;
    }

    return 0;
}
