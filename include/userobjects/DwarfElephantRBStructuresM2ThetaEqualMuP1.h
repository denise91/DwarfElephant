///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTURESM2THETAEQUALMUP1_H
#define DWARFELEPHANTRBSTRUCTURESM2THETAEQUALMUP1_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"


// Forward Declarations
namespace libMesh
{
  class RBParameters;
  class RBTheta;
}

///-----------------------------------THETA---------------------------------
/**
 * Please take the name convention of this package for the mu object into
 * account to ensure a gernal useability of your class.
 */

struct DwarfElephantThetaM2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return 0. * _mu.get_value("mu_2");
  }
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTURESM2THETAEQUALMUP1_H
