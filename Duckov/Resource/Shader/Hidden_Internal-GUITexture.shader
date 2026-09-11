//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Internal-GUITexture" {
    Properties {
        _MainTex ("Texture", any) = "" { }
    }
    SubShader {
        Tags { "RenderType" = "Overlay" }
        Pass {
            Tags { "RenderType" = "Overlay" }
            Blend SrcAlpha OneMinusSrcAlpha, One One
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 25450
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
    SubShader {
        Tags { "RenderType" = "Overlay" }
        Pass {
            Tags { "RenderType" = "Overlay" }
            Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 67210
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