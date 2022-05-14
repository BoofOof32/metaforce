#include "Runtime/GuiSys/CTextRenderBuffer.hpp"

#include "Runtime/Graphics/CGraphics.hpp"
#include "Runtime/Graphics/CGraphicsPalette.hpp"
#include "Runtime/Graphics/CTexture.hpp"
#include "Runtime/Graphics/Shaders/CTextSupportShader.hpp"
#include "Runtime/GuiSys/CFontImageDef.hpp"
#include "Runtime/GuiSys/CFontRenderState.hpp"
#include "Runtime/GuiSys/CInstruction.hpp"
#include "Runtime/GuiSys/CRasterFont.hpp"
#include "Runtime/GuiSys/CTextExecuteBuffer.hpp"

namespace metaforce {

CTextRenderBuffer::CTextRenderBuffer(CTextRenderBuffer&&) noexcept = default;

CTextRenderBuffer::CTextRenderBuffer(EMode mode) : x0_mode(mode) {}

CTextRenderBuffer::~CTextRenderBuffer() = default;

CTextRenderBuffer& CTextRenderBuffer::operator=(CTextRenderBuffer&&) noexcept = default;

void CTextRenderBuffer::SetPrimitive(const Primitive& prim, s32 idx) {
  CMemoryStreamOut out(reinterpret_cast<u8*>(x34_bytecode.data() + x24_primOffsets[idx]),
                       x44_blobSize - x24_primOffsets[idx]);
  if (prim.x4_command == Command::ImageRender) {
    out.WriteUint8(static_cast<u8>(Command::ImageRender));
    out.Put(prim.x8_xPos);
    out.Put(prim.xa_zPos);
    out.Put(prim.xe_imageIndex);
    out.Put(prim.x0_color1.toRGBA());
  } else if (prim.x4_command == Command::CharacterRender) {
    out.WriteUint8(static_cast<u8>(Command::CharacterRender));
    out.Put(prim.x8_xPos);
    out.Put(prim.xa_zPos);
    out.Put(u16(prim.xc_glyph));
    out.Put(prim.x0_color1.toRGBA());
  }
}

CTextRenderBuffer::Primitive CTextRenderBuffer::GetPrimitive(s32 idx) const {
  CMemoryInStream in(reinterpret_cast<const u8*>(x34_bytecode.data() + x24_primOffsets[idx]),
                     x44_blobSize - x24_primOffsets[idx]);
  auto cmd = Command(in.ReadChar());
  if (cmd == Command::ImageRender) {
    u16 xPos = in.ReadShort();
    u16 zPos = in.ReadShort();
    u8 imageIndex = in.ReadChar();
    CTextColor color(in.ReadUint32());
    return {color, Command::ImageRender, xPos, zPos, u'\0', imageIndex};
  }

  if (cmd == Command::CharacterRender) {
    u16 xPos = in.ReadShort();
    u16 zPos = in.ReadShort();
    char16_t glyph = in.ReadUint16();
    CTextColor color(in.ReadUint32());

    return {color, Command::CharacterRender, xPos, zPos, glyph, 0};
  }

  return {CTextColor(zeus::Comp32(0)), Command::Invalid, 0, 0, u'\0', 0};
}

u8* CTextRenderBuffer::GetOutStream() {
  VerifyBuffer();
  return reinterpret_cast<u8*>(x34_bytecode.data()) + x48_curBytecodeOffset;
}

void CTextRenderBuffer::VerifyBuffer() {
  if (x34_bytecode.empty()) {
    x34_bytecode.resize(x44_blobSize);
  }
}

void CTextRenderBuffer::SetMode(EMode mode) { x0_mode = mode; }

int CTextRenderBuffer::GetMatchingPaletteIndex(const CGraphicsPalette& palette) {
  for (int i = 0; i < x50_palettes.size(); ++i) {
    if (memcmp(x50_palettes[i]->GetPaletteData(), palette.GetPaletteData(), 8) == 0) {
      return i;
    }
  }

  return -1;
}

CGraphicsPalette* CTextRenderBuffer::GetNextAvailablePalette() {
  if (x254_nextPalette < 64) {
    x50_palettes.push_back(std::make_unique<CGraphicsPalette>(EPaletteFormat::RGB5A3, 4));
  } else {
    x254_nextPalette = 0;
  }
  ++x254_nextPalette;
  return x50_palettes[x254_nextPalette - 1].get();
}

u32 CTextRenderBuffer::GetCurLen() {
  VerifyBuffer();
  return x44_blobSize - x48_curBytecodeOffset;
}

void CTextRenderBuffer::Render(const zeus::CColor& col, float time) {
  // TODO
}

void CTextRenderBuffer::AddPaletteChange(const CGraphicsPalette& palette) {
  if (x0_mode == EMode::BufferFill) {
    {
      u8* buf = GetOutStream();
      CMemoryStreamOut out(buf, GetCurLen());
      s32 paletteIndex = GetMatchingPaletteIndex(palette);
      if (paletteIndex == -1) {
        GetNextAvailablePalette();
        paletteIndex = x254_nextPalette - 1;
        CGraphicsPalette* destPalette = x50_palettes[x254_nextPalette - 1].get();
        destPalette->Lock();
        memcpy(destPalette->GetPaletteData(), palette.GetPaletteData(), 8);
        destPalette->UnLock();
      }
      out.WriteUint8(static_cast<u8>(Command::PaletteChange));
      out.WriteUint8(paletteIndex);
      x48_curBytecodeOffset += out.GetNumWrites();
    }
  } else {
    x44_blobSize += 2;
  }
}

void CTextRenderBuffer::AddImage(const zeus::CVector2i& offset, const CFontImageDef& image) {
  if (x0_mode == EMode::BufferFill) {
    CMemoryStreamOut out(GetOutStream(), GetCurLen());
    x24_primOffsets.reserve(x24_primOffsets.size() + 1);
    u32 primCap = x24_primOffsets.capacity();
    if (x24_primOffsets.capacity() <= x24_primOffsets.size()) {
      x24_primOffsets.reserve(primCap != 0 ? primCap * 2 : 4);
    }
    x24_primOffsets.push_back(x48_curBytecodeOffset);
    x14_images.reserve(x14_images.size() + 1);
    u32 imgIdx = x14_images.size();
    x14_images.push_back(image);
    out.WriteUint8(static_cast<u8>(Command::ImageRender));
    out.WriteShort(offset.x);
    out.WriteShort(offset.y);
    out.WriteUint8(imgIdx);
    out.WriteLong(zeus::skWhite.toRGBA());
    x48_curBytecodeOffset += out.GetNumWrites();
  } else {
    x44_blobSize += 10;
  }
}

void CTextRenderBuffer::AddCharacter(const zeus::CVector2i& offset, char16_t ch, const CTextColor& color) {
  if (x0_mode == EMode::BufferFill) {
    CMemoryStreamOut out(GetOutStream(), GetCurLen());
    x24_primOffsets.reserve(x24_primOffsets.size() + 1);
    u32 primCap = x24_primOffsets.capacity();
    if (x24_primOffsets.capacity() <= x24_primOffsets.size()) {
      x24_primOffsets.reserve(primCap != 0 ? primCap * 2 : 4);
    }
    x24_primOffsets.push_back(x48_curBytecodeOffset);
    out.WriteUint8(u32(Command::CharacterRender));
    out.WriteShort(offset.x);
    out.WriteShort(offset.y);
    out.WriteShort(ch);
    out.WriteUint32(color.toRGBA());
    x48_curBytecodeOffset += out.GetNumWrites();
  } else {
    x44_blobSize += 11;
  }
}

void CTextRenderBuffer::AddFontChange(const TToken<CRasterFont>& font) {
  if (x0_mode == EMode::BufferFill) {
    CMemoryStreamOut out(GetOutStream(), GetCurLen());
    u32 fontCount = x4_fonts.size();
    bool found = false;
    u8 fontIndex = 0;
    if (fontCount > 0) {
      for (const auto& tok : x4_fonts) {
        if (tok.GetObjectReference() == font.GetObjectReference()) {
          out.WriteUint8(static_cast<u8>(Command::FontChange));
          out.WriteUint8(fontIndex);
          found = true;
          break;
        }
        ++fontIndex;
      }
    }

    if (!found) {
      x4_fonts.reserve(x4_fonts.size() + 1);
      u32 fontIdx = x4_fonts.size();
      x4_fonts.push_back(font);
      out.WriteUint8(static_cast<u8>(Command::FontChange));
      out.WriteUint8(fontIdx);
    }
    x48_curBytecodeOffset += out.GetNumWrites();
  } else {
    x44_blobSize += 2;
  }
}

bool CTextRenderBuffer::HasSpaceAvailable(const zeus::CVector2i& origin, const zeus::CVector2i& extent) {
  std::pair<zeus::CVector2i, zeus::CVector2i> bounds = AccumulateTextBounds();
  if (bounds.first.x > bounds.second.x) {
    return true;
  }

  if (0 < origin.y) {
    return false;
  }

  zeus::CVector2i size = bounds.second - bounds.first;
  return size.y <= extent.y;
}

std::pair<zeus::CVector2i, zeus::CVector2i> CTextRenderBuffer::AccumulateTextBounds() {
  zeus::CVector2i min{INT_MAX, INT_MAX};
  zeus::CVector2i max{INT_MIN, INT_MIN};
  CMemoryInStream in(x34_bytecode.data(), x44_blobSize);

  while (in.GetReadPosition() < x48_curBytecodeOffset) {
    auto cmd = static_cast<Command>(in.ReadChar());
    if (cmd == Command::FontChange) {
      x4c_activeFont = in.ReadChar();
    } else if (cmd == Command::CharacterRender) {
      u16 offX = in.ReadShort();
      u16 offY = in.ReadShort();
      char16_t chr = in.ReadShort();
      in.ReadLong();
      if (x4c_activeFont != -1) {
        auto font = x4_fonts[x4c_activeFont];
        if (font) {
          const auto* glyph = font->GetGlyph(chr);
          if (glyph != nullptr) {
            max.x = std::max(max.x, offX + glyph->GetCellWidth());
            max.y = std::max(max.y, offY + glyph->GetCellHeight());
            min.x = std::min<int>(min.x, offX);
            min.y = std::min<int>(min.y, offY);
          }
        }
      }
    } else if (cmd == Command::ImageRender) {
      u16 offX = in.ReadShort();
      u16 offY = in.ReadShort();
      u8 imageIdx = in.ReadChar();
      in.ReadLong();
      const auto& image = x14_images[imageIdx];
      max.x = std::max(max.x, offX + static_cast<int>(static_cast<float>(image.x4_texs.front()->GetWidth()) *
                                                      image.x14_cropFactor.x()));
      max.y = std::max(max.y, offY + static_cast<int>(static_cast<float>(image.x4_texs.front()->GetHeight()) *
                                                      image.x14_cropFactor.y()));
      min.x = std::min<int>(min.x, offX);
      min.y = std::min<int>(min.y, offY);
    } else if (cmd == Command::PaletteChange) {
      in.ReadChar();
    }
  }
  return {min, max};
}

} // namespace metaforce
