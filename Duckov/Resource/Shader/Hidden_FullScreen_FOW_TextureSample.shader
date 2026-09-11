//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/FullScreen/FOW/TextureSample" {
    Properties {
        _MainTex ("Texture", 2D) = "white" { }
        _fowTexture ("Texture", 2D) = "white" { }
    }
    SubShader {
        Pass {
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 39528
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XZ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XZ" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XZ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XZ" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XZ" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XZ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XZ" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XZ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XZ" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XZ" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_ZY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_ZY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_ZY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_ZY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_ZY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_ZY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_ZY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_ZY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_ZY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_ZY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XZ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XZ" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XZ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XZ" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XZ" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XZ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XZ" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XZ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XZ" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XZ" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XZ" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_XY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_ZY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_ZY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_ZY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_ZY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_ZY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_2D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_ZY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_ZY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_ZY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HARD" "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_ZY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_ZY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INNER_SOFTEN" "IS_3D" "PLANE_ZY" "SAMPLE_REALTIME" "SOFT" "USE_TEXTURE_BLUR" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}