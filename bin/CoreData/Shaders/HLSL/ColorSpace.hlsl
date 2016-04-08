float3 ToLinearTrue(float3 col)
{
    float3 ncol;

    if (col.r <= 0.04045)
    {
        ncol.r = col.r / 12.92;
    }
    else
    {
        ncol.r = pow((col.r + 0.055) / 1.055, 2.4);
    }

    if (col.g <= 0.04045)
    {
        ncol.g = col.g / 12.92;
    }
    else
    {
        ncol.g = pow((col.g + 0.055) / 1.055, 2.4);
    }

    if (col.b <= 0.04045)
    {
        ncol.b = col.b / 12.92;
    }
    else
    {
        ncol.b = pow((col.b + 0.055) / 1.055, 2.4);
    }

    return ncol;
}

float3 ToGammaTrue(float3 col)
{
    float3 ncol;

    if (col.r <= 0.0031308)
    {
        ncol.r = col.r * 12.92;
    }
    else
    {
        ncol.r = 1.055 * pow(col.r, 1.0 / 2.4) - 0.055;
    }

    if (col.g <= 0.0031308)
    {
        ncol.g = col.g * 12.92;
    }
    else
    {
        ncol.g = 1.055 * pow(col.g, 1.0 / 2.4) - 0.055;
    }

    if (col.b <= 0.0031308)
    {
        ncol.b = col.b * 12.92;
    }
    else
    {
        ncol.b = 1.055 * pow(col.b, 1.0 / 2.4) - 0.055;
    }

    return ncol;
}
