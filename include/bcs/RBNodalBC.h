/**
 * This BC is required to use the RB method as it is provided by the
 * RB libMesh package. The RBNodalBC inherits from the NodalBC class. It
 * overwrites the function computeJacobian because for the RB method the
 * stiffness matrix is needed separated in its subdomain contributions. In
 * addition it overwrites the function computeResidual.
 */

///-------------------------------------------------------------------------
#ifndef RBNODALBC_H
#define RBNODALBC_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes
#include "libmesh/equation_systems.h"

// MOOSE includes
#include "NodalBC.h"
#include "MooseMesh.h"
#include "NonlinearSystemBase.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantInitializeRBSystem.h"
#include "CacheBoundaries.h"

///-------------------------------------------------------------------------
// Forward declarations
namespace libMesh
{
  class EquationSystems;
}

class MooseMesh;
class NonlinearSystemBase;
class CacheBoundaries;

class DwarfElephantInitializeRBSystem;
class RBNodalBC;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<RBNodalBC>();

///-------------------------------------------------------------------------
class RBNodalBC :
  public NodalBC
{

//----------------------------------PUBLIC----------------------------------
public:
  RBNodalBC(const InputParameters & parameters);

  /* Methods */
  virtual void computeResidual(NumericVector<Number> & residual) override;
  virtual void computeJacobian() override;

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  /* Attributes */
  bool _mesh_modified;
  const DwarfElephantInitializeRBSystem & _initialize_rb_system;

  Function * _function;
  CacheBoundaries * _cache_boundaries;
};

#endif /* RBNODALBC_H */
