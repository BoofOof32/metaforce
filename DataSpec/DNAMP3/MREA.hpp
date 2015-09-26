#ifndef __DNAMP3_MREA_HPP__
#define __DNAMP3_MREA_HPP__

#include "../DNACommon/DNACommon.hpp"
#include "CMDLMaterials.hpp"
#include "CSKR.hpp"
#include "../DNAMP2/MREA.hpp"

namespace Retro
{
namespace DNAMP3
{

struct MREA
{
    struct StreamReader : DNAMP2::MREA::StreamReader
    {
        std::vector<std::pair<DNAFourCC, atUint32>> m_secIdxs;
        StreamReader(Athena::io::IStreamReader& source,
                     atUint32 blkCount, atUint32 secIdxCount);
        std::vector<std::pair<DNAFourCC, atUint32>>::const_iterator beginSecIdxs()
        {
            return m_secIdxs.begin();
        }
        void writeSecIdxs(Athena::io::IStreamWriter& writer) const;
    };

    struct Header : BigDNA
    {
        DECL_DNA
        Value<atUint32> magic;
        Value<atUint32> version;
        Value<atVec4f> localToWorldMtx[3];
        Value<atUint32> meshCount;
        Value<atUint32> sclyLayerCount;
        Value<atUint32> secCount;
        Value<atUint32> compressedBlockCount;
        Value<atUint32> secIndexCount;
        Seek<20, Athena::Current> align1;
        Vector<atUint32, DNA_COUNT(secCount)> secSizes;

        atUint32 getSecOffset(atUint32 idx) const
        {
            if (idx >= secSizes.size())
                return -1;
            atUint32 retval = 0;
            for (atUint32 i=0 ; i<idx ; ++i)
                retval += secSizes[i];
            return retval;
        }
    };

    struct MeshHeader : BigDNA
    {
        DECL_DNA
        struct VisorFlags : BigDNA
        {
            DECL_DNA
            Value<atUint32> flags;
        } visorFlags;
        Value<atVec4f> xfMtx[3];
        Value<atVec3f> aabb[2];
    };

    struct DEPS : BigDNA
    {
        DECL_DNA
        Value<atUint32> depCount;
        struct Dependency : BigDNA
        {
            DECL_DNA
            UniqueID64 id;
            DNAFourCC type;
        };
        Vector<Dependency, DNA_COUNT(depCount)> deps;
        Value<atUint32> depLayerCount;
        Vector<atUint32, DNA_COUNT(depLayerCount)> depLayers;
    };

    struct BabeDeadLight : BigDNA
    {
        DECL_DNA
        enum LightType : atUint32
        {
            LightLocalAmbient,
            LightDirectional,
            LightCustom,
            LightSpot
        };
        Value<LightType> lightType;
        Value<atVec4f> color;
        Value<atVec3f> position;
        Value<atVec3f> direction;
        Value<atVec3f> codirection;
        Value<float> unk5;
        Value<float> unk6;
        Value<float> unk7;
        Value<atUint8> unk8;
        Value<atUint32> unk9;
        Value<atUint32> unk10;
        Value<float> unk11;
        Value<atVec4f> unk12;
        Value<atUint32> unk13;
    };

    static void ReadBabeDeadToBlender_3(HECL::BlenderConnection::PyOutStream& os,
                                        Athena::io::IStreamReader& rs);

    static bool Extract(const SpecBase& dataSpec,
                        PAKEntryReadStream& rs,
                        const HECL::ProjectPath& outPath,
                        PAKRouter<PAKBridge>& pakRouter,
                        const PAK::Entry& entry,
                        bool,
                        std::function<void(const HECL::SystemChar*)>);

    static bool ExtractLayerDeps(PAKEntryReadStream& rs, PAKBridge::Level::Area& areaOut);
};

}
}

#endif // __DNAMP3_MREA_HPP__
