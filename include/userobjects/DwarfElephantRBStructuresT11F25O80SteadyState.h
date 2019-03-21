 /**
  * The structures are defined for an elliptic PDE with the following restrictions:
  *  1. The number of thetas is equal to eleven (T11).
  *  2. The problem contains 25 load vectors (F25) and 80 outputs (O80).
  *
  * The structures defined are:
  * 1. Theta --> parameter-dependent part of the PDE
  * 2. RBThetaExpansion
  */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTUREST11F28O80STEADYSTATE_H
#define DWARFELEPHANTRBSTRUCTUREST11F28O80STEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresA0ThetaEqualMu0.h"
#include "DwarfElephantRBStructuresA1ThetaEqualMu1.h"
#include "DwarfElephantRBStructuresA2ThetaEqualMu2.h"
#include "DwarfElephantRBStructuresA3ThetaEqualMu3.h"
#include "DwarfElephantRBStructuresA4ThetaEqualMu4.h"
#include "DwarfElephantRBStructuresA5ThetaEqualMu5.h"
#include "DwarfElephantRBStructuresA6ThetaEqualMu6.h"
#include "DwarfElephantRBStructuresA7ThetaEqualMu7.h"
#include "DwarfElephantRBStructuresA8ThetaEqualMu8.h"
#include "DwarfElephantRBStructuresA0ThetaEqualMu0TimesMu8.h"
#include "DwarfElephantRBStructuresA1ThetaEqualMu1TimesMu8.h"
#include "DwarfElephantRBStructuresA2ThetaEqualMu2TimesMu8.h"
#include "DwarfElephantRBStructuresA3ThetaEqualMu3TimesMu8.h"
#include "DwarfElephantRBStructuresA4ThetaEqualMu4TimesMu8.h"
#include "DwarfElephantRBStructuresA5ThetaEqualMu5TimesMu8.h"
#include "DwarfElephantRBStructuresA6ThetaEqualMu6TimesMu8.h"
#include "DwarfElephantRBStructuresA7ThetaEqualMu7TimesMu8.h"
#include "DwarfElephantRBStructuresA0ThetaEqualMu0TimesMu9.h"
#include "DwarfElephantRBStructuresA1ThetaEqualMu1TimesMu9.h"
#include "DwarfElephantRBStructuresA2ThetaEqualMu2TimesMu9.h"
#include "DwarfElephantRBStructuresA3ThetaEqualMu3TimesMu9.h"
#include "DwarfElephantRBStructuresA4ThetaEqualMu4TimesMu9.h"
#include "DwarfElephantRBStructuresA5ThetaEqualMu5TimesMu9.h"
#include "DwarfElephantRBStructuresA6ThetaEqualMu6TimesMu9.h"
#include "DwarfElephantRBStructuresA7ThetaEqualMu7TimesMu9.h"
#include "DwarfElephantRBStructuresA0ThetaEqualMu0TimesMu10.h"
#include "DwarfElephantRBStructuresA1ThetaEqualMu1TimesMu10.h"
#include "DwarfElephantRBStructuresA2ThetaEqualMu2TimesMu10.h"
#include "DwarfElephantRBStructuresA3ThetaEqualMu3TimesMu10.h"
#include "DwarfElephantRBStructuresA4ThetaEqualMu4TimesMu10.h"
#include "DwarfElephantRBStructuresA5ThetaEqualMu5TimesMu10.h"
#include "DwarfElephantRBStructuresA6ThetaEqualMu6TimesMu10.h"
#include "DwarfElephantRBStructuresA7ThetaEqualMu7TimesMu10.h"


// Forward Declarations
namespace libMesh
{
 // class RBParameters;
 // class RBTheta;
  class RBThetaExpansion;
}

///The structures are defined for an elliptic PDE with the following restrictions: 1. The number of thetas is equal to nine (T9). 2. The problem contains two load vectors (F2) and 80 outputs (O80).

/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */

struct DwarfElephantRBT11F25O80SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBT11F25O80SteadyStateExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);
    attach_A_theta(&_theta_a_3);
    attach_A_theta(&_theta_a_4);
    attach_A_theta(&_theta_a_5);
    attach_A_theta(&_theta_a_6);
    attach_A_theta(&_theta_a_7);

    attach_F_theta(&_rb_theta);
    attach_F_theta(&_theta_f_0);
    attach_F_theta(&_theta_f_1);
    attach_F_theta(&_theta_f_2);
    attach_F_theta(&_theta_f_3);
    attach_F_theta(&_theta_f_4);
    attach_F_theta(&_theta_f_5);
    attach_F_theta(&_theta_f_6);
    attach_F_theta(&_theta_f_7);
    attach_F_theta(&_theta_f_8);
    attach_F_theta(&_theta_f_9);
    attach_F_theta(&_theta_f_10);
    attach_F_theta(&_theta_f_11);
    attach_F_theta(&_theta_f_12);
    attach_F_theta(&_theta_f_13);
    attach_F_theta(&_theta_f_14);
    attach_F_theta(&_theta_f_15);
    attach_F_theta(&_theta_f_16);
    attach_F_theta(&_theta_f_17);
    attach_F_theta(&_theta_f_18);
    attach_F_theta(&_theta_f_19);
    attach_F_theta(&_theta_f_20);
    attach_F_theta(&_theta_f_21);
    attach_F_theta(&_theta_f_22);
    attach_F_theta(&_theta_f_23);

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
  DwarfElephantThetaA0EqualMu0TimesMu8 _theta_f_0;
  DwarfElephantThetaA1EqualMu1TimesMu8 _theta_f_1;
  DwarfElephantThetaA2EqualMu2TimesMu8 _theta_f_2;
  DwarfElephantThetaA3EqualMu3TimesMu8 _theta_f_3;
  DwarfElephantThetaA4EqualMu4TimesMu8 _theta_f_4;
  DwarfElephantThetaA5EqualMu5TimesMu8 _theta_f_5;
  DwarfElephantThetaA6EqualMu6TimesMu8 _theta_f_6;
  DwarfElephantThetaA7EqualMu7TimesMu8 _theta_f_7;
  DwarfElephantThetaA0EqualMu0TimesMu9 _theta_f_8;
  DwarfElephantThetaA1EqualMu1TimesMu9 _theta_f_9;
  DwarfElephantThetaA2EqualMu2TimesMu9 _theta_f_10;
  DwarfElephantThetaA3EqualMu3TimesMu9 _theta_f_11;
  DwarfElephantThetaA4EqualMu4TimesMu9 _theta_f_12;
  DwarfElephantThetaA5EqualMu5TimesMu9 _theta_f_13;
  DwarfElephantThetaA6EqualMu6TimesMu9 _theta_f_14;
  DwarfElephantThetaA7EqualMu7TimesMu9 _theta_f_15;
  DwarfElephantThetaA0EqualMu0TimesMu10 _theta_f_16;
  DwarfElephantThetaA1EqualMu1TimesMu10 _theta_f_17;
  DwarfElephantThetaA2EqualMu2TimesMu10 _theta_f_18;
  DwarfElephantThetaA3EqualMu3TimesMu10 _theta_f_19;
  DwarfElephantThetaA4EqualMu4TimesMu10 _theta_f_20;
  DwarfElephantThetaA5EqualMu5TimesMu10 _theta_f_21;
  DwarfElephantThetaA6EqualMu6TimesMu10 _theta_f_22;
  DwarfElephantThetaA7EqualMu7TimesMu10 _theta_f_23;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTUREST11F28O980STEADYSTATE_H
