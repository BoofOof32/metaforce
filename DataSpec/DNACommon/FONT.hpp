#ifndef __COMMON_FONT_HPP__
#define __COMMON_FONT_HPP__

#include "PAK.hpp"
#include "athena/FileWriter.hpp"

namespace DataSpec
{
namespace DNAFont
{
struct GlyphRect : BigYAML
{
    DECL_YAML
    Value<float> left;
    Value<float> top;
    Value<float> right;
    Value<float> bottom;
};
struct IGlyph : BigYAML
{
    DECL_YAML
    Value<atUint16> m_character;
    GlyphRect m_glyphRect;

    atUint16 character() const { return m_character; }
    float left() const { return m_glyphRect.left; }
    float top() const { return m_glyphRect.top; }
    float right() const { return m_glyphRect.right; }
    float bottom() const { return m_glyphRect.bottom; }
    GlyphRect rect() const { return m_glyphRect; }

    virtual int layer() { return 0; }
    virtual atInt32 leftPadding() const=0;
    virtual atInt32 advance() const =0;
    virtual atInt32 rightPadding() const=0;
    virtual atInt32 width() const=0;
    virtual atInt32 height() const=0;
    virtual atInt32 baseline() const=0;
    virtual atInt32 kerningIndex() const =0;
};

struct GlyphMP1 : IGlyph
{
    DECL_YAML
    Value<atInt32> m_leftPadding;
    Value<atInt32> m_advance;
    Value<atInt32> m_rightPadding;
    Value<atInt32> m_width;
    Value<atInt32> m_height;
    Value<atInt32> m_baseline;
    Value<atInt32> m_kerningIndex;

    atInt32 leftPadding() const { return m_leftPadding; }
    atInt32 advance() const { return m_advance; }
    atInt32 rightPadding() const { return m_rightPadding; }
    atInt32 width() const { return m_width; }
    atInt32 height() const { return m_height; }
    atInt32 baseline() const { return m_baseline; }
    atInt32 kerningIndex() const { return m_kerningIndex; }
};

struct GlyphMP2 : IGlyph
{
    DECL_YAML
    Value<atInt8> m_layer;
    Value<atInt8> m_leftPadding;
    Value<atInt8> m_advance;
    Value<atInt8> m_rightPadding;
    Value<atInt8> m_width;
    Value<atInt8> m_height;
    Value<atInt8> m_baseline;
    Value<atInt16> m_kerningIndex;

    atInt32 layer() const { return m_layer; }
    atInt32 leftPadding() const { return m_leftPadding; }
    atInt32 advance() const { return m_advance; }
    atInt32 rightPadding() const { return m_rightPadding; }
    atInt32 width() const { return m_width; }
    atInt32 height() const { return m_height; }
    atInt32 baseline() const { return m_baseline; }
    atInt32 kerningIndex() const { return m_kerningIndex; }
};

struct KerningInfo : BigYAML
{
    DECL_YAML
    Value<atUint16> thisChar;
    Value<atUint16> nextChar;
    Value<atInt32>  adjust;
};

template <class IDType>
struct FONT : BigYAML
{
    DECL_YAML
    Value<atUint32> version;
    Value<atUint32> unknown1;
    Value<atInt32> lineHeight;
    Value<atInt32> verticalOffset;
    Value<atInt32> lineMargin;
    Value<bool> unknown2;
    Value<bool> unknown3;
    Value<atUint32> unknown4;
    Value<atUint32> fontSize; // in points
    String<-1> name;
    IDType textureId;
    Value<atUint32> textureFormat;
    Value<atUint32> glyphCount;
    std::vector<std::unique_ptr<IGlyph>> glyphs;
    Value<atUint32> kerningInfoCount;
    Vector<KerningInfo, DNA_COUNT(kerningInfoCount)> kerningInfo;

    void gatherDependencies(std::vector<hecl::ProjectPath>& pathsOut) const
    {
        g_curSpec->flattenDependencies(textureId, pathsOut);
    }
};

template <class IDType>
bool ExtractFONT(PAKEntryReadStream& rs, const hecl::ProjectPath& outPath);

template <class IDType>
bool WriteFONT(const FONT<IDType>& font, const hecl::ProjectPath& outPath);

}
}

#endif // __COMMON_FONT_HPP__
