#if defined(PBR) && defined(DEFERRED)

/// Convert an RGB color into YCoCg
///     color: input color to convert
float3 YCoCg_FromRGB(in float3 color)
{
	return float3(
		0.25 * color.r + 0.5 * color.g + 0.25 * color.b,
		0.5 * color.r - 0.5 * color.b + 0.5,
		-0.25* color.r + 0.5 * color.g - 0.25 * color.b + 0.5);
}

/// Convert a YCoCg encoded color into RGB
///     ycocg: The YCoCg encoded color to convert
float3 YCoCg_ToRGB(in float3 ycocg)
{
	ycocg.y -= 0.5;
	ycocg.z -= 0.5;
	return float3(
		ycocg.r + ycocg.g - ycocg.b,
		ycocg.r + ycocg.b,
		ycocg.r - ycocg.g - ycocg.b);
}

/// Extract Albedo and specular components from interleaved
///     coords: screen coordinates of the interleaved pixel
float2 YCoCg_GetInterleaved(in float2 coords)
{
	return Sample2D(AlbedoBuffer, coords + float2(cGBufferInvSize.x, 0.0)).ga;
}

/// Encodes the normal as Lambert Azimuth equal-area
///     normal: world space normal to pack
///     viewDir: viewing direction vector of the camera
float2 EncodeNormal(in float3 normal, in float3 viewDir)
{
	float2 enc = normalize(normal.xy) * sqrt(-normal.z * 0.5 + 0.5);
	return enc * 0.5 + 0.5;
}

/// Decodes the normal from Lambert Azimuth equal-area packing
///     screenNormal: 2 channel packed normal from GBuffer
///     viewDir: viewing direction vector of the camera
float3 DecodeGBufferNormal(in float2 screenNormal, in float3 viewDir)
{
	float4 nn = float4(screenNormal, 0, 0) * float4(2, 2, 0, 0) + float4(-1, -1, 1, -1);
	float l = dot(nn.xyz, -nn.xyw);
	nn.z = l;
	nn.xy *= sqrt(l);
	return normalize(nn.xyz * 2 + float3(0, 0, -1));
}

/// Utility function for writing into the GBuffer, Places all GBuffer writes into a single place
///     screenPos: screen position of the pixel
///     albedo: albedo
///     specular: specular color
///     wsNormals: surface normal in worldspace
///     depth: depth position of the pixel
///     roughness: roughness of the surface
void WriteGBuffer(out float4 oAlbedo, out float4 oNormal, out float4 oDepth, in float3 viewDir, in float2 screenPos, in float4 albedo, in float3 specular, in float3 wsNormals, in float depth, in float roughness)
{
	// 2 channel normal
	oNormal.xy = EncodeNormal(wsNormals.xyz, viewDir);
	oNormal.z = roughness;
	oNormal.w = 0;

	// Interleave Co/Cg in a checkboard pattern        
	const float3 ycocgSpec = YCoCg_FromRGB(specular);
	const float3 ycocgAlbedo = YCoCg_FromRGB(albedo.rgb);

	int x = screenPos.x;
	int y = screenPos.y;
	bool pattern = x % 2 == y % 2.0;
	oAlbedo.r = ycocgAlbedo.r;
	oAlbedo.g = pattern ? ycocgAlbedo.b : ycocgAlbedo.g;
	oAlbedo.b = ycocgSpec.r;
	oAlbedo.a = pattern ? ycocgSpec.b : ycocgSpec.g;

	// Write depth
	oDepth = depth;
}

/// Extract YCoCg embedded abledo and specular
///     screenPos: position in the screen
///     coded: the encoded colors RGBA
///     abledo: output for decoded albedo
///     specColor: output for decoded specular color
void DecodeYCoCgElements(in float2 screenPos, in float4 coded, out float3 albedo, out float3 specColor)
{
	float2 interleaved = YCoCg_GetInterleaved(screenPos);
	float3 ycocgAlbedo = float3(coded.rg, interleaved.x);
	float3 ycocgSpecular = float3(coded.ba, interleaved.y);

	int x = screenPos.x / cGBufferInvSize.x;
	int y = screenPos.y / cGBufferInvSize.y;

	// swap channels if necessary
	const bool pattern = x % 2 == y % 2;
	ycocgAlbedo.rgb = pattern ? ycocgAlbedo.rbg : ycocgAlbedo.rgb;
	ycocgSpecular.rgb = pattern ? ycocgSpecular.rbg : ycocgSpecular.rgb;

	albedo = YCoCg_ToRGB(ycocgAlbedo);
	specColor = YCoCg_ToRGB(ycocgSpecular);
}

#endif