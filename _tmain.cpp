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

std::string WideToAnsi(const std::wstring& wstr) {
    if (wstr.empty()) return {};
    BOOL usedDefaultChar = FALSE;
    int size = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wstr.data(), (int)wstr.size(),
                                   nullptr, 0, nullptr, &usedDefaultChar);
    if (size == 0 || usedDefaultChar) {
        throw std::runtime_error(
            "Input contains characters not representable in the current ANSI code page. "
            "Use '-e utf8' for Unicode characters.");
    }
    std::string result(size, 0);
    WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wstr.data(), (int)wstr.size(),
                        &result[0], size, nullptr, nullptr);
    return result;
}

enum class Encoding { ASCII, ANSI, UTF8 };

struct Options {
    std::wstring username;
    std::wstring license;
    Encoding encoding = Encoding::UTF8;
    std::wstring outputFile = L"rarreg.key";
    bool textOnly = false;
    bool activate = false;
    bool showVersion = false;
    bool showHelp = false;
};

bool ParseArguments(int argc, wchar_t* argv[], Options& opts) {
    std::vector<std::wstring> positional;
    for (int i = 1; i < argc; ++i) {
        std::wstring arg = argv[i];
        if (arg == L"-v" || arg == L"--version" || _wcsicmp(arg.c_str(), L"ver") == 0) {
            opts.showVersion = true; return true;
        }
        if (arg == L"-h" || arg == L"--help" || _wcsicmp(arg.c_str(), L"help") == 0) {
            opts.showHelp = true; return true;
        }
        if (arg == L"-t" || arg == L"--text") {
            opts.textOnly = true; continue;
        }
        if (arg == L"-a" || arg == L"--activate") {
            opts.activate = true; continue;
        }
        if (arg == L"-e" || arg == L"--encoding") {
            if (++i >= argc) {
                std::wcerr << L"Error: Missing value for " << arg << L"\n";
                return false;
            }
            std::wstring val = argv[i];
            if (_wcsicmp(val.c_str(), L"ascii") == 0) opts.encoding = Encoding::ASCII;
            else if (_wcsicmp(val.c_str(), L"ansi") == 0) opts.encoding = Encoding::ANSI;
            else if (_wcsicmp(val.c_str(), L"utf8") == 0 || _wcsicmp(val.c_str(), L"utf-8") == 0)
                opts.encoding = Encoding::UTF8;
            else {
                std::wcerr << L"Error: Unknown encoding '" << val << L"'. Use: ascii, ansi, utf8\n";
                return false;
            }
            continue;
        }
        if (arg == L"-o" || arg == L"--output") {
            if (++i >= argc) {
                std::wcerr << L"Error: Missing value for " << arg << L"\n";
                return false;
            }
            opts.outputFile = argv[i]; continue;
        }
        if (!arg.empty() && arg[0] == L'-') {
            std::wcerr << L"Error: Unknown option '" << arg << L"'\n";
            return false;
        }
        positional.push_back(arg);
    }
    if (positional.size() == 2) {
        opts.username = positional[0];
        opts.license = positional[1];
        return true;
    }
    if (positional.empty()) {
        opts.showHelp = true; return true;
    }
    std::wcerr << L"Error: Expected 2 arguments (Username, LicenseName), got "
               << positional.size() << L"\n";
    return false;
}

void ShowHelp(const std::wstring& version) {
    std::wcout << L"WinRAR Keygen v" << version << L"\n\n";
    std::wcout << L"Usage:\n";
    std::wcout << L"  winrar-keygen.exe <Username> <LicenseName> [options]\n";
    std::wcout << L"  winrar-keygen.exe -v | --version\n";
    std::wcout << L"  winrar-keygen.exe -h | --help\n\n";
    std::wcout << L"Options:\n";
    std::wcout << L"  -e, --encoding <enc>   utf8 (default), ascii, ansi\n";
    std::wcout << L"  -o, --output <file>    Output file (default: rarreg.key)\n";
    std::wcout << L"  -a, --activate         Write to %%APPDATA%%\\WinRAR\\rarreg.key\n";
    std::wcout << L"  -t, --text             Print to console only, don't write file\n";
    std::wcout << L"  -v, --version          Show version\n";
    std::wcout << L"  -h, --help             Show this help\n\n";
    std::wcout << L"Examples:\n";
    std::wcout << L"  winrar-keygen.exe \"Github\" \"Single PC usage license\"\n";
    std::wcout << L"  winrar-keygen.exe \"Github\" \"Single PC usage license\" -e ansi\n";
    std::wcout << L"  winrar-keygen.exe \"YourName\" \"Single PC usage license\" -e utf8\n";
    std::wcout << L"  winrar-keygen.exe \"Github\" \"Single PC usage license\" -o \"D:\\keys\\rarreg.key\"\n";
    std::wcout << L"  winrar-keygen.exe \"Github\" \"Single PC usage license\" --activate\n";
    std::wcout << L"  winrar-keygen.exe \"Github\" \"Single PC usage license\" -t\n";
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

void PrintRegisterInfo(const WinRarKeygen<WinRarConfig>::RegisterInfo& Info,
                       const std::wstring& wUser, const std::wstring& wLicense) {
    std::wstring uid = Utf8ToWide(Info.UID);
    std::wstring data = Utf8ToWide(Info.HexData);

    std::wcout << L"RAR registration data\n";
    std::wcout << wUser << L"\n";
    std::wcout << wLicense << L"\n";
    std::wcout << L"UID=" << uid << L"\n";

    for (size_t i = 0; i < data.length(); i += 54) {
        std::wcout << data.substr(i, 54) << L"\n";
    }
}

std::string BuildRegFileContent(const WinRarKeygen<WinRarConfig>::RegisterInfo& Info) {
    std::string s;
    s += "RAR registration data\r\n";
    s += Info.UserName + "\r\n";
    s += Info.LicenseType + "\r\n";
    s += "UID=" + Info.UID + "\r\n";
    for (size_t i = 0; i < Info.HexData.length(); i += 54) {
        s += Info.HexData.substr(i, 54) + "\r\n";
    }
    return s;
}

bool WriteRegFile(const std::wstring& filePath, const std::string& content) {
    FILE* fp = nullptr;
    if (_wfopen_s(&fp, filePath.c_str(), L"wb") != 0 || !fp)
        return false;
    size_t written = fwrite(content.data(), 1, content.size(), fp);
    fclose(fp);
    return written == content.size();
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

    // console use UTF-16, file use UTF-8
    if (IsConsoleHandle(stdoutHandle)) {
        if (_setmode(_fileno(stdout), _O_WTEXT) == -1)
            std::wcerr << L"Failed to set stdout _O_WTEXT\n";
    }
    else {
        // stdout is redirected to a file, use UTF-8
        if (_setmode(_fileno(stdout), _O_U8TEXT) == -1)
            std::wcerr << L"Failed to set stdout _O_U8TEXT\n";
    }

    if (IsConsoleHandle(stderrHandle)) {
        if (_setmode(_fileno(stderr), _O_WTEXT) == -1)
            std::wcerr << L"Failed to set stderr _O_WTEXT\n";
    }
    else {
        if (_setmode(_fileno(stderr), _O_U8TEXT) == -1)
            std::wcerr << L"Failed to set stderr _O_U8TEXT\n";
    }
}

int wmain(int argc, wchar_t* argv[]) {
    ConfigureConsoleOutput();

    Options opts;
    if (!ParseArguments(argc, argv, opts)) {
        return -1;
    }

    std::wstring version = GetExecutableVersion();

    if (opts.showVersion) {
        std::wcout << L"winrar-keygen v" << version << L"\n";
        return 0;
    }
    if (opts.showHelp) {
        ShowHelp(version);
        return 0;
    }

    if (opts.activate && opts.outputFile != L"rarreg.key") {
        std::wcerr << L"Error: --activate and -o cannot be used together.\n";
        return -1;
    }
    if (opts.activate && opts.textOnly) {
        std::wcerr << L"Error: --activate and -t cannot be used together.\n";
        return -1;
    }

    if (opts.activate) {
        wchar_t appdata[MAX_PATH] = {};
        DWORD len = ExpandEnvironmentStringsW(L"%APPDATA%\\WinRAR", appdata, MAX_PATH);
        if (len == 0 || len > MAX_PATH) {
            std::wcerr << L"Error: Failed to resolve %%APPDATA%% path.\n";
            return -1;
        }
        CreateDirectoryW(appdata, nullptr);
        opts.outputFile = std::wstring(appdata) + L"\\rarreg.key";
    }

    try {
        if (opts.username.empty() || opts.license.empty()) {
            std::wcerr << L"Error: Username and License Name must not be empty.\n";
            return -1;
        }
        if (opts.username.length() > 200 || opts.license.length() > 200) {
            std::wcerr << L"Error: Username and License Name must not exceed 200 characters.\n";
            return -1;
        }

        std::wstring wDisplayUser = opts.username;
        std::wstring wDisplayLicense = opts.license;
        std::string user, license;

        switch (opts.encoding) {
        case Encoding::UTF8: {
            auto hasNonAscii = [](const std::wstring& s) {
                for (wchar_t c : s)
                    if (static_cast<unsigned>(c) > 127) return true;
                return false;
            };
            if (hasNonAscii(wDisplayUser) &&
                (wDisplayUser.length() < 5 || wDisplayUser.substr(0, 5) != L"utf8:"))
                wDisplayUser = L"utf8:" + wDisplayUser;
            if (hasNonAscii(wDisplayLicense) &&
                (wDisplayLicense.length() < 5 || wDisplayLicense.substr(0, 5) != L"utf8:"))
                wDisplayLicense = L"utf8:" + wDisplayLicense;
            user = WideToUtf8(wDisplayUser);
            license = WideToUtf8(wDisplayLicense);
            break;
        }
        case Encoding::ANSI:
            user = WideToAnsi(wDisplayUser);
            license = WideToAnsi(wDisplayLicense);
            break;
        case Encoding::ASCII:
        default:
            user = WideToAnsi(wDisplayUser);
            license = WideToAnsi(wDisplayLicense);
            for (unsigned char c : user)
                if (c > 127)
                    throw std::runtime_error(
                        "Username contains non-ASCII characters. Use '-e ansi' or '-e utf8'.");
            for (unsigned char c : license)
                if (c > 127)
                    throw std::runtime_error(
                        "License name contains non-ASCII characters. Use '-e ansi' or '-e utf8'.");
            break;
        }

        auto Info = WinRarKeygen<WinRarConfig>::GenerateRegisterInfo(user.c_str(), license.c_str());

        if (opts.textOnly) {
            PrintRegisterInfo(Info, wDisplayUser, wDisplayLicense);
        } else {
            std::string content = BuildRegFileContent(Info);
            if (!WriteRegFile(opts.outputFile, content)) {
                std::wcerr << L"Error: Failed to write file: " << opts.outputFile << L"\n";
                return -1;
            }

            const wchar_t* encName = (opts.encoding == Encoding::UTF8) ? L"UTF-8" :
                                     (opts.encoding == Encoding::ANSI) ? L"ANSI" : L"ASCII";

            std::wcout << L"\n";
            PrintRegisterInfo(Info, wDisplayUser, wDisplayLicense);
            std::wcout << L"\nDone! " << opts.outputFile << L" has been generated. ("
                       << encName << L")\n";
        }
    }
    catch (std::exception& e) {
        std::wcerr << L"Error: " << Utf8ToWide(e.what()) << L"\n";
        return -1;
    }

    return 0;
}
