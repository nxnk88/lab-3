#include <windows.h>
#include <iostream>
#include <filesystem>
#include <string>


namespace fs = std::filesystem;

int main() {
    // 1) "Системный вызов" через WinAPI (достаточно для лабы)
    DWORD pid = GetCurrentProcessId(); // WinAPI -> системный вызов в ядро

    // 2) Консоль (если соберёшь как Console subsystem — она и так будет)
    // Если вдруг соберёшь как GUI — можно включить:
    // AllocConsole();
    // freopen("CONOUT$", "w", stdout);

    std::cout << "Lab #3 - Obfuscation\n";
    std::cout << "Performed by: GOFMAN, AKSENOV\n";
    std::cout << "PID: " << pid << "\n\n";

    // 3) Documents текущего пользователя
    char userProfile[MAX_PATH]{0};
    DWORD n = GetEnvironmentVariableA("USERPROFILE", userProfile, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) {
        std::cerr << "Failed to get USERPROFILE\n";
        return 1;
    }

    std::string docs = std::string(userProfile) + "\\Documents";
    std::cout << "Listing: " << docs << "\n\n";

    try {
        for (const auto& entry : fs::directory_iterator(docs)) {
            std::cout << (entry.is_directory() ? "[DIR]  " : "[FILE] ")
                      << entry.path().filename().string() << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading directory: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
