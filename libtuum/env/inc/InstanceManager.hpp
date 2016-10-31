/** @file  InstanceManager.hpp
 *  @brief Objects manager class template
 *
 *  @author Meelik Kiik (kiik.meelik@gmail.com)
 *  @date   August, 2015
 *  @version 0.1
 */

#ifndef GR_INSTANCE_MANAGER
#define GR_INSTANCE_MANAGER

#include "platform.hpp"

namespace gr {

  template<class T>
  class InstanceManager
  {
  public:
    typedef int8_t id_t;

    T** objects;
    id_t obj_N, obj_n = 0, obj_it = 0;

    InstanceManager(uint8_t N) {
      obj_N = N;
      objects = new T*[obj_N];

      for(id_t id = 0; id < obj_N; id++)
        objects[id] = nullptr;
    }

    ~InstanceManager() {
      for(id_t id = 0; id < obj_N; id++)
        if(objects[id] != nullptr) delete objects[id];

      delete objects;
    }

    id_t spawn(T* obj = nullptr) {
      if(obj_n >= obj_N) return -1;

      id_t id = -1;
      for(id_t ix = 0; ix < obj_N; ix++) {
        if(objects[ix] != nullptr) continue;

        id = ix;
        if(obj == nullptr)
          objects[id] = new T();
        else
          objects[id] = obj;

        ++obj_n;
        break;
      }

      return id;
    }

    int despawn(id_t id = -1) {
      if(objects[id] == nullptr) return 0;
      if(id == -1) id = obj_it;

      delete objects[id];
      objects[id] = nullptr;
      --obj_n;

      return 1;
    }

    T* get(id_t id) {
      return objects[id];
    }

    id_t size() {
      return obj_n;
    }

    T* next() {
      for(id_t n=0; n < obj_N; n++) {
        if(objects[obj_it] == nullptr) obj_it = (++obj_it) % obj_N;
        return objects[obj_it];
      }

      return nullptr;
    }

  };

}

#endif
