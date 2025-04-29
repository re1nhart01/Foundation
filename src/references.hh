#pragma once

#include "config.hh"
#include "ref.hh"

namespace foundation {
  class References {
  private:
    std::string name;
    std::unordered_map<std::string, Ref*> storage;

    References();
    explicit References(std::string  name);
    ~References();
  public:
    References* operator=(const References*) const;
    void set(const std::string& name, const Component* component);
    bool del(const std::string& name);
    Ref* get(const std::string& name) const;

#if REFERENCE_STORE_SINGLETON
    static References& instance();
#endif
  };
}