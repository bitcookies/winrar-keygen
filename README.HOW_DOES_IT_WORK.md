# How is "rarreg.key" generated?

WinRAR uses an ECC-based signature algorithm to generate `rarreg.key`. The algorithm it used is a variant of Chinese SM2 digital signature algorithm. Different to many standard ECDSAs, the curve that WinRAR selected is a curve over composite field ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only).

## 1. Composite field ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only)

Elements in ground field ![GF2p15-inlined](assets/formula/GF2p15-inlined-light.svg#gh-light-mode-only)![GF2p15-inlined](assets/formula/GF2p15-inlined-dark.svg#gh-dark-mode-only) are represented with standard basis, i.e. polynomial basis. The irreducible polynomial is

<p align="center">
    <img src="assets/formula/1-light.svg#gh-light-mode-only">
    <img src="assets/formula/1-dark.svg#gh-dark-mode-only">
</p>


where each coefficients is in ![GF2-inlined](assets/formula/GF2-inlined-light.svg#gh-light-mode-only)![GF2-inlined](assets/formula/GF2-inlined-dark.svg#gh-dark-mode-only). If we use 

<p align="center">
    <img src="assets/formula/2-light.svg#gh-light-mode-only">
    <img src="assets/formula/2-dark.svg#gh-dark-mode-only">
</p>


as the standard basis of the ground field, an element ![A](assets/formula/AA-inlined-light.svg#gh-light-mode-only)![A](assets/formula/AA-inlined-dark.svg#gh-dark-mode-only) in ![GF2p15-inlined](assets/formula/GF2p15-inlined-light.svg#gh-light-mode-only)![GF2p15-inlined](assets/formula/GF2p15-inlined-dark.svg#gh-dark-mode-only) can be denoted as

<p align="center">
    <img src="assets/formula/3-light.svg#gh-light-mode-only">
    <img src="assets/formula/3-dark.svg#gh-dark-mode-only">
</p>


---

The irreducible polynomial of composite field ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only) is

<p align="center">
    <img src="assets/formula/4-light.svg#gh-light-mode-only">
    <img src="assets/formula/4-dark.svg#gh-dark-mode-only">
</p>


where each coefficients is in ![GF2p15-inlined](assets/formula/GF2p15-inlined-light.svg#gh-light-mode-only)![GF2p15-inlined](assets/formula/GF2p15-inlined-dark.svg#gh-dark-mode-only). If we use 

<p align="center">
    <img src="assets/formula/5-light.svg#gh-light-mode-only">
    <img src="assets/formula/5-dark.svg#gh-dark-mode-only">
</p>


as the standard basis of the composite field, an element ![B](assets/formula/BB-inlined-light.svg#gh-light-mode-only)![B](assets/formula/BB-inlined-dark.svg#gh-dark-mode-only) in ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only) can be denoted as

<p align="center">
    <img src="assets/formula/6-light.svg#gh-light-mode-only">
    <img src="assets/formula/6-dark.svg#gh-dark-mode-only">
</p>


---

For clarity, we use ![D](assets/formula/DD-inlined-light.svg#gh-light-mode-only)![D](assets/formula/DD-inlined-dark.svg#gh-dark-mode-only) , which is a 255-bits-long integer to denote an element ![B](assets/formula/BB-inlined-light.svg#gh-light-mode-only)![B](assets/formula/BB-inlined-dark.svg#gh-dark-mode-only) in ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only). The map between them is

<p align="center">
    <img src="assets/formula/7-light.svg#gh-light-mode-only">
    <img src="assets/formula/7-dark.svg#gh-dark-mode-only">
</p>


## 2. Elliptic curve over ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only)

The equation of the elliptic curve that WinRAR uses is

<p align="center">
    <img src="assets/formula/8-light.svg#gh-light-mode-only">
    <img src="assets/formula/8-dark.svg#gh-dark-mode-only">
</p>


The base point ![G](assets/formula/GG-inlined-light.svg#gh-light-mode-only)![G](assets/formula/GG-inlined-dark.svg#gh-dark-mode-only) is

<p align="center">
    <img src="assets/formula/9-light.svg#gh-light-mode-only">
    <img src="assets/formula/9-dark.svg#gh-dark-mode-only">
</p>


whose order ![n](assets/formula/n-inlined-light.svg#gh-light-mode-only)![n](assets/formula/n-inlined-dark.svg#gh-dark-mode-only)  is

<p align="center">
    <img src="assets/formula/10-light.svg#gh-light-mode-only">
    <img src="assets/formula/10-dark.svg#gh-dark-mode-only">
</p>


## 3. Message hash algorithm

We use 

<p align="center">
    <img src="assets/formula/11-light.svg#gh-light-mode-only">
    <img src="assets/formula/11-dark.svg#gh-dark-mode-only">
</p>


to denote a message whose length is ![l](assets/formula/l-inlined-light.svg#gh-light-mode-only)![l](assets/formula/l-inlined-dark.svg#gh-dark-mode-only). So the SHA1 value of ![M](assets/formula/MM-inlined-light.svg#gh-light-mode-only)![M](assets/formula/MM-inlined-dark.svg#gh-dark-mode-only) should be 

<p align="center">
    <img src="assets/formula/12-light.svg#gh-light-mode-only">
    <img src="assets/formula/12-dark.svg#gh-dark-mode-only">
</p>


where ![s0,4](assets/formula/13-light.svg#gh-light-mode-only)![s0,4](assets/formula/13-dark.svg#gh-dark-mode-only) are 5 state values when SHA1 outputs. Generally speaking, the final SHA1 value should be the join of these 5 state values while each of state values is serialized in big-endian.

However, WinRAR doesn't serialize the 5 state values. Instead, it use a big integer ![h](assets/formula/h-inlined-light.svg#gh-light-mode-only)![h](assets/formula/h-inlined-dark.svg#gh-dark-mode-only) as the hash of the input message.

<p align="center">
    <img src="assets/formula/15-light.svg#gh-light-mode-only">
    <img src="assets/formula/15-dark.svg#gh-dark-mode-only">
</p>


## 4. ECC digital signature algorithm

We use ![k](assets/formula/k-inlined-light.svg#gh-light-mode-only)![k](assets/formula/k-inlined-dark.svg#gh-dark-mode-only) to denote private key, ![P](assets/formula/PP-inlined-light.svg#gh-light-mode-only)![P](assets/formula/PP-inlined-dark.svg#gh-dark-mode-only) to denote public key. So there must be

<p align="center">
    <img src="assets/formula/16-light.svg#gh-light-mode-only">
    <img src="assets/formula/16-dark.svg#gh-dark-mode-only">
</p>


If we use ![h](assets/formula/h-inlined-light.svg#gh-light-mode-only)![h](assets/formula/h-inlined-dark.svg#gh-dark-mode-only) to denote the hash of input data, WinRAR use the following algorithm to perform signing:

1. Generate a random big integer ![Rnd](assets/formula/Rnd-inlined-light.svg#gh-light-mode-only)![Rnd](assets/formula/Rnd-inlined-dark.svg#gh-dark-mode-only) which satisfies ![RND](assets/formula/18-light.svg#gh-light-mode-only)![RND](assets/formula/18-dark.svg#gh-dark-mode-only).

2. Calculate ![r](assets/formula/r-inlined-light.svg#gh-light-mode-only)![r](assets/formula/r-inlined-dark.svg#gh-dark-mode-only)

   <p align="center">
       <img src="assets/formula/19-light.svg#gh-light-mode-only">
       <img src="assets/formula/19-dark.svg#gh-dark-mode-only">
   </p>


   where ![RNDGx](assets/formula/20-light.svg#gh-light-mode-only)![RNDGx](assets/formula/20-dark.svg#gh-dark-mode-only)  means we take X coordinate of ![RNDG](assets/formula/21-light.svg#gh-light-mode-only)![RNDG](assets/formula/21-dark.svg#gh-dark-mode-only) and convert it from ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only) to a big integer.

   If ![r=0](assets/formula/22-light.svg#gh-light-mode-only)![r=0](assets/formula/22-dark.svg#gh-dark-mode-only)  or ![rRnd](assets/formula/23-light.svg#gh-light-mode-only)![rRnd](assets/formula/23-dark.svg#gh-dark-mode-only), go back to step 1.

3. Calculate ![s](assets/formula/s-inlined-light.svg#gh-light-mode-only)![s](assets/formula/s-inlined-dark.svg#gh-dark-mode-only)

   <p align="center">
       <img src="assets/formula/24-light.svg#gh-light-mode-only">
       <img src="assets/formula/24-dark.svg#gh-dark-mode-only">
   </p>


   If ![s=0](assets/formula/25-light.svg#gh-light-mode-only)![s=0](assets/formula/25-dark.svg#gh-dark-mode-only), go back to step 1.

4. Output ![(r,s)](assets/formula/17-light.svg#gh-light-mode-only)![(r,s)](assets/formula/17-dark.svg#gh-dark-mode-only).

## 5. WinRAR private key generation algorithm

We use 

<p align="center">
    <img src="assets/formula/26-light.svg#gh-light-mode-only">
    <img src="assets/formula/26-dark.svg#gh-dark-mode-only">
</p>


to denote input data whose length is ![l](assets/formula/l-inlined-light.svg#gh-light-mode-only)![l](assets/formula/l-inlined-dark.svg#gh-dark-mode-only). WinRAR use it to generate private key ![k](assets/formula/k-inlined-light.svg#gh-light-mode-only)![k](assets/formula/k-inlined-dark.svg#gh-dark-mode-only).

1. We use ![g0-5](assets/formula/27-light.svg#gh-light-mode-only)![g0-5](assets/formula/27-dark.svg#gh-dark-mode-only) to denote 6 32-bits-long integer. So there is

   <p align="center">
       <img src="assets/formula/28-light.svg#gh-light-mode-only">
       <img src="assets/formula/28-dark.svg#gh-dark-mode-only">
   </p>

2. Let ![g0=0](assets/formula/29-light.svg#gh-light-mode-only)![g0=0](assets/formula/29-dark.svg#gh-dark-mode-only).

3. If ![l!=0](assets/formula/30-light.svg#gh-light-mode-only)![l!=0](assets/formula/30-dark.svg#gh-dark-mode-only), we calculate SHA1 value of ![T](assets/formula/TT-inlined-light.svg#gh-light-mode-only)![T](assets/formula/TT-inlined-dark.svg#gh-dark-mode-only). Then assign SHA1 state value ![Si](assets/formula/31-light.svg#gh-light-mode-only)![Si](assets/formula/31-dark.svg#gh-dark-mode-only) to ![gi+1](assets/formula/32-light.svg#gh-light-mode-only)![gi+1](assets/formula/32-dark.svg#gh-dark-mode-only):

   <p align="center">
       <img src="assets/formula/33-light.svg#gh-light-mode-only">
       <img src="assets/formula/33-dark.svg#gh-dark-mode-only">
   </p>


   Otherwise, when ![l=0](assets/formula/34-light.svg#gh-light-mode-only)![l=0](assets/formula/34-dark.svg#gh-dark-mode-only), we let 

   <p align="center">
       <img src="assets/formula/35-light.svg#gh-light-mode-only">
          <img src="assets/formula/35-dark.svg#gh-dark-mode-only">
   </p>

4. Regard ![g0](assets/formula/36-light.svg#gh-light-mode-only)![g0](assets/formula/36-dark.svg#gh-dark-mode-only)  as counter, add itself by 1.

   Calculate SHA1:

   <p align="center">
       <img src="assets/formula/37-light.svg#gh-light-mode-only">
       <img src="assets/formula/37-dark.svg#gh-dark-mode-only">
   </p>


   We takes the lowest 16 bits of ![S0](assets/formula/38-light.svg#gh-light-mode-only)![S0](assets/formula/38-dark.svg#gh-dark-mode-only) and donote it as ![Kg0](assets/formula/39-light.svg#gh-light-mode-only)![Kg0](assets/formula/39-dark.svg#gh-dark-mode-only).

5. Repeat step 4 again with 14 times.

6. After that, we will get ![k1-15](assets/formula/40-light.svg#gh-light-mode-only)![k1-15](assets/formula/40-dark.svg#gh-dark-mode-only). Then output private key

   <p align="center">
       <img src="assets/formula/41-light.svg#gh-light-mode-only">
       <img src="assets/formula/41-dark.svg#gh-dark-mode-only">
   </p>

## 6. The private key and public key of WinRAR

Private key ![k](assets/formula/k-inlined-light.svg#gh-light-mode-only)![k](assets/formula/k-inlined-dark.svg#gh-dark-mode-only) is

<p align="center">
    <img src="assets/formula/42-light.svg#gh-light-mode-only">
    <img src="assets/formula/42-dark.svg#gh-dark-mode-only">
</p>


This private key is generated by the algorithm describled in section 5 where the length of data ![T](assets/formula/TT-inlined-light.svg#gh-light-mode-only)![T](assets/formula/TT-inlined-dark.svg#gh-dark-mode-only) is zero.

Public key ![P](assets/formula/PP-inlined-light.svg#gh-light-mode-only)![P](assets/formula/PP-inlined-dark.svg#gh-dark-mode-only) is

<p align="center">
    <img src="assets/formula/43-light.svg#gh-light-mode-only">
    <img src="assets/formula/43-dark.svg#gh-dark-mode-only">
</p>


## 7. Generation of "rarreg.key"

The generation of license file `rarreg.key` requires 2 arguments:

1. Username, an ANSI-encoded string, without null-terminator. Denoted as

   <p align="center">
       <img src="assets/formula/44-light.svg#gh-light-mode-only">
       <img src="assets/formula/44-dark.svg#gh-dark-mode-only">
   </p>

2. License type, an ANSI-encoded string, without null-terminator. Denoted as 

   <p align="center">
       <img src="assets/formula/45-light.svg#gh-light-mode-only">
       <img src="assets/formula/45-dark.svg#gh-dark-mode-only">
   </p>

The following is the algorithm to generate `rarreg.key`.

1. Use the algorithm describled in section 5, with argument ![U](assets/formula/UU-inlined-light.svg#gh-light-mode-only)![U](assets/formula/UU-inlined-dark.svg#gh-dark-mode-only), to generate private key ![ku](assets/formula/46-light.svg#gh-light-mode-only)![ku](assets/formula/46-dark.svg#gh-dark-mode-only)  and public key ![pu](assets/formula/47-light.svg#gh-light-mode-only)![pu](assets/formula/47-dark.svg#gh-dark-mode-only). Then output hexlified public key string with SM2 compressed public key format. The hexlified public key is denoted as ![Temp](assets/formula/Temp-inlined-light.svg#gh-light-mode-only)![Temp](assets/formula/Temp-inlined-dark.svg#gh-dark-mode-only).

   The length of ![Temp](assets/formula/Temp-inlined-light.svg#gh-light-mode-only)![Temp](assets/formula/Temp-inlined-dark.svg#gh-dark-mode-only) should be 64. If less, pad with `'0'` until the length is 64.

2. Let ![Data3](assets/formula/Data3-inlined-light.svg#gh-light-mode-only)![Data3](assets/formula/Data3-inlined-dark.svg#gh-dark-mode-only) be 

   <p align="center">
       <img src="assets/formula/48-light.svg#gh-light-mode-only">
       <img src="assets/formula/48-dark.svg#gh-dark-mode-only">
   </p>

3. Use the algorithm describled in section 5, with argument ![Data3](assets/formula/Data3-inlined-light.svg#gh-light-mode-only)![Data3](assets/formula/Data3-inlined-dark.svg#gh-dark-mode-only), to generate private key ![kdata3](assets/formula/49-light.svg#gh-light-mode-only)![kdata3](assets/formula/49-dark.svg#gh-dark-mode-only) and public key ![pdata3](assets/formula/50-light.svg#gh-light-mode-only)![pdata3](assets/formula/50-dark.svg#gh-dark-mode-only). Then output hexlified public key string with SM2 compressed public key format. The hexlified public key is denoted as ![Data0](assets/formula/Data0-inlined-light.svg#gh-light-mode-only)![Data0](assets/formula/Data0-inlined-dark.svg#gh-dark-mode-only).

   The length of ![Data0](assets/formula/Data0-inlined-light.svg#gh-light-mode-only)![Data0](assets/formula/Data0-inlined-dark.svg#gh-dark-mode-only) should be 64. If less, pad with `'0'` until the length is 64.

4. Let ![UID](assets/formula/UID-inlined-light.svg#gh-light-mode-only)![UID](assets/formula/UID-inlined-dark.svg#gh-dark-mode-only) be

   <p align="center">
       <img src="assets/formula/51-light.svg#gh-light-mode-only">
       <img src="assets/formula/51-dark.svg#gh-dark-mode-only">
   </p>

5. Use the algorithm describled in section 4, with argument ![L](assets/formula/LL-inlined-light.svg#gh-light-mode-only)![L](assets/formula/LL-inlined-dark.svg#gh-dark-mode-only)  and private key ![k](assets/formula/k-inlined-light.svg#gh-light-mode-only)![k](assets/formula/k-inlined-dark.svg#gh-dark-mode-only)  describled section 6, to get signature ![(rl,sl)](assets/formula/52-light.svg#gh-light-mode-only)![(rl,sl)](assets/formula/52-dark.svg#gh-dark-mode-only).

   The bit length of ![rl](assets/formula/53-light.svg#gh-light-mode-only)![rl](assets/formula/53-dark.svg#gh-dark-mode-only) and ![sl](assets/formula/54-light.svg#gh-light-mode-only)![sl](assets/formula/54-dark.svg#gh-dark-mode-only) shall not be more than 240. Otherwise, repeat this step.

6. Convert ![rl](assets/formula/53-light.svg#gh-light-mode-only)![rl](assets/formula/53-dark.svg#gh-dark-mode-only) and ![sl](assets/formula/54-light.svg#gh-light-mode-only)![sl](assets/formula/54-dark.svg#gh-dark-mode-only) to hex-integer string ![SZrl](assets/formula/55-light.svg#gh-light-mode-only)![SZrl](assets/formula/55-dark.svg#gh-dark-mode-only) and ![SZsl](assets/formula/56-light.svg#gh-light-mode-only)![SZsl](assets/formula/56-dark.svg#gh-dark-mode-only), without `"0x"` prefix. 

   If the length of ![SZrl](assets/formula/55-light.svg#gh-light-mode-only)![SZrl](assets/formula/55-dark.svg#gh-dark-mode-only) or ![SZsl](assets/formula/56-light.svg#gh-light-mode-only)![SZsl](assets/formula/56-dark.svg#gh-dark-mode-only) is less than 60, pad character `'0'` until the length is 60.

7. Let ![Data1](assets/formula/Data1-inlined-light.svg#gh-light-mode-only)![Data1](assets/formula/Data1-inlined-dark.svg#gh-dark-mode-only) be

   <p align="center">
       <img src="assets/formula/57-light.svg#gh-light-mode-only">
       <img src="assets/formula/57-dark.svg#gh-dark-mode-only">
   </p>

8. Let ![Temp](assets/formula/Temp-inlined-light.svg#gh-light-mode-only)![Temp](assets/formula/Temp-inlined-dark.svg#gh-dark-mode-only) be 

   <p align="center">
       <img src="assets/formula/58-light.svg#gh-light-mode-only">
       <img src="assets/formula/58-dark.svg#gh-dark-mode-only">
   </p>


   Use the algorithm describled in section 4, with argument ![Temp](assets/formula/Temp-inlined-light.svg#gh-light-mode-only)![Temp](assets/formula/Temp-inlined-dark.svg#gh-dark-mode-only) and private key ![k](assets/formula/k-inlined-light.svg#gh-light-mode-only)![k](assets/formula/k-inlined-dark.svg#gh-dark-mode-only) describled section 6, to get signature ![(rTemp,sTemp)](assets/formula/59-light.svg#gh-light-mode-only)![(rTemp,sTemp)](assets/formula/59-dark.svg#gh-dark-mode-only).

   The bit length of ![rTemp](assets/formula/60-light.svg#gh-light-mode-only)![rTemp](assets/formula/60-dark.svg#gh-dark-mode-only) and ![sTemp](assets/formula/61-light.svg#gh-light-mode-only)![sTemp](assets/formula/61-dark.svg#gh-dark-mode-only) shall not be more than 240. Otherwise, repeat this step.

9. Convert ![rTemp](assets/formula/60-light.svg#gh-light-mode-only)![rTemp](assets/formula/60-dark.svg#gh-dark-mode-only) and ![sTemp](assets/formula/61-light.svg#gh-light-mode-only)![sTemp](assets/formula/61-dark.svg#gh-dark-mode-only) to hex-integer string ![SZrTemp](assets/formula/62-light.svg#gh-light-mode-only)![SZrTemp](assets/formula/62-dark.svg#gh-dark-mode-only)  and ![SZsTemp](assets/formula/63-light.svg#gh-light-mode-only)![SZsTemp](assets/formula/63-dark.svg#gh-dark-mode-only), without `"0x"` prefix. 

   If the length of ![SZrTemp](assets/formula/62-light.svg#gh-light-mode-only)![SZrTemp](assets/formula/62-dark.svg#gh-dark-mode-only)  or ![SZsTemp](assets/formula/63-light.svg#gh-light-mode-only)![SZsTemp](assets/formula/63-dark.svg#gh-dark-mode-only) is less than 60, pad character `'0'` until the length is 60.

10. Let ![Data2](assets/formula/Data2-inlined-light.svg#gh-light-mode-only)![Data2](assets/formula/Data2-inlined-dark.svg#gh-dark-mode-only) be

    <p align="center">
        <img src="assets/formula/64-light.svg#gh-light-mode-only">
        <img src="assets/formula/64-dark.svg#gh-dark-mode-only">
    </p>

11. Calculate CRC32 value of 

    <p align="center">
        <img src="assets/formula/65-light.svg#gh-light-mode-only">
        <img src="assets/formula/65-dark.svg#gh-dark-mode-only">
    </p>


    The final checksum the complement of CRC32 value. 

    Then convert the checksum to decimal string ![SZchecksum](assets/formula/66-light.svg#gh-light-mode-only)![SZchecksum](assets/formula/66-dark.svg#gh-dark-mode-only). If the length is less than 10, pad character `'0'` until the length is 10.

12. Let ![Data](assets/formula/Data-inlined-light.svg#gh-light-mode-only)![Data](assets/formula/Data-inlined-dark.svg#gh-dark-mode-only) be 

    <p align="center">
        <img src="assets/formula/67-light.svg#gh-light-mode-only">
        <img src="assets/formula/67-dark.svg#gh-dark-mode-only">
    </p>

13. Output with format

    * A fixed header `"RAR registration data"`, taking one line.

    * Username, taking one line.

    * License type, taking one line

    * UID, taking one line, with format:

      <p align="center">
        <img src="assets/formula/68-light.svg#gh-light-mode-only">
          <img src="assets/formula/68-dark.svg#gh-dark-mode-only">
      </p>
    
    * Output ![Data](assets/formula/Data-inlined-light.svg#gh-light-mode-only)![Data](assets/formula/Data-inlined-dark.svg#gh-dark-mode-only), with 54 characters a line.
