//マトリクスバッファ
cbuffer WorldBuffer : register(b0)
{
    matrix World;
}

cbuffer ViewBuffer : register(b1)
{
    matrix View;
}

cbuffer Projection : register(b2)
{
    matrix Projection;
}

//rendererなんかのやつに合わせる
struct MATERIAL
{
    float4 Diffuse;
    float4 Ambient;
    float4 Specular;
    float4 Emission;
    float Shininess;
    float3 Dummy; //16bit境界用
};

struct LIGHT
{
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};

cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}

cbuffer LightBuffer : register(b4)
{
    LIGHT Light;
}

struct Bone
{
    matrix MATRIX;
    matrix Offset;
};

cbuffer BoneBuffer : register(b5)
{
    Bone bone[256];
}

struct VS_IN
{
    float4 position   : POSITIONT0;
    float4 normal     : NORMAL0;
    float4 color      : COLOR0;
    float2 texCoord   : TEXCOORD0;
    int boneNum       : BONE_NUM0;
    int4 boneIndex    : BONE_INDEX0;
    float4 boneWeight : BONE_WEIGHT0;
};

struct VS_OUT
{
    float4 position : SV_POSITION;
    float4 normal   : NORMAL0;
    float4 color    : COLOR0;
    float2 texCoord : TEXCOORD0;
};

//マテリアルバッファ
float4 main( in VS_IN vi, out VS_OUT vo)
{
    //matrix wvp;
    //wvp = mul(World, View);
    //wvp = mul(wvp, Projection);
    //
    //matrix  skinTransfrom = bone[vi.boneIndex[0]].MATRIX * vi.boneWeight[0];
    //        skinTransfrom += bone[vi.boneIndex[1]].MATRIX * vi.boneWeight[1];
    //        skinTransfrom += bone[vi.boneIndex[2]].MATRIX * vi.boneWeight[2];
    //        skinTransfrom += bone[vi.boneIndex[3]].MATRIX * vi.boneWeight[3];
    //
    //vo.position = mul(vi.position, skinTransfrom);
    //vo.position = mul(vo.position, wvp);
    //vo.normal = vi.normal;
    //vo.texCoord = vi.texCoord;
    //
    //float4 worldNormal, normal;
    //normal = float4(vi.normal.xyz, 0.0);
    //worldNormal = mul(normal, World);
    //worldNormal = normalize(worldNormal);
    //
    //float light = 0.5 - 0.5 * dot(Light.Direction.xyz, worldNormal.xyz);
    //
    //vo.color = vi.color * Material.Diffuse * light * Light.Diffuse;
    //vo.color += vi.color * Material.Ambient * Light.Ambient;
    //vo.color.a = 1.0;
}

