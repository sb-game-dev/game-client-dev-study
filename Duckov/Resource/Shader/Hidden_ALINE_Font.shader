//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/ALINE/Font" {
    Properties {
        _Color ("Main Color", Color) = (1,1,1,0.5)
        _FadeColor ("Fade Color", Color) = (1,1,1,0.3)
        _MainTex ("Texture", 2D) = "white" { }
        _FallbackTex ("Fallback Texture", 2D) = "white" { }
        _FallbackAmount ("Fallback Amount", Range(0, 1)) = 1
        _TransitionPoint ("Transition Point", Range(0, 5)) = 0.6
        _MipBias ("Mip Bias", Range(-2, 0)) = -1
        _GammaCorrection ("Gamma Correction", Range(0, 2)) = 1
    }
    SubShader {
        Tags { "IGNOREPROJECTOR" = "true" "RenderType" = "Overlay" }
        Pass {
            Tags { "IGNOREPROJECTOR" = "true" "RenderType" = "Overlay" }
            Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
            ZTest Greater
            ZWrite Off
            Cull Off
            Offset -3, -50
            GpuProgramID 165807
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Tags { "IGNOREPROJECTOR" = "true" "RenderType" = "Overlay" }
            Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
            ZWrite Off
            Cull Off
            Offset -3, -50
            GpuProgramID 215720
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}