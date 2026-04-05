<p align="center">
 <img width="100px" src="Assets/icon.png" align="center" alt="WinRAR Keygen GUI" />
 <h2 align="center">WinRAR Keygen GUI</h2>
 <p align="center">Principle of WinRAR key generation</p>
</p>
<p align="center">
  <a href="https://github.com/bitcookies/winrar-keygen/releases"><img src="https://img.shields.io/github/v/release/bitcookies/winrar-keygen?label=version" /></a>
  <a href="https://github.com/bitcookies/winrar-keygen/issues"><img alt="Issues" src="https://img.shields.io/github/issues/bitcookies/winrar-keygen?color=F48D73" /></a>
  <img src="https://img.shields.io/badge/.NET-8.0-512BD4?logo=dotnet" />
  <img src="https://img.shields.io/badge/WPF_UI-Fluent_Design-0078D4" />
  <a href="https://github.com/bitcookies/winrar-keygen/blob/master/LICENSE"><img alt="License" src="https://img.shields.io/github/license/bitcookies/winrar-keygen.svg" /></a>
</p>
<p align="center">
  <a href="README.md">English</a> | <a href="README.zh-CN.md">简体中文</a>
</p>


## 1. Introduction

WinRAR Keygen GUI is a graphical companion for the [winrar-keygen](https://github.com/bitcookies/winrar-keygen) CLI tool. It provides a modern Windows desktop interface built with .NET 8 WPF and Fluent Design (WPF UI), allowing you to generate WinRAR license files without using the command line.

For the key generation algorithm, see [How does it work?](https://github.com/bitcookies/winrar-keygen/blob/master/README.HOW_DOES_IT_WORK.md)

![Screenshot](assets/gui-light.png#gh-light-mode-only)
![Screenshot](assets/gui-dark.png#gh-dark-mode-only)

## 2. Download

Go to the [Releases](https://github.com/bitcookies/winrar-keygen/releases) page and download the variant that matches your system.

### Build Variants

| Variant | Architecture | .NET Runtime Required | Size |
| ------- | ------------ | --------------------- | ---- |
| **x64** | AMD64 (most Windows PCs) | No (self-contained) | ~75 MB |
| **x64-dotnet** | AMD64 | Yes ([.NET 8 Desktop Runtime](https://dotnet.microsoft.com/download/dotnet/8.0)) | ~6 MB |
| **ARM64** | ARM64 (Surface Pro X, Snapdragon laptops) | No (self-contained) | ~71 MB |
| **ARM64-dotnet** | ARM64 | Yes ([.NET 8 Desktop Runtime](https://dotnet.microsoft.com/download/dotnet/8.0)) | ~6 MB |

> **Which one should I download?**
> - Most users: download **x64** -- it works out of the box on any 64-bit Windows PC.
> - If you already have .NET 8 Desktop Runtime installed, download **x64-dotnet** for a smaller file.
> - For ARM-based Windows devices, download **ARM64** or **ARM64-dotnet**.

The architecture label is displayed in the bottom-right corner of the GUI (e.g. `x64`, `ARM64 (.NET)`).

## 3. Features

### Encoding

Supports three encoding types for the license file:

| Encoding | Description |
| -------- | ----------- |
| **UTF-8** (default) | Supports all Unicode characters. Automatically adds `utf8:` prefix when non-ASCII characters are present. |
| **ASCII** | Only full ASCII characters (0x20--0x7E). Non-ASCII input will trigger a warning. |
| **ANSI** | Windows locale-dependent encoding (e.g. Windows-1252). May produce garbled text on other systems. |

### Activate WinRAR

When enabled, the generated key is written directly to `%APPDATA%\WinRAR\rarreg.key`, activating WinRAR without manual file copying. When disabled, the key is saved to a custom output path.

### Settings

| Setting | Description |
| ------- | ----------- |
| **Remember Settings** | Persist all preferences between sessions. When disabled, settings reset to defaults on next launch. |
| **Autofill License Name** | Pre-fills "Single PC usage license" as the default license name. |
| **Back Up Existing Key** | Creates a timestamped backup of `rarreg.key` before overwriting. |
| **Check for Updates** | Automatically checks GitHub for new releases on startup. A red dot appears on the version number when an update is available. |

### Other

- **Light / Dark theme** -- follows system theme on startup; toggle manually via the moon/sun button.
- **Version check** -- click the version number to manually check for updates or open the releases page.

## 4. Build from Source

### Prerequisites

- [.NET 8 SDK](https://dotnet.microsoft.com/download/dotnet/8.0) or later
- Windows 10 / 11

### Build

```bash
dotnet restore
dotnet build
dotnet run
```

### Publish All Variants

Use the included build script to generate all 4 variants at once:

```powershell
powershell -ExecutionPolicy Bypass -File build.ps1
```

Output is placed in the `publish/` directory:

```
publish/
  x64/winrar-keygen-gui.exe          (~75 MB, self-contained)
  x64-dotnet/winrar-keygen-gui.exe   (~6 MB, requires .NET 8)
  ARM64/winrar-keygen-gui.exe        (~71 MB, self-contained)
  ARM64-dotnet/winrar-keygen-gui.exe (~6 MB, requires .NET 8)
```

## 5. License

The code is available under the [MIT license](https://github.com/bitcookies/winrar-keygen/blob/master/LICENSE)
