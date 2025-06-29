#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale.h>
#include <iostream>
#include <string>
#include <codecvt>
#include "WinRarConfig.hpp"
#include "WinRarKeygen.hpp"
#include <system_error>

std::string WideToUtf8(const std::wstring& wstr) {
    if (wstr.empty()) return {};
    int size = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
    std::string result(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), &result[0], size, nullptr, nullptr);
    return result;
}

std::wstring Utf8ToWide(const std::string& str) {
    if (str.empty()) return {};
    int size = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), nullptr, 0);
    std::wstring result(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), &result[0], size);
    return result;
}

void Help() {
    std::wcout << L"Please use the following command:\n";
    std::wcout << L"Usage:\n";
    std::wcout << L"        winrar-keygen.exe <Username> <License Name>\n\n";
    std::wcout << L"Example:\n";
    std::wcout << L"        winrar-keygen.exe \"GitHub\" \"Single PC usage license\"\n";
}

void PrintRegisterInfo(const WinRarKeygen<WinRarConfig>::RegisterInfo& Info) {
    std::wstring user = Utf8ToWide(Info.UserName);
    std::wstring license = Utf8ToWide(Info.LicenseType);
    std::wstring uid = Utf8ToWide(Info.UID);
    std::wstring data = Utf8ToWide(Info.HexData);

    std::wcout << L"RAR registration data\n";
    std::wcout << user << L"\n";
    std::wcout << license << L"\n";
    std::wcout << L"UID=" << uid << L"\n";

    for (size_t i = 0; i < data.length(); i += 54) {
        std::wcout << data.substr(i, 54) << L"\n";
    }
}

int wmain(int argc, wchar_t* argv[]) {
    SetConsoleOutputCP(CP_UTF8); // powershell code page set to 65001
    if (_setmode(_fileno(stdout), _O_U8TEXT) == -1) {
        std::wcerr << L"Failed to set console to UTF-8 output mode.\n";
    }
    setlocale(LC_ALL, "");

    if (argc == 3) {
        try {
            std::string user = WideToUtf8(argv[1]);
            std::string license = WideToUtf8(argv[2]);

            PrintRegisterInfo(
                WinRarKeygen<WinRarConfig>::GenerateRegisterInfo(user.c_str(), license.c_str())
            );
        }
        catch (std::exception& e) {
            std::wcerr << L"Error: " << e.what() << L"\n";
            return -1;
        }
    }
    else {
        Help();
    }

    return 0;
}
