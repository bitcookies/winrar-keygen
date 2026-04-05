using System;
using System.Security.Cryptography;
using System.Text;

namespace WinRarKeygenGui.Core;

/// <summary>
/// Supported encodings for the generated key file.
/// </summary>
public enum KeyEncoding
{
    UTF8,
    ASCII,
    ANSI
}

/// <summary>
/// Holds all data for a WinRAR registration key.
/// </summary>
public class RegisterInfo
{
    public string UserName { get; set; } = "";
    public string LicenseType { get; set; } = "";
    public string UID { get; set; } = "";
    public string[] Items { get; set; } = new string[4];
    public uint Checksum { get; set; }
    public string HexData { get; set; } = "";
}

/// <summary>
/// Core key generation logic ported from the C++ WinRAR keygen.
/// </summary>
public static class WinRarKeygenCore
{
    private static BigInt GeneratePrivateKey(byte[]? seed)
    {
        uint[] generator = new uint[6];
        ushort[] rawPrivateKey = new ushort[15];

        if (seed != null && seed.Length > 0)
        {
            byte[] sha1Hash = SHA1.HashData(seed);
            for (int i = 0; i < 5; i++)
            {
                generator[i + 1] = BSwap32(BitConverter.ToUInt32(sha1Hash, i * 4));
            }
        }
        else
        {
            generator[1] = 0xeb3eb781;
            generator[2] = 0x50265329;
            generator[3] = 0xdc5ef4a3;
            generator[4] = 0x6847b9d5;
            generator[5] = 0xcde43b4c;
        }

        for (uint i = 0; i < 15; i++)
        {
            generator[0] = i + 1;
            byte[] genBytes = new byte[24];
            for (int j = 0; j < 6; j++)
            {
                byte[] b = BitConverter.GetBytes(generator[j]);
                Array.Copy(b, 0, genBytes, j * 4, 4);
            }
            byte[] sha1 = SHA1.HashData(genBytes);
            rawPrivateKey[i] = (ushort)BSwap32(BitConverter.ToUInt32(sha1, 0));
        }

        return new BigInt(false, rawPrivateKey);
    }

    private static ECPoint GeneratePublicKey(BigInt privateKey)
    {
        return WinRarConfig.G.Multiply(privateKey);
    }

    private static string GeneratePublicKeySM2CompressedFormat(string message)
    {
        byte[] msgBytes = Encoding.UTF8.GetBytes(message);
        var privateKey = GeneratePrivateKey(msgBytes);
        var publicKey = GeneratePublicKey(privateKey);
        var compressed = publicKey.DumpCompressed();

        // Extract X coordinate from compressed point (skip prefix byte)
        byte[] xBytes = new byte[compressed.Length - 1];
        Array.Copy(compressed, 1, xBytes, 0, xBytes.Length);
        var publicKeyXInteger = new BigInt(false, xBytes, false); // big-endian

        publicKeyXInteger = publicKeyXInteger * 2;
        if (compressed[0] == 0x03)
        {
            publicKeyXInteger.SetBit(0);
        }

        string hex = publicKeyXInteger.ToHexString();
        if (hex.Length < 64)
            hex = hex.PadLeft(64, '0');

        return hex;
    }

    private static readonly Random _rng = new();

    private static BigInt GenerateRandomInteger()
    {
        ushort[] raw = new ushort[15];
        for (int i = 0; i < 15; i++)
        {
            raw[i] = (ushort)_rng.Next(0, 0x10000);
        }
        return new BigInt(false, raw);
    }

    private static BigInt GenerateHashInteger(byte[] message)
    {
        byte[] sha1 = SHA1.HashData(message);
        uint[] rawHash = new uint[10];
        for (int i = 0; i < 5; i++)
        {
            rawHash[i] = BSwap32(BitConverter.ToUInt32(sha1, i * 4));
        }
        // SHA1("") with all-zeroed initial value
        rawHash[5] = 0x0ffd8d43;
        rawHash[6] = 0xb4e33c7c;
        rawHash[7] = 0x53461bd1;
        rawHash[8] = 0x0f27a546;
        rawHash[9] = 0x1050d90d;

        // Convert to ushort[15] little-endian (take first 240 bits)
        byte[] bytes = new byte[40];
        for (int i = 0; i < 10; i++)
        {
            byte[] b = BitConverter.GetBytes(rawHash[i]);
            Array.Copy(b, 0, bytes, i * 4, 4);
        }
        ushort[] rawResult = new ushort[15];
        for (int i = 0; i < 15; i++)
        {
            rawResult[i] = BitConverter.ToUInt16(bytes, i * 2);
        }
        return new BigInt(false, rawResult);
    }

    private static (BigInt r, BigInt s) Sign(byte[] data)
    {
        BigInt hash = GenerateHashInteger(data);

        while (true)
        {
            BigInt random = GenerateRandomInteger();

            // r = (G * random).X + hash mod Order
            var point = WinRarConfig.G.Multiply(random);
            var xBytes = point.X.Dump();
            var r = new BigInt();
            r.Load(false, xBytes, true);
            r = (r + hash) % WinRarConfig.Order;

            if (r.IsZero() || r + random == WinRarConfig.Order)
                continue;

            // s = (random - PrivateKey * r) mod Order
            var s = (random - WinRarConfig.PrivateKey * r) % WinRarConfig.Order;
            if (s.IsZero())
                continue;

            return (r, s);
        }
    }

    private static void CalculateChecksum(RegisterInfo info)
    {
        byte[] licBytes = Encoding.UTF8.GetBytes(info.LicenseType);
        byte[] userBytes = Encoding.UTF8.GetBytes(info.UserName);
        byte[] item0 = Encoding.UTF8.GetBytes(info.Items[0]);
        byte[] item1 = Encoding.UTF8.GetBytes(info.Items[1]);
        byte[] item2 = Encoding.UTF8.GetBytes(info.Items[2]);
        byte[] item3 = Encoding.UTF8.GetBytes(info.Items[3]);

        // Concatenate: LicenseType + UserName + Items[0..3]
        int totalLen = licBytes.Length + userBytes.Length + item0.Length + item1.Length + item2.Length + item3.Length;
        byte[] all = new byte[totalLen];
        int offset = 0;
        Array.Copy(licBytes, 0, all, offset, licBytes.Length); offset += licBytes.Length;
        Array.Copy(userBytes, 0, all, offset, userBytes.Length); offset += userBytes.Length;
        Array.Copy(item0, 0, all, offset, item0.Length); offset += item0.Length;
        Array.Copy(item1, 0, all, offset, item1.Length); offset += item1.Length;
        Array.Copy(item2, 0, all, offset, item2.Length); offset += item2.Length;
        Array.Copy(item3, 0, all, offset, item3.Length);

        // Incremental CRC32 (no final inversion, matching the C++ implementation)
        uint crc = 0xFFFFFFFF;
        foreach (byte b in all)
        {
            crc ^= b;
            for (int i = 0; i < 8; i++)
            {
                if ((crc & 1) != 0)
                    crc = (crc >> 1) ^ 0xEDB88320;
                else
                    crc >>= 1;
            }
        }
        info.Checksum = crc;
    }

    public static RegisterInfo GenerateRegisterInfo(string userName, string licenseType)
    {
        var info = new RegisterInfo
        {
            UserName = userName,
            LicenseType = licenseType
        };

        string temp = GeneratePublicKeySM2CompressedFormat(userName);
        info.Items[3] = $"60{temp[..48]}";
        info.Items[0] = GeneratePublicKeySM2CompressedFormat(info.Items[3]);
        info.UID = $"{temp[48..]}{info.Items[0][..4]}";

        // Sign license type
        while (true)
        {
            var (r, s) = Sign(Encoding.UTF8.GetBytes(info.LicenseType));
            string rHex = r.ToHexString().PadLeft(60, '0');
            string sHex = s.ToHexString().PadLeft(60, '0');
            if (rHex.Length == 60 && sHex.Length == 60)
            {
                info.Items[1] = $"60{sHex}{rHex}";
                break;
            }
        }

        // Sign username + items[0]
        string signData = info.UserName + info.Items[0];
        while (true)
        {
            var (r, s) = Sign(Encoding.UTF8.GetBytes(signData));
            string rHex = r.ToHexString().PadLeft(60, '0');
            string sHex = s.ToHexString().PadLeft(60, '0');
            if (rHex.Length == 60 && sHex.Length == 60)
            {
                info.Items[2] = $"60{sHex}{rHex}";
                break;
            }
        }

        CalculateChecksum(info);

        info.HexData = $"{info.Items[0].Length}{info.Items[1].Length}{info.Items[2].Length}{info.Items[3].Length}" +
                       $"{info.Items[0]}{info.Items[1]}{info.Items[2]}{info.Items[3]}" +
                       $"{info.Checksum:D10}";

        return info;
    }

    /// <summary>
    /// Builds the full rarreg.key file content as raw bytes, matching the CLI binary output.
    /// </summary>
    public static byte[] BuildRegFileBytes(RegisterInfo info, KeyEncoding encoding)
    {
        // Select encoding: username and license are encoded accordingly;
        // hex data, UID, and structural parts are always pure ASCII.
        var enc = encoding switch
        {
            KeyEncoding.ANSI => Encoding.Default,  // system ANSI codepage
            KeyEncoding.ASCII => Encoding.ASCII,
            _ => new UTF8Encoding(false)            // UTF-8 without BOM
        };

        using var ms = new System.IO.MemoryStream();
        void WriteStr(string s) { byte[] b = enc.GetBytes(s); ms.Write(b, 0, b.Length); }
        void WriteCRLF() { ms.WriteByte(0x0D); ms.WriteByte(0x0A); }

        WriteStr("RAR registration data"); WriteCRLF();
        WriteStr(info.UserName); WriteCRLF();
        WriteStr(info.LicenseType); WriteCRLF();
        WriteStr("UID=" + info.UID); WriteCRLF();
        for (int i = 0; i < info.HexData.Length; i += 54)
        {
            int len = Math.Min(54, info.HexData.Length - i);
            WriteStr(info.HexData.Substring(i, len)); WriteCRLF();
        }
        return ms.ToArray();
    }

    /// <summary>
    /// Builds the display text for the UI with standard line endings.
    /// </summary>
    public static string BuildDisplayText(RegisterInfo info, string displayUser, string displayLicense)
    {
        var sb = new StringBuilder();
        sb.AppendLine("RAR registration data");
        sb.AppendLine(displayUser);
        sb.AppendLine(displayLicense);
        sb.AppendLine("UID=" + info.UID);
        for (int i = 0; i < info.HexData.Length; i += 54)
        {
            int len = Math.Min(54, info.HexData.Length - i);
            sb.AppendLine(info.HexData.Substring(i, len));
        }
        return sb.ToString().TrimEnd();
    }

    /// <summary>
    /// Processes encoding for username and license, returning the encoded strings
    /// for key generation and the display strings (which may include the utf8: prefix).
    /// </summary>
    public static (string user, string license, string displayUser, string displayLicense) ProcessEncoding(
        string username, string licenseName, KeyEncoding encoding)
    {
        string displayUser = username;
        string displayLicense = licenseName;

        switch (encoding)
        {
            case KeyEncoding.UTF8:
                bool userHasNonAscii = HasNonAscii(username);
                bool licHasNonAscii = HasNonAscii(licenseName);

                if (userHasNonAscii && !username.StartsWith("utf8:"))
                    displayUser = "utf8:" + username;
                if (licHasNonAscii && !licenseName.StartsWith("utf8:"))
                    displayLicense = "utf8:" + licenseName;
                break;

            case KeyEncoding.ASCII:
                if (HasNonAscii(username))
                    throw new InvalidOperationException("Username contains non-ASCII characters. Use UTF-8 encoding.");
                if (HasNonAscii(licenseName))
                    throw new InvalidOperationException("License name contains non-ASCII characters. Use UTF-8 encoding.");
                break;

            case KeyEncoding.ANSI:
                // ANSI uses the system default code page
                break;
        }

        return (displayUser, displayLicense, displayUser, displayLicense);
    }

    private static bool HasNonAscii(string s)
    {
        foreach (char c in s)
            if (c > 127) return true;
        return false;
    }

    private static uint BSwap32(uint v)
    {
        return ((v & 0xFF) << 24) |
               ((v & 0xFF00) << 8) |
               ((v & 0xFF0000) >> 8) |
               ((v & 0xFF000000) >> 24);
    }
}
