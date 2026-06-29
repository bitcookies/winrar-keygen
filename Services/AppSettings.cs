using System;
using System.Globalization;
using System.IO;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace WinRarKeygenGui.Services;

/// <summary>
/// Persists user settings to a JSON file next to the executable.
/// </summary>
public class AppSettings
{
    private static readonly string SettingsPath;

    static AppSettings()
    {
        var exeDir = AppDomain.CurrentDomain.BaseDirectory;
        SettingsPath = Path.Combine(exeDir, "winrar-keygen-settings.json");
    }

    // Persisted properties
    public string Username { get; set; } = "";
    public string LicenseName { get; set; } = "Single PC usage license";
    public int SelectedEncoding { get; set; } = 0;
    public string OutputFilePath { get; set; } = "rarreg.key";
    public bool ActivateWinRar { get; set; } = true;
    public bool AutoFillLicenseName { get; set; } = true;
    public bool BackupExistingKey { get; set; } = true;
    public bool IsDarkTheme { get; set; } = false;
    public string ThemeMode { get; set; } = "System";
    public string LanguageMode { get; set; } = "System";
    public bool RememberSettings { get; set; } = true;
    public bool CheckForUpdates { get; set; } = true;

    [JsonIgnore]
    public bool LoadedFromFile { get; set; }

    public static AppSettings Load()
    {
        try
        {
            if (File.Exists(SettingsPath))
            {
                var json = File.ReadAllText(SettingsPath);
                var loaded = JsonSerializer.Deserialize<AppSettings>(json) ?? new AppSettings();
                loaded.LoadedFromFile = true;

                if (!loaded.RememberSettings)
                {
                    // Return defaults but preserve RememberSettings. Theme and language resolve from Windows.
                    var defaults = new AppSettings();
                    defaults.RememberSettings = false;
                    defaults.LoadedFromFile = true;
                    return defaults;
                }

                using var document = JsonDocument.Parse(json);
                loaded.ThemeMode = NormalizeThemeMode(loaded.ThemeMode);
                if (!document.RootElement.TryGetProperty(nameof(ThemeMode), out _))
                    loaded.ThemeMode = loaded.IsDarkTheme ? "Dark" : "Light";
                loaded.LanguageMode = NormalizeLanguageMode(loaded.LanguageMode);
                return loaded;
            }
        }
        catch
        {
            // Ignore corrupted settings
        }
        return new AppSettings { LoadedFromFile = false };
    }

    public void Save()
    {
        try
        {
            var json = JsonSerializer.Serialize(this, new JsonSerializerOptions { WriteIndented = true });
            File.WriteAllText(SettingsPath, json);
        }
        catch
        {
            // Best effort
        }
    }

    /// <summary>Reloads settings from disk, bypassing the RememberSettings guard.</summary>
    public static AppSettings Reload()
    {
        try
        {
            if (File.Exists(SettingsPath))
            {
                var json = File.ReadAllText(SettingsPath);
                var loaded = JsonSerializer.Deserialize<AppSettings>(json) ?? new AppSettings();
                loaded.LoadedFromFile = true;
                using var document = JsonDocument.Parse(json);
                loaded.ThemeMode = NormalizeThemeMode(loaded.ThemeMode);
                if (!document.RootElement.TryGetProperty(nameof(ThemeMode), out _))
                    loaded.ThemeMode = loaded.IsDarkTheme ? "Dark" : "Light";
                loaded.LanguageMode = NormalizeLanguageMode(loaded.LanguageMode);
                return loaded;
            }
        }
        catch { }
        return new AppSettings { LoadedFromFile = false };
    }

    public static string ResolveSystemLanguageMode()
    {
        var culture = CultureInfo.CurrentUICulture;
        var name = culture.Name;
        var parentName = culture.Parent?.Name ?? "";

        if (name.Equals("zh-CN", StringComparison.OrdinalIgnoreCase) ||
            name.Equals("zh-SG", StringComparison.OrdinalIgnoreCase) ||
            name.StartsWith("zh-Hans", StringComparison.OrdinalIgnoreCase) ||
            parentName.Equals("zh-Hans", StringComparison.OrdinalIgnoreCase))
        {
            return "zh-CN";
        }

        return "en-US";
    }

    public static string NormalizeThemeMode(string? value)
    {
        return value switch
        {
            "Light" => "Light",
            "Dark" => "Dark",
            _ => "System"
        };
    }

    public static string NormalizeLanguageMode(string? value)
    {
        return value switch
        {
            "en-US" => "en-US",
            "zh-CN" => "zh-CN",
            _ => "System"
        };
    }
}
