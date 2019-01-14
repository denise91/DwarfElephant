///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTURESA2THETAEQUALMU2TIMESMU4DIVIDEDBYMU5_H
#define DWARFELEPHANTRBSTRUCTURESA2THETAEQUALMU2TIMESMU4DIVIDEDBYMU5_H

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

struct DwarfElephantThetaA2EqualMu2TimesMu4DividedByMu5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return (_mu.get_value("mu_2")*(_mu.get_value("mu_4")*(1/_mu.get_value("mu_5"))));
  }
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTURESA2THETAEQUALMU2TIMESMU4DIVIDEDBYMU5_H
