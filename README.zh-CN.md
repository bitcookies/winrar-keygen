<p align="center">
 <img width="100px" src="icon.png" align="center" alt="WinRAR Keygen" />
 <h2 align="center">WinRAR Keygen</h2>
 <p align="center">Principle of WinRAR key generation</p>
</p>
<p align="center">
  <a href="https://github.com/bitcookies/winrar-keygen/releases">
  	<img src="https://img.shields.io/github/v/release/bitcookies/winrar-keygen?label=version" />
  </a>
  <a href="https://github.com/bitcookies/winrar-keygen/issues">
  	<img alt="Issues" src="https://img.shields.io/github/issues/bitcookies/winrar-keygen?color=F48D73" />
  </a>
  <img src="https://img.shields.io/badge/Visual%20Studio-2022-5D4298" />
  <a href="https://github.com/bitcookies/winrar-keygen/actions">
      <img src="https://github.com/bitcookies/winrar-keygen/actions/workflows/action.yml/badge.svg" />
  </a>
  <a href="https://github.com/bitcookies/winrar-keygen/blob/master/LICENSE">
  	<img alt="License" src="https://img.shields.io/github/license/bitcookies/winrar-keygen.svg" />
  </a>
</p>
<p align="center">
  <a href="README.zh-CN.md">简体中文</a> | <a href="README.md">English</a>
</p>


## 1. WinRAR是什么？

WinRAR是一款用于管理压缩包文件的共享软件。其算法由作者尤金·罗谢尔研发，享有原创专利。

它可以用来创建或浏览RAR、ZIP等众多格式的压缩包。

WinRAR不是免费软件。如果你想使用它，你应当向 [__RARLAB__](https://www.rarlab.com/) 付费，然后获得一个授权文件 `rarreg.key`。

这份repo将会告诉你 `rarreg.key` 是如何生成的。

## 2. "rarreg.key"是如何生成的？

见 [这里](README.HOW_DOES_IT_WORK.zh-CN.md)。

## 3. 使用方法

有多种方法可供选择：

+ [通过 Secrets 使用 Github Actions](#4-通过-Secrets-使用-Github-Actions) *<⭐ 推荐>*
+ [通过 Push 使用 Github Actions](#5-通过-Push-使用-Github-Actions)
+ [通过 Visual Studio 编译使用](#6-通过-Visual-Studio-编译使用)

## 4. 通过 Secrets 使用 Github Actions

<details>
<summary>点击展开</summary>


使用 [Secrets](https://docs.github.com/en/actions/security-guides/encrypted-secrets) 可以不用对仓库代码进行修改，方便你以后可以无冲突的对仓库进行同步更新，所以我优先推荐使用这种方法：

### 4.1 Fork

点击该项目右上角的 **Fork** 按钮，fork 一份代码到你的 Github：

![Fork](assets/fork-light.png#gh-light-mode-only)

![Fork](assets/fork-dark.png#gh-dark-mode-only)

### 4.2 创建 Secrets

打开你 fork 后的仓库，进入 **Settings > Secrets > Actions > New repository secret** 来创建：

![Secrets](assets/secrets-light.png#gh-light-mode-only)

![Secrets](assets/secrets-dark.png#gh-dark-mode-only)

创建两个 Secrets，名称为 `text1` 和 `text2`，并填入相关值：

![Add Secrets](assets/secrets-add-light.png#gh-light-mode-only)

![Add Secrets](assets/secrets-add-dark.png#gh-dark-mode-only)

创建完成后，你将会看到：

![Secrets Repo](assets/secrets-repo-light.png#gh-light-mode-only)

![Secrets Repo](assets/secrets-repo-dark.png#gh-dark-mode-only)

### 4.3 运行 Workflow

进入 **Actions** 并选择 **WinRAR Keygen Secrets** 来手动执行 Workflow：

![Run](assets/run-workflow-light.png#gh-light-mode-only)

![Run](assets/run-workflow-dark.png#gh-dark-mode-only)

运行成功之后，打开对应的任务，选择 **rarreg_file** 下载：

![Download](assets/file-download-light.png##gh-light-mode-only)

![Download](assets/file-download-dark.png#gh-dark-mode-only)

</details>

## 5. 通过 Push 使用 Github Actions

<details>
<summary>点击展开</summary>

使用 push 操作进行 key 的生成非常的简单和方便，但是当有更新同步时你需要手动进行冲突合并。所以我建议优先 [通过 Secrets 使用 Github Actions](#4-通过-Secrets-使用-Github-Actions) ，但是你仍可以使用 push 操作：

### 5.1 Fork

点击该项目右上角的 **Fork** 按钮，fork 一份代码到你的 Github：

![Fork](assets/fork-light.png#gh-light-mode-only)

![Fork](assets/fork-dark.png#gh-dark-mode-only)

如果你之前 fork 过，然后我提交了新的代码，但是你不懂得如何合并新内容到你的仓库，那你也可以删掉当前 fork 的仓库，然后重新 fork 一次。

### 5.2 修改 info.json

打开你 fork 后的仓库，进入 `keygen/info.json`，点击编辑按钮，对该文件进行编辑：

![Edit](assets/edit-json-light.png#gh-light-mode-only)

![Edit](assets/edit-json-dark.png#gh-dark-mode-only)

打开该文件，你会发现有以下内容：

```json
{
    "text1": "Github",
    "text2": "Github.com"
}
```

你可以自己修改  `text1` 和 `text2` 相对应的值，例如：

```json
{
    "text1": "Your Name",
    "text2": "Your License"
}
```

`test1` 和 `test2` 参数均是 **ANSI 编码，目前已经支持空格**。

修改完成之后，点击 **Commit changes** 按钮，Github Actions 会自动开始执行。

如果 Github Actions 未自动开始，你需要先点击 Actions 页面 **允许此 workflows 运行**，然后再次修改并提交 `keygen/info.json` 。

![Workflow](assets/enable-workflows-light.png#gh-light-mode-only)

![Workflow](assets/enable-workflows-dark.png#gh-dark-mode-only)

### 5.3 下载文件

进入 **Actions** 并选择 **WinRAR Keygen** 页面查看程序运行状况：

![Workflow](assets/push-workflows-light.png#gh-light-mode-only)

![Workflow](assets/push-workflows-dark.png#gh-dark-mode-only)

绿色说明运行成功，黄色说明正在运行，红色说明运行失败。运行成功之后，打开对应的任务，选择 **rarreg_file** 下载：

![Download](assets/file-download-light.png##gh-light-mode-only)

![Download](assets/file-download-dark.png#gh-dark-mode-only)

将 `rarreg_file.zip` 解压缩后会得到 `rarreg.key`，然后拖动导入 WinRAR 即可。

如果你得到的是 key 是无效的，请查看 [解决方法](#7-无效的key)。

</details>

## 6. 通过 Visual Studio 编译使用

<details>
<summary>点击展开</summary>

我建议通过 Github Actions 的方法来使用，但是你仍然可以选择自行编译。

如果你不想自行编译，也可以到 [Release](https://github.com/bitcookies/winrar-keygen/releases/) 页面获取对应版本的 `winrar-keygen.exe`。

### 6.1 前提条件

1. 请确保你有 **Visual Studio 2022**，因为这是一个 VS2022 项目。如果你仍在使用 Visual Studio 2019，可以在 [vs2019](https://github.com/bitcookies/winrar-keygen/tree/vs2019) 分支中找到适合 VS2019 的项目，但是此分支将不再维护。

2. 请确保你安装了 `vcpkg` 以及下面几个库：

   - `mpir:x86-windows-static`

   * `mpir:x64-windows-static`

   你可以通过下的命令来安装：

   ```console
   $ vcpkg install mpir:x86-windows-static
   $ vcpkg install mpir:x64-windows-static
   ```

3. 你的 `vcpkg` 与 __Visual Studio__ 整合了，即你曾成功运行了下面这条命令：

   ```console
   $ vcpkg integrate install
   ```

### 6.2 编译

1. 在 __Visual Studio__ 中打开这个项目。
2. 选择 `Release` 配置。
3. 选择 __生成 > 生成解决方案__。

你将在 `bin/` 目录下看到生成的文件。

### 6.3 如何使用？

直接在终端执行以下代码，配置两个参数即可生成 `rarreg.key`。

这里以 `Github` 和 `Github.com` 为例：

```console
Usage:
        winrar-keygen.exe <Your Name> <Your License>

Example:

        winrar-keygen.exe "Github" "Github.com"
  or:
        winrar-keygen.exe "Github" "Github.com" > rarreg.key
  or:
        winrar-keygen.exe "Github" "Github.com" | Out-File -Encoding ASCII rarreg.key
```

![Terminal](assets/terminal.png)

现在你可以看到新生成的文件：

```console
RAR registration data
Github
Github.com
UID=3a3d02329a32b63da7d8
6412212250a7d8753c5e7037d83011171578c57042fa30c506caae
9954e4853d415ec594e46076cc9a65338309b66c50453ba72158c0
656de97acb2f2a48cf3b75329283544c3e1b366a5062b85d0022f6
de3cdc56b311475b484e80b48157a0c3af60ca4f7f9c75d49bc50d
6bad616c1c58caa922d3ed0cd19771e8191522a586544c3e1b366a
5062b85d29db066f02e777ad78100865f2c31f2dd3a86998609b18
5eede7ed46566b10bf033daa6384062b259194b1acbd1443042646
```

将生成的信息以 **ANSI 编码** 的文本格式保存为 `rarreg.key`。

</details>

## 7. 无效的Key

为什么我生成的 `rarreg.key` 是无效的？

### 7.1 ANSI编码

`test1` 以及 `test2` 生成的许可文本，均是 **ANSI 编码，目前已经支持空格** [Issues #5](https://github.com/bitcookies/winrar-keygen/issues/5)。

```console
winrar-keygen.exe <text1> <text2>
```

具体可参考原理文档：[授权文件"rarreg.key"的生成](https://github.com/bitcookies/winrar-keygen/blob/master/README.HOW_DOES_IT_WORK.zh-CN.md#7-%E6%8E%88%E6%9D%83%E6%96%87%E4%BB%B6rarregkey%E7%9A%84%E7%94%9F%E6%88%90)

### 7.2 TXT编码

如果你使用了如下命令：

```console
winrar-keygen.exe "Github" "Github.com" > rarreg.key
```

在较新的 Windows 10 系统中，PowerShell 将默认以 **UTF16-LE** 格式导出，这将会导致错误。

请使用如下命令：

```console
winrar-keygen.exe "Github" "Github.com" | Out-File -Encoding ASCII rarreg.key
```

### 7.3 Key的位置

如果你无法执行拖动操作，你可以尝试把 `rarreg.key` 放在以下目录中：

```console
C:\Users\yourname\AppData\Roaming\WinRAR\rarreg.key
```

### 7.4 关于简体中文版

在 [__RARLAB__](https://www.rarlab.com/) 下载的简体中文版 WinRAR 将会自带广告组件，即使使用了 `rarreg.key` 授权，广告组件依旧会出现。如果您介意广告，可以下载其他语言版。

## 8. 贡献

### 8.1 反馈和建议

如果您遇到了一些问题，可在 [Issues](https://github.com/bitcookies/winrar-keygen/issues) 页面反馈，会有很多热心的开发者及 Github 用户帮助你。

该项目欢迎贡献和建议，您可以在 [Issues](https://github.com/bitcookies/winrar-keygen/issues) 提出建议，或者进行提交拉取请求 😄

### 8.2 感谢

非常感谢一些热心的开发者，在 [Issues](https://github.com/bitcookies/winrar-keygen/issues) 帮助解答一些问题。

🏆 特别感谢 [@Sonic-The-Hedgehog-LNK1123](https://github.com/Sonic-The-Hedgehog-LNK1123)

## 9. 许可

使用 [MIT License](https://github.com/bitcookies/winrar-keygen/blob/master/LICENSE)
