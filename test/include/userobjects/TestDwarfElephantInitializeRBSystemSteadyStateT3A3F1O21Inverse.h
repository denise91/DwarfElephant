/* This UserObject is required to initialitze the RB system structure
 * and transfer for the steady state case.
 */

///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "TestDwarfElephantRBEvaluationSteadyStateT3A3F1O21Inverse.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantInitializeRBSystemSteadyState;
class TestDwarfElephantRBEvaluationSteadyStateT3A3F1O21Inverse;
class TestDwarfElephantInitializeRBSystemSteadyStateT3A3F1O21Inverse;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantInitializeRBSystemSteadyStateT3A3F1O21Inverse>();

///This UserObject is required to initialitze the RB system structure and transfer for the steady state case.
class TestDwarfElephantInitializeRBSystemSteadyStateT3A3F1O21Inverse :
  public DwarfElephantInitializeRBSystemSteadyState
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantInitializeRBSystemSteadyStateT3A3F1O21Inverse(const InputParameters & params);

    virtual void execute() override;
};
