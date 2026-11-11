#include "Converter.h"
using namespace Engine;
int main()
{
	auto pConverter = CConverter::Create();
	if (nullptr == pConverter)
		return -1;
	if (false == pConverter->Convert("../../../Resource/Mesh/Tree/Pfb_Tree_01_1.fbx", MODEL_TYPE::NONANIM))
		return -1;
	return 0;
}
