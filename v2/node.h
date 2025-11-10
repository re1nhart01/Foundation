#pragma once
#include "esp_log.h"
#include "styling.h"
#include <cstdint>
#include "lvgl.h"


extern "C" {
  #include "../../main/core/lvgl_port.h"
}

namespace foundationV2
{
  class Ref;
  enum  class VNodeType
  {
    View,
    Button,
    Unknown
  };

  struct BaseProps
  {
    std::shared_ptr<Styling> style = nullptr;
    std::shared_ptr<Ref> ref = nullptr;
  };

  struct VNode
  {
    VNodeType type = VNodeType::Unknown;
    lv_obj_t* host = nullptr;
    VNode* parent = nullptr;
    std::shared_ptr<Styling> style;
    std::vector<std::shared_ptr<VNode>> children;

    virtual ~VNode() {}
    virtual void componentDidMount()
    {
      ESP_LOGI("VNode", "componentDidMount");
    }
    virtual void componentWillUnmount()
    {
      ESP_LOGI("VNode", "componentWillUnmount");
    }
    virtual void componentDidUpdate()
    {
      ESP_LOGI("VNode", "componentDidUpdate");
    }
    virtual void componentDidRebuild()
    {
      ESP_LOGI("VNode", "componentDidRebuild");
    }
    virtual void render() = 0;

    void forceUpdate() {
        if (host) {
            lv_obj_invalidate(host);
        }

        this->componentDidUpdate();
    }

    void rebuild() {
      if (this->host) {
          lv_obj_del(this->host);
          this->host = nullptr;
      }

      this->render();
      this->componentDidRebuild();
    }

    void set_state(const std::function<void()> callback, std::vector<VNode*>& nodes) {
      try {
          callback();
      } catch (const std::runtime_error& e) {}

      for (VNode* node : nodes)
      {
        if (node != nullptr)
          {
            node->forceUpdate();
          }
      }

      this->forceUpdate();
    }

    void set_state(std::function<void(int)> callback) {
      try {
        callback(1);
      } catch (const std::runtime_error& e) {}

      this->forceUpdate();
    }

    void set_parent(VNode* parent)
    {
      this->parent = parent;
    }

    template<typename P>
    void setProps(const P& newProps) {

      if constexpr(false) {
          this->forceUpdate(); // rerender
      }
    }

    void mount(VNode* parent) {
      this->parent = parent;
      this->render();
      this->componentDidMount();
    }

    void unmount() {
      this->componentWillUnmount();
      if (host) {
          lv_obj_del(host);
          host = nullptr;
      }
    }

    void set_active(bool active) const {
      if (this->host != nullptr) {
          if (active)
            lv_obj_clear_flag(this->host, LV_OBJ_FLAG_HIDDEN);
          else
            lv_obj_add_flag(this->host, LV_OBJ_FLAG_HIDDEN);
      }
    }


    void set_style() const
    {
      if (this->host && this->style) {
          lv_obj_add_style(this->host, this->style->getStyle(), 0);
      }
    }

    void set_new_style(std::shared_ptr<Styling> new_style)
    {
      this->style = new_style;

      if (this->host && this->style) {
          lv_obj_add_style(this->host, this->style->getStyle(), 0);
      }
    }
  };

  class Ref {
  public:
    std::string name;
    VNode* linked_component = nullptr;

    ~Ref() = default;
    explicit Ref(const std::string& name) {
      this->name = name;
    };

    void set(VNode* component) {
      if (this->linked_component != nullptr) return;
      this->linked_component = component;
    }

    VNode* get() {
      return this->linked_component;
    }


    template <typename T> T get_typed() {
      return static_cast<T>(this->get());
    }
  };
}