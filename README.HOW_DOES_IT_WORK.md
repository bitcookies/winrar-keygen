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

# How is "rarreg.key" generated?

WinRAR uses an ECC-based signature algorithm to generate `rarreg.key`. The algorithm it used is a variant of Chinese SM2 digital signature algorithm. Different to many standard ECDSAs, the curve that WinRAR selected is a curve over composite field ![GF2p15p17-inlined].

## 1. Composite field ![GF2p15p17-inlined]

Elements in ground field ![GF2p15-inlined] are represented with standard basis, i.e. polynomial basis. The irreducible polynomial is

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?P%28%5Calpha%29%3D%5Calpha%5E%7B15%7D&plus;%5Calpha&plus;1")
</p>

where each coefficients is in ![GF2-inlined]. If we use 

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?B_1%3D%5C%7B1%2C%5Calpha%2C%5Calpha%5E2%2C%5Cldots%2C%5Calpha%5E%7B14%7D%5C%7D")
</p>

as the standard basis of the ground field, an element ![A-inlined] in ![GF2p15-inlined] can be denoted as

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?A%3D%5Csum_%7Bi%3D0%7D%5E%7B14%7Da_i%5Calpha%5Ei%20%5Cquad%20%5Cquad%20%5Cquad%20a_i%5Cin%5Ctextrm%7BGF%7D%282%29")
</p>

---

The irreducible polynomial of composite field ![GF2p15p17-inlined] is

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?Q%28%5Cbeta%29%3D%5Cbeta%5E%7B17%7D&plus;%5Cbeta%5E3&plus;1")
</p>

where each coefficients is in ![GF2p15-inlined]. If we use 

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?B_2%3D%5C%7B1%2C%5Cbeta%2C%5Cbeta%5E2%2C%5Cldots%2C%5Cbeta%5E%7B16%7D%5C%7D")
</p>

as the standard basis of the composite field, an element ![B-inlined] in ![GF2p15p17-inlined] can be denoted as

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?B%3D%5Csum_%7Bj%3D0%7D%5E%7B16%7D%28%5Csum_%7Bi%3D0%7D%5E%7B14%7Da_%7Bj%2Ci%7D%5Calpha%5Ei%29%5Cbeta%5Ej%3D%5Csum_%7Bj%3D0%7D%5E%7B16%7D%5Csum_%7Bi%3D0%7D%5E%7B14%7Da_%7Bj%2Ci%7D%5Calpha%5Ei%5Cbeta%5Ej%20%5Cquad%20%5Cquad%20%5Cquad%20a_%7Bj%2Ci%7D%5Cin%5Ctextrm%7BGF%7D%282%29")
</p>

---

For clarity, we use ![D-inlined], which is a 255-bits-long integer to denote an element ![B-inlined] in ![GF2p15p17-inlined]. The map between them is

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?B%3D%5Csum_%7Bj%3D0%7D%5E%7B16%7D%5Csum_%7Bi%3D0%7D%5E%7B14%7Da_%7Bj%2Ci%7D%5Calpha%5Ei%5Cbeta%5Ej%20%5Cleftrightarrow%20D%3D%5Csum_%7Bj%3D0%7D%5E%7B16%7D%5Csum_%7Bi%3D0%7D%5E%7B14%7Da_%7Bj%2Ci%7D%5Ccdot%202%5E%7B15j&plus;i%7D")
</p>

## 2. Elliptic curve over ![GF2p15p17-inlined]

The equation of the elliptic curve that WinRAR uses is

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?y%5E2&plus;xy%3Dx%5E3&plus;161%20%5Cquad%20%5Cquad%20%5Cquad%20161%5Cin%5Ctextrm%7BGF%7D%28%282%5E%7B15%7D%29%5E%7B17%7D%29")
</p>

The base point ![G-inlined] is

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?%5Cbegin%7Baligned%7D%20G%26%3D%28G_x%2CG_y%29%20%5C%5C%20G_x%26%3D%5Ctextrm%7B0x56fdcbc6a27acee0cc2996e0096ae74feb1acf220a2341b898b549440297b8cc%7D%20%5Cquad%20G_x%5Cin%5Ctextrm%7BGF%7D%28%282%5E%7B15%7D%29%5E%7B17%7D%29%5C%5C%20G_y%26%3D%5Ctextrm%7B0x20da32e8afc90b7cf0e76bde44496b4d0794054e6ea60f388682463132f931a7%7D%20%5Cquad%20G_y%5Cin%5Ctextrm%7BGF%7D%28%282%5E%7B15%7D%29%5E%7B17%7D%29%20%5Cend%7Baligned%7D")
</p>

whose order ![n-inlined] is

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?n%3D%5Ctextrm%7B0x1026dd85081b82314691ced9bbec30547840e4bf72d8b5e0d258442bbcd31%7D%20%5Cquad%20n%5Cin%5Cnolinebreak%5Cmathbb%7BZ%7D")
</p>

## 3. Message hash algorithm

We use 

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?M%3Dm_0m_1%20%5Cldots%20m_%7Bl-1%7D%20%5Cquad%20%5Cquad%20m_i%5Cin%5B0%2C%20256%29")
</p>

to denote a message whose length is ![l-inlined]. So the SHA1 value of ![M-inlined] should be 

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?%5Ctextrm%7BSHA%7D_1%28M%29%3DS_0%7C%7CS_1%7C%7CS_2%7C%7CS_3%7C%7CS_4%20%5Cquad%20%5Cquad%20S_i%5Cin%5B0%2C%202%5E%7B32%7D%29")
</p>

where ![](http://latex.codecogs.com/svg.latex?%5Cinline%20S_0%2CS_1%2CS_2%2CS_3%2CS_4) are 5 state values when SHA1 outputs. Generally speaking, the final SHA1 value should be the join of these 5 state values while each of state values is serialized in big-endian.

However, WinRAR doesn't serialize the 5 state values. Instead, it use a big integer ![h-inlined] as the hash of the input message.

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?h%3D%28%5Csum_%7Bi%3D0%7D%5E%7B4%7DS_i%20%5Ccdot%202%5E%7B32i%7D%29&plus;%5Ctextrm%7B0x1bd10xb4e33c7c0ffd8d43%7D%20%5Ccdot%202%5E%7B32*5%7D")
</p>

## 4. ECC digital signature algorithm

We use ![k-inlined] to denote private key, ![P-inlined] to denote public key. So there must be

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?P%3Dk%20%5Ccdot%20G")
</p>

If we use ![h-inlined] to denote the hash of input data, WinRAR use the following algorithm to perform signing:

1. Generate a random big integer ![Rnd-inlined] which satisfies ![](http://latex.codecogs.com/svg.latex?%5Cinline%200%3CRnd%3Cn).

2. Calculate ![r-inlined]

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?r%3D%28%28Rnd%20%5Ccdot%20G%29_x&plus;h%29%5C%20%5C%20Mod%5C%20%5C%20n">
   </p>

   where ![](http://latex.codecogs.com/svg.latex?%5Cinline%20%28Rnd%20%5Ccdot%20G%29_x) means we take X coordinate of ![](http://latex.codecogs.com/svg.latex?%5Cinline%20Rnd%20%5Ccdot%20G) and convert it from ![GF2p15p17-inlined] to a big integer.

   If ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r%3D0) or ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r&plus;Rnd%3Dn), go back to step 1.

3. Calculate ![s-inlined]

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?s%3D%28Rnd-kr%29%5C%20%5C%20Mod%5C%20%5C%20n">
   </p>

   If ![](http://latex.codecogs.com/svg.latex?%5Cinline%20s%3D0), go back to step 1.

4. Output ![](http://latex.codecogs.com/svg.latex?%5Cinline%20%28r%2Cs%29).

## 5. WinRAR private key generation algorithm

We use 

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?T%3Dt_0t_1%20%5Cldots%20t_%7Bl-1%7D%20%5Cquad%20%5Cquad%20t_i%5Cin%5B0%2C256%29">
</p>

to denote input data whose length is ![l-inlined]. WinRAR use it to generate private key ![k-inlined].

1. We use ![](http://latex.codecogs.com/svg.latex?%5Cinline%20g_0%2Cg_1%2Cg_2%2Cg_3%2Cg_4%2Cg_5) to denote 6 32-bits-long integer. So there is

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?g_j%3D%5Csum_%7Bi%3D0%7D%5E%7B3%7Dg_%7Bj%2Ci%7D%20%5Ccdot%202%5E%7B8i%7D%20%5Cquad%20%5Cquad%20g_%7Bj%2Ci%7D%5Cin%5B0%2C256%29">
   </p>

2. Let ![](http://latex.codecogs.com/svg.latex?%5Cinline%20g_0%3D0).

3. If ![](http://latex.codecogs.com/svg.latex?%5Cinline%20l%5Cneq%200), we calculate SHA1 value of ![T-inlined]. Then assign SHA1 state value ![](http://latex.codecogs.com/svg.latex?%5Cinline%20S_i) to ![](http://latex.codecogs.com/svg.latex?%5Cinline%20g_%7Bi&plus;1%7D):

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?%5Cbegin%7Baligned%7D%20%5Ctextrm%7BSHA%7D_1%28T%29%26%3DS_0%7C%7CS_1%7C%7CS_2%7C%7CS_3%7C%7CS_4%20%5C%5C%20g_1%26%3DS_0%20%5C%5C%20g_2%26%3DS_1%20%5C%5C%20g_3%26%3DS_2%20%5C%5C%20g_4%26%3DS_3%20%5C%5C%20g_5%26%3DS_4%20%5C%5C%20%5Cend%7Baligned%7D">
   </p>

   Otherwise, when ![](http://latex.codecogs.com/svg.latex?%5Cinline%20l%3D0), we let 

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?%5Cbegin%7Baligned%7D%20g_1%26%3D%5Ctextrm%7B0xeb3eb781%7D%20%5C%5C%20g_2%26%3D%5Ctextrm%7B0x50265329%7D%20%5C%5C%20g_3%26%3D%5Ctextrm%7B0xdc5ef4a3%7D%20%5C%5C%20g_4%26%3D%5Ctextrm%7B0x6847b9d5%7D%20%5C%5C%20g_5%26%3D%5Ctextrm%7B0xcde43b4c%7D%20%5C%5C%20%5Cend%7Baligned%7D">
   </p>

4. Regard ![](http://latex.codecogs.com/svg.latex?%5Cinline%20g_0) as counter, add itself by 1.

   Calculate SHA1:

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?%5Ctextrm%7BSHA%7D_1%28g_%7B0%2C0%7D%7C%7Cg_%7B0%2C1%7D%7C%7Cg_%7B0%2C2%7D%7C%7Cg_%7B0%2C3%7D%7C%7Cg_%7B1%2C0%7D%7C%7Cg_%7B1%2C1%7D%7C%7C%5Cldots%7C%7Cg_%7B5%2C0%7D%7C%7Cg_%7B5%2C1%7D%7C%7Cg_%7B5%2C2%7D%7C%7Cg_%7B5%2C3%7D%29%3DS_0%7C%7CS_1%7C%7CS_2%7C%7CS_3%7C%7CS_4">
   </p>

   We takes the lowest 16 bits of ![](http://latex.codecogs.com/svg.latex?%5Cinline%20S_0) and donote it as ![](http://latex.codecogs.com/svg.latex?%5Cinline%20k_%7Bg_0%7D).

5. Repeat step 4 again with 14 times.

6. After that, we will get ![](http://latex.codecogs.com/svg.latex?%5Cinline%20k_1%2Ck_2%2Ck_3%2C%5Cldots%2Ck_%7B15%7D). Then output private key

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?k%3D%5Csum_%7Bi%3D1%7D%5E%7B15%7Dk_i%20%5Ccdot%202%5E%7B16i%7D">
   </p>

## 6. The private key and public key of WinRAR

Private key ![k-inlined] is

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?k%3D%5Ctextrm%7B0x59fe6abcca90bdb95f0105271fa85fb9f11f467450c1ae9044b7fd61d65e%7D%20%5Cquad%20%5Cquad%20k%5Cin%5Cnolinebreak%5Cmathbb%7BZ%7D">
</p>

This private key is generated by the algorithm describled in section 5 where the length of data ![T-inlined] is zero.

Public key ![P-inlined] is

<p align="center">
    <img src="http://latex.codecogs.com/svg.latex?%5Cbegin%7Baligned%7D%20P%26%3D%28P_x%2CP_y%29%20%5C%5C%20P_x%26%3D%5Ctextrm%7B0x3861220ed9b36c9753df09a159dfb148135d495db3af8373425ee9a28884ba1a%7D%20%5Cquad%20P_x%5Cin%5Ctextrm%7BGF%7D%28%282%5E%7B15%7D%29%5E%7B17%7D%29%20%5C%5C%20P_y%26%3D%5Ctextrm%7B0x12b64e62db43a56114554b0cbd573379338cea9124c8443c4f50e6c8b013ec20%7D%20%5Cquad%20P_y%5Cin%5Ctextrm%7BGF%7D%28%282%5E%7B15%7D%29%5E%7B17%7D%29%20%5Cend%7Baligned%7D">
</p>

## 7. Generation of "rarreg.key"

The generation of license file `rarreg.key` requires 2 arguments:

1. Username, an ANSI-encoded string, without null-terminator. Denoted as

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?U%3Du_0u_1%20%5Cldots%20u_%7Bl-1%7D">
   </p>

2. License type, an ANSI-encoded string, without null-terminator. Denoted as 

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?L%3Dl_0l_1%20%5Cldots%20l_%7Bl-1%7D">
   </p>

The following is the algorithm to generate `rarreg.key`.

1. Use the algorithm describled in section 5, with argument ![UU-inlined], to generate private key ![](http://latex.codecogs.com/svg.latex?%5Cinline%20k_U) and public key ![](http://latex.codecogs.com/svg.latex?%5Cinline%20P_U). Then output hexlified public key string with SM2 compressed public key format. The hexlified public key is denoted as ![Temp-inlined].

   The length of ![Temp-inlined] should be 64. If less, pad with `'0'` until the length is 64.

2. Let ![Data3-inlined] be 

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?Data%5E3%3D%5Ctexttt%7B%2260%22%7D%7C%7CTemp_0%7C%7CTemp_1%7C%7C%5Cldots%7C%7CTemp_%7B47%7D">
   </p>

3. Use the algorithm describled in section 5, with argument ![Data3-inlined], to generate private key ![](http://latex.codecogs.com/svg.latex?%5Cinline%20k_%7BData%5E3%7D) and public key ![](http://latex.codecogs.com/svg.latex?%5Cinline%20P_%7BData%5E3%7D). Then output hexlified public key string with SM2 compressed public key format. The hexlified public key is denoted as ![Data0-inlined].

   The length of ![Data0-inlined] should be 64. If less, pad with `'0'` until the length is 64.

4. Let ![UID-inlined] be

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?UID%3DTemp_%7B48%7D%7C%7CTemp_%7B49%7D%7C%7C%5Cldots%7C%7CTemp_%7B63%7D%7C%7CData%5E0_0%7C%7CData%5E0_1%7C%7CData%5E0_2%7C%7CData%5E0_3">
   </p>

5. Use the algorithm describled in section 4, with argument ![LL-inlined] and private key ![k-inlined] describled section 6, to get signature ![](http://latex.codecogs.com/svg.latex?%5Cinline%20%28r_L%2Cs_L%29).

   The bit length of ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r_L) and ![](http://latex.codecogs.com/svg.latex?%5Cinline%20s_L) shall not be more than 240. Otherwise, repeat this step.

6. Convert ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r_L) and ![](http://latex.codecogs.com/svg.latex?%5Cinline%20s_L) to hex-integer string ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Br_L%7D) and ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Bs_L%7D), without `"0x"` prefix. 

   If the length of ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Br_L%7D) or ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Bs_L%7D) is less than 60, pad character `'0'` until the length is 60.

7. Let ![Data1-inlined] be

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?Data%5E1%3D%5Ctexttt%7B%2260%22%7D%7C%7CSZ%5E%7Bs_L%7D%7C%7CSZ%5E%7Br_L%7D">
   </p>

8. Let ![Temp-inlined] be 

   <p align="center">
       <img src="http://latex.codecogs.com/svg.latex?Temp%3DU%7C%7CData%5E0">
   </p>

   Use the algorithm describled in section 4, with argument ![Temp-inlined] and private key ![k-inlined] describled section 6, to get signature ![](http://latex.codecogs.com/svg.latex?%5Cinline%20%28r_%7BTemp%7D%2Cs_%7BTemp%7D%29).

   The bit length of ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r_%7BTemp%7D) and ![](http://latex.codecogs.com/svg.latex?%5Cinline%20s_%7BTemp%7D) shall not be more than 240. Otherwise, repeat this step.

9. Convert ![](http://latex.codecogs.com/svg.latex?%5Cinline%20r_%7BTemp%7D) and ![](http://latex.codecogs.com/svg.latex?%5Cinline%20s_%7BTemp%7D) to hex-integer string ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Br_%7BTemp%7D%7D) and ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Bs_%7BTemp%7D%7D), without `"0x"` prefix. 

   If the length of ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Br_%7BTemp%7D%7D) or ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Bs_%7BTemp%7D%7D) is less than 60, pad character `'0'` until the length is 60.

10. Let ![Data2-inlined] be

    <p align="center">
        <img src="http://latex.codecogs.com/svg.latex?Data%5E2%3D%5Ctexttt%7B%2260%22%7D%7C%7CSZ%5E%7Bs_%7BTemp%7D%7D%7C%7CSZ%5E%7Br_%7BTemp%7D%7D">
    </p>

11. Calculate CRC32 value of 

    <p align="center">
        <img src="http://latex.codecogs.com/svg.latex?L%7C%7CU%7C%7CData%5E0%7C%7CData%5E1%7C%7CData%5E2%7C%7CData%5E3">
    </p>

    The final checksum the complement of CRC32 value. 

    Then convert the checksum to decimal string ![](http://latex.codecogs.com/svg.latex?%5Cinline%20SZ%5E%7Bchecksum%7D). If the length is less than 10, pad character `'0'` until the length is 10.

12. Let ![Data-inlined] be 

    <p align="center">
        <img src="http://latex.codecogs.com/svg.latex?%5Cinline%20Data%3DData%5E0%7C%7CData%5E1%7C%7CData%5E2%7C%7CData%5E3%7C%7CSZ%5E%7Bchecksum%7D">
    </p>

13. Output with format

    * A fixed header `"RAR registration data"`, taking one line.

    * Username, taking one line.

    * License type, taking one line

    * UID, taking one line, with format:

      <p align="center">
        <img src="http://latex.codecogs.com/svg.latex?%5Ctexttt%7B%22UID%3D%22%7D%7C%7CUID">
      </p>

    * Output ![Data-inlined], with 54 characters a line.

