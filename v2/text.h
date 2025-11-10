//
// Created by evgeniy on 11/9/25.
//

#ifndef TEXT_H
#define TEXT_H

#endif //TEXT_H


namespace foundationV2
{
  struct TextProps : BaseProps {
    std::shared_ptr<Ref> ref = nullptr;
    std::shared_ptr<Styling> style;
    std::string text;

    lv_event_cb_t on_click = nullptr;
    lv_event_cb_t on_long_press = nullptr;
    lv_event_cb_t on_pressed = nullptr;
    lv_event_cb_t on_released = nullptr;
    lv_event_cb_t on_focused = nullptr;
    lv_event_cb_t on_defocused = nullptr;
  };

  struct Text final : VNode
  {
    std::shared_ptr<TextProps> props = nullptr;
    explicit Text(const TextProps& text_props)
    {
      this->props = std::make_shared<TextProps>(text_props);
    };

    void render() override
    {
      if (!this->parent) return;

      this->host = lv_label_create(this->parent->host);

      lv_label_set_text(this->host, this->props->text.c_str());

      if (this->props->on_click)       lv_obj_add_event_cb(this->host, this->props->on_click, LV_EVENT_CLICKED, nullptr);
      if (this->props->on_long_press)  lv_obj_add_event_cb(this->host, this->props->on_long_press, LV_EVENT_LONG_PRESSED, nullptr);
      if (this->props->on_pressed)     lv_obj_add_event_cb(this->host, this->props->on_pressed, LV_EVENT_PRESSED, nullptr);
      if (this->props->on_released)    lv_obj_add_event_cb(this->host, this->props->on_released, LV_EVENT_RELEASED, nullptr);
      if (this->props->on_focused)     lv_obj_add_event_cb(this->host, this->props->on_focused, LV_EVENT_FOCUSED, nullptr);
      if (this->props->on_defocused)   lv_obj_add_event_cb(this->host, this->props->on_defocused, LV_EVENT_DEFOCUSED, nullptr);

    }

    void update(const std::string &value) const {
      if (this->host == nullptr) return;

      lv_obj_t* obj = this->host;
      if (obj != nullptr) {
          lv_label_set_text(this->host, value.c_str());
      }
    }
  };

  inline void show_text()
  {
    auto v = Text(TextProps{
        .ref = std::make_shared<Ref>("zxc"),
        .text = "zxc"
      });
  }
}