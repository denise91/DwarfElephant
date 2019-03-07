/**
  * The structures are defined for an elliptic PDE with the following restrictions:
  *  1. The number of thetas is equal to one (T1).
  *  2. The problem contains one load vector (F1) and one output (O1).
  *
  * The structures defined are:
  * 1. Theta --> parameter-dependent part of the PDE
  * 2. RBThetaExpansion
  */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTGEOM2DRBTHETAEXPANSION_RBNICS_H
#define DWARFELEPHANTGEOM2DRBTHETAEXPANSION_RBNICS_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"

#include "DwarfElephantGeom2DRBTheta_RBNICS.h"
// Forward Declarations
namespace libMesh
{
  class RBThetaExpansion;
}
///----------------------------RBTHETAEXPANSION-----------------------------
/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */

struct Geom2DRBThetaExpansion : RBThetaExpansion
{
  Geom2DRBThetaExpansion()
  {
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXX_maxZ1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXY_maxZ1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYX_maxZ1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYY_maxZ1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXX_maxZ2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXY_maxZ2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYX_maxZ2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYY_maxZ2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXX_maxX1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXY_maxX1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYX_maxX1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYY_maxX1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXX_maxX2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXY_maxX2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYX_maxX2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYY_maxX2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXX_minZ1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXY_minZ1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYX_minZ1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYY_minZ1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXX_minZ2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXY_minZ2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYX_minZ2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYY_minZ2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXX_minX1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXY_minX1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYX_minX1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYY_minX1_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXX_minX2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXY_minX2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYX_minX2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYY_minX2_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionXX_BoundingBox_0);
  attach_A_theta(&Geom2DRB_ATheta_DiffusionYY_BoundingBox_0);
  attach_A_theta(&Geom2DRB_ATheta_Perfusion_BoundingBox_0);
  attach_A_theta(&_rb_theta);
}
  Geom2DRB_ATheta_DiffusionXX_maxZ1 Geom2DRB_ATheta_DiffusionXX_maxZ1_0;
  Geom2DRB_ATheta_DiffusionXY_maxZ1 Geom2DRB_ATheta_DiffusionXY_maxZ1_0;
  Geom2DRB_ATheta_DiffusionYX_maxZ1 Geom2DRB_ATheta_DiffusionYX_maxZ1_0;
  Geom2DRB_ATheta_DiffusionYY_maxZ1 Geom2DRB_ATheta_DiffusionYY_maxZ1_0;
  Geom2DRB_ATheta_DiffusionXX_maxZ2 Geom2DRB_ATheta_DiffusionXX_maxZ2_0;
  Geom2DRB_ATheta_DiffusionXY_maxZ2 Geom2DRB_ATheta_DiffusionXY_maxZ2_0;
  Geom2DRB_ATheta_DiffusionYX_maxZ2 Geom2DRB_ATheta_DiffusionYX_maxZ2_0;
  Geom2DRB_ATheta_DiffusionYY_maxZ2 Geom2DRB_ATheta_DiffusionYY_maxZ2_0;
  Geom2DRB_ATheta_DiffusionXX_maxX1 Geom2DRB_ATheta_DiffusionXX_maxX1_0;
  Geom2DRB_ATheta_DiffusionXY_maxX1 Geom2DRB_ATheta_DiffusionXY_maxX1_0;
  Geom2DRB_ATheta_DiffusionYX_maxX1 Geom2DRB_ATheta_DiffusionYX_maxX1_0;
  Geom2DRB_ATheta_DiffusionYY_maxX1 Geom2DRB_ATheta_DiffusionYY_maxX1_0;
  Geom2DRB_ATheta_DiffusionXX_maxX2 Geom2DRB_ATheta_DiffusionXX_maxX2_0;
  Geom2DRB_ATheta_DiffusionXY_maxX2 Geom2DRB_ATheta_DiffusionXY_maxX2_0;
  Geom2DRB_ATheta_DiffusionYX_maxX2 Geom2DRB_ATheta_DiffusionYX_maxX2_0;
  Geom2DRB_ATheta_DiffusionYY_maxX2 Geom2DRB_ATheta_DiffusionYY_maxX2_0;
  Geom2DRB_ATheta_DiffusionXX_minZ1 Geom2DRB_ATheta_DiffusionXX_minZ1_0;
  Geom2DRB_ATheta_DiffusionXY_minZ1 Geom2DRB_ATheta_DiffusionXY_minZ1_0;
  Geom2DRB_ATheta_DiffusionYX_minZ1 Geom2DRB_ATheta_DiffusionYX_minZ1_0;
  Geom2DRB_ATheta_DiffusionYY_minZ1 Geom2DRB_ATheta_DiffusionYY_minZ1_0;
  Geom2DRB_ATheta_DiffusionXX_minZ2 Geom2DRB_ATheta_DiffusionXX_minZ2_0;
  Geom2DRB_ATheta_DiffusionXY_minZ2 Geom2DRB_ATheta_DiffusionXY_minZ2_0;
  Geom2DRB_ATheta_DiffusionYX_minZ2 Geom2DRB_ATheta_DiffusionYX_minZ2_0;
  Geom2DRB_ATheta_DiffusionYY_minZ2 Geom2DRB_ATheta_DiffusionYY_minZ2_0;
  Geom2DRB_ATheta_DiffusionXX_minX1 Geom2DRB_ATheta_DiffusionXX_minX1_0;
  Geom2DRB_ATheta_DiffusionXY_minX1 Geom2DRB_ATheta_DiffusionXY_minX1_0;
  Geom2DRB_ATheta_DiffusionYX_minX1 Geom2DRB_ATheta_DiffusionYX_minX1_0;
  Geom2DRB_ATheta_DiffusionYY_minX1 Geom2DRB_ATheta_DiffusionYY_minX1_0;
  Geom2DRB_ATheta_DiffusionXX_minX2 Geom2DRB_ATheta_DiffusionXX_minX2_0;
  Geom2DRB_ATheta_DiffusionXY_minX2 Geom2DRB_ATheta_DiffusionXY_minX2_0;
  Geom2DRB_ATheta_DiffusionYX_minX2 Geom2DRB_ATheta_DiffusionYX_minX2_0;
  Geom2DRB_ATheta_DiffusionYY_minX2 Geom2DRB_ATheta_DiffusionYY_minX2_0;
  Geom2DRB_ATheta_DiffusionXX_BoundingBox Geom2DRB_ATheta_DiffusionXX_BoundingBox_0;
  Geom2DRB_ATheta_DiffusionYY_BoundingBox Geom2DRB_ATheta_DiffusionYY_BoundingBox_0;
  Geom2DRB_ATheta_Perfusion_BoundingBox Geom2DRB_ATheta_Perfusion_BoundingBox_0;
  RBTheta _rb_theta;
};

//------------------------------
#endif // DWARFELEPHANTGEOM2DRBTHETAEXPANSION_RBNICS_H