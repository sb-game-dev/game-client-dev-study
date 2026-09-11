//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/FullScreen/FOW/Blur" {
    Properties {
        _MainTex ("Texture", 2D) = "white" { }
    }
    SubShader {
        Pass {
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 18726
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}