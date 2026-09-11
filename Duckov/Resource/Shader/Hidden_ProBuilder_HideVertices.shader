//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/ProBuilder/HideVertices" {
    Properties {
    }
    SubShader {
        Tags { "IGNOREPROJECTOR" = "true" "RenderType" = "Geometry" }
        Pass {
            Tags { "IGNOREPROJECTOR" = "true" "RenderType" = "Geometry" }
            GpuProgramID 39047
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