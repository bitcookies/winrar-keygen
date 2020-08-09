[GF2-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20%5Ctextrm%7BGF%7D%282%29
[GF2p15-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20%5Ctextrm%7BGF%7D%282%5E%7B15%7D%29
[GF2p15p17-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20%5Ctextrm%7BGF%7D%28%282%5E%7B15%7D%29%5E%7B17%7D%29
[A-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20A
[B-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20B
[D-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20D
[G-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20G
[M-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20M
[P-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20P
[h-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20h
[k-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20k
[l-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20l
[n-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20n
[r-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20r
[s-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20s
[T-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20T
[UU-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20U
[LL-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20L
[Rnd-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20Rnd
[Temp-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20Temp
[UID-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20UID
[Data-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20Data
[Data0-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20Data%5E0
[Data1-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20Data%5E1
[Data2-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20Data%5E2
[Data3-inlined]: http://latex.codecogs.com/svg.latex?%5Cinline%20Data%5E3

# "rarreg.key"是如何生成的？

WinRAR使用了基于ECC的签名算法来生成 `rarreg.key` 文件，其使用的签名算法是中国SM2数字签名算法的变体。与各种标准ECDSA不同的是，WinRAR使用的椭圆曲线是一个基于复合域 ![GF2p15p17-inlined] 上的曲线。

## 1. 复合域 ![GF2p15p17-inlined]

基域 ![GF2p15-inlined] 采用标准基（多项式基）来表达，采用的不可约多项式为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?P%28%5Calpha%29%3D%5Calpha%5E%7B15%7D&plus;%5Calpha&plus;1")
</p>

各项系数全部位于 ![GF2-inlined]。设基域的标准基为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?B_1%3D%5C%7B1%2C%5Calpha%2C%5Calpha%5E2%2C%5Cldots%2C%5Calpha%5E%7B14%7D%5C%7D")
</p>

则位于基域 ![GF2p15-inlined] 上的元素 ![A-inlined] 可以用如下方式表达：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?A%3D%5Csum_%7Bi%3D0%7D%5E%7B14%7Da_i%5Calpha%5Ei%20%5Cquad%20%5Cquad%20%5Cquad%20a_i%5Cin%5Ctextrm%7BGF%7D%282%29")
</p>

---

复合域 ![GF2p15p17-inlined] 的不可约多项式为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?Q%28%5Cbeta%29%3D%5Cbeta%5E%7B17%7D&plus;%5Cbeta%5E3&plus;1")
</p>

各项系数全部位于 ![GF2p15-inlined]。设复合域的标准基为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?B_2%3D%5C%7B1%2C%5Cbeta%2C%5Cbeta%5E2%2C%5Cldots%2C%5Cbeta%5E%7B16%7D%5C%7D")
</p>

则位于复合域 ![GF2p15p17-inlined] 上的元素 ![B-inlined] 可以用如下方式表达：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?B%3D%5Csum_%7Bj%3D0%7D%5E%7B16%7D%28%5Csum_%7Bi%3D0%7D%5E%7B14%7Da_%7Bj%2Ci%7D%5Calpha%5Ei%29%5Cbeta%5Ej%3D%5Csum_%7Bj%3D0%7D%5E%7B16%7D%5Csum_%7Bi%3D0%7D%5E%7B14%7Da_%7Bj%2Ci%7D%5Calpha%5Ei%5Cbeta%5Ej%20%5Cquad%20%5Cquad%20%5Cquad%20a_%7Bj%2Ci%7D%5Cin%5Ctextrm%7BGF%7D%282%29")
</p>

---

为了方便表述我们用255比特的大数 ![D-inlined] 来表示位于复合域 ![GF2p15p17-inlined] 上的元素 ![B-inlined]。它们的对应关系为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?B%3D%5Csum_%7Bj%3D0%7D%5E%7B16%7D%5Csum_%7Bi%3D0%7D%5E%7B14%7Da_%7Bj%2Ci%7D%5Calpha%5Ei%5Cbeta%5Ej%20%5Cleftrightarrow%20D%3D%5Csum_%7Bj%3D0%7D%5E%7B16%7D%5Csum_%7Bi%3D0%7D%5E%7B14%7Da_%7Bj%2Ci%7D%5Ccdot%202%5E%7B15j&plus;i%7D")
</p>

## 2. 复合域 ![GF2p15p17-inlined] 上的椭圆曲线

曲线方程为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?y%5E2&plus;xy%3Dx%5E3&plus;161%20%5Cquad%20%5Cquad%20%5Cquad%20161%5Cin%5Ctextrm%7BGF%7D%28%282%5E%7B15%7D%29%5E%7B17%7D%29")
</p>

基点 ![G-inlined] 为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?%5Cbegin%7Baligned%7D%20G%26%3D%28G_x%2CG_y%29%20%5C%5C%20G_x%26%3D%5Ctextrm%7B0x56fdcbc6a27acee0cc2996e0096ae74feb1acf220a2341b898b549440297b8cc%7D%20%5Cquad%20G_x%5Cin%5Ctextrm%7BGF%7D%28%282%5E%7B15%7D%29%5E%7B17%7D%29%5C%5C%20G_y%26%3D%5Ctextrm%7B0x20da32e8afc90b7cf0e76bde44496b4d0794054e6ea60f388682463132f931a7%7D%20%5Cquad%20G_y%5Cin%5Ctextrm%7BGF%7D%28%282%5E%7B15%7D%29%5E%7B17%7D%29%20%5Cend%7Baligned%7D")
</p>

基点 ![G-inlined] 的阶 ![n-inlined] 为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?n%3D%5Ctextrm%7B0x1026dd85081b82314691ced9bbec30547840e4bf72d8b5e0d258442bbcd31%7D%20%5Cquad%20n%5Cin%5Cnolinebreak%5Cmathbb%7BZ%7D")
</p>

## 3. 消息哈希算法

设长度为 ![l-inlined] 的消息为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?M%3Dm_0m_1%20%5Cldots%20m_%7Bl-1%7D%20%5Cquad%20%5Cquad%20m_i%5Cin%5B0%2C%20256%29")
</p>

则消息 ![M-inlined] 的SHA1值为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?%5Ctextrm%7BSHA%7D_1%28M%29%3DS_0%7C%7CS_1%7C%7CS_2%7C%7CS_3%7C%7CS_4%20%5Cquad%20%5Cquad%20S_i%5Cin%5B0%2C%202%5E%7B32%7D%29")
</p>

其中 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20S_0%2CS_1%2CS_2%2CS_3%2CS_4) 为SHA1算法输出时的5个状态值；将这5个状态值按照大端字节序依次输出，即为的SHA1哈希值 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20%5Ctextrm%7BSHA%7D_1%28M%29)。

WinRAR在做完SHA1计算后，采用大数 ![h-inlined] 作为ECC签名时消息的哈希：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?h%3D%28%5Csum_%7Bi%3D0%7D%5E%7B4%7DS_i%20%5Ccdot%202%5E%7B32i%7D%29&plus;%5Ctextrm%7B0x1bd10xb4e33c7c0ffd8d43%7D%20%5Ccdot%202%5E%7B32*5%7D")
</p>


## 4. ECC签名算法

设私钥为 ![k-inlined]，公钥为 ![P-inlined]，即：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?P%3Dk%20%5Ccdot%20G")
</p>

消息哈希为 ![h-inlined]，则签名 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20%28r%2Cs%29) 为：

1. 生成随机数 ![Rnd-inlined]，满足 ![](http://latex.codecogs.com/svg.latex?%5Cinline%200%3CRnd%3Cn)。

2. 计算 ![r-inlined]

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?r%3D%28%28Rnd%20%5Ccdot%20G%29_x&plus;h%29%5C%20%5C%20Mod%5C%20%5C%20n">
   </p>

   其中 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20%28Rnd%20%5Ccdot%20G%29_x) 表示取 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20Rnd%20%5Ccdot%20G) 的X坐标，同时将X坐标从 ![GF2p15p17-inlined] 转换为大数。

   若 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r%3D0) 或者 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r&plus;Rnd%3Dn) 则回到步骤1。

3. 计算 ![s-inlined]

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?s%3D%28Rnd-kr%29%5C%20%5C%20Mod%5C%20%5C%20n">
   </p>

   若 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20s%3D0) 则回到步骤1。

4. 输出 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20%28r%2Cs%29)。

## 5. WinRAR的私钥生成算法

该算法会利用长度为 ![l-inlined] 的数据 

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?T%3Dt_0t_1%20%5Cldots%20t_%7Bl-1%7D%20%5Cquad%20%5Cquad%20t_i%5Cin%5B0%2C256%29">
</p>

来生成私钥 ![k-inlined]。

1. 设6个32位整数为 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20g_0%2Cg_1%2Cg_2%2Cg_3%2Cg_4%2Cg_5)，则有

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?g_j%3D%5Csum_%7Bi%3D0%7D%5E%7B3%7Dg_%7Bj%2Ci%7D%20%5Ccdot%202%5E%7B8i%7D%20%5Cquad%20%5Cquad%20g_%7Bj%2Ci%7D%5Cin%5B0%2C256%29">
   </p>

2. 令 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20g_0%3D0)。

3. 如果 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20l%5Cneq%200) 则计算 ![T-inlined] 的SHA1值，并将状态值 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20S_i) 赋值给 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20g_%7Bi&plus;1%7D)：

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?%5Cbegin%7Baligned%7D%20%5Ctextrm%7BSHA%7D_1%28T%29%26%3DS_0%7C%7CS_1%7C%7CS_2%7C%7CS_3%7C%7CS_4%20%5C%5C%20g_1%26%3DS_0%20%5C%5C%20g_2%26%3DS_1%20%5C%5C%20g_3%26%3DS_2%20%5C%5C%20g_4%26%3DS_3%20%5C%5C%20g_5%26%3DS_4%20%5C%5C%20%5Cend%7Baligned%7D">
   </p>

   否则，即 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20l%3D0) 时，令：

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?%5Cbegin%7Baligned%7D%20g_1%26%3D%5Ctextrm%7B0xeb3eb781%7D%20%5C%5C%20g_2%26%3D%5Ctextrm%7B0x50265329%7D%20%5C%5C%20g_3%26%3D%5Ctextrm%7B0xdc5ef4a3%7D%20%5C%5C%20g_4%26%3D%5Ctextrm%7B0x6847b9d5%7D%20%5C%5C%20g_5%26%3D%5Ctextrm%7B0xcde43b4c%7D%20%5C%5C%20%5Cend%7Baligned%7D">
   </p>

4. 把 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20g_0) 作为计数器，自增1。

   计算SHA1值：

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?%5Ctextrm%7BSHA%7D_1%28g_%7B0%2C0%7D%7C%7Cg_%7B0%2C1%7D%7C%7Cg_%7B0%2C2%7D%7C%7Cg_%7B0%2C3%7D%7C%7Cg_%7B1%2C0%7D%7C%7Cg_%7B1%2C1%7D%7C%7C%5Cldots%7C%7Cg_%7B5%2C0%7D%7C%7Cg_%7B5%2C1%7D%7C%7Cg_%7B5%2C2%7D%7C%7Cg_%7B5%2C3%7D%29%3DS_0%7C%7CS_1%7C%7CS_2%7C%7CS_3%7C%7CS_4">
   </p>

   取 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20S_0) 的低16位并记为 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20k_%7Bg_0%7D)。

5. 步骤4再重复14次。

6. 重复执行完后会得到 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20k_1%2Ck_2%2Ck_3%2C%5Cldots%2Ck_%7B15%7D)，则输出私钥

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?k%3D%5Csum_%7Bi%3D1%7D%5E%7B15%7Dk_i%20%5Ccdot%202%5E%7B16i%7D">
   </p>

## 6. WinRAR的公钥和私钥

WinRAR的私钥 ![k-inlined] 为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?k%3D%5Ctextrm%7B0x59fe6abcca90bdb95f0105271fa85fb9f11f467450c1ae9044b7fd61d65e%7D%20%5Cquad%20%5Cquad%20k%5Cin%5Cnolinebreak%5Cmathbb%7BZ%7D">
</p>

该私钥是通过算法5生成的，其中数据 ![T-inlined] 的长度为0。

公钥 ![P-inlined] 为：

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?%5Cbegin%7Baligned%7D%20P%26%3D%28P_x%2CP_y%29%20%5C%5C%20P_x%26%3D%5Ctextrm%7B0x3861220ed9b36c9753df09a159dfb148135d495db3af8373425ee9a28884ba1a%7D%20%5Cquad%20P_x%5Cin%5Ctextrm%7BGF%7D%28%282%5E%7B15%7D%29%5E%7B17%7D%29%20%5C%5C%20P_y%26%3D%5Ctextrm%7B0x12b64e62db43a56114554b0cbd573379338cea9124c8443c4f50e6c8b013ec20%7D%20%5Cquad%20P_y%5Cin%5Ctextrm%7BGF%7D%28%282%5E%7B15%7D%29%5E%7B17%7D%29%20%5Cend%7Baligned%7D">
</p>

## 7. 授权文件"rarreg.key"的生成

授权文件的生成需要两个参数：

1. 用户名的ANSI字符串，不包括null-terminator；记为 

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?U%3Du_0u_1%20%5Cldots%20u_%7Bl-1%7D">
   </p>

2. 授权类型的ANSI字符串，不包括null-terminator；记为

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?L%3Dl_0l_1%20%5Cldots%20l_%7Bl-1%7D">
   </p>

`rarreg.key` 的生成算法如下：

1. 使用用户名 ![UU-inlined] 通过算法5计算出私钥 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20k_U) 以及公钥 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20P_U)，并将公钥 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20P_U) 按照SM2压缩公钥格式以Hex字符串（ASCII编码）的形式输出。得到的Hex字符串记为临时值 ![Temp-inlined]。

   ![Temp-inlined] 的长度应该为64；若长度不足，则在前面补字符`'0'`，直到长度为64。

2. 令字符串 ![Data3-inlined]为

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?Data%5E3%3D%5Ctexttt%7B%2260%22%7D%7C%7CTemp_0%7C%7CTemp_1%7C%7C%5Cldots%7C%7CTemp_%7B47%7D">
   </p>

3. 使用 ![Data3-inlined] 通过算法5计算出私钥 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20k_%7BData%5E3%7D) 以及公钥 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20P_%7BData%5E3%7D)，并将公钥 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20P_%7BData%5E3%7D) 按照SM2压缩公钥格式以Hex字符串（ASCII编码）的形式输出。得到的Hex字符串记为 ![Data0-inlined]。

   ![Data0-inlined] 的长度应该为64；若长度不足，则在前面补字符`'0'`，直到长度为64。

4. 令字符串 ![UID-inlined]为

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?UID%3DTemp_%7B48%7D%7C%7CTemp_%7B49%7D%7C%7C%5Cldots%7C%7CTemp_%7B63%7D%7C%7CData%5E0_0%7C%7CData%5E0_1%7C%7CData%5E0_2%7C%7CData%5E0_3">
   </p>

5. 对授权类型 ![LL-inlined] 使用算法4得到签名 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20%28r_L%2Cs_L%29)，其中私钥见第6节。

   要求 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r_L) 和 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20s_L) 的长度都不得超过240比特，否则重复该步骤。

6. 将 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r_L) 和 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20s_L) 以16进制形式输出（无`"0x"`前缀），分别记为 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Br_L%7D) 和 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Bs_L%7D)。

   若长度不满60，则在前面补字符`'0'`，直到长度为60。

7. 令字符串 ![Data1-inlined]为

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?Data%5E1%3D%5Ctexttt%7B%2260%22%7D%7C%7CSZ%5E%7Bs_L%7D%7C%7CSZ%5E%7Br_L%7D">
   </p>

8. 令字符串 ![Temp-inlined]为

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?Temp%3DU%7C%7CData%5E0">
   </p>

   对 ![Temp-inlined] 使用算法4得到签名 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20%28r_%7BTemp%7D%2Cs_%7BTemp%7D%29)，其中私钥见第6节。
   
   要求 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r_%7BTemp%7D) 和 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20s_%7BTemp%7D) 的长度都不得超过240比特，否则重复该步骤。

9. 将 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r_%7BTemp%7D) 和 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20s_%7BTemp%7D) 以16进制形式输出（无`"0x"`前缀），分别记为 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Br_%7BTemp%7D%7D) 和 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Bs_%7BTemp%7D%7D)。

   若长度不满60，则在前面补字符`'0'`，直到长度为60。

10. 令字符串 ![Data2-inlined]为

    <p align="center">
        <img src="http://latex.codecogs.com/svg.latex?Data%5E2%3D%5Ctexttt%7B%2260%22%7D%7C%7CSZ%5E%7Bs_%7BTemp%7D%7D%7C%7CSZ%5E%7Br_%7BTemp%7D%7D">
    </p>

11. 对

    <p align="center">
        <img src="http://latex.codecogs.com/svg.latex?L%7C%7CU%7C%7CData%5E0%7C%7CData%5E1%7C%7CData%5E2%7C%7CData%5E3">
    </p>

    计算CRC32值，最终校验和为CRC32值的反。将校验和以10进制形式输出，若长度不满10，则在前面补字符`'0'`，直到长度为10，记为 ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Bchecksum%7D)。

12. 令字符串 ![Data-inlined]为

    <p align="center">
        <img src="http://latex.codecogs.com/svg.latex?%5Cinline%20Data%3DData%5E0%7C%7CData%5E1%7C%7CData%5E2%7C%7CData%5E3%7C%7CSZ%5E%7Bchecksum%7D">
    </p>

13. 格式化输出。

    * 固定文件头`"RAR registration data"`，占一行。

    * 用户名，占一行。

    * 授权类型，占一行。

    * UID，占一行：

      <p align="center">
        <img src="http://latex.codecogs.com/svg.latex?%5Ctexttt%7B%22UID%3D%22%7D%7C%7CUID">
      </p>

    * 将 ![Data-inlined] 按照每行54个字符输出。

