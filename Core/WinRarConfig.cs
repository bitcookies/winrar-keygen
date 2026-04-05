namespace WinRarKeygenGui.Core;

/// <summary>
/// WinRAR keygen configuration constants: curve parameters, generator point, order, and private key.
/// </summary>
public static class WinRarConfig
{
    private static EllipticCurveGF2m? _curve;
    private static ECPoint? _g;

    public static EllipticCurveGF2m Curve
    {
        get
        {
            _curve ??= new EllipticCurveGF2m(
                new GF2p15p17(), // A = 0
                new GF2p15p17(new ushort[] { 161 }) // B = 161
            );
            return _curve;
        }
    }

    public static ECPoint G
    {
        get
        {
            _g ??= Curve.GetPoint(
                new GF2p15p17(new ushort[]
                {
                    0x38CC, 0x052F, 0x2510, 0x45AA,
                    0x1B89, 0x4468, 0x4882, 0x0D67,
                    0x4FEB, 0x55CE, 0x0025, 0x4CB7,
                    0x0CC2, 0x59DC, 0x289E, 0x65E3,
                    0x56FD
                }),
                new GF2p15p17(new ushort[]
                {
                    0x31A7, 0x65F2, 0x18C4, 0x3412,
                    0x7388, 0x54C1, 0x539B, 0x4A02,
                    0x4D07, 0x12D6, 0x7911, 0x3B5E,
                    0x4F0E, 0x216F, 0x2BF2, 0x1974,
                    0x20DA
                })
            );
            return _g;
        }
    }

    public static readonly BigInt Order = new("0x1026dd85081b82314691ced9bbec30547840e4bf72d8b5e0d258442bbcd31");

    public static readonly BigInt PrivateKey = new("0x59fe6abcca90bdb95f0105271fa85fb9f11f467450c1ae9044b7fd61d65e");
}
