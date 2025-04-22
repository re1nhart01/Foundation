#include "application.hh"
#include "component.hh"
#include "view.cc"

#include "button.cc"
#include "image.cc"
#include "label.cc"
#include "status_bar.cc"
#include "state.cc"
#include "text_input.cc"
#include "macro_component.cc"
#include "stack_navigator.cc"

using namespace foundation;

struct screen_props {
  std::shared_ptr<foundation::Ref> ref = nullptr;
};

class Screen : public Component
{
  screen_props props;
  std::shared_ptr<StackNavigator> navigator;

public:
  explicit Screen(std::shared_ptr<StackNavigator> stack,
                       const screen_props &props)
      : Component(nullptr, nullptr)
  {
    this->props = props;
    this->navigator = std::move(stack);
    if(this->props.ref != nullptr)
      {
        this->props.ref->set(this);
      }
  }

  ~Screen() {
    Component::~Component();
  };

  void on_mount() override {
    Component::on_mount();
  };


  lv_obj_t *render() override
  {
    std::shared_ptr<Styling> style = this->styling();
    std::shared_ptr<Styling> style1 = std::make_shared<Styling>();
    std::shared_ptr<Styling> style2 = std::make_shared<Styling>();

    auto navigator_ref = this->navigator;

    LV_IMG_DECLARE(img_lvgl_logo);

    imageStyle->setSize(100, 100);

    auto renderer = $view(this->parent, view_props{});

    this->renderer_view = renderer;
    this->renderer_view->set_parent(this->parent);
    this->set_component(renderer->render());

    return renderer->get_component();
  }



  std::shared_ptr<Styling> styling() override {
    this->style = std::make_shared<Styling>();

    return this->style;
  }

  Screen *append(lv_obj_t *obj) override
  {
    lv_obj_set_parent(obj, get_component());
    return this;
  }
};
