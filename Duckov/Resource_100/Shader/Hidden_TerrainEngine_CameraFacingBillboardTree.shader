//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/TerrainEngine/CameraFacingBillboardTree" {
    Properties {
        _MainTex ("Base (RGB) Alpha (A)", 2D) = "white" { }
        _NormalTex ("Base (RGB) Alpha (A)", 2D) = "white" { }
        _TranslucencyViewDependency ("View dependency", Range(0, 1)) = 0.7
        _TranslucencyColor ("Translucency Color", Color) = (0.73,0.85,0.41,1)
        _AlphaToMask ("AlphaToMask", Float) = 1
    }
    SubShader {
        Tags { "IGNOREPROJECTOR" = "true" "RenderType" = "TreeBillboard" }
        Pass {
            Tags { "IGNOREPROJECTOR" = "true" "RenderType" = "TreeBillboard" }
            ColorMask RGB 0
            Cull Off
            GpuProgramID 170
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}