#include "DwarfElephantRBIntegratedBC.h"
#include "SubProblem.h"
#include "SystemBase.h"
#include "MooseVariableFE.h"
#include "MooseVariableScalar.h"
#include "Assembly.h"

// libMesh includes
#include "libmesh/quadrature.h"

template<>
InputParameters validParams<DwarfElephantRBIntegratedBC>()
{
  InputParameters params = validParams<IntegratedBC>();

  params.addParam<bool>("use_displaced", false, "Enable/disable the use of the displaced mesh for the data retrieving.");
  params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for initializing the RB system");
  params.addParam<std::string>("simulation_type", "steady", "Determines whether the simulation is steady state or transient.");
  params.addParam<unsigned int>("ID_Aq", 0, "ID of the current stiffness matrix.");
  params.addParam<unsigned int>("ID_Mq", 0, "ID of the current mass matrix.");
  params.addParam<unsigned int>("ID_Fq", 0, "ID of the current load vector.");
  params.addParam<unsigned int>("ID_Oq", 0, "ID of the current output vector.");
  params.addParam<bool>("matrix_seperation_according_to_subdomains", true, "Tells whether the stiffness matrix is separated according to the subdomain_ids");
  params.addParam<bool>("compute_output",false,"Determines whether an output function is used or not");
  params.addParam<bool>("compliant", false, "Specifies if you have a compliant or non-compliant case.");

  return params;
}

DwarfElephantRBIntegratedBC::DwarfElephantRBIntegratedBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _use_displaced(getParam<bool>("use_displaced")),
    _matrix_seperation_according_to_subdomains(getParam<bool>("matrix_seperation_according_to_subdomains")),
    _compute_output(getParam<bool>("compute_output")),
    _compliant(getParam<bool>("compliant")),
    _simulation_type(getParam<std::string>("simulation_type")),
    _ID_first_block(*_fe_problem.mesh().meshSubdomains().begin()),
    _ID_Aq(getParam<unsigned int>("ID_Aq")),
    _ID_Mq(getParam<unsigned int>("ID_Mq")),
    _ID_Fq(getParam<unsigned int>("ID_Fq")),
    _ID_Oq(getParam<unsigned int>("ID_Oq")),
    _es(_use_displaced ? _fe_problem.getDisplacedProblem()->es() : _fe_problem.es())
{
}

DwarfElephantRBIntegratedBC::~DwarfElephantRBIntegratedBC()
{
}

void
DwarfElephantRBIntegratedBC::initialSetup()
{
  if(_simulation_type == "steady")  // SteadyState
    _initialize_rb_system = &getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");
  else
    _initialize_rb_system_transient = &getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");

  if(_compute_output)
    mooseWarning("You are retrieving boundary values for your output of interest.");
}

void
DwarfElephantRBIntegratedBC::computeResidual()
{
  DenseVector<Number> & re = _assembly.residualBlock(_var.number());
  _local_re.resize(re.size());
  _local_re.zero();

  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
    for (_i = 0; _i < _test.size(); _i++)
      _local_re(_i) += _JxW[_qp]*_coord[_qp]*computeQpResidual();

  re += _local_re;

  if(_simulation_type == "steady")  // SteadyState
  {
    if(_initialize_rb_system->getOfflineStage())
      // Add the calculated vectors to the vectors from the RB system.
      if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
      {
        if (_ID_Fq >= _initialize_rb_system->getQf())
          mooseError("The number of load vectors you defined here is not matching the number of load vectors you specified in the RBClasses Class.");

        _initialize_rb_system->getResiduals()[_ID_Fq] -> add_vector(_local_re, _var.dofIndices());

        if (_compliant)
          _initialize_rb_system->getOutputs()[_ID_Fq][0] -> add_vector(_local_re, _var.dofIndices());
      }
  }

  else if (_simulation_type == "transient") // Transient
  {
    if(_initialize_rb_system_transient->getOfflineStage())
      // Add the calculated vectors to the vectors from the RB system.
    if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
    {
      if (_ID_Fq >= _initialize_rb_system_transient->getQf())
        mooseError("The number of load vectors you defined here is not matching the number of load vectors you specified in the RBClasses Class.");

      _initialize_rb_system_transient->getResiduals()[_ID_Fq] -> add_vector(_local_re, _var.dofIndices());

      // if (_compliant)
      //   _initialize_rb_system_transient->getOutputs()[_ID_Fq][0] -> add_vector(_local_re, _var.dofIndices());
      }
    }


  if (_has_save_in)
  {
    Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
    for (unsigned int i=0; i<_save_in.size(); i++)
      _save_in[i]->sys().solution().add_vector(_local_re, _save_in[i]->dofIndices());
  }

 if(_compute_output)
   computeOutput();
}

void
DwarfElephantRBIntegratedBC::computeOutput()
{
  DenseVector<Number> & out = _assembly.residualBlock(_var.number());
  _local_out.resize(out.size());
  _local_out.zero();

  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
    for (_i = 0; _i < _test.size(); _i++)
      _local_out(_i) += _JxW[_qp]*_coord[_qp]*computeQpOutput();

  out += _local_out;

  if(_simulation_type == "steady")  // SteadyState
  {
    if(_initialize_rb_system->getOfflineStage())
      // Add the calculated vectors to the vectors from the RB system.
      if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
      {
        _initialize_rb_system->getOutputs()[_ID_Oq][0] -> add_vector(_local_out, _var.dofIndices());
     }
  }

  else if (_simulation_type == "transient") // Transient
  {
    if(_initialize_rb_system_transient->getOfflineStage())
      // Add the calculated vectors to the vectors from the RB system.
      if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
         _initialize_rb_system_transient->getOutputs()[0][_ID_Oq] -> add_vector(_local_out, _var.dofIndices());
  }
}

void
DwarfElephantRBIntegratedBC::computeJacobian()
{
  if(_matrix_seperation_according_to_subdomains)
  {
    _ID_Aq = _current_elem->subdomain_id() - _ID_first_block;

//    unsigned int _ID_inter = _current_elem->subdomain_id();
//    if (_ID_inter >= _subdomain_split[0] && _ID_inter <= _subdomain_split[_subdomain_split.size()-1])
//      _ID_Aq_split = _ID_inter - _ID_first_block;
  }

  DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());
  _local_ke.resize(ke.m(), ke.n());
  _local_ke.zero();

  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
    for (_i = 0; _i < _test.size(); _i++)
      for (_j = 0; _j < _phi.size(); _j++)
        _local_ke(_i, _j) += _JxW[_qp]*_coord[_qp]*computeQpJacobian();

  ke += _local_ke;

  if(_simulation_type == "steady")  // Steady State
  {
    if (_ID_Aq >= _initialize_rb_system->getQa())
      mooseError("The number of stiffness matrices you defined here is not matching the number of stiffness matrices you specified in the RBClasses Class.");

    if(_initialize_rb_system->getOfflineStage())
    // Add the calculated matrices to the Aq matrices from the RB system.
    if (_fe_problem.getNonlinearSystemBase().getCurrentNonlinearIterationNumber() == 0)
        _initialize_rb_system->getJacobianSubdomain()[_ID_Aq] -> add_matrix(_local_ke, _var.dofIndices());
   }

  else if(_simulation_type == "transient") // Transient
  {
    if (_ID_Aq >= _initialize_rb_system_transient->getQa())
      mooseError("The number of stiffness matrices you defined here is not matching the number of stiffness matrices you specified in the RBClasses Class.");

    if (_ID_Mq >= _initialize_rb_system_transient->getQm())
      mooseError("The number of mass matrices you defined here is not matching the number of mass matrices you specified in the RBClasses Class.");

    if(_initialize_rb_system_transient->getOfflineStage())
    // Add the calculated matrices to the Aq matrices from the RB system.
    if (_fe_problem.getNonlinearSystemBase().getCurrentNonlinearIterationNumber() == 0)
    {
      _initialize_rb_system_transient->getJacobianSubdomain()[_ID_Aq] -> add_matrix(_local_ke, _var.dofIndices());
      _initialize_rb_system_transient->getMassMatrixSubdomain()[_ID_Mq] -> add_matrix(_local_ke, _var.dofIndices());
    }
  }

  if (_has_diag_save_in)
  {
    unsigned int rows = ke.m();
    DenseVector<Number> diag(rows);
    for (unsigned int i=0; i<rows; i++)
      diag(i) = _local_ke(i,i);

    Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
    for (unsigned int i=0; i<_diag_save_in.size(); i++)
      _diag_save_in[i]->sys().solution().add_vector(diag, _diag_save_in[i]->dofIndices());
  }
}

Real
DwarfElephantRBIntegratedBC::computeQpResidual()
{
  return 0;
}

Real
DwarfElephantRBIntegratedBC::computeQpOutput()
{
  return 0;
}
