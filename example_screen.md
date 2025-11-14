# Complete Example

```cpp
class MainScreen : public Component {
public:
    lv_obj_t* render() override {
        return this->delegate(
            $View(
                ViewProps::up()
                    .set_style(this->styling())
                    .set_children({
                        $StatusBar(StatusBarProps::up()),
                        render_header(),
                        render_body(),
                    })
            )
        );
    }

    std::shared_ptr<View> render_header() const {
        return $View(
            ViewProps::up()
                .set_style($s("header.container"))
                .set_children({
                    $Text(TextProps::up().value("Hello")),
                    $Button(
                        ButtonProps::up()
                            .set_child($Text(TextProps::up().value("Open")))
                            .click([this](lv_event_t* e){
                                navigator->navigate("/settings");
                            })
                    )
                })
        );
    }
};
