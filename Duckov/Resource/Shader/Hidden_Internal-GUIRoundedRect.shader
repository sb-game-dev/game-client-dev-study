//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Internal-GUIRoundedRect" {
    Properties {
        _MainTex ("Texture", any) = "white" { }
        _SrcBlend ("SrcBlend", Float) = 5
        _DstBlend ("DstBlend", Float) = 10
    }
    SubShader {
        Pass {
            Blend Zero Zero, One OneMinusSrcAlpha
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 45324
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
        Pass {
            Blend Zero Zero, Zero Zero
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 116409
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
Fallback "Hidden/Internal-GUITextureClip"
}