#include"pch.h"

int main()
{
	FILE* pReadPicture = nullptr;
	FILE* pWritePicture = nullptr;
	errno_t errRead = fopen_s(&pReadPicture,"./picture.png","rb");
	errno_t errWrite = fopen_s(&pWritePicture, "./picture_copy.png", "wb");
	if (errRead == 0)
	{
		cout << "사진 파일 열기에 성공했습니다." << endl;
		fseek(pReadPicture, 0, SEEK_SET);
		
		if (errWrite == 0)
		{
			while (feof(pReadPicture) == 0)
			{
				fputc(fgetc(pReadPicture), pWritePicture);
			}
			cout << "복사할 사진파일 생성완료." << endl;
			fclose(pWritePicture);
		}
		fclose(pReadPicture);
	}
}