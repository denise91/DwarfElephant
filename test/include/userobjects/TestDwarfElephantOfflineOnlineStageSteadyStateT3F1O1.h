/**
 * This UserObject implements the Offline and Online stage of the RB method
 * for the steady state case.
 */

///-------------------------------------------------------------------------
#ifndef TestDwarfElephantOfflineOnlineStageSteadyStateT3F1O1_H
#define TestDwarfElephantOfflineOnlineStageSteadyStateT3F1O1_H

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantOfflineOnlineStageSteadyState.h"
#include "TestDwarfElephantRBEvaluationSteadyStateT3F1O1.h"


///-------------------------------------------------------------------------
// Forward Declarations
class TestDwarfElephantOfflineOnlineStageSteadyStateT3F1O1;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantOfflineOnlineStageSteadyStateT3F1O1>();

///This UserObject implements the Offline and Online stage of the RB method for the steady state case.
class TestDwarfElephantOfflineOnlineStageSteadyStateT3F1O1 :
  public DwarfElephantOfflineOnlineStageSteadyState
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantOfflineOnlineStageSteadyStateT3F1O1(const InputParameters & params);


    /* Methods */
    virtual void execute() override;
};
///-------------------------------------------------------------------------
#endif // TESTDwarfElephantOfflineOnlineStageSteadyStateT3F1O1_H
