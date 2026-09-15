//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/ThermalPass" {
    Properties {
        _Color ("Color", Color) = (0,0,0,0)
        _Power_Smooth ("Power_Smooth", Float) = 0
        _Power_Rough ("Power_Rough", Float) = 0
        _MinDistance ("MinDistance", Float) = 0
        _MaxDistance ("MaxDistance", Float) = 0
        _Alpha ("Alpha", Range(0, 1)) = 0
        unity_Lightmaps ("unity_Lightmaps", 2DArray) = "" { }
        unity_LightmapsInd ("unity_LightmapsInd", 2DArray) = "" { }
        unity_ShadowMasks ("unity_ShadowMasks", 2DArray) = "" { }
    }
    SubShader {
        Tags { "RenderPipeline" = "UniversalPipeline" "ShaderGraphShader" = "true" "ShaderGraphTargetId" = "UniversalFullscreenSubTarget" }
        Pass {
            Name "DrawProcedural"
            Tags { "RenderPipeline" = "UniversalPipeline" "ShaderGraphShader" = "true" "ShaderGraphTargetId" = "UniversalFullscreenSubTarget" }
            Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
            ZTest Off
            ZWrite Off
            Cull Off
            GpuProgramID 63314
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
            Name "Blit"
            Tags { "RenderPipeline" = "UniversalPipeline" "ShaderGraphShader" = "true" "ShaderGraphTargetId" = "UniversalFullscreenSubTarget" }
            Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
            ZTest Off
            ZWrite Off
            Cull Off
            GpuProgramID 83066
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
Fallback "Hidden/Shader Graph/FallbackError"
CustomEditor "UnityEditor.Rendering.Fullscreen.ShaderGraph.FullscreenShaderGUI"
}