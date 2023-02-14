#ifdef _WIN32
#define AILCALL        __stdcall
#else
#define AILCALL
#endif

#ifndef C8
#define C8 char
#endif

#ifndef U32
#define U32 unsigned int
#endif

#ifndef S32
#define S32 signed int
#endif

#ifndef UINTa
#define UINTa unsigned int
#endif

typedef U32 HPROVIDER;
typedef S32 RIBRESULT;

typedef enum
{
    RIB_NONE = 0, // No type
    RIB_CUSTOM,   // Used for pointers to application-specific structures
    RIB_DEC,      // Used for 32-bit integer values to be reported in decimal
    RIB_HEX,      // Used for 32-bit integer values to be reported in hex
    RIB_FLOAT,    // Used for 32-bit single-precision FP values
    RIB_PERCENT,  // Used for 32-bit single-precision FP values to be reported as percentages
    RIB_BOOL,     // Used for Boolean-constrained integer values to be reported as TRUE or FALSE
    RIB_STRING,   // Used for pointers to null-terminated ASCII strings
    RIB_READONLY = 0x80000000  // Property is read-only
}
RIB_DATA_SUBTYPE;

typedef enum
{
    RIB_FUNCTION = 0,
    RIB_PROPERTY       // Property: read-only or read-write data type
}
RIB_ENTRY_TYPE;

typedef struct
{
    RIB_ENTRY_TYPE   type;        // See list above
    C8* entry_name;  // Name of desired function or property
    UINTa            token;       // Function pointer or property token
    RIB_DATA_SUBTYPE subtype;     // Property subtype
}
RIB_INTERFACE_ENTRY;


typedef HPROVIDER(*RIB_alloc_provider_handle_ptr) (long module);
typedef RIBRESULT(*RIB_register_interface_ptr) (HPROVIDER  provider, C8 const* interface_name, S32 entry_count, RIB_INTERFACE_ENTRY const* rlist);
typedef RIBRESULT(*RIB_unregister_interface_ptr)  (HPROVIDER  provider, C8 const* interface_name, S32 entry_count, RIB_INTERFACE_ENTRY const* rlist);

extern "C" __declspec(dllexport) BOOL WINAPI RIB_Main(HPROVIDER provider_handle,
    U32 up_down,
    RIB_alloc_provider_handle_ptr RIB_alloc_provider_handle,
    RIB_register_interface_ptr RIB_register_interface,
    RIB_unregister_interface_ptr RIB_unregister_interface
);

