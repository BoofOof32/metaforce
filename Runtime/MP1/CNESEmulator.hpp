#ifndef __URDE_CNESEMULATOR_HPP__
#define __URDE_CNESEMULATOR_HPP__

#include "RetroTypes.hpp"
#include "zeus/CColor.hpp"

namespace urde
{
class CFinalInput;

namespace MP1
{

class CNESEmulator
{
    bool x20_wantsQuit = false;
    u8 x21_saveState[18];
    bool x34_wantsLoad = false;
    bool x38_stateLoaded = false;
    u8 x39_loadState[18];
    static void DescrambleROM(u8* dataIn, u8* dataOut, u32 dataOutLen = 0x20000, u8 descrambleInit = 0xe9,
                              u32 descramble2Len = 0x1FFFC, u32 descramble2Magic = 0xA663);
public:
    void ProcessUserInput(const CFinalInput& input, int);
    void Update();
    void Draw(const zeus::CColor& mulColor, bool filtering);
    void LoadState(const u8* state);
    const u8* GetSaveState() const { return x21_saveState; }
    bool WantsQuit() const { return x20_wantsQuit; }
    bool WantsLoad() const { return x34_wantsLoad; }
};

}
}

#endif // __URDE_CNESEMULATOR_HPP__
