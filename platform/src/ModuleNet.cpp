
#include "ModuleNet.hpp"

namespace tuum {

  ModuleNet::ModuleNet():
    m_id_seq(1)
  {

  }

  int ModuleNet::reg(Module* mod, std::string uri)
  {
    mod->mnet_init(m_id_seq++, mod->getType(), uri);
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

  int ModuleNet::dereg(Module* mod)
  {
    mod_desc_ptr_t desc = mod->getDescriptor();

    printf("erase ret=%i\n", erase(desc->id));

    mod->mnet_deinit();
    return 0;
  }

  int ModuleNet::find(mod_t type, Module** mod)
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

  int ModuleNet::erase(mod_id_t id) {
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



  ModuleNet gModuleNet;

}


namespace tuum {

  ModuleNet::_mod_t TestMod::Type;

  ModuleNet::mod_t TestMod::getType() { return &TestMod::Type; }



  TestMod::TestMod()
  {
    auto argsf = new EAtomicType[1]{INT32};
    m_endpoints[0] = {"/testPublicFn", 1, argsf, INT32 };

    m_resource.nsp = "/TestMod/0";
    m_resource.epc = 1;
    m_resource.eps = (Endpoint*)&m_endpoints;

    printf("%s\n", m_resource.nsp.c_str());
    for(int i = 0; i < m_resource.epc; i++) {
      printf("* %s\n", m_resource.eps[i].uri.c_str());
    }
  }

  int TestMod::testPublicFn(int v) {

    return 0;
  }

  void mnet_test() {

    TestMod tmod;

    gModuleNet.reg(&tmod);

    TestMod* mod = nullptr;
    int res = gModuleNet.find(&TestMod::Type, (ModuleNet::Module**)&mod);

    if(res < 0) {
      printf("[gModuleNet::find]'TestMod::Type' not found!\n");
    } else {
      printf("[gModuleNet::find]'TestMod::Type' found.\n");
    }

    if(mod) {
      printf("Found module: %i\n", mod->getDescriptor()->id);
    }

    mod = nullptr;
    gModuleNet.dereg(&tmod);

    if(res < 0) {
      printf("[gModuleNet::find]'TestMod::Type' not found!\n");
    } else {
      printf("[gModuleNet::find]'TestMod::Type' found.\n");
    }

  }

}
