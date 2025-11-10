#pragma once

#include "node.h"

namespace foundationV2
{
  struct ViewProps : BaseProps
  {
    short width = LV_PCT(100);
    short height = LV_SIZE_CONTENT;
    std::vector<std::shared_ptr<VNode>> children = {};
    std::shared_ptr<Ref> ref = nullptr;
    std::shared_ptr<Styling> style = nullptr;


    lv_flex_align_t justify_content = LV_FLEX_ALIGN_START;
    lv_flex_align_t align_items = LV_FLEX_ALIGN_CENTER;
    lv_flex_align_t track_cross_place = LV_FLEX_ALIGN_START;
    lv_flex_flow_t flex_direction = LV_FLEX_FLOW_COLUMN;
  };

  struct View : VNode
  {
    std::shared_ptr<ViewProps> props;
    explicit View(const ViewProps& view_props)
    {
      this->props = std::make_shared<ViewProps>(view_props);
      this->children = std::move(std::static_pointer_cast<ViewProps>(this->props)->children);
    };

    void render() override
    {
      const auto vp = std::static_pointer_cast<ViewProps>(this->props);

      if(this->host == nullptr && this->parent != nullptr)
        {
          this->host = lv_obj_create(this->parent->host);
        }

      lv_obj_t *comp = this->host;

      lv_obj_set_layout(comp, LV_LAYOUT_FLEX);
      lv_obj_set_size(comp, vp->width, vp->height);
      lv_obj_set_flex_flow(comp, vp->flex_direction);
      lv_obj_set_flex_align(comp, vp->justify_content, vp->align_items, vp->track_cross_place);

      lv_obj_set_scroll_dir(comp, LV_DIR_NONE);
      lv_obj_set_scrollbar_mode(comp, LV_SCROLLBAR_MODE_OFF);

      for(const auto &child : this->children)
        {
          if(child != nullptr)
            {
              child->set_active(true);
              child->set_parent(this);
              child->render();
              lv_obj_set_parent(child->host, comp);
            }
        }

      this->set_style();
    }
  };

  inline void show()
  {
    auto v = View(ViewProps{
        .children = {},
        .ref = std::make_shared<Ref>("zxc"),
      });
  }


}