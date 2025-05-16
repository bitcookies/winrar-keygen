# 验证基点G在曲线上

## 1. 复合域、曲线和基点G

复合域为 ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only)。

基域为 ![GF2p15-inlined](assets/formula/GF2p15-inlined-light.svg#gh-light-mode-only)![GF2p15-inlined](assets/formula/GF2p15-inlined-dark.svg#gh-dark-mode-only) ，即域中每个元素是一个 `15-bit` 的数字。扩展次数是17，所以整个复合域元素可以看作是一个17项的多项式，每项都是 ![GF2p15-inlined](assets/formula/GF2p15-inlined-light.svg#gh-light-mode-only)![GF2p15-inlined](assets/formula/GF2p15-inlined-dark.svg#gh-dark-mode-only) 中的数。

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

## 2. 转换基点G

将基点 ![G](assets/formula/GG-inlined-light.svg#gh-light-mode-only)![G](assets/formula/GG-inlined-dark.svg#gh-dark-mode-only)（以大整数形式）转换为 ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-light.svg#gh-light-mode-only) ![GF2p15p17-inlined](assets/formula/GF2p15p17-inlined-dark.svg#gh-dark-mode-only)所需的 `15-bit` 小端表示形式。一个转换基点 ![G](assets/formula/GG-inlined-light.svg#gh-light-mode-only)![G](assets/formula/GG-inlined-dark.svg#gh-dark-mode-only) 的 Python 脚本如下：

```python
def to_field_repr(val, bits=15, count=17):
    mask = (1 << bits) - 1
    result = []
    for _ in range(count):
        result.append(val & mask)
        val >>= bits
    return result

def print_field(label, field_data):
    print(f"{label} = to_field([")
    for i in range(len(field_data)):
        print(f"    0x{field_data[i]:04X},", end="\n" if (i + 1) % 4 == 0 else " ")
    print("])")

Gx_int = 0x56fdcbc6a27acee0cc2996e0096ae74feb1acf220a2341b898b549440297b8cc
Gy_int = 0x20da32e8afc90b7cf0e76bde44496b4d0794054e6ea60f388682463132f931a7

Gx_field = to_field_repr(Gx_int)
Gy_field = to_field_repr(Gy_int)

print_field("Gx", Gx_field)
print()
print_field("Gy", Gy_field)
```

输出结果可以看到正是 WinRarConfig.hpp 文件中 435~456 行的内容：

```
Gx = to_field([
    0x38CC,     0x052F,     0x2510,     0x45AA,
    0x1B89,     0x4468,     0x4882,     0x0D67,
    0x4FEB,     0x55CE,     0x0025,     0x4CB7,
    0x0CC2,     0x59DC,     0x289E,     0x65E3,
    0x56FD
])

Gy = to_field([
    0x31A7,     0x65F2,     0x18C4,     0x3412,
    0x7388,     0x54C1,     0x539B,     0x4A02,
    0x4D07,     0x12D6,     0x7911,     0x3B5E,
    0x4F0E,     0x216F,     0x2BF2,     0x1974,
    0x20DA
])
```

## 3. 验证基点G和PK是否在曲线上

一个验证基点 ![G](assets/formula/GG-inlined-light.svg#gh-light-mode-only)![G](assets/formula/GG-inlined-dark.svg#gh-dark-mode-only) 和PK是否在曲线上的 Python 脚本如下：

```python
#  GF(((2^15)^17))
def gf2_15_add(a, b):
    return a ^ b

def gf2_15_mul(a, b):
    # 模 x^15 + x + 1
    res = 0
    for i in range(15):
        if (b >> i) & 1:
            res ^= a << i
    # 模多项式 x^15 + x + 1
    for i in range(29, 14, -1):
        if (res >> i) & 1:
            res ^= 0b1000000000000011 << (i - 15)
    return res & 0x7FFF  # 15-bit mask

def gf2_15_poly_add(a, b):
    return [gf2_15_add(x, y) for x, y in zip(a, b)]

def gf2_15_poly_mul(a, b):
    res = [0] * 33
    for i in range(17):
        for j in range(17):
            res[i + j] ^= gf2_15_mul(a[i], b[j])
    return res

def gf2_15_17_mod(poly):
    # 模 y^17 + y^3 + 1
    for i in range(len(poly) - 1, 16, -1):
        if poly[i]:
            poly[i - 17] ^= poly[i]
            poly[i - 14] ^= poly[i]
            poly[i] = 0
    return poly[:17]

def gf2_15_17_mul(a, b):
    return gf2_15_17_mod(gf2_15_poly_mul(a, b))

def gf2_15_17_square(a):
    return gf2_15_17_mul(a, a)

def gf2_15_17_add(a, b):
    return gf2_15_poly_add(a, b)

def gf2_15_17_eq(a, b):
    return all(x == y for x, y in zip(a, b))

def is_on_curve(x, y, b):
    y2 = gf2_15_17_square(y)
    xy = gf2_15_17_mul(x, y)
    lhs = gf2_15_17_add(y2, xy)
    x2 = gf2_15_17_square(x)
    x3 = gf2_15_17_mul(x2, x)
    rhs = gf2_15_17_add(x3, b)
    return gf2_15_17_eq(lhs, rhs)

def to_field(arr):
    assert len(arr) == 17
    return arr[:]

# 参数定义
b = [0x00] * 17
b = [161] + [0]*16  # GF((2^15)^17) 中的常数元素，等价于 b[0] = 0xA1

Gx = to_field([0x38CC, 0x052F, 0x2510, 0x45AA, 0x1B89, 0x4468, 0x4882, 0x0D67,
               0x4FEB, 0x55CE, 0x0025, 0x4CB7, 0x0CC2, 0x59DC, 0x289E, 0x65E3, 0x56FD])
Gy = to_field([0x31A7, 0x65F2, 0x18C4, 0x3412, 0x7388, 0x54C1, 0x539B, 0x4A02,
               0x4D07, 0x12D6, 0x7911, 0x3B5E, 0x4F0E, 0x216F, 0x2BF2, 0x1974, 0x20DA])

PKx = to_field([0x3A1A, 0x1109, 0x268A, 0x12F7, 0x3734, 0x75F0, 0x576C, 0x2EA4,
                0x4813, 0x3F62, 0x0567, 0x784D, 0x753D, 0x6D92, 0x366C, 0x1107, 0x3861])
PKy = to_field([0x6C20, 0x6027, 0x1B22, 0x7A87, 0x43C4, 0x1908, 0x2449, 0x4675,
                0x7933, 0x2E66, 0x32F5, 0x2A58, 0x1145, 0x74AC, 0x36D0, 0x2731, 0x12B6])

# 验证
print("验证基点 G 是否在曲线上：", is_on_curve(Gx, Gy, b))
print("验证 PK 是否在曲线上：", is_on_curve(PKx, PKy, b))
```
