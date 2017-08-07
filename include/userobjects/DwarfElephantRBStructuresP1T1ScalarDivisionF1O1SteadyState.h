 /**
  * The structures are defined for an elliptic PDE with the following restrictions:
  *  1. The parameter dimension p is equal to one (P1).
  *  2. The number of thetas is equal to one (T1).
  *  3. Theta is equal to mu (for implementing other relationships,please
  *     follow the structure of these implementation for a general usability)
  *     (Equal).
  *  4. The problem contains one load vector (F1) and one output (O1).
  *
  * The structures defined are:
  * 1. Theta --> parameter-dependent part of the PDE
  * 2. RBThetaExpansion
  */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTURESP1T1SCALARDIVISIONF1O1STEADYSTATE_H
#define DWARFELEPHANTRBSTRUCTURESP1T1SCALARDIVISIONF1O1STEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresA0ThetaEqualScalarOverMuP1.h"


// Forward Declarations
namespace libMesh
{
 // class RBParameters;
 // class RBTheta;
  class RBThetaExpansion;
}

///----------------------------RBTHETAEXPANSION-----------------------------
/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */

struct DwarfElephantRBP1T1ScalarDivisionF1O1SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBP1T1ScalarDivisionF1O1SteadyStateExpansion()
  {
    attach_A_theta(&_theta_a_0);

    attach_F_theta(&_rb_theta);

    attach_output_theta(&_rb_theta);

  }
  // Member Variables
  DwarfElephantThetaA0ScalarOverMu _theta_a_0;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTURESP1T1SCALARDIVISIONF1O1STEADYSTATE_H
