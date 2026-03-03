#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <locale.h>
#include <iostream>
#include <string>
#include <vector>
#include <codecvt>
#include "WinRarConfig.hpp"
#include "WinRarKeygen.hpp"
#include <system_error>

#pragma comment(lib, "Version.lib")

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

std::wstring GetExecutableVersion() {
    wchar_t exePath[MAX_PATH] = {};
    DWORD pathLen = GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    if (pathLen == 0) {
        return L"unknown";
    }

    DWORD handle = 0;
    DWORD versionSize = GetFileVersionInfoSizeW(exePath, &handle);
    if (versionSize == 0) {
        return L"unknown";
    }

    std::vector<BYTE> versionData(versionSize);
    if (!GetFileVersionInfoW(exePath, 0, versionSize, versionData.data())) {
        return L"unknown";
    }

    VS_FIXEDFILEINFO* fixedInfo = nullptr;
    UINT len = 0;
    if (!VerQueryValueW(versionData.data(), L"\\",
                        reinterpret_cast<LPVOID*>(&fixedInfo),
                        &len) ||
        fixedInfo == nullptr) {
        return L"unknown";
    }

    return std::to_wstring(HIWORD(fixedInfo->dwFileVersionMS)) + L"." +
           std::to_wstring(LOWORD(fixedInfo->dwFileVersionMS)) + L"." +
           std::to_wstring(HIWORD(fixedInfo->dwFileVersionLS)) + L"." +
           std::to_wstring(LOWORD(fixedInfo->dwFileVersionLS));
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

bool IsConsoleHandle(HANDLE handle) {
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE) {
        return false;
    }
    DWORD mode = 0;
    return GetConsoleMode(handle, &mode) != 0;
}

void ConfigureConsoleOutput() {
    HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE stderrHandle = GetStdHandle(STD_ERROR_HANDLE);

    int mode;

    // console use UTF-16, file use UTF-8
    if (IsConsoleHandle(stdoutHandle)) {
        if ((mode = _setmode(_fileno(stdout), _O_WTEXT)) == -1)
            std::wcerr << L"Failed to set stdout _O_WTEXT\n";
    }
    else {
        // stdout is redirected to a file, use UTF-8
        if ((mode = _setmode(_fileno(stdout), _O_U8TEXT)) == -1)
            std::wcerr << L"Failed to set stdout _O_U8TEXT\n";
    }

    if (IsConsoleHandle(stderrHandle)) {
        if ((mode = _setmode(_fileno(stderr), _O_WTEXT)) == -1)
            std::wcerr << L"Failed to set stderr _O_WTEXT\n";
    }
    else {
        if ((mode = _setmode(_fileno(stderr), _O_U8TEXT)) == -1)
            std::wcerr << L"Failed to set stderr _O_U8TEXT\n";
    }
}

int wmain(int argc, wchar_t* argv[]) {
    ConfigureConsoleOutput();

    if (argc == 2 &&
        (_wcsicmp(argv[1], L"ver") == 0 || _wcsicmp(argv[1], L"--version") == 0 || _wcsicmp(argv[1], L"-v") == 0)) {
        std::wcout << GetExecutableVersion() << L"\n";
    }
    else if (argc == 3) {
        try {
            std::string user = WideToUtf8(argv[1]);
            std::string license = WideToUtf8(argv[2]);

            PrintRegisterInfo(
                WinRarKeygen<WinRarConfig>::GenerateRegisterInfo(user.c_str(), license.c_str())
            );
        }
        catch (std::exception& e) {
            std::wcerr << L"Error: " << Utf8ToWide(e.what()) << L"\n";
            return -1;
        }
    }
    else {
        Help();
    }

    return 0;
}
