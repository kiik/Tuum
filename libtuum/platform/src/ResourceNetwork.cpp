
#include "ResourceNetwork.hpp"

namespace tuum {

  ResourceNetwork::ResourceNetwork():
    m_id_seq(1)
  {

  }

  int ResourceNetwork::reg(Resource* mod, std::string uri)
  {
    mod->rnet_init(this, m_id_seq++, mod->getType(), uri);
    mod_desc_ptr_t desc = mod->getDescriptor();
    mm_idMap[desc->id] = desc;

    auto it = mm_typeMap.find(desc->type);
    if(it != mm_typeMap.end()) {
      it->second.push_back(desc);
    } else {
      mm_typeMap[desc->type].push_back(desc);
    }

    return 0;
  }

  int ResourceNetwork::dereg(Resource* mod)
  {
    mod_desc_ptr_t desc = mod->getDescriptor();

    printf("erase ret=%i\n", erase(desc->id));

    mod->rnet_deinit();
    return 0;
  }

  int ResourceNetwork::find(res_t type, Resource** mod)
  {
    auto it = mm_typeMap.find(type);

    if(it != mm_typeMap.end()) {
      //TODO: Vector return support
      if(it->second.size() > 0) {
        *mod = it->second[0]->mod;
        return 0;
      }
    }

    return -1;
  }

  int ResourceNetwork::erase(res_id_t id) {
    auto it = mm_idMap.find(id);
    if(it == mm_idMap.end()) return -1;

    auto it2 = mm_typeMap.find(it->second->type);
    if(it2 == mm_typeMap.end()) return -2;

    auto desc_set = it2->second;
    auto it3 = std::find(desc_set.begin(), desc_set.end(), it->second);
    if(it3 == desc_set.end()) return -3;

    mm_idMap.erase(it);
    desc_set.erase(it3);

    //desc_set = it2->second;
    //it3 = std::find(desc_set.begin(), desc_set.end(), it->second);
    //if(it3 == desc_set.end()) return -4;


    return 0;
  }



  ResourceNetwork gResourceNetwork;

}


namespace tuum {

  ResourceNetwork::_res_t TestRes::Type;

  ResourceNetwork::res_t TestRes::getType() { return &TestRes::Type; }

  TestRes::TestRes()
  {
    auto argsf = new EAtomicType[1]{INT32};
    m_endpoints[0] = {"/testPublicFn", 1, argsf, INT32 };

    m_resource.nsp = "/TestRes/0";
    m_resource.epc = 1;
    m_resource.eps = (Endpoint*)&m_endpoints;

    printf("%s\n", m_resource.nsp.c_str());
    for(int i = 0; i < m_resource.epc; i++) {
      printf("* %s\n", m_resource.eps[i].uri.c_str());
    }
  }

  int TestRes::testPublicFn(int v) {

    return 0;
  }

  void rnet_test() {

    TestRes tmod;

    gResourceNetwork.reg(&tmod);

    TestRes* mod = nullptr;
    int res = gResourceNetwork.find(&TestRes::Type, (ResourceNetwork::Resource**)&mod);

    if(res < 0) {
      printf("[gResourceNetwork::find]'TestRes::Type' not found!\n");
    } else {
      printf("[gResourceNetwork::find]'TestRes::Type' found.\n");
    }

    if(mod) {
      printf("Found module: %i\n", mod->getDescriptor()->id);
    }

    mod = nullptr;
    gResourceNetwork.dereg(&tmod);

    if(res < 0) {
      printf("[gResourceNetwork::find]'TestRes::Type' not found!\n");
    } else {
      printf("[gResourceNetwork::find]'TestRes::Type' found.\n");
    }

  }

}
