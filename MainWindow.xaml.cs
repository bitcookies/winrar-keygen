using System.ComponentModel;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using Wpf.Ui.Appearance;
using Wpf.Ui.Controls;
using WinRarKeygenGui.Services;
using WinRarKeygenGui.ViewModels;

namespace WinRarKeygenGui;

public partial class MainWindow : FluentWindow
{
    private static readonly Duration HalfFlip = new(TimeSpan.FromMilliseconds(180));
    private bool _isFlipping;
    private double _lockedHeight;

    public MainWindow()
    {
        InitializeComponent();
        Loaded += OnLoaded;
        Closing += OnClosing;
        LocationChanged += OnLocationChanged;

        if (DataContext is MainViewModel vm)
            vm.RequestShowResult += () => Dispatcher.Invoke(FlipToResult);
    }

    private void OnLoaded(object sender, RoutedEventArgs e)
    {
        if (DataContext is MainViewModel vm)
        {
            var targetTheme = vm.Settings.IsDarkTheme
                ? ApplicationTheme.Dark
                : ApplicationTheme.Light;

            ApplicationThemeManager.Apply(targetTheme);
            App.UpdateCustomBrushes(vm.Settings.IsDarkTheme);

            ThemeIcon.Symbol = vm.Settings.IsDarkTheme
                ? SymbolRegular.WeatherSunny24
                : SymbolRegular.WeatherMoon24;

            // Set initial encoding pill position (no animation)
            SetEncodingPillPosition(vm.SelectedEncoding);

            // Listen for encoding changes to animate the pill
            vm.PropertyChanged += (s, args) =>
            {
                if (args.PropertyName == nameof(MainViewModel.SelectedEncoding))
                    AnimateEncodingPill(vm.SelectedEncoding);
            };

            // Fire-and-forget background update check
            _ = vm.RunUpdateCheckAsync();
        }
    }

    private void SetEncodingPillPosition(int index)
    {
        if (EncodingPill.ActualWidth <= 0) return;
        EncodingPillTranslate.X = index * EncodingPill.ActualWidth;
    }

    private void AnimateEncodingPill(int index)
    {
        if (EncodingPill.ActualWidth <= 0) return;
        var targetX = index * EncodingPill.ActualWidth;
        var animation = new DoubleAnimation
        {
            To = targetX,
            Duration = TimeSpan.FromMilliseconds(200),
            EasingFunction = new CubicEase { EasingMode = EasingMode.EaseInOut }
        };
        EncodingPillTranslate.BeginAnimation(TranslateTransform.XProperty, animation);
    }

    private void OnLocationChanged(object? sender, EventArgs e)
    {
        // Force WPF Popups to reposition when window moves
        foreach (var popup in new[] { UsernameWarningPopup, LicenseWarningPopup })
        {
            if (popup.IsOpen)
            {
                var offset = popup.HorizontalOffset;
                popup.HorizontalOffset = offset + 1;
                popup.HorizontalOffset = offset;
            }
        }
    }

    private void OnClosing(object? sender, CancelEventArgs e)
    {
        if (DataContext is MainViewModel vm)
        {
            var isDark = ApplicationThemeManager.GetAppTheme() == ApplicationTheme.Dark;
            vm.SaveSettings(isDark);
        }
    }

    private void ThemeToggle_Click(object sender, RoutedEventArgs e)
    {
        var currentTheme = ApplicationThemeManager.GetAppTheme();
        var newTheme = currentTheme == ApplicationTheme.Dark
            ? ApplicationTheme.Light
            : ApplicationTheme.Dark;

        ApplicationThemeManager.Apply(newTheme);

        bool isDark = newTheme == ApplicationTheme.Dark;
        App.UpdateCustomBrushes(isDark);

        ThemeIcon.Symbol = isDark
            ? SymbolRegular.WeatherSunny24
            : SymbolRegular.WeatherMoon24;

        if (DataContext is MainViewModel vm)
            vm.SaveSettings(isDark);
    }

    private void VersionLink_MouseEnter(object sender, MouseEventArgs e)
    {
        VersionLink.Foreground = (Brush)FindResource("AccentBrush");
    }

    private void VersionLink_MouseLeave(object sender, MouseEventArgs e)
    {
        VersionLink.SetResourceReference(ForegroundProperty, "TextFillColorTertiaryBrush");
    }

    private async void VersionLink_Click(object sender, MouseButtonEventArgs e)
    {
        if (DataContext is MainViewModel vm)
        {
            if (vm.HasUpdate)
            {
                // Update available — open releases page
                Process.Start(new ProcessStartInfo
                {
                    FileName = AppEnvironment.ReleasesUrl,
                    UseShellExecute = true
                });
            }
            else
            {
                // No update known — trigger manual check
                await vm.ManualCheckForUpdateAsync();
            }
        }
    }

    private void WinRarPath_MouseEnter(object sender, MouseEventArgs e)
    {
        WinRarPathLink.Foreground = (Brush)FindResource("AccentBrush");
    }

    private void WinRarPath_MouseLeave(object sender, MouseEventArgs e)
    {
        WinRarPathLink.SetResourceReference(ForegroundProperty, "TextFillColorTertiaryBrush");
    }

    private void WinRarPath_Click(object sender, MouseButtonEventArgs e)
    {
        var appData = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
        var winrarDir = System.IO.Path.Combine(appData, "WinRAR");
        System.IO.Directory.CreateDirectory(winrarDir);
        Process.Start(new ProcessStartInfo
        {
            FileName = winrarDir,
            UseShellExecute = true
        });
    }

    private void StatusPath_MouseEnter(object sender, MouseEventArgs e)
    {
        StatusPathLink.Foreground = (Brush)FindResource("AccentBrush");
    }

    private void StatusPath_MouseLeave(object sender, MouseEventArgs e)
    {
        StatusPathLink.SetResourceReference(ForegroundProperty, "TextFillColorSecondaryBrush");
    }

    private void StatusPath_Click(object sender, MouseButtonEventArgs e)
    {
        if (DataContext is MainViewModel vm && !string.IsNullOrEmpty(vm.StatusFilePath))
        {
            var dir = System.IO.Path.GetDirectoryName(vm.StatusFilePath);
            if (dir != null && System.IO.Directory.Exists(dir))
            {
                Process.Start(new ProcessStartInfo
                {
                    FileName = dir,
                    UseShellExecute = true
                });
            }
        }
    }

    private void Settings_Click(object sender, RoutedEventArgs e)
    {
        FlipToBack();
    }

    private void BackToMain_Click(object sender, RoutedEventArgs e)
    {
        FlipToFront(BackPanel, BackScale);
    }

    private void ResultBackToMain_Click(object sender, RoutedEventArgs e)
    {
        FlipToFront(ResultPanel, ResultScale);
    }

    private void LockWindowHeight()
    {
        _lockedHeight = ActualHeight;
        SizeToContent = SizeToContent.Manual;
        Height = _lockedHeight;
    }

    private void UnlockWindowHeight()
    {
        SizeToContent = SizeToContent.Height;
    }

    private void FlipToBack()
    {
        FlipFromFront(BackPanel, BackScale);
    }

    private void FlipToResult()
    {
        FlipFromFront(ResultPanel, ResultScale, onExpanded: LaunchConfetti);
    }

    /// <summary>Flips away from the front panel to the specified target panel.</summary>
    private void FlipFromFront(Border targetPanel, ScaleTransform targetScale, Action? onExpanded = null)
    {
        if (_isFlipping) return;

        // Hide warning popups when leaving front panel
        if (DataContext is MainViewModel vm)
            vm.HideWarnings();
        _isFlipping = true;
        LockWindowHeight();

        var shrink = new DoubleAnimation(1, 0, HalfFlip)
        {
            EasingFunction = new CubicEase { EasingMode = EasingMode.EaseIn }
        };
        shrink.Completed += (_, _) =>
        {
            FrontPanel.Visibility = Visibility.Collapsed;
            targetPanel.Visibility = Visibility.Visible;

            var expand = new DoubleAnimation(0, 1, HalfFlip)
            {
                EasingFunction = new BackEase { EasingMode = EasingMode.EaseOut, Amplitude = 0.3 }
            };
            expand.Completed += (_, _) =>
            {
                _isFlipping = false;
                onExpanded?.Invoke();
            };
            targetScale.BeginAnimation(ScaleTransform.ScaleXProperty, expand);
        };
        FrontScale.BeginAnimation(ScaleTransform.ScaleXProperty, shrink);
    }

    private void LaunchConfetti()
    {
        const int count = 50;
        const double durationMs = 1600;
        var rng = new Random();
        var colors = new[]
        {
            Color.FromRgb(0xE5, 0x39, 0x35), // red
            Color.FromRgb(0xFB, 0x8C, 0x00), // orange
            Color.FromRgb(0xFF, 0xD6, 0x00), // yellow
            Color.FromRgb(0x43, 0xA0, 0x47), // green
            Color.FromRgb(0x1E, 0x88, 0xE5), // blue
            Color.FromRgb(0x8E, 0x24, 0xAA), // purple
            Color.FromRgb(0xE9, 0x1E, 0x63), // pink
            Color.FromRgb(0x00, 0xAC, 0xC1), // teal
        };

        double canvasW = ConfettiCanvas.ActualWidth > 0 ? ConfettiCanvas.ActualWidth : ActualWidth;
        double canvasH = ConfettiCanvas.ActualHeight > 0 ? ConfettiCanvas.ActualHeight : ActualHeight;

        int cleanupCounter = 0;

        for (int i = 0; i < count; i++)
        {
            var color = colors[rng.Next(colors.Length)];
            bool isCircle = rng.Next(2) == 0;

            FrameworkElement piece;
            if (isCircle)
            {
                piece = new Ellipse
                {
                    Width = rng.Next(4, 8),
                    Height = rng.Next(4, 8),
                    Fill = new SolidColorBrush(color),
                    IsHitTestVisible = false,
                    Opacity = 0.85
                };
            }
            else
            {
                piece = new Rectangle
                {
                    Width = rng.Next(5, 10),
                    Height = rng.Next(3, 7),
                    Fill = new SolidColorBrush(color),
                    RadiusX = 1, RadiusY = 1,
                    IsHitTestVisible = false,
                    Opacity = 0.85
                };
            }

            double startX = rng.NextDouble() * canvasW;
            double startY = -10 - rng.NextDouble() * 40;

            Canvas.SetLeft(piece, startX);
            Canvas.SetTop(piece, startY);
            piece.RenderTransformOrigin = new Point(0.5, 0.5);
            piece.RenderTransform = new RotateTransform(0);

            ConfettiCanvas.Children.Add(piece);

            var dur = new Duration(TimeSpan.FromMilliseconds(durationMs + rng.Next(-200, 300)));

            // Fall down
            double endY = canvasH + 20;
            var fallAnim = new DoubleAnimation(startY, endY, dur)
            {
                EasingFunction = new QuadraticEase { EasingMode = EasingMode.EaseIn }
            };

            // Horizontal drift
            double drift = startX + rng.NextDouble() * 80 - 40;
            var driftAnim = new DoubleAnimation(startX, drift, dur);

            // Rotate
            double endAngle = rng.Next(-360, 360);
            var rotateAnim = new DoubleAnimation(0, endAngle, dur);

            // Fade out in last 40%
            var fadeAnim = new DoubleAnimation(0.85, 0, dur)
            {
                BeginTime = TimeSpan.FromMilliseconds(durationMs * 0.55)
            };

            // Cleanup when fall completes
            fallAnim.Completed += (_, _) =>
            {
                ConfettiCanvas.Children.Remove(piece);
                cleanupCounter++;
                if (cleanupCounter >= count)
                    ConfettiCanvas.Children.Clear();
            };

            piece.BeginAnimation(Canvas.TopProperty, fallAnim);
            piece.BeginAnimation(Canvas.LeftProperty, driftAnim);
            ((RotateTransform)piece.RenderTransform).BeginAnimation(RotateTransform.AngleProperty, rotateAnim);
            piece.BeginAnimation(UIElement.OpacityProperty, fadeAnim);
        }
    }

    /// <summary>Flips back from the specified source panel to the front panel.</summary>
    private void FlipToFront(Border sourcePanel, ScaleTransform sourceScale)
    {
        if (_isFlipping) return;
        _isFlipping = true;
        LockWindowHeight();

        var shrink = new DoubleAnimation(1, 0, HalfFlip)
        {
            EasingFunction = new CubicEase { EasingMode = EasingMode.EaseIn }
        };
        shrink.Completed += (_, _) =>
        {
            sourcePanel.Visibility = Visibility.Collapsed;
            FrontPanel.Visibility = Visibility.Visible;

            var expand = new DoubleAnimation(0, 1, HalfFlip)
            {
                EasingFunction = new BackEase { EasingMode = EasingMode.EaseOut, Amplitude = 0.3 }
            };
            expand.Completed += (_, _) =>
            {
                _isFlipping = false;
                UnlockWindowHeight();
            };
            FrontScale.BeginAnimation(ScaleTransform.ScaleXProperty, expand);
        };
        sourceScale.BeginAnimation(ScaleTransform.ScaleXProperty, shrink);
    }
}
