//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/ALINE/Outline" {
    Properties {
        _Color ("Main Color", Color) = (1,1,1,0.5)
        _FadeColor ("Fade Color", Color) = (1,1,1,0.3)
        _PixelWidth ("Width (px)", Float) = 4
        _LengthPadding ("Length Padding (px)", Float) = 0
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
            GpuProgramID 242246
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
            ColorMask 0 0
            Cull Off
            Offset -3, -50
            GpuProgramID 275502
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
            GpuProgramID 353917
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