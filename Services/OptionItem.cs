using CommunityToolkit.Mvvm.ComponentModel;

namespace WinRarKeygenGui.Services;

public sealed partial class OptionItem(string value, string displayName) : ObservableObject
{
    public string Value { get; } = value;

    [ObservableProperty]
    private string _displayName = displayName;
}
