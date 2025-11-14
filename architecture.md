# Architecture

Foundation UI is structured around several core primitives:

## 1. VNode (Virtual Node)
A VNode is an abstract description of UI:
- props
- list of children
- LVGL host (`lv_obj_t*`)
- parent pointer
- render() logic

VNode stores *structure*, not logic.

---

## 2. Component
A Component is a class representing UI + logic.

Each component:
- Has lifecycle (`render`, `component_did_mount`)
- Holds internal state
- Produces a VNode tree
- Keeps reference to its LVGL object
- Supports partial rerender via `set_state`

Example:

```cpp
class MyComponent : public Component {
public:
    lv_obj_t* render() override;
    void component_did_mount() override;
};
