/** @file TSMeshFilter.hpp
 *  @brief Mesh filter component.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#ifndef TS_MESH_FILTER_H
#define TS_MESH_FILTER_H

#include "3dcore/TSMesh.hpp"
#include "3dcore/TSComponent.hpp"

namespace tuum { namespace ts {

  class MeshFilter : public Component {
  public:
    MeshFilter();

    void setMesh(Mesh*);
    Mesh* getMesh();

    static TSOType type;
    TSOType* getType() const;

  private:
    Mesh* mesh;
  };

}}

#endif
