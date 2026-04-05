using System;
using System.Numerics;

namespace WinRarKeygenGui.Core;

/// <summary>
/// BigInteger wrapper for the keygen algorithm, replacing the C++ mpz/GMP-based class.
/// </summary>
public class BigInt
{
    public BigInteger Value { get; set; }

    public BigInt()
    {
        Value = BigInteger.Zero;
    }

    public BigInt(BigInteger value)
    {
        Value = value;
    }

    public BigInt(BigInt other)
    {
        Value = other.Value;
    }

    /// <summary>
    /// Construct from hex string (with or without "0x" prefix).
    /// </summary>
    public BigInt(string hexStr)
    {
        if (hexStr.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
            hexStr = hexStr[2..];
        Value = BigInteger.Parse("0" + hexStr, System.Globalization.NumberStyles.HexNumber);
    }

    /// <summary>
    /// Construct from raw bytes (big endian or little endian).
    /// </summary>
    public BigInt(bool isNegative, byte[] buffer, bool littleEndian)
    {
        byte[] data;
        if (littleEndian)
        {
            // BigInteger expects little-endian with a leading zero byte to ensure positive
            data = new byte[buffer.Length + 1];
            Array.Copy(buffer, data, buffer.Length);
            data[buffer.Length] = 0; // ensure positive
        }
        else
        {
            // Convert big-endian to little-endian
            data = new byte[buffer.Length + 1];
            for (int i = 0; i < buffer.Length; i++)
                data[buffer.Length - 1 - i] = buffer[i];
            data[buffer.Length] = 0;
        }
        Value = new BigInteger(data);
        if (isNegative) Value = -Value;
    }

    /// <summary>
    /// Construct from ushort[] array (little-endian, matching C++ behavior).
    /// </summary>
    public BigInt(bool isNegative, ushort[] buffer)
    {
        var bytes = new byte[buffer.Length * 2 + 1];
        for (int i = 0; i < buffer.Length; i++)
        {
            bytes[i * 2] = (byte)(buffer[i] & 0xFF);
            bytes[i * 2 + 1] = (byte)(buffer[i] >> 8);
        }
        bytes[^1] = 0; // ensure positive
        Value = new BigInteger(bytes);
        if (isNegative) Value = -Value;
    }

    /// <summary>
    /// Load from byte buffer (matching C++ Load with little-endian).
    /// </summary>
    public void Load(bool isNegative, byte[] buffer, bool littleEndian)
    {
        byte[] data;
        if (littleEndian)
        {
            data = new byte[buffer.Length + 1];
            Array.Copy(buffer, data, buffer.Length);
        }
        else
        {
            data = new byte[buffer.Length + 1];
            for (int i = 0; i < buffer.Length; i++)
                data[buffer.Length - 1 - i] = buffer[i];
        }
        data[^1] = 0;
        Value = new BigInteger(data);
        if (isNegative) Value = -Value;
    }

    public bool IsZero() => Value.IsZero;
    public bool IsPositive() => Value.Sign > 0;
    public bool IsNegative() => Value.Sign < 0;

    public int BitLength() => Value.IsZero ? 0 : (int)Value.GetBitLength();

    public bool TestBit(int i) => !Value.IsZero && (Value >> i & BigInteger.One) == BigInteger.One;

    public void SetBit(int i) => Value |= BigInteger.One << i;

    public static BigInt operator +(BigInt a, BigInt b) => new(a.Value + b.Value);
    public static BigInt operator -(BigInt a, BigInt b) => new(a.Value - b.Value);
    public static BigInt operator *(BigInt a, BigInt b) => new(a.Value * b.Value);
    public static BigInt operator *(BigInt a, int b) => new(a.Value * b);

    /// <summary>
    /// Floor-division modulo, matching mpz_fdiv_r behavior for negative numbers.
    /// </summary>
    public static BigInt operator %(BigInt a, BigInt b)
    {
        var r = BigInteger.Remainder(a.Value, b.Value);
        if (r.Sign < 0) r += BigInteger.Abs(b.Value);
        return new BigInt(r);
    }

    public static bool operator ==(BigInt a, BigInt b)
    {
        if (a is null && b is null) return true;
        if (a is null || b is null) return false;
        return a.Value == b.Value;
    }
    public static bool operator !=(BigInt a, BigInt b) => !(a == b);

    public override bool Equals(object? obj) => obj is BigInt other && Value == other.Value;
    public override int GetHashCode() => Value.GetHashCode();

    /// <summary>
    /// Convert to hex string (lowercase), no "0x" prefix.
    /// </summary>
    public string ToHexString()
    {
        if (Value.IsZero) return "0";
        var hex = Value.ToString("x");
        // Remove leading zeros
        return hex.TrimStart('0');
    }

    /// <summary>
    /// Export as big-endian byte array (absolute value).
    /// </summary>
    public byte[] ToByteArrayBigEndian()
    {
        var bytes = BigInteger.Abs(Value).ToByteArray(); // little-endian, unsigned
        // Remove trailing zero if present
        int len = bytes.Length;
        while (len > 1 && bytes[len - 1] == 0) len--;
        var result = new byte[len];
        for (int i = 0; i < len; i++)
            result[len - 1 - i] = bytes[i];
        return result;
    }
}
