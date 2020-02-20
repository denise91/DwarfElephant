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
#ifndef DWARFELEPHANTGEOM3DRBTHETAEXPANSION_RFA_H
#define DWARFELEPHANTGEOM3DRBTHETAEXPANSION_RFA_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"

#include "DwarfElephantGeom3DRBTheta_RFA.h"
#include "DwarfElephantMeshSubdomainJacobians.h"
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

struct Geom3DRBThetaExpansion : RBThetaExpansion
{
  Geom3DRBThetaExpansion()
  {
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_VesselCyl_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_VesselCyl_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_VesselCyl_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_BoundingBox_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_BoundingBox_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_BoundingBox_0);
  attach_A_theta(&_rb_theta);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_1);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_2);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_3);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_4);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_5);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_6);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_7);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_8);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_9);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_10);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_11);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_12);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_13);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_14);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_15);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_16);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_17);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_18);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_19);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_20);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_21);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_22);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_23);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_24);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_25);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_26);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_27);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_28);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_29);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_30);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_31);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_32);
    num_subdomains = 32;
}
  Geom3DRB_ATheta_DiffusionXX_maxZ1 Geom3DRB_ATheta_DiffusionXX_maxZ1_0;
  Geom3DRB_ATheta_DiffusionYY_maxZ1 Geom3DRB_ATheta_DiffusionYY_maxZ1_0;
  Geom3DRB_ATheta_DiffusionZZ_maxZ1 Geom3DRB_ATheta_DiffusionZZ_maxZ1_0;
  Geom3DRB_ATheta_DiffusionXX_maxZ2 Geom3DRB_ATheta_DiffusionXX_maxZ2_0;
  Geom3DRB_ATheta_DiffusionYY_maxZ2 Geom3DRB_ATheta_DiffusionYY_maxZ2_0;
  Geom3DRB_ATheta_DiffusionZZ_maxZ2 Geom3DRB_ATheta_DiffusionZZ_maxZ2_0;
  Geom3DRB_ATheta_DiffusionXX_maxZ3 Geom3DRB_ATheta_DiffusionXX_maxZ3_0;
  Geom3DRB_ATheta_DiffusionYY_maxZ3 Geom3DRB_ATheta_DiffusionYY_maxZ3_0;
  Geom3DRB_ATheta_DiffusionZZ_maxZ3 Geom3DRB_ATheta_DiffusionZZ_maxZ3_0;
  Geom3DRB_ATheta_DiffusionXX_maxZ4 Geom3DRB_ATheta_DiffusionXX_maxZ4_0;
  Geom3DRB_ATheta_DiffusionYY_maxZ4 Geom3DRB_ATheta_DiffusionYY_maxZ4_0;
  Geom3DRB_ATheta_DiffusionZZ_maxZ4 Geom3DRB_ATheta_DiffusionZZ_maxZ4_0;
  Geom3DRB_ATheta_DiffusionXX_maxZ5 Geom3DRB_ATheta_DiffusionXX_maxZ5_0;
  Geom3DRB_ATheta_DiffusionYY_maxZ5 Geom3DRB_ATheta_DiffusionYY_maxZ5_0;
  Geom3DRB_ATheta_DiffusionZZ_maxZ5 Geom3DRB_ATheta_DiffusionZZ_maxZ5_0;
  Geom3DRB_ATheta_DiffusionXX_minX1 Geom3DRB_ATheta_DiffusionXX_minX1_0;
  Geom3DRB_ATheta_DiffusionYY_minX1 Geom3DRB_ATheta_DiffusionYY_minX1_0;
  Geom3DRB_ATheta_DiffusionZZ_minX1 Geom3DRB_ATheta_DiffusionZZ_minX1_0;
  Geom3DRB_ATheta_DiffusionXX_minX2 Geom3DRB_ATheta_DiffusionXX_minX2_0;
  Geom3DRB_ATheta_DiffusionYY_minX2 Geom3DRB_ATheta_DiffusionYY_minX2_0;
  Geom3DRB_ATheta_DiffusionZZ_minX2 Geom3DRB_ATheta_DiffusionZZ_minX2_0;
  Geom3DRB_ATheta_DiffusionXX_minX3 Geom3DRB_ATheta_DiffusionXX_minX3_0;
  Geom3DRB_ATheta_DiffusionYY_minX3 Geom3DRB_ATheta_DiffusionYY_minX3_0;
  Geom3DRB_ATheta_DiffusionZZ_minX3 Geom3DRB_ATheta_DiffusionZZ_minX3_0;
  Geom3DRB_ATheta_DiffusionXX_minX4 Geom3DRB_ATheta_DiffusionXX_minX4_0;
  Geom3DRB_ATheta_DiffusionYY_minX4 Geom3DRB_ATheta_DiffusionYY_minX4_0;
  Geom3DRB_ATheta_DiffusionZZ_minX4 Geom3DRB_ATheta_DiffusionZZ_minX4_0;
  Geom3DRB_ATheta_DiffusionXX_minX5 Geom3DRB_ATheta_DiffusionXX_minX5_0;
  Geom3DRB_ATheta_DiffusionYY_minX5 Geom3DRB_ATheta_DiffusionYY_minX5_0;
  Geom3DRB_ATheta_DiffusionZZ_minX5 Geom3DRB_ATheta_DiffusionZZ_minX5_0;
  Geom3DRB_ATheta_DiffusionXX_maxY1 Geom3DRB_ATheta_DiffusionXX_maxY1_0;
  Geom3DRB_ATheta_DiffusionYY_maxY1 Geom3DRB_ATheta_DiffusionYY_maxY1_0;
  Geom3DRB_ATheta_DiffusionZZ_maxY1 Geom3DRB_ATheta_DiffusionZZ_maxY1_0;
  Geom3DRB_ATheta_DiffusionXX_maxY2 Geom3DRB_ATheta_DiffusionXX_maxY2_0;
  Geom3DRB_ATheta_DiffusionYY_maxY2 Geom3DRB_ATheta_DiffusionYY_maxY2_0;
  Geom3DRB_ATheta_DiffusionZZ_maxY2 Geom3DRB_ATheta_DiffusionZZ_maxY2_0;
  Geom3DRB_ATheta_DiffusionXX_maxY3 Geom3DRB_ATheta_DiffusionXX_maxY3_0;
  Geom3DRB_ATheta_DiffusionYY_maxY3 Geom3DRB_ATheta_DiffusionYY_maxY3_0;
  Geom3DRB_ATheta_DiffusionZZ_maxY3 Geom3DRB_ATheta_DiffusionZZ_maxY3_0;
  Geom3DRB_ATheta_DiffusionXX_maxY4 Geom3DRB_ATheta_DiffusionXX_maxY4_0;
  Geom3DRB_ATheta_DiffusionYY_maxY4 Geom3DRB_ATheta_DiffusionYY_maxY4_0;
  Geom3DRB_ATheta_DiffusionZZ_maxY4 Geom3DRB_ATheta_DiffusionZZ_maxY4_0;
  Geom3DRB_ATheta_DiffusionXX_maxY5 Geom3DRB_ATheta_DiffusionXX_maxY5_0;
  Geom3DRB_ATheta_DiffusionYY_maxY5 Geom3DRB_ATheta_DiffusionYY_maxY5_0;
  Geom3DRB_ATheta_DiffusionZZ_maxY5 Geom3DRB_ATheta_DiffusionZZ_maxY5_0;
  Geom3DRB_ATheta_DiffusionXX_maxX1 Geom3DRB_ATheta_DiffusionXX_maxX1_0;
  Geom3DRB_ATheta_DiffusionYY_maxX1 Geom3DRB_ATheta_DiffusionYY_maxX1_0;
  Geom3DRB_ATheta_DiffusionZZ_maxX1 Geom3DRB_ATheta_DiffusionZZ_maxX1_0;
  Geom3DRB_ATheta_DiffusionXX_maxX2 Geom3DRB_ATheta_DiffusionXX_maxX2_0;
  Geom3DRB_ATheta_DiffusionYY_maxX2 Geom3DRB_ATheta_DiffusionYY_maxX2_0;
  Geom3DRB_ATheta_DiffusionZZ_maxX2 Geom3DRB_ATheta_DiffusionZZ_maxX2_0;
  Geom3DRB_ATheta_DiffusionXX_maxX3 Geom3DRB_ATheta_DiffusionXX_maxX3_0;
  Geom3DRB_ATheta_DiffusionYY_maxX3 Geom3DRB_ATheta_DiffusionYY_maxX3_0;
  Geom3DRB_ATheta_DiffusionZZ_maxX3 Geom3DRB_ATheta_DiffusionZZ_maxX3_0;
  Geom3DRB_ATheta_DiffusionXX_maxX4 Geom3DRB_ATheta_DiffusionXX_maxX4_0;
  Geom3DRB_ATheta_DiffusionYY_maxX4 Geom3DRB_ATheta_DiffusionYY_maxX4_0;
  Geom3DRB_ATheta_DiffusionZZ_maxX4 Geom3DRB_ATheta_DiffusionZZ_maxX4_0;
  Geom3DRB_ATheta_DiffusionXX_maxX5 Geom3DRB_ATheta_DiffusionXX_maxX5_0;
  Geom3DRB_ATheta_DiffusionYY_maxX5 Geom3DRB_ATheta_DiffusionYY_maxX5_0;
  Geom3DRB_ATheta_DiffusionZZ_maxX5 Geom3DRB_ATheta_DiffusionZZ_maxX5_0;
  Geom3DRB_ATheta_DiffusionXX_minY1 Geom3DRB_ATheta_DiffusionXX_minY1_0;
  Geom3DRB_ATheta_DiffusionYY_minY1 Geom3DRB_ATheta_DiffusionYY_minY1_0;
  Geom3DRB_ATheta_DiffusionZZ_minY1 Geom3DRB_ATheta_DiffusionZZ_minY1_0;
  Geom3DRB_ATheta_DiffusionXX_minY2 Geom3DRB_ATheta_DiffusionXX_minY2_0;
  Geom3DRB_ATheta_DiffusionYY_minY2 Geom3DRB_ATheta_DiffusionYY_minY2_0;
  Geom3DRB_ATheta_DiffusionZZ_minY2 Geom3DRB_ATheta_DiffusionZZ_minY2_0;
  Geom3DRB_ATheta_DiffusionXX_minY3 Geom3DRB_ATheta_DiffusionXX_minY3_0;
  Geom3DRB_ATheta_DiffusionYY_minY3 Geom3DRB_ATheta_DiffusionYY_minY3_0;
  Geom3DRB_ATheta_DiffusionZZ_minY3 Geom3DRB_ATheta_DiffusionZZ_minY3_0;
  Geom3DRB_ATheta_DiffusionXX_minY4 Geom3DRB_ATheta_DiffusionXX_minY4_0;
  Geom3DRB_ATheta_DiffusionYY_minY4 Geom3DRB_ATheta_DiffusionYY_minY4_0;
  Geom3DRB_ATheta_DiffusionZZ_minY4 Geom3DRB_ATheta_DiffusionZZ_minY4_0;
  Geom3DRB_ATheta_DiffusionXX_minY5 Geom3DRB_ATheta_DiffusionXX_minY5_0;
  Geom3DRB_ATheta_DiffusionYY_minY5 Geom3DRB_ATheta_DiffusionYY_minY5_0;
  Geom3DRB_ATheta_DiffusionZZ_minY5 Geom3DRB_ATheta_DiffusionZZ_minY5_0;
  Geom3DRB_ATheta_DiffusionXX_minZ1 Geom3DRB_ATheta_DiffusionXX_minZ1_0;
  Geom3DRB_ATheta_DiffusionYY_minZ1 Geom3DRB_ATheta_DiffusionYY_minZ1_0;
  Geom3DRB_ATheta_DiffusionZZ_minZ1 Geom3DRB_ATheta_DiffusionZZ_minZ1_0;
  Geom3DRB_ATheta_DiffusionXX_minZ2 Geom3DRB_ATheta_DiffusionXX_minZ2_0;
  Geom3DRB_ATheta_DiffusionYY_minZ2 Geom3DRB_ATheta_DiffusionYY_minZ2_0;
  Geom3DRB_ATheta_DiffusionZZ_minZ2 Geom3DRB_ATheta_DiffusionZZ_minZ2_0;
  Geom3DRB_ATheta_DiffusionXX_minZ3 Geom3DRB_ATheta_DiffusionXX_minZ3_0;
  Geom3DRB_ATheta_DiffusionYY_minZ3 Geom3DRB_ATheta_DiffusionYY_minZ3_0;
  Geom3DRB_ATheta_DiffusionZZ_minZ3 Geom3DRB_ATheta_DiffusionZZ_minZ3_0;
  Geom3DRB_ATheta_DiffusionXX_minZ4 Geom3DRB_ATheta_DiffusionXX_minZ4_0;
  Geom3DRB_ATheta_DiffusionYY_minZ4 Geom3DRB_ATheta_DiffusionYY_minZ4_0;
  Geom3DRB_ATheta_DiffusionZZ_minZ4 Geom3DRB_ATheta_DiffusionZZ_minZ4_0;
  Geom3DRB_ATheta_DiffusionXX_minZ5 Geom3DRB_ATheta_DiffusionXX_minZ5_0;
  Geom3DRB_ATheta_DiffusionYY_minZ5 Geom3DRB_ATheta_DiffusionYY_minZ5_0;
  Geom3DRB_ATheta_DiffusionZZ_minZ5 Geom3DRB_ATheta_DiffusionZZ_minZ5_0;
  Geom3DRB_ATheta_DiffusionXX_VesselCyl Geom3DRB_ATheta_DiffusionXX_VesselCyl_0;
  Geom3DRB_ATheta_DiffusionYY_VesselCyl Geom3DRB_ATheta_DiffusionYY_VesselCyl_0;
  Geom3DRB_ATheta_DiffusionZZ_VesselCyl Geom3DRB_ATheta_DiffusionZZ_VesselCyl_0;
  Geom3DRB_ATheta_DiffusionXX_BoundingBox Geom3DRB_ATheta_DiffusionXX_BoundingBox_0;
  Geom3DRB_ATheta_DiffusionYY_BoundingBox Geom3DRB_ATheta_DiffusionYY_BoundingBox_0;
  Geom3DRB_ATheta_DiffusionZZ_BoundingBox Geom3DRB_ATheta_DiffusionZZ_BoundingBox_0;
  RBTheta _rb_theta;
public:
    subdomain_1 rbtheta_subdomain_1;
    subdomain_2 rbtheta_subdomain_2;
    subdomain_3 rbtheta_subdomain_3;
    subdomain_4 rbtheta_subdomain_4;
    subdomain_5 rbtheta_subdomain_5;
    subdomain_6 rbtheta_subdomain_6;
    subdomain_7 rbtheta_subdomain_7;
    subdomain_8 rbtheta_subdomain_8;
    subdomain_9 rbtheta_subdomain_9;
    subdomain_10 rbtheta_subdomain_10;
    subdomain_11 rbtheta_subdomain_11;
    subdomain_12 rbtheta_subdomain_12;
    subdomain_13 rbtheta_subdomain_13;
    subdomain_14 rbtheta_subdomain_14;
    subdomain_15 rbtheta_subdomain_15;
    subdomain_16 rbtheta_subdomain_16;
    subdomain_17 rbtheta_subdomain_17;
    subdomain_18 rbtheta_subdomain_18;
    subdomain_19 rbtheta_subdomain_19;
    subdomain_20 rbtheta_subdomain_20;
    subdomain_21 rbtheta_subdomain_21;
    subdomain_22 rbtheta_subdomain_22;
    subdomain_23 rbtheta_subdomain_23;
    subdomain_24 rbtheta_subdomain_24;
    subdomain_25 rbtheta_subdomain_25;
    subdomain_26 rbtheta_subdomain_26;
    subdomain_27 rbtheta_subdomain_27;
    subdomain_28 rbtheta_subdomain_28;
    subdomain_29 rbtheta_subdomain_29;
    subdomain_30 rbtheta_subdomain_30;
    subdomain_31 rbtheta_subdomain_31;
    subdomain_32 rbtheta_subdomain_32;
    std::vector<RBTheta *> subdomain_jac_rbthetas;
    unsigned int num_subdomains;
};

//------------------------------
#endif // DWARFELEPHANTGEOM3DRBTHETAEXPANSION_RFA_H