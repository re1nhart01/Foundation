#include "view.hh"


/*
***typedef enum {
  LV_FLEX_ALIGN_START,
  LV_FLEX_ALIGN_END,
  LV_FLEX_ALIGN_CENTER,
  LV_FLEX_ALIGN_SPACE_EVENLY,
  LV_FLEX_ALIGN_SPACE_AROUND,
  LV_FLEX_ALIGN_SPACE_BETWEEN,
} lv_flex_align_t;

typedef enum
{
  LV_FLEX_FLOW_ROW = 0x00,
  LV_FLEX_FLOW_COLUMN = _LV_FLEX_COLUMN,
  LV_FLEX_FLOW_ROW_WRAP = LV_FLEX_FLOW_ROW | _LV_FLEX_WRAP,
  LV_FLEX_FLOW_ROW_REVERSE = LV_FLEX_FLOW_ROW | _LV_FLEX_REVERSE,
  LV_FLEX_FLOW_ROW_WRAP_REVERSE
  = LV_FLEX_FLOW_ROW | _LV_FLEX_WRAP | _LV_FLEX_REVERSE,
  LV_FLEX_FLOW_COLUMN_WRAP = LV_FLEX_FLOW_COLUMN | _LV_FLEX_WRAP,
  LV_FLEX_FLOW_COLUMN_REVERSE = LV_FLEX_FLOW_COLUMN | _LV_FLEX_REVERSE,
  LV_FLEX_FLOW_COLUMN_WRAP_REVERSE
  = LV_FLEX_FLOW_COLUMN | _LV_FLEX_WRAP | _LV_FLEX_REVERSE,
} lv_flex_flow_t;
*/

  namespace foundation
{
  View::View(lv_obj_t * parent, const view_props &props)
      : Component(nullptr, parent), props(props)
  {
    set_style(props.style);
    if(!props.children.empty())
      {
        this->children.insert(this->children.end(), props.children.begin(),
                              props.children.end());
      }

    if(this->props.ref != nullptr)
      {
        this->props.ref->set(this);
      }
  }

  lv_obj_t *View::render()
  {
    if(get_component() == nullptr || this->parent == nullptr)
      {
        this->set_component(this->create_initial(this->parent));
      }
    lv_obj_t *comp = get_component();
    lv_obj_set_layout(comp, LV_LAYOUT_FLEX);
    lv_obj_set_size(comp, props.width, props.height);
    lv_obj_set_flex_flow(comp, props.flex_direction);
    lv_obj_set_flex_align(comp, props.justify_content, props.align_items,
                          props.track_cross_place);

    std::shared_ptr<Styling> style = this->styling();

    for (const auto& child : this->children) {
        if (child != nullptr) {
            child->set_active(true);
            child->set_parent(comp);
            child->render();
            lv_obj_set_parent(child->get_component(), comp);
        }
    }

    if (style != nullptr) {
        lv_obj_add_style(this->get_component(), style->getStyle(), LV_PART_MAIN);
    }

    return comp;
  }

  std::shared_ptr<Styling> View::styling() {
    if (this->props.style) {
        return this->props.style;
    }
    return {};
  }

  View* View::append(lv_obj_t *obj) {
    lv_obj_set_parent(obj, get_component());
    return this;
  }

  lv_obj_t* View::create_initial(lv_obj_t* parental) {
    return lv_obj_create(parental);
  }

} // namespace foundation
