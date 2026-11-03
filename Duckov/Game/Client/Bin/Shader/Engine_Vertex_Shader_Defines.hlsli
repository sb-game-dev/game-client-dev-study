
struct Material
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular; // w = SpecPower
    float4 Reflect;
};
cbuffer cbPerObject : register(b0)
{
    row_major float4x4 g_matWorld;
    row_major float4x4 g_matWorldInvTranspose;
    Material g_Material;
};

cbuffer FrameData : register(b1)
{
    row_major matrix g_ViewMatrix, g_ProjMatrix;
    row_major matrix g_OrthoViewMatrix, g_OrthoProjMatrix;
    
    row_major matrix g_ViewInverseMatrix, g_ProjInverseMatrix;
    row_major matrix g_OrthoViewInverseMatrix, g_OrthoProjInverseMatrix;
    float4 g_vEye;
};
