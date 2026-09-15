//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/FullScreen/FOW/FOW_RT" {
    Properties {
        _MainTex ("Texture", 2D) = "white" { }
    }
    SubShader {
        Pass {
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 58793
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "HARD" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "HARD" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IGNORE_HEIGHT" "INNER_SOFTEN" "SAMPLE_REALTIME" "SOFT" "USE_FADEIN" "USE_REGROW" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 102631
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