 /**
  * The structures are defined for an elliptic PDE with the following restrictions:
  *  1. The number of thetas is equal to eight (T8).
  *  2. The problem contains nine load vectors (F9) and ten outputs (O10).
  *
  * The structures defined are:
  * 1. Theta --> parameter-dependent part of the PDE
  * 2. RBThetaExpansion
  */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTUREST8F9O10STEADYSTATE_H
#define DWARFELEPHANTRBSTRUCTUREST8F9O10STEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresA00ThetaConstant.h"
#include "DwarfElephantRBStructuresA0ThetaEqualMu0.h"
#include "DwarfElephantRBStructuresA0ThetaNormMu0.h"
#include "DwarfElephantRBStructuresA0ThetaNormMu1.h"
#include "DwarfElephantRBStructuresA1ThetaEqualMu1.h"
#include "DwarfElephantRBStructuresA1ThetaNormMu0.h"
#include "DwarfElephantRBStructuresA1ThetaNormMu1.h"
#include "DwarfElephantRBStructuresA2ThetaEqualMu2.h"
#include "DwarfElephantRBStructuresA2ThetaNormMu0.h"
#include "DwarfElephantRBStructuresA2ThetaNormMu1.h"
#include "DwarfElephantRBStructuresA3ThetaEqualMu3.h"
#include "DwarfElephantRBStructuresA4ThetaEqualMu4.h"
#include "DwarfElephantRBStructuresA5ThetaEqualMu5.h"
#include "DwarfElephantRBStructuresA6ThetaEqualMu6.h"
#include "DwarfElephantRBStructuresA7ThetaEqualMu7.h"


// Forward Declarations
namespace libMesh
{
 // class RBParameters;
 // class RBTheta;
  class RBThetaExpansion;
}

///The structures are defined for an elliptic PDE with the following restrictions: 1. The number of thetas is equal to eight (T8). 2. The problem contains nine load vectors (F9) and ten outputs (O10).

/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */

struct DwarfElephantRBT8F9O10SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBT8F9O10SteadyStateExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_A_theta(&_rb_theta);
    attach_A_theta(&_theta_a_0);

    attach_F_theta(&_rb_theta);
    attach_F_theta(&_theta_a_0);
    attach_F_theta(&_theta_a_1);
    attach_F_theta(&_theta_a_2);
    attach_F_theta(&_theta_a_3);
    attach_F_theta(&_theta_a_4);
    attach_F_theta(&_theta_a_5);
    attach_F_theta(&_theta_a_6);
    attach_F_theta(&_theta_a_7);

    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
  }
  // Member Variables
  DwarfElephantThetaA0EqualMu0 _theta_a_0;
  DwarfElephantThetaA1EqualMu1 _theta_a_1;
  DwarfElephantThetaA2EqualMu2 _theta_a_2;
  DwarfElephantThetaA3EqualMu3 _theta_a_3;
  DwarfElephantThetaA4EqualMu4 _theta_a_4;
  DwarfElephantThetaA5EqualMu5 _theta_a_5;
  DwarfElephantThetaA6EqualMu6 _theta_a_6;
  DwarfElephantThetaA7EqualMu7 _theta_a_7;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTUREST8F9O10STEADYSTATE_H
