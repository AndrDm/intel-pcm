// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LABVIEWPCM_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LABVIEWPCM_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LABVIEWPCM_EXPORTS
#define LABVIEWPCM_API __declspec(dllexport)
#else
#define LABVIEWPCM_API __declspec(dllimport)
#endif

// This class is exported from the dll
class LABVIEWPCM_API CLabVIEWpcm {
public:
	CLabVIEWpcm(void);
	// TODO: add your methods here.
};

extern LABVIEWPCM_API int nLabVIEWpcm;

LABVIEWPCM_API int fnLabVIEWpcm(void);
