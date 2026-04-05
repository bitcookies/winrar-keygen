using System;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using WinRarKeygenGui.Core;
using WinRarKeygenGui.Services;

namespace WinRarKeygenGui.ViewModels;

public partial class MainViewModel : ObservableObject
{
    private readonly AppSettings _settings;

    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(GenerateCommand))]
    private string _username = "";

    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(GenerateCommand))]
    private string _licenseName = "";

    [ObservableProperty]
    private int _selectedEncoding = 0;

    [ObservableProperty]
    private string _outputFilePath = "rarreg.key";

    [ObservableProperty]
    private bool _activateWinRar = true;

    [ObservableProperty]
    private string _outputText = "";

    [ObservableProperty]
    private bool _hasOutput = false;

    [ObservableProperty]
    private bool _isGenerating = false;

    [ObservableProperty]
    private string _statusMessage = "";

    [ObservableProperty]
    private string _statusFilePath = "";

    [ObservableProperty]
    private bool _copySuccess = false;

    [ObservableProperty]
    private bool _autoFillLicenseName = true;

    [ObservableProperty]
    private bool _backupExistingKey = true;

    [ObservableProperty]
    private bool _rememberSettings = true;

    [ObservableProperty]
    private bool _checkForUpdates = true;

    [ObservableProperty]
    private bool _hasUpdate = false;

    [ObservableProperty]
    private bool _isCheckingUpdate = false;

    [ObservableProperty]
    private string _versionDisplayText = CurrentVersion;

    [ObservableProperty]
    private string _usernameWarning = "";

    [ObservableProperty]
    private string _licenseNameWarning = "";

    [ObservableProperty]
    private bool _usernameWarningVisible;

    [ObservableProperty]
    private bool _licenseNameWarningVisible;

    private CancellationTokenSource? _usernameWarnCts;
    private CancellationTokenSource? _licenseWarnCts;
    private bool _suppressSave;

    /// <summary>Raised after successful key generation so the view can flip to the result panel.</summary>
    public event Action? RequestShowResult;

    public static string CurrentVersion { get; } =
        $"v{Assembly.GetExecutingAssembly().GetName().Version!.ToString(3)}";
    public string VersionText => CurrentVersion;

    public static string ArchLabel { get; } = BuildArchLabel();

    private static string BuildArchLabel()
    {
        var arch = RuntimeInformation.ProcessArchitecture switch
        {
            Architecture.X64 => "x64",
            Architecture.X86 => "x86",
            Architecture.Arm64 => "ARM64",
            _ => RuntimeInformation.ProcessArchitecture.ToString()
        };
#if SELF_CONTAINED
        return arch;
#else
        return $"{arch} (.NET)";
#endif
    }

    public MainViewModel()
    {
        _settings = AppSettings.Load();

        // Restore persisted state
        _username = _settings.Username;
        _selectedEncoding = _settings.SelectedEncoding;
        _outputFilePath = _settings.OutputFilePath;
        _activateWinRar = _settings.ActivateWinRar;
        _autoFillLicenseName = _settings.AutoFillLicenseName;
        _backupExistingKey = _settings.BackupExistingKey;
        _rememberSettings = _settings.RememberSettings;
        _checkForUpdates = _settings.CheckForUpdates;
        // Restore license name based on autofill setting
        _licenseName = _autoFillLicenseName
            ? (_settings.LicenseName.Length > 0 ? _settings.LicenseName : "Single PC usage license")
            : _settings.LicenseName;
    }

    /// <summary>Exposes the loaded settings so the view can read persisted values.</summary>
    public AppSettings Settings => _settings;

    /// <summary>Persists current state to the settings file.</summary>
    public void SaveSettings(bool? isDark = null)
    {
        _settings.Username = Username;
        _settings.LicenseName = LicenseName;
        _settings.SelectedEncoding = SelectedEncoding;
        _settings.OutputFilePath = OutputFilePath;
        _settings.ActivateWinRar = ActivateWinRar;
        _settings.AutoFillLicenseName = AutoFillLicenseName;
        _settings.BackupExistingKey = BackupExistingKey;
        _settings.RememberSettings = RememberSettings;
        _settings.CheckForUpdates = CheckForUpdates;
        if (isDark.HasValue)
            _settings.IsDarkTheme = isDark.Value;
        _settings.Save();
    }

    partial void OnAutoFillLicenseNameChanged(bool value)
    {
        if (value && string.IsNullOrWhiteSpace(LicenseName))
            LicenseName = "Single PC usage license";
        else if (!value)
            LicenseName = "";
        if (!_suppressSave) SaveSettings();
    }

    partial void OnBackupExistingKeyChanged(bool value)
    {
        if (!_suppressSave) SaveSettings();
    }

    partial void OnRememberSettingsChanged(bool value)
    {
        if (!value)
        {
            // Reset UI to defaults but keep saved values intact on disk
            _suppressSave = true;
            AutoFillLicenseName = true;
            BackupExistingKey = true;
            CheckForUpdates = true;
            _suppressSave = false;

            // Only persist the RememberSettings flag
            _settings.RememberSettings = false;
            _settings.Save();
        }
        else
        {
            // Restore previously saved settings from disk
            var saved = AppSettings.Reload();
            _suppressSave = true;
            Username = saved.Username;
            LicenseName = saved.LicenseName.Length > 0 ? saved.LicenseName : "Single PC usage license";
            SelectedEncoding = saved.SelectedEncoding;
            OutputFilePath = saved.OutputFilePath;
            ActivateWinRar = saved.ActivateWinRar;
            AutoFillLicenseName = saved.AutoFillLicenseName;
            BackupExistingKey = saved.BackupExistingKey;
            CheckForUpdates = saved.CheckForUpdates;
            _suppressSave = false;
            SaveSettings();
        }
    }

    partial void OnCheckForUpdatesChanged(bool value)
    {
        if (!value)
        {
            HasUpdate = false;
        }
        else
        {
            _ = RunUpdateCheckAsync();
        }
        if (!_suppressSave) SaveSettings();
    }

    partial void OnSelectedEncodingChanged(int value)
    {
        if (!_suppressSave) SaveSettings();
        UpdateEncodingWarnings();
    }

    partial void OnActivateWinRarChanged(bool value)
    {
        if (!_suppressSave) SaveSettings();
    }

    partial void OnUsernameChanged(string value) => UpdateEncodingWarnings();
    partial void OnLicenseNameChanged(string value) => UpdateEncodingWarnings();

    private static bool HasNonAscii(string s) => s.Any(c => c > 127);

    /// <summary>Updates the encoding warnings.</summary>
    private void UpdateEncodingWarnings()
    {
        if (SelectedEncoding == 1) // ASCII
        {
            const string asciiWarning = "Contains non-ASCII characters. Name may appear garbled in the license.";
            UsernameWarning = HasNonAscii(Username) ? asciiWarning : "";
            LicenseNameWarning = HasNonAscii(LicenseName) ? asciiWarning : "";
        }
        else if (SelectedEncoding == 2) // ANSI
        {
            const string ansiWarning = "Contains non-ASCII characters. ANSI encoding is locale-dependent and may produce garbled text on other systems.";
            UsernameWarning = HasNonAscii(Username) ? ansiWarning : "";
            LicenseNameWarning = HasNonAscii(LicenseName) ? ansiWarning : "";
        }
        else
        {
            UsernameWarning = "";
            LicenseNameWarning = "";
        }

        ScheduleUsernameWarningHide();
        ScheduleLicenseWarningHide();
    }

    private async void ScheduleUsernameWarningHide()
    {
        _usernameWarnCts?.Cancel();
        if (string.IsNullOrEmpty(UsernameWarning)) { UsernameWarningVisible = false; return; }
        UsernameWarningVisible = true;
        var cts = new CancellationTokenSource();
        _usernameWarnCts = cts;
        try { await Task.Delay(5000, cts.Token); UsernameWarningVisible = false; }
        catch (TaskCanceledException) { }
    }

    private async void ScheduleLicenseWarningHide()
    {
        _licenseWarnCts?.Cancel();
        if (string.IsNullOrEmpty(LicenseNameWarning)) { LicenseNameWarningVisible = false; return; }
        LicenseNameWarningVisible = true;
        var cts = new CancellationTokenSource();
        _licenseWarnCts = cts;
        try { await Task.Delay(5000, cts.Token); LicenseNameWarningVisible = false; }
        catch (TaskCanceledException) { }
    }

    public void HideWarnings()
    {
        _usernameWarnCts?.Cancel();
        _licenseWarnCts?.Cancel();
        UsernameWarningVisible = false;
        LicenseNameWarningVisible = false;
    }

    private bool CanGenerate() => !string.IsNullOrWhiteSpace(Username) && !string.IsNullOrWhiteSpace(LicenseName) && !IsGenerating;

    [RelayCommand(CanExecute = nameof(CanGenerate))]
    private async Task GenerateAsync()
    {
        IsGenerating = true;
        StatusMessage = "";
        StatusFilePath = "";
        HasOutput = false;

        try
        {
            var encoding = SelectedEncoding switch
            {
                0 => KeyEncoding.UTF8,
                1 => KeyEncoding.ASCII,
                2 => KeyEncoding.ANSI,
                _ => KeyEncoding.UTF8
            };

            var (user, license, displayUser, displayLicense) =
                WinRarKeygenCore.ProcessEncoding(Username.Trim(), LicenseName.Trim(), encoding);

            // Run keygen on background thread
            var info = await Task.Run(() => WinRarKeygenCore.GenerateRegisterInfo(user, license));

            string displayText = WinRarKeygenCore.BuildDisplayText(info, displayUser, displayLicense);
            OutputText = displayText;
            HasOutput = true;

            // Build raw binary content (like CLI's fwrite "wb" mode)
            byte[] fileBytes = WinRarKeygenCore.BuildRegFileBytes(info, encoding);
            string encName = encoding switch
            {
                KeyEncoding.UTF8 => "UTF-8",
                KeyEncoding.ASCII => "ASCII",
                KeyEncoding.ANSI => "ANSI",
                _ => "UTF-8"
            };

            if (!ActivateWinRar)
            {
                string filePath = OutputFilePath;
                if (!Path.IsPathRooted(filePath))
                    filePath = Path.Combine(AppEnvironment.DefaultOutputDirectory, filePath);

                await File.WriteAllBytesAsync(filePath, fileBytes);
                StatusMessage = $"Saved ({encName})";
                StatusFilePath = filePath;
            }
            else
            {
                // Activate: write to %APPDATA%\WinRAR\rarreg.key
                string appData = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
                string winrarDir = Path.Combine(appData, "WinRAR");
                Directory.CreateDirectory(winrarDir);
                string activatePath = Path.Combine(winrarDir, "rarreg.key");

                // Backup existing key if enabled
                if (BackupExistingKey && File.Exists(activatePath))
                {
                    string timestamp = DateTime.Now.ToString("yyyyMMdd_HHmmss");
                    string backupPath = Path.Combine(winrarDir, $"rarreg.key.{timestamp}.bak");
                    File.Copy(activatePath, backupPath, overwrite: true);
                }

                await File.WriteAllBytesAsync(activatePath, fileBytes);
                StatusMessage = "Activated";
                StatusFilePath = activatePath;
            }

            // Persist after successful generation
            SaveSettings();

            // Notify view to flip to result panel
            RequestShowResult?.Invoke();
        }
        catch (Exception ex)
        {
            StatusMessage = $"Error: {ex.Message}";
            HasOutput = false;
        }
        finally
        {
            IsGenerating = false;
        }
    }

    [RelayCommand]
    private async Task CopyOutputAsync()
    {
        if (string.IsNullOrEmpty(OutputText)) return;

        try
        {
            Clipboard.SetText(OutputText);
            CopySuccess = true;
            await Task.Delay(2000);
            CopySuccess = false;
        }
        catch
        {
            // Clipboard access can fail
        }
    }

    /// <summary>Runs a background update check (safe to fire and forget).</summary>
    public async Task RunUpdateCheckAsync()
    {
        if (!CheckForUpdates || IsCheckingUpdate) return;
        IsCheckingUpdate = true;
        try
        {
            var (hasUpdate, _) = await UpdateChecker.CheckForUpdateAsync(CurrentVersion);
            HasUpdate = hasUpdate;
        }
        finally
        {
            IsCheckingUpdate = false;
        }
    }

    /// <summary>Manual update check triggered by clicking the version text.</summary>
    public async Task ManualCheckForUpdateAsync()
    {
        if (IsCheckingUpdate) return;
        IsCheckingUpdate = true;
        VersionDisplayText = "Checking for updates";
        try
        {
            var (hasUpdate, _) = await UpdateChecker.CheckForUpdateAsync(CurrentVersion);
            HasUpdate = hasUpdate;
            if (!hasUpdate)
            {
                VersionDisplayText = "You have the latest version";
                await Task.Delay(2500);
                VersionDisplayText = CurrentVersion;
            }
            else
            {
                VersionDisplayText = CurrentVersion;
            }
        }
        catch
        {
            VersionDisplayText = CurrentVersion;
        }
        finally
        {
            IsCheckingUpdate = false;
        }
    }

    [RelayCommand]
    private void BrowseOutputFile()
    {
        var dialog = new Microsoft.Win32.SaveFileDialog
        {
            FileName = "rarreg.key",
            DefaultExt = ".key",
            Filter = "Key files (*.key)|*.key|All files (*.*)|*.*",
            InitialDirectory = AppEnvironment.DefaultOutputDirectory
        };

        if (dialog.ShowDialog() == true)
        {
            OutputFilePath = dialog.FileName;
        }
    }

}
