#ifndef HECLBACKEND_GLSL_HPP
#define HECLBACKEND_GLSL_HPP

#include "ProgrammableCommon.hpp"

namespace HECL
{
namespace Backend
{

struct GLSL : ProgrammableCommon
{
    void reset(const IR& ir, Diagnostics& diag);
    std::string makeVert(const char* glslVer, unsigned col, unsigned uv, unsigned w,
                         unsigned skinSlots, unsigned texMtxs) const;
    std::string makeFrag(const char* glslVer,
                         const char* lightingSource, const char* lightingEntry) const;
    std::string makeFrag(const char* glslVer,
                         const char* lightingSource, const char* lightingEntry,
                         const char* postSource, const char* postEntry) const;

private:
    std::string GenerateVertInStruct(unsigned col, unsigned uv, unsigned w) const;
    std::string GenerateVertToFragStruct() const;
    std::string GenerateVertUniformStruct(unsigned skinSlots, unsigned texMtxs) const;

    std::string EmitVec3(const atVec4f& vec) const
    {
        return HECL::Format("vec3(%g,%g,%g)", vec.vec[0], vec.vec[1], vec.vec[2]);
    }

    std::string EmitTexGenSource2(TexGenSrc src, int uvIdx) const;
    std::string EmitTexGenSource4(TexGenSrc src, int uvIdx) const;
};

}
}

#endif // HECLBACKEND_GLSL_HPP
