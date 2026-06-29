namespace WinRarKeygenGui.Services;

public sealed class AppText
{
    public required string Username { get; init; }
    public required string LicenseName { get; init; }
    public required string Encoding { get; init; }
    public required string Output { get; init; }
    public required string Browse { get; init; }
    public required string ActivateWinRar { get; init; }
    public required string WriteTo { get; init; }
    public required string GenerateKey { get; init; }
    public required string Settings { get; init; }
    public required string Back { get; init; }
    public required string CheckForUpdatesTooltip { get; init; }
    public required string Appearance { get; init; }
    public required string Theme { get; init; }
    public required string Language { get; init; }
    public required string WindowsDefault { get; init; }
    public required string Light { get; init; }
    public required string Dark { get; init; }
    public required string RememberSettings { get; init; }
    public required string RememberSettingsDescription { get; init; }
    public required string AutofillLicenseName { get; init; }
    public required string AutofillLicenseNameDescription { get; init; }
    public required string BackUpExistingKey { get; init; }
    public required string BackUpExistingKeyDescription { get; init; }
    public required string CheckForUpdates { get; init; }
    public required string CheckForUpdatesDescription { get; init; }
    public required string GeneratedKey { get; init; }
    public required string Generated { get; init; }
    public required string Copy { get; init; }
    public required string Copied { get; init; }
    public required string KeyWrittenTo { get; init; }
    public required string Saved { get; init; }
    public required string Activated { get; init; }
    public required string ErrorPrefix { get; init; }
    public required string CheckingForUpdates { get; init; }
    public required string LatestVersion { get; init; }
    public required string AsciiWarning { get; init; }
    public required string AnsiWarning { get; init; }
    public required string UsernameNonAsciiError { get; init; }
    public required string LicenseNameNonAsciiError { get; init; }
    public required string SaveDialogFilter { get; init; }

    public static AppText English { get; } = new()
    {
        Username = "Username",
        LicenseName = "License Name",
        Encoding = "Encoding",
        Output = "Output",
        Browse = "Browse",
        ActivateWinRar = "Activate WinRAR",
        WriteTo = "Write to ",
        GenerateKey = "Generate Key",
        Settings = "Settings",
        Back = "Back",
        CheckForUpdatesTooltip = "Check for updates",
        Appearance = "Appearance",
        Theme = "Theme",
        Language = "Language",
        WindowsDefault = "Windows default",
        Light = "Light",
        Dark = "Dark",
        RememberSettings = "Remember Settings",
        RememberSettingsDescription = "Persist preferences between sessions",
        AutofillLicenseName = "Autofill License Name",
        AutofillLicenseNameDescription = "Defaults to Single PC usage license",
        BackUpExistingKey = "Back Up Existing Key",
        BackUpExistingKeyDescription = "Back up rarreg.key before overwriting",
        CheckForUpdates = "Check for Updates",
        CheckForUpdatesDescription = "Automatically check GitHub for new releases",
        GeneratedKey = "Generated Key",
        Generated = "Generated",
        Copy = "Copy",
        Copied = "Copied",
        KeyWrittenTo = "Key written to ",
        Saved = "Saved",
        Activated = "Activated",
        ErrorPrefix = "Error",
        CheckingForUpdates = "Checking for updates",
        LatestVersion = "You have the latest version",
        AsciiWarning = "Contains non-ASCII characters. Name may appear garbled in the license.",
        AnsiWarning = "Contains non-ASCII characters. ANSI encoding is locale-dependent and may produce garbled text on other systems.",
        UsernameNonAsciiError = "Username contains non-ASCII characters. Use UTF-8 encoding.",
        LicenseNameNonAsciiError = "License name contains non-ASCII characters. Use UTF-8 encoding.",
        SaveDialogFilter = "Key files (*.key)|*.key|All files (*.*)|*.*"
    };

    public static AppText SimplifiedChinese { get; } = new()
    {
        Username = "用户名",
        LicenseName = "许可证名称",
        Encoding = "编码",
        Output = "输出",
        Browse = "浏览",
        ActivateWinRar = "激活 WinRAR",
        WriteTo = "写入到 ",
        GenerateKey = "生成密钥",
        Settings = "设置",
        Back = "返回",
        CheckForUpdatesTooltip = "检查更新",
        Appearance = "外观",
        Theme = "主题",
        Language = "语言",
        WindowsDefault = "Windows 默认",
        Light = "浅色",
        Dark = "深色",
        RememberSettings = "记住设置",
        RememberSettingsDescription = "在会话之间保留偏好设置",
        AutofillLicenseName = "自动填充许可证名称",
        AutofillLicenseNameDescription = "默认使用 Single PC usage license",
        BackUpExistingKey = "备份现有密钥",
        BackUpExistingKeyDescription = "覆盖前备份 rarreg.key",
        CheckForUpdates = "检查更新",
        CheckForUpdatesDescription = "自动检查 GitHub 新版本",
        GeneratedKey = "已生成的密钥",
        Generated = "已生成",
        Copy = "复制",
        Copied = "已复制",
        KeyWrittenTo = "密钥已写入 ",
        Saved = "已保存",
        Activated = "已激活",
        ErrorPrefix = "错误",
        CheckingForUpdates = "正在检查更新",
        LatestVersion = "当前已是最新版本",
        AsciiWarning = "包含非 ASCII 字符。名称在许可证中可能显示为乱码。",
        AnsiWarning = "包含非 ASCII 字符。ANSI 编码依赖系统区域设置，在其他系统上可能产生乱码。",
        UsernameNonAsciiError = "用户名包含非 ASCII 字符。请使用 UTF-8 编码。",
        LicenseNameNonAsciiError = "许可证名称包含非 ASCII 字符。请使用 UTF-8 编码。",
        SaveDialogFilter = "密钥文件 (*.key)|*.key|所有文件 (*.*)|*.*"
    };

    public static AppText FromLanguageMode(string languageMode)
    {
        return languageMode == "zh-CN" ? SimplifiedChinese : English;
    }
}
