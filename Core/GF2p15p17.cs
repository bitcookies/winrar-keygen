using System;

namespace WinRarKeygenGui.Core;

/// <summary>
/// Galois Field GF((2^15)^17) with irreducible polynomials:
///   Ground field: x^15 + x + 1
///   Extension field: y^17 + y^3 + 1
/// </summary>
public class GF2p15p17
{
    public const int FieldDegree = 17;
    public const int SubFieldBits = 15;
    public const int TotalBits = FieldDegree * SubFieldBits; // 255
    public const int DumpSize = (TotalBits + 7) / 8; // 32

    private static readonly ushort[] LogTable = new ushort[0x8000];
    private static readonly ushort[] ExpTable = new ushort[0x8000];

    static GF2p15p17()
    {
        const int Order = 0x7fff;
        ExpTable[0] = 1;
        for (int i = 1; i < Order; i++)
        {
            uint temp = (uint)(ExpTable[i - 1] * 2);
            if ((temp & 0x8000) != 0)
                temp ^= 0x8003;
            ExpTable[i] = (ushort)temp;
        }
        ExpTable[Order] = (ushort)(~ExpTable[Order]);

        for (int i = 0; i < Order; i++)
        {
            LogTable[ExpTable[i]] = (ushort)i;
        }
    }

    public ushort[] Items { get; }

    public GF2p15p17()
    {
        Items = new ushort[FieldDegree];
    }

    public GF2p15p17(ushort[] elements)
    {
        Items = new ushort[FieldDegree];
        Array.Copy(elements, Items, Math.Min(elements.Length, FieldDegree));
    }

    public GF2p15p17(GF2p15p17 other)
    {
        Items = new ushort[FieldDegree];
        Array.Copy(other.Items, Items, FieldDegree);
    }

    public bool IsZero()
    {
        for (int i = 0; i < FieldDegree; i++)
            if (Items[i] != 0) return false;
        return true;
    }

    public bool IsOne()
    {
        if (Items[0] != 1) return false;
        for (int i = 1; i < FieldDegree; i++)
            if (Items[i] != 0) return false;
        return true;
    }

    public bool Equals(GF2p15p17 other)
    {
        for (int i = 0; i < FieldDegree; i++)
            if (Items[i] != other.Items[i]) return false;
        return true;
    }

    public static GF2p15p17 Add(GF2p15p17 a, GF2p15p17 b)
    {
        var result = new GF2p15p17();
        for (int i = 0; i < FieldDegree; i++)
            result.Items[i] = (ushort)(a.Items[i] ^ b.Items[i]);
        return result;
    }

    public static GF2p15p17 AddOne(GF2p15p17 a)
    {
        var result = new GF2p15p17(a);
        result.Items[0] ^= 1;
        return result;
    }

    private static void FullMultiply(int m, int n, ushort[] result, ushort[] a, ushort[] b)
    {
        Array.Clear(result, 0, m + n - 1);
        for (int i = 0; i < m; i++)
        {
            if (a[i] != 0)
            {
                for (int j = 0; j < n; j++)
                {
                    if (b[j] != 0)
                    {
                        int g = LogTable[a[i]] + LogTable[b[j]];
                        if (g >= 0x7fff) g -= 0x7fff;
                        result[i + j] ^= ExpTable[g];
                    }
                }
            }
        }
    }

    private static void ModularReduction(int n, ushort[] a)
    {
        // y^17 + y^3 + 1
        for (int i = n - 1; i > 16; i--)
        {
            if (a[i] != 0)
            {
                a[i - 17] ^= a[i];
                a[i - 17 + 3] ^= a[i];
                a[i] = 0;
            }
        }
    }

    public static GF2p15p17 Multiply(GF2p15p17 a, GF2p15p17 b)
    {
        var temp = new ushort[33]; // 16+16+1
        FullMultiply(17, 17, temp, a.Items, b.Items);
        ModularReduction(33, temp);
        var result = new GF2p15p17();
        Array.Copy(temp, result.Items, FieldDegree);
        return result;
    }

    public static GF2p15p17 Square(GF2p15p17 a)
    {
        var temp = new ushort[33];
        for (int i = 0; i < 17; i++)
        {
            if (a.Items[i] != 0)
            {
                int g = LogTable[a.Items[i]] * 2;
                if (g >= 0x7fff) g -= 0x7fff;
                temp[2 * i] = ExpTable[g];
            }
            else
            {
                temp[2 * i] = 0;
            }
        }
        for (int i = 1; i < 33; i += 2)
            temp[i] = 0;

        ModularReduction(33, temp);
        var result = new GF2p15p17();
        Array.Copy(temp, result.Items, FieldDegree);
        return result;
    }

    public static GF2p15p17 Inverse(GF2p15p17 a)
    {
        if (a.IsZero())
            throw new DivideByZeroException("Zero doesn't have inverse.");

        int degB, degC, degF, degG;
        var B = new ushort[34];
        var C = new ushort[34];
        var F = new ushort[34];
        var G = new ushort[34];

        // Initialize B = 1
        B[0] = 1;
        degB = 0;

        // Initialize C = 0
        degC = 0;

        // Initialize F = a
        degF = 0;
        for (int i = 0; i < 17; i++)
        {
            F[i] = a.Items[i];
            if (F[i] != 0) degF = i;
        }

        // Initialize G = y^17 + y^3 + 1
        G[0] = 1;
        G[3] = 1;
        G[17] = 1;
        degG = 17;

        // We'll use references to swap
        var lpF = F;
        var lpG = G;
        var lpB = B;
        var lpC = C;
        var refDegF = degF;
        var refDegG = degG;
        var refDegB = degB;
        var refDegC = degC;

        while (true)
        {
            if (refDegF == 0)
            {
                var result = new GF2p15p17();
                for (int i = 0; i <= refDegB; i++)
                {
                    if (lpB[i] != 0)
                    {
                        int g = LogTable[lpB[i]] - LogTable[lpF[0]];
                        if (g < 0) g += 0x7fff;
                        result.Items[i] = ExpTable[g];
                    }
                }
                return result;
            }

            if (refDegF < refDegG)
            {
                (lpF, lpG) = (lpG, lpF);
                (refDegF, refDegG) = (refDegG, refDegF);
                (lpB, lpC) = (lpC, lpB);
                (refDegB, refDegC) = (refDegC, refDegB);
            }

            int j = refDegF - refDegG;
            int gg = LogTable[lpF[refDegF]] - LogTable[lpG[refDegG]];
            if (gg < 0) gg += 0x7fff;
            ushort alpha = ExpTable[gg];

            // lpF += (alpha * x^j) * lpG
            AddScale(lpF, ref refDegF, alpha, j, lpG, refDegG);
            // lpB += (alpha * x^j) * lpC
            AddScale(lpB, ref refDegB, alpha, j, lpC, refDegC);
        }
    }

    private static void AddScale(ushort[] a, ref int degA, ushort alpha, int j, ushort[] b, int degB)
    {
        int logAlpha = LogTable[alpha];
        for (int i = 0; i <= degB; i++)
        {
            if (b[i] != 0)
            {
                int g = logAlpha + LogTable[b[i]];
                if (g >= 0x7fff) g -= 0x7fff;
                a[i + j] ^= ExpTable[g];
                if (a[i + j] != 0 && i + j > degA)
                    degA = i + j;
            }
        }
        while (degA > 0 && a[degA] == 0) degA--;
    }

    public static GF2p15p17 Divide(GF2p15p17 a, GF2p15p17 b)
    {
        return Multiply(a, Inverse(b));
    }

    public byte[] Dump()
    {
        var bytes = new byte[DumpSize];
        int left_bits = 8;
        int writeIdx = 0;

        for (int i = 0; i < 17; i++)
        {
            byte low8 = (byte)(Items[i] & 0xFF);
            byte high7 = (byte)(Items[i] >> 8);

            if (left_bits == 8)
            {
                bytes[writeIdx] = low8;
                writeIdx++;
            }
            else
            {
                bytes[writeIdx] |= (byte)(low8 << (8 - left_bits));
                writeIdx++;
                if (writeIdx < DumpSize)
                    bytes[writeIdx] = (byte)(low8 >> left_bits);
            }

            if (left_bits == 8)
            {
                if (writeIdx < DumpSize)
                    bytes[writeIdx] = high7;
                left_bits = 1;
            }
            else if (left_bits == 7)
            {
                bytes[writeIdx] |= (byte)(high7 << 1);
                writeIdx++;
                left_bits = 8;
            }
            else
            {
                bytes[writeIdx] |= (byte)(high7 << (8 - left_bits));
                writeIdx++;
                if (writeIdx < DumpSize)
                    bytes[writeIdx] = (byte)(high7 >> left_bits);
                left_bits = 8 - (7 - left_bits);
            }
        }
        return bytes;
    }
}
