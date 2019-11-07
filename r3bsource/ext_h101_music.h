/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_MUSIC_EXT_H101_H__
#define __GUARD_H101_MUSIC_EXT_H101_H__

#ifndef __CINT__
#include <stdint.h>
#else
/* For CINT (old version trouble with stdint.h): */
#ifndef uint32_t
typedef unsigned int uint32_t;
typedef int int32_t;
#endif
#endif
#ifndef EXT_STRUCT_CTRL
#define EXT_STRUCT_CTRL(x)
#endif

/********************************************************
 *
 * Plain structure (layout as ntuple/root file):
 */

typedef struct EXT_STR_h101_MUSIC_t
{
    /* RAW */
    uint32_t MUSIC_EM /* [1,8] */;
    uint32_t MUSIC_EMI[8 EXT_STRUCT_CTRL(MUSIC_EM)] /* [1,8] */;
    uint32_t MUSIC_EME[8 EXT_STRUCT_CTRL(MUSIC_EM)] /* [1,80] */;
    uint32_t MUSIC_E /* [0,80] */;
    uint32_t MUSIC_Ev[80 EXT_STRUCT_CTRL(MUSIC_E)] /* [0,65535] */;
    uint32_t MUSIC_TM /* [1,8] */;
    uint32_t MUSIC_TMI[8 EXT_STRUCT_CTRL(MUSIC_TM)] /* [1,8] */;
    uint32_t MUSIC_TME[8 EXT_STRUCT_CTRL(MUSIC_TM)] /* [1,80] */;
    uint32_t MUSIC_T /* [0,80] */;
    uint32_t MUSIC_Tv[80 EXT_STRUCT_CTRL(MUSIC_T)] /* [0,65535] */;
    uint32_t MUSIC_TREFM /* [1,1] */;
    uint32_t MUSIC_TREFMI[1 EXT_STRUCT_CTRL(MUSIC_TREFM)] /* [1,1] */;
    uint32_t MUSIC_TREFME[1 EXT_STRUCT_CTRL(MUSIC_TREFM)] /* [1,10] */;
    uint32_t MUSIC_TREF /* [0,10] */;
    uint32_t MUSIC_TREFv[10 EXT_STRUCT_CTRL(MUSIC_TREF)] /* [0,65535] */;
    uint32_t MUSIC_TRIG /* [0,65535] */;

} EXT_STR_h101_MUSIC;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_MUSIC_onion_t
{
    /* RAW */
    uint32_t MUSIC_EM;
    uint32_t MUSIC_EMI[8 /* MUSIC_EM */];
    uint32_t MUSIC_EME[8 /* MUSIC_EM */];
    uint32_t MUSIC_E;
    uint32_t MUSIC_Ev[80 /* MUSIC_E */];
    uint32_t MUSIC_TM;
    uint32_t MUSIC_TMI[8 /* MUSIC_TM */];
    uint32_t MUSIC_TME[8 /* MUSIC_TM */];
    uint32_t MUSIC_T;
    uint32_t MUSIC_Tv[80 /* MUSIC_T */];
    uint32_t MUSIC_TREFM;
    uint32_t MUSIC_TREFMI[1 /* MUSIC_TREFM */];
    uint32_t MUSIC_TREFME[1 /* MUSIC_TREFM */];
    uint32_t MUSIC_TREF;
    uint32_t MUSIC_TREFv[10 /* MUSIC_TREF */];
    uint32_t MUSIC_TRIG;

} EXT_STR_h101_MUSIC_onion;

/*******************************************************/

#define EXT_STR_h101_MUSIC_ITEMS_INFO(ok, si, offset, struct_t, printerr)                                            \
    do                                                                                                               \
    {                                                                                                                \
        ok = 1;                                                                                                      \
        /* RAW */                                                                                                    \
        EXT_STR_ITEM_INFO_LIM(ok, si, offset, struct_t, printerr, MUSIC_EM, UINT32, "MUSIC_EM", 8);                  \
        EXT_STR_ITEM_INFO_ZZP(ok, si, offset, struct_t, printerr, MUSIC_EMI, UINT32, "MUSIC_EMI", "MUSIC_EM");       \
        EXT_STR_ITEM_INFO_ZZP(ok, si, offset, struct_t, printerr, MUSIC_EME, UINT32, "MUSIC_EME", "MUSIC_EM");       \
        EXT_STR_ITEM_INFO_LIM(ok, si, offset, struct_t, printerr, MUSIC_E, UINT32, "MUSIC_E", 80);                   \
        EXT_STR_ITEM_INFO_ZZP(ok, si, offset, struct_t, printerr, MUSIC_Ev, UINT32, "MUSIC_Ev", "MUSIC_E");          \
        EXT_STR_ITEM_INFO_LIM(ok, si, offset, struct_t, printerr, MUSIC_TM, UINT32, "MUSIC_TM", 8);                  \
        EXT_STR_ITEM_INFO_ZZP(ok, si, offset, struct_t, printerr, MUSIC_TMI, UINT32, "MUSIC_TMI", "MUSIC_TM");       \
        EXT_STR_ITEM_INFO_ZZP(ok, si, offset, struct_t, printerr, MUSIC_TME, UINT32, "MUSIC_TME", "MUSIC_TM");       \
        EXT_STR_ITEM_INFO_LIM(ok, si, offset, struct_t, printerr, MUSIC_T, UINT32, "MUSIC_T", 80);                   \
        EXT_STR_ITEM_INFO_ZZP(ok, si, offset, struct_t, printerr, MUSIC_Tv, UINT32, "MUSIC_Tv", "MUSIC_T");          \
        EXT_STR_ITEM_INFO_LIM(ok, si, offset, struct_t, printerr, MUSIC_TREFM, UINT32, "MUSIC_TREFM", 1);            \
        EXT_STR_ITEM_INFO_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, MUSIC_TREFMI, UINT32, "MUSIC_TREFMI", "MUSIC_TREFM");                \
        EXT_STR_ITEM_INFO_ZZP(                                                                                       \
            ok, si, offset, struct_t, printerr, MUSIC_TREFME, UINT32, "MUSIC_TREFME", "MUSIC_TREFM");                \
        EXT_STR_ITEM_INFO_LIM(ok, si, offset, struct_t, printerr, MUSIC_TREF, UINT32, "MUSIC_TREF", 10);             \
        EXT_STR_ITEM_INFO_ZZP(ok, si, offset, struct_t, printerr, MUSIC_TREFv, UINT32, "MUSIC_TREFv", "MUSIC_TREF"); \
        EXT_STR_ITEM_INFO_LIM(ok, si, offset, struct_t, printerr, MUSIC_TRIG, UINT32, "MUSIC_TRIG", 65535);          \
                                                                                                                     \
    } while (0);

#endif /*__GUARD_H101_MUSIC_EXT_H101_H__*/

/*******************************************************/
