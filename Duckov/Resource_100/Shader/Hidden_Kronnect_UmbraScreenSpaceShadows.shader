//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Kronnect/UmbraScreenSpaceShadows" {
    Properties {
        _NoiseTex ("Noise Tex", 2D) = "white" { }
    }
    SubShader {
        Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
        Pass {
            Name "Umbra Shadows"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 47587
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
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Blur Horiz"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 97288
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLUR_HQ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLUR_HQ" "_CONTACT_HARDENING" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Blur Vert"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 139000
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLUR_HQ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLUR_HQ" "_CONTACT_HARDENING" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Box Blur"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 241697
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Compose with Blending"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 276180
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_PRESERVE_EDGES" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_NORMALS_TEXTURE" "_PRESERVE_EDGES" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Downsample Depth"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 377354
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
            Name "Umbra Cascade Blending"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 394662
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
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X2" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CONTACT_HARDENING" "_LOOP_STEP_X3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_MASK_TEXTURE" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "ScreenSpaceShadows"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 522680
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
        Pass {
            Name "Compose Unity Shadows"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 567013
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_PRESERVE_EDGES" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Contact Shadows"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            Blend One One, One One
            BlendOp Min, Min
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 651292
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Compose"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 677670
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_PRESERVE_EDGES" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Debug Shadows"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 733198
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_PRESERVE_EDGES" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Contact Shadows After Opaque"
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" }
            Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 820492
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X2" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LOOP_STEP_X3" "_NORMALS_TEXTURE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}