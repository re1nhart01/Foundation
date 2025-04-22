#pragma once


namespace foundation {
    class Component;

    class Ref {
    public:
        std::string name;
        Component* linked_component = nullptr;

        ~Ref() = default;
        explicit Ref(const std::string& name) {
            this->name = name;
        };

        void set(Component* component) {
            if (this->linked_component != nullptr) return;
            this->linked_component = component;
        }

        Component* get() {
            return this->linked_component;
        }
    };
}
