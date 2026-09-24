#ifndef Engine_Macro_h__
#define Engine_Macro_h__


#ifndef			MSG_BOX
#define			MSG_BOX(_message)			MessageBox(nullptr, TEXT(_message), L"System Message", MB_OK)
#endif

#define			NS_BEGIN(NAMESPACE)		namespace NAMESPACE {
#define			NS_END					}
	
#define			NS_USING(NAMESPACE)		using namespace NAMESPACE;
	
#ifdef	ENGINE_EXPORTS
#define ENGINE_DLL		_declspec(dllexport)
#else
#define ENGINE_DLL		_declspec(dllimport)
#endif
	
/* 싱글턴 : 클래스를 할당(객체화)하는 횟수를 n개로 제한한다. -> 1개로 제한한다. */

#define NO_COPY(CLASSNAME)										\
		private:												\
		CLASSNAME(const CLASSNAME&) = delete;					\
		CLASSNAME& operator = (const CLASSNAME&) = delete;
	
#define DECLARE_SINGLETON(CLASSNAME)								\
		NO_COPY(CLASSNAME)											\
		public:														\
			static CLASSNAME& Get(void)								\
			{														\
				static CLASSNAME Instance = {};						\
				return Instance;									\
			}														
	



#endif // Engine_Macro_h__
