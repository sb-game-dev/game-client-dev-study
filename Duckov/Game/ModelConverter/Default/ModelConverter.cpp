#include "Converter.h"
using namespace Engine;

int main(int argc, char* argv[])
{
	// 인자가 없으면 실행 안함
	if (argc < 2)
	{
		return -1;
	}

	auto pConverter = CConverter::Create();
	if (nullptr == pConverter)
		return -1;

	uint32_t	iNumFailed = 0;
	for (int i = 1; i < argc; ++i)
	{
		if (false == pConverter->Convert(argv[i], MODEL_TYPE::NONANIM))
			++iNumFailed;
	}

	uint32_t	iNumTotal = static_cast<uint32_t>(argc - 1);
	cout << "\n[Result] 성공 " << (iNumTotal - iNumFailed) << " / 실패 " << iNumFailed << '\n';

	return 0 == iNumFailed ? 0 : -1;

	//if (false == pConverter->Convert("../../../Resource/Mesh/Tree/Pfb_Tree_01_1.fbx", MODEL_TYPE::NONANIM))
	//	return -1;
}
