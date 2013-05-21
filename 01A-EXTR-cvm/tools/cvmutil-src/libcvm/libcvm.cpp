// cl -W3 -DUNICODE -D_UNICODE -D_WIN32_WINNT=0x500 libcvm.cpp cvm_test.cpp /link user32.lib

#include <tchar.h>

#include "libcvm.h"


#if !defined(NEVER_DEFINED)
	#define DEBUG_CODE /##/
#else
	#include <stdio.h>
	#define DEBUG_CODE
#endif

namespace {

static const WORD LOOKUP_TABLE[] = 
{
// 0x00-0xFF
/*00-0F*/	0x401B, 0x4021, 0x4025, 0x402B, 0x4031, 0x403F, 0x4043, 0x4045, 0x405D, 0x4061, 0x4067, 0x406D, 0x4087, 0x4091, 0x40A3, 0x40A9,
/*10-1F*/	0x40B1, 0x40B7, 0x40BD, 0x40DB, 0x40DF, 0x40EB, 0x40F7, 0x40F9, 0x4109, 0x410B, 0x4111, 0x4115, 0x4121, 0x4133, 0x4135, 0x413B,
/*20-2F*/	0x413F, 0x4159, 0x4165, 0x416B, 0x4177, 0x417B, 0x4193, 0x41AB, 0x41B7, 0x41BD, 0x41BF, 0x41CB, 0x41E7, 0x41EF, 0x41F3, 0x41F9,
/*30-3F*/	0x4205, 0x4207, 0x4219, 0x421F, 0x4223, 0x4229, 0x422F, 0x4243, 0x4253, 0x4255, 0x425B, 0x4261, 0x4273, 0x427D, 0x4283, 0x4285,
/*40-4F*/	0x4289, 0x4291, 0x4297, 0x429D, 0x42B5, 0x42C5, 0x42CB, 0x42D3, 0x42DD, 0x42E3, 0x42F1, 0x4307, 0x430F, 0x431F, 0x4325, 0x4327,
/*50-5F*/	0x4333, 0x4337, 0x4339, 0x434F, 0x4357, 0x4369, 0x438B, 0x438D, 0x4393, 0x43A5, 0x43A9, 0x43AF, 0x43B5, 0x43BD, 0x43C7, 0x43CF,
/*60-6F*/	0x43E1, 0x43E7, 0x43EB, 0x43ED, 0x43F1, 0x43F9, 0x4409, 0x440B, 0x4417, 0x4423, 0x4429, 0x443B, 0x443F, 0x4445, 0x444B, 0x4451,
/*70-7F*/	0x4453, 0x4459, 0x4465, 0x446F, 0x4483, 0x448F, 0x44A1, 0x44A5, 0x44AB, 0x44AD, 0x44BD, 0x44BF, 0x44C9, 0x44D7, 0x44DB, 0x44F9,
/*80-8F*/	0x44FB, 0x4505, 0x4511, 0x4513, 0x452B, 0x4531, 0x4541, 0x4549, 0x4553, 0x4555, 0x4561, 0x4577, 0x457D, 0x457F, 0x458F, 0x45A3,
/*90-9F*/	0x45AD, 0x45AF, 0x45BB, 0x45C7, 0x45D9, 0x45E3, 0x45EF, 0x45F5, 0x45F7, 0x4601, 0x4603, 0x4609, 0x4613, 0x4625, 0x4627, 0x4633,
/*A0-AF*/	0x4639, 0x463D, 0x4643, 0x4645, 0x465D, 0x4679, 0x467B, 0x467F, 0x4681, 0x468B, 0x468D, 0x469D, 0x46A9, 0x46B1, 0x46C7, 0x46C9,
/*B0-BF*/	0x46CF, 0x46D3, 0x46D5, 0x46DF, 0x46E5, 0x46F9, 0x4705, 0x470F, 0x4717, 0x4723, 0x4729, 0x472F, 0x4735, 0x4739, 0x474B, 0x474D,
/*C0-CF*/	0x4751, 0x475D, 0x476F, 0x4771, 0x477D, 0x4783, 0x4787, 0x4789, 0x4799, 0x47A5, 0x47B1, 0x47BF, 0x47C3, 0x47CB, 0x47DD, 0x47E1,
/*D0-DF*/	0x47ED, 0x47FB, 0x4801, 0x4807, 0x480B, 0x4813, 0x4819, 0x481D, 0x4831, 0x483D, 0x4847, 0x4855, 0x4859, 0x485B, 0x486B, 0x486D,
/*E0-EF*/	0x4879, 0x4897, 0x489B, 0x48A1, 0x48B9, 0x48CD, 0x48E5, 0x48EF, 0x48F7, 0x4903, 0x490D, 0x4919, 0x491F, 0x492B, 0x4937, 0x493D,
/*F0-FF*/	0x4945, 0x4955, 0x4963, 0x4969, 0x496D, 0x4973, 0x4997, 0x49AB, 0x49B5, 0x49D3, 0x49DF, 0x49E1, 0x49E5, 0x49E7, 0x4A03, 0x4A0F,
// 0x100-0x1FF
/*00-0F*/	0x4A1D, 0x4A23, 0x4A39, 0x4A41, 0x4A45, 0x4A57, 0x4A5D, 0x4A6B, 0x4A7D, 0x4A81, 0x4A87, 0x4A89, 0x4A8F, 0x4AB1, 0x4AC3, 0x4AC5,
/*10-1F*/	0x4AD5, 0x4ADB, 0x4AED, 0x4AEF, 0x4B07, 0x4B0B, 0x4B0D, 0x4B13, 0x4B1F, 0x4B25, 0x4B31, 0x4B3B, 0x4B43, 0x4B49, 0x4B59, 0x4B65,
/*20-2F*/	0x4B6D, 0x4B77, 0x4B85, 0x4BAD, 0x4BB3, 0x4BB5, 0x4BBB, 0x4BBF, 0x4BCB, 0x4BD9, 0x4BDD, 0x4BDF, 0x4BE3, 0x4BE5, 0x4BE9, 0x4BF1,
/*30-3F*/	0x4BF7, 0x4C01, 0x4C07, 0x4C0D, 0x4C0F, 0x4C15, 0x4C1B, 0x4C21, 0x4C2D, 0x4C33, 0x4C4B, 0x4C55, 0x4C57, 0x4C61, 0x4C67, 0x4C73,
/*40-4F*/	0x4C79, 0x4C7F, 0x4C8D, 0x4C93, 0x4C99, 0x4CCD, 0x4CE1, 0x4CE7, 0x4CF1, 0x4CF3, 0x4CFD, 0x4D05, 0x4D0F, 0x4D1B, 0x4D27, 0x4D29,
/*50-5F*/	0x4D2F, 0x4D33, 0x4D41, 0x4D51, 0x4D59, 0x4D65, 0x4D6B, 0x4D81, 0x4D83, 0x4D8D, 0x4D95, 0x4D9B, 0x4DB1, 0x4DB3, 0x4DC9, 0x4DCF,
/*60-6F*/	0x4DD7, 0x4DE1, 0x4DED, 0x4DF9, 0x4DFB, 0x4E05, 0x4E0B, 0x4E17, 0x4E19, 0x4E1D, 0x4E2B, 0x4E35, 0x4E37, 0x4E3D, 0x4E4F, 0x4E53,
/*70-7F*/	0x4E5F, 0x4E67, 0x4E79, 0x4E85, 0x4E8B, 0x4E91, 0x4E95, 0x4E9B, 0x4EA1, 0x4EAF, 0x4EB3, 0x4EB5, 0x4EC1, 0x4ECD, 0x4ED1, 0x4ED7,
/*80-8F*/	0x4EE9, 0x4EFB, 0x4F07, 0x4F09, 0x4F19, 0x4F25, 0x4F2D, 0x4F3F, 0x4F49, 0x4F63, 0x4F67, 0x4F6D, 0x4F75, 0x4F7B, 0x4F81, 0x4F85,
/*90-9F*/	0x4F87, 0x4F91, 0x4FA5, 0x4FA9, 0x4FAF, 0x4FB7, 0x4FBB, 0x4FCF, 0x4FD9, 0x4FDB, 0x4FFD, 0x4FFF, 0x5003, 0x501B, 0x501D, 0x5029,
/*A0-AF*/	0x5035, 0x503F, 0x5045, 0x5047, 0x5053, 0x5071, 0x5077, 0x5083, 0x5093, 0x509F, 0x50A1, 0x50B7, 0x50C9, 0x50D5, 0x50E3, 0x50ED,
/*B0-BF*/	0x50EF, 0x50FB, 0x5107, 0x510B, 0x510D, 0x5111, 0x5117, 0x5123, 0x5125, 0x5135, 0x5147, 0x5149, 0x5171, 0x5179, 0x5189, 0x518F,
/*C0-CF*/	0x5197, 0x51A1, 0x51A3, 0x51A7, 0x51B9, 0x51C1, 0x51CB, 0x51D3, 0x51DF, 0x51E3, 0x51F5, 0x51F7, 0x5209, 0x5213, 0x5215, 0x5219,
/*D0-DF*/	0x521B, 0x521F, 0x5227, 0x5243, 0x5245, 0x524B, 0x5261, 0x526D, 0x5273, 0x5281, 0x5293, 0x5297, 0x529D, 0x52A5, 0x52AB, 0x52B1,
/*E0-EF*/	0x52BB, 0x52C3, 0x52C7, 0x52C9, 0x52DB, 0x52E5, 0x52EB, 0x52FF, 0x5315, 0x531D, 0x5323, 0x5341, 0x5345, 0x5347, 0x534B, 0x535D,
/*F0-FF*/	0x5363, 0x5381, 0x5383, 0x5387, 0x538F, 0x5395, 0x5399, 0x539F, 0x53AB, 0x53B9, 0x53DB, 0x53E9, 0x53EF, 0x53F3, 0x53F5, 0x53FB,
// 0x200-0x2FF
/*00-0F*/	0x53FF, 0x540D, 0x5411, 0x5413, 0x5419, 0x5435, 0x5437, 0x543B, 0x5441, 0x5449, 0x5453, 0x5455, 0x545F, 0x5461, 0x546B, 0x546D,
/*10-1F*/	0x5471, 0x548F, 0x5491, 0x549D, 0x54A9, 0x54B3, 0x54C5, 0x54D1, 0x54DF, 0x54E9, 0x54EB, 0x54F7, 0x54FD, 0x5507, 0x550D, 0x551B,
/*20-2F*/	0x5527, 0x552B, 0x5539, 0x553D, 0x554F, 0x5551, 0x555B, 0x5563, 0x5567, 0x556F, 0x5579, 0x5585, 0x5597, 0x55A9, 0x55B1, 0x55B7,
/*30-3F*/	0x55C9, 0x55D9, 0x55E7, 0x55ED, 0x55F3, 0x55FD, 0x560B, 0x560F, 0x5615, 0x5617, 0x5623, 0x562F, 0x5633, 0x5639, 0x563F, 0x564B,
/*40-4F*/	0x564D, 0x565D, 0x565F, 0x566B, 0x5671, 0x5675, 0x5683, 0x5689, 0x568D, 0x568F, 0x569B, 0x56AD, 0x56B1, 0x56D5, 0x56E7, 0x56F3,
/*50-5F*/	0x56FF, 0x5701, 0x5705, 0x5707, 0x570B, 0x5713, 0x571F, 0x5723, 0x5747, 0x574D, 0x575F, 0x5761, 0x576D, 0x5777, 0x577D, 0x5789,
/*60-6F*/	0x57A1, 0x57A9, 0x57AF, 0x57B5, 0x57C5, 0x57D1, 0x57D3, 0x57E5, 0x57EF, 0x5803, 0x580D, 0x580F, 0x5815, 0x5827, 0x582B, 0x582D,
/*70-7F*/	0x5855, 0x585B, 0x585D, 0x586D, 0x586F, 0x5873, 0x587B, 0x588D, 0x5897, 0x58A3, 0x58A9, 0x58AB, 0x58B5, 0x58BD, 0x58C1, 0x58C7,
/*80-8F*/	0x58D3, 0x58D5, 0x58DF, 0x58F1, 0x58F9, 0x58FF, 0x5903, 0x5917, 0x591B, 0x5921, 0x5945, 0x594B, 0x594D, 0x5957, 0x595D, 0x5975,
/*90-9F*/	0x597B, 0x5989, 0x5999, 0x599F, 0x59B1, 0x59B3, 0x59BD, 0x59D1, 0x59DB, 0x59E3, 0x59E9, 0x59ED, 0x59F3, 0x59F5, 0x59FF, 0x5A01,
/*A0-AF*/	0x5A0D, 0x5A11, 0x5A13, 0x5A17, 0x5A1F, 0x5A29, 0x5A2F, 0x5A3B, 0x5A4D, 0x5A5B, 0x5A67, 0x5A77, 0x5A7F, 0x5A85, 0x5A95, 0x5A9D,
/*B0-BF*/	0x5AA1, 0x5AA3, 0x5AA9, 0x5ABB, 0x5AD3, 0x5AE5, 0x5AEF, 0x5AFB, 0x5AFD, 0x5B01, 0x5B0F, 0x5B19, 0x5B1F, 0x5B25, 0x5B2B, 0x5B3D,
/*C0-CF*/	0x5B49, 0x5B4B, 0x5B67, 0x5B79, 0x5B87, 0x5B97, 0x5BA3, 0x5BB1, 0x5BC9, 0x5BD5, 0x5BEB, 0x5BF1, 0x5BF3, 0x5BFD, 0x5C05, 0x5C09,
/*D0-DF*/	0x5C0B, 0x5C0F, 0x5C1D, 0x5C29, 0x5C2F, 0x5C33, 0x5C39, 0x5C47, 0x5C4B, 0x5C4D, 0x5C51, 0x5C6F, 0x5C75, 0x5C77, 0x5C7D, 0x5C87,
/*E0-EF*/	0x5C89, 0x5CA7, 0x5CBD, 0x5CBF, 0x5CC3, 0x5CC9, 0x5CD1, 0x5CD7, 0x5CDD, 0x5CED, 0x5CF9, 0x5D05, 0x5D0B, 0x5D13, 0x5D17, 0x5D19,
/*F0-FF*/	0x5D31, 0x5D3D, 0x5D41, 0x5D47, 0x5D4F, 0x5D55, 0x5D5B, 0x5D65, 0x5D67, 0x5D6D, 0x5D79, 0x5D95, 0x5DA3, 0x5DA9, 0x5DAD, 0x5DB9,
// 0x300-0x3FF
/*00-0F*/	0x5DC1, 0x5DC7, 0x5DD3, 0x5DD7, 0x5DDD, 0x5DEB, 0x5DF1, 0x5DFD, 0x5E07, 0x5E0D, 0x5E13, 0x5E1B, 0x5E21, 0x5E27, 0x5E2B, 0x5E2D,
/*10-1F*/	0x5E31, 0x5E39, 0x5E45, 0x5E49, 0x5E57, 0x5E69, 0x5E73, 0x5E75, 0x5E85, 0x5E8B, 0x5E9F, 0x5EA5, 0x5EAF, 0x5EB7, 0x5EBB, 0x5ED9,
/*20-2F*/	0x5EFD, 0x5F09, 0x5F11, 0x5F27, 0x5F33, 0x5F35, 0x5F3B, 0x5F47, 0x5F57, 0x5F5D, 0x5F63, 0x5F65, 0x5F77, 0x5F7B, 0x5F95, 0x5F99,
/*30-3F*/	0x5FA1, 0x5FB3, 0x5FBD, 0x5FC5, 0x5FCF, 0x5FD5, 0x5FE3, 0x5FE7, 0x5FFB, 0x6011, 0x6023, 0x602F, 0x6037, 0x6053, 0x605F, 0x6065,
/*40-4F*/	0x606B, 0x6073, 0x6079, 0x6085, 0x609D, 0x60AD, 0x60BB, 0x60BF, 0x60CD, 0x60D9, 0x60DF, 0x60E9, 0x60F5, 0x6109, 0x610F, 0x6113,
/*50-5F*/	0x611B, 0x612D, 0x6139, 0x614B, 0x6155, 0x6157, 0x615B, 0x616F, 0x6179, 0x6187, 0x618B, 0x6191, 0x6193, 0x619D, 0x61B5, 0x61C7,
/*60-6F*/	0x61C9, 0x61CD, 0x61E1, 0x61F1, 0x61FF, 0x6209, 0x6217, 0x621D, 0x6221, 0x6227, 0x623B, 0x6241, 0x624B, 0x6251, 0x6253, 0x625F,
/*70-7F*/	0x6265, 0x6283, 0x628D, 0x6295, 0x629B, 0x629F, 0x62A5, 0x62AD, 0x62D5, 0x62D7, 0x62DB, 0x62DD, 0x62E9, 0x62FB, 0x62FF, 0x6305,
/*80-8F*/	0x630D, 0x6317, 0x631D, 0x632F, 0x6341, 0x6343, 0x634F, 0x635F, 0x6367, 0x636D, 0x6371, 0x6377, 0x637D, 0x637F, 0x63B3, 0x63C1,
/*90-9F*/	0x63C5, 0x63D9, 0x63E9, 0x63EB, 0x63EF, 0x63F5, 0x6401, 0x6403, 0x6409, 0x6415, 0x6421, 0x6427, 0x642B, 0x6439, 0x6443, 0x6449,
/*A0-AF*/	0x644F, 0x645D, 0x6467, 0x6475, 0x6485, 0x648D, 0x6493, 0x649F, 0x64A3, 0x64AB, 0x64C1, 0x64C7, 0x64C9, 0x64DB, 0x64F1, 0x64F7,
/*B0-BF*/	0x64F9, 0x650B, 0x6511, 0x6521, 0x652F, 0x6539, 0x653F, 0x654B, 0x654D, 0x6553, 0x6557, 0x655F, 0x6571, 0x657D, 0x658D, 0x658F,
/*C0-CF*/	0x6593, 0x65A1, 0x65A5, 0x65AD, 0x65B9, 0x65C5, 0x65E3, 0x65F3, 0x65FB, 0x65FF, 0x6601, 0x6607, 0x661D, 0x6629, 0x6631, 0x663B,
/*D0-DF*/	0x6641, 0x6647, 0x664D, 0x665B, 0x6661, 0x6673, 0x667D, 0x6689, 0x668B, 0x6695, 0x6697, 0x669B, 0x66B5, 0x66B9, 0x66C5, 0x66CD,
/*E0-EF*/	0x66D1, 0x66E3, 0x66EB, 0x66F5, 0x6703, 0x6713, 0x6719, 0x671F, 0x6727, 0x6731, 0x6737, 0x673F, 0x6745, 0x6751, 0x675B, 0x676F,
/*F0-FF*/	0x6779, 0x6781, 0x6785, 0x6791, 0x67AB, 0x67BD, 0x67C1, 0x67CD, 0x67DF, 0x67E5, 0x6803, 0x6809, 0x6811, 0x6817, 0x682D, 0x6839,
};


inline void write4BE(BYTE *p, DWORD val)
{
	DWORD shifts[4] = { 0x18, 0x10, 0x08, 0 };

	for ( int i = 0; i < 4; ++i)
		p[i] = static_cast<BYTE>((val >> shifts[i]) & 0xFF);
}

inline void write2BE(BYTE *p, DWORD val)
{
	DWORD shifts[2] = { 0x08, 0 };

	for ( int i = 0; i < 2; ++i)
		p[i] = static_cast<BYTE>((val >> shifts[i]) & 0xFF);
}


inline DWORD read2BE(BYTE *p)
{
	DWORD val = 0;
	for ( int i = 0; i < 2; ++i)
		val = (val << 8) + p[i];
	return val;
}

DWORD GetMultipliers(const WORD* const /*in*/ pLookupTable, LPBYTE /*in*/ pInputBuffer, int inputBufferLength, int loopCount, LPBYTE /*out*/ pDestFactors = 0);
// Derives values from given buffer.
// Returns main value, and optionally write 2 other WORD values in user-provided pDestFactors buffer.
DWORD GetMultipliers(const WORD* const /*in*/ pLookupTable, LPBYTE /*in*/ pInputBuffer, int inputBufferLength, int loopCount, LPBYTE /*out*/ pDestFactors)
{
	// note, only multiplier1 is used for scrambled ROFS
	DWORD multiplier1 = 0x4A1D, multiplier2 = 0x53FF, multiplier3 = 0x5DC1;
	
	for ( int i = 0; i < loopCount; ++i )
	{
		DWORD multiplier_tmp;
DEBUG_CODE			fprintf(stderr, "# @(%02X): 0x%08X\n", pInputBuffer[i], pLookupTable[*(char*)(pInputBuffer + i) + 0x80]);

DEBUG_CODE			fprintf(stderr, "### (0x%04X) 0x%04X * 0x%04X = 0x%08X\n", multiplier1, ((short int)multiplier1), (pLookupTable[*(char*)(pInputBuffer + i) + 0x80]), ((short int)multiplier1) * (pLookupTable[*(char*)(pInputBuffer + i) + 0x80]));

		multiplier_tmp = multiplier1 = ((short int)multiplier1) * (pLookupTable[*(char*)(pInputBuffer + i) + 0x80]);
		multiplier1 &= 0x800003FF;
		if ( LONG(multiplier1) < 0 )
		{
			multiplier1 = static_cast<DWORD>(- LONG(multiplier1));
		}
DEBUG_CODE			fprintf(stderr, "#MUL1=> 0x%08X (0x%03X): 0x%04X\n", multiplier_tmp, multiplier1, pLookupTable[multiplier1]);
		multiplier1 = pLookupTable[multiplier1];

		multiplier_tmp = multiplier2 = ((short int)multiplier2) * (pLookupTable[*(char*)(pInputBuffer + i) + 0x80]);
		multiplier2 &= 0x800003FF;
		if ( LONG(multiplier2) < 0 )
		{
			multiplier2 = static_cast<DWORD>(- LONG(multiplier2));
		}
DEBUG_CODE			fprintf(stderr, "#MUL2=> 0x%08X (0x%03X): 0x%04X\n", multiplier_tmp, multiplier2, pLookupTable[multiplier2]);
		multiplier2 = pLookupTable[multiplier2];


		multiplier_tmp = multiplier3 = ((short int)multiplier3) * (pLookupTable[*(char*)(pInputBuffer + i) + 0x80]);
		multiplier3 &= 0x800003FF;
		if ( LONG(multiplier3) < 0 )
		{
			multiplier3 = static_cast<DWORD>(- LONG(multiplier3));
		}
DEBUG_CODE			fprintf(stderr, "#MUL3=> 0x%04X (0x%03X): 0x%04X\n", multiplier_tmp, multiplier3, pLookupTable[multiplier3]);
		multiplier3 = pLookupTable[multiplier3];
	}
	
	DEBUG_CODE	fprintf(stderr, "#MUL#0x%03X, 0x%03X, 0x%03X\n", multiplier1, multiplier2, multiplier3);

	if ( pDestFactors )
	{
		write2BE(pDestFactors, multiplier2);
		write2BE(pDestFactors+2, multiplier3);
	}

	return LOWORD(multiplier1);
}





// ;  Xorgen0
void Xorgen0(LPBYTE /*in*/ IV, LPBYTE /*in*/ xorgenValues, LPBYTE /*out*/ mutatedVector)
{
	mutatedVector[0] = IV[3] ^ xorgenValues[0];
	mutatedVector[1] = IV[0];
	mutatedVector[2] = IV[7] ^ xorgenValues[3];
	mutatedVector[3] = IV[4];
	mutatedVector[4] = IV[1];
	mutatedVector[5] = IV[6] ^ xorgenValues[2];
	mutatedVector[6] = IV[2];
	mutatedVector[7] = IV[5] ^ xorgenValues[1];
}


// ;  Xorgen1
void Xorgen1(LPBYTE /*in*/ IV, LPBYTE /*in*/ xorgenValues, LPBYTE /*out*/ mutatedVector)
{
	mutatedVector[0] = IV[2] ^ xorgenValues[1];
	mutatedVector[1] = IV[7];
	mutatedVector[2] = IV[5];
	mutatedVector[3] = IV[3] ^ xorgenValues[2];
	mutatedVector[4] = IV[0] ^ xorgenValues[0];
	mutatedVector[5] = IV[6];
	mutatedVector[6] = IV[4];
	mutatedVector[7] = IV[1] ^ xorgenValues[3];
}

// ;  Xorgen2
void Xorgen2(LPBYTE /*in*/ IV, LPBYTE /*in*/ xorgenValues, LPBYTE /*out*/ mutatedVector)
{
	mutatedVector[0] = IV[1];
	mutatedVector[1] = IV[7] ^ xorgenValues[2];
	mutatedVector[2] = IV[6];
	mutatedVector[3] = IV[2] ^ xorgenValues[1];
	mutatedVector[4] = IV[5] ^ xorgenValues[3];
	mutatedVector[5] = IV[3];
	mutatedVector[6] = IV[0] ^ xorgenValues[0];
	mutatedVector[7] = IV[4];
}

// ;  Xorgen3
void Xorgen3(LPBYTE /*in*/ IV, LPBYTE /*in*/ xorgenValues, LPBYTE /*out*/ mutatedVector)
{
	// Conversion to BYTE truncates
	mutatedVector[0] = IV[3] + xorgenValues[2];
	mutatedVector[1] = IV[6];
	mutatedVector[2] = IV[0];
	mutatedVector[3] = IV[2];
	mutatedVector[4] = IV[4] + xorgenValues[0];
	mutatedVector[5] = IV[1] + xorgenValues[1];
	mutatedVector[6] = IV[7];
	mutatedVector[7] = IV[5] + xorgenValues[3];
}

// ;  Xorgen4
void Xorgen4(LPBYTE /*in*/ IV, LPBYTE /*in*/ xorgenValues, LPBYTE /*out*/ mutatedVector)
{
	mutatedVector[0] = IV[7];
	mutatedVector[1] = IV[0] + xorgenValues[3];
	mutatedVector[2] = IV[2] + xorgenValues[0];
	mutatedVector[3] = IV[6] + xorgenValues[1];
	mutatedVector[4] = IV[4];
	mutatedVector[5] = IV[3];
	mutatedVector[6] = IV[5];
	mutatedVector[7] = IV[1] + xorgenValues[2];
}

// ;  Xorgen5
void Xorgen5(LPBYTE /*in*/ IV, LPBYTE /*in*/ xorgenValues, LPBYTE /*out*/ mutatedVector)
{
	mutatedVector[0] = IV[2];
	mutatedVector[1] = IV[3] + xorgenValues[2];
	mutatedVector[2] = IV[6];
	mutatedVector[3] = IV[7] + xorgenValues[0];
	mutatedVector[4] = IV[0];
	mutatedVector[5] = IV[1] + xorgenValues[1];
	mutatedVector[6] = IV[4];
	mutatedVector[7] = IV[5] + xorgenValues[3];
}

// ;  Xorgen6
void Xorgen6(LPBYTE /*in*/ IV, LPBYTE /*in*/ xorgenValues, LPBYTE /*out*/ mutatedVector)
{
	mutatedVector[0] = IV[3] + xorgenValues[0];
	mutatedVector[1] = IV[7];
	mutatedVector[2] = IV[2] ^ xorgenValues[1];
	mutatedVector[3] = IV[6];
	mutatedVector[4] = IV[1];
	mutatedVector[5] = IV[5] ^ xorgenValues[2];
	mutatedVector[6] = IV[0];
	mutatedVector[7] = IV[4] + xorgenValues[3];
}

// ;  Xorgen7
void Xorgen7(LPBYTE /*in*/ IV, LPBYTE /*in*/ xorgenValues, LPBYTE /*out*/ mutatedVector)
{
	mutatedVector[0] = IV[7];
	mutatedVector[1] = IV[4] ^ xorgenValues[3];
	mutatedVector[2] = IV[3];
	mutatedVector[3] = IV[1] + xorgenValues[2];
	mutatedVector[4] = IV[0];
	mutatedVector[5] = IV[2];
	mutatedVector[6] = IV[5] + xorgenValues[1];
	mutatedVector[7] = IV[6] ^ xorgenValues[0];
}

// ;  Xorgen8
void Xorgen8(LPBYTE /*in*/ IV, LPBYTE /*in*/ xorgenValues, LPBYTE /*out*/ mutatedVector)
{
	mutatedVector[0] = IV[3];
	mutatedVector[1] = IV[0] ^ xorgenValues[1];
	mutatedVector[2] = IV[6];
	mutatedVector[3] = IV[4] + xorgenValues[0];
	mutatedVector[4] = IV[2] ^ xorgenValues[3];
	mutatedVector[5] = IV[7];
	mutatedVector[6] = IV[1];
	mutatedVector[7] = IV[5] + xorgenValues[2];
}



CvmXorgenDelegate xorgen_methods[] = {
	Xorgen0,
	Xorgen1,
	Xorgen2,
	Xorgen3,
	Xorgen4,
	Xorgen5,
	Xorgen6,
	Xorgen7,
	Xorgen8,
};



void createSeedTableFromInteger(DWORD seednum, BYTE* pDestSeed)
{
	write4BE(pDestSeed, (seednum << 20) + seednum);
}




};



//----------------------------------- Public ---------------------------------------//


// Creates an initialization vector for the Xor operations
// Uses a seed (pInitializer), which is the product code of specified length. If length == -1, it is calculated based on string length of 0-terminated pInitializer.
// The vector (pDestBuffer), which is supposed to be at least 8 bytes long, is modified in-place.
void CvmCreateXorIV(const BYTE* const pInitializer, int length, const WORD* const pLookupTable, LPBYTE /*out*/ pDestBuffer)
{
	if ( length == -1 )
		length = lstrlenA(reinterpret_cast<const char* const>(pInitializer));

	// ****
	// Compute 32-bit hash of pInitializer
	// ****
	DWORD sum = 0;
	int i, j;
	
	for ( i = 0; i < length; ++i )
	{
		sum = pInitializer[i] * (sum + pInitializer[i]);
		// fprintf(stderr, "*[i=%d] 0x%08X\n", i, sum);

		for ( j = i + 1; j < length; ++j )
		{
			sum += pInitializer[j];
		}
		// fprintf(stderr, "*\t[j=%d]\t0x%08X\n", j, sum);
	}

	DWORD sum2 = (((sum << 0x14) & 0xFFFFFFFF) + sum) & 0xFFFFFFFF;
	// fprintf(stderr, "0x%08X => 0x%08X\n", sum, sum2);
	

	// ****
	// Fill vector for computation (8 bytes)
	// ****
	DWORD shifts[4] = { 0x18, 0, 0x10, 0x08 };

	for ( i = 0; i < 4; ++i)
	{
		pDestBuffer[i] = static_cast<BYTE>((sum2 >> shifts[i]) & 0xFF);
		// fprintf(stderr, "# 0x%02X\n", pDestBuffer[i]);
		pDestBuffer[7-i] = pDestBuffer[i];   //  AA BB CC DD DD CC BB AA
	}
	

	// ****
	// Compute vector in-place, word by word (for a total of 8 bytes)
	// ****	
	for ( int k = 0; k < 4; ++k )
	{
		DWORD updated = GetMultipliers(pLookupTable, pDestBuffer, 8, 2);
		write2BE(pDestBuffer, updated);
		pDestBuffer += 2;
	}

}





//-------------------------------------------------------------------------------//


const WORD * const CvmGetXorLookupTable()
{
	return ::LOOKUP_TABLE;
}


const CvmXorgenDelegate * const CvmGetXorgenMethods()
{
	return ::xorgen_methods;
}





void CvmDecodeSector(LPBYTE IV, LPBYTE /*in/out*/ pData, int dataLength, BYTE sectorIndex)
{
	DWORD offset = 0;
	
	// seednum is initialized using IV, and further modified when processing bytes
	DWORD seednum = IV[5];
	// seedTable is generated using seednum for every 8-byte block and is used in GetMultipliers()
	BYTE seedTable[4] = {};

	// xorgenValues is an array generated by GetMultipliers() and used by xorgen Methods
	BYTE xorgenValues[4] = {};

	// vector to XOR against, that changes every 8 bytes.
	BYTE outputMutatedVector[8] = {};



	for(LPBYTE pCurrent = pData; pCurrent < pData + 0x800; )
	{
		seednum *= sectorIndex;
		createSeedTableFromInteger(seednum, seedTable);

		// in:seedTable out:retval, xorgenValues
		DWORD mul1 = GetMultipliers(LOOKUP_TABLE, seedTable, 4, 4, xorgenValues);
DEBUG_CODE		fprintf(stderr, "mul1:[%04X](%d) mul2:[%04X] mul3:[%04X]\n", mul1, mul1 % 9, read2BE(xorgenValues), read2BE(xorgenValues+2));

		memset(outputMutatedVector, 0x00, 8);

		// Call function pointer in table
		xorgen_methods[mul1 % 9](IV, xorgenValues, outputMutatedVector);

		// reinitialize seednum, its final value in this block will be used for next block.
		seednum = (mul1 % 9) + offset;

		// process data (in-place) using outputMutatedVector, update seednum
		for ( int i = 0; i < 8; ++i )
		{
DEBUG_CODE			fprintf(stderr, "### (%d, %d) 0x%08X * 0x%02X = 0x%08X\n", (mul1 % 9), offset, seednum, outputMutatedVector[i], seednum * outputMutatedVector[i]);
			seednum *= outputMutatedVector[i];
			pCurrent[i] ^= outputMutatedVector[i];
		}
		pCurrent += 8;
		offset += 8;
DEBUG_CODE		fprintf(stderr, "* seednum: [%08X]\n", seednum);
DEBUG_CODE		fprintf(stderr, "* pCurrent: [%08X]\n", pCurrent);
	}


DEBUG_CODE	fprintf(stderr, "* seednum: [%08X]\n", seednum);
}