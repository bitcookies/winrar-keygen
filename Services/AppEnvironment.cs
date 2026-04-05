using System;
using System.IO;

namespace WinRarKeygenGui.Services;

public static class AppEnvironment
{
    public const string GitHubRepository = "bitcookies/winrar-keygen";

    public static string ReleasesUrl => $"https://github.com/{GitHubRepository}/releases";
    public static string LatestReleaseApiUrl => $"https://api.github.com/repos/{GitHubRepository}/releases/latest";

    public static string SettingsDirectory { get; } = BuildSettingsDirectory();
    public static string SettingsPath { get; } = Path.Combine(SettingsDirectory, "winrar-keygen-settings.json");
    public static string DefaultOutputDirectory { get; } = BuildDefaultOutputDirectory();

    private static string BuildSettingsDirectory()
    {
        var localAppData = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
        if (!string.IsNullOrWhiteSpace(localAppData))
            return Path.Combine(localAppData, "WinRarKeygenGui");

        return AppDomain.CurrentDomain.BaseDirectory;
    }

    private static string BuildDefaultOutputDirectory()
    {
        var documents = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
        if (!string.IsNullOrWhiteSpace(documents))
            return documents;

        return AppDomain.CurrentDomain.BaseDirectory;
    }
}
