#ifndef STEAM_WRAPPER_H
#define STEAM_WRAPPER_H

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t uint64_steamid; // Used when passing or returning CSteamID
typedef uint64_t uint64_gameid; // Used when passing or return CGameID
enum EFriendFlags {
    k_EFriendFlagNone = 0x00,
    k_EFriendFlagBlocked = 0x01,
    k_EFriendFlagFriendshipRequested = 0x02,
    k_EFriendFlagImmediate = 0x04, // "regular" friend
    k_EFriendFlagClanMember = 0x08,
    k_EFriendFlagOnGameServer = 0x10,
    // k_EFriendFlagHasPlayedWith = 0x20, // not currently used
    // k_EFriendFlagFriendOfFriend = 0x40, // not currently used
    k_EFriendFlagRequestingFriendship = 0x80,
    k_EFriendFlagRequestingInfo = 0x100,
    k_EFriendFlagIgnored = 0x200,
    k_EFriendFlagIgnoredFriend = 0x400,
    // k_EFriendFlagSuggested = 0x800, // not used
    k_EFriendFlagChatMember = 0x1000,
    k_EFriendFlagAll = 0xFFFF,
};

#define STEAM_CLASSES \
    STEAM_CLASS(SteamFriends, v017) \
    STEAM_CLASS(SteamUtils, v010) \
    STEAM_CLASS(SteamUser, v021)

#define STEAM_CLASS(NAME, VERSION) typedef struct I##NAME I##NAME;
STEAM_CLASSES
#undef STEAM_CLASS

#define STEAM_CLASS(NAME, VERSION) extern I##NAME *I##NAME##Ptr;
STEAM_CLASSES
#undef STEAM_CLASS

#define STEAM_CLASS(NAME, VERSION) I##NAME *SteamAPI_##NAME##_##VERSION(void);
STEAM_CLASSES
#undef STEAM_CLASS

#ifdef INCLUDE_SRC

#define STEAM_CLASS(NAME, VERSION) I##NAME *I##NAME##Ptr;
STEAM_CLASSES
#undef STEAM_CLASS

#endif /* INCLUDE_SRC */

#define STEAM_FRIENDS_FUNCTIONS \
    STEAM_FUNCTION(const char *, GetPersonaName, STEAM_ARGS_VOID, STEAM_PARAMS_VOID) \
    STEAM_FUNCTION(int, GetFriendCount, STEAM_ARGS(int iFriendFlags), STEAM_PARAMS(iFriendFlags)) \
    STEAM_FUNCTION(int, GetLargeFriendAvatar, STEAM_ARGS(uint64_steamid steamIDFriend), STEAM_PARAMS(steamIDFriend))

#define STEAM_USER_FUNCTIONS \
    STEAM_FUNCTION(uint64_steamid, GetSteamID, STEAM_ARGS_VOID, STEAM_PARAMS_VOID)

#define STEAM_UTILS_FUNCTIONS \
    STEAM_FUNCTION(bool, GetImageSize, STEAM_ARGS(int iImage, uint32_t *pnWidth, uint32_t *pnHeight), STEAM_PARAMS(iImage, pnWidth, pnHeight)) \
    STEAM_FUNCTION(bool, GetImageRGBA, STEAM_ARGS(int iImage, uint8_t *pubDest, int nDestBufferSize), STEAM_PARAMS(iImage, pubDest, nDestBufferSize))

#define STEAM_ARGS(...) STEAM_ARGS2(STEAM_CLASS_NAME, __VA_ARGS__)
#define STEAM_ARGS2(CLASS, ...) STEAM_ARGS3(CLASS, __VA_ARGS__)

#define STEAM_PARAMS(...) STEAM_PARAMS2(STEAM_CLASS_NAME, __VA_ARGS__)
#define STEAM_PARAMS2(CLASS, ...) STEAM_PARAMS3(CLASS, __VA_ARGS__)

#define STEAM_ARGS_VOID STEAM_ARGS_VOID2(STEAM_CLASS_NAME)
#define STEAM_ARGS_VOID2(CLASS) STEAM_ARGS_VOID3(CLASS)

#define STEAM_PARAMS_VOID STEAM_PARAMS_VOID2(STEAM_CLASS_NAME)
#define STEAM_PARAMS_VOID2(CLASS) STEAM_PARAMS_VOID3(CLASS)

#define STEAM_FUNCTION(RET, NAME, ARGS, PARAMS) STEAM_FUNCTION2(STEAM_CLASS_NAME, RET, NAME, ARGS, PARAMS)
#define STEAM_FUNCTION2(CLASS, RET, NAME, ARGS, PARAMS) STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS)

#pragma region SteamFriends
#define STEAM_CLASS_NAME SteamFriends
#define STEAM_FUNCTIONS STEAM_FRIENDS_FUNCTIONS

extern const struct STEAM_CLASS_NAME {
#define STEAM_ARGS3(CLASS, ...) (__VA_ARGS__)
#define STEAM_ARGS_VOID3(CLASS) (void)
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) RET (*NAME)ARGS;
    STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
#undef STEAM_ARGS_VOID3
#undef STEAM_ARGS3
} STEAM_CLASS_NAME;

#ifdef INCLUDE_SRC

#define STEAM_ARGS3(CLASS, ...) (I##CLASS *self, __VA_ARGS__)
#define STEAM_ARGS_VOID3(CLASS) (I##CLASS *self)
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) extern RET SteamAPI_I##CLASS##_##NAME ARGS;
STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
#undef STEAM_ARGS_VOID3
#undef STEAM_ARGS3

#define STEAM_ARGS3(CLASS, ...) (__VA_ARGS__)
#define STEAM_ARGS_VOID3(CLASS) (void)
#define STEAM_PARAMS3(CLASS, ...) (I##CLASS##Ptr, __VA_ARGS__)
#define STEAM_PARAMS_VOID3(CLASS) (I##CLASS##Ptr)
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) static inline RET I##CLASS##_##NAME ARGS {return SteamAPI_I##CLASS##_##NAME PARAMS;}
STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
#undef STEAM_PARAMS_VOID3
#undef STEAM_PARAMS3
#undef STEAM_ARGS_VOID3
#undef STEAM_ARGS3

const struct STEAM_CLASS_NAME STEAM_CLASS_NAME = {
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) .NAME = I##CLASS##_##NAME,
    STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
};

#endif /* INCLUDE_SRC */

#undef STEAM_FUNCTIONS
#undef STEAM_CLASS_NAME
#pragma endregion

#pragma region SteamUser
#define STEAM_CLASS_NAME SteamUser
#define STEAM_FUNCTIONS STEAM_USER_FUNCTIONS

extern const struct STEAM_CLASS_NAME {
#define STEAM_ARGS3(CLASS, ...) (__VA_ARGS__)
#define STEAM_ARGS_VOID3(CLASS) (void)
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) RET (*NAME)ARGS;
    STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
#undef STEAM_ARGS_VOID3
#undef STEAM_ARGS3
} STEAM_CLASS_NAME;

#ifdef INCLUDE_SRC

#define STEAM_ARGS3(CLASS, ...) (I##CLASS *self, __VA_ARGS__)
#define STEAM_ARGS_VOID3(CLASS) (I##CLASS *self)
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) extern RET SteamAPI_I##CLASS##_##NAME ARGS;
STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
#undef STEAM_ARGS_VOID3
#undef STEAM_ARGS3

#define STEAM_ARGS3(CLASS, ...) (__VA_ARGS__)
#define STEAM_ARGS_VOID3(CLASS) (void)
#define STEAM_PARAMS3(CLASS, ...) (I##CLASS##Ptr, __VA_ARGS__)
#define STEAM_PARAMS_VOID3(CLASS) (I##CLASS##Ptr)
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) static inline RET I##CLASS##_##NAME ARGS {return SteamAPI_I##CLASS##_##NAME PARAMS;}
STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
#undef STEAM_PARAMS_VOID3
#undef STEAM_PARAMS3
#undef STEAM_ARGS_VOID3
#undef STEAM_ARGS3

const struct STEAM_CLASS_NAME STEAM_CLASS_NAME = {
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) .NAME = I##CLASS##_##NAME,
    STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
};

#endif /* INCLUDE_SRC */

#undef STEAM_FUNCTIONS
#undef STEAM_CLASS_NAME
#pragma endregion

#pragma region SteamUtils
#define STEAM_CLASS_NAME SteamUtils
#define STEAM_FUNCTIONS STEAM_UTILS_FUNCTIONS

extern const struct STEAM_CLASS_NAME {
#define STEAM_ARGS3(CLASS, ...) (__VA_ARGS__)
#define STEAM_ARGS_VOID3(CLASS) (void)
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) RET (*NAME)ARGS;
    STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
#undef STEAM_ARGS_VOID3
#undef STEAM_ARGS3
} STEAM_CLASS_NAME;

#ifdef INCLUDE_SRC

#define STEAM_ARGS3(CLASS, ...) (I##CLASS *self, __VA_ARGS__)
#define STEAM_ARGS_VOID3(CLASS) (I##CLASS *self)
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) extern RET SteamAPI_I##CLASS##_##NAME ARGS;
STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
#undef STEAM_ARGS_VOID3
#undef STEAM_ARGS3

#define STEAM_ARGS3(CLASS, ...) (__VA_ARGS__)
#define STEAM_ARGS_VOID3(CLASS) (void)
#define STEAM_PARAMS3(CLASS, ...) (I##CLASS##Ptr, __VA_ARGS__)
#define STEAM_PARAMS_VOID3(CLASS) (I##CLASS##Ptr)
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) static inline RET I##CLASS##_##NAME ARGS {return SteamAPI_I##CLASS##_##NAME PARAMS;}
STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
#undef STEAM_PARAMS_VOID3
#undef STEAM_PARAMS3
#undef STEAM_ARGS_VOID3
#undef STEAM_ARGS3

const struct STEAM_CLASS_NAME STEAM_CLASS_NAME = {
#define STEAM_FUNCTION3(CLASS, RET, NAME, ARGS, PARAMS) .NAME = I##CLASS##_##NAME,
    STEAM_FUNCTIONS
#undef STEAM_FUNCTION3
};

#endif /* INCLUDE_SRC */

#undef STEAM_FUNCTIONS
#undef STEAM_CLASS_NAME
#pragma endregion

bool CSteamAPI_Init(void);
void SteamAPI_Shutdown(void);
bool SteamAPI_RestartAppIfNecessary(uint32_t unOwnAppID);

#ifdef INCLUDE_SRC

/// Wrapper around SteamAPI_Init which loads interface pointers for internal function calls
bool CSteamAPI_Init(void)
{
    bool SteamAPI_Init(void);
    if (!SteamAPI_Init())
        return 0;
#define STEAM_CLASS(NAME, VERSION) if (!(I##NAME##Ptr = SteamAPI_##NAME##_##VERSION())) return 0;
    STEAM_CLASSES
#undef STEAM_CLASS
    return 1;
}

#endif /* INCLUDE_SRC */

#endif /* STEAM_WRAPPER_H */
