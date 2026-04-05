using System;
using System.IO;
using System.Text.Json;

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
    public bool RememberSettings { get; set; } = true;
    public bool CheckForUpdates { get; set; } = true;

    public static AppSettings Load()
    {
        try
        {
            if (File.Exists(SettingsPath))
            {
                var json = File.ReadAllText(SettingsPath);
                var loaded = JsonSerializer.Deserialize<AppSettings>(json) ?? new AppSettings();

                if (!loaded.RememberSettings)
                {
                    // Return defaults but preserve RememberSettings and IsDarkTheme
                    var defaults = new AppSettings();
                    defaults.RememberSettings = false;
                    defaults.IsDarkTheme = loaded.IsDarkTheme;
                    return defaults;
                }

                return loaded;
            }
        }
        catch
        {
            // Ignore corrupted settings
        }
        return new AppSettings();
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
                return JsonSerializer.Deserialize<AppSettings>(json) ?? new AppSettings();
            }
        }
        catch { }
        return new AppSettings();
    }
}
