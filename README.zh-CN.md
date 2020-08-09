# WinRAR-Keygen

[README for English](README.md)

<center><img src="icon1.png" alt="icon1" width="18%"></center>

## 1. WinRAR是什么？

WinRAR是一款用于管理压缩包文件的共享软件。其算法由作者尤金·罗谢尔研发，享有原创专利。

它可以用来创建或浏览RAR、ZIP等众多格式的压缩包。

WinRAR不是免费的软件。如果你想使用它，你应当向 [__RARLAB__](https://rarlab.com/) 付费，然后获得一个授权文件 `rarreg.key`。

这份repo将会告诉你 `rarreg.key` 是如何生成的。

## 2. "rarreg.key"是如何生成的？

见 [这里](README.HOW_DOES_IT_WORK.zh-CN.md)。

## 3. 如何编译？

如果你不想自己编译，也可以到 [release](https://github.com/bitcookies/winrar-keygen/release) 页面获取 `winrar-keygen.exe`。

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

```
Usage:
        winrar-keygen.exe <your name> <license type>

Example:

        winrar-keygen.exe "Rebecca Morrison" "Single PC usage license"
  or:
        winrar-keygen.exe "Rebecca Morrison" "Single PC usage license" > rarreg.key
```

现在你可以看到新生成的文件，将生成的信息保存为 `rarreg.key ` 即可：

```console
$ winrar-keygen.exe "DoubleLabyrinth" "Single PC usage license"
RAR registration data
DoubleLabyrinth
Single PC usage license
UID=d2fb7cb15c078a3def58
6412212250ef58bef21cdcb49ca34b7040112cae5a512f1adad1a8
f6d2ee8c382fe64f8e3d6035c6ab9048e2c5c62f0238f183d28519
aa87488bf38f5b634cf28190bdf438ac593b1857cdb55a7fcb0eb0
c3e4c2736090b3dfa45384e08e9de05c5860d3051942adf2db9d96
e2ec37f1cfae00b3e2455093b90e4e352f016f6b9853c735d45fb4
01f9cbb91d3f3ac5664511229f8c9b0a9e1d61a2e087b481607e91
bfc8a83414f6807d31a5f8c587513aa54f9b1249ad804214409316
```
