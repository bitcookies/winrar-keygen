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
  <a href="README.md">English</a> | <a href="README.zh-CN.md">简体中文</a>
</p>

## 1. WinRAR是什么？

WinRAR 是一款用于管理压缩包文件的共享软件。其算法由作者尤金·罗谢尔研发，享有原创专利。

它可以用来创建或浏览 RAR、ZIP 等众多格式的压缩包。

WinRAR 不是免费软件。如果你想使用它，你应当向 [**RARLAB**](https://www.rarlab.com/) 付费，然后获得一个授权文件 `rarreg.key`。

这份 repo 将会告诉你 `rarreg.key` 是如何生成的。

## 2. "rarreg.key"是如何生成的？

见 [这里](README.HOW_DOES_IT_WORK.zh-CN.md)。

## 3. 使用方法

有多种方法可供选择：

+ [使用 Github Actions](#4-使用-Github-Actions)
+ [使用 Github Actions with secrets](#5-使用-Github-Actions-with-secrets)
+ [通过 Visual Studio 编译使用](#6-通过-Visual-Studio-编译使用)

### 3.1 编码说明

WinRAR Keygen 支持 `ASCII`、`ANSI` 和 `UTF8NoBOM` 三种编码类型，对应支持的字符如下表：

> [!NOTE]
> 默认使用 `utf8`，但是你也可以指定编码为 `ascii` 或 `ansi`。

| 编码                                         | 支持的字符                                                   | 字符示例                                                     |
| -------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| [ascii](https://en.wikipedia.org/wiki/ASCII) | 仅支持 ASCII 编码字符                                        | <img width="300px" src="assets/ascii-characters-light.svg#gh-light-mode-only"><img width="300px" src="assets/ascii-characters-dark.svg#gh-dark-mode-only"> |
| ansi                                         | 没有一种固定的 ANSI 编码，通常是 [Windows-1252](http://en.wikipedia.org/wiki/Windows-1252)，但也可以是其他本地 | <img width="300px" src="assets/windows-1252-characters-light.svg#gh-light-mode-only"><img width="300px" src="assets/windows-1252-characters-dark.svg#gh-dark-mode-only"> |
| [utf8](https://en.wikipedia.org/wiki/UTF-8)  | 支持无 BOM 的 UTF-8                                          | ASCII characters, English, 简体中文, 繁體中文, Deutsch, Français, Русский, Italiano, 日本語, 한국어, Lengua española, Ελληνική γλώσσα 等。 |

### 3.2 License 类型

WinRAR license 有 `rarreg.key` 和 `rarkey.rar` 两种类型，它们仅在导入上有区别：

| <img width="60px">rarreg.key<img width="60px"> |  <img width="60px">rarkey.rar<img width="60px">  |
| :--------------------------------------------: | :----------------------------------------------: |
| <img width="100px" src="assets/file-icon.svg"> | <img width="100px" src="assets/winrar-icon.svg"> |
|             拖动导入或放于指定位置             |                 双击运行自动导入                 |

你可以把 `rarreg.key` 放置于以下目录中：

```shell
%APPDATA%\WinRAR\rarreg.key
```

你也可以将 `rarreg.key` 压缩成 `rarkey.rar` 然后双击运行，授权导入将会自动进行。

## 4. 使用 Github Actions

<details>
<summary>点击展开</summary>

新的 workflow 能很方便的帮助你生成 license，你只需跟随以下步骤即可：

> 你的 `Username` 和 `License Name` 会出现在 actions 的日志中，如果你不想泄露这些信息，请参考 [5. 使用 Github Actions with secrets](#5-使用-Github-Actions-with-secrets)。

### 4.1 Fork

点击该项目右上角的 **Fork** 按钮，fork 一份代码到你的 Github：

![Fork](assets/fork-light.png#gh-light-mode-only)

![Fork](assets/fork-dark.png#gh-dark-mode-only)

### 4.2 允许 fork 仓库运行 workflows

返回到你刚刚 fork 完成的 repo，然后点击 **Actions** 去允许 workflows 在你的 fork repo 中运行：

![Workflow](assets/enable-workflows-light.png#gh-light-mode-only)

![Workflow](assets/enable-workflows-dark.png#gh-dark-mode-only)

### 4.3 运行 workflow

允许 workflow 后，选择 **WinRAR Keygen > Run workflow** 并填入信息就可以开始生成了：

> License 编码的区别请参考 [3.1 编码说明](#31-编码说明)。

![Secrets](assets/run-ketgen-light.png#gh-light-mode-only)

![Secrets](assets/run-ketgen-dark.png#gh-dark-mode-only)

运行成功之后，打开对应的任务，选择 **rarreg_file** 下载：

> 文件保留 90 天，超出时间后会自动销毁。

![Download](assets/file-download-light.png#gh-light-mode-only)

![Download](assets/file-download-dark.png#gh-dark-mode-only)

将 `rarreg_file.zip` 解压缩后会得到 `rarreg.key`，然后拖动导入 WinRAR 即可。你也可以将 `rarreg.key` 压缩成 `rarkey.rar`，然后双击运行，授权导入将会自动进行。

</details>

## 5. 使用 Github Actions with secrets

<details>
<summary>点击展开</summary>

使用 [secrets](https://docs.github.com/en/actions/security-guides/encrypted-secrets) 可以帮助你隐藏 license 信息。

### 5.1 Fork

点击该项目右上角的 **Fork** 按钮，fork 一份代码到你的 Github：

![Fork](assets/fork-light.png#gh-light-mode-only)

![Fork](assets/fork-dark.png#gh-dark-mode-only)

### 5.2 允许 fork 仓库运行 workflows

返回到你刚刚 fork 完成的 repo，然后点击 **Actions** 去允许 workflows 在你的 fork repo 中运行：

![Workflow](assets/enable-workflows-light.png#gh-light-mode-only)

![Workflow](assets/enable-workflows-dark.png#gh-dark-mode-only)

### 5.3 创建 secrets

允许 workflows 后，进入 **Settings > Secrets and variables > Actions > New repository secret** 创建 secrets：

![Secrets](assets/secrets-light.png#gh-light-mode-only)

![Secrets](assets/secrets-dark.png#gh-dark-mode-only)

创建三个 secrets，名称为 `TEXT1` 、 `TEXT2` 和 `PWD`，并填入相关值：

> 填入的值应与你选择的编码类型保持一致。

| Secrets Name<img width="120px"> | Explanation<img width="120px"> |
| ------------------------------- | ------------------------------ |
| TEXT1                           | 用户名                         |
| TEXT2                           | 许可名                         |
| PWD                             | 压缩包密码                     |

![Add Secrets](assets/secrets-add-light.png#gh-light-mode-only)

![Add Secrets](assets/secrets-add-dark.png#gh-dark-mode-only)

创建完成后，你将会看到：

![Secrets Repo](assets/secrets-repo-light.png#gh-light-mode-only)

![Secrets Repo](assets/secrets-repo-dark.png#gh-dark-mode-only)

### 5.4 运行 workflow

进入 **Actions** 选择 **WinRAR Keygen with secrets  >  Run workflow** 并填入信息：

> License 编码的区别请参考 [3.1 编码说明](#31-编码说明)。

![Run](assets/run-workflow-light.png#gh-light-mode-only)

![Run](assets/run-workflow-dark.png#gh-dark-mode-only)

运行成功之后，打开对应的任务，选择 **rarreg_file** 下载：

> 文件仅保留 **1 天**，请及时下载。

![Download](assets/file-download-light.png#gh-light-mode-only)

![Download](assets/file-download-dark.png#gh-dark-mode-only)

将 `rarreg_file.zip` 解压缩后会得到 `rarreg.7z`，使用你设置的密码进行解压缩获得 `rarreg.key`，然后拖动导入 WinRAR 即可。你也可以将 `rarreg.key` 压缩成 `rarkey.rar`，然后双击运行，授权导入将会自动进行。

</details>

## 6. 通过 Visual Studio 编译使用

<details>
<summary>点击展开</summary>

我建议通过 Github Actions 的方法来使用，但是你仍然可以选择自行编译。

如果你不想自行编译，也可以到 [Release](https://github.com/bitcookies/winrar-keygen/releases/) 页面获取对应版本的 `winrar-keygen.exe`。

### 6.1 前提条件

1. 请确保你有 **Visual Studio 2022**，因为这是一个 VS2022 项目。如果你仍在使用 Visual Studio 2019，可以在 [vs2019](https://github.com/bitcookies/winrar-keygen/tree/vs2019) 分支中找到适合 VS2019 的项目，但是此分支将不再维护。

2. 请确保你安装了 `vcpkg` 以及下面几个库：

   + `mpir:x86-windows-static`
   + `mpir:x64-windows-static`
   + `mpir:gmp:x64-windows`

   你可以通过下的命令来安装：

   ```shell
   $ vcpkg install mpir:x86-windows-static
   $ vcpkg install mpir:x64-windows-static
   $ vcpkg install gmp:x64-windows
   ```

3. 你的 `vcpkg` 与 **Visual Studio** 整合了，即你曾成功运行了下面这条命令：

   ```shell
   $ vcpkg integrate install
   ```

### 6.2 编译

1. 在 **Visual Studio** 中打开这个项目；
2. 选择 **Release** 配置；
3. 选择 **生成 > 生成解决方案**。

你将在 `bin/` 目录下看到生成的文件。

### 6.3 如何使用？

直接在终端执行以下代码，配置两个参数即可生成 `rarreg.key`。

```shell
Usage:
  winrar-keygen.exe <Username> <LicenseName> [options]
  winrar-keygen.exe -v | --version
  winrar-keygen.exe -h | --help

Options:
  -e, --encoding <enc>   utf8 (default), ascii, ansi
  -o, --output <file>    Output file (default: rarreg.key)
  -a, --activate         Write to %%APPDATA%%\WinRAR\rarreg.key
  -t, --text             Print to console only, don't write file
  -v, --version          Show version
  -h, --help             Show this help
```

#### 参数选项

| 参数                   | 描述                                    |
| :--------------------- | :-------------------------------------- |
| `-e, --encoding <enc>` | `utf8` (默认), `ascii`, `ansi`          |
| `-o, --output <file>`  | Output file path (默认: `rarreg.key`)   |
| `-a, --activate`       | Write to `%APPDATA%\WinRAR\rarreg.key`  |
| `-t, --text`           | Print to console only, don't write file |
| `-v, --version`        | Show version                            |
| `-h, --help`           | Show help                               |

这里以 `Github` 和 `Single PC usage license` 参数和 ASCII 编码为例：

```shell
./winrar-keygen.exe "Github" "Single PC usage license" -t -e ascii
```

现在你可以看到新生成的文件：

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

### 6.4 更多示例

生成 UTF-8 编码的 license 并直接激活 WinRAR：

> UTF-8 编码的 license 将会根据字符自动决定是否添加 `utf8:` 前缀

```shell
./winrar-keygen.exe "Github" "Single PC usage license" -a
```

生成 ANSI 编码的 license 并生成 license 文件：

> ANSI 编码与 Windows 的地区有关，一般当前地区的字符能够正常展示，也会遇到字符乱码问题

```shell
./winrar-keygen.exe "Github" "Single PC usage license" -e ansi
```

生成 ASCII 编码的 license 并只在控制台输出：

```shell
./winrar-keygen.exe "Github" "Single PC usage license" -t -e asci
```

</details>

## 7. 常见错误

### 7.1 Keygen 错误

从 `ver4` 版本开始，Keygen 增加了一些常见的 Error 提示信息，请根据输出信息来进行修正。

使用 `-h` 或 `--help` 来查看帮助信息：

```shell
./winrar-keygen.exe -h
```

### 7.2 Github Actions 错误

如果你使用 `ascii` 编码时发生了错误，原因是你使用了非 ASCII 字符。

如果你 `ansi` 编码时发生了错误，原因是因为字符编码不受当前 Windows 系统支持。GitHub Actions 的系统平台是 `windows-2022-english` （ANSI code page 1252），包含非 ASCII 字符都会失败。

### 7.3 关于简体中文版

在 [**RARLAB**](https://www.rarlab.com/) 下载的简体中文版 WinRAR 将会自带广告组件，即使使用了 `rarreg.key` 授权，广告组件依旧会出现。这是由于简体中文代理商的一些意见，RARLAB 已将简体中文安装包的公开链接更换成了带有广告的简体中文安装包。

感谢 [@hoochanlon](https://github.com/hoochanlon) 提供的一些方法。可以使用 [win-rar-extractor](https://github.com/lvtx/WinRAR-Extractor) 获取简体中文商业版的下载连接；也可以根据商业版的地址规律，获取相应版本的简体中文安装包：

简体中文 **「商业版」** 下载地址：

```
# 7.13
https://www.win-rar.com/fileadmin/winrar-versions/sc/sc20250804/rrlb/winrar-x64-713sc.exe
https://www.win-rar.com/fileadmin/winrar-versions/sc/sc20250804/wrr/winrar-x64-713sc.exe

# 7.12
https://www.win-rar.com/fileadmin/winrar-versions/sc/sc20250627/rrlb/winrar-x64-712sc.exe
https://www.win-rar.com/fileadmin/winrar-versions/sc/sc20250627/wrr/winrar-x64-712sc.exe

# 7.11 （注意该版本的日期格式变更为了 YYYYDDMM）
https://www.win-rar.com/fileadmin/winrar-versions/sc/sc20253103/rrlb/winrar-x64-711sc.exe
https://www.win-rar.com/fileadmin/winrar-versions/sc/sc20253103/wrr/winrar-x64-711sc.exe

# 7.10 （注意该版本的日期格式变更为了 YYYYDDMM）
https://www.win-rar.com/fileadmin/winrar-versions/sc/sc20251003/rrlb/winrar-x64-710sc.exe
https://www.win-rar.com/fileadmin/winrar-versions/sc/sc20251003/wrr/winrar-x64-710sc.exe

# 6.24
https://www.win-rar.com/fileadmin/winrar-versions/sc/sc20231013/wrr/winrar-x32-624sc.exe
https://www.win-rar.com/fileadmin/winrar-versions/sc/sc20231013/wrr/winrar-x64-624sc.exe

```

简体中文 **「广告版」** （以 `6.24` 版本为例），不要下载此类版本：

```
# 其链接特点是「不包含」日期信息

win-rar 渠道：
https://www.win-rar.com/fileadmin/winrar-versions/winrar/winrar-x32-624sc.exe
https://www.win-rar.com/fileadmin/winrar-versions/winrar/winrar-x64-624sc.exe

rarlab 渠道：
https://www.rarlab.com/rar/winrar-x32-624sc.exe
https://www.rarlab.com/rar/winrar-x64-624sc.exe
```

请注意区分上述连接地址，更多方法可以查看 [Issues #14](https://github.com/bitcookies/winrar-keygen/issues/14) 和 [Issues #19](https://github.com/bitcookies/winrar-keygen/issues/19)。

## 8. 贡献

### 8.1 反馈和建议

如果您在使用过程中遇到问题或有任何建议，欢迎在 [Issues](https://github.com/bitcookies/winrar-keygen/issues) 页面反馈，或提交 Pull Request。我们以及社区中的开发者将乐于为您提供帮助。

### 8.2 感谢

感谢所有为本项目做出贡献的开发者，以及在 [Issues](https://github.com/bitcookies/winrar-keygen/issues) 中热心解答问题的社区成员。

## 9. 许可

使用 [MIT License](https://github.com/bitcookies/winrar-keygen/blob/master/LICENSE)
