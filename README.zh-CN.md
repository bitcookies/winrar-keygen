<p align="center">
 <img width="100px" src="icon.png" align="center" alt="WinRAR Keygen" />
 <h2 align="center">WinRAR Keygen</h2>
 <p align="center">Principle of WinRAR key generation</p>
</p>
<p align="center">
  <img src="https://img.shields.io/github/v/release/bitcookies/winrar-keygen?label=version" />
  <a href="https://github.com/bitcookies/winrar-keygen/issues">
  	<img alt="Issues" src="https://img.shields.io/github/issues/bitcookies/winrar-keygen?color=F48D73" />
  </a>
  <img src="https://img.shields.io/badge/Visual%20Studio-2022-5D4298" />
  <a href="https://github.com/bitcookies/winrar-keygen/actions">
      <img src="https://img.shields.io/badge/Github-Actions-4184F4" />
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

## 3. 通过 Github Actions 使用(发现错误)

2021.12.9 **发现了一个错误，导致Github Actions生成的ke也是无效的，正在排查中**

Github Action 是微软收购 Github 之后推出的 CI/CD 工具，通过以下步骤即可在 GitHub Action 上运行程序：

### 3.1 Fork

点击该项目右上角的 **Fork** 按钮，fork 一份代码到你的 Github：

![step-1](assets/actions-step-1.png)

如果你之前 fork 过，然后我提交了新的代码，但是你不懂得如何合并新内容到你的仓库，那你也可以删掉当前 fork 的仓库，然后重新 fork 一次。

### 3.2 修改 info.json

进入 `keygen/info.json`，点击编辑按钮，对该文件进行编辑：

![step-2](assets/actions-step-2.png)

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
    "text1": "yourname",
    "text2": "yourteam"
}
```

需要注意的是，`test1` 和 `test2` 参数均是**不含空格的 ANSI 编码。**

修改完成之后，点击 **Commit changes** 按钮，Github Actions 会自动开始执行。

如果 Github Actions 未自动开始，你需要先点击 Actions 页面 **允许此 workflows 运行**，然后再次修改并提交 `keygen/info.json` 。

### 3.3 下载文件

进入 Actions 页面查看程序运行状况：

![step-3](assets/actions-step-3.png)

绿色说明运行成功，黄色说明正在运行，红色说明运行失败。运行成功之后，打开对应的任务，选择 **rarreg_file** 下载：

![step-4](assets/actions-step-4.png)

解压缩后会得到 `rarreg.key` ，拖动导入 WinRAR 即可。

如果你得到的是无效的 key，请检查 `test1` 和 `test2` 参数是否是**不含空格的 ANSI 编码。**

## 4. 通过 Visual Studio 编译使用

我建议通过 Github Actions 的方法来使用，但是你仍然可以自己进行编译。

如果你不想自己编译，也可以到 [Release](https://github.com/bitcookies/winrar-keygen/releases/) 页面获取对应版本的 `winrar-keygen.exe`。

### 4.1 前提条件

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

### 4.2 编译

1. 在 __Visual Studio__ 中打开这个项目。
2. 选择 `Release` 配置。
3. 选择 __生成 > 生成解决方案__。

你将在 `bin/` 目录下看到生成的文件。

### 4.3 如何使用？

直接在终端执行以下代码，配置两个参数即可生成 `rarreg.key`。

这里以 `Github` 和 `Github.com` 为例：

```console
Usage:
        winrar-keygen.exe <your name> <license type>

Example:

        winrar-keygen.exe "Github" "Github.com"
  or:
        winrar-keygen.exe "Github" "Github.com" > rarreg.key
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

将生成的信息以文本格式保存为 `rarreg.key`，拖动导入 WinRAR 即可。

## 5. 无效的Key

为什么我生成的 `rarreg.key` 是无效的？

### 5.1 ANSI编码

`test1` 以及 `test2` 生成的许可文本，均是 **不含空格的 ANSI 编码。**

```console
winrar-keygen.exe <text1> <text2>
```

### 5.2 终端编码的问题

[Issues #5](https://github.com/bitcookies/winrar-keygen/issues/5) 请务必使用 ANSI 编码（不包含空格）：

具体可参考原理文档：[授权文件"rarreg.key"的生成](https://github.com/bitcookies/winrar-keygen/blob/master/README.HOW_DOES_IT_WORK.zh-CN.md#7-%E6%8E%88%E6%9D%83%E6%96%87%E4%BB%B6rarregkey%E7%9A%84%E7%94%9F%E6%88%90)

感谢 [@Sonic-The-Hedgehog-LNK1123](https://github.com/Sonic-The-Hedgehog-LNK1123).

## 6. 遇到问题

### 6.1 反馈

如果您遇到了一些问题，可在 [Issues](https://github.com/bitcookies/winrar-keygen/issues) 页面反馈，会有很多热心的开发者及 Github 用户帮助你。

### 6.2 安全

[Issues #1](https://github.com/bitcookies/winrar-keygen/issues/1) 一些杀毒软件可能会误报，如果您不信任此二进制可执行文件，您唯一的选择就是自己编译代码。

### 6.3 下载

[Issues #4](https://github.com/bitcookies/winrar-keygen/issues/4) IDM等下载工具可能会有问题，请使用浏览器（例如 chrome、edge）下载。

### 6.4 关于简体中文版

在 [__RARLAB__](https://www.rarlab.com/) 下载的简体中文版 WinRAR 将会自带广告组件，即使使用了 `rarreg.key` 授权，广告组件依旧会出现。如果您介意广告，可以尝试下载其他语言版。

## 7. 贡献

该项目欢迎贡献和建议，您可以在 [Issues](https://github.com/bitcookies/winrar-keygen/issues) 提出建议，或者进行提交拉取请求 :-)

非常感谢一些热心的开发者，在 [Issues](https://github.com/bitcookies/winrar-keygen/issues) 帮助解答一些问题。

感谢 [@Sonic-The-Hedgehog-LNK1123](https://github.com/Sonic-The-Hedgehog-LNK1123)

## 8. 许可

使用 [MIT License](https://github.com/bitcookies/winrar-keygen/blob/master/LICENSE)
