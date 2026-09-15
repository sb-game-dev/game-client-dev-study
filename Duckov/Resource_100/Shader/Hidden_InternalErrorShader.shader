//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/InternalErrorShader" {
    Properties {
    }
    SubShader {
        Pass {
            GpuProgramID 57320
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "gles3 " {
                    "#ifdef VERTEX
                    #version 300 es
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    in highp vec4 in_POSITION0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    void main()
                    {
                        SV_Target0 = vec4(1.0, 0.0, 1.0, 1.0);
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "metal " {
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                        float4 hlslcc_mtx4x4unity_MatrixVP[4];
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float4 POSITION0 [[ attribute(0) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 mtl_Position [[ position, invariant ]];
                    };
                    
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        float4 u_xlat1;
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
                        output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
                        return output;
                    }
                    "
                }
                SubProgram "glcore " {
                    "#ifdef VERTEX
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    in  vec4 in_POSITION0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    layout(location = 0) out vec4 SV_Target0;
                    void main()
                    {
                        SV_Target0 = vec4(1.0, 0.0, 1.0, 1.0);
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_SINGLE_PASS_STEREO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "gles3 " {
                    Keywords { "UNITY_SINGLE_PASS_STEREO" }
                    "#ifdef VERTEX
                    #version 300 es
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    UNITY_BINDING(0) uniform UnityStereoGlobals {
                    #endif
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixP[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixV[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixInvV[8];
                    	UNITY_UNIFORM vec4                hlslcc_mtx4x4unity_StereoMatrixVP[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraProjection[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraInvProjection[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoWorldToCamera[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraToWorld[8];
                    	UNITY_UNIFORM vec3 Xhlslcc_UnusedXunity_StereoWorldSpaceCameraPos[2];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXunity_StereoScaleOffset[2];
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    };
                    #endif
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    UNITY_BINDING(1) uniform UnityStereoEyeIndex {
                    #endif
                    	UNITY_UNIFORM int                unity_StereoEyeIndex;
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    };
                    #endif
                    in highp vec4 in_POSITION0;
                    vec4 u_xlat0;
                    int u_xlati1;
                    vec4 u_xlat2;
                    void main()
                    {
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlati1 = int(unity_StereoEyeIndex << (2 & int(0x1F)));
                        u_xlat2 = u_xlat0.yyyy * hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 1)];
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[u_xlati1] * u_xlat0.xxxx + u_xlat2;
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 2)] * u_xlat0.zzzz + u_xlat2;
                        gl_Position = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 3)] * u_xlat0.wwww + u_xlat2;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    void main()
                    {
                        SV_Target0 = vec4(1.0, 0.0, 1.0, 1.0);
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "metal " {
                    Keywords { "UNITY_SINGLE_PASS_STEREO" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    };
                    
                    struct UnityStereoGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_StereoMatrixP[8];
                        float4 hlslcc_mtx4x4unity_StereoMatrixV[8];
                        float4 hlslcc_mtx4x4unity_StereoMatrixInvV[8];
                        float4 hlslcc_mtx4x4unity_StereoMatrixVP[8];
                        float4 hlslcc_mtx4x4unity_StereoCameraProjection[8];
                        float4 hlslcc_mtx4x4unity_StereoCameraInvProjection[8];
                        float4 hlslcc_mtx4x4unity_StereoWorldToCamera[8];
                        float4 hlslcc_mtx4x4unity_StereoCameraToWorld[8];
                        float3 unity_StereoWorldSpaceCameraPos[2];
                        float4 unity_StereoScaleOffset[2];
                    };
                    
                    struct UnityStereoEyeIndex_Type
                    {
                        int unity_StereoEyeIndex;
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float4 POSITION0 [[ attribute(0) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 mtl_Position [[ position, invariant ]];
                    };
                    
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        constant UnityStereoGlobals_Type& UnityStereoGlobals [[ buffer(1) ]],
                        constant UnityStereoEyeIndex_Type& UnityStereoEyeIndex [[ buffer(2) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        int u_xlati1;
                        float4 u_xlat2;
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlati1 = UnityStereoEyeIndex.unity_StereoEyeIndex << 0x2;
                        u_xlat2 = u_xlat0.yyyy * UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 1)];
                        u_xlat2 = fma(UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[u_xlati1], u_xlat0.xxxx, u_xlat2);
                        u_xlat2 = fma(UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 2)], u_xlat0.zzzz, u_xlat2);
                        output.mtl_Position = fma(UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 3)], u_xlat0.wwww, u_xlat2);
                        return output;
                    }
                    "
                }
                SubProgram "glcore " {
                    Keywords { "UNITY_SINGLE_PASS_STEREO" }
                    "#ifdef VERTEX
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    UNITY_BINDING(0) uniform UnityStereoGlobals {
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixP[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixV[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixInvV[8];
                    	vec4                hlslcc_mtx4x4unity_StereoMatrixVP[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraProjection[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraInvProjection[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoWorldToCamera[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraToWorld[8];
                    	vec3 Xhlslcc_UnusedXunity_StereoWorldSpaceCameraPos[2];
                    	vec4 Xhlslcc_UnusedXunity_StereoScaleOffset[2];
                    };
                    UNITY_BINDING(1) uniform UnityStereoEyeIndex {
                    	int                unity_StereoEyeIndex;
                    };
                    in  vec4 in_POSITION0;
                    vec4 u_xlat0;
                    int u_xlati1;
                    vec4 u_xlat2;
                    void main()
                    {
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlati1 = unity_StereoEyeIndex << (2 & int(0x1F));
                        u_xlat2 = u_xlat0.yyyy * hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 1)];
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[u_xlati1] * u_xlat0.xxxx + u_xlat2;
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 2)] * u_xlat0.zzzz + u_xlat2;
                        gl_Position = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 3)] * u_xlat0.wwww + u_xlat2;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    layout(location = 0) out vec4 SV_Target0;
                    void main()
                    {
                        SV_Target0 = vec4(1.0, 0.0, 1.0, 1.0);
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "vulkan " {
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "STEREO_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "gles3 " {
                    Keywords { "STEREO_INSTANCING_ON" }
                    "#ifdef VERTEX
                    #version 300 es
                    #extension GL_AMD_vertex_shader_layer : require
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    UNITY_BINDING(0) uniform UnityStereoGlobals {
                    #endif
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixP[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixV[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixInvV[8];
                    	UNITY_UNIFORM vec4                hlslcc_mtx4x4unity_StereoMatrixVP[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraProjection[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraInvProjection[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoWorldToCamera[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraToWorld[8];
                    	UNITY_UNIFORM vec3 Xhlslcc_UnusedXunity_StereoWorldSpaceCameraPos[2];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXunity_StereoScaleOffset[2];
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    };
                    #endif
                    in highp vec4 in_POSITION0;
                    flat out highp uint vs_BLENDINDICES0;
                    float u_xlat0;
                    uint u_xlatu0;
                    vec4 u_xlat1;
                    vec4 u_xlat2;
                    int u_xlati3;
                    void main()
                    {
                        u_xlat0 = float(uint(gl_InstanceID));
                        u_xlat0 = u_xlat0 * 0.5;
                        u_xlat0 = fract(u_xlat0);
                        u_xlat0 = u_xlat0 + u_xlat0;
                        u_xlat0 = roundEven(u_xlat0);
                        u_xlatu0 = uint(u_xlat0);
                        u_xlati3 = int(int(u_xlatu0) << (2 & int(0x1F)));
                        u_xlat1 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat1 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat1;
                        u_xlat1 = u_xlat1 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat2 = u_xlat1.yyyy * hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati3 + 1)];
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[u_xlati3] * u_xlat1.xxxx + u_xlat2;
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati3 + 2)] * u_xlat1.zzzz + u_xlat2;
                        gl_Position = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati3 + 3)] * u_xlat1.wwww + u_xlat2;
                        vs_BLENDINDICES0 = u_xlatu0;
                        gl_Layer = int(u_xlatu0);
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    void main()
                    {
                        SV_Target0 = vec4(1.0, 0.0, 1.0, 1.0);
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "metal " {
                    Keywords { "STEREO_INSTANCING_ON" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    };
                    
                    struct UnityStereoGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_StereoMatrixP[8];
                        float4 hlslcc_mtx4x4unity_StereoMatrixV[8];
                        float4 hlslcc_mtx4x4unity_StereoMatrixInvV[8];
                        float4 hlslcc_mtx4x4unity_StereoMatrixVP[8];
                        float4 hlslcc_mtx4x4unity_StereoCameraProjection[8];
                        float4 hlslcc_mtx4x4unity_StereoCameraInvProjection[8];
                        float4 hlslcc_mtx4x4unity_StereoWorldToCamera[8];
                        float4 hlslcc_mtx4x4unity_StereoCameraToWorld[8];
                        float3 unity_StereoWorldSpaceCameraPos[2];
                        float4 unity_StereoScaleOffset[2];
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float4 POSITION0 [[ attribute(0) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 mtl_Position [[ position, invariant ]];
                        uint mtl_Layer [[ render_target_array_index ]];
                    };
                    
                    constant bool has_base_vertex_instance [[ function_constant(4) ]];
                    		template <typename UVecType> UVecType bitFieldInsert(const UVecType width, const UVecType offset, const UVecType src2, const UVecType src3)
                    		{
                    			UVecType bitmask = (((UVecType(1) << width)-1) << offset) & 0xffffffff;
                    			return ((src2 << offset) & bitmask) | (src3 & ~bitmask);
                    		}; 
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        constant UnityStereoGlobals_Type& UnityStereoGlobals [[ buffer(1) ]],
                        uint mtl_InstanceID [[ instance_id ]],
                        uint mtl_BaseInstance [[ base_instance, function_constant(has_base_vertex_instance) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        if(has_base_vertex_instance)
                            mtl_InstanceID = mtl_InstanceID - mtl_BaseInstance;
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        int u_xlati1;
                        float4 u_xlat2;
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlati1 = int(bitFieldInsert(0x1u, 0x2u, mtl_InstanceID, 0x0u));
                        u_xlat2 = u_xlat0.yyyy * UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 1)];
                        u_xlat2 = fma(UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[u_xlati1], u_xlat0.xxxx, u_xlat2);
                        u_xlat2 = fma(UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 2)], u_xlat0.zzzz, u_xlat2);
                        output.mtl_Position = fma(UnityStereoGlobals.hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 3)], u_xlat0.wwww, u_xlat2);
                        output.mtl_Layer = int(mtl_InstanceID & 0x1u);
                        return output;
                    }
                    "
                }
                SubProgram "glcore " {
                    Keywords { "STEREO_INSTANCING_ON" }
                    "#ifdef VERTEX
                    #version 330
                    #extension GL_ARB_explicit_attrib_location : require
                    #extension GL_AMD_vertex_shader_layer : require
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    UNITY_BINDING(0) uniform UnityStereoGlobals {
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixP[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixV[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixInvV[8];
                    	vec4                hlslcc_mtx4x4unity_StereoMatrixVP[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraProjection[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraInvProjection[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoWorldToCamera[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraToWorld[8];
                    	vec3 Xhlslcc_UnusedXunity_StereoWorldSpaceCameraPos[2];
                    	vec4 Xhlslcc_UnusedXunity_StereoScaleOffset[2];
                    };
                    in  vec4 in_POSITION0;
                    flat out uint vs_BLENDINDICES0;
                    vec4 u_xlat0;
                    uint u_xlatu1;
                    vec4 u_xlat2;
                    int u_xlati4;
                    void main()
                    {
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlatu1 = uint(gl_InstanceID) & 1u;
                        u_xlati4 = int(u_xlatu1) << (2 & int(0x1F));
                        u_xlat2 = u_xlat0.yyyy * hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati4 + 1)];
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[u_xlati4] * u_xlat0.xxxx + u_xlat2;
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati4 + 2)] * u_xlat0.zzzz + u_xlat2;
                        gl_Position = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati4 + 3)] * u_xlat0.wwww + u_xlat2;
                        vs_BLENDINDICES0 = u_xlatu1;
                        gl_Layer = int(u_xlatu1);
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 330
                    #extension GL_ARB_explicit_attrib_location : require
                    
                    layout(location = 0) out vec4 SV_Target0;
                    void main()
                    {
                        SV_Target0 = vec4(1.0, 0.0, 1.0, 1.0);
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "UNITY_SINGLE_PASS_STEREO" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "STEREO_MULTIVIEW_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "gles3 " {
                    Keywords { "STEREO_MULTIVIEW_ON" }
                    "#ifdef VERTEX
                    #version 300 es
                    #extension GL_OVR_multiview2 : require
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    UNITY_BINDING(0) uniform UnityStereoGlobals {
                    #endif
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixP[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixV[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixInvV[8];
                    	UNITY_UNIFORM vec4                hlslcc_mtx4x4unity_StereoMatrixVP[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraProjection[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraInvProjection[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoWorldToCamera[8];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraToWorld[8];
                    	UNITY_UNIFORM vec3 Xhlslcc_UnusedXunity_StereoWorldSpaceCameraPos[2];
                    	UNITY_UNIFORM vec4 Xhlslcc_UnusedXunity_StereoScaleOffset[2];
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    };
                    #endif
                    layout(num_views = 2) in;
                    in highp vec4 in_POSITION0;
                    flat out highp uint vs_BLENDINDICES0;
                    vec4 u_xlat0;
                    int u_xlati1;
                    vec4 u_xlat2;
                    void main()
                    {
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlati1 = int(int(gl_ViewID_OVR) << (2 & int(0x1F)));
                        u_xlat2 = u_xlat0.yyyy * hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 1)];
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[u_xlati1] * u_xlat0.xxxx + u_xlat2;
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 2)] * u_xlat0.zzzz + u_xlat2;
                        gl_Position = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 3)] * u_xlat0.wwww + u_xlat2;
                        vs_BLENDINDICES0 = gl_ViewID_OVR;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    void main()
                    {
                        SV_Target0 = vec4(1.0, 0.0, 1.0, 1.0);
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "metal " {
                    Keywords { "STEREO_MULTIVIEW_ON" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                        float4 hlslcc_mtx4x4unity_MatrixVP[4];
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float4 POSITION0 [[ attribute(0) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 mtl_Position [[ position, invariant ]];
                    };
                    
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        float4 u_xlat1;
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
                        output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
                        return output;
                    }
                    "
                }
                SubProgram "glcore " {
                    Keywords { "STEREO_MULTIVIEW_ON" }
                    "#ifdef VERTEX
                    #version 330
                    #extension GL_ARB_explicit_attrib_location : require
                    #extension GL_OVR_multiview2 : require
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    UNITY_BINDING(0) uniform UnityStereoGlobals {
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixP[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixV[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoMatrixInvV[8];
                    	vec4                hlslcc_mtx4x4unity_StereoMatrixVP[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraProjection[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraInvProjection[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoWorldToCamera[8];
                    	vec4 Xhlslcc_UnusedXhlslcc_mtx4x4unity_StereoCameraToWorld[8];
                    	vec3 Xhlslcc_UnusedXunity_StereoWorldSpaceCameraPos[2];
                    	vec4 Xhlslcc_UnusedXunity_StereoScaleOffset[2];
                    };
                    layout(num_views = 2) in;
                    in  vec4 in_POSITION0;
                    flat out uint vs_BLENDINDICES0;
                    vec4 u_xlat0;
                    int u_xlati1;
                    vec4 u_xlat2;
                    void main()
                    {
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlati1 = int(gl_ViewID_OVR) << (2 & int(0x1F));
                        u_xlat2 = u_xlat0.yyyy * hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 1)];
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[u_xlati1] * u_xlat0.xxxx + u_xlat2;
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 2)] * u_xlat0.zzzz + u_xlat2;
                        gl_Position = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 3)] * u_xlat0.wwww + u_xlat2;
                        vs_BLENDINDICES0 = gl_ViewID_OVR;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 330
                    #extension GL_ARB_explicit_attrib_location : require
                    
                    layout(location = 0) out vec4 SV_Target0;
                    void main()
                    {
                        SV_Target0 = vec4(1.0, 0.0, 1.0, 1.0);
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "STEREO_INSTANCING_ON" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "gles " {
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec4 in_POSITION0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    #define SV_Target0 gl_FragData[0]
                    void main()
                    {
                        SV_Target0 = vec4(1.0, 0.0, 1.0, 1.0);
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "UNITY_SINGLE_PASS_STEREO" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_StereoMatrixVP[8];
                    uniform 	int unity_StereoEyeIndex;
                    attribute highp vec4 in_POSITION0;
                    vec4 u_xlat0;
                    int u_xlati1;
                    vec4 u_xlat2;
                    int op_shl(int a, int b) { return int(floor(float(a) * pow(2.0, float(b)))); }
                    ivec2 op_shl(ivec2 a, ivec2 b) { a.x = op_shl(a.x, b.x); a.y = op_shl(a.y, b.y); return a; }
                    ivec3 op_shl(ivec3 a, ivec3 b) { a.x = op_shl(a.x, b.x); a.y = op_shl(a.y, b.y); a.z = op_shl(a.z, b.z); return a; }
                    ivec4 op_shl(ivec4 a, ivec4 b) { a.x = op_shl(a.x, b.x); a.y = op_shl(a.y, b.y); a.z = op_shl(a.z, b.z); a.w = op_shl(a.w, b.w); return a; }
                    
                    void main()
                    {
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlati1 = op_shl(unity_StereoEyeIndex, 2);
                        u_xlat2 = u_xlat0.yyyy * hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 1)];
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[u_xlati1] * u_xlat0.xxxx + u_xlat2;
                        u_xlat2 = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 2)] * u_xlat0.zzzz + u_xlat2;
                        gl_Position = hlslcc_mtx4x4unity_StereoMatrixVP[(u_xlati1 + 3)] * u_xlat0.wwww + u_xlat2;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    #define SV_Target0 gl_FragData[0]
                    void main()
                    {
                        SV_Target0 = vec4(1.0, 0.0, 1.0, 1.0);
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "STEREO_MULTIVIEW_ON" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                    )
                    {
                        Mtl_FragmentOut output;
                        output.SV_Target0 = float4(1.0, 0.0, 1.0, 1.0);
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_SINGLE_PASS_STEREO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "UNITY_SINGLE_PASS_STEREO" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                    )
                    {
                        Mtl_FragmentOut output;
                        output.SV_Target0 = float4(1.0, 0.0, 1.0, 1.0);
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "STEREO_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "STEREO_INSTANCING_ON" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                    )
                    {
                        Mtl_FragmentOut output;
                        output.SV_Target0 = float4(1.0, 0.0, 1.0, 1.0);
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "STEREO_MULTIVIEW_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "STEREO_MULTIVIEW_ON" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                    )
                    {
                        Mtl_FragmentOut output;
                        output.SV_Target0 = float4(1.0, 0.0, 1.0, 1.0);
                        return output;
                    }
                    "
                }
            }
        }
        Pass {
            Name "DepthNormalsOnly"
            Tags { "LIGHTMODE" = "DepthNormalsOnly" }
            ColorMask 0 0
            Fog {
                Mode Off
            }
            GpuProgramID 77375
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                        float4 hlslcc_mtx4x4unity_MatrixVP[4];
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float3 POSITION0 [[ attribute(0) ]] ;
                        float4 COLOR0 [[ attribute(1) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 COLOR0 [[ user(COLOR0) ]];
                        float4 mtl_Position [[ position, invariant ]];
                    };
                    
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        float4 u_xlat1;
                        output.COLOR0 = input.COLOR0;
                        output.COLOR0 = clamp(output.COLOR0, 0.0f, 1.0f);
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
                        output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
                        return output;
                    }
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "FOG_LINEAR" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_LINEAR" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                        float4 hlslcc_mtx4x4unity_MatrixV[4];
                        float4 hlslcc_mtx4x4unity_MatrixVP[4];
                        float4 unity_FogParams;
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float3 POSITION0 [[ attribute(0) ]] ;
                        float4 COLOR0 [[ attribute(1) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 COLOR0 [[ user(COLOR0) ]];
                        float TEXCOORD0 [[ user(TEXCOORD0) ]];
                        float4 mtl_Position [[ position, invariant ]];
                    };
                    
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        float4 u_xlat1;
                        output.COLOR0 = input.COLOR0;
                        output.COLOR0 = clamp(output.COLOR0, 0.0f, 1.0f);
                        u_xlat0.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].xxx, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].zzz, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].www, u_xlat0.xyz);
                        u_xlat0.xyz = u_xlat0.xyz * input.POSITION0.yyy;
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.xxx, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.zzz, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].www, u_xlat1.xyz);
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        output.TEXCOORD0 = fma(u_xlat0.x, VGlobals.unity_FogParams.z, VGlobals.unity_FogParams.w);
                        output.TEXCOORD0 = clamp(output.TEXCOORD0, 0.0f, 1.0f);
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
                        output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
                        return output;
                    }
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "FOG_EXP" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_EXP" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                        float4 hlslcc_mtx4x4unity_MatrixV[4];
                        float4 hlslcc_mtx4x4unity_MatrixVP[4];
                        float4 unity_FogParams;
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float3 POSITION0 [[ attribute(0) ]] ;
                        float4 COLOR0 [[ attribute(1) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 COLOR0 [[ user(COLOR0) ]];
                        float TEXCOORD0 [[ user(TEXCOORD0) ]];
                        float4 mtl_Position [[ position, invariant ]];
                    };
                    
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        float4 u_xlat1;
                        output.COLOR0 = input.COLOR0;
                        output.COLOR0 = clamp(output.COLOR0, 0.0f, 1.0f);
                        u_xlat0.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].xxx, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].zzz, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].www, u_xlat0.xyz);
                        u_xlat0.xyz = u_xlat0.xyz * input.POSITION0.yyy;
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.xxx, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.zzz, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].www, u_xlat1.xyz);
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * VGlobals.unity_FogParams.y;
                        u_xlat0.x = exp2((-u_xlat0.x));
                        output.TEXCOORD0 = min(u_xlat0.x, 1.0);
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
                        output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
                        return output;
                    }
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "FOG_EXP2" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_EXP2" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                        float4 hlslcc_mtx4x4unity_MatrixV[4];
                        float4 hlslcc_mtx4x4unity_MatrixVP[4];
                        float4 unity_FogParams;
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float3 POSITION0 [[ attribute(0) ]] ;
                        float4 COLOR0 [[ attribute(1) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 COLOR0 [[ user(COLOR0) ]];
                        float TEXCOORD0 [[ user(TEXCOORD0) ]];
                        float4 mtl_Position [[ position, invariant ]];
                    };
                    
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        float4 u_xlat1;
                        output.COLOR0 = input.COLOR0;
                        output.COLOR0 = clamp(output.COLOR0, 0.0f, 1.0f);
                        u_xlat0.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].xxx, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].zzz, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].www, u_xlat0.xyz);
                        u_xlat0.xyz = u_xlat0.xyz * input.POSITION0.yyy;
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.xxx, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.zzz, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].www, u_xlat1.xyz);
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * VGlobals.unity_FogParams.x;
                        u_xlat0.x = u_xlat0.x * (-u_xlat0.x);
                        output.TEXCOORD0 = exp2(u_xlat0.x);
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
                        output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
                        return output;
                    }
                    "
                }
                SubProgram "gles " {
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec3 in_POSITION0;
                    attribute mediump vec4 in_COLOR0;
                    varying mediump vec4 vs_COLOR0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    varying mediump vec4 vs_COLOR0;
                    #define SV_Target0 gl_FragData[0]
                    void main()
                    {
                        SV_Target0 = vs_COLOR0;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "FOG_LINEAR" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    attribute highp vec3 in_POSITION0;
                    attribute mediump vec4 in_COLOR0;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.z + unity_FogParams.w;
                        u_xlat0.x = clamp(u_xlat0.x, 0.0, 1.0);
                        vs_TEXCOORD0 = u_xlat0.x;
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	mediump vec4 unity_FogColor;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "FOG_EXP" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    attribute highp vec3 in_POSITION0;
                    attribute mediump vec4 in_COLOR0;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.y;
                        u_xlat0.x = exp2((-u_xlat0.x));
                        u_xlat0.x = min(u_xlat0.x, 1.0);
                        vs_TEXCOORD0 = u_xlat0.x;
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	mediump vec4 unity_FogColor;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "FOG_EXP2" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    attribute highp vec3 in_POSITION0;
                    attribute mediump vec4 in_COLOR0;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.x;
                        u_xlat0.x = u_xlat0.x * (-u_xlat0.x);
                        vs_TEXCOORD0 = exp2(u_xlat0.x);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	mediump vec4 unity_FogColor;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    "#ifdef VERTEX
                    #version 300 es
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    in highp vec3 in_POSITION0;
                    in mediump vec4 in_COLOR0;
                    out mediump vec4 vs_COLOR0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    in mediump vec4 vs_COLOR0;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    void main()
                    {
                        SV_Target0 = vs_COLOR0;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    "#ifdef VERTEX
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    in  vec3 in_POSITION0;
                    in  vec4 in_COLOR0;
                    out vec4 vs_COLOR0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    in  vec4 vs_COLOR0;
                    layout(location = 0) out vec4 SV_Target0;
                    void main()
                    {
                        SV_Target0 = vs_COLOR0;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "FOG_LINEAR" }
                    "#ifdef VERTEX
                    #version 300 es
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in highp vec3 in_POSITION0;
                    in mediump vec4 in_COLOR0;
                    out mediump vec4 vs_COLOR0;
                    out mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.z + unity_FogParams.w;
                        u_xlat0.x = clamp(u_xlat0.x, 0.0, 1.0);
                        vs_TEXCOORD0 = u_xlat0.x;
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	mediump vec4 unity_FogColor;
                    in mediump vec4 vs_COLOR0;
                    in mediump float vs_TEXCOORD0;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "FOG_LINEAR" }
                    "#ifdef VERTEX
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in  vec3 in_POSITION0;
                    in  vec4 in_COLOR0;
                    out vec4 vs_COLOR0;
                    out float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        vs_TEXCOORD0 = u_xlat0.x * unity_FogParams.z + unity_FogParams.w;
                        vs_TEXCOORD0 = clamp(vs_TEXCOORD0, 0.0, 1.0);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 unity_FogColor;
                    in  vec4 vs_COLOR0;
                    in  float vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec3 u_xlat0;
                    void main()
                    {
                        u_xlat0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "FOG_EXP" }
                    "#ifdef VERTEX
                    #version 300 es
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in highp vec3 in_POSITION0;
                    in mediump vec4 in_COLOR0;
                    out mediump vec4 vs_COLOR0;
                    out mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.y;
                        u_xlat0.x = exp2((-u_xlat0.x));
                        u_xlat0.x = min(u_xlat0.x, 1.0);
                        vs_TEXCOORD0 = u_xlat0.x;
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	mediump vec4 unity_FogColor;
                    in mediump vec4 vs_COLOR0;
                    in mediump float vs_TEXCOORD0;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "FOG_EXP" }
                    "#ifdef VERTEX
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in  vec3 in_POSITION0;
                    in  vec4 in_COLOR0;
                    out vec4 vs_COLOR0;
                    out float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.y;
                        u_xlat0.x = exp2((-u_xlat0.x));
                        vs_TEXCOORD0 = min(u_xlat0.x, 1.0);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 unity_FogColor;
                    in  vec4 vs_COLOR0;
                    in  float vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec3 u_xlat0;
                    void main()
                    {
                        u_xlat0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "FOG_EXP2" }
                    "#ifdef VERTEX
                    #version 300 es
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in highp vec3 in_POSITION0;
                    in mediump vec4 in_COLOR0;
                    out mediump vec4 vs_COLOR0;
                    out mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.x;
                        u_xlat0.x = u_xlat0.x * (-u_xlat0.x);
                        vs_TEXCOORD0 = exp2(u_xlat0.x);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	mediump vec4 unity_FogColor;
                    in mediump vec4 vs_COLOR0;
                    in mediump float vs_TEXCOORD0;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "FOG_EXP2" }
                    "#ifdef VERTEX
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in  vec3 in_POSITION0;
                    in  vec4 in_COLOR0;
                    out vec4 vs_COLOR0;
                    out float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.x;
                        u_xlat0.x = u_xlat0.x * (-u_xlat0.x);
                        vs_TEXCOORD0 = exp2(u_xlat0.x);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 unity_FogColor;
                    in  vec4 vs_COLOR0;
                    in  float vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec3 u_xlat0;
                    void main()
                    {
                        u_xlat0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "vulkan " {
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct Mtl_FragmentIn
                    {
                        float4 COLOR0 [[ user(COLOR0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        output.SV_Target0 = input.COLOR0;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_LINEAR" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        float4 unity_FogColor;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float4 COLOR0 [[ user(COLOR0) ]] ;
                        float TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float3 u_xlat0;
                        u_xlat0.xyz = input.COLOR0.xyz + (-FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.xyz = fma(float3(input.TEXCOORD0), u_xlat0.xyz, FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.w = input.COLOR0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_EXP" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        float4 unity_FogColor;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float4 COLOR0 [[ user(COLOR0) ]] ;
                        float TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float3 u_xlat0;
                        u_xlat0.xyz = input.COLOR0.xyz + (-FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.xyz = fma(float3(input.TEXCOORD0), u_xlat0.xyz, FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.w = input.COLOR0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_EXP2" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        float4 unity_FogColor;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float4 COLOR0 [[ user(COLOR0) ]] ;
                        float TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float3 u_xlat0;
                        u_xlat0.xyz = input.COLOR0.xyz + (-FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.xyz = fma(float3(input.TEXCOORD0), u_xlat0.xyz, FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.w = input.COLOR0.w;
                        return output;
                    }
                    "
                }
            }
        }
        Pass {
            Name "DepthOnly"
            Tags { "LIGHTMODE" = "DepthOnly" }
            ColorMask 0 0
            Fog {
                Mode Off
            }
            GpuProgramID 142911
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                        float4 hlslcc_mtx4x4unity_MatrixVP[4];
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float3 POSITION0 [[ attribute(0) ]] ;
                        float4 COLOR0 [[ attribute(1) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 COLOR0 [[ user(COLOR0) ]];
                        float4 mtl_Position [[ position, invariant ]];
                    };
                    
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        float4 u_xlat1;
                        output.COLOR0 = input.COLOR0;
                        output.COLOR0 = clamp(output.COLOR0, 0.0f, 1.0f);
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
                        output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
                        return output;
                    }
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "FOG_LINEAR" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_LINEAR" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                        float4 hlslcc_mtx4x4unity_MatrixV[4];
                        float4 hlslcc_mtx4x4unity_MatrixVP[4];
                        float4 unity_FogParams;
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float3 POSITION0 [[ attribute(0) ]] ;
                        float4 COLOR0 [[ attribute(1) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 COLOR0 [[ user(COLOR0) ]];
                        float TEXCOORD0 [[ user(TEXCOORD0) ]];
                        float4 mtl_Position [[ position, invariant ]];
                    };
                    
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        float4 u_xlat1;
                        output.COLOR0 = input.COLOR0;
                        output.COLOR0 = clamp(output.COLOR0, 0.0f, 1.0f);
                        u_xlat0.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].xxx, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].zzz, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].www, u_xlat0.xyz);
                        u_xlat0.xyz = u_xlat0.xyz * input.POSITION0.yyy;
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.xxx, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.zzz, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].www, u_xlat1.xyz);
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        output.TEXCOORD0 = fma(u_xlat0.x, VGlobals.unity_FogParams.z, VGlobals.unity_FogParams.w);
                        output.TEXCOORD0 = clamp(output.TEXCOORD0, 0.0f, 1.0f);
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
                        output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
                        return output;
                    }
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "FOG_EXP" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_EXP" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                        float4 hlslcc_mtx4x4unity_MatrixV[4];
                        float4 hlslcc_mtx4x4unity_MatrixVP[4];
                        float4 unity_FogParams;
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float3 POSITION0 [[ attribute(0) ]] ;
                        float4 COLOR0 [[ attribute(1) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 COLOR0 [[ user(COLOR0) ]];
                        float TEXCOORD0 [[ user(TEXCOORD0) ]];
                        float4 mtl_Position [[ position, invariant ]];
                    };
                    
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        float4 u_xlat1;
                        output.COLOR0 = input.COLOR0;
                        output.COLOR0 = clamp(output.COLOR0, 0.0f, 1.0f);
                        u_xlat0.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].xxx, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].zzz, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].www, u_xlat0.xyz);
                        u_xlat0.xyz = u_xlat0.xyz * input.POSITION0.yyy;
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.xxx, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.zzz, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].www, u_xlat1.xyz);
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * VGlobals.unity_FogParams.y;
                        u_xlat0.x = exp2((-u_xlat0.x));
                        output.TEXCOORD0 = min(u_xlat0.x, 1.0);
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
                        output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
                        return output;
                    }
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "FOG_EXP2" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_EXP2" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    struct VGlobals_Type
                    {
                        float4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                        float4 hlslcc_mtx4x4unity_MatrixV[4];
                        float4 hlslcc_mtx4x4unity_MatrixVP[4];
                        float4 unity_FogParams;
                    };
                    
                    struct Mtl_VertexIn
                    {
                        float3 POSITION0 [[ attribute(0) ]] ;
                        float4 COLOR0 [[ attribute(1) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 COLOR0 [[ user(COLOR0) ]];
                        float TEXCOORD0 [[ user(TEXCOORD0) ]];
                        float4 mtl_Position [[ position, invariant ]];
                    };
                    
                    vertex Mtl_VertexOut xlatMtlMain(
                        constant VGlobals_Type& VGlobals [[ buffer(0) ]],
                        Mtl_VertexIn input [[ stage_in ]])
                    {
                        Mtl_VertexOut output;
                        float4 u_xlat0;
                        float4 u_xlat1;
                        output.COLOR0 = input.COLOR0;
                        output.COLOR0 = clamp(output.COLOR0, 0.0f, 1.0f);
                        u_xlat0.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].xxx, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].zzz, u_xlat0.xyz);
                        u_xlat0.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1].www, u_xlat0.xyz);
                        u_xlat0.xyz = u_xlat0.xyz * input.POSITION0.yyy;
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.xxx, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2].www, u_xlat1.xyz);
                        u_xlat0.xyz = fma(u_xlat1.xyz, input.POSITION0.zzz, u_xlat0.xyz);
                        u_xlat1.xyz = VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * VGlobals.hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[0].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].xxx, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[2].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].zzz, u_xlat1.xyz);
                        u_xlat1.xyz = fma(VGlobals.hlslcc_mtx4x4unity_MatrixV[3].xyz, VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3].www, u_xlat1.xyz);
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * VGlobals.unity_FogParams.x;
                        u_xlat0.x = u_xlat0.x * (-u_xlat0.x);
                        output.TEXCOORD0 = exp2(u_xlat0.x);
                        u_xlat0 = input.POSITION0.yyyy * VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[0], input.POSITION0.xxxx, u_xlat0);
                        u_xlat0 = fma(VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[2], input.POSITION0.zzzz, u_xlat0);
                        u_xlat0 = u_xlat0 + VGlobals.hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * VGlobals.hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[0], u_xlat0.xxxx, u_xlat1);
                        u_xlat1 = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[2], u_xlat0.zzzz, u_xlat1);
                        output.mtl_Position = fma(VGlobals.hlslcc_mtx4x4unity_MatrixVP[3], u_xlat0.wwww, u_xlat1);
                        return output;
                    }
                    "
                }
                SubProgram "gles " {
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec3 in_POSITION0;
                    attribute mediump vec4 in_COLOR0;
                    varying mediump vec4 vs_COLOR0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    varying mediump vec4 vs_COLOR0;
                    #define SV_Target0 gl_FragData[0]
                    void main()
                    {
                        SV_Target0 = vs_COLOR0;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "FOG_LINEAR" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    attribute highp vec3 in_POSITION0;
                    attribute mediump vec4 in_COLOR0;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.z + unity_FogParams.w;
                        u_xlat0.x = clamp(u_xlat0.x, 0.0, 1.0);
                        vs_TEXCOORD0 = u_xlat0.x;
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	mediump vec4 unity_FogColor;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "FOG_EXP" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    attribute highp vec3 in_POSITION0;
                    attribute mediump vec4 in_COLOR0;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.y;
                        u_xlat0.x = exp2((-u_xlat0.x));
                        u_xlat0.x = min(u_xlat0.x, 1.0);
                        vs_TEXCOORD0 = u_xlat0.x;
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	mediump vec4 unity_FogColor;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "FOG_EXP2" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    attribute highp vec3 in_POSITION0;
                    attribute mediump vec4 in_COLOR0;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.x;
                        u_xlat0.x = u_xlat0.x * (-u_xlat0.x);
                        vs_TEXCOORD0 = exp2(u_xlat0.x);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	mediump vec4 unity_FogColor;
                    varying mediump vec4 vs_COLOR0;
                    varying mediump float vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    "#ifdef VERTEX
                    #version 300 es
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    in highp vec3 in_POSITION0;
                    in mediump vec4 in_COLOR0;
                    out mediump vec4 vs_COLOR0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    in mediump vec4 vs_COLOR0;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    void main()
                    {
                        SV_Target0 = vs_COLOR0;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    "#ifdef VERTEX
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    in  vec3 in_POSITION0;
                    in  vec4 in_COLOR0;
                    out vec4 vs_COLOR0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    in  vec4 vs_COLOR0;
                    layout(location = 0) out vec4 SV_Target0;
                    void main()
                    {
                        SV_Target0 = vs_COLOR0;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "FOG_LINEAR" }
                    "#ifdef VERTEX
                    #version 300 es
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in highp vec3 in_POSITION0;
                    in mediump vec4 in_COLOR0;
                    out mediump vec4 vs_COLOR0;
                    out mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.z + unity_FogParams.w;
                        u_xlat0.x = clamp(u_xlat0.x, 0.0, 1.0);
                        vs_TEXCOORD0 = u_xlat0.x;
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	mediump vec4 unity_FogColor;
                    in mediump vec4 vs_COLOR0;
                    in mediump float vs_TEXCOORD0;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "FOG_LINEAR" }
                    "#ifdef VERTEX
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in  vec3 in_POSITION0;
                    in  vec4 in_COLOR0;
                    out vec4 vs_COLOR0;
                    out float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        vs_TEXCOORD0 = u_xlat0.x * unity_FogParams.z + unity_FogParams.w;
                        vs_TEXCOORD0 = clamp(vs_TEXCOORD0, 0.0, 1.0);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 unity_FogColor;
                    in  vec4 vs_COLOR0;
                    in  float vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec3 u_xlat0;
                    void main()
                    {
                        u_xlat0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "FOG_EXP" }
                    "#ifdef VERTEX
                    #version 300 es
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in highp vec3 in_POSITION0;
                    in mediump vec4 in_COLOR0;
                    out mediump vec4 vs_COLOR0;
                    out mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.y;
                        u_xlat0.x = exp2((-u_xlat0.x));
                        u_xlat0.x = min(u_xlat0.x, 1.0);
                        vs_TEXCOORD0 = u_xlat0.x;
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	mediump vec4 unity_FogColor;
                    in mediump vec4 vs_COLOR0;
                    in mediump float vs_TEXCOORD0;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "FOG_EXP" }
                    "#ifdef VERTEX
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in  vec3 in_POSITION0;
                    in  vec4 in_COLOR0;
                    out vec4 vs_COLOR0;
                    out float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.y;
                        u_xlat0.x = exp2((-u_xlat0.x));
                        vs_TEXCOORD0 = min(u_xlat0.x, 1.0);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 unity_FogColor;
                    in  vec4 vs_COLOR0;
                    in  float vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec3 u_xlat0;
                    void main()
                    {
                        u_xlat0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "FOG_EXP2" }
                    "#ifdef VERTEX
                    #version 300 es
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in highp vec3 in_POSITION0;
                    in mediump vec4 in_COLOR0;
                    out mediump vec4 vs_COLOR0;
                    out mediump float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.x;
                        u_xlat0.x = u_xlat0.x * (-u_xlat0.x);
                        vs_TEXCOORD0 = exp2(u_xlat0.x);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    #extension GL_EXT_shader_framebuffer_fetch : enable
                    #endif
                    
                    precision highp float;
                    precision highp int;
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	mediump vec4 unity_FogColor;
                    in mediump vec4 vs_COLOR0;
                    in mediump float vs_TEXCOORD0;
                    #ifdef GL_EXT_shader_framebuffer_fetch
                    layout(location = 0) inout mediump vec4 SV_Target0;
                    #else
                    layout(location = 0) out mediump vec4 SV_Target0;
                    #endif
                    mediump vec3 u_xlat16_0;
                    void main()
                    {
                        u_xlat16_0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat16_0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "FOG_EXP2" }
                    "#ifdef VERTEX
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixV[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    uniform 	vec4 unity_FogParams;
                    in  vec3 in_POSITION0;
                    in  vec4 in_COLOR0;
                    out vec4 vs_COLOR0;
                    out float vs_TEXCOORD0;
                    vec4 u_xlat0;
                    vec4 u_xlat1;
                    void main()
                    {
                        vs_COLOR0 = in_COLOR0;
                        vs_COLOR0 = clamp(vs_COLOR0, 0.0, 1.0);
                        u_xlat0.xyz = hlslcc_mtx4x4unity_ObjectToWorld[1].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].xxx + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].zzz + u_xlat0.xyz;
                        u_xlat0.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[1].www + u_xlat0.xyz;
                        u_xlat0.xyz = u_xlat0.xyz * in_POSITION0.yyy;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[0].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[0].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.xxx + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[2].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[2].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat1.xyz * in_POSITION0.zzz + u_xlat0.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_ObjectToWorld[3].yyy * hlslcc_mtx4x4unity_MatrixV[1].xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[0].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].xxx + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[2].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].zzz + u_xlat1.xyz;
                        u_xlat1.xyz = hlslcc_mtx4x4unity_MatrixV[3].xyz * hlslcc_mtx4x4unity_ObjectToWorld[3].www + u_xlat1.xyz;
                        u_xlat0.xyz = u_xlat0.xyz + u_xlat1.xyz;
                        u_xlat0.x = dot(u_xlat0.xyz, u_xlat0.xyz);
                        u_xlat0.x = sqrt(u_xlat0.x);
                        u_xlat0.x = u_xlat0.x * unity_FogParams.x;
                        u_xlat0.x = u_xlat0.x * (-u_xlat0.x);
                        vs_TEXCOORD0 = exp2(u_xlat0.x);
                        u_xlat0 = in_POSITION0.yyyy * hlslcc_mtx4x4unity_ObjectToWorld[1];
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[0] * in_POSITION0.xxxx + u_xlat0;
                        u_xlat0 = hlslcc_mtx4x4unity_ObjectToWorld[2] * in_POSITION0.zzzz + u_xlat0;
                        u_xlat0 = u_xlat0 + hlslcc_mtx4x4unity_ObjectToWorld[3];
                        u_xlat1 = u_xlat0.yyyy * hlslcc_mtx4x4unity_MatrixVP[1];
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[0] * u_xlat0.xxxx + u_xlat1;
                        u_xlat1 = hlslcc_mtx4x4unity_MatrixVP[2] * u_xlat0.zzzz + u_xlat1;
                        gl_Position = hlslcc_mtx4x4unity_MatrixVP[3] * u_xlat0.wwww + u_xlat1;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 150
                    #extension GL_ARB_explicit_attrib_location : require
                    #ifdef GL_ARB_shader_bit_encoding
                    #extension GL_ARB_shader_bit_encoding : enable
                    #endif
                    
                    #define HLSLCC_ENABLE_UNIFORM_BUFFERS 1
                    #if HLSLCC_ENABLE_UNIFORM_BUFFERS
                    #define UNITY_UNIFORM
                    #else
                    #define UNITY_UNIFORM uniform
                    #endif
                    #define UNITY_SUPPORTS_UNIFORM_LOCATION 1
                    #if UNITY_SUPPORTS_UNIFORM_LOCATION
                    #define UNITY_LOCATION(x) layout(location = x)
                    #define UNITY_BINDING(x) layout(binding = x, std140)
                    #else
                    #define UNITY_LOCATION(x)
                    #define UNITY_BINDING(x) layout(std140)
                    #endif
                    uniform 	vec4 unity_FogColor;
                    in  vec4 vs_COLOR0;
                    in  float vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec3 u_xlat0;
                    void main()
                    {
                        u_xlat0.xyz = vs_COLOR0.xyz + (-unity_FogColor.xyz);
                        SV_Target0.xyz = vec3(vs_TEXCOORD0) * u_xlat0.xyz + unity_FogColor.xyz;
                        SV_Target0.w = vs_COLOR0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "vulkan " {
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct Mtl_FragmentIn
                    {
                        float4 COLOR0 [[ user(COLOR0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        output.SV_Target0 = input.COLOR0;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_LINEAR" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        float4 unity_FogColor;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float4 COLOR0 [[ user(COLOR0) ]] ;
                        float TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float3 u_xlat0;
                        u_xlat0.xyz = input.COLOR0.xyz + (-FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.xyz = fma(float3(input.TEXCOORD0), u_xlat0.xyz, FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.w = input.COLOR0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_EXP" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        float4 unity_FogColor;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float4 COLOR0 [[ user(COLOR0) ]] ;
                        float TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float3 u_xlat0;
                        u_xlat0.xyz = input.COLOR0.xyz + (-FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.xyz = fma(float3(input.TEXCOORD0), u_xlat0.xyz, FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.w = input.COLOR0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "FOG_EXP2" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        float4 unity_FogColor;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float4 COLOR0 [[ user(COLOR0) ]] ;
                        float TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float3 u_xlat0;
                        u_xlat0.xyz = input.COLOR0.xyz + (-FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.xyz = fma(float3(input.TEXCOORD0), u_xlat0.xyz, FGlobals.unity_FogColor.xyz);
                        output.SV_Target0.w = input.COLOR0.w;
                        return output;
                    }
                    "
                }
            }
        }
    }
}