//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/FrameDebuggerRenderTargetDisplay" {
    Properties {
        _MainTex ("", any) = "black" { }
    }
    SubShader {
        Pass {
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 41681
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "gles " {
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec4 in_POSITION0;
                    attribute highp vec3 in_TEXCOORD0;
                    varying highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform lowp sampler2D _MainTex;
                    varying highp vec3 vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    vec4 u_xlat0;
                    ivec4 u_xlatu0;
                    mediump float u_xlat16_1;
                    vec3 u_xlat2;
                    vec3 u_xlat3;
                    float u_xlat6;
                    bool u_xlatb6;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  ivec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = int(0);
                        u_xlatu0.w = int(0);
                        u_xlat0 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), int(u_xlatu0.w));
                        u_xlat0 = u_xlat0 + (-_Levels.xxxx);
                        u_xlat16_1 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_1);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat2.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat6 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb6 = u_xlat6==1.0;
                        u_xlat0 = (bool(u_xlatb6)) ? u_xlat2.xxxx : u_xlat0;
                        u_xlat2.xyz = u_xlat0.xyz;
                        u_xlat2.xyz = clamp(u_xlat2.xyz, 0.0, 1.0);
                        u_xlat3.xyz = u_xlat2.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat3.xyz = u_xlat2.xyz * u_xlat3.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat2.xyz = u_xlat2.xyz * u_xlat3.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat2.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
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
                        float3 TEXCOORD0 [[ attribute(1) ]] ;
                    };
                    
                    struct Mtl_VertexOut
                    {
                        float4 mtl_Position [[ position, invariant ]];
                        float3 TEXCOORD0 [[ user(TEXCOORD0) ]];
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
                        output.TEXCOORD0.xyz = input.TEXCOORD0.xyz;
                        return output;
                    }
                    "
                }
                SubProgram "gles " {
                    Keywords { "_MSAA_2" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec4 in_POSITION0;
                    attribute highp vec3 in_TEXCOORD0;
                    varying highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform highp sampler2DMS _MainTex;
                    varying highp vec3 vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    vec4 u_xlat0;
                    ivec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  ivec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = int(0);
                        u_xlatu0.w = int(0);
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<2 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.5, 0.5, 0.5, 0.5) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "_MSAA_4" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec4 in_POSITION0;
                    attribute highp vec3 in_TEXCOORD0;
                    varying highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform highp sampler2DMS _MainTex;
                    varying highp vec3 vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    vec4 u_xlat0;
                    ivec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  ivec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = int(0);
                        u_xlatu0.w = int(0);
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<4 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.25, 0.25, 0.25, 0.25) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "_MSAA_8" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec4 in_POSITION0;
                    attribute highp vec3 in_TEXCOORD0;
                    varying highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform highp sampler2DMS _MainTex;
                    varying highp vec3 vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    vec4 u_xlat0;
                    ivec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  ivec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = int(0);
                        u_xlatu0.w = int(0);
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<8 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.125, 0.125, 0.125, 0.125) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "_TEX2DARRAY" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec4 in_POSITION0;
                    attribute highp vec3 in_TEXCOORD0;
                    varying highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform lowp sampler2DArray _MainTex;
                    varying highp vec3 vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    vec4 u_xlat0;
                    mediump float u_xlat16_1;
                    vec3 u_xlat2;
                    vec3 u_xlat3;
                    float u_xlat6;
                    bool u_xlatb6;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0 = texture(_MainTex, u_xlat0.xyz);
                        u_xlat0 = u_xlat0 + (-_Levels.xxxx);
                        u_xlat16_1 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_1);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat2.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat6 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb6 = u_xlat6==1.0;
                        u_xlat0 = (bool(u_xlatb6)) ? u_xlat2.xxxx : u_xlat0;
                        u_xlat2.xyz = u_xlat0.xyz;
                        u_xlat2.xyz = clamp(u_xlat2.xyz, 0.0, 1.0);
                        u_xlat3.xyz = u_xlat2.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat3.xyz = u_xlat2.xyz * u_xlat3.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat2.xyz = u_xlat2.xyz * u_xlat3.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat2.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
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
                    in highp vec4 in_POSITION0;
                    in highp vec3 in_TEXCOORD0;
                    out highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    UNITY_LOCATION(0) uniform mediump sampler2D _MainTex;
                    in highp vec3 vs_TEXCOORD0;
                    layout(location = 0) out highp vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    mediump float u_xlat16_1;
                    vec3 u_xlat2;
                    vec3 u_xlat3;
                    float u_xlat6;
                    bool u_xlatb6;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  uvec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = uint(uint(0u));
                        u_xlatu0.w = uint(uint(0u));
                        u_xlat0 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), int(u_xlatu0.w));
                        u_xlat0 = u_xlat0 + (-_Levels.xxxx);
                        u_xlat16_1 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_1);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat2.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat6 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb6 = u_xlat6==1.0;
                        u_xlat0 = (bool(u_xlatb6)) ? u_xlat2.xxxx : u_xlat0;
                        u_xlat2.xyz = u_xlat0.xyz;
                        u_xlat2.xyz = clamp(u_xlat2.xyz, 0.0, 1.0);
                        u_xlat3.xyz = u_xlat2.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat3.xyz = u_xlat2.xyz * u_xlat3.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat2.xyz = u_xlat2.xyz * u_xlat3.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat2.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
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
                    in  vec4 in_POSITION0;
                    in  vec3 in_TEXCOORD0;
                    out vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	vec4 _Levels;
                    uniform 	vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    UNITY_LOCATION(0) uniform  sampler2D _MainTex;
                    in  vec3 vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec3 u_xlat1;
                    vec3 u_xlat2;
                    float u_xlat4;
                    bool u_xlatb4;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  uvec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = uint(0u);
                        u_xlatu0.w = uint(0u);
                        u_xlat0 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), int(u_xlatu0.w));
                        u_xlat0 = u_xlat0 + (-_Levels.xxxx);
                        u_xlat1.x = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "_MSAA_2" "_TEX2DARRAY" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec4 in_POSITION0;
                    attribute highp vec3 in_TEXCOORD0;
                    varying highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #extension GL_OES_texture_storage_multisample_2d_array : require
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform 	float _MainTexDepth;
                    uniform highp sampler2DMSArray _MainTex;
                    varying highp vec3 vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    vec4 u_xlat0;
                    ivec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * vec3(_MainTexWidth, _MainTexHeight, _MainTexDepth);
                        u_xlatu0.xyz =  ivec3(ivec3(u_xlat0.xyz));
                        u_xlatu0.w = 0;
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<2 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.5, 0.5, 0.5, 0.5) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "_MSAA_2" }
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
                    in highp vec3 in_TEXCOORD0;
                    out highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    UNITY_LOCATION(0) uniform highp sampler2DMS _MainTex;
                    in highp vec3 vs_TEXCOORD0;
                    layout(location = 0) out highp vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  uvec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = uint(uint(0u));
                        u_xlatu0.w = uint(uint(0u));
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<2 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.5, 0.5, 0.5, 0.5) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "_MSAA_2" }
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
                    in  vec3 in_TEXCOORD0;
                    out vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	vec4 _Levels;
                    uniform 	vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    UNITY_LOCATION(0) uniform  sampler2DMS _MainTex;
                    in  vec3 vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    vec3 u_xlat2;
                    float u_xlat4;
                    bool u_xlatb4;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  uvec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = uint(0u);
                        u_xlatu0.w = uint(0u);
                        u_xlat1 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 0);
                        u_xlat0 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 1);
                        u_xlat0 = u_xlat0 + u_xlat1;
                        u_xlat0 = u_xlat0 * vec4(0.5, 0.5, 0.5, 0.5) + (-_Levels.xxxx);
                        u_xlat1.x = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "_MSAA_4" "_TEX2DARRAY" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec4 in_POSITION0;
                    attribute highp vec3 in_TEXCOORD0;
                    varying highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #extension GL_OES_texture_storage_multisample_2d_array : require
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform 	float _MainTexDepth;
                    uniform highp sampler2DMSArray _MainTex;
                    varying highp vec3 vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    vec4 u_xlat0;
                    ivec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * vec3(_MainTexWidth, _MainTexHeight, _MainTexDepth);
                        u_xlatu0.xyz =  ivec3(ivec3(u_xlat0.xyz));
                        u_xlatu0.w = 0;
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<4 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.25, 0.25, 0.25, 0.25) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "_MSAA_4" }
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
                    in highp vec3 in_TEXCOORD0;
                    out highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    UNITY_LOCATION(0) uniform highp sampler2DMS _MainTex;
                    in highp vec3 vs_TEXCOORD0;
                    layout(location = 0) out highp vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  uvec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = uint(uint(0u));
                        u_xlatu0.w = uint(uint(0u));
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<4 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.25, 0.25, 0.25, 0.25) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "_MSAA_4" }
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
                    in  vec3 in_TEXCOORD0;
                    out vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	vec4 _Levels;
                    uniform 	vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    UNITY_LOCATION(0) uniform  sampler2DMS _MainTex;
                    in  vec3 vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    vec4 u_xlat2;
                    float u_xlat4;
                    bool u_xlatb4;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  uvec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = uint(0u);
                        u_xlatu0.w = uint(0u);
                        u_xlat1 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 0);
                        u_xlat2 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 1);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 2);
                        u_xlat0 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 3);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat0 = u_xlat0 + u_xlat1;
                        u_xlat0 = u_xlat0 * vec4(0.25, 0.25, 0.25, 0.25) + (-_Levels.xxxx);
                        u_xlat1.x = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "_MSAA_8" "_TEX2DARRAY" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec4 in_POSITION0;
                    attribute highp vec3 in_TEXCOORD0;
                    varying highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    #extension GL_OES_texture_storage_multisample_2d_array : require
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform 	float _MainTexDepth;
                    uniform highp sampler2DMSArray _MainTex;
                    varying highp vec3 vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    vec4 u_xlat0;
                    ivec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * vec3(_MainTexWidth, _MainTexHeight, _MainTexDepth);
                        u_xlatu0.xyz =  ivec3(ivec3(u_xlat0.xyz));
                        u_xlatu0.w = 0;
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<8 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.125, 0.125, 0.125, 0.125) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "_MSAA_8" }
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
                    in highp vec3 in_TEXCOORD0;
                    out highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    UNITY_LOCATION(0) uniform highp sampler2DMS _MainTex;
                    in highp vec3 vs_TEXCOORD0;
                    layout(location = 0) out highp vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  uvec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = uint(uint(0u));
                        u_xlatu0.w = uint(uint(0u));
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<8 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.125, 0.125, 0.125, 0.125) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "_MSAA_8" }
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
                    in  vec3 in_TEXCOORD0;
                    out vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	vec4 _Levels;
                    uniform 	vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    UNITY_LOCATION(0) uniform  sampler2DMS _MainTex;
                    in  vec3 vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    vec4 u_xlat2;
                    float u_xlat4;
                    bool u_xlatb4;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.x = vs_TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * vec2(_MainTexWidth, _MainTexHeight);
                        u_xlatu0.xy =  uvec2(ivec2(u_xlat0.xy));
                        u_xlatu0.z = uint(0u);
                        u_xlatu0.w = uint(0u);
                        u_xlat1 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 0);
                        u_xlat2 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 1);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 2);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 3);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 4);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 5);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 6);
                        u_xlat0 = texelFetch(_MainTex, ivec2(u_xlatu0.xy), 7);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat0 = u_xlat0 + u_xlat1;
                        u_xlat0 = u_xlat0 * vec4(0.125, 0.125, 0.125, 0.125) + (-_Levels.xxxx);
                        u_xlat1.x = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles " {
                    Keywords { "_CUBEMAP" }
                    "#ifdef VERTEX
                    #version 100
                    
                    uniform 	vec4 hlslcc_mtx4x4unity_ObjectToWorld[4];
                    uniform 	vec4 hlslcc_mtx4x4unity_MatrixVP[4];
                    attribute highp vec4 in_POSITION0;
                    attribute highp vec3 in_TEXCOORD0;
                    varying highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 100
                    
                    #ifdef GL_FRAGMENT_PRECISION_HIGH
                        precision highp float;
                    #else
                        precision mediump float;
                    #endif
                    precision highp int;
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform highp samplerCube _MainTex;
                    varying highp vec3 vs_TEXCOORD0;
                    #define SV_Target0 gl_FragData[0]
                    vec4 u_xlat0;
                    mediump float u_xlat16_1;
                    vec3 u_xlat2;
                    vec3 u_xlat3;
                    float u_xlat6;
                    bool u_xlatb6;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0 = textureCube(_MainTex, u_xlat0.xyz);
                        u_xlat0 = u_xlat0 + (-_Levels.xxxx);
                        u_xlat16_1 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_1);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat2.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat6 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb6 = u_xlat6==1.0;
                        u_xlat0 = (bool(u_xlatb6)) ? u_xlat2.xxxx : u_xlat0;
                        u_xlat2.xyz = u_xlat0.xyz;
                        u_xlat2.xyz = clamp(u_xlat2.xyz, 0.0, 1.0);
                        u_xlat3.xyz = u_xlat2.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat3.xyz = u_xlat2.xyz * u_xlat3.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat2.xyz = u_xlat2.xyz * u_xlat3.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat2.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "_TEX2DARRAY" }
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
                    in highp vec3 in_TEXCOORD0;
                    out highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    UNITY_LOCATION(0) uniform mediump sampler2DArray _MainTex;
                    in highp vec3 vs_TEXCOORD0;
                    layout(location = 0) out highp vec4 SV_Target0;
                    vec4 u_xlat0;
                    mediump float u_xlat16_1;
                    vec3 u_xlat2;
                    vec3 u_xlat3;
                    float u_xlat6;
                    bool u_xlatb6;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0 = texture(_MainTex, u_xlat0.xyz);
                        u_xlat0 = u_xlat0 + (-_Levels.xxxx);
                        u_xlat16_1 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_1);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat2.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat6 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb6 = u_xlat6==1.0;
                        u_xlat0 = (bool(u_xlatb6)) ? u_xlat2.xxxx : u_xlat0;
                        u_xlat2.xyz = u_xlat0.xyz;
                        u_xlat2.xyz = clamp(u_xlat2.xyz, 0.0, 1.0);
                        u_xlat3.xyz = u_xlat2.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat3.xyz = u_xlat2.xyz * u_xlat3.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat2.xyz = u_xlat2.xyz * u_xlat3.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat2.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "_TEX2DARRAY" }
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
                    in  vec3 in_TEXCOORD0;
                    out vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	vec4 _Levels;
                    uniform 	vec4 _Channels;
                    UNITY_LOCATION(0) uniform  sampler2DArray _MainTex;
                    in  vec3 vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec4 u_xlat0;
                    vec3 u_xlat1;
                    vec3 u_xlat2;
                    float u_xlat4;
                    bool u_xlatb4;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0 = texture(_MainTex, u_xlat0.xyz);
                        u_xlat0 = u_xlat0 + (-_Levels.xxxx);
                        u_xlat1.x = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "vulkan " {
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "_MSAA_2" "_TEX2DARRAY" }
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
                    in highp vec3 in_TEXCOORD0;
                    out highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #extension GL_OES_texture_storage_multisample_2d_array : require
                    
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform 	float _MainTexDepth;
                    UNITY_LOCATION(0) uniform highp sampler2DMSArray _MainTex;
                    in highp vec3 vs_TEXCOORD0;
                    layout(location = 0) out highp vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * vec3(_MainTexWidth, _MainTexHeight, _MainTexDepth);
                        u_xlatu0.xyz =  uvec3(ivec3(u_xlat0.xyz));
                        u_xlatu0.w = uint(0u);
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<2 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.5, 0.5, 0.5, 0.5) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "_MSAA_2" "_TEX2DARRAY" }
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
                    in  vec3 in_TEXCOORD0;
                    out vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	vec4 _Levels;
                    uniform 	vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform 	float _MainTexDepth;
                    UNITY_LOCATION(0) uniform  sampler2DMSArray _MainTex;
                    in  vec3 vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    vec3 u_xlat2;
                    float u_xlat4;
                    bool u_xlatb4;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * vec3(_MainTexWidth, _MainTexHeight, _MainTexDepth);
                        u_xlatu0.xyz =  uvec3(ivec3(u_xlat0.xyz));
                        u_xlatu0.w = 0u;
                        u_xlat1 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 0);
                        u_xlat0 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 1);
                        u_xlat0 = u_xlat0 + u_xlat1;
                        u_xlat0 = u_xlat0 * vec4(0.5, 0.5, 0.5, 0.5) + (-_Levels.xxxx);
                        u_xlat1.x = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "_MSAA_2" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "_MSAA_4" "_TEX2DARRAY" }
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
                    in highp vec3 in_TEXCOORD0;
                    out highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #extension GL_OES_texture_storage_multisample_2d_array : require
                    
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform 	float _MainTexDepth;
                    UNITY_LOCATION(0) uniform highp sampler2DMSArray _MainTex;
                    in highp vec3 vs_TEXCOORD0;
                    layout(location = 0) out highp vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * vec3(_MainTexWidth, _MainTexHeight, _MainTexDepth);
                        u_xlatu0.xyz =  uvec3(ivec3(u_xlat0.xyz));
                        u_xlatu0.w = uint(0u);
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<4 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.25, 0.25, 0.25, 0.25) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "_MSAA_4" "_TEX2DARRAY" }
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
                    in  vec3 in_TEXCOORD0;
                    out vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	vec4 _Levels;
                    uniform 	vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform 	float _MainTexDepth;
                    UNITY_LOCATION(0) uniform  sampler2DMSArray _MainTex;
                    in  vec3 vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    vec4 u_xlat2;
                    float u_xlat4;
                    bool u_xlatb4;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * vec3(_MainTexWidth, _MainTexHeight, _MainTexDepth);
                        u_xlatu0.xyz =  uvec3(ivec3(u_xlat0.xyz));
                        u_xlatu0.w = 0u;
                        u_xlat1 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 0);
                        u_xlat2 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 1);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 2);
                        u_xlat0 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 3);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat0 = u_xlat0 + u_xlat1;
                        u_xlat0 = u_xlat0 * vec4(0.25, 0.25, 0.25, 0.25) + (-_Levels.xxxx);
                        u_xlat1.x = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "_MSAA_4" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "_MSAA_8" "_TEX2DARRAY" }
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
                    in highp vec3 in_TEXCOORD0;
                    out highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    #extension GL_OES_texture_storage_multisample_2d_array : require
                    
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform 	float _MainTexDepth;
                    UNITY_LOCATION(0) uniform highp sampler2DMSArray _MainTex;
                    in highp vec3 vs_TEXCOORD0;
                    layout(location = 0) out highp vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    bool u_xlatb1;
                    vec3 u_xlat2;
                    int u_xlati2;
                    vec4 u_xlat3;
                    mediump float u_xlat16_4;
                    float u_xlat6;
                    bool u_xlatb7;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * vec3(_MainTexWidth, _MainTexHeight, _MainTexDepth);
                        u_xlatu0.xyz =  uvec3(ivec3(u_xlat0.xyz));
                        u_xlatu0.w = uint(0u);
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        for(int u_xlati_loop_1 = 0 ; u_xlati_loop_1<8 ; u_xlati_loop_1++)
                        {
                            u_xlat3 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), u_xlati_loop_1);
                            u_xlat1 = u_xlat1 + u_xlat3;
                        }
                        u_xlat0 = u_xlat1 * vec4(0.125, 0.125, 0.125, 0.125) + (-_Levels.xxxx);
                        u_xlat16_4 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_4);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat6 = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? vec4(u_xlat6) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "_MSAA_8" "_TEX2DARRAY" }
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
                    in  vec3 in_TEXCOORD0;
                    out vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	vec4 _Levels;
                    uniform 	vec4 _Channels;
                    uniform 	float _MainTexWidth;
                    uniform 	float _MainTexHeight;
                    uniform 	float _MainTexDepth;
                    UNITY_LOCATION(0) uniform  sampler2DMSArray _MainTex;
                    in  vec3 vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec4 u_xlat0;
                    uvec4 u_xlatu0;
                    vec4 u_xlat1;
                    vec4 u_xlat2;
                    float u_xlat4;
                    bool u_xlatb4;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * vec3(_MainTexWidth, _MainTexHeight, _MainTexDepth);
                        u_xlatu0.xyz =  uvec3(ivec3(u_xlat0.xyz));
                        u_xlatu0.w = 0u;
                        u_xlat1 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 0);
                        u_xlat2 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 1);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 2);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 3);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 4);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 5);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat2 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 6);
                        u_xlat0 = texelFetch(_MainTex, ivec3(u_xlatu0.xyz), 7);
                        u_xlat1 = u_xlat1 + u_xlat2;
                        u_xlat0 = u_xlat0 + u_xlat1;
                        u_xlat0 = u_xlat0 * vec4(0.125, 0.125, 0.125, 0.125) + (-_Levels.xxxx);
                        u_xlat1.x = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "_MSAA_8" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "gles3 " {
                    Keywords { "_CUBEMAP" }
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
                    in highp vec3 in_TEXCOORD0;
                    out highp vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
                        return;
                    }
                    
                    #endif
                    #ifdef FRAGMENT
                    #version 300 es
                    
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	mediump vec4 _Levels;
                    uniform 	mediump vec4 _Channels;
                    UNITY_LOCATION(0) uniform highp samplerCube _MainTex;
                    in highp vec3 vs_TEXCOORD0;
                    layout(location = 0) out highp vec4 SV_Target0;
                    vec4 u_xlat0;
                    mediump float u_xlat16_1;
                    vec3 u_xlat2;
                    vec3 u_xlat3;
                    float u_xlat6;
                    bool u_xlatb6;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0 = texture(_MainTex, u_xlat0.xyz);
                        u_xlat0 = u_xlat0 + (-_Levels.xxxx);
                        u_xlat16_1 = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / vec4(u_xlat16_1);
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat2.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat6 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb6 = u_xlat6==1.0;
                        u_xlat0 = (bool(u_xlatb6)) ? u_xlat2.xxxx : u_xlat0;
                        u_xlat2.xyz = u_xlat0.xyz;
                        u_xlat2.xyz = clamp(u_xlat2.xyz, 0.0, 1.0);
                        u_xlat3.xyz = u_xlat2.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat3.xyz = u_xlat2.xyz * u_xlat3.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat2.xyz = u_xlat2.xyz * u_xlat3.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat2.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "glcore " {
                    Keywords { "_CUBEMAP" }
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
                    in  vec3 in_TEXCOORD0;
                    out vec3 vs_TEXCOORD0;
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
                        vs_TEXCOORD0.xyz = in_TEXCOORD0.xyz;
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
                    uniform 	int _UndoOutputSRGB;
                    uniform 	int _ShouldYFlip;
                    uniform 	vec4 _Levels;
                    uniform 	vec4 _Channels;
                    UNITY_LOCATION(0) uniform  samplerCube _MainTex;
                    in  vec3 vs_TEXCOORD0;
                    layout(location = 0) out vec4 SV_Target0;
                    vec4 u_xlat0;
                    vec3 u_xlat1;
                    vec3 u_xlat2;
                    float u_xlat4;
                    bool u_xlatb4;
                    void main()
                    {
                        u_xlat0.x = (-vs_TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (_ShouldYFlip != 0) ? u_xlat0.x : vs_TEXCOORD0.y;
                        u_xlat0.xz = vs_TEXCOORD0.xz;
                        u_xlat0 = texture(_MainTex, u_xlat0.xyz);
                        u_xlat0 = u_xlat0 + (-_Levels.xxxx);
                        u_xlat1.x = (-_Levels.x) + _Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * _Channels;
                        u_xlat1.x = dot(u_xlat0, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(_Channels, vec4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0, 1.0);
                        u_xlat2.xyz = u_xlat1.xyz * vec3(0.305306017, 0.305306017, 0.305306017) + vec3(0.682171106, 0.682171106, 0.682171106);
                        u_xlat2.xyz = u_xlat1.xyz * u_xlat2.xyz + vec3(0.0125228781, 0.0125228781, 0.0125228781);
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        SV_Target0.xyz = (_UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        SV_Target0.w = u_xlat0.w;
                        return;
                    }
                    
                    #endif
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "_TEX2DARRAY" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "_MSAA_2" "_TEX2DARRAY" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "_MSAA_4" "_TEX2DARRAY" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "_MSAA_8" "_TEX2DARRAY" }
                    "// disassembly error Unable to decode SMOL-V shader
                    "
                }
                SubProgram "vulkan " {
                    Keywords { "_CUBEMAP" }
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
                    struct FGlobals_Type
                    {
                        int _UndoOutputSRGB;
                        int _ShouldYFlip;
                        float4 _Levels;
                        float4 _Channels;
                        float _MainTexWidth;
                        float _MainTexHeight;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        texture2d<float, access::sample > _MainTex [[ texture(0) ]] ,
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float4 u_xlat0;
                        uint4 u_xlatu0;
                        float3 u_xlat1;
                        float3 u_xlat2;
                        float u_xlat4;
                        bool u_xlatb4;
                        u_xlat0.x = (-input.TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (FGlobals._ShouldYFlip != 0) ? u_xlat0.x : input.TEXCOORD0.y;
                        u_xlat0.x = input.TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * float2(FGlobals._MainTexWidth, FGlobals._MainTexHeight);
                        u_xlatu0.xy = uint2(int2(u_xlat0.xy));
                        u_xlatu0.z = uint(0x0u);
                        u_xlatu0.w = uint(0x0u);
                        u_xlat0 = _MainTex.read(u_xlatu0.xy, u_xlatu0.w);
                        u_xlat0 = u_xlat0 + (-FGlobals._Levels.xxxx);
                        u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * FGlobals._Channels;
                        u_xlat1.x = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
                        u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
                        u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        output.SV_Target0.w = u_xlat0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "_MSAA_2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "_MSAA_2" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        int _UndoOutputSRGB;
                        int _ShouldYFlip;
                        float4 _Levels;
                        float4 _Channels;
                        float _MainTexWidth;
                        float _MainTexHeight;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        texture2d_ms<float, access::read > _MainTex [[ texture(0) ]] ,
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float4 u_xlat0;
                        uint4 u_xlatu0;
                        float4 u_xlat1;
                        bool u_xlatb1;
                        float3 u_xlat2;
                        int u_xlati2;
                        float4 u_xlat3;
                        float u_xlat5;
                        bool u_xlatb6;
                        u_xlat0.x = (-input.TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (FGlobals._ShouldYFlip != 0) ? u_xlat0.x : input.TEXCOORD0.y;
                        u_xlat0.x = input.TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * float2(FGlobals._MainTexWidth, FGlobals._MainTexHeight);
                        u_xlatu0.xy = uint2(int2(u_xlat0.xy));
                        u_xlatu0.z = uint(0x0u);
                        u_xlatu0.w = uint(0x0u);
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        u_xlati2 = 0x0;
                        while(true){
                            u_xlatb6 = u_xlati2>=0x2;
                            if(u_xlatb6){break;}
                            u_xlat3 = _MainTex.read(u_xlatu0.xy, uint(u_xlati2));
                            u_xlat1 = u_xlat1 + u_xlat3;
                            u_xlati2 = u_xlati2 + 0x1;
                        }
                        u_xlat0 = fma(u_xlat1, float4(0.5, 0.5, 0.5, 0.5), (-FGlobals._Levels.xxxx));
                        u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * FGlobals._Channels;
                        u_xlat1.x = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat5 = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? float4(u_xlat5) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
                        u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
                        u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        output.SV_Target0.w = u_xlat0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "_MSAA_4" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "_MSAA_4" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        int _UndoOutputSRGB;
                        int _ShouldYFlip;
                        float4 _Levels;
                        float4 _Channels;
                        float _MainTexWidth;
                        float _MainTexHeight;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        texture2d_ms<float, access::read > _MainTex [[ texture(0) ]] ,
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float4 u_xlat0;
                        uint4 u_xlatu0;
                        float4 u_xlat1;
                        bool u_xlatb1;
                        float3 u_xlat2;
                        int u_xlati2;
                        float4 u_xlat3;
                        float u_xlat5;
                        bool u_xlatb6;
                        u_xlat0.x = (-input.TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (FGlobals._ShouldYFlip != 0) ? u_xlat0.x : input.TEXCOORD0.y;
                        u_xlat0.x = input.TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * float2(FGlobals._MainTexWidth, FGlobals._MainTexHeight);
                        u_xlatu0.xy = uint2(int2(u_xlat0.xy));
                        u_xlatu0.z = uint(0x0u);
                        u_xlatu0.w = uint(0x0u);
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        u_xlati2 = 0x0;
                        while(true){
                            u_xlatb6 = u_xlati2>=0x4;
                            if(u_xlatb6){break;}
                            u_xlat3 = _MainTex.read(u_xlatu0.xy, uint(u_xlati2));
                            u_xlat1 = u_xlat1 + u_xlat3;
                            u_xlati2 = u_xlati2 + 0x1;
                        }
                        u_xlat0 = fma(u_xlat1, float4(0.25, 0.25, 0.25, 0.25), (-FGlobals._Levels.xxxx));
                        u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * FGlobals._Channels;
                        u_xlat1.x = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat5 = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? float4(u_xlat5) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
                        u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
                        u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        output.SV_Target0.w = u_xlat0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "_MSAA_8" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "_MSAA_8" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        int _UndoOutputSRGB;
                        int _ShouldYFlip;
                        float4 _Levels;
                        float4 _Channels;
                        float _MainTexWidth;
                        float _MainTexHeight;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        texture2d_ms<float, access::read > _MainTex [[ texture(0) ]] ,
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float4 u_xlat0;
                        uint4 u_xlatu0;
                        float4 u_xlat1;
                        bool u_xlatb1;
                        float3 u_xlat2;
                        int u_xlati2;
                        float4 u_xlat3;
                        float u_xlat5;
                        bool u_xlatb6;
                        u_xlat0.x = (-input.TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (FGlobals._ShouldYFlip != 0) ? u_xlat0.x : input.TEXCOORD0.y;
                        u_xlat0.x = input.TEXCOORD0.x;
                        u_xlat0.xy = u_xlat0.xy * float2(FGlobals._MainTexWidth, FGlobals._MainTexHeight);
                        u_xlatu0.xy = uint2(int2(u_xlat0.xy));
                        u_xlatu0.z = uint(0x0u);
                        u_xlatu0.w = uint(0x0u);
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        u_xlati2 = 0x0;
                        while(true){
                            u_xlatb6 = u_xlati2>=0x8;
                            if(u_xlatb6){break;}
                            u_xlat3 = _MainTex.read(u_xlatu0.xy, uint(u_xlati2));
                            u_xlat1 = u_xlat1 + u_xlat3;
                            u_xlati2 = u_xlati2 + 0x1;
                        }
                        u_xlat0 = fma(u_xlat1, float4(0.125, 0.125, 0.125, 0.125), (-FGlobals._Levels.xxxx));
                        u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * FGlobals._Channels;
                        u_xlat1.x = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat5 = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? float4(u_xlat5) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
                        u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
                        u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        output.SV_Target0.w = u_xlat0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "_TEX2DARRAY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "_TEX2DARRAY" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        int _UndoOutputSRGB;
                        int _ShouldYFlip;
                        float4 _Levels;
                        float4 _Channels;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        sampler sampler_MainTex [[ sampler (0) ]],
                        texture2d_array<float, access::sample > _MainTex [[ texture(0) ]] ,
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float4 u_xlat0;
                        float3 u_xlat1;
                        float3 u_xlat2;
                        float u_xlat4;
                        bool u_xlatb4;
                        u_xlat0.x = (-input.TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (FGlobals._ShouldYFlip != 0) ? u_xlat0.x : input.TEXCOORD0.y;
                        u_xlat0.xz = input.TEXCOORD0.xz;
                        u_xlat0 = _MainTex.sample(sampler_MainTex, u_xlat0.xy, round(u_xlat0.z));
                        u_xlat0 = u_xlat0 + (-FGlobals._Levels.xxxx);
                        u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * FGlobals._Channels;
                        u_xlat1.x = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
                        u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
                        u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        output.SV_Target0.w = u_xlat0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "_MSAA_2" "_TEX2DARRAY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "_MSAA_2" "_TEX2DARRAY" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        int _UndoOutputSRGB;
                        int _ShouldYFlip;
                        float4 _Levels;
                        float4 _Channels;
                        float _MainTexWidth;
                        float _MainTexHeight;
                        float _MainTexDepth;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        texture2d_ms_array<float, access::read > _MainTex [[ texture(0) ]] ,
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float4 u_xlat0;
                        uint4 u_xlatu0;
                        float4 u_xlat1;
                        bool u_xlatb1;
                        float3 u_xlat2;
                        int u_xlati2;
                        float4 u_xlat3;
                        float u_xlat5;
                        bool u_xlatb6;
                        u_xlat0.x = (-input.TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (FGlobals._ShouldYFlip != 0) ? u_xlat0.x : input.TEXCOORD0.y;
                        u_xlat0.xz = input.TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * float3(FGlobals._MainTexWidth, FGlobals._MainTexHeight, FGlobals._MainTexDepth);
                        u_xlatu0.xyz = uint3(int3(u_xlat0.xyz));
                        u_xlatu0.w = 0x0u;
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        u_xlati2 = 0x0;
                        while(true){
                            u_xlatb6 = u_xlati2>=0x2;
                            if(u_xlatb6){break;}
                            u_xlat3 = _MainTex.read(u_xlatu0.xy, u_xlatu0.z, uint(u_xlati2));
                            u_xlat1 = u_xlat1 + u_xlat3;
                            u_xlati2 = u_xlati2 + 0x1;
                        }
                        u_xlat0 = fma(u_xlat1, float4(0.5, 0.5, 0.5, 0.5), (-FGlobals._Levels.xxxx));
                        u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * FGlobals._Channels;
                        u_xlat1.x = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat5 = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? float4(u_xlat5) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
                        u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
                        u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        output.SV_Target0.w = u_xlat0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "_MSAA_4" "_TEX2DARRAY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "_MSAA_4" "_TEX2DARRAY" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        int _UndoOutputSRGB;
                        int _ShouldYFlip;
                        float4 _Levels;
                        float4 _Channels;
                        float _MainTexWidth;
                        float _MainTexHeight;
                        float _MainTexDepth;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        texture2d_ms_array<float, access::read > _MainTex [[ texture(0) ]] ,
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float4 u_xlat0;
                        uint4 u_xlatu0;
                        float4 u_xlat1;
                        bool u_xlatb1;
                        float3 u_xlat2;
                        int u_xlati2;
                        float4 u_xlat3;
                        float u_xlat5;
                        bool u_xlatb6;
                        u_xlat0.x = (-input.TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (FGlobals._ShouldYFlip != 0) ? u_xlat0.x : input.TEXCOORD0.y;
                        u_xlat0.xz = input.TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * float3(FGlobals._MainTexWidth, FGlobals._MainTexHeight, FGlobals._MainTexDepth);
                        u_xlatu0.xyz = uint3(int3(u_xlat0.xyz));
                        u_xlatu0.w = 0x0u;
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        u_xlati2 = 0x0;
                        while(true){
                            u_xlatb6 = u_xlati2>=0x4;
                            if(u_xlatb6){break;}
                            u_xlat3 = _MainTex.read(u_xlatu0.xy, u_xlatu0.z, uint(u_xlati2));
                            u_xlat1 = u_xlat1 + u_xlat3;
                            u_xlati2 = u_xlati2 + 0x1;
                        }
                        u_xlat0 = fma(u_xlat1, float4(0.25, 0.25, 0.25, 0.25), (-FGlobals._Levels.xxxx));
                        u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * FGlobals._Channels;
                        u_xlat1.x = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat5 = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? float4(u_xlat5) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
                        u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
                        u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        output.SV_Target0.w = u_xlat0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "_MSAA_8" "_TEX2DARRAY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "_MSAA_8" "_TEX2DARRAY" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        int _UndoOutputSRGB;
                        int _ShouldYFlip;
                        float4 _Levels;
                        float4 _Channels;
                        float _MainTexWidth;
                        float _MainTexHeight;
                        float _MainTexDepth;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        texture2d_ms_array<float, access::read > _MainTex [[ texture(0) ]] ,
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float4 u_xlat0;
                        uint4 u_xlatu0;
                        float4 u_xlat1;
                        bool u_xlatb1;
                        float3 u_xlat2;
                        int u_xlati2;
                        float4 u_xlat3;
                        float u_xlat5;
                        bool u_xlatb6;
                        u_xlat0.x = (-input.TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (FGlobals._ShouldYFlip != 0) ? u_xlat0.x : input.TEXCOORD0.y;
                        u_xlat0.xz = input.TEXCOORD0.xz;
                        u_xlat0.xyz = u_xlat0.xyz * float3(FGlobals._MainTexWidth, FGlobals._MainTexHeight, FGlobals._MainTexDepth);
                        u_xlatu0.xyz = uint3(int3(u_xlat0.xyz));
                        u_xlatu0.w = 0x0u;
                        u_xlat1.x = float(0.0);
                        u_xlat1.y = float(0.0);
                        u_xlat1.z = float(0.0);
                        u_xlat1.w = float(0.0);
                        u_xlati2 = 0x0;
                        while(true){
                            u_xlatb6 = u_xlati2>=0x8;
                            if(u_xlatb6){break;}
                            u_xlat3 = _MainTex.read(u_xlatu0.xy, u_xlatu0.z, uint(u_xlati2));
                            u_xlat1 = u_xlat1 + u_xlat3;
                            u_xlati2 = u_xlati2 + 0x1;
                        }
                        u_xlat0 = fma(u_xlat1, float4(0.125, 0.125, 0.125, 0.125), (-FGlobals._Levels.xxxx));
                        u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * FGlobals._Channels;
                        u_xlat1.x = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb1 = u_xlat1.x==1.0;
                        u_xlat5 = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlat0 = (bool(u_xlatb1)) ? float4(u_xlat5) : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
                        u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
                        u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        output.SV_Target0.w = u_xlat0.w;
                        return output;
                    }
                    "
                }
                SubProgram "d3d11 " {
                    Keywords { "_CUBEMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "metal " {
                    Keywords { "_CUBEMAP" }
                    "#include <metal_stdlib>
                    #include <metal_texture>
                    using namespace metal;
                    constant uint32_t rp_output_remap_mask [[ function_constant(1) ]];
                    constant const uint rp_output_remap_0 = (rp_output_remap_mask >> 0) & 0xF;
                    struct FGlobals_Type
                    {
                        int _UndoOutputSRGB;
                        int _ShouldYFlip;
                        float4 _Levels;
                        float4 _Channels;
                    };
                    
                    struct Mtl_FragmentIn
                    {
                        float3 TEXCOORD0 [[ user(TEXCOORD0) ]] ;
                    };
                    
                    struct Mtl_FragmentOut
                    {
                        float4 SV_Target0 [[ color(rp_output_remap_0) ]];
                    };
                    
                    fragment Mtl_FragmentOut xlatMtlMain(
                        constant FGlobals_Type& FGlobals [[ buffer(0) ]],
                        sampler sampler_MainTex [[ sampler (0) ]],
                        texturecube<float, access::sample > _MainTex [[ texture(0) ]] ,
                        Mtl_FragmentIn input [[ stage_in ]])
                    {
                        Mtl_FragmentOut output;
                        float4 u_xlat0;
                        float3 u_xlat1;
                        float3 u_xlat2;
                        float u_xlat4;
                        bool u_xlatb4;
                        u_xlat0.x = (-input.TEXCOORD0.y) + 1.0;
                        u_xlat0.y = (FGlobals._ShouldYFlip != 0) ? u_xlat0.x : input.TEXCOORD0.y;
                        u_xlat0.xz = input.TEXCOORD0.xz;
                        u_xlat0 = _MainTex.sample(sampler_MainTex, u_xlat0.xyz);
                        u_xlat0 = u_xlat0 + (-FGlobals._Levels.xxxx);
                        u_xlat1.x = (-FGlobals._Levels.x) + FGlobals._Levels.y;
                        u_xlat0 = u_xlat0 / u_xlat1.xxxx;
                        u_xlat0 = u_xlat0 * FGlobals._Channels;
                        u_xlat1.x = dot(u_xlat0, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlat4 = dot(FGlobals._Channels, float4(1.0, 1.0, 1.0, 1.0));
                        u_xlatb4 = u_xlat4==1.0;
                        u_xlat0 = (bool(u_xlatb4)) ? u_xlat1.xxxx : u_xlat0;
                        u_xlat1.xyz = u_xlat0.xyz;
                        u_xlat1.xyz = clamp(u_xlat1.xyz, 0.0f, 1.0f);
                        u_xlat2.xyz = fma(u_xlat1.xyz, float3(0.305306017, 0.305306017, 0.305306017), float3(0.682171106, 0.682171106, 0.682171106));
                        u_xlat2.xyz = fma(u_xlat1.xyz, u_xlat2.xyz, float3(0.0125228781, 0.0125228781, 0.0125228781));
                        u_xlat1.xyz = u_xlat1.xyz * u_xlat2.xyz;
                        output.SV_Target0.xyz = (FGlobals._UndoOutputSRGB != 0) ? u_xlat1.xyz : u_xlat0.xyz;
                        output.SV_Target0.w = u_xlat0.w;
                        return output;
                    }
                    "
                }
            }
        }
    }
}