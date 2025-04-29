#include "ref.hh"

#include <string>
#include <unordered_map>
#include <utility>
#include "config.hh"
#include "references.hh"

namespace foundation {

    References::References() : name(APP_STORAGE_NAME) {};
    References::References(std::string  name) : name(std::move(name)) {
      this->storage = std::unordered_map<std::string, Ref*>();
    }
    References::~References() {
      for (auto& [key, ref] : storage) {
          delete ref;
      }
    };

    References* References::operator=(const References* other) const {
      return nullptr;
    };

    void References::set(const std::string& name, const Component* component) {
      auto ref = new Ref(name);
      ref->set(const_cast<Component*>(component));

      if (this->storage.find(name) != this->storage.end()) {
          this->del(name);
      }

      this->storage[name] = ref;
    }

    bool References::del(const std::string& name) {
      const auto ref_get = this->storage.find(name);
      const bool exists = ref_get != this->storage.end();

      if (exists) {
          if (auto ref = ref_get->second; ref != nullptr) {
              delete ref;
            }
        }
      this->storage.erase(name);
      return exists;
    }

    Ref* References::get(const std::string& name) const {
      auto ref_get = this->storage.find(name);
      return ref_get->second;
    }

#if REFERENCE_STORE_SINGLETON
  References& References::instance() {
      static References instance;
      return instance;
    }
#endif
}