//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/ScreenSpaceShadows" {
    Properties {
    }
    SubShader {
        Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
        Pass {
            Name "ScreenSpaceShadows"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 64912
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}