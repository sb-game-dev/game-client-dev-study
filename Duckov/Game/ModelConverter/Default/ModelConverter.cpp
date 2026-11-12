#include "Converter.h"
using namespace Engine;

static void Print_Usage()
{
	cout << "사용법 : ModelConverter.exe <FBX 경로> [<FBX 경로> ...]\n";
	cout << "  예)   ModelConverter.exe ../../../Resource/Mesh/Tree/Pfb_Tree_01_1.fbx\n";
	cout << "  FBX 파일들을 exe 위로 끌어다 놓아도 됩니다.\n";
}

int main(int argc, char* argv[])
{
	// 인자가 없으면 사용법 출력
	if (argc < 2)
	{
		Print_Usage();
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
	return 0;
}
