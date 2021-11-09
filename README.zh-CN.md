<p align="center">
 <img width="100px" src="icon.svg" align="center" alt="WinRAR Keygen" />
 <h2 align="center">WinRAR Keygen</h2>
 <p align="center">Principle of WinRAR key generation</p>
</p>

<p align="center">
  <img src="https://img.shields.io/github/v/release/bitcookies/winrar-keygen?label=version" />
  <a href="https://github.com/bitcookies/winrar-keygen/issues">
  	<img alt="Issues" src="https://img.shields.io/github/issues/bitcookies/winrar-keygen?color=F48D73" />
  </a>
  <img src="https://img.shields.io/badge/Visual%20Studio-2019-blueviolet" />
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

## 3. 如何编译？

如果你不想自己编译，也可以到 [Release](https://github.com/bitcookies/winrar-keygen/releases/) 页面获取对应版本的 `winrar-keygen.exe`。

### 3.1 前提条件

1. 请确保你有 __Visual Studio 2019__ 或其更高版本。因为这是一个VS2019项目。

2. 请确保你安装了 `vcpkg` 以及下面几个库：

   * `mpir:x86-windows-static`
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

### 3.2 编译

1. 在 __Visual Studio__ 中打开这个项目。

2. 选择 `Release` 配置。

3. 选择 __生成 > 生成解决方案__。

## 4. 如何使用？

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

![Terminal](terminal.png)

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

将生成的信息以文本格式保存为 `rarreg.key ` ，拖动导入 WinRAR 即可。

## 5. 无效的Key

为什么我生成的 `rarreg.key` 是无效的？

### 5.1 包含非英文字符

如果 `text1` 和 `text2` 参数包含**非英文字符**，即使 WinRAR Keygen 能够生成 `rarreg.key`，但是是无效的。

```console
winrar-keygen.exe <text1> <text2>
```

### 5.2 终端编码的问题

有可能是终端编码的问题，你可以使用 `chcp` 命令暂时切换。

具体可参考 Microsoft 文档：[chcp | Microsoft Docs](https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/chcp)

## 6. 遇到问题

### 6.1 反馈

如果您遇到了一些问题，可在 [Issues](https://github.com/bitcookies/winrar-keygen/issues) 页面反馈，会有很多热心的开发者及 Github 用户帮助你。

### 6.2 安全

一些杀毒软件可能会误报，如果您不信任此二进制可执行文件，您唯一的选择就是自己编译代码。

### 6.3 感谢

非常感谢一些热心的开发者，在 [Issues](https://github.com/bitcookies/winrar-keygen/issues) 帮助解答一些问题。

感谢 [@Sonic-The-Hedgehog-LNK1123](https://github.com/Sonic-The-Hedgehog-LNK1123) 和 [@nitu2003](https://github.com/nitu2003).

## 7. 关于WinRAR广告

在 [__RARLAB__](https://www.rarlab.com/) 下载的简体中文版 WinRAR 将会自带广告组件，即使使用了 `rarreg.key` 授权，广告组件依旧会出现。如果您介意广告，可以尝试下载其他语言版。

## 8. 许可

使用 [MIT License](https://github.com/bitcookies/winrar-keygen/blob/master/LICENSE)
