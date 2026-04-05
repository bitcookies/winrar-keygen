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


## 1. 简介

WinRAR Keygen GUI 是 [winrar-keygen](https://github.com/bitcookies/winrar-keygen) 命令行工具的图形界面版本。基于 .NET 8 WPF 和 Fluent Design (WPF UI) 构建，提供现代化的 Windows 桌面体验，无需使用命令行即可生成 WinRAR 授权文件。

密钥生成算法详见 [原理说明](https://github.com/bitcookies/winrar-keygen/blob/master/README.HOW_DOES_IT_WORK.zh-CN.md)。

![截图](assets/gui-light.png#gh-light-mode-only)
![截图](assets/gui-dark.png#gh-dark-mode-only)

## 2. 下载

前往 [Releases](https://github.com/bitcookies/winrar-keygen/releases) 页面下载适合你系统的版本。

### 版本区别

| 版本 | 架构 | 需要 .NET 运行时 | 体积 |
| ---- | ---- | --------------- | ---- |
| **x64** | AMD64（大多数 Windows 电脑） | 不需要（自包含） | ~75 MB |
| **x64-dotnet** | AMD64 | 需要（[.NET 8 Desktop Runtime](https://dotnet.microsoft.com/download/dotnet/8.0)） | ~6 MB |
| **ARM64** | ARM64（Surface Pro X、骁龙笔记本等） | 不需要（自包含） | ~71 MB |
| **ARM64-dotnet** | ARM64 | 需要（[.NET 8 Desktop Runtime](https://dotnet.microsoft.com/download/dotnet/8.0)） | ~6 MB |

> **应该下载哪个？**
> - 大多数用户：下载 **x64** -- 双击即用，无需安装任何依赖。
> - 如果已安装 .NET 8 Desktop Runtime，可以下载 **x64-dotnet**，体积更小。
> - ARM 架构的 Windows 设备请下载 **ARM64** 或 **ARM64-dotnet**。

GUI 右下角会显示当前版本的架构标签（如 `x64`、`ARM64 (.NET)`）。

## 3. 功能

### 编码

支持三种编码类型：

| 编码 | 说明 |
| ---- | ---- |
| **UTF-8**（默认） | 支持所有 Unicode 字符。包含非 ASCII 字符时自动添加 `utf8:` 前缀。 |
| **ASCII** | 仅支持 ASCII 字符（0x20--0x7E）。输入非 ASCII 字符时会弹出警告。 |
| **ANSI** | Windows 区域相关编码（如 Windows-1252）。在其他系统上可能出现乱码。 |

### 激活 WinRAR

开启后，生成的密钥会直接写入 `%APPDATA%\WinRAR\rarreg.key`，自动激活 WinRAR，无需手动复制文件。关闭后，密钥保存到自定义输出路径。

### 设置

| 设置 | 说明 |
| ---- | ---- |
| **Remember Settings** | 记住所有设置。关闭后下次启动恢复默认值。 |
| **Autofill License Name** | 自动填充 "Single PC usage license" 作为默认许可名称。 |
| **Back Up Existing Key** | 覆盖前自动备份已有的 `rarreg.key`（带时间戳）。 |
| **Check for Updates** | 启动时自动检查 GitHub 上的新版本。有更新时版本号旁会出现红点。 |

### 其他

- **亮色 / 暗色主题** -- 启动时跟随系统主题，也可通过底部按钮手动切换。
- **版本检查** -- 点击版本号可手动检查更新或打开发布页面。

## 4. 从源码构建

### 前置要求

- [.NET 8 SDK](https://dotnet.microsoft.com/download/dotnet/8.0) 或更高版本
- Windows 10 / 11

### 编译

```bash
dotnet restore
dotnet build
dotnet run
```

### 发布全部版本

使用构建脚本一次生成全部 4 个变体：

```powershell
powershell -ExecutionPolicy Bypass -File build.ps1
```

输出到 `publish/` 目录：

```
publish/
  x64/winrar-keygen-gui.exe          (~75 MB, 自包含)
  x64-dotnet/winrar-keygen-gui.exe   (~6 MB, 需要 .NET 8)
  ARM64/winrar-keygen-gui.exe        (~71 MB, 自包含)
  ARM64-dotnet/winrar-keygen-gui.exe (~6 MB, 需要 .NET 8)
```

## 5. 许可

本项目使用 [MIT License](LICENSE)。
