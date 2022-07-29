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


## 1. What is WinRAR?

WinRAR is a trialware file archiver utility for Windows, developed by Eugene Roshal of win.rar GmbH. 

It can create and view archives in RAR or ZIP file formats and unpack numerous archive file formats. 

WinRAR is not a free software. If you want to use it, you should pay to [__RARLAB__](https://www.rarlab.com/) and then you will get a license file named `rarreg.key`. 

This repository will tell you how WinRAR license file `"rarreg.key"` is generated. 

## 2. How is "rarreg.key" generated?

See [here](README.HOW_DOES_IT_WORK.md).

## 3. How to use?

There are several ways to use it:

- [Use Github Actions with Secrets](#4-Use-Github-Actions-with-Secrets) *<⭐ Recommend>*
- [Use Github Actions with Push](#5-Use-Github-Actions-with-Push)
- [Build in Visual Studio](#6-Build-in-Visual-Studio)

## 4. Use Github Actions with Secrets

<details>
<summary>Click to expand</summary>


Use [Secrets](https://docs.github.com/en/actions/security-guides/encrypted-secrets) you don't need to commits to the repository, so you can fetch upstream without conflicts. So I recommend using this method.

### 4.1 Fork

**Fork** this repo.

![Fork](assets/fork-light.png#gh-light-mode-only)

![Fork](assets/fork-dark.png#gh-dark-mode-only)

### 4.2 Creating Secrets

Open your forked repository, and go to **Settings > Secrets > Actions > New repository secret**.

![Secrets](assets/secrets-light.png#gh-light-mode-only)

![Secrets](assets/secrets-dark.png#gh-dark-mode-only)

Create two Secrets named `text1` and `text2` and fill in values.

![Add Secrets](assets/secrets-add-light.png#gh-light-mode-only)

![Add Secrets](assets/secrets-add-dark.png#gh-dark-mode-only)

Once created, you will see:

![Secrets Repo](assets/secrets-repo-light.png#gh-light-mode-only)

![Secrets Repo](assets/secrets-repo-dark.png#gh-dark-mode-only)

### 4.3 Run Workflow

Go to **Actions** and select **WinRAR Keygen Secrets** to run Workflow manually.

![Run](assets/run-workflow-light.png#gh-light-mode-only)

![Run](assets/run-workflow-dark.png#gh-dark-mode-only)

After running successfully, open the corresponding task and select **rarreg_file** to download.

![Download](assets/file-download-light.png##gh-light-mode-only)

![Download](assets/file-download-dark.png#gh-dark-mode-only)

</details>

## 5. Use Github Actions with Push

<details>
<summary>Click to expand</summary>

Using push for key generation is very simple and convenient, but when there are updates to fetch upstream, you need to manually merge conflicts. So I would recommend [Use Github Actions with Secrets](#4-Use-Github-Actions-with-Secrets), but you can still use the push action.

### 5.1 Fork

**Fork** this repo.

![Fork](assets/fork-light.png#gh-light-mode-only)

![Fork](assets/fork-dark.png#gh-dark-mode-only)

If you've forked before and I've committed new code, but you don't know how to merge the new content into your repository, then you can delete the current fork and fork again.

### 5.2 Modify info.json

Open your forked repository, and go to `keygen/info.json` and click on the edit button to edit the file.

![Edit](assets/edit-json-light.png#gh-light-mode-only)

![Edit](assets/edit-json-dark.png#gh-dark-mode-only)

You can see:

```json
{
    "text1": "Github",
    "text2": "Github.com"
}
```

You can modify the values corresponding to `text1` and `text2`:

```json
{
    "text1": "Your Name",
    "text2": "Your License"
}
```

It is important to note that `test1` and `test2` are **ANSI-encoded string, space are now supported.**

Once you have finished making changes, click the **Commit changes** button and Github Actions will start automatically.

If Github Actions does not start automatically, you will need to click on the Actions page to **allow this workflows to run**, then modify and commit `keygen/info.json` again.

![Workflow](assets/enable-workflows-light.png#gh-light-mode-only)

![Workflow](assets/enable-workflows-dark.png#gh-dark-mode-only)

### 5.3 Download Key

Go to **Actions** and select **WinRAR Keygen** to see the status of the program.

![Workflow](assets/push-workflows-light.png#gh-light-mode-only)

![Workflow](assets/push-workflows-dark.png#gh-dark-mode-only)

Green means it ran successfully, yellow means it is running, red means it failed. After running successfully, open the corresponding task and select **rarreg_file** to download.

![Download](assets/file-download-light.png##gh-light-mode-only)

![Download](assets/file-download-dark.png#gh-dark-mode-only)

After extract `rarreg_file.zip`, you will get `rarreg.key`, just drag and drop it into WinRAR.

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

   ```console
   $ vcpkg install mpir:x86-windows-static
   $ vcpkg install mpir:x64-windows-static
   ```

3. Your `vcpkg` has been integrated into your __Visual Studio__, which means you have run successfully.

   ```console
   $ vcpkg integrate install
   ```
   

### 6.2 Build

1. Open this project in __Visual Studio__.

2. Select `Release` configuration.

3. Select __Build > Build Solution__.

You will see executable files in `bin/` directory. 

### 6.3 How to Use?

Execute the following code in the terminal and configure two parameters to generate `rarreg.key`.

Here is an example use `Github` and `Github.com`:

```
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

Now you can see the newly generated file:

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

Save the generated information in **ANSI encoding format** as `rarreg.key`.

</details>

## 7. Invalid Key

Why is my `rarreg.key` invalid?

### 7.1 ANSI Encoded

`test1` and `test2` are **ANSI-encoded string, space are now supported** [Issues #5](https://github.com/bitcookies/winrar-keygen/issues/5).

```console
winrar-keygen.exe <text1> <text2>
```

You can refer to: [Generation of "rarreg.key"](https://github.com/bitcookies/winrar-keygen/blob/master/README.HOW_DOES_IT_WORK.md#7-generation-of-rarregkey)

### 7.2 TXT Encoding

If you use the following command:

```console
winrar-keygen.exe "Github" "Github.com" > rarreg.key
```

In the newer Windows 10, PowerShell will export in **UTF16-LE** format by default, which will cause the error.

Please use the following command:

```console
winrar-keygen.exe "Github" "Github.com" | Out-File -Encoding ASCII rarreg.key
```

### 7.3 Location of Key

If you are unable to drag, you can try to put the `rarreg.key` in the following directory.

```console
C:\Users\yourname\AppData\Roaming\WinRAR\rarreg.key
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
