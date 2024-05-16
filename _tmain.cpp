#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include "WinRarConfig.hpp"
#include "WinRarKeygen.hpp"
#include <system_error>

void Help() {
    _putts(TEXT("Please use the following command:\n"));
    _putts(TEXT("Usage:"));
    _putts(TEXT("        winrar-keygen.exe <Username> <License Name>"));
    _putts(TEXT(""));
    _putts(TEXT("Example:"));
    _putts(TEXT("        winrar-keygen.exe \"Github\" \"Single PC usage license\"\n"));
}

void PrintRegisterInfo(const WinRarKeygen<WinRarConfig>::RegisterInfo& Info) {
    _tprintf_s(TEXT("%hs\n"), "RAR registration data");
    _tprintf_s(TEXT("%hs\n"), Info.UserName.c_str());
    _tprintf_s(TEXT("%hs\n"), Info.LicenseType.c_str());
    _tprintf_s(TEXT("UID=%hs\n"), Info.UID.c_str());
    for (size_t i = 0; i < Info.HexData.length(); i += 54) {
        _tprintf_s(TEXT("%.54hs\n"), Info.HexData.c_str() + i);
    }
}

std::string ToACP(PCWSTR lpszUnicodeString) {
    int len;

    len = WideCharToMultiByte(CP_ACP, 0, lpszUnicodeString, -1, NULL, 0, NULL, NULL);
    if (len == 0) {
        auto err = GetLastError();
        throw std::system_error(err, std::system_category());
    }

    std::string Result(len, '\x00');

    len = WideCharToMultiByte(CP_ACP, 0, lpszUnicodeString, -1, Result.data(), static_cast<int>(Result.length()), NULL, NULL);
    if (len == 0) {
        auto err = GetLastError();
        throw std::system_error(err, std::system_category());
    }

    while (Result.back() == '\x00') {
        Result.pop_back();
    }

    return Result;
}

int _tmain(int argc, PTSTR argv[]) {
    setlocale(LC_ALL, "");
    if (argc == 3) {
        try {
            PrintRegisterInfo(
#if defined(_UNICODE) || defined(UNICODE)
                WinRarKeygen<WinRarConfig>::GenerateRegisterInfo(ToACP(argv[1]).c_str(), ToACP(argv[2]).c_str())
#else
                WinRarKeygen<WinRarConfig>::GenerateRegisterInfo(argv[1], argv[2])
#endif
            );
        } catch (std::exception& e) {
            _tprintf_s(TEXT("%hs\n"), e.what());
            return -1;
        }
    } else {
        Help();
    }
    return 0;
}
