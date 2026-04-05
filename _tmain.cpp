#ifdef _WIN32
#include <windows.h>
#include <winhttp.h>
#include <fcntl.h>
#include <io.h>
#else
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>
#include <strings.h>
#endif

#include <locale.h>
#include <iostream>
#include <string>
#include <vector>
#include "WinRarConfig.hpp"
#include "WinRarKeygen.hpp"
#include <stdexcept>

#ifdef _WIN32
#pragma comment(lib, "Version.lib")
#pragma comment(lib, "winhttp.lib")
#endif

#ifndef APP_VERSION
#define APP_VERSION "4.1.0.0"
#endif

#ifdef _WIN32
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
#endif

enum class Encoding { ASCII, ANSI, UTF8 };

struct Options {
#ifdef _WIN32
    std::wstring username;
    std::wstring license;
    Encoding encoding = Encoding::UTF8;
    std::wstring outputFile = L"rarreg.key";
#else
    std::string username;
    std::string license;
    Encoding encoding = Encoding::UTF8;
    std::string outputFile = "rarreg.key";
#endif
    bool textOnly = false;
    bool activate = false;
    bool showVersion = false;
    bool showHelp = false;
    bool checkUpdate = false;
};

#ifdef _WIN32
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
        if (arg == L"-u" || arg == L"--update") {
            opts.checkUpdate = true; return true;
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
#else
bool ParseArguments(int argc, char* argv[], Options& opts) {
    std::vector<std::string> positional;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-v" || arg == "--version" || strcasecmp(arg.c_str(), "ver") == 0) {
            opts.showVersion = true; return true;
        }
        if (arg == "-h" || arg == "--help" || strcasecmp(arg.c_str(), "help") == 0) {
            opts.showHelp = true; return true;
        }
        if (arg == "-t" || arg == "--text") {
            opts.textOnly = true; continue;
        }
        if (arg == "-a" || arg == "--activate") {
            opts.activate = true; continue;
        }
        if (arg == "-u" || arg == "--update") {
            opts.checkUpdate = true; return true;
        }
        if (arg == "-e" || arg == "--encoding") {
            if (++i >= argc) {
                std::cerr << "Error: Missing value for " << arg << "\n";
                return false;
            }
            std::string val = argv[i];
            if (strcasecmp(val.c_str(), "ascii") == 0) opts.encoding = Encoding::ASCII;
            else if (strcasecmp(val.c_str(), "ansi") == 0) opts.encoding = Encoding::ANSI;
            else if (strcasecmp(val.c_str(), "utf8") == 0 || strcasecmp(val.c_str(), "utf-8") == 0)
                opts.encoding = Encoding::UTF8;
            else {
                std::cerr << "Error: Unknown encoding '" << val << "'. Use: ascii, ansi, utf8\n";
                return false;
            }
            continue;
        }
        if (arg == "-o" || arg == "--output") {
            if (++i >= argc) {
                std::cerr << "Error: Missing value for " << arg << "\n";
                return false;
            }
            opts.outputFile = argv[i]; continue;
        }
        if (!arg.empty() && arg[0] == '-') {
            std::cerr << "Error: Unknown option '" << arg << "'\n";
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
    std::cerr << "Error: Expected 2 arguments (Username, LicenseName), got "
              << positional.size() << "\n";
    return false;
}
#endif

#ifdef _WIN32
void ShowHelp(const std::wstring& version) {
    std::wcout << L"WinRAR Keygen v" << version << L"\n\n";
    std::wcout << L"Usage:\n";
    std::wcout << L"  winrar-keygen.exe <Username> <LicenseName> [options]\n";
    std::wcout << L"  winrar-keygen.exe -v | --version\n";
    std::wcout << L"  winrar-keygen.exe -h | --help\n\n";
    std::wcout << L"Options:\n";
    std::wcout << L"  -e, --encoding <enc>   utf8 (default), ascii, ansi\n";
    std::wcout << L"  -o, --output <file>    Output file (default: rarreg.key)\n";
    std::wcout << L"  -a, --activate         Write to %APPDATA%\\WinRAR\\rarreg.key\n";
    std::wcout << L"  -t, --text             Print to console only, don't write file\n";
    std::wcout << L"  -u, --update           Check for updates on GitHub\n";
    std::wcout << L"  -v, --version          Show version\n";
    std::wcout << L"  -h, --help             Show this help\n\n";
    std::wcout << L"Examples:\n";
    std::wcout << L"  winrar-keygen.exe \"Github\" \"Single PC usage license\"\n";
    std::wcout << L"  winrar-keygen.exe \"Github\" \"Single PC usage license\" -e ascii\n";
    std::wcout << L"  winrar-keygen.exe \"Github\" \"Single PC usage license\" -a\n";
    std::wcout << L"  winrar-keygen.exe \"Github\" \"Single PC usage license\" -t\n";
}
#else
void ShowHelp(const std::string& version) {
    std::cout << "WinRAR Keygen v" << version << "\n\n";
    std::cout << "Usage:\n";
    std::cout << "  winrar-keygen <Username> <LicenseName> [options]\n";
    std::cout << "  winrar-keygen -v | --version\n";
    std::cout << "  winrar-keygen -h | --help\n\n";
    std::cout << "Options:\n";
    std::cout << "  -e, --encoding <enc>   utf8 (default), ascii\n";
    std::cout << "  -o, --output <file>    Output file (default: rarreg.key)\n";
#ifdef __APPLE__
    std::cout << "  -a, --activate         Write to ~/Library/Application Support/com.rarlab.WinRAR/rarreg.key\n";
#else
    std::cout << "  -a, --activate         Write to ~/.rarkey\n";
#endif
    std::cout << "  -t, --text             Print to console only, don't write file\n";
    std::cout << "  -u, --update           Check for updates on GitHub\n";
    std::cout << "  -v, --version          Show version\n";
    std::cout << "  -h, --help             Show this help\n\n";
    std::cout << "Examples:\n";
    std::cout << "  winrar-keygen \"Github\" \"Single PC usage license\"\n";
    std::cout << "  winrar-keygen \"Github\" \"Single PC usage license\" -e ascii\n";
    std::cout << "  winrar-keygen \"Github\" \"Single PC usage license\" -a\n";
    std::cout << "  winrar-keygen \"Github\" \"Single PC usage license\" -t\n";
}
#endif

#ifdef _WIN32
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
#else
std::string GetAppVersion() {
    return APP_VERSION;
}
#endif

#ifdef _WIN32
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
#else
void PrintRegisterInfo(const WinRarKeygen<WinRarConfig>::RegisterInfo& Info,
                       const std::string& user, const std::string& license) {
    std::cout << "RAR registration data\n";
    std::cout << user << "\n";
    std::cout << license << "\n";
    std::cout << "UID=" << Info.UID << "\n";

    for (size_t i = 0; i < Info.HexData.length(); i += 54) {
        std::cout << Info.HexData.substr(i, 54) << "\n";
    }
}
#endif

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

#ifdef _WIN32
bool WriteRegFile(const std::wstring& filePath, const std::string& content) {
    FILE* fp = nullptr;
    if (_wfopen_s(&fp, filePath.c_str(), L"wb") != 0 || !fp)
        return false;
    size_t written = fwrite(content.data(), 1, content.size(), fp);
    fclose(fp);
    return written == content.size();
}
#else
bool WriteRegFile(const std::string& filePath, const std::string& content) {
    FILE* fp = fopen(filePath.c_str(), "wb");
    if (!fp) return false;
    size_t written = fwrite(content.data(), 1, content.size(), fp);
    fclose(fp);
    return written == content.size();
}
#endif

#ifdef _WIN32
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
#endif

struct Version {
    int major = 0, minor = 0, patch = 0;
    bool valid = false;
};

Version ParseVersion(const std::string& verStr) {
    Version v;
    std::string s = verStr;
    if (!s.empty() && (s[0] == 'v' || s[0] == 'V')) s = s.substr(1);
#ifdef _MSC_VER
    int count = sscanf_s(s.c_str(), "%d.%d.%d", &v.major, &v.minor, &v.patch);
#else
    int count = sscanf(s.c_str(), "%d.%d.%d", &v.major, &v.minor, &v.patch);
#endif
    v.valid = (count >= 2);
    return v;
}

bool IsNewer(const Version& remote, const Version& local) {
    if (remote.major != local.major) return remote.major > local.major;
    if (remote.minor != local.minor) return remote.minor > local.minor;
    return remote.patch > local.patch;
}

std::string ExtractTagFromJson(const std::string& responseBody) {
    std::string tagKey = "\"tag_name\"";
    size_t pos = responseBody.find(tagKey);
    if (pos == std::string::npos) return "";
    pos = responseBody.find('\"', pos + tagKey.length());
    if (pos == std::string::npos) return "";
    size_t end = responseBody.find('\"', pos + 1);
    if (end == std::string::npos) return "";
    return responseBody.substr(pos + 1, end - pos - 1);
}

int CompareAndPrintUpdate(const std::string& currentVersion, const std::string& remoteTag) {
    Version local = ParseVersion(currentVersion);
    Version remote = ParseVersion(remoteTag);

    if (!remote.valid) {
#ifdef _WIN32
        std::wcerr << L"Error: Could not parse remote version '" << Utf8ToWide(remoteTag) << L"'.\n";
#else
        std::cerr << "Error: Could not parse remote version '" << remoteTag << "'.\n";
#endif
        return -1;
    }

    if (IsNewer(remote, local)) {
#ifdef _WIN32
        std::wcout << L"\n  New version available: " << Utf8ToWide(remoteTag)
                   << L" (current: v" << Utf8ToWide(currentVersion) << L")\n";
        std::wcout << L"  Download: https://github.com/bitcookies/winrar-keygen/releases/latest\n\n";
#else
        std::cout << "\n  New version available: " << remoteTag
                  << " (current: v" << currentVersion << ")\n";
        std::cout << "  Download: https://github.com/bitcookies/winrar-keygen/releases/latest\n\n";
#endif
    } else {
#ifdef _WIN32
        std::wcout << L"Already up to date. (v" << Utf8ToWide(currentVersion) << L")\n";
#else
        std::cout << "Already up to date. (v" << currentVersion << ")\n";
#endif
    }

    return 0;
}

#ifdef _WIN32
int CheckForUpdate(const std::string& currentVersion) {
    std::wcout << L"Checking for updates...\n";

    HINTERNET hSession = WinHttpOpen(L"winrar-keygen-updater",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
        std::wcerr << L"Error: Failed to initialize WinHTTP.\n";
        return -1;
    }

    HINTERNET hConnect = WinHttpConnect(hSession, L"api.github.com",
        INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!hConnect) {
        std::wcerr << L"Error: Failed to connect to api.github.com.\n";
        WinHttpCloseHandle(hSession);
        return -1;
    }

    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET",
        L"/repos/bitcookies/winrar-keygen/releases/latest",
        nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    if (!hRequest) {
        std::wcerr << L"Error: Failed to create HTTP request.\n";
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return -1;
    }

    BOOL bResult = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    if (!bResult) {
        std::wcerr << L"Error: Failed to send HTTP request. Check your network connection.\n";
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return -1;
    }

    bResult = WinHttpReceiveResponse(hRequest, nullptr);
    if (!bResult) {
        std::wcerr << L"Error: No response from GitHub API.\n";
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return -1;
    }

    std::string responseBody;
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    do {
        dwSize = 0;
        WinHttpQueryDataAvailable(hRequest, &dwSize);
        if (dwSize == 0) break;
        std::vector<char> buffer(dwSize);
        WinHttpReadData(hRequest, buffer.data(), dwSize, &dwDownloaded);
        responseBody.append(buffer.data(), dwDownloaded);
    } while (dwSize > 0);

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    if (responseBody.empty()) {
        std::wcerr << L"Error: Empty response from GitHub API.\n";
        return -1;
    }

    std::string remoteTag = ExtractTagFromJson(responseBody);
    if (remoteTag.empty()) {
        std::wcerr << L"Error: Could not find version info in GitHub response.\n";
        return -1;
    }

    return CompareAndPrintUpdate(currentVersion, remoteTag);
}
#else
int CheckForUpdate(const std::string& currentVersion) {
    std::cout << "Checking for updates...\n";

    FILE* pipe = popen("curl -s https://api.github.com/repos/bitcookies/winrar-keygen/releases/latest 2>/dev/null", "r");
    if (!pipe) {
        std::cerr << "Error: Failed to run curl. Make sure curl is installed.\n";
        return -1;
    }

    std::string responseBody;
    char buf[4096];
    while (fgets(buf, sizeof(buf), pipe)) {
        responseBody += buf;
    }
    int status = pclose(pipe);

    if (status != 0 || responseBody.empty()) {
        std::cerr << "Error: Failed to fetch update info. Check your network connection.\n";
        return -1;
    }

    std::string remoteTag = ExtractTagFromJson(responseBody);
    if (remoteTag.empty()) {
        std::cerr << "Error: Could not find version info in GitHub response.\n";
        return -1;
    }

    return CompareAndPrintUpdate(currentVersion, remoteTag);
}
#endif

#ifdef _WIN32
int wmain(int argc, wchar_t* argv[]) {
    ConfigureConsoleOutput();

    Options opts;
    if (!ParseArguments(argc, argv, opts)) {
        return -1;
    }

    std::wstring version = GetExecutableVersion();
    std::string versionUtf8 = WideToUtf8(version);

    if (opts.showVersion) {
        std::wcout << L"winrar-keygen v" << version << L"\n";
        return 0;
    }
    if (opts.showHelp) {
        ShowHelp(version);
        return 0;
    }
    if (opts.checkUpdate) {
        return CheckForUpdate(versionUtf8);
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
            std::wcerr << L"Error: Failed to resolve %APPDATA% path.\n";
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
#else
int main(int argc, char* argv[]) {
    Options opts;
    if (!ParseArguments(argc, argv, opts)) {
        return -1;
    }

    std::string version = GetAppVersion();

    if (opts.showVersion) {
        std::cout << "winrar-keygen v" << version << "\n";
        return 0;
    }
    if (opts.showHelp) {
        ShowHelp(version);
        return 0;
    }
    if (opts.checkUpdate) {
        return CheckForUpdate(version);
    }

    if (opts.activate && opts.outputFile != "rarreg.key") {
        std::cerr << "Error: --activate and -o cannot be used together.\n";
        return -1;
    }
    if (opts.activate && opts.textOnly) {
        std::cerr << "Error: --activate and -t cannot be used together.\n";
        return -1;
    }

    if (opts.activate) {
#ifdef __APPLE__
        const char* home = getenv("HOME");
        if (!home) {
            std::cerr << "Error: Failed to resolve $HOME path.\n";
            return -1;
        }
        std::string activateDir = std::string(home) + "/Library/Application Support/com.rarlab.WinRAR";
        mkdir(activateDir.c_str(), 0755);
        opts.outputFile = activateDir + "/rarreg.key";
#else
        const char* home = getenv("HOME");
        if (!home) {
            std::cerr << "Error: Failed to resolve $HOME path.\n";
            return -1;
        }
        opts.outputFile = std::string(home) + "/.rarkey";
#endif
    }

    try {
        if (opts.username.empty() || opts.license.empty()) {
            std::cerr << "Error: Username and License Name must not be empty.\n";
            return -1;
        }
        if (opts.username.length() > 200 || opts.license.length() > 200) {
            std::cerr << "Error: Username and License Name must not exceed 200 characters.\n";
            return -1;
        }

        std::string displayUser = opts.username;
        std::string displayLicense = opts.license;
        std::string user, license;

        switch (opts.encoding) {
        case Encoding::UTF8: {
            auto hasNonAscii = [](const std::string& s) {
                for (unsigned char c : s)
                    if (c > 127) return true;
                return false;
            };
            if (hasNonAscii(displayUser) &&
                (displayUser.length() < 5 || displayUser.substr(0, 5) != "utf8:"))
                displayUser = "utf8:" + displayUser;
            if (hasNonAscii(displayLicense) &&
                (displayLicense.length() < 5 || displayLicense.substr(0, 5) != "utf8:"))
                displayLicense = "utf8:" + displayLicense;
            user = displayUser;
            license = displayLicense;
            break;
        }
        case Encoding::ANSI:
            std::cerr << "Warning: ANSI encoding is not supported on this platform. Using UTF-8.\n";
            user = displayUser;
            license = displayLicense;
            break;
        case Encoding::ASCII:
        default:
            user = displayUser;
            license = displayLicense;
            for (unsigned char c : user)
                if (c > 127)
                    throw std::runtime_error(
                        "Username contains non-ASCII characters. Use '-e utf8'.");
            for (unsigned char c : license)
                if (c > 127)
                    throw std::runtime_error(
                        "License name contains non-ASCII characters. Use '-e utf8'.");
            break;
        }

        auto Info = WinRarKeygen<WinRarConfig>::GenerateRegisterInfo(user.c_str(), license.c_str());

        if (opts.textOnly) {
            PrintRegisterInfo(Info, displayUser, displayLicense);
        } else {
            std::string content = BuildRegFileContent(Info);
            if (!WriteRegFile(opts.outputFile, content)) {
                std::cerr << "Error: Failed to write file: " << opts.outputFile << "\n";
                return -1;
            }

            const char* encName = (opts.encoding == Encoding::UTF8) ? "UTF-8" :
                                  (opts.encoding == Encoding::ANSI) ? "ANSI" : "ASCII";

            std::cout << "\n";
            PrintRegisterInfo(Info, displayUser, displayLicense);
            std::cout << "\nDone! " << opts.outputFile << " has been generated. ("
                      << encName << ")\n";
        }
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return -1;
    }

    return 0;
}
#endif
