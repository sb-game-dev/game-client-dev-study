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

	for (int i = 1; i < argc; ++i)
		pConverter->Convert(argv[i], MODEL_TYPE::ANIM);

}
