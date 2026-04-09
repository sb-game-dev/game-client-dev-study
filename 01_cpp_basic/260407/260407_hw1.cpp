#include"pch.h"

int main()
{
	FILE* pReadPicture = nullptr;
	FILE* pWritePicture = nullptr;
	errno_t errRead = fopen_s(&pReadPicture,"./picture.png","rb");
	errno_t errWrite = fopen_s(&pWritePicture, "./picture_copy.png", "wb");
	if (errRead == 0)
	{
		fseek(pReadPicture, 0, SEEK_END);
		int iSize = ftell(pReadPicture);
		cout << "사진 파일 열기에 성공했습니다." << endl;
		fseek(pReadPicture, 0, SEEK_SET);
		char* c = new char[iSize];
		if (errWrite == 0)
		{
			fread(c, sizeof(char), iSize, pReadPicture);
			fwrite(c, sizeof(char), iSize, pWritePicture);
			//while (feof(pReadPicture) == 0)
			//{
			//	fread(&c, sizeof(char), 1, pReadPicture);
			//	fwrite(&c, sizeof(char), 1, pWritePicture);
			//}
			cout << "복사할 사진파일 생성완료." << endl;
			fclose(pWritePicture);
		}
		fclose(pReadPicture);
	}
}