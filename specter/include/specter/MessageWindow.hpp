#pragma once

#include "ModalWindow.hpp"
#include "MultiLineTextView.hpp"
#include "Button.hpp"

namespace specter {

class MessageWindow : public ModalWindow {
public:
  enum class Type { InfoOk, ErrorOk, ConfirmOkCancel };

private:
  Type m_type;
  std::function<void(bool ok)> m_func;

  std::unique_ptr<MultiLineTextView> m_text;

  struct OKBinding : IButtonBinding {
    MessageWindow& m_mw;
    std::string m_name;
    OKBinding(MessageWindow& mw, std::string_view name) : m_mw(mw), m_name(name) {}
    std::string_view name(const Control* control) const { return m_name; }
    void activated(const Button* button, const boo::SWindowCoord& coord) { m_mw.m_func(true); }
  } m_okBind;
  ViewChild<std::unique_ptr<Button>> m_ok;

  struct CancelBinding : IButtonBinding {
    MessageWindow& m_mw;
    std::string m_name;
    CancelBinding(MessageWindow& mw, std::string_view name) : m_mw(mw), m_name(name) {}
    std::string_view name(const Control* control) const { return m_name; }
    void activated(const Button* button, const boo::SWindowCoord& coord) { m_mw.m_func(false); }
  } m_cancelBind;
  ViewChild<std::unique_ptr<Button>> m_cancel;

public:
  MessageWindow(ViewResources& res, View& parentView, Type type, std::string_view message,
                std::function<void(bool ok)> func);

  void updateContentOpacity(float opacity) {
    zeus::CColor color = zeus::CColor::lerp({1, 1, 1, 0}, {1, 1, 1, 1}, opacity);
    ModalWindow::setMultiplyColor(color);
    m_text->setMultiplyColor(color);
    m_ok.m_view->setMultiplyColor(color);
    m_cancel.m_view->setMultiplyColor(color);
  }

  void mouseDown(const boo::SWindowCoord&, boo::EMouseButton, boo::EModifierKey);
  void mouseUp(const boo::SWindowCoord&, boo::EMouseButton, boo::EModifierKey);
  void mouseMove(const boo::SWindowCoord&);
  void mouseEnter(const boo::SWindowCoord&);
  void mouseLeave(const boo::SWindowCoord&);

  void resized(const boo::SWindowRect& root, const boo::SWindowRect& sub);
  void draw(boo::IGraphicsCommandQueue* gfxQ);
};

} // namespace specter
