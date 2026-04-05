using System.Collections.Generic;
using System.Windows.Media;

namespace WinRarKeygenGui.Themes;

/// <summary>
/// Defines all custom brush colors for a theme.
/// To add a new theme, create a new static ThemeColorSet instance.
/// </summary>
public record ThemeColorSet(
    Color SettingsCardBg,
    Color SettingsDividerBrush,
    Color SegmentedControlBg,
    Color SegmentedActiveBg,
    Color SegmentedHoverBg,
    Color InputBg,
    Color InputBorderBrush,
    Color InputBottomBorderBrush,
    Color SurfaceBrush,
    Color SurfaceHoverBrush,
    Color AccentBrush,
    Color AccentHoverBrush,
    Color OutputBoxBg,
    Color OutputBoxBorder,
    Color WarningForeground,
    Color WarningPopupBg,
    Color WarningPopupBorder
)
{
    /// <summary>Returns all brush key-color pairs for applying to ResourceDictionary.</summary>
    public IEnumerable<(string Key, Color Color)> GetAll()
    {
        yield return (nameof(SettingsCardBg), SettingsCardBg);
        yield return (nameof(SettingsDividerBrush), SettingsDividerBrush);
        yield return (nameof(SegmentedControlBg), SegmentedControlBg);
        yield return (nameof(SegmentedActiveBg), SegmentedActiveBg);
        yield return (nameof(SegmentedHoverBg), SegmentedHoverBg);
        yield return (nameof(InputBg), InputBg);
        yield return (nameof(InputBorderBrush), InputBorderBrush);
        yield return (nameof(InputBottomBorderBrush), InputBottomBorderBrush);
        yield return (nameof(SurfaceBrush), SurfaceBrush);
        yield return (nameof(SurfaceHoverBrush), SurfaceHoverBrush);
        yield return (nameof(AccentBrush), AccentBrush);
        yield return (nameof(AccentHoverBrush), AccentHoverBrush);
        yield return (nameof(OutputBoxBg), OutputBoxBg);
        yield return (nameof(OutputBoxBorder), OutputBoxBorder);
        yield return (nameof(WarningForeground), WarningForeground);
        yield return (nameof(WarningPopupBg), WarningPopupBg);
        yield return (nameof(WarningPopupBorder), WarningPopupBorder);
    }
}

public static class ThemePresets
{
    public static ThemeColorSet Light { get; } = new(
        SettingsCardBg:        Color.FromArgb(0x08, 0x00, 0x00, 0x00),  // rgba(0,0,0,0.03)
        SettingsDividerBrush:  Color.FromArgb(0x0D, 0x00, 0x00, 0x00),  // rgba(0,0,0,0.05)
        SegmentedControlBg:    Color.FromArgb(0x0A, 0x00, 0x00, 0x00),  // rgba(0,0,0,0.04)
        SegmentedActiveBg:     Colors.White,
        SegmentedHoverBg:      Color.FromArgb(0x0A, 0x00, 0x00, 0x00),  // rgba(0,0,0,0.04)
        InputBg:               Color.FromArgb(0x8C, 0xFF, 0xFF, 0xFF),  // rgba(255,255,255,0.55)
        InputBorderBrush:      Color.FromArgb(0x14, 0x00, 0x00, 0x00),  // rgba(0,0,0,0.08)
        InputBottomBorderBrush:Color.FromArgb(0x1A, 0x00, 0x00, 0x00),  // rgba(0,0,0,0.1)
        SurfaceBrush:          Color.FromArgb(0xA6, 0xFF, 0xFF, 0xFF),  // rgba(255,255,255,0.65)
        SurfaceHoverBrush:     Color.FromArgb(0xD9, 0xFF, 0xFF, 0xFF),  // rgba(255,255,255,0.85)
        AccentBrush:           Color.FromRgb(0xC8, 0x66, 0x1E),        // #C8661E
        AccentHoverBrush:      Color.FromRgb(0xB5, 0x5B, 0x18),        // #B55B18
        OutputBoxBg:           Color.FromArgb(0xB3, 0xF9, 0xF9, 0xF9), // rgba(249,249,249,0.7)
        OutputBoxBorder:       Color.FromArgb(0x0F, 0x00, 0x00, 0x00),
        WarningForeground:    Color.FromRgb(0xB8, 0x86, 0x0B),         // #B8860B dark goldenrod
        WarningPopupBg:       Color.FromArgb(0xFF, 0xFF, 0xF8, 0xE1),  // #FFF8E1 warm cream
        WarningPopupBorder:   Color.FromArgb(0x40, 0xB8, 0x86, 0x0B)   // semi-transparent goldenrod
    );

    public static ThemeColorSet Dark { get; } = new(
        SettingsCardBg:        Color.FromRgb(0x16, 0x16, 0x16),         // #161616
        SettingsDividerBrush:  Color.FromArgb(0x0F, 0xFF, 0xFF, 0xFF),  // rgba(255,255,255,0.06)
        SegmentedControlBg:    Color.FromArgb(0x18, 0xFF, 0xFF, 0xFF),  // rgba(255,255,255,0.09)
        SegmentedActiveBg:     Color.FromArgb(0x1F, 0xFF, 0xFF, 0xFF),  // rgba(255,255,255,0.12)
        SegmentedHoverBg:      Color.FromArgb(0x14, 0xFF, 0xFF, 0xFF),  // rgba(255,255,255,0.08)
        InputBg:               Color.FromArgb(0x20, 0xFF, 0xFF, 0xFF),  // rgba(255,255,255,0.12)
        InputBorderBrush:      Color.FromArgb(0x1A, 0xFF, 0xFF, 0xFF),  // rgba(255,255,255,0.10)
        InputBottomBorderBrush:Color.FromArgb(0x14, 0xFF, 0xFF, 0xFF),
        SurfaceBrush:          Color.FromArgb(0xCC, 0x2A, 0x2A, 0x2A),  // rgba(42,42,42,0.8)
        SurfaceHoverBrush:     Color.FromArgb(0xCC, 0x3C, 0x3C, 0x3C),  // rgba(60,60,60,0.8)
        AccentBrush:           Color.FromRgb(0xE7, 0x7C, 0x35),        // #E77C35
        AccentHoverBrush:      Color.FromRgb(0xF0, 0x8A, 0x42),        // slightly brighter
        OutputBoxBg:           Color.FromArgb(0x33, 0x00, 0x00, 0x00),  // rgba(0,0,0,0.2)
        OutputBoxBorder:       Color.FromArgb(0x0F, 0xFF, 0xFF, 0xFF),
        WarningForeground:    Color.FromRgb(0xE8, 0xA7, 0x30),         // #E8A730 lighter amber for dark bg
        WarningPopupBg:       Color.FromArgb(0xFF, 0x33, 0x2B, 0x00),  // #332B00 dark warm brown
        WarningPopupBorder:   Color.FromArgb(0x50, 0xE8, 0xA7, 0x30)   // semi-transparent amber
    );
}
