using System;

namespace WinRarKeygenGui.Core;

/// <summary>
/// Elliptic Curve over GF(2^m): y^2 + xy = x^3 + Ax^2 + B
/// </summary>
public class EllipticCurveGF2m
{
    public GF2p15p17 A { get; }
    public GF2p15p17 B { get; }

    public EllipticCurveGF2m(GF2p15p17 a, GF2p15p17 b)
    {
        if (b.IsZero()) throw new ArgumentException("B cannot be zero.");
        A = a;
        B = b;
    }

    public ECPoint GetInfinityPoint() => new(this);

    public ECPoint GetPoint(GF2p15p17 x, GF2p15p17 y) => new(this, x, y);
}

public class ECPoint
{
    private readonly EllipticCurveGF2m _curve;
    public GF2p15p17 X { get; private set; }
    public GF2p15p17 Y { get; private set; }

    public ECPoint(EllipticCurveGF2m curve)
    {
        _curve = curve;
        X = new GF2p15p17();
        Y = new GF2p15p17();
    }

    public ECPoint(EllipticCurveGF2m curve, GF2p15p17 x, GF2p15p17 y)
    {
        _curve = curve;
        X = new GF2p15p17(x);
        Y = new GF2p15p17(y);
    }

    public ECPoint(ECPoint other)
    {
        _curve = other._curve;
        X = new GF2p15p17(other.X);
        Y = new GF2p15p17(other.Y);
    }

    public bool IsAtInfinity() => X.IsZero() && Y.IsZero();

    public ECPoint Negate()
    {
        var result = new ECPoint(_curve);
        result.X = new GF2p15p17(X);
        result.Y = GF2p15p17.Add(X, Y);
        return result;
    }

    public ECPoint Double()
    {
        if (IsAtInfinity()) return new ECPoint(this);

        // m = Y/X + X
        var m = GF2p15p17.Add(GF2p15p17.Divide(Y, X), X);

        // NewX = m^2 + m + A
        var newX = GF2p15p17.Add(GF2p15p17.Add(GF2p15p17.Square(m), m), _curve.A);

        // NewY = X^2 + (m+1)*NewX
        var newY = GF2p15p17.Add(
            GF2p15p17.Multiply(GF2p15p17.AddOne(m), newX),
            GF2p15p17.Square(X)
        );

        return new ECPoint(_curve, newX, newY);
    }

    public ECPoint Add(ECPoint other)
    {
        if (IsAtInfinity()) return new ECPoint(other);
        if (other.IsAtInfinity()) return new ECPoint(this);

        if (X.Equals(other.X))
        {
            if (Y.Equals(other.Y))
                return Double();
            else
                return new ECPoint(_curve); // infinity
        }

        // m = (Y0 + Y1) / (X0 + X1)
        var m = GF2p15p17.Divide(
            GF2p15p17.Add(Y, other.Y),
            GF2p15p17.Add(X, other.X)
        );

        // NewX = m^2 + m + X0 + X1 + A
        var newX = GF2p15p17.Square(m);
        newX = GF2p15p17.Add(newX, m);
        newX = GF2p15p17.Add(newX, X);
        newX = GF2p15p17.Add(newX, other.X);
        newX = GF2p15p17.Add(newX, _curve.A);

        // NewY = m*(X0 + NewX) + NewX + Y0
        var newY = GF2p15p17.Multiply(m, GF2p15p17.Add(X, newX));
        newY = GF2p15p17.Add(newY, newX);
        newY = GF2p15p17.Add(newY, Y);

        return new ECPoint(_curve, newX, newY);
    }

    public ECPoint Multiply(BigInt n)
    {
        var result = new ECPoint(_curve);
        var temp = new ECPoint(this);
        int bitLen = n.BitLength();

        for (int i = 0; i < bitLen; i++)
        {
            if (n.TestBit(i))
                result = result.Add(temp);
            temp = temp.Double();
        }
        return result;
    }

    public byte[] DumpCompressed()
    {
        if (IsAtInfinity()) return new byte[] { 0x00 };

        var xBytes = X.Dump();
        var zBytes = GF2p15p17.Divide(Y, X).Dump();

        byte prefix = (zBytes[0] & 1) != 0 ? (byte)0x03 : (byte)0x02;

        // to big endian
        Array.Reverse(xBytes);
        var result = new byte[1 + xBytes.Length];
        result[0] = prefix;
        Array.Copy(xBytes, 0, result, 1, xBytes.Length);
        return result;
    }
}
