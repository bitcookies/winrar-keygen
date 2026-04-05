using System.Windows;
using System.Windows.Media;
using Wpf.Ui.Appearance;
using WinRarKeygenGui.Themes;

namespace WinRarKeygenGui;

public partial class App : Application
{
    protected override void OnStartup(StartupEventArgs e)
    {
        base.OnStartup(e);
        ApplicationThemeManager.ApplySystemTheme();

        var isDark = ApplicationThemeManager.GetAppTheme() == ApplicationTheme.Dark;
        UpdateCustomBrushes(isDark);
    }

    /// <summary>
    /// Apply a theme color set to all custom brushes in the resource dictionary.
    /// </summary>
    public static void ApplyTheme(ThemeColorSet theme)
    {
        var res = Current.Resources;
        foreach (var (key, color) in theme.GetAll())
            res[key] = new SolidColorBrush(color);
    }

    /// <summary>
    /// Convenience method: select Light or Dark preset by boolean flag.
    /// </summary>
    public static void UpdateCustomBrushes(bool isDark)
    {
        ApplyTheme(isDark ? ThemePresets.Dark : ThemePresets.Light);
    }
}
