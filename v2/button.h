#pragma once
#include "node.h"

#include <functional>
#include <memory>

namespace foundationV2
{
  static void event_adapter(lv_event_t *event);

  struct ButtonProps : BaseProps
  {
    std::shared_ptr<Ref> ref = nullptr;
    std::shared_ptr<Styling> style = nullptr;
    std::shared_ptr<VNode> child = nullptr;

    std::string text;
    std::function<void(lv_event_t *)> on_click = nullptr;
    std::function<void(lv_event_t *)> on_long_press = nullptr;
    std::function<void(lv_event_t *)> on_pressed = nullptr;
    std::function<void(lv_event_t *)> on_released = nullptr;
    std::function<void(lv_event_t *)> on_focused = nullptr;
    std::function<void(lv_event_t *)> on_defocused = nullptr;
  };

  struct Button final : VNode
  {
    std::shared_ptr<ButtonProps> props = nullptr;
    lv_obj_t *label = nullptr;
    explicit Button(const ButtonProps& button_props)
    {
      this->props = std::make_shared<ButtonProps>(button_props);
    };

    void render() override
    {
      if (!this->parent) return;

      this->host = lv_btn_create(this->parent->host);

      lv_obj_set_layout(this->host, LV_LAYOUT_FLEX);
      lv_obj_set_flex_flow(this->host, LV_FLEX_FLOW_ROW);
      lv_obj_set_flex_align(this->host, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

      if (this->props != nullptr) {
          this->props->child->set_parent(this);
          this->props->child->set_active(true);
          this->props->child->render();
      }

      if (!this->props->text.empty()) {
          this->label = lv_label_create(this->host);
          lv_label_set_text(this->label, this->props->text.c_str());
      }

      this->set_style();

      lv_obj_add_flag(this->host, LV_OBJ_FLAG_CLICKABLE);

      lv_obj_add_event_cb(this->host, event_adapter, LV_EVENT_CLICKED, this);
      lv_obj_add_event_cb(this->host, event_adapter, LV_EVENT_PRESSED, this);
      lv_obj_add_event_cb(this->host, event_adapter, LV_EVENT_RELEASED, this);
      lv_obj_add_event_cb(this->host, event_adapter, LV_EVENT_LONG_PRESSED, this);
    }
  };

  inline void show_button()
  {
    auto v = Button(ButtonProps{
        .ref = std::make_shared<Ref>("zxc"),
        .text = "Pressed"
      });
  }


}