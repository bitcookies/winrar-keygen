# "rarreg.key"是如何生成的？

WinRAR 使用了基于 ECC 的签名算法来生成 `rarreg.key` 文件，其使用的签名算法是中国 SM2 数字签名算法的变体。与各种标准 ECDSA 不同的是，WinRAR 使用的椭圆曲线是一个基于复合域 ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only) 上的曲线。

## 1. 复合域 ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only)

基域 ![GF2p15-inlined](assets/formula/GF2p15-inlined-light.svg#gh-light-mode-only)![GF2p15-inlined](assets/formula/GF2p15-inlined-dark.svg#gh-dark-mode-only) 采用标准基（多项式基）来表达，采用的不可约多项式为：

<p align="center">
    <img src="assets/formula/1-light.svg#gh-light-mode-only">
    <img src="assets/formula/1-dark.svg#gh-dark-mode-only">
</p>

各项系数全部位于 ![GF2-inlined](assets/formula/GF2-inlined-light.svg#gh-light-mode-only)![GF2-inlined](assets/formula/GF2-inlined-dark.svg#gh-dark-mode-only)。设基域的标准基为：

<p align="center">
    <img src="assets/formula/2-light.svg#gh-light-mode-only">
    <img src="assets/formula/2-dark.svg#gh-dark-mode-only">
</p>

则位于基域 ![GF2p15-inlined](assets/formula/GF2p15-inlined-light.svg#gh-light-mode-only)![GF2p15-inlined](assets/formula/GF2p15-inlined-dark.svg#gh-dark-mode-only) 上的元素 ![A](assets/formula/AA-inlined-light.svg#gh-light-mode-only)![A](assets/formula/AA-inlined-dark.svg#gh-dark-mode-only) 可以用如下方式表达：

<p align="center">
    <img src="assets/formula/3-light.svg#gh-light-mode-only">
    <img src="assets/formula/3-dark.svg#gh-dark-mode-only">
</p>

---

复合域 ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only) 的不可约多项式为：

<p align="center">
    <img src="assets/formula/4-light.svg#gh-light-mode-only">
    <img src="assets/formula/4-dark.svg#gh-dark-mode-only">
</p>

各项系数全部位于 ![GF2p15-inlined](assets/formula/GF2p15-inlined-light.svg#gh-light-mode-only)![GF2p15-inlined](assets/formula/GF2p15-inlined-dark.svg#gh-dark-mode-only)。设复合域的标准基为：

<p align="center">
    <img src="assets/formula/5-light.svg#gh-light-mode-only">
    <img src="assets/formula/5-dark.svg#gh-dark-mode-only">
</p>

则位于复合域 ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only) 上的元素 ![B](assets/formula/BB-inlined-light.svg#gh-light-mode-only)![B](assets/formula/BB-inlined-dark.svg#gh-dark-mode-only) 可以用如下方式表达：

<p align="center">
    <img src="assets/formula/6-light.svg#gh-light-mode-only">
    <img src="assets/formula/6-dark.svg#gh-dark-mode-only">
</p>

---

为了方便表述我们用255比特的大数 ![D](assets/formula/DD-inlined-light.svg#gh-light-mode-only)![D](assets/formula/DD-inlined-dark.svg#gh-dark-mode-only) 来表示位于复合域 ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only) 上的元素 ![B](assets/formula/BB-inlined-light.svg#gh-light-mode-only)![B](assets/formula/BB-inlined-dark.svg#gh-dark-mode-only)。它们的对应关系为：

<p align="center">
    <img src="assets/formula/7-light.svg#gh-light-mode-only">
    <img src="assets/formula/7-dark.svg#gh-dark-mode-only">
</p>

## 2. 复合域 ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only) 上的椭圆曲线

曲线方程为：

<p align="center">
    <img src="assets/formula/8-light.svg#gh-light-mode-only">
    <img src="assets/formula/8-dark.svg#gh-dark-mode-only">
</p>

基点 ![G](assets/formula/GG-inlined-light.svg#gh-light-mode-only)![G](assets/formula/GG-inlined-dark.svg#gh-dark-mode-only) 为：

<p align="center">
    <img src="assets/formula/9-light.svg#gh-light-mode-only">
    <img src="assets/formula/9-dark.svg#gh-dark-mode-only">
</p>

基点 ![G](assets/formula/GG-inlined-light.svg#gh-light-mode-only)![G](assets/formula/GG-inlined-dark.svg#gh-dark-mode-only) 的阶 ![n](assets/formula/n-inlined-light.svg#gh-light-mode-only)![n](assets/formula/n-inlined-dark.svg#gh-dark-mode-only) 为：

<p align="center">
    <img src="assets/formula/10-light.svg#gh-light-mode-only">
    <img src="assets/formula/10-dark.svg#gh-dark-mode-only">
</p>

## 3. 消息哈希算法

设长度为 ![l](assets/formula/l-inlined-light.svg#gh-light-mode-only)![l](assets/formula/l-inlined-dark.svg#gh-dark-mode-only) 的消息为：

<p align="center">
    <img src="assets/formula/11-light.svg#gh-light-mode-only">
    <img src="assets/formula/11-dark.svg#gh-dark-mode-only">
</p>

则消息 ![M](assets/formula/MM-inlined-light.svg#gh-light-mode-only)![M](assets/formula/MM-inlined-dark.svg#gh-dark-mode-only) 的 SHA1 值为：

<p align="center">
    <img src="assets/formula/12-light.svg#gh-light-mode-only">
    <img src="assets/formula/12-dark.svg#gh-dark-mode-only">
</p>

其中 ![s0,4](assets/formula/13-light.svg#gh-light-mode-only)![s0,4](assets/formula/13-dark.svg#gh-dark-mode-only) 为 SHA1 算法输出时的5个状态值；将这5个状态值按照大端字节序依次输出，即为的 SHA1 哈希值 ![SHA1M](assets/formula/14-light.svg#gh-light-mode-only)![SHA1M](assets/formula/14-dark.svg#gh-dark-mode-only)。

WinRAR 在做完 SHA1 计算后，采用大数 ![h](assets/formula/h-inlined-light.svg#gh-light-mode-only)![h](assets/formula/h-inlined-dark.svg#gh-dark-mode-only) 作为 ECC 签名时消息的哈希：

<p align="center">
    <img src="assets/formula/15-light.svg#gh-light-mode-only">
    <img src="assets/formula/15-dark.svg#gh-dark-mode-only">
</p>

## 4. ECC签名算法

设私钥为 ![k](assets/formula/k-inlined-light.svg#gh-light-mode-only)![k](assets/formula/k-inlined-dark.svg#gh-dark-mode-only)，公钥为 ![P](assets/formula/PP-inlined-light.svg#gh-light-mode-only)![P](assets/formula/PP-inlined-dark.svg#gh-dark-mode-only)，即：

<p align="center">
    <img src="assets/formula/16-light.svg#gh-light-mode-only">
    <img src="assets/formula/16-dark.svg#gh-dark-mode-only">
</p>

消息哈希为 ![h](assets/formula/h-inlined-light.svg#gh-light-mode-only)![h](assets/formula/h-inlined-dark.svg#gh-dark-mode-only)，则签名 ![(r,s)](assets/formula/17-light.svg#gh-light-mode-only)![(r,s)](assets/formula/17-dark.svg#gh-dark-mode-only) 为：

1. 生成随机数 ![Rnd](assets/formula/Rnd-inlined-light.svg#gh-light-mode-only)![Rnd](assets/formula/Rnd-inlined-dark.svg#gh-dark-mode-only)，满足 ![RND](assets/formula/18-light.svg#gh-light-mode-only)![RND](assets/formula/18-dark.svg#gh-dark-mode-only)。

2. 计算 ![r](assets/formula/r-inlined-light.svg#gh-light-mode-only)![r](assets/formula/r-inlined-dark.svg#gh-dark-mode-only)

   <p align="center">
       <img src="assets/formula/19-light.svg#gh-light-mode-only">
       <img src="assets/formula/19-dark.svg#gh-dark-mode-only">
   </p>


   其中 ![RNDGx](assets/formula/20-light.svg#gh-light-mode-only)![RNDGx](assets/formula/20-dark.svg#gh-dark-mode-only) 表示取 ![RNDG](assets/formula/21-light.svg#gh-light-mode-only)![RNDG](assets/formula/21-dark.svg#gh-dark-mode-only) 的 X 坐标，同时将 X 坐标从 ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only) 转换为大数。

   若 ![r=0](assets/formula/22-light.svg#gh-light-mode-only)![r=0](assets/formula/22-dark.svg#gh-dark-mode-only) 或者 ![rRnd](assets/formula/23-light.svg#gh-light-mode-only)![rRnd](assets/formula/23-dark.svg#gh-dark-mode-only) 则回到步骤1。

3. 计算 ![s](assets/formula/s-inlined-light.svg#gh-light-mode-only)![s](assets/formula/s-inlined-dark.svg#gh-dark-mode-only)

   <p align="center">
       <img src="assets/formula/24-light.svg#gh-light-mode-only">
       <img src="assets/formula/24-dark.svg#gh-dark-mode-only">
   </p>


   若 ![s=0](assets/formula/25-light.svg#gh-light-mode-only)![s=0](assets/formula/25-dark.svg#gh-dark-mode-only) 则回到步骤1。

4. 输出 ![(r,s)](assets/formula/17-light.svg#gh-light-mode-only)![(r,s)](assets/formula/17-dark.svg#gh-dark-mode-only)。

## 5. WinRAR的私钥生成算法

该算法会利用长度为 ![l](assets/formula/l-inlined-light.svg#gh-light-mode-only)![l](assets/formula/l-inlined-dark.svg#gh-dark-mode-only) 的数据 

<p align="center">
    <img src="assets/formula/26-light.svg#gh-light-mode-only">
    <img src="assets/formula/26-dark.svg#gh-dark-mode-only">
</p>

来生成私钥 ![k](assets/formula/k-inlined-light.svg#gh-light-mode-only)![k](assets/formula/k-inlined-dark.svg#gh-dark-mode-only)。

1. 设6个32位整数为 ![g0-5](assets/formula/27-light.svg#gh-light-mode-only)![g0-5](assets/formula/27-dark.svg#gh-dark-mode-only)，则有

   <p align="center">
       <img src="assets/formula/28-light.svg#gh-light-mode-only">
       <img src="assets/formula/28-dark.svg#gh-dark-mode-only">
   </p>

2. 令 ![g0=0](assets/formula/29-light.svg#gh-light-mode-only)![g0=0](assets/formula/29-dark.svg#gh-dark-mode-only)。

3. 如果 ![l!=0](assets/formula/30-light.svg#gh-light-mode-only)![l!=0](assets/formula/30-dark.svg#gh-dark-mode-only) 则计算 ![T](assets/formula/TT-inlined-light.svg#gh-light-mode-only)![T](assets/formula/TT-inlined-dark.svg#gh-dark-mode-only) 的 SHA1 值，并将状态值 ![Si](assets/formula/31-light.svg#gh-light-mode-only)![Si](assets/formula/31-dark.svg#gh-dark-mode-only) 赋值给 ![gi+1](assets/formula/32-light.svg#gh-light-mode-only)![gi+1](assets/formula/32-dark.svg#gh-dark-mode-only)：

   <p align="center">
       <img src="assets/formula/33-light.svg#gh-light-mode-only">
       <img src="assets/formula/33-dark.svg#gh-dark-mode-only">
   </p>


   否则，即 ![l=0](assets/formula/34-light.svg#gh-light-mode-only)![l=0](assets/formula/34-dark.svg#gh-dark-mode-only) 时，令：

   <p align="center">
       <img src="assets/formula/35-light.svg#gh-light-mode-only">
       <img src="assets/formula/35-dark.svg#gh-dark-mode-only">
   </p>

4. 把 ![g0](assets/formula/36-light.svg#gh-light-mode-only)![g0](assets/formula/36-dark.svg#gh-dark-mode-only)  作为计数器，自增1。

   计算 SHA1 值：

   <p align="center">
       <img src="assets/formula/37-light.svg#gh-light-mode-only">
       <img src="assets/formula/37-dark.svg#gh-dark-mode-only">
   </p>


   取 ![S0](assets/formula/38-light.svg#gh-light-mode-only)![S0](assets/formula/38-dark.svg#gh-dark-mode-only) 的低16位并记为 ![Kg0](assets/formula/39-light.svg#gh-light-mode-only)![Kg0](assets/formula/39-dark.svg#gh-dark-mode-only)。

5. 步骤4再重复14次。

6. 重复执行完后会得到 ![k1-15](assets/formula/40-light.svg#gh-light-mode-only)![k1-15](assets/formula/40-dark.svg#gh-dark-mode-only)，则输出私钥

   <p align="center">
       <img src="assets/formula/41-light.svg#gh-light-mode-only">
       <img src="assets/formula/41-dark.svg#gh-dark-mode-only">
   </p>

## 6. WinRAR的公钥和私钥

WinRAR 的私钥 ![k](assets/formula/k-inlined-light.svg#gh-light-mode-only)![k](assets/formula/k-inlined-dark.svg#gh-dark-mode-only) 为：

<p align="center">
    <img src="assets/formula/42-light.svg#gh-light-mode-only">
    <img src="assets/formula/42-dark.svg#gh-dark-mode-only">
</p>

该私钥是通过算法5生成的，其中数据 ![T](assets/formula/TT-inlined-light.svg#gh-light-mode-only)![T](assets/formula/TT-inlined-dark.svg#gh-dark-mode-only) 的长度为0。

公钥 ![P](assets/formula/PP-inlined-light.svg#gh-light-mode-only)![P](assets/formula/PP-inlined-dark.svg#gh-dark-mode-only) 为：

<p align="center">
    <img src="assets/formula/43-light.svg#gh-light-mode-only">
    <img src="assets/formula/43-dark.svg#gh-dark-mode-only">
</p>

## 7. 授权文件"rarreg.key"的生成

授权文件的生成需要两个参数：

1. 用户名的 ANSI 字符串，不包括 null-terminator；记为 

   <p align="center">
       <img src="assets/formula/44-light.svg#gh-light-mode-only">
       <img src="assets/formula/44-dark.svg#gh-dark-mode-only">
   </p>

2. 授权类型的 ANSI 字符串，不包括 null-terminator；记为

   <p align="center">
       <img src="assets/formula/45-light.svg#gh-light-mode-only">
       <img src="assets/formula/45-dark.svg#gh-dark-mode-only">
   </p>

`rarreg.key` 的生成算法如下：

1. 使用用户名 ![U](assets/formula/UU-inlined-light.svg#gh-light-mode-only)![U](assets/formula/UU-inlined-dark.svg#gh-dark-mode-only) 通过算法5计算出私钥 ![ku](assets/formula/46-light.svg#gh-light-mode-only)![ku](assets/formula/46-dark.svg#gh-dark-mode-only) 以及公钥 ![pu](assets/formula/47-light.svg#gh-light-mode-only)![pu](assets/formula/47-dark.svg#gh-dark-mode-only)，并将公钥 ![pu](assets/formula/47-light.svg#gh-light-mode-only)![pu](assets/formula/47-dark.svg#gh-dark-mode-only) 按照 SM2 压缩公钥格式以 Hex 字符串（ASCII编码）的形式输出。得到的 Hex 字符串记为临时值 ![Temp](assets/formula/Temp-inlined-light.svg#gh-light-mode-only)![Temp](assets/formula/Temp-inlined-dark.svg#gh-dark-mode-only)。

   ![Temp](assets/formula/Temp-inlined-light.svg#gh-light-mode-only)![Temp](assets/formula/Temp-inlined-dark.svg#gh-dark-mode-only) 的长度应该为64；若长度不足，则在前面补字符 `'0'`，直到长度为64。

2. 令字符串 ![Data3](assets/formula/Data3-inlined-light.svg#gh-light-mode-only)![Data3](assets/formula/Data3-inlined-dark.svg#gh-dark-mode-only) 为

   <p align="center">
       <img src="assets/formula/48-light.svg#gh-light-mode-only">
       <img src="assets/formula/48-dark.svg#gh-dark-mode-only">
   </p>

3. 使用 ![Data3](assets/formula/Data3-inlined-light.svg#gh-light-mode-only)![Data3](assets/formula/Data3-inlined-dark.svg#gh-dark-mode-only) 通过算法5计算出私钥 ![kdata3](assets/formula/49-light.svg#gh-light-mode-only)![kdata3](assets/formula/49-dark.svg#gh-dark-mode-only) 以及公钥 ![pdata3](assets/formula/50-light.svg#gh-light-mode-only)![pdata3](assets/formula/50-dark.svg#gh-dark-mode-only)，并将公钥 ![pdata3](assets/formula/50-light.svg#gh-light-mode-only)![pdata3](assets/formula/50-dark.svg#gh-dark-mode-only) 按照 SM2 压缩公钥格式以 Hex 字符串（ASCII编码）的形式输出。得到的 Hex 字符串记为 ![Data0](assets/formula/Data0-inlined-light.svg#gh-light-mode-only)![Data0](assets/formula/Data0-inlined-dark.svg#gh-dark-mode-only)。

   ![Data0](assets/formula/Data0-inlined-light.svg#gh-light-mode-only)![Data0](assets/formula/Data0-inlined-dark.svg#gh-dark-mode-only) 的长度应该为64；若长度不足，则在前面补字符 `'0'`，直到长度为64。

4. 令字符串 ![UID](assets/formula/UID-inlined-light.svg#gh-light-mode-only)![UID](assets/formula/UID-inlined-dark.svg#gh-dark-mode-only) 为

   <p align="center">
       <img src="assets/formula/51-light.svg#gh-light-mode-only">
       <img src="assets/formula/51-dark.svg#gh-dark-mode-only">
   </p>

5. 对授权类型 ![L](assets/formula/LL-inlined-light.svg#gh-light-mode-only)![L](assets/formula/LL-inlined-dark.svg#gh-dark-mode-only) 使用算法4得到签名 ![(rl,sl)](assets/formula/52-light.svg#gh-light-mode-only)![(rl,sl)](assets/formula/52-dark.svg#gh-dark-mode-only)，其中私钥见第6节。

   要求 ![rl](assets/formula/53-light.svg#gh-light-mode-only)![rl](assets/formula/53-dark.svg#gh-dark-mode-only) 和 ![sl](assets/formula/54-light.svg#gh-light-mode-only)![sl](assets/formula/54-dark.svg#gh-dark-mode-only) 的长度都不得超过240比特，否则重复该步骤。

6. 将 ![rl](assets/formula/53-light.svg#gh-light-mode-only)![rl](assets/formula/53-dark.svg#gh-dark-mode-only) 和 ![sl](assets/formula/54-light.svg#gh-light-mode-only)![sl](assets/formula/54-dark.svg#gh-dark-mode-only) 以16进制形式输出（无 `"0x"` 前缀），分别记为 ![SZrl](assets/formula/55-light.svg#gh-light-mode-only)![SZrl](assets/formula/55-dark.svg#gh-dark-mode-only) 和 ![SZsl](assets/formula/56-light.svg#gh-light-mode-only)![SZsl](assets/formula/56-dark.svg#gh-dark-mode-only)。

   若长度不满60，则在前面补字符 `'0'`，直到长度为60。

7. 令字符串 ![Data1](assets/formula/Data1-inlined-light.svg#gh-light-mode-only)![Data1](assets/formula/Data1-inlined-dark.svg#gh-dark-mode-only) 为

   <p align="center">
       <img src="assets/formula/57-light.svg#gh-light-mode-only">
       <img src="assets/formula/57-dark.svg#gh-dark-mode-only">
   </p>

8. 令字符串 ![Temp](assets/formula/Temp-inlined-light.svg#gh-light-mode-only)![Temp](assets/formula/Temp-inlined-dark.svg#gh-dark-mode-only) 为

   <p align="center">
       <img src="assets/formula/58-light.svg#gh-light-mode-only">
       <img src="assets/formula/58-dark.svg#gh-dark-mode-only">
   </p>


   对 ![Temp](assets/formula/Temp-inlined-light.svg#gh-light-mode-only)![Temp](assets/formula/Temp-inlined-dark.svg#gh-dark-mode-only) 使用算法4得到签名 ![(rTemp,sTemp)](assets/formula/59-light.svg#gh-light-mode-only)![(rTemp,sTemp)](assets/formula/59-dark.svg#gh-dark-mode-only)，其中私钥见第6节。

   要求 ![rTemp](assets/formula/60-light.svg#gh-light-mode-only)![rTemp](assets/formula/60-dark.svg#gh-dark-mode-only) 和 ![sTemp](assets/formula/61-light.svg#gh-light-mode-only)![sTemp](assets/formula/61-dark.svg#gh-dark-mode-only)  的长度都不得超过240比特，否则重复该步骤。

9. 将 ![rTemp](assets/formula/60-light.svg#gh-light-mode-only)![rTemp](assets/formula/60-dark.svg#gh-dark-mode-only) 和 ![sTemp](assets/formula/61-light.svg#gh-light-mode-only)![sTemp](assets/formula/61-dark.svg#gh-dark-mode-only) 以16进制形式输出（无 `"0x"` 前缀），分别记为 ![SZrTemp](assets/formula/62-light.svg#gh-light-mode-only)![SZrTemp](assets/formula/62-dark.svg#gh-dark-mode-only) 和 ![SZsTemp](assets/formula/63-light.svg#gh-light-mode-only)![SZsTemp](assets/formula/63-dark.svg#gh-dark-mode-only)。

   若长度不满60，则在前面补字符 `'0'`，直到长度为60。

10. 令字符串 ![Data2](assets/formula/Data2-inlined-light.svg#gh-light-mode-only)![Data2](assets/formula/Data2-inlined-dark.svg#gh-dark-mode-only) 为

    <p align="center">
        <img src="assets/formula/64-light.svg#gh-light-mode-only">
        <img src="assets/formula/64-dark.svg#gh-dark-mode-only">
    </p>

11. 对

    <p align="center">
        <img src="assets/formula/65-light.svg#gh-light-mode-only">
        <img src="assets/formula/65-dark.svg#gh-dark-mode-only">
    </p>

计算 CRC32 值，最终校验和为 CRC32 值的反。将校验和以10进制形式输出，若长度不满10，则在前面补字符 `'0'`，直到长度为10，记为 ![SZchecksum](assets/formula/66-light.svg#gh-light-mode-only)![SZchecksum](assets/formula/66-dark.svg#gh-dark-mode-only)。

12. 令字符串 ![Data](assets/formula/Data-inlined-light.svg#gh-light-mode-only)![Data](assets/formula/Data-inlined-dark.svg#gh-dark-mode-only) 为

    <p align="center">
        <img src="assets/formula/67-light.svg#gh-light-mode-only">
        <img src="assets/formula/67-dark.svg#gh-dark-mode-only">
    </p>

13. 格式化输出。

    * 固定文件头 `"RAR registration data"`，占一行。

    * 用户名，占一行。

    * 授权类型，占一行。

    * UID，占一行：

      <p align="center">
      	<img src="assets/formula/68-light.svg#gh-light-mode-only">
          <img src="assets/formula/68-dark.svg#gh-dark-mode-only">
      </p>
    
    * 将 ![Data](assets/formula/Data-inlined-light.svg#gh-light-mode-only)![Data](assets/formula/Data-inlined-dark.svg#gh-dark-mode-only) 按照每行54个字符输出。
