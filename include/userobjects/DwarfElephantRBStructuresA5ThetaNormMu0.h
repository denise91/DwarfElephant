///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTURESA5THETANORMMU0_H
#define DWARFELEPHANTRBSTRUCTURESA5THETANORMMU0_H

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

/**
 * Please take the name convention of this package for the mu object into
 * account to ensure a gernal useability of your class.
 */

struct DwarfElephantThetaA5NormMu0 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return _mu.get_value("mu_5")/_mu.get_value("mu_0");
  }
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTURESA5THETANORMMU0_H
