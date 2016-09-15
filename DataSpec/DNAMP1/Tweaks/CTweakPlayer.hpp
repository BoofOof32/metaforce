#ifndef _DNAMP1_CTWEAKPLAYER_HPP_
#define _DNAMP1_CTWEAKPLAYER_HPP_

#include "../../DNACommon/Tweaks/ITweakPlayer.hpp"

namespace DataSpec
{
namespace DNAMP1
{

struct CTweakPlayer : ITweakPlayer
{
    Delete _d;
    Value<float> x4_[8];
    Value<float> x24_[8];
    Value<float> x44_[8];
    Value<float> x64_[8];
    Value<float> x84_[8];
    Value<float> xa4_[8];
    Value<float> xc4_;
    Value<float> xc8_;
    Value<float> xcc_;
    Value<float> xd0_;
    Value<float> xd4_;
    Value<float> xd8_;
    Value<float> xdc_;
    Value<float> xe0_;
    Value<float> xe4_;
    Value<float> xe8_;
    Value<float> xec_;
    Value<float> xf0_;
    Value<float> xf4_;
    Value<float> xf8_;
    Value<float> xfc_;
    Value<float> x100_;
    Value<float> x104_;
    Value<float> x108_;
    Value<float> x10c_;
    Value<float> x110_;
    Value<float> x114_;
    Value<float> x118_;
    Value<float> x11c_;
    Value<float> x120_;
    Value<float> x124_;
    Value<float> x128_;
    Value<float> x12c_;
    Value<float> x130_;
    Value<float> x134_;
    Value<float> x138_;
    Value<float> x13c_;
    Value<float> x140_;
    Value<float> x144_;
    Value<float> x148_;
    Value<float> x14c_;
    Value<float> x150_leftDiv;
    Value<float> x154_rightDiv;
    Value<float> x158_[3];
    Value<float> x164_[3];
    Value<float> x170_[3];
    Value<float> x17c_;
    Value<float> x180_;
    Value<float> x184_;
    Value<float> x188_;
    Value<float> x18c_;
    Value<float> x190_;
    Value<float> x194_;
    Value<float> x198_;
    Value<float> x19c_;
    Value<float> x1a0_;
    Value<float> x1a4_;
    Value<atUint32> x1a8_[2];
    Value<atUint32> x1b0_[2];
    Value<atUint32> x1b8_[2];
    Value<atUint32> x1c0_[2];
    Value<atUint32> x1c8_[2];
    Value<atUint32> x1d0_[2];
    Value<float> x1d8_;
    Value<float> x1dc_;
    Value<float> x1e0_;
    Value<float> x1e4_;
    Value<float> x1e8_;
    Value<float> x1ec_;
    Value<float> x1f0_;
    Value<float> x1f4_;
    Value<float> x1f8_;
    Value<float> x1fc_;
    Value<bool> x200_24_ : 1;
    Value<bool> x200_25_ : 1;
    Value<float> x204_;
    Value<float> x208_;
    Value<float> x20c_;
    Value<float> x210_;
    Value<float> x214_;
    Value<float> x218_;
    Value<bool> x21c_24_ : 1;
    Value<bool> x21c_25_ : 1;
    Value<bool> x21c_26_ : 1;
    Value<float> x220_;
    Value<float> x224_;
    Value<bool> x228_24_ : 1;
    Value<bool> x228_25_ : 1;
    Value<bool> x228_26_ : 1;
    Value<bool> x228_27_ : 1;
    Value<bool> x228_28_ : 1;
    Value<bool> x228_29_ : 1;
    Value<bool> x228_30_ : 1;
    Value<bool> x228_31_ : 1;
    Value<bool> x229_24_ : 1;
    Value<bool> x229_25_ : 1;
    Value<bool> x229_26_ : 1;
    Value<bool> x229_27_ : 1;
    Value<bool> x229_28_ : 1;
    Value<bool> x229_29_ : 1;
    Value<bool> x229_30_ : 1;
    Value<bool> x229_31_ : 1;
    Value<bool> x22a_24_ : 1;
    Value<bool> x22a_25_ : 1;
    Value<bool> x22a_26_ : 1;
    Value<bool> x22a_27_ : 1;
    Value<bool> x22a_28_ : 1;
    Value<float> x22c_;
    Value<float> x230_;
    Value<float> x234_;
    Value<float> x238_;
    Value<float> x23c_;
    Value<float> x240_;
    Value<float> x244_;
    Value<float> x248_;
    Value<float> x24c_;
    Value<float> x250_;
    Value<float> x254_;
    Value<float> x258_;
    Value<float> x25c_;
    Value<float> x260_;
    Value<float> x264_;
    Value<float> x268_;
    Value<float> x26c_playerHeight;
    Value<float> x270_playerXYHalfExtent;
    Value<float> x274_;
    Value<float> x278_;
    Value<float> x27c_;
    Value<float> x280_;
    Value<float> x284_;
    Value<float> x288_;
    Value<float> x28c_;
    Value<float> x290_;
    Value<float> x294_;
    Value<float> x298_;
    Value<float> x29c_;
    Value<float> x2a0_;
    Value<float> x2a4_;
    Value<float> x2a8_;
    Value<float> x2ac_;
    Value<float> x2b0_;
    Value<float> x2b4_;
    Value<float> x2b8_;
    Value<float> x2bc_;
    Value<float> x2c0_;
    Value<float> x2c4_;
    Value<float> x2c8_;
    Value<float> x2cc_;
    Value<atUint32> x2d0_;
    Value<bool> x2d4_;
    Value<bool> x2d5_;
    Value<float> x2d8_;
    Value<float> x2dc_;
    Value<float> x2e0_;
    Value<float> x2e4_;
    Value<float> x2e8_;
    Value<float> x2ec_;
    Value<float> x2f0_;
    Value<bool>  x2f4_;
    Value<float> x2f8_;
    Value<atUint32> x2fc_;
    Value<float> x300_;
    Value<float> x304_;
    Value<float> x308_;
    float GetPlayerHeight() const { return x26c_playerHeight; }
    float GetPlayerXYHalfExtent() const { return x270_playerXYHalfExtent; }
    float GetPlayerSomething1() const { return x274_; }
    float GetPlayerSomething2() const { return x278_; }
    float GetPlayerSomething3() const { return x27c_; }
    float GetPlayerSomething4() const { return x134_; }
    bool GetPlayerSomething5() const { return x228_24_; }
    float GetLeftLogicalThreshold() const {return x150_leftDiv;}
    float GetRightLogicalThreshold() const {return x154_rightDiv;}
    CTweakPlayer() = default;
    CTweakPlayer(athena::io::IStreamReader& reader)
    {
        read(reader);
        FixupValues();
    }

    void read(athena::io::IStreamReader& __dna_reader);
    void write(athena::io::IStreamWriter& __dna_writer) const;
    void read(athena::io::YAMLDocReader& __dna_docin);
    void write(athena::io::YAMLDocWriter& __dna_docout) const;
    void FixupValues();
    static const char* DNAType();
    const char* DNATypeV() const { return DNAType(); }

    size_t binarySize(size_t __isz) const;
};

}
}

#endif // _DNAMP1_CTWEAKPLAYER_HPP_
