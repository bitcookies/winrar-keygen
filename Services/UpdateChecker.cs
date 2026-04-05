using System;
using System.Net.Http;
using System.Text.Json;
using System.Threading.Tasks;

namespace WinRarKeygenGui.Services;

/// <summary>
/// Checks GitHub releases for newer versions.
/// </summary>
public static class UpdateChecker
{
    /// <summary>
    /// Checks if a newer version is available on GitHub.
    /// Returns (hasUpdate, latestVersion). Swallows all exceptions.
    /// </summary>
    public static async Task<(bool HasUpdate, string? LatestVersion)> CheckForUpdateAsync(string currentVersion)
    {
        try
        {
            using var client = new HttpClient();
            client.Timeout = TimeSpan.FromSeconds(5);
            client.DefaultRequestHeaders.UserAgent.ParseAdd("WinRarKeygenGUI");

            var response = await client.GetAsync(AppEnvironment.LatestReleaseApiUrl);
            response.EnsureSuccessStatusCode();

            var json = await response.Content.ReadAsStringAsync();
            using var doc = JsonDocument.Parse(json);
            var tagName = doc.RootElement.GetProperty("tag_name").GetString();

            if (string.IsNullOrEmpty(tagName))
                return (false, null);

            // Strip leading 'v' for comparison
            var remoteStr = tagName.TrimStart('v');
            var localStr = currentVersion.TrimStart('v');

            if (Version.TryParse(remoteStr, out var remoteVer) &&
                Version.TryParse(localStr, out var localVer))
            {
                return (remoteVer > localVer, tagName);
            }
        }
        catch
        {
            // Best effort; silently ignore network or parse errors.
        }

        return (false, null);
    }
}
