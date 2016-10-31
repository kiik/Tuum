


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

  struct res_data_t {
    std::string nsp;

    size_t epc;
    Endpoint *eps;
  };


  /** @class ResourceNetwork
   *  @brief Handles creation of a object network, where objects can register themselves as resources and receive binary messages from external sources via URI based addressing.
   */
  class ResourceNetwork {
  public:
    struct _res_t {};

    typedef uint32_t res_id_t;
    typedef _res_t*  res_t;

    class Resource;

    struct mod_desc_t {
      res_id_t id = 0;
      res_t type = nullptr;
      std::string uri = "";
      Resource* mod = nullptr;
    };

    typedef mod_desc_t* mod_desc_ptr_t;
    typedef std::vector<mod_desc_ptr_t> mod_desc_ptr_set;

    class Resource {
    public:
      Resource():
        m_parent(nullptr)
      {

      }

      int rnet_init(ResourceNetwork* rnet, res_id_t id, res_t type, std::string uri) {
        m_parent = rnet;
        m_desc.id = id;
        m_desc.type = type;
        m_desc.uri = uri;
        m_desc.mod = this;
      }

      int rnet_deinit() {
        m_parent = nullptr;
        m_desc.id = 0;
        m_desc.type = nullptr;
        m_desc.uri = "";
        m_desc.mod = nullptr;
      }

      mod_desc_ptr_t getDescriptor() { return &m_desc; }

      virtual res_t getType() = 0;

    private:
      mod_desc_t m_desc;
      ResourceNetwork* m_parent;
    };

    typedef std::map<res_id_t, mod_desc_ptr_t> ResourceIdMap;
    typedef std::map<res_t, mod_desc_ptr_set> ResourceTypeMap;

  public:
    ResourceNetwork();

    int find(res_t, Resource**);
    int erase(res_id_t);

    int reg(Resource*, std::string = "");
    int dereg(Resource*);

  protected:
    res_id_t m_id_seq;

    ResourceIdMap mm_idMap;
    ResourceTypeMap mm_typeMap;
  };


  class TestRes : public ResourceNetwork::Resource
  {
  public:
    TestRes();

    ResourceNetwork::res_t getType();
    static ResourceNetwork::_res_t Type;

    int testPublicFn(int = 0);

  protected:
    res_data_t m_resource;
    Endpoint m_endpoints[1];
  };


  extern ResourceNetwork gResourceNetwork;

}


namespace tuum {
    void rnet_test();
}

#endif
