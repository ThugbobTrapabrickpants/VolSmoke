typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
float16
float2
typedef pointer32 ImageBaseOffset32;

typedef int    int32_t;
typedef long long    int64_t;
typedef long long    longlong;
typedef unsigned long long    qword;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned int    uint32_t;
typedef unsigned long long    uintptr_t;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef short    wchar_t;
typedef unsigned short    word;
#define unkbyte9   unsigned long long
#define unkbyte10   unsigned long long
#define unkbyte11   unsigned long long
#define unkbyte12   unsigned long long
#define unkbyte13   unsigned long long
#define unkbyte14   unsigned long long
#define unkbyte15   unsigned long long
#define unkbyte16   unsigned long long

#define unkuint9   unsigned long long
#define unkuint10   unsigned long long
#define unkuint11   unsigned long long
#define unkuint12   unsigned long long
#define unkuint13   unsigned long long
#define unkuint14   unsigned long long
#define unkuint15   unsigned long long
#define unkuint16   unsigned long long

#define unkint9   long long
#define unkint10   long long
#define unkint11   long long
#define unkint12   long long
#define unkint13   long long
#define unkint14   long long
#define unkint15   long long
#define unkint16   long long

#define unkfloat1   float
#define unkfloat2   float
#define unkfloat3   float
#define unkfloat5   double
#define unkfloat6   double
#define unkfloat7   double
#define unkfloat9   long double
#define unkfloat11   long double
#define unkfloat12   long double
#define unkfloat13   long double
#define unkfloat14   long double
#define unkfloat15   long double
#define unkfloat16   long double

#define BADSPACEBASE   void
#define code   void

typedef unsigned short    wchar16;
typedef struct random_device random_device, *Prandom_device;

struct random_device { // PlaceHolder Class Structure
};

typedef struct _Prime_rehash_policy _Prime_rehash_policy, *P_Prime_rehash_policy;

struct _Prime_rehash_policy { // PlaceHolder Class Structure
};

typedef uint ULONG;

typedef uchar BYTE;

typedef uint DWORD;

typedef ushort WORD;

typedef ulonglong ULONGLONG;

typedef uint ULong;

typedef ulonglong size_t;

typedef float2 __bf16;

typedef int errno_t;

typedef qword DWORD64;

typedef int WINBOOL;

typedef int LONG;

typedef ulonglong ULONG_PTR;

typedef longlong LONGLONG;

typedef longlong ptrdiff_t;

typedef int BOOL;

typedef float2 _Float16;

typedef uint UINT;

typedef struct threadlocaleinfostruct threadlocaleinfostruct, *Pthreadlocaleinfostruct;

typedef struct threadlocaleinfostruct *pthreadlocinfo;

struct threadlocaleinfostruct {
};

typedef struct localeinfo_struct localeinfo_struct, *Plocaleinfo_struct;

typedef struct threadmbcinfostruct threadmbcinfostruct, *Pthreadmbcinfostruct;

typedef struct threadmbcinfostruct *pthreadmbcinfo;

struct localeinfo_struct {
    pthreadlocinfo locinfo;
    pthreadmbcinfo mbcinfo;
};

struct threadmbcinfostruct {
};

typedef struct localeinfo_struct *_locale_t;

typedef struct _RTL_CRITICAL_SECTION _RTL_CRITICAL_SECTION, *P_RTL_CRITICAL_SECTION;

typedef struct _RTL_CRITICAL_SECTION RTL_CRITICAL_SECTION;

typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;

typedef struct _RTL_CRITICAL_SECTION_DEBUG _RTL_CRITICAL_SECTION_DEBUG, *P_RTL_CRITICAL_SECTION_DEBUG;

typedef struct _RTL_CRITICAL_SECTION_DEBUG *PRTL_CRITICAL_SECTION_DEBUG;

typedef void *HANDLE;

typedef struct _LIST_ENTRY _LIST_ENTRY, *P_LIST_ENTRY;

typedef struct _LIST_ENTRY LIST_ENTRY;

struct _RTL_CRITICAL_SECTION {
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;
};

struct _RTL_CRITICAL_SECTION_DEBUG {
    WORD Type;
    WORD CreatorBackTraceIndex;
    struct _RTL_CRITICAL_SECTION *CriticalSection;
    LIST_ENTRY ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Flags;
    WORD CreatorBackTraceIndexHigh;
    WORD SpareWORD;
};

struct _LIST_ENTRY {
    struct _LIST_ENTRY *Flink;
    struct _LIST_ENTRY *Blink;
};

typedef struct _RTL_CRITICAL_SECTION *PRTL_CRITICAL_SECTION;

typedef PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;

typedef enum _EXCEPTION_DISPOSITION {
    ExceptionContinueExecution=0,
    ExceptionContinueSearch=1,
    ExceptionNestedException=2,
    ExceptionCollidedUnwind=3
} _EXCEPTION_DISPOSITION;

typedef enum _EXCEPTION_DISPOSITION EXCEPTION_DISPOSITION;

typedef enum VARENUM {
    VT_EMPTY=0,
    VT_NULL=1,
    VT_I2=2,
    VT_I4=3,
    VT_R4=4,
    VT_R8=5,
    VT_CY=6,
    VT_DATE=7,
    VT_BSTR=8,
    VT_DISPATCH=9,
    VT_ERROR=10,
    VT_BOOL=11,
    VT_VARIANT=12,
    VT_UNKNOWN=13,
    VT_DECIMAL=14,
    VT_I1=16,
    VT_UI1=17,
    VT_UI2=18,
    VT_UI4=19,
    VT_I8=20,
    VT_UI8=21,
    VT_INT=22,
    VT_UINT=23,
    VT_VOID=24,
    VT_HRESULT=25,
    VT_PTR=26,
    VT_SAFEARRAY=27,
    VT_CARRAY=28,
    VT_USERDEFINED=29,
    VT_LPSTR=30,
    VT_LPWSTR=31,
    VT_RECORD=36,
    VT_INT_PTR=37,
    VT_UINT_PTR=38,
    VT_FILETIME=64,
    VT_BLOB=65,
    VT_STREAM=66,
    VT_STORAGE=67,
    VT_STREAMED_OBJECT=68,
    VT_STORED_OBJECT=69,
    VT_BLOB_OBJECT=70,
    VT_CF=71,
    VT_CLSID=72,
    VT_VERSIONED_STREAM=73,
    VT_BSTR_BLOB=4095,
    VT_ILLEGALMASKED=4095,
    VT_TYPEMASK=4095,
    VT_VECTOR=4096,
    VT_ARRAY=8192,
    VT_BYREF=16384,
    VT_RESERVED=32768,
    VT_ILLEGAL=65535
} VARENUM;

typedef union __mingw_ldbl_type_t __mingw_ldbl_type_t, *P__mingw_ldbl_type_t;

typedef struct anon_struct_16_5_a4d538a0_for_lh anon_struct_16_5_a4d538a0_for_lh, *Panon_struct_16_5_a4d538a0_for_lh;

struct anon_struct_16_5_a4d538a0_for_lh {
    uint32_t low;
    uint32_t high;
    int32_t sign_exponent:16;
    int32_t res1:16;
    int32_t res0:32;
};

union __mingw_ldbl_type_t {
    long double x;
    struct anon_struct_16_5_a4d538a0_for_lh lh;
};

typedef union __mingw_dbl_type_t __mingw_dbl_type_t, *P__mingw_dbl_type_t;

typedef struct anon_struct_8_2_19ee64c9_for_lh anon_struct_8_2_19ee64c9_for_lh, *Panon_struct_8_2_19ee64c9_for_lh;

struct anon_struct_8_2_19ee64c9_for_lh {
    uint32_t low;
    uint32_t high;
};

union __mingw_dbl_type_t {
    double x;
    ulonglong val;
    struct anon_struct_8_2_19ee64c9_for_lh lh;
};

typedef struct _iobuf.conflict _iobuf.conflict, *P_iobuf.conflict;

typedef struct _iobuf.conflict FILE.conflict;

struct _iobuf.conflict {
    void *_Placeholder;
};

typedef struct _iobuf _iobuf, *P_iobuf;

struct _iobuf {
    char *_ptr;
    int _cnt;
    char *_base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char *_tmpfname;
};

typedef struct _iobuf FILE;

typedef BYTE *LPBYTE;

typedef DWORD *PDWORD;

typedef BYTE *PBYTE;

typedef void *LPCVOID;

typedef void *LPVOID;

typedef struct __mingwthr_key __mingwthr_key, *P__mingwthr_key;

typedef struct __mingwthr_key __mingwthr_key_t;

struct __mingwthr_key {
    DWORD key;
    void (*dtor)(void *);
    __mingwthr_key_t *next;
};

typedef char *__gnuc_va_list;

typedef __gnuc_va_list va_list;

typedef struct _Mbstatet _Mbstatet, *P_Mbstatet;

typedef struct _Mbstatet mbstate_t;

struct _Mbstatet {
    ulong _Wchar;
    wchar_t _Byte;
    wchar_t _State;
};

typedef void (*func_ptr)(void);

typedef enum anon_enum_32 {
    FPI_Round_zero=0,
    STRTOG_Zero=0,
    FPI_Round_near=1,
    STRTOG_Normal=1,
    FPI_Round_up=2,
    STRTOG_Denormal=2,
    FPI_Round_down=3,
    STRTOG_Infinite=3,
    STRTOG_NaN=4,
    STRTOG_NaNbits=5,
    STRTOG_NoNumber=6,
    STRTOG_Retmask=7,
    STRTOG_Neg=8,
    STRTOG_Inexlo=16,
    STRTOG_Inexhi=32,
    STRTOG_Inexact=48,
    STRTOG_Underflow=64,
    STRTOG_Overflow=128
} anon_enum_32;

typedef struct FPI.conflict FPI.conflict, *PFPI.conflict;

struct FPI.conflict {
    int32_t nbits;
    int32_t emin;
    int32_t emax;
    int32_t rounding;
    int32_t sudden_underflow;
    int32_t int_max;
};

typedef struct FPI FPI, *PFPI;

struct FPI {
    int nbits;
    int emin;
    int emax;
    int rounding;
    int sudden_underflow;
    int int_max;
};

typedef struct _TEB _TEB, *P_TEB;

struct _TEB {
};

typedef enum __enative_startup_state {
    __uninitialized=0,
    __initializing=1,
    __initialized=2
} __enative_startup_state;

typedef struct lconv lconv, *Plconv;

struct lconv {
    char *decimal_point;
    char *thousands_sep;
    char *grouping;
    char *int_curr_symbol;
    char *currency_symbol;
    char *mon_decimal_point;
    char *mon_thousands_sep;
    char *mon_grouping;
    char *positive_sign;
    char *negative_sign;
    char int_frac_digits;
    char frac_digits;
    char p_cs_precedes;
    char p_sep_by_space;
    char n_cs_precedes;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;
    wchar_t *_W_decimal_point;
    wchar_t *_W_thousands_sep;
    wchar_t *_W_int_curr_symbol;
    wchar_t *_W_currency_symbol;
    wchar_t *_W_mon_decimal_point;
    wchar_t *_W_mon_thousands_sep;
    wchar_t *_W_positive_sign;
    wchar_t *_W_negative_sign;
};

typedef struct runtime_pseudo_reloc_v2 runtime_pseudo_reloc_v2, *Pruntime_pseudo_reloc_v2;

struct runtime_pseudo_reloc_v2 {
    DWORD magic1;
    DWORD magic2;
    DWORD version;
};

typedef struct runtime_pseudo_reloc_item_v2 runtime_pseudo_reloc_item_v2, *Pruntime_pseudo_reloc_item_v2;

struct runtime_pseudo_reloc_item_v2 {
    DWORD sym;
    DWORD target;
    DWORD flags;
};

typedef struct runtime_pseudo_reloc_item_v1 runtime_pseudo_reloc_item_v1, *Pruntime_pseudo_reloc_item_v1;

struct runtime_pseudo_reloc_item_v1 {
    DWORD addend;
    DWORD target;
};

typedef struct sSecInfo sSecInfo, *PsSecInfo;

typedef void *PVOID;

typedef ULONG_PTR SIZE_T;

typedef struct _IMAGE_SECTION_HEADER _IMAGE_SECTION_HEADER, *P_IMAGE_SECTION_HEADER;

typedef struct _IMAGE_SECTION_HEADER *PIMAGE_SECTION_HEADER;

typedef union anon_union_4_2_d8da8690_for_Misc anon_union_4_2_d8da8690_for_Misc, *Panon_union_4_2_d8da8690_for_Misc;

struct sSecInfo {
    DWORD old_protect;
    PVOID base_address;
    SIZE_T region_size;
    PBYTE sec_start;
    PIMAGE_SECTION_HEADER hash;
};

union anon_union_4_2_d8da8690_for_Misc {
    DWORD PhysicalAddress;
    DWORD VirtualSize;
};

struct _IMAGE_SECTION_HEADER {
    BYTE Name[8];
    union anon_union_4_2_d8da8690_for_Misc Misc;
    DWORD VirtualAddress;
    DWORD SizeOfRawData;
    DWORD PointerToRawData;
    DWORD PointerToRelocations;
    DWORD PointerToLinenumbers;
    WORD NumberOfRelocations;
    WORD NumberOfLinenumbers;
    DWORD Characteristics;
};

typedef struct _IMAGE_IMPORT_DESCRIPTOR _IMAGE_IMPORT_DESCRIPTOR, *P_IMAGE_IMPORT_DESCRIPTOR;

typedef struct _IMAGE_IMPORT_DESCRIPTOR IMAGE_IMPORT_DESCRIPTOR;

typedef union anon_union_4_2_b1ad5ba6_for__IMAGE_IMPORT_DESCRIPTOR_0 anon_union_4_2_b1ad5ba6_for__IMAGE_IMPORT_DESCRIPTOR_0, *Panon_union_4_2_b1ad5ba6_for__IMAGE_IMPORT_DESCRIPTOR_0;

union anon_union_4_2_b1ad5ba6_for__IMAGE_IMPORT_DESCRIPTOR_0 {
    DWORD Characteristics;
    DWORD OriginalFirstThunk;
};

struct _IMAGE_IMPORT_DESCRIPTOR {
    union anon_union_4_2_b1ad5ba6_for__IMAGE_IMPORT_DESCRIPTOR_0 field_0;
    DWORD TimeDateStamp;
    DWORD ForwarderChain;
    DWORD Name;
    DWORD FirstThunk;
};

typedef struct _MEMORY_BASIC_INFORMATION _MEMORY_BASIC_INFORMATION, *P_MEMORY_BASIC_INFORMATION;

struct _MEMORY_BASIC_INFORMATION {
    PVOID BaseAddress;
    PVOID AllocationBase;
    DWORD AllocationProtect;
    WORD PartitionId;
    SIZE_T RegionSize;
    DWORD State;
    DWORD Protect;
    DWORD Type;
};

typedef struct _IMAGE_DOS_HEADER _IMAGE_DOS_HEADER, *P_IMAGE_DOS_HEADER;

struct _IMAGE_DOS_HEADER {
    WORD e_magic;
    WORD e_cblp;
    WORD e_cp;
    WORD e_crlc;
    WORD e_cparhdr;
    WORD e_minalloc;
    WORD e_maxalloc;
    WORD e_ss;
    WORD e_sp;
    WORD e_csum;
    WORD e_ip;
    WORD e_cs;
    WORD e_lfarlc;
    WORD e_ovno;
    WORD e_res[4];
    WORD e_oemid;
    WORD e_oeminfo;
    WORD e_res2[10];
    LONG e_lfanew;
};

typedef enum JOB_OBJECT_NET_RATE_CONTROL_FLAGS {
    JOB_OBJECT_NET_RATE_CONTROL_ENABLE=1,
    JOB_OBJECT_NET_RATE_CONTROL_MAX_BANDWIDTH=2,
    JOB_OBJECT_NET_RATE_CONTROL_DSCP_TAG=4,
    JOB_OBJECT_NET_RATE_CONTROL_VALID_FLAGS=7
} JOB_OBJECT_NET_RATE_CONTROL_FLAGS;

typedef struct _MEMORY_BASIC_INFORMATION MEMORY_BASIC_INFORMATION;

typedef struct _EXCEPTION_REGISTRATION_RECORD _EXCEPTION_REGISTRATION_RECORD, *P_EXCEPTION_REGISTRATION_RECORD;

typedef union anon_union_8_2_30252521_for__EXCEPTION_REGISTRATION_RECORD_0 anon_union_8_2_30252521_for__EXCEPTION_REGISTRATION_RECORD_0, *Panon_union_8_2_30252521_for__EXCEPTION_REGISTRATION_RECORD_0;

typedef union anon_union_8_2_988ba941_for__EXCEPTION_REGISTRATION_RECORD_1 anon_union_8_2_988ba941_for__EXCEPTION_REGISTRATION_RECORD_1, *Panon_union_8_2_988ba941_for__EXCEPTION_REGISTRATION_RECORD_1;

typedef struct _EXCEPTION_RECORD _EXCEPTION_RECORD, *P_EXCEPTION_RECORD;

typedef struct _CONTEXT _CONTEXT, *P_CONTEXT;

typedef EXCEPTION_DISPOSITION (*PEXCEPTION_ROUTINE)(struct _EXCEPTION_RECORD *, PVOID, struct _CONTEXT *, PVOID);

typedef union anon_union_512_3_a3503179_for__CONTEXT_38 anon_union_512_3_a3503179_for__CONTEXT_38, *Panon_union_512_3_a3503179_for__CONTEXT_38;

typedef struct _M128A _M128A, *P_M128A;

typedef struct _M128A M128A;

typedef struct _XMM_SAVE_AREA32 _XMM_SAVE_AREA32, *P_XMM_SAVE_AREA32;

typedef struct _XMM_SAVE_AREA32 XMM_SAVE_AREA32;

typedef struct anon_struct_416_18_1bcf7cc9_for_anon_union_512_3_a3503179_for__CONTEXT_38_2 anon_struct_416_18_1bcf7cc9_for_anon_union_512_3_a3503179_for__CONTEXT_38_2, *Panon_struct_416_18_1bcf7cc9_for_anon_union_512_3_a3503179_for__CONTEXT_38_2;

union anon_union_8_2_30252521_for__EXCEPTION_REGISTRATION_RECORD_0 {
    struct _EXCEPTION_REGISTRATION_RECORD *Next;
    struct _EXCEPTION_REGISTRATION_RECORD *prev;
};

union anon_union_8_2_988ba941_for__EXCEPTION_REGISTRATION_RECORD_1 {
    PEXCEPTION_ROUTINE Handler;
    PEXCEPTION_ROUTINE handler;
};

struct _EXCEPTION_RECORD {
    DWORD ExceptionCode;
    DWORD ExceptionFlags;
    struct _EXCEPTION_RECORD *ExceptionRecord;
    PVOID ExceptionAddress;
    DWORD NumberParameters;
    ULONG_PTR ExceptionInformation[15];
};

struct anon_struct_416_18_1bcf7cc9_for_anon_union_512_3_a3503179_for__CONTEXT_38_2 {
    M128A Header[2];
    M128A Legacy[8];
    M128A Xmm0;
    M128A Xmm1;
    M128A Xmm2;
    M128A Xmm3;
    M128A Xmm4;
    M128A Xmm5;
    M128A Xmm6;
    M128A Xmm7;
    M128A Xmm8;
    M128A Xmm9;
    M128A Xmm10;
    M128A Xmm11;
    M128A Xmm12;
    M128A Xmm13;
    M128A Xmm14;
    M128A Xmm15;
};

struct _M128A {
    ULONGLONG Low;
    LONGLONG High;
};

struct _XMM_SAVE_AREA32 {
    WORD ControlWord;
    WORD StatusWord;
    BYTE TagWord;
    BYTE Reserved1;
    WORD ErrorOpcode;
    DWORD ErrorOffset;
    WORD ErrorSelector;
    WORD Reserved2;
    DWORD DataOffset;
    WORD DataSelector;
    WORD Reserved3;
    DWORD MxCsr;
    DWORD MxCsr_Mask;
    M128A FloatRegisters[8];
    M128A XmmRegisters[16];
    BYTE Reserved4[96];
};

struct _EXCEPTION_REGISTRATION_RECORD {
    union anon_union_8_2_30252521_for__EXCEPTION_REGISTRATION_RECORD_0 field_0;
    union anon_union_8_2_988ba941_for__EXCEPTION_REGISTRATION_RECORD_1 field_1;
};

union anon_union_512_3_a3503179_for__CONTEXT_38 {
    XMM_SAVE_AREA32 FltSave;
    XMM_SAVE_AREA32 FloatSave;
    struct anon_struct_416_18_1bcf7cc9_for_anon_union_512_3_a3503179_for__CONTEXT_38_2 field_2;
};

struct _CONTEXT {
    DWORD64 P1Home;
    DWORD64 P2Home;
    DWORD64 P3Home;
    DWORD64 P4Home;
    DWORD64 P5Home;
    DWORD64 P6Home;
    DWORD ContextFlags;
    DWORD MxCsr;
    WORD SegCs;
    WORD SegDs;
    WORD SegEs;
    WORD SegFs;
    WORD SegGs;
    WORD SegSs;
    DWORD EFlags;
    DWORD64 Dr0;
    DWORD64 Dr1;
    DWORD64 Dr2;
    DWORD64 Dr3;
    DWORD64 Dr6;
    DWORD64 Dr7;
    DWORD64 Rax;
    DWORD64 Rcx;
    DWORD64 Rdx;
    DWORD64 Rbx;
    DWORD64 Rsp;
    DWORD64 Rbp;
    DWORD64 Rsi;
    DWORD64 Rdi;
    DWORD64 R8;
    DWORD64 R9;
    DWORD64 R10;
    DWORD64 R11;
    DWORD64 R12;
    DWORD64 R13;
    DWORD64 R14;
    DWORD64 R15;
    DWORD64 Rip;
    union anon_union_512_3_a3503179_for__CONTEXT_38 field_38;
    M128A VectorRegister[26];
    DWORD64 VectorControl;
    DWORD64 DebugControl;
    DWORD64 LastBranchToRip;
    DWORD64 LastBranchFromRip;
    DWORD64 LastExceptionToRip;
    DWORD64 LastExceptionFromRip;
};

typedef struct _IMAGE_NT_HEADERS64 _IMAGE_NT_HEADERS64, *P_IMAGE_NT_HEADERS64;

typedef struct _IMAGE_FILE_HEADER _IMAGE_FILE_HEADER, *P_IMAGE_FILE_HEADER;

typedef struct _IMAGE_FILE_HEADER IMAGE_FILE_HEADER;

typedef struct _IMAGE_OPTIONAL_HEADER64 _IMAGE_OPTIONAL_HEADER64, *P_IMAGE_OPTIONAL_HEADER64;

typedef struct _IMAGE_OPTIONAL_HEADER64 IMAGE_OPTIONAL_HEADER64;

typedef struct _IMAGE_DATA_DIRECTORY _IMAGE_DATA_DIRECTORY, *P_IMAGE_DATA_DIRECTORY;

typedef struct _IMAGE_DATA_DIRECTORY IMAGE_DATA_DIRECTORY;

struct _IMAGE_NT_HEADERS64 {
    DWORD Signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER64 OptionalHeader;
};

struct _IMAGE_FILE_HEADER {
    WORD Machine;
    WORD NumberOfSections;
    DWORD TimeDateStamp;
    DWORD PointerToSymbolTable;
    DWORD NumberOfSymbols;
    WORD SizeOfOptionalHeader;
    WORD Characteristics;
};

struct _IMAGE_OPTIONAL_HEADER64 {
    WORD Magic;
    BYTE MajorLinkerVersion;
    BYTE MinorLinkerVersion;
    DWORD SizeOfCode;
    DWORD SizeOfInitializedData;
    DWORD SizeOfUninitializedData;
    DWORD AddressOfEntryPoint;
    DWORD BaseOfCode;
    ULONGLONG ImageBase;
    DWORD SectionAlignment;
    DWORD FileAlignment;
    WORD MajorOperatingSystemVersion;
    WORD MinorOperatingSystemVersion;
    WORD MajorImageVersion;
    WORD MinorImageVersion;
    WORD MajorSubsystemVersion;
    WORD MinorSubsystemVersion;
    DWORD Win32VersionValue;
    DWORD SizeOfImage;
    DWORD SizeOfHeaders;
    DWORD CheckSum;
    WORD Subsystem;
    WORD DllCharacteristics;
    ULONGLONG SizeOfStackReserve;
    ULONGLONG SizeOfStackCommit;
    ULONGLONG SizeOfHeapReserve;
    ULONGLONG SizeOfHeapCommit;
    DWORD LoaderFlags;
    DWORD NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[16];
};

struct _IMAGE_DATA_DIRECTORY {
    DWORD VirtualAddress;
    DWORD Size;
};

typedef IMAGE_IMPORT_DESCRIPTOR *PIMAGE_IMPORT_DESCRIPTOR;

typedef struct _NT_TIB _NT_TIB, *P_NT_TIB;

typedef struct _NT_TIB NT_TIB;

typedef union anon_union_8_2_9ea3c503_for__NT_TIB_4 anon_union_8_2_9ea3c503_for__NT_TIB_4, *Panon_union_8_2_9ea3c503_for__NT_TIB_4;

union anon_union_8_2_9ea3c503_for__NT_TIB_4 {
    PVOID FiberData;
    DWORD Version;
};

struct _NT_TIB {
    struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList;
    PVOID StackBase;
    PVOID StackLimit;
    PVOID SubSystemTib;
    union anon_union_8_2_9ea3c503_for__NT_TIB_4 field_4;
    PVOID ArbitraryUserPointer;
    struct _NT_TIB *Self;
};

typedef NT_TIB *PNT_TIB;

typedef struct _IMAGE_OPTIONAL_HEADER64 *PIMAGE_OPTIONAL_HEADER64;

typedef PIMAGE_OPTIONAL_HEADER64 PIMAGE_OPTIONAL_HEADER;

typedef struct _IMAGE_DOS_HEADER *PIMAGE_DOS_HEADER;

typedef struct _IMAGE_NT_HEADERS64 *PIMAGE_NT_HEADERS64;

typedef struct _IMAGE_TLS_DIRECTORY64 _IMAGE_TLS_DIRECTORY64, *P_IMAGE_TLS_DIRECTORY64;

typedef struct _IMAGE_TLS_DIRECTORY64 IMAGE_TLS_DIRECTORY64;

typedef IMAGE_TLS_DIRECTORY64 IMAGE_TLS_DIRECTORY;

struct _IMAGE_TLS_DIRECTORY64 {
    ULONGLONG StartAddressOfRawData;
    ULONGLONG EndAddressOfRawData;
    ULONGLONG AddressOfIndex;
    ULONGLONG AddressOfCallBacks;
    DWORD SizeOfZeroFill;
    DWORD Characteristics;
};

typedef struct _MEMORY_BASIC_INFORMATION *PMEMORY_BASIC_INFORMATION;

typedef struct _IMAGE_DOS_HEADER IMAGE_DOS_HEADER;

typedef PIMAGE_NT_HEADERS64 PIMAGE_NT_HEADERS;

typedef void (*PIMAGE_TLS_CALLBACK)(PVOID, DWORD, PVOID);

typedef ULONG_PTR DWORD_PTR;

typedef struct _onexit_table_t _onexit_table_t, *P_onexit_table_t;

typedef void (*_PVFV)(void);

struct _onexit_table_t {
    _PVFV *_first;
    _PVFV *_last;
    _PVFV *_end;
};

typedef int (*_PIFV)(void);

typedef union __pformat_fpreg_t __pformat_fpreg_t, *P__pformat_fpreg_t;

typedef struct anon_struct_16_2_b02704d6_for___pformat_fpreg_t_2 anon_struct_16_2_b02704d6_for___pformat_fpreg_t_2, *Panon_struct_16_2_b02704d6_for___pformat_fpreg_t_2;

struct anon_struct_16_2_b02704d6_for___pformat_fpreg_t_2 {
    ulonglong __pformat_fpreg_mantissa;
    short __pformat_fpreg_exponent;
};

union __pformat_fpreg_t {
    double __pformat_fpreg_double_t;
    long double __pformat_fpreg_ldouble_t;
    struct anon_struct_16_2_b02704d6_for___pformat_fpreg_t_2 field_2;
    wchar_t __pformat_fpreg_bitmap[5];
    ULong __pformat_fpreg_bits;
};

typedef enum __pformat_length_t {
    PFORMAT_LENGTH_INT=0,
    PFORMAT_LENGTH_SHORT=1,
    PFORMAT_LENGTH_LONG=2,
    PFORMAT_LENGTH_LLONG=3,
    PFORMAT_LENGTH_LLONG128=4,
    PFORMAT_LENGTH_CHAR=5
} __pformat_length_t;

typedef union __pformat_intarg_t __pformat_intarg_t, *P__pformat_intarg_t;

typedef union __uI128 __uI128, *P__uI128;

typedef struct __tI128 __tI128, *P__tI128;

typedef struct __tI128_2 __tI128_2, *P__tI128_2;

struct __tI128 {
    int64_t digits[2];
};

struct __tI128_2 {
    uint32_t digits32[4];
};

union __uI128 {
    struct __tI128 t128;
    struct __tI128_2 t128_2;
};

union __pformat_intarg_t {
    long __pformat_long_t;
    int64_t __pformat_llong_t;
    ulong __pformat_ulong_t;
    ulonglong __pformat_ullong_t;
    wchar_t __pformat_ushort_t;
    uchar __pformat_uchar_t;
    short __pformat_short_t;
    char __pformat_char_t;
    void *__pformat_ptr_t;
    union __uI128 __pformat_u128_t;
};

typedef struct __pformat_t __pformat_t, *P__pformat_t;

struct __pformat_t {
    void *dest;
    int32_t flags;
    int32_t width;
    int32_t precision;
    int32_t rplen;
    wchar_t rpchr;
    int32_t thousands_chr_len;
    wchar_t thousands_chr;
    int32_t count;
    int32_t quota;
    int32_t expmin;
};

typedef enum __pformat_state_t {
    PFORMAT_INIT=0,
    PFORMAT_SET_WIDTH=1,
    PFORMAT_GET_PRECISION=2,
    PFORMAT_SET_PRECISION=3,
    PFORMAT_END=4
} __pformat_state_t;

typedef enum tagCOINITBASE {
    COINITBASE_MULTITHREADED=0
} tagCOINITBASE;

typedef union anon_union_4_2_9472fd7b anon_union_4_2_9472fd7b, *Panon_union_4_2_9472fd7b;

union anon_union_4_2_9472fd7b {
    ULong L[1];
    float f;
};

typedef struct __Bigint __Bigint, *P__Bigint;

struct __Bigint {
    struct __Bigint *next;
    int k;
    int maxwds;
    int sign;
    int wds;
    ULong x[1];
};

typedef union _dbl_union _dbl_union, *P_dbl_union;

typedef union _dbl_union dbl_union;

union _dbl_union {
    double d;
    ULong L[2];
};

typedef int (*_onexit_t)(void);

typedef struct _SECURITY_ATTRIBUTES _SECURITY_ATTRIBUTES, *P_SECURITY_ATTRIBUTES;


// WARNING! conflicting data type names: /WinDef.h/DWORD - /DWARF/DWORD

struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
};


// WARNING! conflicting data type names: /winbase.h/LPCRITICAL_SECTION - /DWARF/minwinbase.h/LPCRITICAL_SECTION


// WARNING! conflicting data type names: /excpt.h/_CONTEXT - /DWARF/winnt.h/_CONTEXT

typedef struct _CONTEXT *PCONTEXT;

typedef PCONTEXT LPCONTEXT;

typedef DWORD (*PTHREAD_START_ROUTINE)(LPVOID);

typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

typedef struct _RTL_SRWLOCK _RTL_SRWLOCK, *P_RTL_SRWLOCK;

typedef struct _RTL_SRWLOCK RTL_SRWLOCK;

typedef RTL_SRWLOCK *PSRWLOCK;

struct _RTL_SRWLOCK {
    PVOID Ptr;
};

typedef struct _SECURITY_ATTRIBUTES *LPSECURITY_ATTRIBUTES;


// WARNING! conflicting data type names: /winnt.h/_MEMORY_BASIC_INFORMATION - /DWARF/winnt.h/_MEMORY_BASIC_INFORMATION

typedef struct _CONTEXT CONTEXT;

typedef struct _struct_19 _struct_19, *P_struct_19;


// WARNING! conflicting data type names: /winnt.h/LONG - /DWARF/LONG

struct _struct_19 {
    DWORD LowPart;
    LONG HighPart;
};


// WARNING! conflicting data type names: /winnt.h/_RTL_CRITICAL_SECTION_DEBUG - /DWARF/winnt.h/_RTL_CRITICAL_SECTION_DEBUG


// WARNING! conflicting data type names: /excpt.h/_EXCEPTION_RECORD - /DWARF/winnt.h/_EXCEPTION_RECORD

typedef struct _EXCEPTION_RECORD EXCEPTION_RECORD;

typedef EXCEPTION_RECORD *PEXCEPTION_RECORD;


// WARNING! conflicting data type names: /winnt.h/_RTL_CRITICAL_SECTION - /DWARF/winnt.h/_RTL_CRITICAL_SECTION

typedef char CHAR;

typedef union _LARGE_INTEGER _LARGE_INTEGER, *P_LARGE_INTEGER;

typedef struct _struct_20 _struct_20, *P_struct_20;

struct _struct_19 {
    DWORD LowPart;
    LONG HighPart;
};

struct _struct_20 {
    DWORD LowPart;
    LONG HighPart;
};

union _LARGE_INTEGER {
    struct _struct_19 s;
    struct _struct_20 u;
    LONGLONG QuadPart;
};

typedef union _LARGE_INTEGER LARGE_INTEGER;

typedef struct _XSAVE_FORMAT _XSAVE_FORMAT, *P_XSAVE_FORMAT;

struct _XSAVE_FORMAT {
    WORD ControlWord;
    WORD StatusWord;
    BYTE TagWord;
    BYTE Reserved1;
    WORD ErrorOpcode;
    DWORD ErrorOffset;
    WORD ErrorSelector;
    WORD Reserved2;
    DWORD DataOffset;
    WORD DataSelector;
    WORD Reserved3;
    DWORD MxCsr;
    DWORD MxCsr_Mask;
    M128A FloatRegisters[8];
    M128A XmmRegisters[16];
    BYTE Reserved4[96];
};


// WARNING! conflicting data type names: /winnt.h/PRTL_CRITICAL_SECTION - /DWARF/winnt.h/PRTL_CRITICAL_SECTION

typedef struct _struct_55 _struct_55, *P_struct_55;

struct _struct_55 {
    M128A Header[2];
    M128A Legacy[8];
    M128A Xmm0;
    M128A Xmm1;
    M128A Xmm2;
    M128A Xmm3;
    M128A Xmm4;
    M128A Xmm5;
    M128A Xmm6;
    M128A Xmm7;
    M128A Xmm8;
    M128A Xmm9;
    M128A Xmm10;
    M128A Xmm11;
    M128A Xmm12;
    M128A Xmm13;
    M128A Xmm14;
    M128A Xmm15;
};


// WARNING! conflicting data type names: /winnt.h/XMM_SAVE_AREA32 - /DWARF/winnt.h/XMM_SAVE_AREA32

typedef struct _RUNTIME_FUNCTION _RUNTIME_FUNCTION, *P_RUNTIME_FUNCTION;

struct _RUNTIME_FUNCTION {
    DWORD BeginAddress;
    DWORD EndAddress;
    DWORD UnwindData;
};


// WARNING! conflicting data type names: /winnt.h/LIST_ENTRY - /DWARF/winnt.h/LIST_ENTRY

typedef struct _RUNTIME_FUNCTION *PRUNTIME_FUNCTION;

typedef EXCEPTION_DISPOSITION (EXCEPTION_ROUTINE)(struct _EXCEPTION_RECORD *, PVOID, struct _CONTEXT *, PVOID);

typedef struct _M128A *PM128A;

typedef struct _UNWIND_HISTORY_TABLE_ENTRY _UNWIND_HISTORY_TABLE_ENTRY, *P_UNWIND_HISTORY_TABLE_ENTRY;

typedef struct _UNWIND_HISTORY_TABLE_ENTRY UNWIND_HISTORY_TABLE_ENTRY;


// WARNING! conflicting data type names: /basetsd.h/DWORD64 - /DWARF/DWORD64

struct _UNWIND_HISTORY_TABLE_ENTRY {
    DWORD64 ImageBase;
    PRUNTIME_FUNCTION FunctionEntry;
};

typedef union _union_61 _union_61, *P_union_61;

typedef struct _struct_62 _struct_62, *P_struct_62;

struct _struct_62 {
    PM128A Xmm0;
    PM128A Xmm1;
    PM128A Xmm2;
    PM128A Xmm3;
    PM128A Xmm4;
    PM128A Xmm5;
    PM128A Xmm6;
    PM128A Xmm7;
    PM128A Xmm8;
    PM128A Xmm9;
    PM128A Xmm10;
    PM128A Xmm11;
    PM128A Xmm12;
    PM128A Xmm13;
    PM128A Xmm14;
    PM128A Xmm15;
};

union _union_61 {
    PM128A FloatingContext[16];
    struct _struct_62 s;
};

typedef union _union_63 _union_63, *P_union_63;

typedef ulonglong *PDWORD64;

typedef struct _struct_64 _struct_64, *P_struct_64;

struct _struct_64 {
    PDWORD64 Rax;
    PDWORD64 Rcx;
    PDWORD64 Rdx;
    PDWORD64 Rbx;
    PDWORD64 Rsp;
    PDWORD64 Rbp;
    PDWORD64 Rsi;
    PDWORD64 Rdi;
    PDWORD64 R8;
    PDWORD64 R9;
    PDWORD64 R10;
    PDWORD64 R11;
    PDWORD64 R12;
    PDWORD64 R13;
    PDWORD64 R14;
    PDWORD64 R15;
};

union _union_63 {
    PDWORD64 IntegerContext[16];
    struct _struct_64 s;
};

typedef struct _UNWIND_HISTORY_TABLE _UNWIND_HISTORY_TABLE, *P_UNWIND_HISTORY_TABLE;

typedef struct _UNWIND_HISTORY_TABLE *PUNWIND_HISTORY_TABLE;

struct _UNWIND_HISTORY_TABLE {
    DWORD Count;
    BYTE LocalHint;
    BYTE GlobalHint;
    BYTE Search;
    BYTE Once;
    DWORD64 LowAddress;
    DWORD64 HighAddress;
    UNWIND_HISTORY_TABLE_ENTRY Entry[12];
};

typedef CHAR *LPCSTR;


// WARNING! conflicting data type names: /winnt.h/PMEMORY_BASIC_INFORMATION - /DWARF/winnt.h/PMEMORY_BASIC_INFORMATION

typedef struct _XSAVE_FORMAT XSAVE_FORMAT;


// WARNING! conflicting data type names: /winnt.h/PRTL_CRITICAL_SECTION_DEBUG - /DWARF/winnt.h/PRTL_CRITICAL_SECTION_DEBUG


// WARNING! conflicting data type names: /winnt.h/_LIST_ENTRY - /DWARF/winnt.h/_LIST_ENTRY

typedef union _union_54 _union_54, *P_union_54;

struct _struct_55 {
    M128A Header[2];
    M128A Legacy[8];
    M128A Xmm0;
    M128A Xmm1;
    M128A Xmm2;
    M128A Xmm3;
    M128A Xmm4;
    M128A Xmm5;
    M128A Xmm6;
    M128A Xmm7;
    M128A Xmm8;
    M128A Xmm9;
    M128A Xmm10;
    M128A Xmm11;
    M128A Xmm12;
    M128A Xmm13;
    M128A Xmm14;
    M128A Xmm15;
};

union _union_54 {
    XMM_SAVE_AREA32 FltSave;
    struct _struct_55 s;
};

typedef CHAR *LPSTR;

typedef struct _KNONVOLATILE_CONTEXT_POINTERS _KNONVOLATILE_CONTEXT_POINTERS, *P_KNONVOLATILE_CONTEXT_POINTERS;

typedef struct _KNONVOLATILE_CONTEXT_POINTERS *PKNONVOLATILE_CONTEXT_POINTERS;

union _union_61 {
    PM128A FloatingContext[16];
    struct _struct_62 s;
};

union _union_63 {
    PDWORD64 IntegerContext[16];
    struct _struct_64 s;
};

struct _KNONVOLATILE_CONTEXT_POINTERS {
    union _union_61 u;
    union _union_63 u2;
};


// WARNING! conflicting data type names: /winnt.h/PEXCEPTION_ROUTINE - /DWARF/winnt.h/PEXCEPTION_ROUTINE


// WARNING! conflicting data type names: /DOS/IMAGE_DOS_HEADER - /DWARF/winnt.h/IMAGE_DOS_HEADER

typedef longlong INT_PTR;

typedef ULONG_PTR *PDWORD_PTR;

typedef ulonglong UINT_PTR;

typedef struct _SETJMP_FLOAT128 _SETJMP_FLOAT128, *P_SETJMP_FLOAT128;

typedef struct _SETJMP_FLOAT128 SETJMP_FLOAT128;

typedef SETJMP_FLOAT128 _JBTYPE;

struct _SETJMP_FLOAT128 {
    ulonglong Part[2];
};

typedef struct _FILETIME _FILETIME, *P_FILETIME;

typedef struct _FILETIME *LPFILETIME;

struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
};

typedef INT_PTR (*FARPROC)(void);

typedef struct HINSTANCE__ HINSTANCE__, *PHINSTANCE__;

typedef struct HINSTANCE__ *HINSTANCE;

struct HINSTANCE__ {
    int unused;
};

typedef HINSTANCE HMODULE;

typedef HANDLE *LPHANDLE;

typedef DWORD *LPDWORD;

typedef HANDLE HLOCAL;


// WARNING! conflicting data type names: /WinDef.h/PDWORD - /DWARF/minwindef.h/PDWORD

typedef long *LPLONG;

typedef struct _IMAGE_RUNTIME_FUNCTION_ENTRY _IMAGE_RUNTIME_FUNCTION_ENTRY, *P_IMAGE_RUNTIME_FUNCTION_ENTRY;

struct _IMAGE_RUNTIME_FUNCTION_ENTRY {
    ImageBaseOffset32 BeginAddress;
    dword EndAddress; // Apply ImageBaseOffset32 to see reference
    ImageBaseOffset32 UnwindInfoAddressOrData;
};


// WARNING! conflicting data type names: /PE/IMAGE_FILE_HEADER - /DWARF/winnt.h/IMAGE_FILE_HEADER


// WARNING! conflicting data type names: /PE/IMAGE_OPTIONAL_HEADER64 - /DWARF/winnt.h/IMAGE_OPTIONAL_HEADER64

typedef struct IMAGE_SECTION_HEADER IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

typedef union Misc Misc, *PMisc;

typedef enum SectionFlags {
    IMAGE_SCN_TYPE_NO_PAD=8,
    IMAGE_SCN_RESERVED_0001=16,
    IMAGE_SCN_CNT_CODE=32,
    IMAGE_SCN_CNT_INITIALIZED_DATA=64,
    IMAGE_SCN_CNT_UNINITIALIZED_DATA=128,
    IMAGE_SCN_LNK_OTHER=256,
    IMAGE_SCN_LNK_INFO=512,
    IMAGE_SCN_RESERVED_0040=1024,
    IMAGE_SCN_LNK_REMOVE=2048,
    IMAGE_SCN_LNK_COMDAT=4096,
    IMAGE_SCN_GPREL=32768,
    IMAGE_SCN_MEM_16BIT=131072,
    IMAGE_SCN_MEM_PURGEABLE=131072,
    IMAGE_SCN_MEM_LOCKED=262144,
    IMAGE_SCN_MEM_PRELOAD=524288,
    IMAGE_SCN_ALIGN_1BYTES=1048576,
    IMAGE_SCN_ALIGN_2BYTES=2097152,
    IMAGE_SCN_ALIGN_4BYTES=3145728,
    IMAGE_SCN_ALIGN_8BYTES=4194304,
    IMAGE_SCN_ALIGN_16BYTES=5242880,
    IMAGE_SCN_ALIGN_32BYTES=6291456,
    IMAGE_SCN_ALIGN_64BYTES=7340032,
    IMAGE_SCN_ALIGN_128BYTES=8388608,
    IMAGE_SCN_ALIGN_256BYTES=9437184,
    IMAGE_SCN_ALIGN_512BYTES=10485760,
    IMAGE_SCN_ALIGN_1024BYTES=11534336,
    IMAGE_SCN_ALIGN_2048BYTES=12582912,
    IMAGE_SCN_ALIGN_4096BYTES=13631488,
    IMAGE_SCN_ALIGN_8192BYTES=14680064,
    IMAGE_SCN_LNK_NRELOC_OVFL=16777216,
    IMAGE_SCN_MEM_DISCARDABLE=33554432,
    IMAGE_SCN_MEM_NOT_CACHED=67108864,
    IMAGE_SCN_MEM_NOT_PAGED=134217728,
    IMAGE_SCN_MEM_SHARED=268435456,
    IMAGE_SCN_MEM_EXECUTE=536870912,
    IMAGE_SCN_MEM_READ=1073741824,
    IMAGE_SCN_MEM_WRITE=2147483648
} SectionFlags;

union Misc {
    dword PhysicalAddress;
    dword VirtualSize;
};

struct IMAGE_SECTION_HEADER {
    char Name[8];
    union Misc Misc;
    ImageBaseOffset32 VirtualAddress;
    dword SizeOfRawData;
    dword PointerToRawData;
    dword PointerToRelocations;
    dword PointerToLinenumbers;
    word NumberOfRelocations;
    word NumberOfLinenumbers;
    enum SectionFlags Characteristics;
};

typedef struct IMAGE_NT_HEADERS64 IMAGE_NT_HEADERS64, *PIMAGE_NT_HEADERS64;

struct IMAGE_FILE_HEADER {
    word Machine; // 34404
    word NumberOfSections;
    dword TimeDateStamp;
    dword PointerToSymbolTable;
    dword NumberOfSymbols;
    word SizeOfOptionalHeader;
    word Characteristics;
};

struct IMAGE_OPTIONAL_HEADER64 {
    word Magic;
    byte MajorLinkerVersion;
    byte MinorLinkerVersion;
    dword SizeOfCode;
    dword SizeOfInitializedData;
    dword SizeOfUninitializedData;
    ImageBaseOffset32 AddressOfEntryPoint;
    ImageBaseOffset32 BaseOfCode;
    pointer64 ImageBase;
    dword SectionAlignment;
    dword FileAlignment;
    word MajorOperatingSystemVersion;
    word MinorOperatingSystemVersion;
    word MajorImageVersion;
    word MinorImageVersion;
    word MajorSubsystemVersion;
    word MinorSubsystemVersion;
    dword Win32VersionValue;
    dword SizeOfImage;
    dword SizeOfHeaders;
    dword CheckSum;
    word Subsystem;
    word DllCharacteristics;
    qword SizeOfStackReserve;
    qword SizeOfStackCommit;
    qword SizeOfHeapReserve;
    qword SizeOfHeapCommit;
    dword LoaderFlags;
    dword NumberOfRvaAndSizes;
    struct IMAGE_DATA_DIRECTORY DataDirectory[16];
};

struct IMAGE_NT_HEADERS64 {
    char Signature[4];
    struct IMAGE_FILE_HEADER FileHeader;
    struct IMAGE_OPTIONAL_HEADER64 OptionalHeader;
};


// WARNING! conflicting data type names: /PE/IMAGE_DATA_DIRECTORY - /DWARF/winnt.h/IMAGE_DATA_DIRECTORY

typedef struct IMAGE_BASE_RELOCATION IMAGE_BASE_RELOCATION, *PIMAGE_BASE_RELOCATION;

struct IMAGE_BASE_RELOCATION {
    dword VirtualAddress;
    dword SizeOfBlock;
};

typedef struct IMAGE_THUNK_DATA64 IMAGE_THUNK_DATA64, *PIMAGE_THUNK_DATA64;

struct IMAGE_THUNK_DATA64 {
    qword StartAddressOfRawData;
    qword EndAddressOfRawData;
    qword AddressOfIndex;
    qword AddressOfCallBacks;
    dword SizeOfZeroFill;
    dword Characteristics;
};

typedef struct IMAGE_DIRECTORY_ENTRY_EXPORT IMAGE_DIRECTORY_ENTRY_EXPORT, *PIMAGE_DIRECTORY_ENTRY_EXPORT;

struct IMAGE_DIRECTORY_ENTRY_EXPORT {
    dword Characteristics;
    dword TimeDateStamp;
    word MajorVersion;
    word MinorVersion;
    ImageBaseOffset32 Name;
    dword Base;
    dword NumberOfFunctions;
    dword NumberOfNames;
    ImageBaseOffset32 AddressOfFunctions;
    ImageBaseOffset32 AddressOfNames;
    ImageBaseOffset32 AddressOfNameOrdinals;
};


// WARNING! conflicting data type names: /mbstring.h/_iobuf - /DWARF/stdio.h/_iobuf


// WARNING! conflicting data type names: /mbstring.h/FILE - /DWARF/stdio.h/FILE


// WARNING! conflicting data type names: /vadefs.h/va_list - /DWARF/vadefs.h/va_list


// WARNING! conflicting data type names: /vadefs.h/uintptr_t - /uintptr_t

typedef struct sockaddr sockaddr, *Psockaddr;

typedef ushort u_short;

struct sockaddr {
    u_short sa_family;
    char sa_data[14];
};

typedef ulong u_long;

typedef struct WSAData WSAData, *PWSAData;

typedef struct WSAData WSADATA;

struct WSAData {
    WORD wVersion;
    WORD wHighVersion;
    ushort iMaxSockets;
    ushort iMaxUdpDg;
    char *lpVendorInfo;
    char szDescription[257];
    char szSystemStatus[129];
};

typedef UINT_PTR SOCKET;

typedef WSADATA *LPWSADATA;


// WARNING! conflicting data type names: /wchar.h/mbstate_t - /DWARF/wchar.h/mbstate_t

typedef struct ID3D12Resource ID3D12Resource, *PID3D12Resource;

struct ID3D12Resource { // PlaceHolder Structure
};

typedef struct ID3D11Texture2D ID3D11Texture2D, *PID3D11Texture2D;

struct ID3D11Texture2D { // PlaceHolder Structure
};

typedef struct _Unwind_Context _Unwind_Context, *P_Unwind_Context;

struct _Unwind_Context { // PlaceHolder Structure
};

typedef struct ID3D11DepthStencilView ID3D11DepthStencilView, *PID3D11DepthStencilView;

struct ID3D11DepthStencilView { // PlaceHolder Structure
};

typedef struct ID3D12GraphicsCommandList ID3D12GraphicsCommandList, *PID3D12GraphicsCommandList;

struct ID3D12GraphicsCommandList { // PlaceHolder Structure
};

typedef struct ID3D11Device ID3D11Device, *PID3D11Device;

struct ID3D11Device { // PlaceHolder Structure
};

typedef struct _Unwind_Exception _Unwind_Exception, *P_Unwind_Exception;

struct _Unwind_Exception { // PlaceHolder Structure
};

typedef struct ID3D11DeviceContext ID3D11DeviceContext, *PID3D11DeviceContext;

struct ID3D11DeviceContext { // PlaceHolder Structure
};

typedef struct D3D11_TEXTURE2D_DESC D3D11_TEXTURE2D_DESC, *PD3D11_TEXTURE2D_DESC;

struct D3D11_TEXTURE2D_DESC { // PlaceHolder Structure
};

typedef struct ID3D11Buffer ID3D11Buffer, *PID3D11Buffer;

struct ID3D11Buffer { // PlaceHolder Structure
};

typedef undefined DXGI_FORMAT;

typedef struct lsda_header_info lsda_header_info, *Plsda_header_info;

struct lsda_header_info { // PlaceHolder Structure
};

typedef struct ID3D11RenderTargetView ID3D11RenderTargetView, *PID3D11RenderTargetView;

struct ID3D11RenderTargetView { // PlaceHolder Structure
};

typedef struct ID3D11ShaderResourceView ID3D11ShaderResourceView, *PID3D11ShaderResourceView;

struct ID3D11ShaderResourceView { // PlaceHolder Structure
};

typedef undefined _Unwind_Reason_Code;

typedef struct ID3D12CommandQueue ID3D12CommandQueue, *PID3D12CommandQueue;

struct ID3D12CommandQueue { // PlaceHolder Structure
};

typedef struct ID3D12Device ID3D12Device, *PID3D12Device;

struct ID3D12Device { // PlaceHolder Structure
};

typedef struct __forced_unwind __forced_unwind, *P__forced_unwind;

struct __forced_unwind { // PlaceHolder Structure
};

typedef struct __class_type_info __class_type_info, *P__class_type_info;

struct __class_type_info { // PlaceHolder Structure
};

typedef struct __foreign_exception __foreign_exception, *P__foreign_exception;

struct __foreign_exception { // PlaceHolder Structure
};

typedef struct __si_class_type_info __si_class_type_info, *P__si_class_type_info;

struct __si_class_type_info { // PlaceHolder Structure
};

typedef struct __dyncast_result __dyncast_result, *P__dyncast_result;

struct __dyncast_result { // PlaceHolder Structure
};

typedef undefined __sub_kind;

typedef struct __upcast_result __upcast_result, *P__upcast_result;

struct __upcast_result { // PlaceHolder Structure
};

typedef struct exception exception, *Pexception;

struct exception { // PlaceHolder Structure
};

typedef struct out_of_range out_of_range, *Pout_of_range;

struct out_of_range { // PlaceHolder Structure
};


// WARNING! conflicting data type names: /Demangler/std/string - /string

typedef struct bad_cast bad_cast, *Pbad_cast;

struct bad_cast { // PlaceHolder Structure
};

typedef undefined initializer_list;

typedef struct logic_error logic_error, *Plogic_error;

struct logic_error { // PlaceHolder Structure
};

typedef struct invalid_argument invalid_argument, *Pinvalid_argument;

struct invalid_argument { // PlaceHolder Structure
};

typedef struct bad_exception bad_exception, *Pbad_exception;

struct bad_exception { // PlaceHolder Structure
};

typedef struct error_condition error_condition, *Perror_condition;

struct error_condition { // PlaceHolder Structure
};

typedef struct bad_typeid bad_typeid, *Pbad_typeid;

struct bad_typeid { // PlaceHolder Structure
};

typedef struct __sso_string __sso_string, *P__sso_string;

struct __sso_string { // PlaceHolder Structure
};

typedef struct allocator allocator, *Pallocator;

struct allocator { // PlaceHolder Structure
};

typedef struct underflow_error underflow_error, *Punderflow_error;

struct underflow_error { // PlaceHolder Structure
};

typedef struct length_error length_error, *Plength_error;

struct length_error { // PlaceHolder Structure
};

typedef struct runtime_error runtime_error, *Pruntime_error;

struct runtime_error { // PlaceHolder Structure
};

typedef struct system_error system_error, *Psystem_error;

struct system_error { // PlaceHolder Structure
};

typedef struct bad_alloc bad_alloc, *Pbad_alloc;

struct bad_alloc { // PlaceHolder Structure
};

typedef struct type_info type_info, *Ptype_info;

struct type_info { // PlaceHolder Structure
};

typedef struct overflow_error overflow_error, *Poverflow_error;

struct overflow_error { // PlaceHolder Structure
};

typedef struct range_error range_error, *Prange_error;

struct range_error { // PlaceHolder Structure
};

typedef struct domain_error domain_error, *Pdomain_error;

struct domain_error { // PlaceHolder Structure
};

typedef struct __cow_string __cow_string, *P__cow_string;

struct __cow_string { // PlaceHolder Structure
};

typedef struct error_code error_code, *Perror_code;

struct error_code { // PlaceHolder Structure
};

typedef undefined forward_iterator_tag;

typedef struct bad_array_new_length bad_array_new_length, *Pbad_array_new_length;

struct bad_array_new_length { // PlaceHolder Structure
};

typedef struct _Hash_node_base _Hash_node_base, *P_Hash_node_base;

struct _Hash_node_base { // PlaceHolder Structure
};

typedef struct _Hash_node _Hash_node, *P_Hash_node;

struct _Hash_node { // PlaceHolder Structure
};

typedef struct error_category error_category, *Perror_category;

struct error_category { // PlaceHolder Structure
};

typedef struct _Alloc_hider _Alloc_hider, *P_Alloc_hider;

struct _Alloc_hider { // PlaceHolder Structure
};


// WARNING! conflicting data type names: /Demangler/std/__cxx11/string - /string

typedef struct generic_error_category generic_error_category, *Pgeneric_error_category;

struct generic_error_category { // PlaceHolder Structure
};

typedef struct system_error_category system_error_category, *Psystem_error_category;

struct system_error_category { // PlaceHolder Structure
};

typedef struct __concurrence_lock_error __concurrence_lock_error, *P__concurrence_lock_error;

struct __concurrence_lock_error { // PlaceHolder Structure
};

typedef undefined __normal_iterator;

typedef struct __concurrence_unlock_error __concurrence_unlock_error, *P__concurrence_unlock_error;

struct __concurrence_unlock_error { // PlaceHolder Structure
};

typedef struct __concurrence_wait_error __concurrence_wait_error, *P__concurrence_wait_error;

struct __concurrence_wait_error { // PlaceHolder Structure
};

typedef struct __concurrence_broadcast_error __concurrence_broadcast_error, *P__concurrence_broadcast_error;

struct __concurrence_broadcast_error { // PlaceHolder Structure
};

typedef undefined GpuTelemetryMark;

typedef struct NetworkReceiver NetworkReceiver, *PNetworkReceiver;

struct NetworkReceiver { // PlaceHolder Structure
};

typedef struct SimulationDispatcher SimulationDispatcher, *PSimulationDispatcher;

struct SimulationDispatcher { // PlaceHolder Structure
};

typedef struct D3D12DepthCapture D3D12DepthCapture, *PD3D12DepthCapture;

struct D3D12DepthCapture { // PlaceHolder Structure
};

typedef struct BeamNGShadowHook BeamNGShadowHook, *PBeamNGShadowHook;

struct BeamNGShadowHook { // PlaceHolder Structure
};

typedef struct ESnap ESnap, *PESnap;

struct ESnap { // PlaceHolder Structure
};

typedef struct Vec3 Vec3, *PVec3;

struct Vec3 { // PlaceHolder Structure
};

typedef struct SmokeRenderer SmokeRenderer, *PSmokeRenderer;

struct SmokeRenderer { // PlaceHolder Structure
};

typedef struct D3D12SimulationDispatcher D3D12SimulationDispatcher, *PD3D12SimulationDispatcher;

struct D3D12SimulationDispatcher { // PlaceHolder Structure
};

typedef struct D3D12SmokeRenderer D3D12SmokeRenderer, *PD3D12SmokeRenderer;

struct D3D12SmokeRenderer { // PlaceHolder Structure
};

typedef struct VSnap VSnap, *PVSnap;

struct VSnap { // PlaceHolder Structure
};

typedef struct GpuProfiler GpuProfiler, *PGpuProfiler;

struct GpuProfiler { // PlaceHolder Structure
};

typedef struct ParsedTelemetry ParsedTelemetry, *PParsedTelemetry;

struct ParsedTelemetry { // PlaceHolder Structure
};

typedef struct D3D11GraphicsStateGuard D3D11GraphicsStateGuard, *PD3D11GraphicsStateGuard;

struct D3D11GraphicsStateGuard { // PlaceHolder Structure
};

typedef struct D3D12ResourceManager D3D12ResourceManager, *PD3D12ResourceManager;

struct D3D12ResourceManager { // PlaceHolder Structure
};

typedef struct D3D11ComputeStateGuard D3D11ComputeStateGuard, *PD3D11ComputeStateGuard;

struct D3D11ComputeStateGuard { // PlaceHolder Structure
};

typedef struct D3D11ResourceManager D3D11ResourceManager, *PD3D11ResourceManager;

struct D3D11ResourceManager { // PlaceHolder Structure
};

typedef struct swapchain swapchain, *Pswapchain;

struct swapchain { // PlaceHolder Structure
};

typedef struct command_list command_list, *Pcommand_list;

struct command_list { // PlaceHolder Structure
};

typedef struct resource_view_desc resource_view_desc, *Presource_view_desc;

struct resource_view_desc { // PlaceHolder Structure
};

typedef struct subresource_data subresource_data, *Psubresource_data;

struct subresource_data { // PlaceHolder Structure
};

typedef struct rect rect, *Prect;

struct rect { // PlaceHolder Structure
};

typedef undefined resource_view;

typedef undefined resource_usage;

typedef struct resource_desc resource_desc, *Presource_desc;

struct resource_desc { // PlaceHolder Structure
};

typedef struct command_queue command_queue, *Pcommand_queue;

struct command_queue { // PlaceHolder Structure
};

typedef undefined pipeline_stage;

typedef undefined pipeline_layout;

typedef undefined resource;

typedef struct pipeline_subobject pipeline_subobject, *Ppipeline_subobject;

struct pipeline_subobject { // PlaceHolder Structure
};

typedef undefined pipeline;

typedef struct device device, *Pdevice;

struct device { // PlaceHolder Structure
};


// WARNING! conflicting data type names: /crtdefs.h/lconv - /DWARF/locale.h/lconv




WINBOOL _CRT_INIT(HANDLE hDllHandle,DWORD dwReason,LPVOID lpreserved);
WINBOOL DllMainCRTStartup(HANDLE hDllHandle,DWORD dwReason,LPVOID lpreserved);
int atexit(_PVFV func);
void __gcc_register_frame(void);
void __gcc_deregister_frame(void);
void on_bind_d3d12_pipeline(longlong *param_1,ulonglong param_2,longlong param_3);
void on_destroy_d3d12_pipeline(longlong *param_1,ulonglong param_2,longlong param_3);
void on_init_d3d12_pipeline(longlong *param_1,undefined8 param_2,longlong param_3,int *param_4,ulonglong param_5);
void on_reset_d3d12_command_list(longlong *param_1,undefined8 param_2,longlong param_3);
void on_destroy_resource_view(longlong *param_1,ulonglong param_2,longlong param_3);
void on_init_resource_view(longlong *param_1,longlong param_2,ulonglong param_3,undefined8 param_4,ulonglong param_5);
void on_destroy_resource(longlong *param_1,ulonglong param_2,longlong param_3);
void on_init_resource(longlong *param_1,longlong *param_2,longlong param_3,undefined8 param_4,ulonglong param_5);
void on_destroy_swapchain(undefined8 param_1,undefined8 param_2,longlong param_3);
void on_destroy_device(longlong *param_1,undefined8 param_2,longlong param_3);
ulonglong SelectSimulationStep(longlong param_1,ulonglong param_2);
void RenderSmokeCore(longlong *param_1,longlong *param_2,longlong param_3,longlong *param_4,uint param_5,uint param_6);
void TryRenderBeforeBeamNGUi(undefined8 *param_1,int param_2);
undefined8 on_draw_indexed(longlong *param_1,uint param_2,longlong param_3);
undefined8 on_draw(longlong *param_1,uint param_2,longlong param_3);
void on_present(char *param_1,float *param_2,float *param_3,undefined8 param_4);
undefined8 DllMain(HMODULE param_1,char *param_2,longlong param_3,undefined8 param_4);
bool realsmoke::(anonymous_namespace)::bounded(float *param_1,float param_2);
undefined8 realsmoke::(anonymous_namespace)::parseNumber(longlong *param_1,ulonglong *param_2,ulonglong param_3,float *param_4);
undefined8 realsmoke::(anonymous_namespace)::optionalVec(longlong *param_1,char *param_2,ulonglong param_3,ulonglong param_4,ulonglong *param_5,char param_6);
longlong * std::operator+(longlong *param_1,undefined1 *param_2,ulonglong param_3,char *param_4);
int realsmoke::(anonymous_namespace)::optionalFloat(longlong *param_1,char *param_2,ulonglong param_3,ulonglong param_4,float *param_5);
int realsmoke::(anonymous_namespace)::optionalFloat(longlong *param_1,char *param_2,ulonglong param_3,float *param_4);
uint realsmoke::(anonymous_namespace)::messageTypeIs(longlong *param_1,char *param_2);
undefined8 realsmoke::(anonymous_namespace)::optionalUnsigned(longlong *param_1,char *param_2,ulonglong param_3,undefined8 *param_4);
longlong * std::operator+(longlong *param_1,longlong *param_2,undefined1 *param_3,ulonglong param_4);
ulonglong realsmoke::(anonymous_namespace)::parseEnvironment(longlong *param_1,undefined8 *param_2,float *param_3);
void __tcf_ZZN9realsmoke12_GLOBAL__N_1L16parseEnvironmentERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKNS_5ESnapERS9_E15replayWarmupKey(void);
void __tcf_ZZN9realsmoke12_GLOBAL__N_1L16parseEnvironmentERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKNS_5ESnapERS9_E12realDeltaKey(void);
void __tcf_ZZN9realsmoke12_GLOBAL__N_1L16parseEnvironmentERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKNS_5ESnapERS9_E18simulationDeltaKey(void);
void __tcf_ZZN9realsmoke12_GLOBAL__N_1L16parseEnvironmentERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKNS_5ESnapERS9_E16resetSequenceKey(void);
void __tcf_ZZN9realsmoke12_GLOBAL__N_1L16parseEnvironmentERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKNS_5ESnapERS9_E14renderFrameKey(void);
void __tcf_ZZN9realsmoke12_GLOBAL__N_1L16parseEnvironmentERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKNS_5ESnapERS9_E5quote(void);
undefined8 realsmoke::(anonymous_namespace)::parseVehicle(longlong *param_1,float *param_2);
ulonglong realsmoke::ParseTelemetry(longlong *param_1,undefined8 *param_2,undefined4 *param_3);
void __thiscall realsmoke::NetworkReceiver::NetworkReceiver(NetworkReceiver *this);
undefined1 *realsmoke::NetworkReceiver::Instance(undefined8 param_1,undefined8 param_2,longlong param_3);
void __thiscall realsmoke::NetworkReceiver::InitSocket(NetworkReceiver *this);
void __thiscall realsmoke::NetworkReceiver::EnsureStarted(NetworkReceiver *this);
void __thiscall realsmoke::NetworkReceiver::Poll(NetworkReceiver *this);
undefined8 realsmoke::NetworkReceiver::ThreadProc(NetworkReceiver *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void __thiscall realsmoke::NetworkReceiver::EnsureStarted(NetworkReceiver *this);
void __thiscall realsmoke::NetworkReceiver::Stop(NetworkReceiver *this);
void __thiscall realsmoke::NetworkReceiver::~NetworkReceiver(NetworkReceiver *this);
void __tcf_ZZN9realsmoke15NetworkReceiver8InstanceEvE10s_instance(void);
void __thiscall realsmoke::NetworkReceiver::GetSnapshot(NetworkReceiver *this,void *param_1,undefined8 *param_2,undefined8 *param_3);
NetworkReceiver __thiscall realsmoke::NetworkReceiver::HasActiveVehicle(NetworkReceiver *this);
undefined8 __thiscall realsmoke::NetworkReceiver::GetLastVehiclePacketMs(NetworkReceiver *this);
void realsmoke::EnsureNetworkReceiver(undefined8 param_1,undefined8 param_2,longlong param_3);
void realsmoke::CleanupNetwork(undefined8 param_1,undefined8 param_2,longlong param_3);
void realsmoke::GetTelemetrySnapshot(void *param_1,undefined8 *param_2,undefined8 *param_3);
void __thiscall realsmoke::D3D11ResourceManager::D3D11ResourceManager(D3D11ResourceManager *this);
undefined1 *realsmoke::D3D11ResourceManager::Instance(undefined8 param_1,undefined8 param_2,longlong param_3);
void __thiscall realsmoke::D3D11ResourceManager::Cleanup(D3D11ResourceManager *this);
void __thiscall realsmoke::D3D11ResourceManager::~D3D11ResourceManager(D3D11ResourceManager *this);
void __tcf_ZZN9realsmoke20D3D11ResourceManager8InstanceEvE10s_instance(void);
undefined8 __thiscall realsmoke::D3D11ResourceManager::Init(D3D11ResourceManager *this,longlong *param_1);
ulonglong __thiscall realsmoke::D3D11ResourceManager::EnsureGrid(D3D11ResourceManager *this,float param_1,float param_2);
ulonglong __thiscall realsmoke::D3D11ResourceManager::Init(D3D11ResourceManager *this,longlong *param_1);
ulonglong realsmoke::InitD3D(longlong *param_1,undefined8 param_2,longlong param_3);
void realsmoke::CleanupD3D(undefined8 param_1,undefined8 param_2,longlong param_3);
void __thiscall realsmoke::D3D12ResourceManager::D3D12ResourceManager(D3D12ResourceManager *this);
undefined1 *realsmoke::D3D12ResourceManager::Instance(undefined8 param_1,undefined8 param_2,longlong param_3);
void __thiscall realsmoke::D3D12ResourceManager::ReleaseSimulationTextures(D3D12ResourceManager *this);
longlong __thiscall realsmoke::D3D12ResourceManager::GetCpuDescriptor(D3D12ResourceManager *this,int param_1);
longlong __thiscall realsmoke::D3D12ResourceManager::GetGpuDescriptor(D3D12ResourceManager *this,int param_1);
longlong __thiscall realsmoke::D3D12ResourceManager::GetClearCpuDescriptor(D3D12ResourceManager *this,int param_1);
undefined8 __thiscall realsmoke::D3D12ResourceManager::CreateHeaps(D3D12ResourceManager *this);
bool __thiscall realsmoke::D3D12ResourceManager::CreateRootSignatures(D3D12ResourceManager *this);
undefined8 __thiscall realsmoke::D3D12ResourceManager::CreateConstantBuffers(D3D12ResourceManager *this);
undefined8 __thiscall realsmoke::D3D12ResourceManager::CreateSimulationTextures(D3D12ResourceManager *this);
undefined8 __thiscall realsmoke::D3D12ResourceManager::BeginCommandList(D3D12ResourceManager *this);
undefined8 __thiscall realsmoke::D3D12ResourceManager::ExecuteCommandList(D3D12ResourceManager *this,undefined8 param_1,undefined8 param_2,undefined8 param_3);
void __thiscall realsmoke::D3D12ResourceManager::DiscardCommandList(D3D12ResourceManager *this);
void __thiscall realsmoke::D3D12ResourceManager::WaitForGpuIdle(D3D12ResourceManager *this);
void __thiscall realsmoke::D3D12ResourceManager::Cleanup(D3D12ResourceManager *this);
void __thiscall realsmoke::D3D12ResourceManager::~D3D12ResourceManager(D3D12ResourceManager *this);
void __tcf_ZZN9realsmoke20D3D12ResourceManager8InstanceEvE10s_instance(void);
ulonglong __thiscall realsmoke::D3D12ResourceManager::EnsureGrid(D3D12ResourceManager *this,float param_1,float param_2);
undefined8 __thiscall realsmoke::D3D12ResourceManager::EnsurePipelines(D3D12ResourceManager *this,uint param_1);
ulonglong __thiscall realsmoke::D3D12ResourceManager::Init(D3D12ResourceManager *this,longlong *param_1,longlong param_2);
D3D12ResourceManager __thiscall realsmoke::D3D12ResourceManager::TryReadActiveBounds(D3D12ResourceManager *this,undefined8 param_2);
void __thiscall realsmoke::GpuProfiler::GpuProfiler(GpuProfiler *this);
undefined1 *realsmoke::GpuProfiler::Instance(undefined8 param_1,undefined8 param_2,longlong param_3);
void __thiscall realsmoke::GpuProfiler::ResetSession(GpuProfiler *this);
void __thiscall realsmoke::GpuProfiler::Cleanup(GpuProfiler *this);
void __thiscall realsmoke::GpuProfiler::~GpuProfiler(GpuProfiler *this);
void __tcf_ZZN9realsmoke11GpuProfiler8InstanceEvE10s_instance(void);
undefined8 __thiscall realsmoke::GpuProfiler::Init(GpuProfiler *this,longlong *param_1,undefined8 param_2,undefined8 param_3);
undefined8 __thiscall realsmoke::GpuProfiler::Init(GpuProfiler *this,longlong *param_1,undefined8 param_2,undefined8 param_3);
void realsmoke::GpuProfiler::LogReport(longlong param_1,undefined8 param_2,undefined8 param_3);
void __thiscall realsmoke::GpuProfiler::Collect(GpuProfiler *this,longlong *param_1);
void __thiscall realsmoke::GpuProfiler::Collect(GpuProfiler *this,longlong *param_1);
void __thiscall realsmoke::GpuProfiler::BeginFrame(GpuProfiler *this,longlong *param_1,longlong param_2,float param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9);
void __thiscall realsmoke::GpuProfiler::Mark(GpuProfiler *this,longlong *param_1,uint param_2);
void __thiscall realsmoke::GpuProfiler::EndFrame(GpuProfiler *this,longlong *param_1);
void __thiscall realsmoke::GpuProfiler::CollectOccupancy(GpuProfiler *this,longlong *param_1);
void __thiscall realsmoke::GpuProfiler::SubmitOccupancy(GpuProfiler *this,longlong *param_1,longlong param_2,longlong param_3,longlong param_4,int param_5,int param_6,int param_7,longlong param_8);
undefined8 realsmoke::InitGpuTelemetry(longlong *param_1,undefined8 param_2,longlong param_3,undefined8 param_4);
void realsmoke::CleanupGpuTelemetry(undefined8 param_1,undefined8 param_2,longlong param_3);
void realsmoke::CollectGpuTelemetry(longlong *param_1,undefined8 param_2,longlong param_3);
void realsmoke::BeginGpuTelemetryFrame(longlong *param_1,longlong param_2,float param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9);
void realsmoke::MarkGpuTelemetry(longlong *param_1,ulonglong param_2,longlong param_3);
void realsmoke::EndGpuTelemetryFrame(longlong *param_1,undefined8 param_2,longlong param_3);
void realsmoke::CollectOccupancyTelemetry(longlong *param_1,undefined8 param_2,longlong param_3);
void realsmoke::SubmitOccupancyTelemetry(longlong *param_1,longlong param_2,longlong param_3,longlong param_4,int param_5,int param_6,int param_7,longlong param_8);
void realsmoke::ResetGpuTelemetrySession(undefined8 param_1,undefined8 param_2,longlong param_3);
void realsmoke::BeamNGShadowHook::CaptureColor(longlong param_1,longlong *param_2,longlong *param_3,longlong *param_4);
undefined1 *realsmoke::BeamNGShadowHook::Instance(undefined8 param_1,undefined8 param_2,longlong param_3);
void __thiscall realsmoke::BeamNGShadowHook::BeamNGShadowHook(BeamNGShadowHook *this);
void __thiscall realsmoke::BeamNGShadowHook::BeginFrame(BeamNGShadowHook *this,undefined4 param_1,undefined4 param_2);
void __thiscall realsmoke::BeamNGShadowHook::OnDestroySwapchain(BeamNGShadowHook *this);
void __thiscall realsmoke::BeamNGShadowHook::~BeamNGShadowHook(BeamNGShadowHook *this);
void __tcf_ZZN9realsmoke16BeamNGShadowHook8InstanceEvE10s_instance(void);
void __thiscall realsmoke::BeamNGShadowHook::OnDepthBind(BeamNGShadowHook *this,undefined8 param_2_00,int param_2,longlong *param_3,longlong *param_4);
undefined8 realsmoke::BeamNGShadowHook::GetTexture2DDesc(longlong *param_1,undefined8 param_2);
undefined4 realsmoke::BeamNGShadowHook::CopyNativeConstantBuffer(longlong *param_1,longlong *param_2,longlong *param_3,uint param_4,longlong *param_5,uint *param_6);
bool __thiscall realsmoke::BeamNGShadowHook::CaptureDepth(BeamNGShadowHook *this,longlong *param_1,longlong *param_2,longlong *param_3,uint param_4,uint param_5);
void __thiscall realsmoke::BeamNGShadowHook::CaptureColor(BeamNGShadowHook *this,longlong *param_1,longlong *param_2,longlong *param_3,int param_4,int param_5);
void realsmoke::BeamNGShadowHook::TryLogShadowConstants(void);
void realsmoke::BeamNGShadowHook::TryLogDepthReadback(void);
void realsmoke::BeamNGShadowHook::TryLogSunDirection(void);
void realsmoke::on_depth_bind(longlong *param_1,longlong param_2,ulonglong *param_3,longlong *param_4);
void realsmoke::on_destroy_swapchain(undefined8 param_1,undefined8 param_2,longlong param_3);
void realsmoke::CaptureSceneDepth(longlong *param_1,longlong *param_2,longlong *param_3,uint param_4,uint param_5);
void realsmoke::CaptureSceneColor(longlong *param_1,longlong *param_2,longlong *param_3,int param_4,int param_5);
undefined8 __thiscall realsmoke::BeamNGShadowHook::OnDispatch(BeamNGShadowHook *this,undefined8 *param_1,longlong param_3_00,uint param_3,int param_4);
undefined8 realsmoke::on_dispatch(undefined8 *param_1,ulonglong param_2,longlong param_3,int param_4);
undefined1 *realsmoke::D3D12DepthCapture::Instance(undefined8 param_1,undefined8 param_2,longlong param_3);
void __thiscall realsmoke::D3D12DepthCapture::OnInitResourceView(D3D12DepthCapture *this,longlong *param_1,longlong param_2,undefined8 param_3,ulonglong param_4);
undefined4 __thiscall realsmoke::D3D12DepthCapture::IsMainDepthLocked(D3D12DepthCapture *this,ulonglong param_1);
void __thiscall realsmoke::D3D12DepthCapture::OnResetCommandList(D3D12DepthCapture *this,ulonglong param_1);
void __thiscall realsmoke::D3D12DepthCapture::OnDestroyPipeline(D3D12DepthCapture *this,longlong *param_1,ulonglong param_2);
uint __thiscall realsmoke::D3D12DepthCapture::SnapshotSceneColor(D3D12DepthCapture *this,longlong *param_1,longlong *param_2);
undefined8 realsmoke::D3D12DepthCapture::GetCopyFormats(undefined4 param_1,undefined4 *param_2,undefined4 *param_3);
uint __thiscall realsmoke::D3D12DepthCapture::SnapshotDepth(D3D12DepthCapture *this,longlong *param_1,longlong *param_2,undefined8 param_3);
void __thiscall realsmoke::D3D12DepthCapture::BeginFrame(D3D12DepthCapture *this,undefined4 param_1,undefined4 param_2);
void __thiscall realsmoke::D3D12DepthCapture::Cleanup(D3D12DepthCapture *this);
void __thiscall realsmoke::D3D12DepthCapture::~D3D12DepthCapture(D3D12DepthCapture *this);
void __tcf_ZZN9realsmoke17D3D12DepthCapture8InstanceEvE8instance(void);
undefined8 __thiscall realsmoke::D3D12DepthCapture::GetDepthTexture(D3D12DepthCapture *this);
undefined4 __thiscall realsmoke::D3D12DepthCapture::GetDepthSrvFormat(D3D12DepthCapture *this);
undefined8 __thiscall realsmoke::D3D12DepthCapture::GetSceneBeforeUiTexture(D3D12DepthCapture *this);
undefined4 __thiscall realsmoke::D3D12DepthCapture::GetSceneBeforeUiFormat(D3D12DepthCapture *this);
void __thiscall realsmoke::D3D12DepthCapture::OnInitResource(D3D12DepthCapture *this,longlong *param_1,longlong *param_2,ulonglong param_3);
void __thiscall realsmoke::D3D12DepthCapture::TryCapturePreUi(D3D12DepthCapture *this,longlong *param_1,uint param_2,int param_3);
void __thiscall realsmoke::D3D12DepthCapture::OnInitPipeline(D3D12DepthCapture *this,longlong *param_1,uint param_2,int *param_3,ulonglong param_4);
void __thiscall realsmoke::D3D12DepthCapture::OnDestroyResource(D3D12DepthCapture *this,longlong *param_1,ulonglong param_2);
void __thiscall realsmoke::D3D12DepthCapture::OnDestroyResourceView(D3D12DepthCapture *this,longlong *param_1,ulonglong param_2);
void __thiscall realsmoke::D3D12DepthCapture::OnBindRenderTargets(D3D12DepthCapture *this,longlong *param_1,int param_2,ulonglong *param_3,ulonglong param_4);
void __thiscall realsmoke::D3D12DepthCapture::OnBindPipeline(D3D12DepthCapture *this,longlong *param_1,ulonglong param_2,longlong param_3);
void __tcf_ZZN9realsmoke20SimulationDispatcher8InstanceEvE10s_instance(undefined8 param_1,undefined8 param_2,longlong param_3);
undefined1 *realsmoke::SimulationDispatcher::Instance(undefined8 param_1,undefined8 param_2,longlong param_3);
void __thiscall realsmoke::SimulationDispatcher::SimulationDispatcher(SimulationDispatcher *this);
void __thiscall realsmoke::SimulationDispatcher::~SimulationDispatcher(SimulationDispatcher *this,undefined8 param_1,longlong param_2);
void __thiscall realsmoke::SimulationDispatcher::Reset(SimulationDispatcher *this,undefined8 param_1,longlong param_2);
char __thiscall realsmoke::SimulationDispatcher::ResetFluid(SimulationDispatcher *this,longlong *param_1,undefined1 *param_2,undefined8 param_3);
void __thiscall realsmoke::SimulationDispatcher::BuildDensityBricks(SimulationDispatcher *this,longlong *param_1,longlong param_2);
void realsmoke::BuildDensityBricks(longlong *param_1,longlong param_2,longlong param_3);
SimulationDispatcher __thiscall realsmoke::SimulationDispatcher::StepSimulation(SimulationDispatcher *this,longlong param_2,longlong *param_3,float *param_4,longlong param_5,float param_6,longlong param_7,undefined4 param_8,undefined4 param_9);
void __tcf_ZZN9realsmoke25D3D12SimulationDispatcher8InstanceEvE10s_instance(undefined8 param_1,undefined8 param_2,longlong param_3);
undefined1 *realsmoke::D3D12SimulationDispatcher::Instance(undefined8 param_1,undefined8 param_2,longlong param_3);
void __thiscall realsmoke::D3D12SimulationDispatcher::D3D12SimulationDispatcher(D3D12SimulationDispatcher *this);
void __thiscall realsmoke::D3D12SimulationDispatcher::~D3D12SimulationDispatcher(D3D12SimulationDispatcher *this,undefined8 param_1,longlong param_2);
void __thiscall realsmoke::D3D12SimulationDispatcher::Reset(D3D12SimulationDispatcher *this,undefined8 param_1,longlong param_2);
D3D12ResourceManager __thiscall realsmoke::D3D12SimulationDispatcher::ResetFluid(D3D12SimulationDispatcher *this,longlong *param_2,longlong *param_3);
void __thiscall realsmoke::D3D12SimulationDispatcher::BuildDensityBricks(D3D12SimulationDispatcher *this,longlong *param_1,longlong *param_2,longlong param_3);
D3D12ResourceManager realsmoke::D3D12SimulationDispatcher::StepSimulation(D3D12SimulationDispatcher *param_1,longlong *param_2,longlong *param_3,float *param_4,longlong param_5,float param_6,longlong param_7);
void __tcf_ZZN9realsmoke13SmokeRenderer8InstanceEvE10s_instance(void);
undefined1 *realsmoke::SmokeRenderer::Instance(undefined8 param_1,undefined8 param_2,longlong param_3);
void __thiscall realsmoke::SmokeRenderer::SmokeRenderer(SmokeRenderer *this);
void __thiscall realsmoke::SmokeRenderer::~SmokeRenderer(void);
ulonglong __thiscall realsmoke::SmokeRenderer::Render(SmokeRenderer *this,longlong *param_1,longlong *param_2,longlong param_3,longlong *param_4,longlong *param_5,longlong param_6,undefined4 *param_7,undefined4 *param_8,undefined4 param_9,uint param_10,uint param_11,longlong param_12);
void __tcf_ZZN9realsmoke18D3D12SmokeRenderer8InstanceEvE10s_instance(void);
undefined8 *realsmoke::D3D12SmokeRenderer::Instance(undefined8 param_1,undefined8 param_2,longlong param_3);
void __thiscall realsmoke::D3D12SmokeRenderer::D3D12SmokeRenderer(D3D12SmokeRenderer *this);
void __thiscall realsmoke::D3D12SmokeRenderer::~D3D12SmokeRenderer(D3D12SmokeRenderer *this);
void __thiscall realsmoke::D3D12SmokeRenderer::Cleanup(D3D12SmokeRenderer *this);
char realsmoke::D3D12SmokeRenderer::Render(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4,undefined8 param_5,longlong param_6,int param_7,longlong param_8,int param_9,longlong param_10,undefined4 *param_11,undefined4 *param_12,undefined4 param_13,uint param_14,uint param_15);
SOCKET __stdcall socket(int af,int type,int protocol);
int __stdcall setsockopt(SOCKET s,int level,int optname,char *optval,int optlen);
int __stdcall recvfrom(SOCKET s,char *buf,int len,int flags,sockaddr *from,int *fromlen);
int __stdcall ioctlsocket(SOCKET s,long cmd,u_long *argp);
u_short __stdcall htons(u_short hostshort);
u_long __stdcall htonl(u_long hostlong);
int __stdcall closesocket(SOCKET s);
int __stdcall bind(SOCKET s,sockaddr *addr,int namelen);
int __stdcall WSAStartup(WORD wVersionRequired,LPWSADATA lpWSAData);
int __stdcall WSAGetLastError(void);
int __stdcall WSACleanup(void);
void D3D12SerializeRootSignature(void);
uint * d_make_comp(longlong param_1,uint param_2,longlong param_3,longlong param_4);
undefined4 * d_make_name(longlong param_1,longlong param_2,int param_3);
int d_number(longlong param_1);
undefined8 d_call_offset(longlong param_1,int param_2);
uint * d_ref_qualifier(longlong param_1,uint *param_2);
undefined8 d_discriminator(longlong param_1);
void d_count_templates_scopes(longlong param_1,uint *param_2);
int d_pack_length(int *param_1);
void d_growable_string_callback_adapter(void *param_1,size_t param_2,longlong *param_3);
bool next_is_type_qual.isra.0(byte *param_1);
void d_append_char(longlong param_1,undefined1 param_2);
int * d_lookup_template_argument(longlong param_1,longlong param_2);
void d_append_string(char *param_1,char *param_2);
int * d_find_pack(longlong param_1,uint *param_2);
undefined4 * d_template_param(longlong param_1);
void d_append_num(char *param_1,uint param_2);
void d_print_lambda_parm_name(char *param_1,int param_2,uint param_3);
undefined4 * d_source_name(longlong param_1);
undefined8 d_maybe_module_name(longlong param_1,longlong *param_2);
uint * d_substitution(longlong param_1,uint param_2);
uint * d_type(longlong param_1);
longlong d_parmlist(longlong param_1);
uint * d_bare_function_type(longlong param_1,int param_2);
uint * d_function_type(longlong param_1);
uint * d_operator_name(longlong param_1);
uint * d_template_parm(longlong param_1,undefined4 *param_2);
uint * d_template_head(longlong param_1,undefined4 *param_2);
uint * d_unqualified_name(longlong param_1,longlong param_2,longlong param_3);
uint * d_expr_primary(longlong param_1);
uint * d_template_arg(longlong param_1);
uint * d_template_args_1(longlong param_1);
uint * d_prefix(longlong param_1,int param_2);
uint * d_expression_1(longlong param_1);
uint * d_cv_qualifiers(longlong param_1,uint *param_2,uint param_3);
uint * d_exprlist(longlong param_1,char param_2);
uint * d_special_name(longlong param_1);
uint * d_name(longlong param_1,int param_2);
uint * d_encoding.part.0(longlong param_1,int param_2);
void d_print_comp_inner(char *param_1,undefined8 param_2,uint *param_3);
void d_print_comp(char *param_1,undefined8 param_2,uint *param_3);
void d_print_mod(undefined1 *param_1,undefined8 param_2,uint *param_3);
void d_print_function_type(char *param_1,undefined8 param_2,longlong param_3,longlong *param_4);
void d_print_mod_list(char *param_1,undefined8 param_2,undefined8 *param_3,int param_4);
void d_print_array_type(undefined2 *param_1,undefined8 param_2,longlong param_3,longlong *param_4);
void d_print_expr_op(undefined1 *param_1,undefined8 param_2,int *param_3);
bool d_demangle_callback.constprop.0(char *param_1,undefined *param_2,undefined8 param_3);
void d_print_subexpr(undefined1 *param_1,undefined8 param_2,uint *param_3);
undefined8 d_maybe_print_fold_expression(undefined1 *param_1,undefined8 param_2,longlong param_3);
undefined8 d_maybe_print_designated_init(undefined1 *param_1,undefined8 param_2,uint *param_3);
char * __cxa_demangle(char *param_1,char *param_2,ulonglong *param_3,undefined4 *param_4);
uint __gcclibcxx_demangle_callback(char *param_1,undefined *param_2,undefined8 param_3);
void __do_global_dtors(void);
void __do_global_ctors(void);
void __main(void);
void __dyn_tls_dtor(HANDLE hDllHandle,DWORD dwReason,LPVOID lpreserved);
void __dyn_tls_init(HANDLE hDllHandle,DWORD dwReason,LPVOID lpreserved);
int __tlregdtor(_PVFV func);
void __report_error(char *msg,...);
void mark_section_writable(LPVOID addr);
void _pei386_runtime_relocator(void);
void __mingwthr_run_key_dtors(void);
int ___w64_mingwthr_add_key_dtor(DWORD key,_func_void_void_ptr *dtor);
int ___w64_mingwthr_remove_key_dtor(DWORD key);
WINBOOL __mingw_TLScallback(HANDLE hDllHandle,DWORD reason,LPVOID reserved);
void _fpreset(void);
WINBOOL _ValidateImageBase(PBYTE pImageBase);
PIMAGE_SECTION_HEADER _FindPESection(PBYTE pImageBase,DWORD_PTR rva);
PIMAGE_SECTION_HEADER _FindPESectionByName(char *pName);
PIMAGE_SECTION_HEADER __mingw_GetSectionForAddress(LPVOID p);
int __mingw_GetSectionCount(void);
PIMAGE_SECTION_HEADER _FindPESectionExec(size_t eNo);
PBYTE _GetPEImageBase(void);
WINBOOL _IsNonwritableInCurrentImage(PBYTE pTarget);
char * __mingw_enum_import_library_names(int i);
ulonglong ___chkstk_ms(void);
void .text(undefined8 *param_1);
undefined8 _Unwind_GetGR(longlong param_1,uint param_2);
void _Unwind_SetGR(longlong param_1,uint param_2,undefined8 param_3);
undefined8 _Unwind_GetCFA(undefined8 *param_1);
undefined8 _Unwind_GetIP(longlong param_1);
undefined8 _Unwind_GetIPInfo(longlong param_1,undefined4 *param_2);
void _Unwind_SetIP(longlong param_1,undefined8 param_2);
undefined8 _Unwind_GetLanguageSpecificData(longlong param_1);
longlong _Unwind_GetRegionStart(longlong param_1);
longlong _Unwind_FindEnclosingFunction(DWORD64 param_1);
undefined8 _Unwind_GetDataRelBase(void);
undefined8 _Unwind_GetTextRelBase(longlong param_1);
undefined8 _GCC_specific_handler(PEXCEPTION_RECORD param_1,PVOID param_2,PCONTEXT param_3,ULONG_PTR *param_4,undefined *param_5);
undefined8 _Unwind_RaiseException(ULONG_PTR param_1);
void _Unwind_Resume(PVOID param_1);
undefined8 _Unwind_Resume_or_Rethrow(undefined8 *param_1);
undefined8 _Unwind_ForcedUnwind(undefined8 *param_1,undefined8 param_2,undefined8 param_3);
void _Unwind_DeleteException(longlong param_1);
undefined8 _Unwind_Backtrace(undefined *param_1,undefined8 param_2);
float __strtof(char *s,char **sp);
void __chk_fail(void);
void __stack_chk_fail(void);
int __mingw_fprintf(FILE *stream,char *fmt,...);
char * __pformat_cvt(int32_t mode,long double *val,int32_t nd,int32_t *dp,int32_t *sign);
void __pformat_putc(int32_t c,__pformat_t *stream);
void __pformat_wputchars(wchar_t *s,int32_t count,__pformat_t *stream);
void __pformat_putchars(char *s,int32_t count,__pformat_t *stream);
void __pformat_puts(char *s,__pformat_t *stream);
void __pformat_emit_inf_or_nan(int32_t sign,char *value,__pformat_t *stream);
void __pformat_int(__pformat_intarg_t *value,__pformat_t *stream);
void __pformat_xint(int32_t fmt,__pformat_intarg_t *value,__pformat_t *stream);
void __pformat_emit_radix_point(__pformat_t *stream);
void __pformat_emit_float(int32_t sign,char *value,int32_t len,__pformat_t *stream);
void __pformat_emit_efloat(int32_t sign,char *value,int32_t e,__pformat_t *stream);
void __pformat_efloat(long double *x,__pformat_t *stream);
void __pformat_float(long double *x,__pformat_t *stream);
void __pformat_gfloat(long double *x,__pformat_t *stream);
void __pformat_emit_xfloat(__pformat_fpreg_t *value,__pformat_t *stream);
int32_t __mingw_pformat(int32_t flags,void *dest,int32_t max,char *fmt,va_list argv);
int __mingw_snprintf(char *buf,size_t length,char *fmt,...);
int __mingw_vfprintf(FILE *stream,char *fmt,va_list argv);
int __mingw_vsnprintf(char *buf,size_t length,char *fmt,va_list argv);
char * __rv_alloc_D2A(int i);
char * __nrv_alloc_D2A(char *s,char **rve,int n);
void __freedtoa(char *s);
int __quorem_D2A(__Bigint *b,__Bigint *S);
char * __gdtoa(FPI *fpi,int be,ULong *bits,int *kindp,int mode,int ndigits,int *decpt,char **rve);
void __rshift_D2A(__Bigint *b,int k);
int __trailz_D2A(__Bigint *b);
void dtoa_lock(uint n);
void dtoa_lock_cleanup(void);
__Bigint * __Balloc_D2A(int k);
void __Bfree_D2A(__Bigint *v);
__Bigint * __multadd_D2A(__Bigint *b,int m,int a);
__Bigint * __i2b_D2A(int i);
__Bigint * __mult_D2A(__Bigint *a,__Bigint *b);
__Bigint * __pow5mult_D2A(__Bigint *b,int k);
__Bigint * __lshift_D2A(__Bigint *b,int k);
int __cmp_D2A(__Bigint *a,__Bigint *b);
__Bigint * __diff_D2A(__Bigint *a,__Bigint *b);
double __b2d_D2A(__Bigint *a,int *e);
__Bigint * __d2b_D2A(double dd,int *e,int *bits);
char * __strcp_D2A(char *a,char *b);
__Bigint * __increment_D2A(__Bigint *b);
int rvOK(dbl_union *d,FPI *fpi,long *expo,ULong *bits,int exact,int rd,int *irv);
void __decrement_D2A(__Bigint *b);
__Bigint * __set_ones_D2A(__Bigint *b,int n);
int __strtodg(char *s00,char **se,FPI *fpi,long *expo,ULong *bits);
__Bigint * __sum_D2A(__Bigint *a,__Bigint *b);
int __gethex_D2A(char **sp,FPI *fpi,long *expo,__Bigint **bp,int sign);
int __hexnan_D2A(char **sp,FPI *fpi,ULong *x0);
__Bigint * __s2b_D2A(char *s,int nd0,int nd,ULong y9,int dplen);
double __ratio_D2A(__Bigint *a,__Bigint *b);
int __match_D2A(char **sp,char *t);
void __copybits_D2A(ULong *c,int n,__Bigint *b);
ULong __any_on_D2A(__Bigint *b,int k);
int vfprintf(FILE.conflict *_File,char *_Format,va_list _ArgList);
int fprintf(FILE.conflict *_File,char *_Format,...);
ulonglong * __local_stdio_printf_options(void);
void _amsg_exit(int ret);
int __cdecl isspace(int _C);
void * __cdecl memset(void *_Dst,int _Val,size_t _Size);
int __cdecl strcmp(char *_Str1,char *_Str2);
size_t __cdecl strlen(char *_Str);
int __cdecl strncmp(char *_Str1,char *_Str2,size_t _MaxCount);
size_t __cdecl strnlen(char *_Str,size_t _MaxCount);
size_t __cdecl wcslen(wchar_t *_Str);
size_t __cdecl wcsnlen(wchar_t *_Src,size_t _MaxCount);
void __acrt_iob_func(void);
void __stdio_common_vfprintf(void);
int __cdecl _read(int _FileHandle,void *_DstBuf,uint _MaxCharCount);
int __cdecl write(int _FileHandle,void *_Buf,uint _MaxCharCount);
int __cdecl fclose(FILE *_File);
FILE * __cdecl fopen(char *_Filename,char *_Mode);
int __cdecl fputc(int _Ch,FILE *_File);
int __cdecl fputs(char *_Str,FILE *_File);
size_t __cdecl fwrite(void *_Str,size_t _Size,size_t _Count,FILE *_File);
int * __cdecl _errno(void);
void _execute_onexit_table(void);
void __cdecl _exit(int _Code);
void _initialize_onexit_table(void);
void _initterm(void);
void _initterm_e(void);
void _register_onexit_function(void);
void __cdecl abort(void);
char * __cdecl strerror(int param_1);
void * __cdecl memchr(void *_Buf,int _Val,size_t _MaxCount);
int __cdecl memcmp(void *_Buf1,void *_Buf2,size_t _Size);
void * __cdecl memcpy(void *_Dst,void *_Src,size_t _Size);
void * __cdecl memmove(void *_Dst,void *_Src,size_t _Size);
char * __cdecl strchr(char *_Str,int _Val);
float __cdecl expf(float _X);
lconv * __cdecl localeconv(void);
void * __cdecl calloc(size_t _Count,size_t _Size);
void __cdecl free(void *_Memory);
void * __cdecl malloc(size_t _Size);
void * __cdecl realloc(void *_Memory,size_t _NewSize);
void __cdecl _lock_file(FILE *_File);
void __cdecl _unlock_file(FILE *_File);
char * __cdecl getenv(char *_VarName);
size_t __cdecl mbrtowc(wchar_t *_DstCh,char *_SrcCh,size_t _SizeInBytes,mbstate_t *_State);
ulong __cdecl strtoul(char *_Str,char **_EndPtr,int _Radix);
void strtoull(void);
size_t __cdecl wcrtomb(char *_Dest,wchar_t _Source,mbstate_t *_State);
DWORD __stdcall WaitForSingleObject(HANDLE hHandle,DWORD dwMilliseconds);
SIZE_T __stdcall VirtualQuery(LPCVOID lpAddress,PMEMORY_BASIC_INFORMATION lpBuffer,SIZE_T dwLength);
BOOL __stdcall VirtualProtect(LPVOID lpAddress,SIZE_T dwSize,DWORD flNewProtect,PDWORD lpflOldProtect);
LPVOID __stdcall TlsGetValue(DWORD dwTlsIndex);
BOOL __stdcall TerminateProcess(HANDLE hProcess,UINT uExitCode);
void __stdcall Sleep(DWORD dwMilliseconds);
PEXCEPTION_ROUTINE __stdcall RtlVirtualUnwind(DWORD HandlerType,DWORD64 ImageBase,DWORD64 ControlPc,PRUNTIME_FUNCTION FunctionEntry,PCONTEXT ContextRecord,PVOID *HandlerData,PDWORD64 EstablisherFrame,PKNONVOLATILE_CONTEXT_POINTERS ContextPointers);
void __stdcall RtlUnwindEx(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue,PCONTEXT ContextRecord,PUNWIND_HISTORY_TABLE HistoryTable);
PRUNTIME_FUNCTION __stdcall RtlLookupFunctionEntry(DWORD64 ControlPc,PDWORD64 ImageBase,PUNWIND_HISTORY_TABLE HistoryTable);
void __stdcall ReleaseSRWLockShared(PSRWLOCK SRWLock);
void __stdcall ReleaseSRWLockExclusive(PSRWLOCK SRWLock);
void __stdcall RaiseException(DWORD dwExceptionCode,DWORD dwExceptionFlags,DWORD nNumberOfArguments,ULONG_PTR *lpArguments);
HLOCAL __stdcall LocalFree(HLOCAL hMem);
void __stdcall LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
void K32EnumProcessModules(void);
BOOL __stdcall IsProcessorFeaturePresent(DWORD ProcessorFeature);
void __stdcall InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
ULONGLONG __stdcall GetTickCount64(void);
FARPROC __stdcall GetProcAddress(HMODULE hModule,LPCSTR lpProcName);
DWORD __stdcall GetLastError(void);
DWORD __stdcall GetCurrentProcessId(void);
HANDLE __stdcall GetCurrentProcess(void);
DWORD __stdcall FormatMessageA(DWORD dwFlags,LPCVOID lpSource,DWORD dwMessageId,DWORD dwLanguageId,LPSTR lpBuffer,DWORD nSize,va_list *Arguments);
void __stdcall EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
BOOL __stdcall DisableThreadLibraryCalls(HMODULE hLibModule);
void __stdcall DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
HANDLE __stdcall CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,SIZE_T dwStackSize,LPTHREAD_START_ROUTINE lpStartAddress,LPVOID lpParameter,DWORD dwCreationFlags,LPDWORD lpThreadId);
HANDLE __stdcall CreateEventExA(LPSECURITY_ATTRIBUTES lpEventAttributes,LPCSTR lpName,DWORD dwFlags,DWORD dwDesiredAccess);
BOOL __stdcall CloseHandle(HANDLE hObject);
void __stdcall AcquireSRWLockShared(PSRWLOCK SRWLock);
void __stdcall AcquireSRWLockExclusive(PSRWLOCK SRWLock);
undefined8 .text(HANDLE param_1,int param_2,LPCRITICAL_SECTION param_3,int *param_4);
undefined8 pthread_condattr_destroy(undefined4 *param_1);
undefined8 pthread_condattr_init(undefined4 *param_1);
undefined8 pthread_condattr_getpshared(undefined4 *param_1,undefined4 *param_2);
undefined8 pthread_condattr_getclock(longlong param_1,undefined4 *param_2);
undefined8 pthread_condattr_setclock(longlong param_1,int param_2);
undefined8 pthread_condattr_setpshared(undefined4 *param_1,uint param_2);
undefined8 pthread_cond_init(undefined8 *param_1,int *param_2);
byte do_sema_b_wait_intern(HANDLE param_1,int param_2,uint param_3);
ulonglong do_sema_b_wait(HANDLE param_1,int param_2,uint param_3,LPCRITICAL_SECTION param_4,int *param_5);
ulonglong pthread_cond_destroy(longlong *param_1);
ulonglong pthread_cond_signal(undefined8 *param_1);
ulonglong pthread_cond_broadcast(undefined8 *param_1);
void cleanup_wait(longlong *param_1);
ulonglong pthread_cond_wait(longlong *param_1,longlong *param_2);
ulonglong pthread_cond_timedwait_impl(longlong *param_1,longlong *param_2,longlong *param_3,int param_4);
void pthread_cond_timedwait64(longlong *param_1,longlong *param_2,longlong *param_3);
void pthread_cond_timedwait32(longlong *param_1,longlong *param_2,int *param_3);
void pthread_cond_timedwait64_relative_np(longlong *param_1,longlong *param_2,longlong *param_3);
void pthread_cond_timedwait32_relative_np(longlong *param_1,longlong *param_2,int *param_3);
void pthread_cond_timedwait(longlong *param_1,longlong *param_2,longlong *param_3);
void pthread_cond_timedwait_relative_np(longlong *param_1,longlong *param_2,longlong *param_3);
ulonglong _pthread_get_tick_count.part.0(_struct_19 *param_1);
ulonglong _pthread_time_in_ms(void);
longlong _pthread_time_in_ms_from_timespec(longlong *param_1);
longlong _pthread_rel_time_in_ms(longlong *param_1);
DWORD _pthread_wait_for_single_object(HANDLE param_1,DWORD param_2);
DWORD _pthread_wait_for_multiple_objects(DWORD param_1,HANDLE *param_2,BOOL param_3,DWORD param_4);
undefined4 * mutex_impl_init(longlong *param_1,longlong param_2);
undefined8 pthread_mutex_lock_intern(longlong *param_1,DWORD param_2);
void pthread_mutex_timedlock(longlong *param_1,longlong *param_2);
undefined8 pthread_mutex_lock(longlong *param_1);
void pthread_mutex_timedlock64(longlong *param_1,longlong *param_2);
void pthread_mutex_timedlock32(longlong *param_1,int *param_2);
bool pthread_mutex_unlock(longlong *param_1);
undefined8 pthread_mutex_trylock(longlong *param_1);
undefined8 pthread_mutex_init(longlong *param_1,uint *param_2);
undefined8 pthread_mutex_destroy(undefined8 *param_1);
undefined8 pthread_mutexattr_init(undefined4 *param_1);
byte pthread_mutexattr_destroy(longlong param_1);
undefined8 pthread_mutexattr_gettype(uint *param_1,uint *param_2);
undefined8 pthread_mutexattr_settype(uint *param_1,uint param_2);
undefined8 pthread_mutexattr_getpshared(uint *param_1,uint *param_2);
undefined8 pthread_mutexattr_setpshared(uint *param_1,uint param_2);
undefined8 pthread_mutexattr_getprotocol(uint *param_1,uint *param_2);
undefined8 pthread_mutexattr_setprotocol(uint *param_1,uint param_2);
undefined8 pthread_mutexattr_getprioceiling(uint *param_1,uint *param_2);
undefined8 pthread_mutexattr_setprioceiling(uint *param_1,int param_2);
undefined8 pthread_spin_init(undefined8 *param_1,uint param_2);
undefined8 pthread_spin_destroy(longlong *param_1);
undefined8 pthread_spin_lock(undefined8 *param_1);
undefined8 pthread_spin_trylock(undefined8 *param_1);
byte pthread_spin_unlock(undefined8 *param_1);
undefined4 pthread_check.part.0(ulonglong param_1);
undefined8 sched_get_priority_min(uint param_1);
undefined8 sched_get_priority_max(uint param_1);
undefined8 pthread_attr_setschedparam(longlong param_1,undefined4 *param_2);
undefined8 pthread_attr_getschedparam(longlong param_1,undefined4 *param_2);
byte pthread_attr_setschedpolicy(longlong param_1,uint param_2);
undefined8 pthread_attr_getschedpolicy(longlong param_1,undefined4 *param_2);
undefined4 pthread_getschedparam(ulonglong param_1,undefined4 *param_2,undefined4 *param_3);
undefined8 pthread_setschedparam(ulonglong param_1,uint param_2,int *param_3);
undefined8 sched_getscheduler(longlong param_1);
undefined4 sched_setscheduler(longlong param_1,int param_2,longlong param_3);
undefined8 sched_yield(void);
bool SetThreadName_SEH(int *param_1);
undefined8 __pthread_get_pointer(ulonglong param_1);
longlong * enterOnceObject(longlong param_1);
ulonglong __pthread_register_pointer(undefined8 param_1);
void pthread_tls_init(void);
void SetThreadName(undefined4 param_1,undefined8 param_2);
void replace_spin_keys.part.0(void);
void leaveOnceObject.part.0(void *param_1);
void _pthread_once_cleanup(void *param_1);
void * pop_pthread_mem(void);
void push_pthread_mem.part.0(void *param_1);
void push_pthread_mem(void *param_1);
void _pthread_once_raw.part.0.constprop.0.isra.0(void);
void _pthread_cleanup_dest.part.0(ulonglong param_1);
void pthread_create_wrapper(undefined4 *param_1);
LPVOID __pthread_self_lite(void);
void tls_callback_2(undefined8 param_1,int param_2);
undefined8 __pth_gpointer_locked(ulonglong param_1);
undefined8 pthread_timechange_handler_np(void);
int pthread_num_processors_np(void);
int pthread_set_num_processors_np(int param_1);
undefined8 pthread_once(uint *param_1,undefined *param_2);
undefined8 pthread_key_create(uint *param_1,longlong param_2);
undefined8 pthread_key_delete(uint param_1);
undefined8 pthread_getspecific(uint param_1);
undefined8 pthread_setspecific(uint param_1,undefined8 param_2);
bool pthread_equal(longlong param_1,longlong param_2);
void _pthread_cleanup_dest(ulonglong param_1);
undefined8 pthread_self(void);
undefined8 pthread_getevent(void);
undefined8 pthread_gethandle(ulonglong param_1);
longlong pthread_getclean(void);
undefined8 pthread_get_concurrency(undefined4 *param_1);
undefined8 pthread_set_concurrency(undefined4 param_1);
void pthread_exit(ulonglong param_1);
uint _pthread_invoke_cancel(void);
uint test_cancel_locked(ulonglong param_1);
uint __pthread_shallcancel(void);
void _pthread_setnobreak(int param_1);
LPVOID pthread_testcancel(void);
undefined8 _pthread_delay_np_ms(DWORD param_1);
void __pthread_delay_np.isra.0(longlong *param_1);
undefined8 pthread_delay32_np(int *param_1);
undefined8 pthread_delay64_np(longlong *param_1);
undefined8 pthread_delay_np(longlong *param_1);
byte pthread_cancel(ulonglong param_1);
byte pthread_kill(ulonglong param_1,int param_2);
uint _pthread_get_state(uint *param_1,uint param_2);
undefined8 _pthread_set_state(uint *param_1,uint param_2,uint param_3);
undefined8 pthread_attr_init(undefined4 *param_1);
undefined8 pthread_attr_destroy(undefined1 (*param_1) [16]);
undefined8 pthread_attr_setdetachstate(uint *param_1,uint param_2);
undefined8 pthread_attr_getdetachstate(uint *param_1,uint *param_2);
undefined8 pthread_attr_setinheritsched(uint *param_1,uint param_2);
undefined8 pthread_attr_getinheritsched(uint *param_1,uint *param_2);
undefined8 pthread_attr_setscope(uint *param_1,uint param_2);
undefined8 pthread_attr_getscope(uint *param_1,uint *param_2);
undefined8 pthread_attr_getstack(longlong param_1,longlong *param_2,longlong *param_3);
undefined8 pthread_attr_setstack(longlong param_1,longlong param_2,longlong param_3);
undefined8 pthread_attr_getstackaddr(longlong param_1,undefined8 *param_2);
undefined8 pthread_attr_setstackaddr(longlong param_1,undefined8 param_2);
undefined8 pthread_attr_getstacksize(longlong param_1,undefined8 *param_2);
undefined8 pthread_attr_setstacksize(longlong param_1,undefined8 param_2);
undefined8 pthread_setcancelstate(uint param_1,uint *param_2);
undefined8 pthread_setcanceltype(uint param_1,uint *param_2);
undefined8 pthread_create(undefined8 *param_1,uint *param_2,undefined8 param_3,undefined8 param_4);
undefined8 pthread_join(ulonglong param_1,undefined8 *param_2);
undefined8 _pthread_tryjoin(ulonglong param_1,undefined8 *param_2);
undefined8 pthread_detach(ulonglong param_1);
undefined4 pthread_getconcurrency(void);
undefined8 pthread_setconcurrency(undefined4 param_1);
undefined4 pthread_setname_np(ulonglong param_1,char *param_2);
undefined4 pthread_getname_np(ulonglong param_1,undefined1 *param_2,ulonglong param_3);
undefined4 rwl_ref_destroy(undefined8 *param_1,undefined8 *param_2);
undefined8 rwl_ref_unlock(undefined8 *param_1);
undefined4 rwl_unref(longlong *param_1,undefined4 param_2);
void st_cancelwrite(longlong param_1);
void __pthread_rwlock_timedrdlock.part.0(longlong *param_1,longlong *param_2);
void __pthread_rwlock_timedwrlock.part.0(longlong *param_1,longlong *param_2);
ulonglong pthread_rwlock_init(undefined8 *param_1);
ulonglong rwlock_static_init(longlong *param_1);
ulonglong rwl_ref.isra.0(longlong *param_1);
void pthread_rwlock_timedrdlock(longlong *param_1,longlong *param_2);
ulonglong pthread_rwlock_timedwrlock(longlong *param_1,longlong *param_2);
int pthread_rwlock_destroy(undefined8 *param_1);
void pthread_rwlock_rdlock(longlong *param_1);
void pthread_rwlock_timedrdlock64(longlong *param_1,longlong *param_2);
void pthread_rwlock_timedrdlock32(longlong *param_1,int *param_2);
void pthread_rwlock_tryrdlock(longlong *param_1);
void pthread_rwlock_trywrlock(longlong *param_1);
void pthread_rwlock_unlock(longlong *param_1);
void pthread_rwlock_wrlock(longlong *param_1);
ulonglong pthread_rwlock_timedwrlock64(longlong *param_1,longlong *param_2);
ulonglong pthread_rwlock_timedwrlock32(longlong *param_1,int *param_2);
byte pthread_rwlockattr_destroy(longlong param_1);
undefined8 pthread_rwlockattr_init(undefined4 *param_1);
undefined8 pthread_rwlockattr_getpshared(undefined4 *param_1,undefined4 *param_2);
undefined8 pthread_rwlockattr_setpshared(uint *param_1,uint param_2);
DWORD __stdcall WaitForMultipleObjects(DWORD nCount,HANDLE *lpHandles,BOOL bWaitAll,DWORD dwMilliseconds);
BOOL __stdcall TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
BOOL __stdcall TlsSetValue(DWORD dwTlsIndex,LPVOID lpTlsValue);
DWORD __stdcall TlsAlloc(void);
DWORD __stdcall SuspendThread(HANDLE hThread);
BOOL __stdcall SetThreadPriority(HANDLE hThread,int nPriority);
BOOL __stdcall SetThreadContext(HANDLE hThread,CONTEXT *lpContext);
BOOL __stdcall SetProcessAffinityMask(HANDLE hProcess,DWORD_PTR dwProcessAffinityMask);
void __stdcall SetLastError(DWORD dwErrCode);
BOOL __stdcall SetEvent(HANDLE hEvent);
DWORD __stdcall ResumeThread(HANDLE hThread);
BOOL __stdcall ResetEvent(HANDLE hEvent);
BOOL __stdcall ReleaseSemaphore(HANDLE hSemaphore,LONG lReleaseCount,LPLONG lpPreviousCount);
BOOL __stdcall QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
BOOL __stdcall QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
void __stdcall OutputDebugStringA(LPCSTR lpOutputString);
HANDLE __stdcall OpenProcess(DWORD dwDesiredAccess,BOOL bInheritHandle,DWORD dwProcessId);
DWORD __stdcall GetTickCount(void);
int __stdcall GetThreadPriority(HANDLE hThread);
BOOL __stdcall GetThreadContext(HANDLE hThread,LPCONTEXT lpContext);
void __stdcall GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime);
BOOL __stdcall GetProcessAffinityMask(HANDLE hProcess,PDWORD_PTR lpProcessAffinityMask,PDWORD_PTR lpSystemAffinityMask);
HMODULE __stdcall GetModuleHandleA(LPCSTR lpModuleName);
DWORD __stdcall GetCurrentThreadId(void);
HANDLE __stdcall GetCurrentThread(void);
BOOL __stdcall DuplicateHandle(HANDLE hSourceProcessHandle,HANDLE hSourceHandle,HANDLE hTargetProcessHandle,LPHANDLE lpTargetHandle,DWORD dwDesiredAccess,BOOL bInheritHandle,DWORD dwOptions);
HANDLE __stdcall CreateSemaphoreA(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,LONG lInitialCount,LONG lMaximumCount,LPCSTR lpName);
HANDLE __stdcall CreateEventA(LPSECURITY_ATTRIBUTES lpEventAttributes,BOOL bManualReset,BOOL bInitialState,LPCSTR lpName);
void _assert(char *message,char *file,uint line);
int snprintf(char *__stream,size_t __n,char *__format,...);
char * __cdecl strdup(char *_Src);
void __stdio_common_vsprintf(void);
int __cdecl fileno(FILE *_File);
int __cdecl _setmode(int _FileHandle,int _Mode);
int __cdecl fflush(FILE *_File);
uintptr_t __cdecl _beginthreadex(void *_Security,uint _StackSize,_StartAddress *_StartAddress,void *_ArgList,uint _InitFlag,uint *_ThrdAddr);
void __cdecl _endthreadex(uint _Retval);
int __cdecl _setjmp(_JBTYPE *_Buf);
void __cdecl longjmp(_JBTYPE *_Buf,int _Value);
size_t __cdecl mbsrtowcs(wchar_t *_Dest,char **_PSrc,size_t _Count,mbstate_t *_State);
void __thiscall std::bad_exception::~bad_exception(void);
void __thiscall std::exception::~exception(void);
void get_adjusted_ptr(longlong *param_1,longlong *param_2,undefined8 *param_3);
byte * parse_lsda_header(longlong param_1,byte *param_2,longlong *param_3);
undefined8 check_exception_spec(longlong param_1,longlong *param_2,undefined8 param_3,ulonglong param_4);
longlong base_of_encoded_value(byte param_1,longlong param_2);
void __gxx_exception_cleanup(uint param_1,longlong param_2);
ulonglong *read_encoded_value_with_base(byte param_1,ulonglong *param_2,ulonglong *param_3,undefined8 *param_4);
void __cxxabiv1::__terminate(undefined *param_1);
void __cxxabiv1::__unexpected(undefined *param_1);
void __thiscall __cxxabiv1::__forced_unwind::~__forced_unwind(__forced_unwind *this);
void __thiscall __cxxabiv1::__forced_unwind::~__forced_unwind(void);
void __thiscall __cxxabiv1::__class_type_info::~__class_type_info(__class_type_info *this);
void __thiscall __cxxabiv1::__class_type_info::~__class_type_info(__class_type_info *this);
void __thiscall __cxxabiv1::__foreign_exception::~__foreign_exception(__foreign_exception *this);
void __thiscall __cxxabiv1::__foreign_exception::~__foreign_exception(void);
void __thiscall __cxxabiv1::__si_class_type_info::~__si_class_type_info(__si_class_type_info *this);
void __thiscall __cxxabiv1::__si_class_type_info::~__si_class_type_info(__si_class_type_info *this);
undefined8 __cxxabiv1::__gxx_personality_imp(int param_1,uint param_2,longlong param_3,byte *param_4,longlong param_5);
void __thiscall(anonymous_namespace)::system_error_category::~system_error_category(system_error_category *this);
void __thiscall (anonymous_namespace)::system_error_category::~system_error_category(void);
void __thiscall(anonymous_namespace)::generic_error_category::~generic_error_category(generic_error_category *this);
void __thiscall (anonymous_namespace)::generic_error_category::~generic_error_category(void);
ulonglong * (anonymous_namespace)::pool::free(longlong param_1);
ulonglong * (anonymous_namespace)::pool::allocate(ulonglong param_1);
void (anonymous_namespace)::init_static_cond(void);
void (anonymous_namespace)::init(void);
longlong .text$_ZN7reshade8internal25get_reshade_module_handleEP11HINSTANCE__(longlong param_1,undefined8 param_2,longlong param_3);
ulonglong __gnu_cxx::__concat_size_t(void *param_1,ulonglong param_2,ulonglong param_3);
int __gnu_cxx::__snprintf_lite(char *param_1,longlong param_2,char *param_3,ulonglong *param_4);
void __thiscall .text$_ZN9__gnu_cxx24__concurrence_lock_errorD0Ev(void *this);
void __thiscall .text$_ZN9__gnu_cxx24__concurrence_lock_errorD1Ev(void *this);
void __thiscall .text$_ZN9__gnu_cxx24__concurrence_wait_errorD0Ev(void *this);
void __thiscall .text$_ZN9__gnu_cxx24__concurrence_wait_errorD1Ev(void *this);
void __thiscall .text$_ZN9__gnu_cxx26__concurrence_unlock_errorD0Ev(void *this);
void __thiscall .text$_ZN9__gnu_cxx26__concurrence_unlock_errorD1Ev(void *this);
void __gnu_cxx::__verbose_terminate_handler(void);
void __thiscall .text$_ZN9__gnu_cxx29__concurrence_broadcast_errorD0Ev(void *this);
void __thiscall .text$_ZN9__gnu_cxx29__concurrence_broadcast_errorD1Ev(void *this);
void .text$_ZN9__gnu_cxx30__throw_concurrence_lock_errorEv(void);
void .text$_ZN9__gnu_cxx32__throw_concurrence_unlock_errorEv(void);
void .text$_ZN9__gnu_cxx35__throw_concurrence_broadcast_errorEv(void);
void .text$_ZN9realsmoke11SafeReleaseI24ID3D11ShaderResourceViewEEvRPT_(longlong *param_1);
void __thiscall .text$_ZN9realsmoke22D3D11ComputeStateGuardD1Ev(void *this);
void __thiscall .text$_ZN9realsmoke23D3D11GraphicsStateGuardD1Ev(void *this);
void .text$_ZN9realsmoke8LogDebugEPKcz(char *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,...);
void __thiscall __cxxabiv1::__class_type_info::__do_catch(__class_type_info *this,type_info *param_1,undefined8 *param_2,uint param_3);
void __thiscall __cxxabiv1::__class_type_info::__do_upcast(__class_type_info *this,type_info *param_1,undefined8 param_2,undefined8 *param_3);
undefined8 __thiscall __cxxabiv1::__class_type_info::__do_upcast(__class_type_info *this,type_info *param_1,undefined8 *param_2);
undefined8 __thiscall __cxxabiv1::__class_type_info::__do_dyncast(__class_type_info *this,undefined8 param_1,undefined4 param_2,type_info *param_3,longlong param_4,type_info *param_5,longlong param_6,longlong *param_7);
char __thiscall __cxxabiv1::__class_type_info::__do_find_public_src(__class_type_info *this,undefined8 param_2_00,longlong param_2,undefined8 param_4_00,longlong param_4);
void __thiscall __cxxabiv1::__si_class_type_info::__do_upcast(__si_class_type_info *this,type_info *param_1,undefined8 param_2,undefined8 *param_3);
undefined8 __thiscall __cxxabiv1::__si_class_type_info::__do_dyncast(__si_class_type_info *this,longlong param_1,undefined4 param_2,type_info *param_3,longlong param_4,type_info *param_5,longlong param_6,longlong *param_7);
undefined8 __thiscall __cxxabiv1::__si_class_type_info::__do_find_public_src(__si_class_type_info *this,undefined8 param_1,longlong param_2,type_info *param_3,longlong param_4);
bool __thiscall(anonymous_namespace)::system_error_category::equivalent(system_error_category *this,int param_1,int *param_2);
void (anonymous_namespace)::system_error_category::default_error_condition(int *param_1,undefined8 param_2,int param_3);
char * (anonymous_namespace)::system_error_category::name(void);
longlong *(anonymous_namespace)::system_error_category::message[abi:cxx11](longlong *param_1,undefined8 param_2,DWORD param_3);
bool __thiscall(anonymous_namespace)::generic_error_category::equivalent(generic_error_category *this,int param_1,int *param_2);
char * (anonymous_namespace)::generic_error_category::name(void);
longlong *(anonymous_namespace)::generic_error_category::message[abi:cxx11](longlong *param_1,undefined8 param_2,int param_3);
char * .text$_ZNK9__gnu_cxx24__concurrence_lock_error4whatEv(void);
char * .text$_ZNK9__gnu_cxx24__concurrence_wait_error4whatEv(void);
char * .text$_ZNK9__gnu_cxx26__concurrence_unlock_error4whatEv(void);
char * .text$_ZNK9__gnu_cxx29__concurrence_broadcast_error4whatEv(void);
bool .text$_ZNKSs11_M_disjunctEPKc(ulonglong *param_1,ulonglong param_2);
void .text$_ZNKSs12find_last_ofEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSs12find_last_ofEPKcyy(longlong *param_1,void *param_2,ulonglong param_3,size_t param_4);
void .text$_ZNKSs12find_last_ofERKSsy(longlong *param_1,undefined8 *param_2,ulonglong param_3);
void .text$_ZNKSs12find_last_ofEcy(longlong *param_1,char param_2,ulonglong param_3);
void .text$_ZNKSs13find_first_ofEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSs13find_first_ofEPKcyy(longlong *param_1,void *param_2,ulonglong param_3,size_t param_4);
void .text$_ZNKSs13find_first_ofERKSsy(longlong *param_1,undefined8 *param_2,ulonglong param_3);
void .text$_ZNKSs13find_first_ofEcy(longlong *param_1,char param_2,ulonglong param_3);
undefined8 .text$_ZNKSs13get_allocatorEv(undefined8 param_1);
void .text$_ZNKSs15_M_check_lengthEyyPKc(longlong *param_1,longlong param_2,ulonglong param_3,char *param_4);
void .text$_ZNKSs16find_last_not_ofEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSs16find_last_not_ofEPKcyy(longlong *param_1,void *param_2,ulonglong param_3,size_t param_4);
void .text$_ZNKSs16find_last_not_ofERKSsy(longlong *param_1,undefined8 *param_2,ulonglong param_3);
ulonglong .text$_ZNKSs16find_last_not_ofEcy(longlong *param_1,char param_2,ulonglong param_3);
void .text$_ZNKSs17find_first_not_ofEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSs17find_first_not_ofEPKcyy(longlong *param_1,void *param_2,ulonglong param_3,size_t param_4);
void .text$_ZNKSs17find_first_not_ofERKSsy(longlong *param_1,undefined8 *param_2,ulonglong param_3);
ulonglong .text$_ZNKSs17find_first_not_ofEcy(longlong *param_1,char param_2,ulonglong param_3);
longlong .text$_ZNKSs2atEy(longlong *param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4);
longlong .text$_ZNKSs3endEv(longlong *param_1);
uint .text$_ZNKSs4_Rep12_M_is_leakedEv(longlong param_1);
undefined4 .text$_ZNKSs4_Rep12_M_is_sharedEv(longlong param_1);
longlong .text$_ZNKSs4backEv(longlong *param_1);
longlong .text$_ZNKSs4cendEv(longlong *param_1);
size_t .text$_ZNKSs4copyEPcyy(longlong *param_1,undefined1 *param_2,ulonglong param_3,ulonglong param_4);
undefined8 .text$_ZNKSs4dataEv(undefined8 *param_1);
void .text$_ZNKSs4findEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSs4findEPKcyy(longlong *param_1,char *param_2,ulonglong param_3,ulonglong param_4);
void .text$_ZNKSs4findERKSsy(longlong *param_1,undefined8 *param_2,ulonglong param_3);
longlong .text$_ZNKSs4findEcy(longlong *param_1,char param_2,ulonglong param_3);
undefined8 * .text$_ZNKSs4rendEv(undefined8 *param_1,undefined8 *param_2);
undefined8 .text$_ZNKSs4sizeEv(longlong *param_1);
undefined8 .text$_ZNKSs5beginEv(undefined8 *param_1);
undefined8 .text$_ZNKSs5c_strEv(undefined8 *param_1);
undefined8 * .text$_ZNKSs5crendEv(undefined8 *param_1,undefined8 *param_2);
undefined8 .text$_ZNKSs5emptyEv(longlong *param_1);
undefined8 .text$_ZNKSs5frontEv(undefined8 *param_1);
void .text$_ZNKSs5rfindEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSs5rfindEPKcyy(longlong *param_1,void *param_2,ulonglong param_3,ulonglong param_4);
void .text$_ZNKSs5rfindERKSsy(longlong *param_1,undefined8 *param_2,ulonglong param_3);
longlong .text$_ZNKSs5rfindEcy(longlong *param_1,char param_2,ulonglong param_3);
longlong .text$_ZNKSs6_M_repEv(longlong *param_1);
undefined8 .text$_ZNKSs6cbeginEv(undefined8 *param_1);
undefined8 .text$_ZNKSs6lengthEv(longlong *param_1);
longlong * .text$_ZNKSs6rbeginEv(longlong *param_1,longlong *param_2);
void * .text$_ZNKSs6substrEyy(void *param_1,longlong *param_2,ulonglong param_3,ulonglong param_4);
undefined8 .text$_ZNKSs7_M_dataEv(undefined8 *param_1);
longlong .text$_ZNKSs7_M_iendEv(longlong *param_1);
ulonglong .text$_ZNKSs7compareEPKc(undefined8 *param_1,char *param_2);
ulonglong .text$_ZNKSs7compareERKSs(undefined8 *param_1,undefined8 *param_2);
ulonglong .text$_ZNKSs7compareEyyPKc(longlong *param_1,ulonglong param_2,ulonglong param_3,char *param_4);
ulonglong .text$_ZNKSs7compareEyyPKcy(longlong *param_1,ulonglong param_2,ulonglong param_3,void *param_4,ulonglong param_5);
ulonglong .text$_ZNKSs7compareEyyRKSs(longlong *param_1,ulonglong param_2,ulonglong param_3,undefined8 *param_4);
ulonglong .text$_ZNKSs7compareEyyRKSsyy(longlong *param_1,ulonglong param_2,ulonglong param_3,longlong *param_4,ulonglong param_5,ulonglong param_6);
longlong * .text$_ZNKSs7crbeginEv(longlong *param_1,longlong *param_2);
void .text$_ZNKSs8_M_checkEyPKc(longlong *param_1,ulonglong param_2,ulonglong param_3);
ulonglong .text$_ZNKSs8_M_limitEyy(longlong *param_1,longlong param_2,ulonglong param_3);
undefined8 .text$_ZNKSs8capacityEv(longlong *param_1);
undefined8 .text$_ZNKSs8max_sizeEv(void);
undefined8 .text$_ZNKSs9_M_ibeginEv(undefined8 *param_1);
longlong .text$_ZNKSsixEy(longlong *param_1,longlong param_2);
char * std::bad_typeid::what(void);
int * std::error_code::default_error_condition(int *param_1,int *param_2);
undefined8 __thiscall std::logic_error::what(logic_error *this);
undefined8 __thiscall std::__cow_string::c_str(__cow_string *this);
char * std::bad_exception::what(void);
undefined8 __thiscall std::random_device::_M_getentropy(random_device *this);
char * std::bad_array_new_length::what(void);
__cow_string *std::_V2::error_category::_M_message[abi:cxx11](__cow_string *param_1,longlong *param_2,DWORD param_3);
bool __thiscall std::_V2::error_category::equivalent(error_category *this,int *param_1,int param_2);
bool __thiscall std::_V2::error_category::equivalent(error_category *this,int param_1,int *param_2);
undefined4 *std::_V2::error_category::default_error_condition(undefined4 *param_1,undefined8 param_2,undefined4 param_3);
bool .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE11_M_disjunctEPKc(ulonglong *param_1,ulonglong param_2);
undefined8.text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE11_M_is_localEv(longlong *param_1);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12find_last_ofEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12find_last_ofEPKcyy(longlong *param_1,void *param_2,ulonglong param_3,size_t param_4);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12find_last_ofERKS4_y(longlong *param_1,undefined8 *param_2,ulonglong param_3);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12find_last_ofEcy(longlong *param_1,char param_2,ulonglong param_3);
longlong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13_M_local_dataEv(longlong param_1);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13find_first_ofEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13find_first_ofEPKcyy(longlong *param_1,void *param_2,ulonglong param_3,size_t param_4);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13find_first_ofERKS4_y(longlong *param_1,undefined8 *param_2,ulonglong param_3);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13find_first_ofEcy(longlong *param_1,char param_2,ulonglong param_3);
undefined8.text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13get_allocatorEv(undefined8 param_1);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE15_M_check_lengthEyyPKc(longlong param_1,longlong param_2,ulonglong param_3,char *param_4);
undefined8.text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE16_M_get_allocatorEv(undefined8 param_1);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE16find_last_not_ofEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE16find_last_not_ofEPKcyy(longlong *param_1,void *param_2,ulonglong param_3,size_t param_4);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE16find_last_not_ofERKS4_y(longlong *param_1,undefined8 *param_2,ulonglong param_3);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE16find_last_not_ofEcy(longlong *param_1,char param_2,ulonglong param_3);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE17find_first_not_ofEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE17find_first_not_ofEPKcyy(longlong *param_1,void *param_2,ulonglong param_3,size_t param_4);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE17find_first_not_ofERKS4_y(longlong *param_1,undefined8 *param_2,ulonglong param_3);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE17find_first_not_ofEcy(longlong *param_1,char param_2,ulonglong param_3);
longlong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE2atEy(longlong *param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4);
longlong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE3endEv(longlong *param_1);
longlong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4backEv(longlong *param_1);
longlong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4cendEv(longlong *param_1);
size_t .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4copyEPcyy(longlong *param_1,undefined1 *param_2,ulonglong param_3,ulonglong param_4);
undefined8 .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4dataEv(undefined8 *param_1);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEPKcyy(longlong *param_1,char *param_2,ulonglong param_3,ulonglong param_4);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findERKS4_y(longlong *param_1,undefined8 *param_2,ulonglong param_3);
longlong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEcy(longlong *param_1,char param_2,ulonglong param_3);
undefined8 *.text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4rendEv(undefined8 *param_1,undefined8 *param_2);
undefined8 .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4sizeEv(longlong param_1);
undefined8 .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5beginEv(undefined8 *param_1);
undefined8 .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5c_strEv(undefined8 *param_1);
undefined8 *.text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5crendEv(undefined8 *param_1,undefined8 *param_2);
bool .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5emptyEv(longlong param_1);
undefined8 .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5frontEv(undefined8 *param_1);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5rfindEPKcy(longlong *param_1,char *param_2,ulonglong param_3);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5rfindEPKcyy(longlong *param_1,void *param_2,ulonglong param_3,ulonglong param_4);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5rfindERKS4_y(longlong *param_1,undefined8 *param_2,ulonglong param_3);
longlong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5rfindEcy(longlong *param_1,char param_2,ulonglong param_3);
undefined8.text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6cbeginEv(undefined8 *param_1);
undefined8 .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6lengthEv(longlong param_1);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6rbeginEv(longlong *param_1,longlong *param_2);
longlong *.text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6substrEyy(longlong *param_1,longlong *param_2,ulonglong param_3,ulonglong param_4);
undefined8.text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7_M_dataEv(undefined8 *param_1);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEPKc(undefined8 *param_1,char *param_2);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareERKS4_(undefined8 *param_1,undefined8 *param_2);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEyyPKc(longlong *param_1,ulonglong param_2,ulonglong param_3,char *param_4);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEyyPKcy(longlong *param_1,ulonglong param_2,ulonglong param_3,void *param_4,ulonglong param_5);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEyyRKS4_(longlong *param_1,ulonglong param_2,ulonglong param_3,undefined8 *param_4);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEyyRKS4_yy(longlong *param_1,ulonglong param_2,ulonglong param_3,longlong *param_4,ulonglong param_5,ulonglong param_6);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7crbeginEv(longlong *param_1,longlong *param_2);
void .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE8_M_checkEyPKc(longlong param_1,ulonglong param_2,ulonglong param_3);
ulonglong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE8_M_limitEyy(longlong param_1,longlong param_2,ulonglong param_3);
longlong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE8capacityEv(longlong *param_1);
undefined8 .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE8max_sizeEv(void);
longlong .text$_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEy(longlong *param_1,longlong param_2);
uint __thiscall std::__detail::_Prime_rehash_policy::_M_next_bkt(_Prime_rehash_policy *this,ulonglong param_1);
undefined1 (*) [16]std::__detail::_Prime_rehash_policy::_M_need_rehash(undefined1 (*param_1) [16],_Prime_rehash_policy *param_2,ulonglong param_3,longlong param_4,longlong param_5);
char * std::bad_cast::what(void);
char * std::bad_alloc::what(void);
char * std::exception::what(void);
undefined8 std::type_info::__do_catch(longlong param_1,longlong param_2);
undefined8 std::type_info::__do_upcast(void);
undefined8 std::type_info::__is_pointer_p(void);
undefined8 __thiscall std::type_info::operator==(type_info *this,type_info *param_1);
ulonglong .text$_ZNSs10_S_compareEyy(longlong param_1,longlong param_2);
void __thiscall .text$_ZNSs12_Alloc_hiderC1EPcRKSaIcE(void *this,undefined8 param_1);
void __thiscall .text$_ZNSs12_Alloc_hiderC2EPcRKSaIcE(void *this,undefined8 param_1);
void .text$_ZNSs12_M_leak_hardEv(longlong *param_1);
ulonglong * .text$_ZNSs12_S_constructEycRKSaIcE(ulonglong param_1,char param_2);
ulonglong *.text$_ZNSs12_S_constructIN9__gnu_cxx17__normal_iteratorIPcSsEEEES2_T_S4_RKSaIcESt20forward_iterator_tag(undefined1 *param_1,longlong param_2);
ulonglong *.text$_ZNSs12_S_constructIPKcEEPcT_S3_RKSaIcESt20forward_iterator_tag(undefined1 *param_1,longlong param_2);
ulonglong * std::string::_S_construct<>(undefined1 *param_1,longlong param_2);
ulonglong *.text$_ZNSs12_S_constructIPcEES0_T_S1_RKSaIcESt20forward_iterator_tag(undefined1 *param_1,longlong param_2);
undefined1 * .text$_ZNSs12_S_empty_repEv(void);
void .text$_ZNSs13_S_copy_charsEPcN9__gnu_cxx17__normal_iteratorIPKcSsEES4_(undefined1 *param_1,undefined1 *param_2,longlong param_3);
void .text$_ZNSs13_S_copy_charsEPcN9__gnu_cxx17__normal_iteratorIS_SsEES2_(undefined1 *param_1,undefined1 *param_2,longlong param_3);
void .text$_ZNSs13_S_copy_charsEPcPKcS1_(undefined1 *param_1,undefined1 *param_2,longlong param_3);
void .text$_ZNSs13_S_copy_charsEPcS_S_(undefined1 *param_1,undefined1 *param_2,longlong param_3);
void .text$_ZNSs13shrink_to_fitEv(longlong *param_1);
longlong *.text$_ZNSs14_M_replace_auxEyyyc(longlong *param_1,size_t param_2,longlong param_3,ulonglong param_4,char param_5);
longlong *.text$_ZNSs15_M_replace_safeEyyPKcy(longlong *param_1,size_t param_2,longlong param_3,undefined1 *param_4,size_t param_5);
void .text$_ZNSs18_S_construct_aux_2EycRKSaIcE(ulonglong param_1,char param_2);
longlong .text$_ZNSs2atEy(longlong *param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4);
longlong .text$_ZNSs3endEv(longlong *param_1);
void .text$_ZNSs4_Rep10_M_destroyERKSaIcE(void *param_1);
void .text$_ZNSs4_Rep10_M_disposeERKSaIcE(void *param_1);
longlong .text$_ZNSs4_Rep10_M_refcopyEv(longlong param_1);
longlong .text$_ZNSs4_Rep10_M_refdataEv(longlong param_1);
undefined1 * .text$_ZNSs4_Rep12_S_empty_repEv(void);
void .text$_ZNSs4_Rep13_M_set_leakedEv(longlong param_1);
void .text$_ZNSs4_Rep15_M_set_sharableEv(longlong param_1);
void .text$_ZNSs4_Rep26_M_set_length_and_sharableEy(longlong *param_1,longlong param_2);
size_t * .text$_ZNSs4_Rep7_M_grabERKSaIcES2_(size_t *param_1,undefined8 param_2);
size_t * .text$_ZNSs4_Rep8_M_cloneERKSaIcEy(size_t *param_1,undefined8 param_2,longlong param_3);
void .text$_ZNSs4_Rep9_S_createEyyRKSaIcE(ulonglong param_1,ulonglong param_2);
longlong .text$_ZNSs4backEv(longlong *param_1);
void .text$_ZNSs4rendEv(longlong *param_1,longlong *param_2);
void .text$_ZNSs4swapERSs(longlong *param_1,longlong *param_2);
longlong .text$_ZNSs5beginEv(longlong *param_1);
void .text$_ZNSs5clearEv(longlong *param_1);
longlong .text$_ZNSs5eraseEN9__gnu_cxx17__normal_iteratorIPcSsEE(longlong *param_1,longlong param_2);
longlong .text$_ZNSs5eraseEN9__gnu_cxx17__normal_iteratorIPcSsEES2_(longlong *param_1,longlong param_2,longlong param_3);
longlong * .text$_ZNSs5eraseEyy(longlong *param_1,ulonglong param_2,ulonglong param_3);
longlong .text$_ZNSs5frontEv(longlong *param_1);
void .text$_ZNSs6appendEPKc(longlong *param_1,char *param_2);
longlong * .text$_ZNSs6appendEPKcy(longlong *param_1,undefined1 *param_2,ulonglong param_3);
longlong * .text$_ZNSs6appendERKSs(longlong *param_1,longlong *param_2);
longlong *.text$_ZNSs6appendERKSsyy(longlong *param_1,longlong *param_2,ulonglong param_3,ulonglong param_4);
void .text$_ZNSs6appendESt16initializer_listIcE(longlong *param_1,undefined8 *param_2);
longlong * .text$_ZNSs6appendEyc(longlong *param_1,ulonglong param_2,char param_3);
longlong * .text$_ZNSs6assignEOSs(longlong *param_1,longlong *param_2);
void .text$_ZNSs6assignEPKc(ulonglong *param_1,char *param_2);
ulonglong * .text$_ZNSs6assignEPKcy(ulonglong *param_1,undefined1 *param_2,ulonglong param_3);
longlong * .text$_ZNSs6assignERKSs(longlong *param_1,longlong *param_2);
void .text$_ZNSs6assignERKSsyy(ulonglong *param_1,longlong *param_2,ulonglong param_3,ulonglong param_4);
void .text$_ZNSs6assignESt16initializer_listIcE(ulonglong *param_1,undefined8 *param_2);
void .text$_ZNSs6assignEyc(longlong *param_1,ulonglong param_2,char param_3);
void .text$_ZNSs6insertEN9__gnu_cxx17__normal_iteratorIPcSsEESt16initializer_listIcE(ulonglong *param_1,longlong param_2,undefined8 *param_3);
longlong .text$_ZNSs6insertEN9__gnu_cxx17__normal_iteratorIPcSsEEc(longlong *param_1,longlong param_2,char param_3);
void .text$_ZNSs6insertEN9__gnu_cxx17__normal_iteratorIPcSsEEyc(longlong *param_1,longlong param_2,ulonglong param_3,char param_4);
void .text$_ZNSs6insertEyPKc(ulonglong *param_1,ulonglong param_2,char *param_3);
ulonglong *.text$_ZNSs6insertEyPKcy(ulonglong *param_1,ulonglong param_2,undefined1 *param_3,ulonglong param_4);
void .text$_ZNSs6insertEyRKSs(ulonglong *param_1,ulonglong param_2,undefined8 *param_3);
void .text$_ZNSs6insertEyRKSsyy(ulonglong *param_1,ulonglong param_2,longlong *param_3,ulonglong param_4,ulonglong param_5);
void .text$_ZNSs6insertEyyc(longlong *param_1,ulonglong param_2,ulonglong param_3,char param_4);
void .text$_ZNSs6rbeginEv(longlong *param_1,longlong *param_2);
void .text$_ZNSs6resizeEy(longlong *param_1,ulonglong param_2);
void .text$_ZNSs6resizeEyc(longlong *param_1,ulonglong param_2,char param_3);
void .text$_ZNSs7_M_copyEPcPKcy(undefined1 *param_1,undefined1 *param_2,size_t param_3);
undefined8 .text$_ZNSs7_M_dataEPc(undefined8 *param_1,undefined8 param_2);
void .text$_ZNSs7_M_leakEv(longlong *param_1);
void .text$_ZNSs7_M_moveEPcPKcy(undefined1 *param_1,undefined1 *param_2,size_t param_3);
void .text$_ZNSs7replaceEN9__gnu_cxx17__normal_iteratorIPcSsEES2_NS0_IPKcSsEES5_(ulonglong *param_1,longlong param_2,longlong param_3,undefined1 *param_4,longlong param_5);
void .text$_ZNSs7replaceEN9__gnu_cxx17__normal_iteratorIPcSsEES2_PKc(ulonglong *param_1,longlong param_2,longlong param_3,char *param_4);
void .text$_ZNSs7replaceEN9__gnu_cxx17__normal_iteratorIPcSsEES2_PKcS4_(ulonglong *param_1,longlong param_2,longlong param_3,undefined1 *param_4,longlong param_5);
void .text$_ZNSs7replaceEN9__gnu_cxx17__normal_iteratorIPcSsEES2_PKcy(ulonglong *param_1,longlong param_2,longlong param_3,undefined1 *param_4,ulonglong param_5);
void .text$_ZNSs7replaceEN9__gnu_cxx17__normal_iteratorIPcSsEES2_RKSs(ulonglong *param_1,longlong param_2,longlong param_3,undefined8 *param_4);
void .text$_ZNSs7replaceEN9__gnu_cxx17__normal_iteratorIPcSsEES2_S1_S1_(ulonglong *param_1,longlong param_2,longlong param_3,undefined1 *param_4,longlong param_5);
void .text$_ZNSs7replaceEN9__gnu_cxx17__normal_iteratorIPcSsEES2_S2_S2_(ulonglong *param_1,longlong param_2,longlong param_3,undefined1 *param_4,longlong param_5);
void .text$_ZNSs7replaceEN9__gnu_cxx17__normal_iteratorIPcSsEES2_St16initializer_listIcE(ulonglong *param_1,longlong param_2,longlong param_3,undefined8 *param_4);
void .text$_ZNSs7replaceEN9__gnu_cxx17__normal_iteratorIPcSsEES2_yc(longlong *param_1,longlong param_2,longlong param_3,ulonglong param_4,char param_5);
void .text$_ZNSs7replaceEyyPKc(ulonglong *param_1,ulonglong param_2,ulonglong param_3,char *param_4);
ulonglong *.text$_ZNSs7replaceEyyPKcy(ulonglong *param_1,ulonglong param_2,ulonglong param_3,undefined1 *param_4,ulonglong param_5);
void .text$_ZNSs7replaceEyyRKSs(ulonglong *param_1,ulonglong param_2,ulonglong param_3,undefined8 *param_4);
void .text$_ZNSs7replaceEyyRKSsyy(ulonglong *param_1,ulonglong param_2,ulonglong param_3,longlong *param_4,ulonglong param_5,ulonglong param_6);
void .text$_ZNSs7replaceEyyyc(longlong *param_1,ulonglong param_2,ulonglong param_3,ulonglong param_4,char param_5);
void .text$_ZNSs7reserveEv(longlong *param_1);
void .text$_ZNSs7reserveEy(longlong *param_1,ulonglong param_2);
void .text$_ZNSs8pop_backEv(longlong *param_1);
void .text$_ZNSs9_M_assignEPcyc(char *param_1,size_t param_2,char param_3);
void .text$_ZNSs9_M_mutateEyyy(longlong *param_1,size_t param_2,longlong param_3,longlong param_4);
void .text$_ZNSs9push_backEc(longlong *param_1,undefined1 param_2);
void __thiscall .text$_ZNSsC1EOSs(void *this,longlong *param_1);
void __thiscall .text$_ZNSsC1EOSsRKSaIcE(void *this,undefined8 *param_1);
void __thiscall .text$_ZNSsC1EPKcRKSaIcE(void *this,char *param_1);
void __thiscall .text$_ZNSsC1EPKcyRKSaIcE(void *this,undefined1 *param_1,longlong param_2);
void __thiscall .text$_ZNSsC1ERKSaIcE(void *this);
void __thiscall .text$_ZNSsC1ERKSs(void *this,longlong *param_1);
void __thiscall .text$_ZNSsC1ERKSsRKSaIcE(void *this,longlong *param_1,undefined8 param_2);
void __thiscall .text$_ZNSsC1ERKSsyRKSaIcE(void *this,longlong *param_1,ulonglong param_2);
void __thiscall.text$_ZNSsC1ERKSsyy(void *this,longlong *param_1,ulonglong param_2,ulonglong param_3);
void __thiscall.text$_ZNSsC1ERKSsyyRKSaIcE(void *this,longlong *param_1,ulonglong param_2,ulonglong param_3);
void __thiscall .text$_ZNSsC1ESt16initializer_listIcERKSaIcE(void *this,undefined8 *param_1);
void __thiscall .text$_ZNSsC1Ev(void *this);
void __thiscall .text$_ZNSsC1EycRKSaIcE(void *this,ulonglong param_1,char param_2);
void __thiscall.text$_ZNSsC1IN9__gnu_cxx17__normal_iteratorIPcSsEEEET_S4_RKSaIcE(void *this,undefined1 *param_1,longlong param_2);
void __thiscall .text$_ZNSsC1IPKcEET_S2_RKSaIcE(void *this,undefined1 *param_1,longlong param_2);
void __thiscall .text$_ZNSsC1IPcEET_S1_RKSaIcE(void *this,undefined1 *param_1,longlong param_2);
void __thiscall .text$_ZNSsC2EOSs(void *this,longlong *param_1);
void __thiscall .text$_ZNSsC2EOSsRKSaIcE(void *this,undefined8 *param_1);
void __thiscall .text$_ZNSsC2EPKcRKSaIcE(void *this,char *param_1);
void __thiscall .text$_ZNSsC2EPKcyRKSaIcE(void *this,undefined1 *param_1,longlong param_2);
void __thiscall .text$_ZNSsC2ERKSaIcE(void *this);
void __thiscall .text$_ZNSsC2ERKSs(void *this,longlong *param_1);
void __thiscall .text$_ZNSsC2ERKSsRKSaIcE(void *this,longlong *param_1,undefined8 param_2);
void __thiscall .text$_ZNSsC2ERKSsyRKSaIcE(void *this,longlong *param_1,ulonglong param_2);
void __thiscall.text$_ZNSsC2ERKSsyy(void *this,longlong *param_1,ulonglong param_2,ulonglong param_3);
void __thiscall.text$_ZNSsC2ERKSsyyRKSaIcE(void *this,longlong *param_1,ulonglong param_2,ulonglong param_3);
void __thiscall .text$_ZNSsC2ESt16initializer_listIcERKSaIcE(void *this,undefined8 *param_1);
void __thiscall .text$_ZNSsC2Ev(void *this);
void __thiscall .text$_ZNSsC2EycRKSaIcE(void *this,ulonglong param_1,char param_2);
void __thiscall.text$_ZNSsC2IN9__gnu_cxx17__normal_iteratorIPcSsEEEET_S4_RKSaIcE(void *this,undefined1 *param_1,longlong param_2);
void __thiscall .text$_ZNSsC2IPKcEET_S2_RKSaIcE(void *this,undefined1 *param_1,longlong param_2);
void __thiscall .text$_ZNSsC2IPcEET_S1_RKSaIcE(void *this,undefined1 *param_1,longlong param_2);
void __thiscall .text$_ZNSsD1Ev(void *this);
void __thiscall .text$_ZNSsD2Ev(void *this);
void * __thiscall .text$_ZNSsaSEOSs(void *this,longlong *param_1);
void __thiscall .text$_ZNSsaSEPKc(void *this,char *param_1);
void * __thiscall .text$_ZNSsaSERKSs(void *this,longlong *param_1);
void * __thiscall .text$_ZNSsaSESt16initializer_listIcE(void *this,undefined8 *param_1);
void * __thiscall .text$_ZNSsaSEc(void *this,char param_1);
longlong .text$_ZNSsixEy(longlong *param_1,longlong param_2);
void __thiscall .text$_ZNSspLEPKc(void *this,char *param_1);
void * __thiscall .text$_ZNSspLERKSs(void *this,longlong *param_1);
void __thiscall .text$_ZNSspLESt16initializer_listIcE(void *this,undefined8 *param_1);
void __thiscall .text$_ZNSspLEc(void *this,undefined1 param_1);
longlong *.text$_ZNSt10_HashtableIySt4pairIKyN9realsmoke17D3D12DepthCapture12CommandStateEESaIS5_ENSt8__detail10_Select1stESt8equal_toIyESt4hashIyENS7_18_Mod_range_hashingENS7_20_Default_ranged_hashENS7_20_Prime_rehash_policyENS7_17_Hashtable_traitsILb0ELb0ELb1EEEE21_M_insert_unique_nodeEyyPNS7_10_Hash_nodeIS5_Lb0EEEy(longlong *param_1,longlong param_2,ulonglong param_3,longlong *param_4,longlong param_5);
longlong .text$_ZNSt10_HashtableIySt4pairIKyN9realsmoke17D3D12DepthCapture12ResourceInfoEESaIS5_ENSt8__detail10_Select1stESt8equal_toIyESt4hashIyENS7_18_Mod_range_hashingENS7_20_Default_ranged_hashENS7_20_Prime_rehash_policyENS7_17_Hashtable_traitsILb0ELb0ELb1EEEE4findERS1_(longlong *param_1,ulonglong *param_2);
longlong .text$_ZNSt10_HashtableIySt4pairIKyyESaIS2_ENSt8__detail10_Select1stESt8equal_toIyESt4hashIyENS4_18_Mod_range_hashingENS4_20_Default_ranged_hashENS4_20_Prime_rehash_policyENS4_17_Hashtable_traitsILb0ELb0ELb1EEEE4findERS1_(longlong *param_1,ulonglong *param_2);
longlong .text$_ZNSt10_HashtableIySt4pairIKyyESaIS2_ENSt8__detail10_Select1stESt8equal_toIyESt4hashIyENS4_18_Mod_range_hashingENS4_20_Default_ranged_hashENS4_20_Prime_rehash_policyENS4_17_Hashtable_traitsILb0ELb0ELb1EEEE8_M_eraseEyPNS4_15_Hash_node_baseEPNS4_10_Hash_nodeIS2_Lb0EEE(longlong *param_1,ulonglong param_2,longlong *param_3,longlong *param_4);
void __thiscall std::bad_typeid::~bad_typeid(bad_typeid *this);
void __thiscall std::bad_typeid::~bad_typeid(bad_typeid *this);
void __thiscall std::logic_error::logic_error(logic_error *this,longlong param_1);
void __thiscall std::logic_error::logic_error(logic_error *this,char *param_1);
void __thiscall std::logic_error::logic_error(logic_error *this,undefined8 *param_1);
void __thiscall std::logic_error::logic_error(logic_error *this,longlong param_1);
void __thiscall std::logic_error::logic_error(logic_error *this,longlong *param_1);
void __thiscall std::logic_error::~logic_error(logic_error *this);
void __thiscall std::logic_error::~logic_error(logic_error *this);
logic_error * __thiscall std::logic_error::operator=(logic_error *this,longlong param_1);
logic_error * __thiscall std::logic_error::operator=(logic_error *this,longlong param_1);
void __thiscall std::range_error::range_error(range_error *this,char *param_1);
void __thiscall std::range_error::range_error(range_error *this,undefined8 *param_1);
void __thiscall std::range_error::range_error(range_error *this,longlong *param_1);
void __thiscall std::range_error::~range_error(range_error *this);
void __thiscall std::range_error::~range_error(range_error *this);
int std::(anonymous_namespace)::__x86_rdrand(void);
ulonglong std::(anonymous_namespace)::__x86_rdseed(undefined *param_1);
undefined4 std::(anonymous_namespace)::__winxp_rand_s(void);
int std::(anonymous_namespace)::__x86_rdseed_rdrand(void);
void __thiscall std::__cow_string::__cow_string(__cow_string *this,longlong *param_1);
void __thiscall std::__cow_string::__cow_string(__cow_string *this,char *param_1);
void __thiscall std::__cow_string::__cow_string(__cow_string *this,undefined1 *param_1,ulonglong param_2);
void __thiscall std::__cow_string::__cow_string(__cow_string *this,undefined8 *param_1);
void __thiscall std::__cow_string::__cow_string(__cow_string *this,longlong *param_1);
void __thiscall std::__cow_string::__cow_string(__cow_string *this,longlong *param_1);
void __thiscall std::__cow_string::__cow_string(__cow_string *this);
void __thiscall std::__cow_string::~__cow_string(__cow_string *this);
__cow_string * __thiscall std::__cow_string::operator=(__cow_string *this,longlong *param_1);
__cow_string * __thiscall std::__cow_string::operator=(__cow_string *this,longlong *param_1);
void __thiscall std::__sso_string::__sso_string(__sso_string *this,longlong *param_1);
void __thiscall std::__sso_string::__sso_string(__sso_string *this,__sso_string *param_1,ulonglong param_2);
void __thiscall std::__sso_string::__sso_string(__sso_string *this,undefined8 *param_1);
void __thiscall std::__sso_string::__sso_string(__sso_string *this,undefined8 *param_1);
void __thiscall std::__sso_string::__sso_string(__sso_string *this,undefined8 *param_1);
void __thiscall std::__sso_string::__sso_string(__sso_string *this);
void __thiscall std::__sso_string::~__sso_string(__sso_string *this);
__sso_string * __thiscall std::__sso_string::operator=(__sso_string *this,__sso_string *param_1);
__sso_string * __thiscall std::__sso_string::operator=(__sso_string *this,undefined8 *param_1);
void __thiscall std::domain_error::domain_error(domain_error *this,char *param_1);
void __thiscall std::domain_error::domain_error(domain_error *this,undefined8 *param_1);
void __thiscall std::domain_error::domain_error(domain_error *this,longlong *param_1);
void __thiscall std::domain_error::~domain_error(domain_error *this);
void __thiscall std::domain_error::~domain_error(domain_error *this);
void __thiscall std::length_error::length_error(length_error *this,char *param_1);
void __thiscall std::length_error::length_error(length_error *this,undefined8 *param_1);
void __thiscall std::length_error::length_error(length_error *this,longlong *param_1);
void __thiscall std::length_error::~length_error(length_error *this);
void __thiscall std::length_error::~length_error(length_error *this);
void __thiscall std::out_of_range::out_of_range(out_of_range *this,char *param_1);
void __thiscall std::out_of_range::out_of_range(out_of_range *this,undefined8 *param_1);
void __thiscall std::out_of_range::out_of_range(out_of_range *this,longlong *param_1);
void __thiscall std::out_of_range::~out_of_range(out_of_range *this);
void __thiscall std::out_of_range::~out_of_range(out_of_range *this);
void __thiscall.text$_ZNSt12system_errorC1ESt10error_codePKc(void *this,undefined8 *param_1,char *param_2);
void __thiscall std::system_error::~system_error(system_error *this);
void __thiscall std::system_error::~system_error(system_error *this);
void __thiscall std::bad_exception::~bad_exception(bad_exception *this);
void __thiscall std::bad_exception::~bad_exception(void);
void __thiscall std::random_device::_M_init_pretr1(random_device *this,undefined8 *param_1);
void __thiscall std::random_device::_M_init_pretr1(random_device *this,undefined8 *param_1);
ulonglong __thiscall std::random_device::_M_getval_pretr1(random_device *this);
void std::random_device::_M_fini(void);
void __thiscall std::random_device::_M_init(random_device *this,undefined1 *param_1,longlong param_2);
void __thiscall std::random_device::_M_init(random_device *this,undefined8 *param_1);
void __thiscall std::random_device::_M_init(random_device *this,undefined8 *param_1);
ulonglong __thiscall std::random_device::_M_getval(random_device *this);
void __thiscall std::runtime_error::runtime_error(runtime_error *this,longlong param_1);
void __thiscall std::runtime_error::runtime_error(runtime_error *this,char *param_1);
void __thiscall std::runtime_error::runtime_error(runtime_error *this,undefined8 *param_1);
void __thiscall std::runtime_error::runtime_error(runtime_error *this,longlong param_1);
void __thiscall std::runtime_error::runtime_error(runtime_error *this,longlong *param_1);
void __thiscall std::runtime_error::~runtime_error(runtime_error *this);
void __thiscall std::runtime_error::~runtime_error(runtime_error *this);
runtime_error * __thiscall std::runtime_error::operator=(runtime_error *this,longlong param_1);
runtime_error * __thiscall std::runtime_error::operator=(runtime_error *this,longlong param_1);
void __thiscall std::overflow_error::overflow_error(overflow_error *this,char *param_1);
void __thiscall std::overflow_error::overflow_error(overflow_error *this,undefined8 *param_1);
void __thiscall std::overflow_error::overflow_error(overflow_error *this,longlong *param_1);
void __thiscall std::overflow_error::~overflow_error(overflow_error *this);
void __thiscall std::overflow_error::~overflow_error(overflow_error *this);
void __thiscall std::underflow_error::underflow_error(underflow_error *this,char *param_1);
void __thiscall std::underflow_error::underflow_error(underflow_error *this,undefined8 *param_1);
void __thiscall std::underflow_error::underflow_error(underflow_error *this,longlong *param_1);
void __thiscall std::underflow_error::~underflow_error(underflow_error *this);
void __thiscall std::underflow_error::~underflow_error(underflow_error *this);
void __thiscall std::invalid_argument::invalid_argument(invalid_argument *this,char *param_1);
void __thiscall std::invalid_argument::invalid_argument(invalid_argument *this,undefined8 *param_1);
void __thiscall std::invalid_argument::invalid_argument(invalid_argument *this,longlong *param_1);
void __thiscall std::invalid_argument::~invalid_argument(invalid_argument *this);
void __thiscall std::invalid_argument::~invalid_argument(invalid_argument *this);
void __thiscall std::bad_array_new_length::~bad_array_new_length(bad_array_new_length *this);
void __thiscall std::bad_array_new_length::~bad_array_new_length(bad_array_new_length *this);
void __thiscall std::_V2::error_category::~error_category(error_category *this);
void __thiscall std::_V2::error_category::~error_category(void);
undefined ** std::_V2::system_category(void);
undefined ** std::_V2::generic_category(void);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_destroyEy(undefined8 *param_1);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv(undefined8 *param_1);
ulonglong *.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEyyPKcy(ulonglong *param_1,size_t param_2,ulonglong param_3,undefined8 *param_4,ulonglong param_5);
ulonglong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_S_compareEyy(longlong param_1,longlong param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE11_M_capacityEy(longlong param_1,undefined8 param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE11_S_allocateERS3_y(undefined8 param_1,size_t param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_Alloc_hiderC1EPcOS3_(void *this,undefined8 param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_Alloc_hiderC1EPcRKS3_(void *this,undefined8 param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_Alloc_hiderC2EPcOS3_(void *this,undefined8 param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_Alloc_hiderC2EPcRKS3_(void *this,undefined8 param_1);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructEyc(longlong *param_1,ulonglong param_2,char param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructILb0EEEvPKcy(longlong *param_1,undefined1 *param_2,ulonglong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructILb1EEEvPKcy(undefined8 *param_1,undefined1 *param_2,ulonglong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIN9__gnu_cxx17__normal_iteratorIPKcS4_EEEEvT_SB_St20forward_iterator_tag(undefined8 *param_1,undefined1 *param_2,longlong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIN9__gnu_cxx17__normal_iteratorIPcS4_EEEEvT_SA_St20forward_iterator_tag(undefined8 *param_1,undefined1 *param_2,longlong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPKcEEvT_S8_St20forward_iterator_tag(undefined8 *param_1,undefined1 *param_2,longlong param_3);
void std::__cxx11::string::_M_construct<>(undefined8 *param_1,undefined1 *param_2,longlong param_3);
void std::__cxx11::string::_M_construct<>(undefined8 *param_1,undefined1 *param_2,longlong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag(undefined8 *param_1,undefined1 *param_2,longlong param_3);
longlong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13_M_local_dataEv(longlong param_1);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13_M_set_lengthEy(longlong *param_1,longlong param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13_S_copy_charsEPcN9__gnu_cxx17__normal_iteratorIPKcS4_EESA_(undefined1 *param_1,undefined1 *param_2,longlong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13_S_copy_charsEPcN9__gnu_cxx17__normal_iteratorIS5_S4_EES8_(undefined1 *param_1,undefined1 *param_2,longlong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13_S_copy_charsEPcPKcS7_(undefined1 *param_1,undefined1 *param_2,longlong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13_S_copy_charsEPcS5_S5_(undefined1 *param_1,undefined1 *param_2,longlong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13shrink_to_fitEv(longlong *param_1);
longlong *.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE14_M_replace_auxEyyyc(longlong *param_1,size_t param_2,ulonglong param_3,ulonglong param_4,char param_5);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE15_M_replace_coldEPcyPKcyy(undefined8 param_1,undefined8 *param_2,ulonglong param_3,undefined8 *param_4,ulonglong param_5,ulonglong param_6);
undefined8.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE16_M_get_allocatorEv(undefined8 param_1);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE17_M_init_local_bufEv(void);
longlong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE17_M_use_local_dataEv(longlong param_1);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE18_M_construct_aux_2Eyc(longlong *param_1,ulonglong param_2,char param_3);
longlong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE2atEy(longlong *param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4);
longlong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE3endEv(longlong *param_1);
longlong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4backEv(longlong *param_1);
undefined8 *.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4rendEv(undefined8 *param_1,undefined8 *param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4swapERS4_(undefined8 *param_1,undefined8 *param_2);
undefined8 .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5beginEv(undefined8 *param_1);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5clearEv(undefined8 *param_1);
longlong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5eraseEN9__gnu_cxx17__normal_iteratorIPKcS4_EE(longlong *param_1,longlong param_2);
longlong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5eraseEN9__gnu_cxx17__normal_iteratorIPKcS4_EES9_(longlong *param_1,undefined1 *param_2,longlong param_3);
longlong *.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5eraseEyy(longlong *param_1,ulonglong param_2,ulonglong param_3);
undefined8 .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5frontEv(undefined8 *param_1);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendEPKc(longlong *param_1,char *param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendEPKcy(longlong *param_1,undefined1 *param_2,ulonglong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendERKS4_(longlong *param_1,undefined8 *param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendERKS4_yy(longlong *param_1,longlong *param_2,ulonglong param_3,ulonglong param_4);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendESt16initializer_listIcE(longlong *param_1,undefined8 *param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendEyc(longlong *param_1,ulonglong param_2,char param_3);
undefined8 *.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6assignEOS4_(undefined8 *param_1,undefined8 *param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6assignEPKc(ulonglong *param_1,char *param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6assignEPKcy(ulonglong *param_1,undefined8 *param_2,ulonglong param_3);
undefined8 *.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6assignERKS4_(undefined8 *param_1,undefined8 *param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6assignERKS4_yy(ulonglong *param_1,longlong *param_2,ulonglong param_3,ulonglong param_4);
undefined8 *.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6assignESt16initializer_listIcE(undefined8 *param_1,undefined8 *param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6assignEyc(longlong *param_1,ulonglong param_2,char param_3);
longlong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6insertEN9__gnu_cxx17__normal_iteratorIPKcS4_EESt16initializer_listIcE(ulonglong *param_1,longlong param_2,undefined8 *param_3);
longlong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6insertEN9__gnu_cxx17__normal_iteratorIPKcS4_EEc(longlong *param_1,longlong param_2,char param_3);
longlong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6insertEN9__gnu_cxx17__normal_iteratorIPKcS4_EEyc(longlong *param_1,longlong param_2,ulonglong param_3,char param_4);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6insertEN9__gnu_cxx17__normal_iteratorIPcS4_EESt16initializer_listIcE(ulonglong *param_1,longlong param_2,undefined8 *param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6insertEyPKc(ulonglong *param_1,ulonglong param_2,char *param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6insertEyPKcy(ulonglong *param_1,ulonglong param_2,undefined8 *param_3,ulonglong param_4);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6insertEyRKS4_(ulonglong *param_1,ulonglong param_2,undefined8 *param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6insertEyRKS4_yy(ulonglong *param_1,ulonglong param_2,longlong *param_3,ulonglong param_4,ulonglong param_5);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6insertEyyc(longlong *param_1,ulonglong param_2,ulonglong param_3,char param_4);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6rbeginEv(longlong *param_1,longlong *param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6resizeEy(longlong *param_1,ulonglong param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6resizeEyc(longlong *param_1,ulonglong param_2,char param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7_M_dataEPc(undefined8 *param_1,undefined8 param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7_S_copyEPcPKcy(undefined1 *param_1,undefined1 *param_2,size_t param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7_S_moveEPcPKcy(undefined1 *param_1,undefined1 *param_2,size_t param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEN9__gnu_cxx17__normal_iteratorIPKcS4_EES9_NS6_IPcS4_EESB_(ulonglong *param_1,longlong param_2,longlong param_3,undefined8 *param_4,longlong param_5);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEN9__gnu_cxx17__normal_iteratorIPKcS4_EES9_PcSA_(ulonglong *param_1,longlong param_2,longlong param_3,undefined8 *param_4,longlong param_5);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEN9__gnu_cxx17__normal_iteratorIPKcS4_EES9_RKS4_(ulonglong *param_1,longlong param_2,longlong param_3,undefined8 *param_4);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEN9__gnu_cxx17__normal_iteratorIPKcS4_EES9_S8_(ulonglong *param_1,longlong param_2,longlong param_3,char *param_4);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEN9__gnu_cxx17__normal_iteratorIPKcS4_EES9_S8_S8_(ulonglong *param_1,longlong param_2,longlong param_3,undefined8 *param_4,longlong param_5);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEN9__gnu_cxx17__normal_iteratorIPKcS4_EES9_S8_y(ulonglong *param_1,longlong param_2,longlong param_3,undefined8 *param_4,ulonglong param_5);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEN9__gnu_cxx17__normal_iteratorIPKcS4_EES9_S9_S9_(ulonglong *param_1,longlong param_2,longlong param_3,undefined8 *param_4,longlong param_5);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEN9__gnu_cxx17__normal_iteratorIPKcS4_EES9_St16initializer_listIcE(ulonglong *param_1,longlong param_2,longlong param_3,undefined8 *param_4);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEN9__gnu_cxx17__normal_iteratorIPKcS4_EES9_yc(longlong *param_1,longlong param_2,longlong param_3,ulonglong param_4,char param_5);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEyyPKc(ulonglong *param_1,ulonglong param_2,ulonglong param_3,char *param_4);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEyyPKcy(ulonglong *param_1,ulonglong param_2,ulonglong param_3,undefined8 *param_4,ulonglong param_5);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEyyRKS4_(ulonglong *param_1,ulonglong param_2,ulonglong param_3,undefined8 *param_4);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEyyRKS4_yy(ulonglong *param_1,ulonglong param_2,ulonglong param_3,longlong *param_4,ulonglong param_5,ulonglong param_6);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEyyyc(longlong *param_1,ulonglong param_2,ulonglong param_3,ulonglong param_4,char param_5);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7reserveEv(longlong *param_1);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7reserveEy(undefined8 *param_1,ulonglong param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE8_M_eraseEyy(longlong *param_1,longlong param_2,longlong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE8pop_backEv(longlong *param_1);
longlong *.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_appendEPKcy(longlong *param_1,undefined1 *param_2,size_t param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_assignERKS4_(undefined8 *param_1,undefined8 *param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERyy(undefined8 param_1,ulonglong *param_2,ulonglong param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_lengthEy(longlong param_1,undefined8 param_2);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEyyPKcy(longlong *param_1,size_t param_2,longlong param_3,undefined1 *param_4,size_t param_5);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_S_assignEPcyc(char *param_1,size_t param_2,char param_3);
void .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9push_backEc(longlong *param_1,undefined1 param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EOS4_(void *this,longlong *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EOS4_RKS3_(void *this,undefined8 *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_(void *this,char *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcyRKS3_(void *this,undefined1 *param_1,longlong param_2);
void __thiscall .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS3_(void *this);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_(void *this,undefined8 *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_RKS3_(void *this,undefined8 *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_yRKS3_(void *this,longlong *param_1,ulonglong param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_yy(void *this,longlong *param_1,ulonglong param_2,ulonglong param_3);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_yyRKS3_(void *this,longlong *param_1,ulonglong param_2,ulonglong param_3);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ESt16initializer_listIcERKS3_(void *this,undefined8 *param_1);
void __thiscall .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1Ev(void *this);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EycRKS3_(void *this,ulonglong param_1,char param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IN9__gnu_cxx17__normal_iteratorIPcS4_EEvEET_SA_RKS3_(void *this,undefined1 *param_1,longlong param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IPKcvEET_S8_RKS3_(void *this,undefined1 *param_1,longlong param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IPcvEET_S7_RKS3_(void *this,undefined1 *param_1,longlong param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EOS4_(void *this,longlong *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EOS4_RKS3_(void *this,undefined8 *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_(void *this,char *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcyRKS3_(void *this,undefined1 *param_1,longlong param_2);
void __thiscall .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2ERKS3_(void *this);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2ERKS4_(void *this,undefined8 *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2ERKS4_RKS3_(void *this,undefined8 *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2ERKS4_yRKS3_(void *this,longlong *param_1,ulonglong param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2ERKS4_yy(void *this,longlong *param_1,ulonglong param_2,ulonglong param_3);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2ERKS4_yyRKS3_(void *this,longlong *param_1,ulonglong param_2,ulonglong param_3);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2ESt16initializer_listIcERKS3_(void *this,undefined8 *param_1);
void __thiscall .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2Ev(void *this);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EycRKS3_(void *this,ulonglong param_1,char param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IN9__gnu_cxx17__normal_iteratorIPcS4_EEvEET_SA_RKS3_(void *this,undefined1 *param_1,longlong param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IPKcvEET_S8_RKS3_(void *this,undefined1 *param_1,longlong param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IPcvEET_S7_RKS3_(void *this,undefined1 *param_1,longlong param_2);
void __thiscall .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev(void *this);
void __thiscall .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev(void *this);
void * __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEaSEOS4_(void *this,undefined8 *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEaSEPKc(void *this,char *param_1);
void * __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEaSERKS4_(void *this,undefined8 *param_1);
void * __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEaSESt16initializer_listIcE(void *this,undefined8 *param_1);
void * __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEaSEc(void *this,char param_1);
longlong .text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEy(longlong *param_1,longlong param_2);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEpLEPKc(void *this,char *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEpLERKS4_(void *this,undefined8 *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEpLESt16initializer_listIcE(void *this,undefined8 *param_1);
void __thiscall.text$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEpLEc(void *this,undefined1 param_1);
longlong *.text$_ZNSt8__detail9_Map_baseIySt4pairIKyN9realsmoke17D3D12DepthCapture12PipelineInfoEESaIS6_ENS_10_Select1stESt8equal_toIyESt4hashIyENS_18_Mod_range_hashingENS_20_Default_ranged_hashENS_20_Prime_rehash_policyENS_17_Hashtable_traitsILb0ELb0ELb1EEELb1EEixERS2_(longlong *param_1,ulonglong *param_2);
longlong *.text$_ZNSt8__detail9_Map_baseIySt4pairIKyN9realsmoke17D3D12DepthCapture12ResourceInfoEESaIS6_ENS_10_Select1stESt8equal_toIyESt4hashIyENS_18_Mod_range_hashingENS_20_Default_ranged_hashENS_20_Prime_rehash_policyENS_17_Hashtable_traitsILb0ELb0ELb1EEELb1EEixERS2_(longlong *param_1,ulonglong *param_2);
void __thiscall std::bad_cast::~bad_cast(bad_cast *this);
void __thiscall std::bad_cast::~bad_cast(bad_cast *this);
void __thiscall std::bad_alloc::~bad_alloc(bad_alloc *this);
void __thiscall std::bad_alloc::~bad_alloc(bad_alloc *this);
void __thiscall std::exception::~exception(exception *this);
void __thiscall std::exception::~exception(void);
void __thiscall std::type_info::~type_info(type_info *this);
void __thiscall std::type_info::~type_info(void);
undefined * std::get_terminate(void);
undefined * std::set_terminate(undefined *param_1);
undefined * std::get_unexpected(void);
undefined * std::set_unexpected(undefined *param_1);
undefined8 std::get_new_handler(void);
undefined8 std::set_new_handler(undefined8 param_1);
undefined4 std::uncaught_exception(void);
undefined4 std::uncaught_exceptions(void);
longlong *.text$_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEPKS5_RKS8_(longlong *param_1,char *param_2,undefined8 *param_3);
longlong *.text$_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_SA_(longlong *param_1,undefined8 *param_2,undefined8 *param_3);
longlong *.text$_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EES5_RKS8_(longlong *param_1,undefined1 param_2,undefined8 *param_3);
longlong *.text$_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_(longlong *param_1,char *param_2,undefined8 *param_3);
longlong *.text$_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_S8_(longlong *param_1,undefined8 *param_2,undefined8 *param_3);
longlong *.text$_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ES3_RKS6_(longlong *param_1,undefined1 param_2,undefined8 *param_3);
void operator.delete(void *param_1);
void operator.delete(void *param_1);
void * operator.new(size_t param_1);
void __cxa_allocate_dependent_exception(void);
ulonglong * __cxa_allocate_exception(longlong param_1);
longlong __cxa_begin_catch(longlong *param_1);
void __cxa_call_unexpected(longlong *param_1);
longlong __cxa_current_exception_type(void);
void __cxa_end_catch(void);
void __cxa_free_dependent_exception(void *param_1);
void __cxa_free_exception(longlong param_1);
undefined8 __cxa_get_exception_ptr(longlong param_1);
longlong __cxa_get_globals(void);
longlong __cxa_get_globals_fast(void);
ulonglong __cxa_guard_abort(longlong param_1);
ulonglong __cxa_guard_acquire(char *param_1);
longlong * __cxa_guard_release(undefined1 *param_1,undefined8 param_2,longlong param_3);
longlong __cxa_init_primary_exception(longlong param_1,undefined8 param_2,undefined8 param_3);
void __cxa_rethrow(void);
void __cxa_throw(longlong param_1,undefined8 param_2,undefined8 param_3);
void __gxx_personality_seh0(PEXCEPTION_RECORD param_1,PVOID param_2,PCONTEXT param_3,ULONG_PTR *param_4);
void __tcf_ZN12_GLOBAL__N_1L14emergency_poolE(void);
void __tcf_ZN12_GLOBAL__N_1L24system_category_instanceE(void);
void __tcf_ZN12_GLOBAL__N_1L25generic_category_instanceE(void);
void std::terminate(void);
void std::unexpected(void);
void std::__throw_bad_exception(void);
void std::__throw_bad_alloc(void);
void std::__throw_bad_array_new_length(void);
void std::__throw_bad_cast(void);
void std::__throw_bad_typeid(void);
void std::__throw_logic_error(char *param_1);
void std::__throw_domain_error(char *param_1);
void std::__throw_invalid_argument(char *param_1);
void std::__throw_length_error(char *param_1);
void std::__throw_out_of_range(char *param_1);
void std::__throw_out_of_range_fmt(char *param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4,...);
void std::__throw_runtime_error(char *param_1);
void std::__throw_range_error(char *param_1);
void std::__throw_overflow_error(char *param_1);
void std::__throw_underflow_error(char *param_1);
void __gnu_cxx::__throw_insufficient_space(undefined1 *param_1,longlong param_2);
void std::__throw_system_error(DWORD param_1);
void std::_GLOBAL__sub_I___throw_system_error(void);
void d_type.cold(void);
void __gnu_cxx::__freeres(void);
void __gnu_cxx::_GLOBAL__sub_I___freeres(void);
void __cxa_call_terminate(longlong *param_1);
void std::(anonymous_namespace)::__throw_syserr(uint param_1,char *param_2);
void init(void);
void winpthreads_init(void);
void __cdecl pthread_tls_init.cold(void);
void __cdecl _pthread_once_raw.part.0.constprop.0.isra.0.cold(void);
void __cdecl __pthread_self_lite.cold(void);
void pthread_once.cold(undefined8 param_1,undefined8 param_2);
void register_frame_ctor(void);

