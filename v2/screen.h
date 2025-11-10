//
// Created by evgeniy on 11/9/25.
//

#ifndef SCREEN_H
#define SCREEN_H
#include "esp_log.h"
#include "view.h"

#endif //SCREEN_H

#include "lvgl.h"
#include "node.h"

namespace foundationV2
{
  struct ScreenProps : BaseProps {
  public:
    lv_obj_t* scr_instance;
  };

  struct Screen : VNode
  {
    std::shared_ptr<ScreenProps> props;
    explicit Screen(ScreenProps& screen_props)
    {
      this->props = std::make_shared<ScreenProps>(screen_props);
    }
    ~Screen() override = default;

    virtual std::shared_ptr<VNode> render_root() = 0;

    void set_full_wh(short width, short height)
    {
      lv_obj_set_size(this->host, LV_PCT(100), LV_PCT(100));
    }

    void render() override {
      this->host = this->props->scr_instance;
      auto node = this->render_root();
      node->mount(this);
    };

  };
}
