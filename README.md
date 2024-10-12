<p align="center">
 <img width="100px" src="icon.png" align="center" alt="WinRAR Keygen" />
 <h2 align="center">WinRAR Keygen</h2>
 <p align="center">Principle of WinRAR key generation</p>
</p>
<p align="center">
  <a href="https://github.com/bitcookies/winrar-keygen/releases"><img src="https://img.shields.io/github/v/release/bitcookies/winrar-keygen?label=version" /></a>
  <a href="https://github.com/bitcookies/winrar-keygen/issues"><img alt="Issues" src="https://img.shields.io/github/issues/bitcookies/winrar-keygen?color=F48D73" /></a>
  <img src="https://img.shields.io/badge/Visual%20Studio-2022-5D4298?logo=data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBzdGFuZGFsb25lPSJubyI/PjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+PHN2ZyB0PSIxNzI4MTA5NjA3MzUyIiBjbGFzcz0iaWNvbiIgdmlld0JveD0iMCAwIDEwMjQgMTAyNCIgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHAtaWQ9IjYxMjAiIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMjQiIGhlaWdodD0iMjQiPjxwYXRoIGQ9Ik03MTguOTMzMzMzIDg1LjMzMzMzM0wzODcuODQgNDE2Ljg1MzMzM2wtMjA5LjA2NjY2Ny0xNjQuNjkzMzMzTDg3LjQ2NjY2NyAyOTguNjY2NjY3djQyNi42NjY2NjZsOTEuNzMzMzMzIDQ2LjUwNjY2NyAyMTAuMzQ2NjY3LTE2NC4yNjY2NjdMNzE5Ljc4NjY2NyA5MzguNjY2NjY3IDkzOC42NjY2NjcgODUwLjM0NjY2N1YxNzAuNjY2NjY3ek0xODYuNDUzMzMzIDYxMC4xMzMzMzNWNDExLjczMzMzM2wxMDQuMTA2NjY3IDEwMy42OHogbTUyNi4wOCA1NS4wNEw1MTQuMTMzMzMzIDUxMmwxOTguNC0xNTMuMTczMzMzeiIgcC1pZD0iNjEyMSIgZmlsbD0iIzk1OWRhNSI+PC9wYXRoPjwvc3ZnPg==" />
  <a href="https://github.com/bitcookies/winrar-keygen/actions"><img src="https://github.com/bitcookies/winrar-keygen/actions/workflows/keygen.yml/badge.svg" /></a>
  <a href="https://github.com/bitcookies/winrar-keygen/blob/master/LICENSE"><img alt="License" src="https://img.shields.io/github/license/bitcookies/winrar-keygen.svg" /></a>
</p>
<p align="center">
  <a href="README.zh-CN.md">简体中文</a> | <a href="README.md">English</a>
</p>


## 1. What is WinRAR?

WinRAR is a trialware file archiver utility for Windows, developed by Eugene Roshal of win.rar GmbH. 

It can create and view archives in RAR or ZIP file formats and unpack numerous archive file formats. 

WinRAR is not a free software. If you want to use it, you should pay to [__RARLAB__](https://www.rarlab.com/) and then you will get a license file named `rarreg.key`. 

This repository will tell you how WinRAR license file `"rarreg.key"` is generated. 

## 2. How is "rarreg.key" generated?

See [here](README.HOW_DOES_IT_WORK.md).

## 3. How to use?

There are several ways to use it.

- [Use Github Actions](#4-Use-Github-Actions) 
- [Use Github Actions with secrets](#5-Use-Github-Actions-with-secrets)
- [Build in Visual Studio](#6-Build-in-Visual-Studio)

### 3.1 Encoding

WinRAR Keygen supports `ASCII`, `ANSI` and `UTF-8` encoding types, the corresponding supported characters are listed in the table below.

> [!NOTE]
> The default is `utf8`, but you can specify the encoding as `ascii` or `ansi`.

| Encoding                                     | Supported Characters                                         | Character Examples                                           |
| -------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| [ascii](https://en.wikipedia.org/wiki/ASCII) | Only full ASCII characters are supported.                    | <img width="300px" src="assets/ascii-characters-light.svg#gh-light-mode-only"><img width="300px" src="assets/ascii-characters-dark.svg#gh-dark-mode-only"> |
| ansi                                         | There is no one fixed ANSI code, usually [Windows-1252](https://en.wikipedia.org/wiki/Windows-1252), but other local codes are also possible. | <img width="300px" src="assets/windows-1252-characters-light.svg#gh-light-mode-only"><img width="300px" src="assets/windows-1252-characters-dark.svg#gh-dark-mode-only"> |
| [utf8](https://en.wikipedia.org/wiki/UTF-8)  | Support full UTF-8 encoded characters.                       | ASCII characters, English, 简体中文, 繁體中文, Deutsch, Français, Русский, Italiano, 日本語, 한국어, Lengua española, Ελληνική γλώσσα, et al. |

### 3.2 License type

There are two types of WinRAR licenses, `rarreg.key` and `rarkey.rar`, which differ only in their import.

|                   rarreg.key                   |                    rarkey.rar                    |
| :--------------------------------------------: | :----------------------------------------------: |
| <img width="100px" src="assets/file-icon.svg"> | <img width="100px" src="assets/winrar-icon.svg"> |
|     Drag to import or place in a location      |       Double-click to run automatic import       |

If you are unable to drag, you can try to put the `rarreg.key` in the following directory.

```shell
C:\Users\yourname\AppData\Roaming\WinRAR\rarreg.key
```

You can also compress `rarreg.key` into `rarkey.rar` and double-click it to run it, and the license import will take place automatically.

## 4. Use Github Actions

<details>
<summary>Click to expand</summary>

The new workflow can easily help you generate a license, you just need to follow these steps.

> Your `Username` and `License Name` will appear in the actions log, if you don't want to give out this information, see [5. Using Github Actions with secrets](#5-Use-Github-Actions-with-secrets).

### 4.1 Fork

**Fork** this repo.

![Fork](assets/fork-light.png#gh-light-mode-only)

![Fork](assets/fork-dark.png#gh-dark-mode-only)

### 4.2 Allow fork repo to run workflows

Go back to the repo you just forked and click **Actions** to allow Workflows to run in your forked repo.

![Workflow](assets/enable-workflows-light.png#gh-light-mode-only)

![Workflow](assets/enable-workflows-dark.png#gh-dark-mode-only)

### 4.3 Run workflow

After allowing the workflow, go to **Actions > WinRAR Keygen > Run workflow** and fill in the information to start generating.

> For the difference of license encoding, please refer to [3.1 Encoding](#31-Encoding).

![Secrets](assets/run-ketgen-light.png#gh-light-mode-only)

![Secrets](assets/run-ketgen-dark.png#gh-dark-mode-only)

After running successfully, open the corresponding task and select **rarreg_file** to download.

> File retention 90 days.

![Download](assets/file-download-light.png#gh-light-mode-only)

![Download](assets/file-download-dark.png#gh-dark-mode-only)

Extract rarreg_file.zip to get `rarreg.key` and drag to import into WinRAR. You can also compress `rarreg.key` into `rarkey.rar`, then double-click it to run it, and the license import will be done automatically.

If you get an invalid key, please check [the specific solution](#7-invalid-key).

</details>

## 5. Use Github Actions with secrets

<details>
<summary>Click to expand</summary>

Using [secrets](https://docs.github.com/en/actions/security-guides/encrypted-secrets) can help you hide license information.

### 5.1 Fork

**Fork** this repo.

![Fork](assets/fork-light.png#gh-light-mode-only)

![Fork](assets/fork-dark.png#gh-dark-mode-only)

### 5.2 Allow fork repo to run workflows

Go back to the repo you just forked and click **Actions** to allow Workflows to run in your forked repo.

![Workflow](assets/enable-workflows-light.png#gh-light-mode-only)

![Workflow](assets/enable-workflows-dark.png#gh-dark-mode-only)

### 5.3 Create secrets

After allowing the workflow, go to **Settings > Secrets and variables > Actions > New repository secret** to create a secret.

![Secrets](assets/secrets-light.png#gh-light-mode-only)

![Secrets](assets/secrets-dark.png#gh-dark-mode-only)

Create three secrets with the names `TEXT1`, `TEXT2` and `PWD` and fill in the relevant values.

> The value filled in should be consistent with the type of code you have chosen.

| Secrets Name<img width="120px"> | Explanation<img width="120px"> |
| ------------------------------- | ------------------------------ |
| TEXT1                           | Your Name                      |
| TEXT2                           | Your License Name              |
| PWD                             | 7-Zip Password                 |

![Add Secrets](assets/secrets-add-light.png#gh-light-mode-only)

![Add Secrets](assets/secrets-add-dark.png#gh-dark-mode-only)

Once created, you will see it.

![Secrets Repo](assets/secrets-repo-light.png#gh-light-mode-only)

![Secrets Repo](assets/secrets-repo-dark.png#gh-dark-mode-only)

### 5.4 Run workflow

Go to **Actions** and select **WinRAR Keygen with secrets** to run workflow manually.

For the difference of license encoding, please refer to [3.1 Encoding](#31-Encoding).

![Run](assets/run-workflow-light.png#gh-light-mode-only)

![Run](assets/run-workflow-dark.png#gh-dark-mode-only)

After running successfully, open the corresponding task and select **rarreg_file** to download.

> File retained for **1 day** only.

![Download](assets/file-download-light.png#gh-light-mode-only)

![Download](assets/file-download-dark.png#gh-dark-mode-only)

Extract `rarreg_file.zip` to get `rarreg.7z`, unzip it with the password to get `rarreg.key`, then drag and drop to import into WinRAR. You can also compress `rarreg.key` into `rarkey.rar`, then double-click it to run it, and the license import will be done automatically.

If you get an invalid key, please check [the specific solution](#7-invalid-key).

</details>

## 6. Build in Visual Studio

<details>
<summary>Click to expand</summary>

I recommend using the Github Actions, but you can still do your own compilation.

If you don't want to compile it yourself, you can also go to the [release](https://github.com/bitcookies/winrar-keygen/releases/) page to get `winrar-keygen.exe`.

### 6.1 Prerequisites

1. Please make sure that you have **Visual Studio 2022**. Because this is a VS2022 project. If you are still using Visual Studio 2019, you can find projects for VS2019 in the [vs2019](https://github.com/bitcookies/winrar-keygen/tree/vs2019) branch, but this branch will no longer be maintained.

2. Please make sure you have installed `vcpkg` and the following libraries:

   * `mpir:x86-windows-static`
   * `mpir:x64-windows-static`

   is installed.

   You can install them by:

   ```shell
   $ vcpkg install mpir:x86-windows-static
   $ vcpkg install mpir:x64-windows-static
   ```

3. Your `vcpkg` has been integrated into your __Visual Studio__, which means you have run successfully.

   ```shell
   $ vcpkg integrate install
   ```
   

### 6.2 Build

1. Open this project in __Visual Studio__.

2. Select `Release` configuration.

3. Select __Build > Build Solution__.

You will see executable files in `bin/` directory. 

### 6.3 How to use?

Execute the following code in the terminal and configure two parameters to generate `rarreg.key`.

Here is an example of ASCII encoding for `Github` and `Single PC usage license`:

```shell
Usage:
        winrar-keygen.exe <Username> <License Name>

Example:

        winrar-keygen.exe "Github" "Single PC usage license"

  or:
        winrar-keygen.exe "Github" "Github.com" | Out-File -Encoding ASCII rarreg.key
```

![Terminal](assets/terminal.png)

Now you can see the newly generated file.

```console
RAR registration data
Github
Single PC usage license
UID=3a3d02329a32b63da7d8
6412212250a7d8753c5e7037d83011171578c57042fa30c506caae
9954e4853d415ec594e46017cb3db740bc4b32e47aea25db62f350
9f22065a27da4f8216d2938e1050b6e3347501a3767d1fdd7ee130
dd4ab952600ba16a99236d910bfa995d5f60651ec451f462511507
95b3722d059f2d5303a231e396cf21f17098edeec0b6e3347501a3
767d1fdd7ee45388769767642338ee8a63178f3458b71de5609b18
5eede7ed46566b10bf033daa6384062b259194b1acbd0378116064
```

Save the generated information in **ANSI encoding** as `rarreg.key`.

### 6.4 Multi-language support

Execute the following code in the terminal and configure two paramet

When using ANSI encoding, you can only use characters from the country or region where your operating system is located. ANSI encoding is supported from Powershell 7.4 onwards, and you will also need to [upgrade your Powershell](https://learn.microsoft.com/en-us/powershell/scripting/install/installing-powershell-on-windows?view=powershell-7.4).

Generate multi-language licenses in ANSI encoding.

```shell
winrar-keygen.exe "简体中文" "license" | Out-File -Encoding ansi rarreg.key

winrar-keygen.exe "繁體中文" "license" | Out-File -Encoding ansi rarreg.key

winrar-keygen.exe "Deutsch" "license" | Out-File -Encoding ansi rarreg.key

winrar-keygen.exe "Français" "license" | Out-File -Encoding ansi rarreg.key

winrar-keygen.exe "日本語" "license" | Out-File -Encoding ansi rarreg.key

winrar-keygen.exe "한국어" "license" | Out-File -Encoding ansi rarreg.key
```

When generating utf-8 licenses, you may need to check Use ***[Beta:Use Unicode UTF-8 for global language support](https://stackoverflow.com/a/57134096/10242225)*** in **Control Panel > Clock and Regions > Regions > Administration > Change System Region Settings** in order to process the data correctly. However, it is not recommended that you do this, which may cause many software to not work properly, and it is recommended to [use Github Actions](#4-Use-Github-Actions).

Generate multi-language licenses with UTF-8 encoding.

> `utf8:` is to ensure constant character representation in WinRAR across languages.

```shell
winrar-keygen.exe "utf8:简体中文" "license" | Out-File -Encoding utf8 rarreg.key

winrar-keygen.exe "utf8:繁體中文" "license" | Out-File -Encoding utf8 rarreg.key

winrar-keygen.exe "utf8:Deutsch" "license" | Out-File -Encoding utf8 rarreg.key

winrar-keygen.exe "utf8:Français" "license" | Out-File -Encoding utf8 rarreg.key

winrar-keygen.exe "utf8:日本語" "license" | Out-File -Encoding utf8 rarreg.key

winrar-keygen.exe "utf8:한국어" "license" | Out-File -Encoding utf8 rarreg.key
```

</details>

## 7. Invalid key

Why is my `rarreg.key` invalid?

### 7.1 Character encoding

`TEXT1` and `TEXT2` are required to fulfill [corresponding coding requirements](#31-Encoding).

```console
winrar-keygen.exe <TEXT1> <TEXT2>
```

You can refer to: [Generation of "rarreg.key"](https://github.com/bitcookies/winrar-keygen/blob/master/README.HOW_DOES_IT_WORK.md#7-generation-of-rarregkey)

### 7.2 Text encoding

If you use the following command:

```shell
winrar-keygen.exe "Github" "Single PC usage license" > rarreg.key
```

In the newer Windows 10, PowerShell will export in **UTF16-LE** format by default, which will cause the error.

Please use the following command:

```shell
winrar-keygen.exe "Github" "Github.com" | Out-File -Encoding ascii rarreg.key

winrar-keygen.exe "Github" "Github.com" | Out-File -Encoding ansi rarreg.key

winrar-keygen.exe "utf8:Github" "Github.com" | Out-File -Encoding utf8 rarreg.key
```

## 8. Contributing

### 8.1 Suggestion

If you encounter some problems, you can report on the [Issues](https://github.com/bitcookies/winrar-keygen/issues) page. There will be many enthusiastic developers or Github users to help you.

This project welcomes contributions and suggestions. You can make suggestions in [Issues](https://github.com/bitcookies/winrar-keygen/issues), or submit a pull request 😄

### 8.2 Thanks

Thank you very much to some enthusiastic developers for helping answer some questions in [Issues](https://github.com/bitcookies/winrar-keygen/issues).

🏆 Special Thanks [@Sonic-The-Hedgehog-LNK1123](https://github.com/Sonic-The-Hedgehog-LNK1123)

## 9. License

The code is available under the [MIT license](https://github.com/bitcookies/winrar-keygen/blob/master/LICENSE)
