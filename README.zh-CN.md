# WinRAR-Keygen

[README for English](README.md)

<p align='center'><img width="100px" src="icon1.png" /></p>

## 1. WinRAR是什么？

WinRAR是一款用于管理压缩包文件的共享软件。其算法由作者尤金·罗谢尔研发，享有原创专利。

它可以用来创建或浏览RAR、ZIP等众多格式的压缩包。

WinRAR不是免费的软件。如果你想使用它，你应当向 [__RARLAB__](https://rarlab.com/) 付费，然后获得一个授权文件 `rarreg.key`。

这份repo将会告诉你 `rarreg.key` 是如何生成的。

## 2. "rarreg.key"是如何生成的？

见 [这里](README.HOW_DOES_IT_WORK.zh-CN.md)。

## 3. 如何编译？

如果你不想自己编译，也可以到 [Release](https://github.com/bitcookies/winrar-keygen/releases/) 页面获取 `winrar-keygen.exe`。

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

```
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

将生成的信息以文本格式保存为 `rarreg.key ` ，拖动即可导入WinRAR。