## Steamworks SDK in C

Thanks to Valve extern "C"'ing all their functions we can use a simple C file with definitions of functions which are included when linking with `steam_api.lib`. I took this a bit further using macros to make a pretty interface. Example:
```c
#define INCLUDE_SRC
#include "steam_wrapper.h"

int main(void)
{
    if (!CSteamAPI_Init())
        return 1;
    const char *name = SteamFriends.GetPersonaName();
    printf("%s\n", name);
    SteamAPI_Shutdown();
}
```

## Loading different functions

If you wish to load functions that aren't loaded by default (which is currently most of them), simply add their definitions to STEAM_${CLASS}_FUNCTIONS. The identifiers in STEAM_PARAMS() are simply the names of the arguments in the same order. Example:
```c
#define STEAM_FRIENDS_FUNCTIONS \
    ALL_THE_STUFF_IVE_ALREADY_INCLUDED \
    STEAM_FUNCTION(int, GetSmallFriendAvatar, STEAM_ARGS(uint64_steamid steamIDFriend), STEAM_PARAMS(steamIDFriend))
```
Or if the function has no arguments:
```c
#define STEAM_FRIENDS_FUNCTIONS \
    ALL_THE_STUFF_IVE_ALREADY_INCLUDED \
    STEAM_FUNCTION(const char *, GetPersonaName, STEAM_ARGS_VOID, STEAM_PARAMS_VOID)
```

## Changing interface versions

If you use a different version of Steamworks than I developed on (likely, if you're from the future) then you'll need to update the STEAM_CLASSES define with the proper version numbers specified in `steam_api_flat.h`. Example:
```c
// steam_api_flat.h
S_API ISteamFriends *SteamAPI_SteamFriends_v017();
// v017 is the identifier,
// so store that in
// steam_wrapper.h
#define STEAM_CLASSES \
    STEAM_CLASS(SteamFriends, v017)
```

## Avoid flooding

If you wish to keep your global functions to a minimum, move everything defined in INCLUDE_SRC blocks to a `steam_wrapper.c` and include `steam_wrapper.h` at the top. This will keep Steam's functions (SteamAPI_ICLASSNAME_FUNCNAME) and my inline functions (ICLASSNAME_FUNCNAME) internal to `steam_wrapper.c`, exposing only the SteamCLASSNAME structs to your application.

## More information

You can view the expanded macros on [Compiler Explorer](https://godbolt.org).

1. Copy `steam_wrapper.h` into window
1. Compiler Options: `-DINCLUDE_SRC -E`
1. Add New... -> Preprocessor output

## License

```
MIT License

Copyright (c) 2022 Dawson Frakes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
