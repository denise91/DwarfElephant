/**
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to two (T2) and the number of Aq to two (A2).
 *  2. The problem contains one Fq (F1) and five outputs (O5).
 *
 * The structures defined are:
 * 1. Theta --> parameter-dependent part of the PDE
 * 2. RBThetaExpansion
 */


///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu0.h"
#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu1.h"


// Forward Declarations
namespace libMesh
{
  class RBThetaExpansion;
}

struct DwarfElephantRBT2A2F1O5SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBT2A2F1O5SteadyStateExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);

    attach_F_theta(&_rb_theta);

    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);

  }
  // Member Variables
  DwarfElephantThetaEqualScalarDividedByMu0 _theta_a_0;
  DwarfElephantThetaEqualScalarDividedByMu1 _theta_a_1;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
