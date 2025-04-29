#include <utility>

#include "label.hh"

namespace foundation {

  Label::Label(label_props  props)
      : Component(nullptr, nullptr), props(std::move(props)) {
    this->parent = nullptr;

    if (this->props.ref != nullptr) {
        this->props.ref->set(this);
    }
  }

  lv_obj_t* Label::render() {
    lv_obj_t* parent_obj = this->get_parent();
    if (!parent_obj) return nullptr;

    set_component(lv_label_create(parent_obj));
    auto* obj = get_component();

    lv_label_set_text(obj, props.text.c_str());

    const auto& e = props;
    if (e.on_click)       lv_obj_add_event_cb(obj, e.on_click, LV_EVENT_CLICKED, nullptr);
    if (e.on_long_press)  lv_obj_add_event_cb(obj, e.on_long_press, LV_EVENT_LONG_PRESSED, nullptr);
    if (e.on_pressed)     lv_obj_add_event_cb(obj, e.on_pressed, LV_EVENT_PRESSED, nullptr);
    if (e.on_released)    lv_obj_add_event_cb(obj, e.on_released, LV_EVENT_RELEASED, nullptr);
    if (e.on_focused)     lv_obj_add_event_cb(obj, e.on_focused, LV_EVENT_FOCUSED, nullptr);
    if (e.on_defocused)   lv_obj_add_event_cb(obj, e.on_defocused, LV_EVENT_DEFOCUSED, nullptr);

    return obj;
  }

  std::shared_ptr<Styling> Label::styling() {
    return props.style;
  }

  Label* Label::append(lv_obj_t* obj) {
    lv_obj_set_parent(obj, get_component());
    return this;
  }

} // namespace foundation
