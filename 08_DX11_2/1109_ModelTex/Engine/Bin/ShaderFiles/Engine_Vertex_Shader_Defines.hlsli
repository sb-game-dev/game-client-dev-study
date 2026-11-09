

cbuffer ObjectData : register(b0)
{
    row_major matrix g_WorldMatrix;
};

cbuffer FrameData : register(b1)
{
    row_major matrix g_ViewMatrix, g_ProjMatrix;
    row_major matrix g_OrthoViewMatrix, g_OrthoProjMatrix;
    
    row_major matrix g_ViewInverseMatrix, g_ProjInverseMatrix;
    row_major matrix g_OrthoViewInverseMatrix, g_OrthoProjInverseMatrix;
    float4 g_vCamPosition;
};
