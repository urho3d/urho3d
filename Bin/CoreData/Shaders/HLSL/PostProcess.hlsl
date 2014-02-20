
static const float PI = 3.14159265;

float2 Noise(float2 coord)
{
    float noiseX = clamp(frac(sin(dot(coord, float2(12.9898, 78.233))) * 43758.5453), 0.0, 1.0);
    float noiseY = clamp(frac(sin(dot(coord, float2(12.9898, 78.233) * 2.0)) * 43758.5453), 0.0, 1.0);
    return float2(noiseX, noiseY);
}

// Adapted: http://callumhay.blogspot.com/2010/09/gaussian-blur-shader-glsl.html
float4 GaussianBlur(int blurKernelSize, float2 blurDir, float2 blurRadius, float sigma, sampler2D texSampler, float2 texCoord)
{
    const int blurKernelHalfSize = blurKernelSize / 2;

    // Incremental Gaussian Coefficent Calculation (See GPU Gems 3 pp. 877 - 889)
    float3 gaussCoeff;
    gaussCoeff.x = 1.0 / (sqrt(2.0 * PI) * sigma);
    gaussCoeff.y = exp(-0.5 / (sigma * sigma));
    gaussCoeff.z = gaussCoeff.y * gaussCoeff.y;

    float2 blurVec = blurRadius * blurDir;
    float4 avgValue = float4(0.0, 0.0, 0.0, 0.0);
    float gaussCoeffSum = 0.0;

    avgValue += tex2D(texSampler, texCoord) * gaussCoeff.x;
    gaussCoeffSum += gaussCoeff.x;
    gaussCoeff.xy *= gaussCoeff.yz;

    for (int i = 1; i <= blurKernelHalfSize; i++)
    {
        avgValue += tex2D(texSampler, texCoord - i * blurVec) * gaussCoeff.x;
        avgValue += tex2D(texSampler, texCoord + i * blurVec) * gaussCoeff.x;

        gaussCoeffSum += 2.0 * gaussCoeff.x;
        gaussCoeff.xy *= gaussCoeff.yz;
    }

    return avgValue / gaussCoeffSum;
}

static const float3 LumWeights = float3(0.2126, 0.7152, 0.0722);

float3 ReinhardEq3Tonemap(float3 x)
{
    return x / (x + 1.0);
}

float3 ReinhardEq4Tonemap(float3 x, float white)
{
    return x * (1.0 + x / white) / (1.0 + x);
}

// Unchared2 tone mapping (See http://filmicgames.com)
static const float A = 0.15;
static const float B = 0.50;
static const float C = 0.10;
static const float D = 0.20;
static const float E = 0.02;
static const float F = 0.30;

float3 Uncharted2Tonemap(float3 x)
{
   return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

float3 ColorCorrection(float3 color, sampler3D lut)
{
    float lutSize = 16.0;
    float scale = (lutSize - 1.0) / lutSize;
    float offset = 1.0 / (2.0 * lutSize);
    return tex3D(lut, clamp(color, 0.0, 1.0) * scale + offset).rgb;
}

static const float Gamma = 2.2;
static const float InverseGamma = 1.0 / 2.2;

float3 ToGamma(float3 color)
{
    return float3(pow(color, Gamma));
}

float3 ToInverseGamma(float3 color)
{
    return float3(pow(color, InverseGamma));
}
