# FDLuna

This repository contains all the example code from the book 'Introduction to 3D Game Programming with DirectX 11' by Frank D. Luna (ISBN: 978-1-9364202-2-3), updated for Windows 10 and Visual Studio 2022.

As written, the original code no longer works due to changes in DirectX SDK from Windows 8 onwards. Specifically, 'XNA Maths' was deprecated, as was the effects (FX) framework. The former has been completely replaced by DirectXMaths, while the latter is largely replaced by DirectX Toolkit. 

All the XNA Maths data types now exist in the DirectX, DirectX::PackedVector and DirectX::TriangleTest namespaces. As is the convention, all DirectX names are explicitly qualified in example code headers while 'using namespace' directives are used in all source files.

xnacollision.h and xnacollision.cpp are no longer required and have been removed. They have been replaced by DirectXMath and are made available by including directxcollision.h instead.

Effects11.lib and Effects11d.lib have been replaced with the latest versions from Chuck Walbourn, along with d3dx11effect.h.

DXERR.lib is no longer included in the DirectX SDK, however this has been replaced with dxerr.h and dxerr.cpp.

DDSTextureLoader.h and DDSTextureLoader.cpp are provided to load all textures.

All BMP (bitmap) textures have been replaced with DDS (Direct Draw Surface) equivalents. It is no longer necessary to create texture arrays in code; DDS supports texture arrays and texture cubes.

As with the original code, every project has its own solution. For convenience, the FDLuna solution allows you to load all the projects at once; simply set the startup project to whichever project you are interested in. 

The only other major change I've made is to move all unique assets (textures and models) into a single 'Assets' folder, thus eliminating the need for duplicate assets in this repository.
