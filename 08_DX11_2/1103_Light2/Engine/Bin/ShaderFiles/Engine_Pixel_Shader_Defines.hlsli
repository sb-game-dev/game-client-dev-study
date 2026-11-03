
sampler g_PointSampler : register(s0);
sampler g_LinearSampler : register(s1);

cbuffer FrameData : register(b1)
{
    row_major matrix g_ViewMatrix, g_ProjMatrix;
    row_major matrix g_OrthoViewMatrix, g_OrthoProjMatrix;
    
    row_major matrix g_ViewInverseMatrix, g_ProjInverseMatrix;
    row_major matrix g_OrthoViewInverseMatrix, g_OrthoProjInverseMatrix;
    float4 g_vCamPosition;
};

static const vector g_vMtrlAmbient = 1.f;
static const vector g_vMtrlSpecular = 1.f;