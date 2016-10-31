


#ifndef TUUM_MODULE_NET_H
#define TUUM_MODULE_NET_H

#include <map>

#include "platform.hpp"

namespace tuum {

  enum EAtomicType {
    INT32 = 1,
  };

  struct Endpoint {
    std::string uri;
    size_t argc;
    EAtomicType* argv;
    EAtomicType ret;
  };

  struct Resource {
    std::string nsp;

    size_t epc;
    Endpoint *eps;
  };


  class ModuleNet {
  public:
    struct _mod_t {};

    typedef uint32_t mod_id_t;
    typedef _mod_t*  mod_t;

    class Module;

    struct mod_desc_t {
      mod_id_t id = 0;
      mod_t type = nullptr;
      std::string uri = "";
      Module* mod = nullptr;
    };

    typedef mod_desc_t* mod_desc_ptr_t;
    typedef std::vector<mod_desc_ptr_t> mod_desc_ptr_set;

    class Module {
    public:
      Module()
      {

      }

      int mnet_init(mod_id_t id, mod_t type, std::string uri) {
        m_desc.id = id;
        m_desc.type = type;
        m_desc.uri = uri;
        m_desc.mod = this;
      }

      int mnet_deinit() {
        m_desc.id = 0;
        m_desc.type = nullptr;
        m_desc.uri = "";
        m_desc.mod = nullptr;
      }

      mod_desc_ptr_t getDescriptor() { return &m_desc; }

      virtual mod_t getType() = 0;

    private:
      mod_desc_t m_desc;
    };

    typedef std::map<mod_id_t, mod_desc_ptr_t> ModuleIdMap;
    typedef std::map<mod_t, mod_desc_ptr_set> ModuleTypeMap;

  public:
    ModuleNet();

    int find(mod_t, Module**);
    int erase(mod_id_t);

    int reg(Module*, std::string = "");
    int dereg(Module*);

  protected:
    mod_id_t m_id_seq;

    ModuleIdMap mm_idMap;
    ModuleTypeMap mm_typeMap;
  };


  class TestMod : public ModuleNet::Module
  {
  public:
    TestMod();

    ModuleNet::mod_t getType();
    static ModuleNet::_mod_t Type;

    int testPublicFn(int = 0);

  protected:
    Resource m_resource;
    Endpoint m_endpoints[1];
  };


  extern ModuleNet gModuleNet;

}


namespace tuum {
    void mnet_test();
}

#endif
