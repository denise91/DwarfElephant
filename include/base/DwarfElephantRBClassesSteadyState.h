/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * DwarfElephantRBEvaluation: requires only the definition of the lower
 * coercivity constant. The value is here specified for a three layer
 * problem.
 *
 * DwarfElephantRBConstruction: In order to construct the RB System with the
 * DwarfElephantRBEvaluation subclass the method build_rb_evaluation needs to be
 * overriden.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBCLASSESSTEADYSTATE_H
#define DWARFELEPHANTRBCLASSESSTEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
//#if defined(LIBMESH_HAVE_SLEPC) && defined(LIBMESH_HAVE_GLPK)
#include <boost/version.hpp>
#include <fstream>
#include <limits>
#include <bitset>
// libMesh includes
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"
#include "libmesh/numeric_vector.h"

// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"
#include "libmesh/rb_construction.h"
#include "libmesh/rb_eim_construction.h"
#include "libmesh/rb_scm_construction.h"
#include "libmesh/rb_evaluation.h"
#include "libmesh/rb_eim_evaluation.h"
#include "libmesh/rb_scm_evaluation.h"
#include "libmesh/rb_eim_assembly.h"
#include "libmesh/auto_ptr.h" // libmesh_make_unique



// MOOSE includes
#include "FEProblemBase.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBStructuresT3F1O1SteadyState.h"
#include "DwarfElephantGeom3DRBThetaExpansion_RFA.h"
#include "DwarfElephantEIMStructures.h"
#include "libmesh/vtk_io.h"
#include "libmesh/exodusII_io.h"
#include "DwarfElephantNonAffineFunction_3DRBRFA.h"
#include <boost/lexical_cast.hpp>
#include<sstream>
#include <iomanip>
#include <limits>
///-------------------------------------------------------------------------
// Forward Declarations
namespace libMesh
{
  template <typename T> class SparseMatrix;
  template <typename T> class NumericVector;
  template <typename T> class PetscMatrix;

  class EquationSystems;
  //class RBConstruction;
  //class RBEIMConstruction;
  //class RBSCMConstruction;
  //class RBEvaluation;
  //class RBEIMEvaluation;
  //class RBSCMEvaluation;
  class RBEIMAssembly;
  class RBParameters;
}

//using libMesh::RBConstruction;
//using libMesh::RBEIMConstruction;
//using libMesh::RBSCMConstruction;
//using libMesh::RBEvaluation;
//using libMesh::RBEIMEvaluation;
//using libMesh::RBSCMEvaluation;
//               RBSCMEvaluation

//class DwarfElephantInitializeRBSystemSteadyState;


/*
struct CustomRBTheta : RBTheta
{
    virtual Number evaluate(const RBParameters &_mu)
    {
        return _mu.get_value("mu_2");
    }
};
 */
struct ShiftedGaussian : public RBParametrizedFunction
{
    virtual Number evaluate(const RBParameters & mu,
                          const Point & p,
                          const Elem & /*elem*/)
    {
        Real center_x = mu.get_value("mu_0");
        Real center_y = mu.get_value("mu_1");
        Real center_z = mu.get_value("mu_2");
        return exp(1e0*(-pow(p(0) - center_x,2)-pow(p(1) - center_y,2)-pow(p(2) - center_z,2)));
    }
};

struct CustomRBThetaExpansion : RBThetaExpansion
{
  CustomRBThetaExpansion()
  {
    // Setting up the RBThetaExpansion object
    
    attach_A_theta(&_rb_theta);
    //attach_F_theta(&_rb_theta);

    //attach_output_theta(&_rb_theta);

  }
  // Member Variables
  //CustomRBTheta _theta_a_1;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};


///------------------------DWARFELEPHANTRBEVALUATION------------------------
class DwarfElephantRBEvaluationSteadyState : public RBEvaluation
{

//---------------------------------PUBLIC-----------------------------------
public:
  DwarfElephantRBEvaluationSteadyState(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem, bool _RB_RFA_in=false);

  virtual ~DwarfElephantRBEvaluationSteadyState() {}
    virtual Real get_stability_lower_bound();
  
    virtual Real rb_solve(unsigned int N)
{
  LOG_SCOPE("rb_solve()", "RBEvaluation");

  if (N > get_n_basis_functions())
    libmesh_error_msg("ERROR: N cannot be larger than the number of basis functions in rb_solve");

  const RBParameters & mu = get_parameters();
  unsigned int M = 0;
  if (_RB_RFA)
      M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;
  // Resize (and clear) the solution vector
  RB_solution.resize(N);

  // Assemble the RB system
  DenseMatrix<Number> RB_system_matrix(N,N);
  RB_system_matrix.zero();

  DenseMatrix<Number> RB_Aq_a;
  for (unsigned int q_a=0; q_a<get_rb_theta_expansion().get_n_A_terms(); q_a++)
    {
      RB_Aq_vector[q_a].get_principal_submatrix(N, RB_Aq_a);

      RB_system_matrix.add(get_rb_theta_expansion().eval_A_theta(q_a, mu), RB_Aq_a);
    }

  // Assemble the RB rhs
  DenseVector<Number> RB_rhs(N);
  RB_rhs.zero();

  DenseVector<Number> RB_Fq_f;
  for (unsigned int q_f=0; q_f<get_rb_theta_expansion().get_n_F_terms(); q_f++)
    {
      RB_Fq_vector[q_f].get_principal_subvector(N, RB_Fq_f);

      if (_RB_RFA)
          RB_rhs.add(get_rb_theta_expansion().eval_F_theta((q_f%M), mu)*dynamic_cast<Geom3DRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f/M)]->evaluate(mu), RB_Fq_f);
      else
          RB_rhs.add(get_rb_theta_expansion().eval_F_theta(q_f,mu),RB_Fq_f);
    }

  // Solve the linear system
  if (N > 0)
    {
      RB_system_matrix.lu_solve(RB_rhs, RB_solution);
    }

  // Evaluate RB outputs
  DenseVector<Number> RB_output_vector_N;
  for (unsigned int n=0; n<get_rb_theta_expansion().get_n_outputs(); n++)
    {
      RB_outputs[n] = 0.;
      for (unsigned int q_l=0; q_l<get_rb_theta_expansion().get_n_output_terms(n); q_l++)
        {
          RB_output_vectors[n][q_l].get_principal_subvector(N, RB_output_vector_N);
          RB_outputs[n] += get_rb_theta_expansion().eval_output_theta(n,q_l,mu)*RB_output_vector_N.dot(RB_solution);
        }
    }

  if (evaluate_RB_error_bound) // Calculate the error bounds
    {
      // Evaluate the dual norm of the residual for RB_solution_vector
      Real epsilon_N = compute_residual_dual_norm(N);

      // Get lower bound for coercivity constant
      const Real alpha_LB = get_stability_lower_bound();
      // alpha_LB needs to be positive to get a valid error bound
      libmesh_assert_greater ( alpha_LB, 0. );

      // Evaluate the (absolute) error bound
      Real abs_error_bound = epsilon_N / residual_scaling_denom(alpha_LB);

      // Now compute the output error bounds
      for (unsigned int n=0; n<get_rb_theta_expansion().get_n_outputs(); n++)
        {
          RB_output_error_bounds[n] = abs_error_bound * eval_output_dual_norm(n, mu);
        }

      return abs_error_bound;
    }
  else // Don't calculate the error bounds
    {
      // Just return -1. if we did not compute the error bound
      return -1.;
    }
}
    
    virtual Real compute_residual_dual_norm(const unsigned int N)
{
  LOG_SCOPE("compute_residual_dual_norm()", "RBEvaluation");

  const RBParameters & mu = get_parameters();

  // Use the stored representor inner product values
  // to evaluate the residual norm
  Number residual_norm_sq = 0.;
  
  unsigned int M = 0;
  if (_RB_RFA)
      M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;

  unsigned int q=0;
  for (unsigned int q_f1=0; q_f1<get_rb_theta_expansion().get_n_F_terms(); q_f1++)
    {
      for (unsigned int q_f2=q_f1; q_f2<get_rb_theta_expansion().get_n_F_terms(); q_f2++)
        {
          Real delta = (q_f1==q_f2) ? 1. : 2.;
          if (_RB_RFA)
              residual_norm_sq += delta * libmesh_real(
                                                   get_rb_theta_expansion().eval_F_theta((q_f1%M), mu)*dynamic_cast<Geom3DRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f1/M)]->evaluate(mu)
                                                   * libmesh_conj(get_rb_theta_expansion().eval_F_theta((q_f2%M), mu)) * libmesh_conj(dynamic_cast<Geom3DRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f2/M)]->evaluate(mu)) * Fq_representor_innerprods[q] );
          else
              residual_norm_sq += delta * libmesh_real(
                                                   get_rb_theta_expansion().eval_F_theta(q_f1, mu)
                                                   * libmesh_conj(get_rb_theta_expansion().eval_F_theta(q_f2, mu)) * Fq_representor_innerprods[q] );

          q++;
        }
    }

  for (unsigned int q_f=0; q_f<get_rb_theta_expansion().get_n_F_terms(); q_f++)
    {
      for (unsigned int q_a=0; q_a<get_rb_theta_expansion().get_n_A_terms(); q_a++)
        {
          for (unsigned int i=0; i<N; i++)
            {
              Real delta = 2.;
              if (_RB_RFA)
                  residual_norm_sq +=
                delta * libmesh_real( get_rb_theta_expansion().eval_F_theta(q_f%M, mu) * dynamic_cast<Geom3DRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f/M)]->evaluate(mu) *
                                      libmesh_conj(get_rb_theta_expansion().eval_A_theta(q_a, mu)) *
                                      libmesh_conj(RB_solution(i)) * Fq_Aq_representor_innerprods[q_f][q_a][i] );
              else
                  residual_norm_sq +=
                delta * libmesh_real( get_rb_theta_expansion().eval_F_theta(q_f, mu) *
                                      libmesh_conj(get_rb_theta_expansion().eval_A_theta(q_a, mu)) *
                                      libmesh_conj(RB_solution(i)) * Fq_Aq_representor_innerprods[q_f][q_a][i] );
            }
        }
    }

  q=0;
  for (unsigned int q_a1=0; q_a1<get_rb_theta_expansion().get_n_A_terms(); q_a1++)
    {
      for (unsigned int q_a2=q_a1; q_a2<get_rb_theta_expansion().get_n_A_terms(); q_a2++)
        {
          Real delta = (q_a1==q_a2) ? 1. : 2.;

          for (unsigned int i=0; i<N; i++)
            {
              for (unsigned int j=0; j<N; j++)
                {
                  residual_norm_sq +=
                    delta * libmesh_real( libmesh_conj(get_rb_theta_expansion().eval_A_theta(q_a1, mu)) *
                                          get_rb_theta_expansion().eval_A_theta(q_a2, mu) *
                                          libmesh_conj(RB_solution(i)) * RB_solution(j) * Aq_Aq_representor_innerprods[q][i][j] );
                }
            }

          q++;
        }
    }

  if (libmesh_real(residual_norm_sq) < 0.)
    {
      //    libMesh::out << "Warning: Square of residual norm is negative "
      //                 << "in RBSystem::compute_residual_dual_norm()" << std::endl;

      //     Sometimes this is negative due to rounding error,
      //     but when this occurs the error is on the order of 1.e-10,
      //     so shouldn't affect error bound much...
      residual_norm_sq = std::abs(residual_norm_sq);
    }

  return std::sqrt( libmesh_real(residual_norm_sq) );
}

  FEProblemBase & get_fe_problem(){return fe_problem;}

  FEProblemBase & fe_problem;
  //DwarfElephantEIMTestRBThetaExpansion _eim_test_rb_theta_expansion;
  //Geom2DRBThetaExpansion _goem_2D_rb_theta_expansion;
  Geom3DRBThetaExpansion _geom_3D_rb_theta_expansion;
  //CustomRBThetaExpansion RBExpansion;
  //libMesh::RBSCMEvaluation * rb_scm_eval;
  bool _RB_RFA;
};

///-----------------------DWARFELEPHANTRBCONSTRUCTION-----------------------
class DwarfElephantRBConstructionSteadyState : public RBConstruction
{

//---------------------------------PUBLIC-----------------------------------
public:

  // Constructor
  DwarfElephantRBConstructionSteadyState (EquationSystems & es,
                        const std::string & name_in,
                        const unsigned int number_in);

  // Destructor
  virtual ~DwarfElephantRBConstructionSteadyState () { }

  // Type of the system
  typedef DwarfElephantRBConstructionSteadyState _sys_type;

  // Type of the parent
  typedef RBConstruction Parent;

  // Initialize data structure
  virtual void init_data() override;
 
  virtual Real train_reduced_basis(const bool resize_rb_eval_data=true) override;
  
  //virtual void compute_Fq_representor_innerprods(bool compute_inner_products=true) override;
  
NumericVector<Number> * get_nonAffineF() // To test against EIM example from Martin's publication
  {
    return _nonAffineF.get();
  }
//  Real train_reduced_basis(const bool resize_rb_eval_data = true);

  void allocate_RB_error_structures() // To test against EIM example from Martin's publication
  {
    _nonAffineF = NumericVector<Number>::build(this->comm());
    _nonAffineF->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
    _nonAffineF->zero();
  }

void compute_error_X_norm_vs_N(NumericVector<Number>* _EIMFEsolution, RBParameters _rb_online_mu, EquationSystems & _es)// Compute X inner product of the difference between full FE solution and EIM_FE solution
  {
    Number truthError_X_norm;
    std::unique_ptr<NumericVector<Number>> _RB_solution;
   _RB_solution = NumericVector<Number>::build(this->comm());
    _RB_solution->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
    _RB_solution->zero();

    get_rb_evaluation().set_parameters(_rb_online_mu);
    for (int N = 1; N <= get_rb_evaluation().get_n_basis_functions(); N++)
    {
      Real online_error_bound;
      online_error_bound = get_rb_evaluation().rb_solve(N);
      
      this-> load_rb_solution();

      *_es.get_system("rb0").solution = *_es.get_system("RBSystem").solution;
      //_fe_problem.getNonlinearSystemBase().update();
      std::stringstream ss;
      std::string temp_string;
      ss << std::setw(2) << std::setfill('0') << N;
      temp_string = "out_" + ss.str();
      //VTKIO(get_mesh()).write_equation_systems(temp_string+".pvtu", _es);
      // compute X norm of RB vs EIMFE error.
      for (int i = 0; i < N; i++)
      {
         _RB_solution->add(get_rb_evaluation().RB_solution(i),get_rb_evaluation().get_basis_function(i));     
      }
      *_RB_solution-=*_EIMFEsolution;
      get_non_dirichlet_inner_product_matrix_if_avail()->vector_mult(*inner_product_storage_vector,*(_RB_solution.get()));
    truthError_X_norm = std::sqrt(inner_product_storage_vector->dot(*(_RB_solution.get())));
      libMesh::out << "N = " << N << " Error = " << truthError_X_norm  << " Error bound = " << online_error_bound << "\n";
      if (truthError_X_norm > online_error_bound) {libMesh::out << "                  ^^^^^^^^^              Error is larger than error bound!" << "\n";}
      _RB_solution->zero();
    }
    
    
  }

  void do_RB_vs_FE_Error_analysis(RBParameters mu, EquationSystems & _es)
  {
    // compute full FE solution
      unsigned int  M = 0;
      if (dynamic_cast<DwarfElephantRBEvaluationSteadyState&>(get_rb_evaluation())._RB_RFA)
          M = dynamic_cast<Geom3DRBThetaExpansion&>(get_rb_theta_expansion()).get_n_F_terms()/dynamic_cast<Geom3DRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;
      std::unique_ptr<NumericVector<Number>> FullFEsolution;
      FullFEsolution = NumericVector<Number>::build(this->comm());
      FullFEsolution->init(this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

      FullFEsolution -> zero();
      FullFEsolution -> close();


      this -> matrix -> zero();
      this -> rhs -> zero();
      
      this -> matrix -> close();
      this -> rhs -> close();

      
      for (int i = 0; i < get_rb_theta_expansion().get_n_A_terms(); i++)
        matrix -> add(get_rb_theta_expansion().eval_A_theta(i,mu),*get_Aq(i));

      for (int i = 0; i < get_rb_theta_expansion().get_n_F_terms(); i++)
      {
        if (dynamic_cast<DwarfElephantRBEvaluationSteadyState&>(get_rb_evaluation())._RB_RFA)
            rhs -> add(get_rb_theta_expansion().eval_F_theta((i%M),mu) * dynamic_cast<Geom3DRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[i/M]->evaluate(mu),*get_Fq(i));//*_nonAffineF);
        else
            rhs -> add(get_rb_theta_expansion().eval_F_theta(i,mu),*get_Fq(i));
      }
      
      this -> matrix -> close();
      this -> rhs -> close();
      if (extra_linear_solver)
    {
      // If extra_linear_solver has been initialized, then we use it for the
      // truth solves.
      solve_for_matrix_and_rhs(*extra_linear_solver, *matrix, *rhs);

      if (assert_convergence)
        check_convergence(*extra_linear_solver);
    }
  else
    {
      solve_for_matrix_and_rhs(*get_linear_solver(), *matrix, *rhs);

      if (assert_convergence)
        check_convergence(*get_linear_solver());
    }
    FullFEsolution -> add(*solution);
    ExodusII_IO(get_mesh()).write_equation_systems ("FullFEtruth.e",
this->get_equation_systems());
    compute_error_X_norm_vs_N(FullFEsolution.get(), mu, _es);
  }

  virtual void truth_assembly() override
{
  LOG_SCOPE("truth_assembly()", "RBConstruction");
  unsigned int  M = 0;
  if (dynamic_cast<DwarfElephantRBEvaluationSteadyState&>(get_rb_evaluation())._RB_RFA)
   M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;
  const RBParameters & mu = get_parameters();

  this->matrix->zero();
  this->rhs->zero();

  this->matrix->close();
  this->rhs->close();

  {
    // We should have already assembled the matrices
    // and vectors in the affine expansion, so
    // just use them

    for (unsigned int q_a=0; q_a<get_rb_theta_expansion().get_n_A_terms(); q_a++)
      {
        matrix->add(get_rb_theta_expansion().eval_A_theta(q_a, mu), *get_Aq(q_a));
      }

    std::unique_ptr<NumericVector<Number>> temp_vec = NumericVector<Number>::build(this->comm());
    temp_vec->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
    for (unsigned int q_f=0; q_f<get_rb_theta_expansion().get_n_F_terms(); q_f++)
      {
        *temp_vec = *get_Fq(q_f);
        if (dynamic_cast<DwarfElephantRBEvaluationSteadyState&>(get_rb_evaluation())._RB_RFA)
            temp_vec->scale( get_rb_theta_expansion().eval_F_theta((q_f%M), mu) * dynamic_cast<Geom3DRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[q_f/M]->evaluate(mu) );
        else
            temp_vec->scale(get_rb_theta_expansion().eval_F_theta(q_f,mu));
        rhs->add(*temp_vec);
      }
  }

  this->matrix->close();
  this->rhs->close();
}
  
  std::unique_ptr<NumericVector<Number>> _nonAffineF; 

  unsigned int u_var;
  std::ofstream GreedyOutputFile;
};


class DwarfElephantEIMEvaluationSteadyState : public RBEIMEvaluation
{
public:

  DwarfElephantEIMEvaluationSteadyState(const libMesh::Parallel::Communicator & comm);

  
  virtual ~DwarfElephantEIMEvaluationSteadyState() {}

  ShiftedGaussian_3DRFA sg;
  //ShiftedGaussian sg;
  //AffineFunction sg;
};



// A simple subclass of RBEIMConstruction.
class DwarfElephantEIMConstructionSteadyState : public RBEIMConstruction
{
public:

  /**
   * Constructor.
   */
  DwarfElephantEIMConstructionSteadyState (EquationSystems & es,
                         const std::string & name_in,
                         const unsigned int number_in);

  
  virtual ~DwarfElephantEIMConstructionSteadyState() {}
  /**
   * The type of the parent.
   */
  typedef RBEIMConstruction Parent;

  virtual std::unique_ptr<ElemAssembly> build_eim_assembly(unsigned int index);
  
  virtual void init_data();
  
  Real get_error_bound_normalization()
  {
      return _error_bound_normalization;
  }
  
  /**
   * Initialize the implicit system that is used to perform L2 projections.
   */
  virtual void init_implicit_system();

  /**
   * Initialize the explicit system that is used to store the basis functions.
   */
  virtual void init_explicit_system();

  virtual Real train_reduced_basis(const bool resize_rb_eval_data=true)
{
  // precompute all the parametrized functions that we'll use in the greedy
  initialize_parametrized_functions_in_training_set();

  LOG_SCOPE("train_reduced_basis()", "RBConstruction");

  int count = 0;

  // initialize rb_eval's parameters
  get_rb_evaluation().initialize_parameters(*this);

  // possibly resize data structures according to Nmax
  if (resize_rb_eval_data)
    {
      get_rb_evaluation().resize_data_structures(get_Nmax());
    }

  // Clear the Greedy param list
  for (std::size_t i=0; i<get_rb_evaluation().greedy_param_list.size(); i++)
    get_rb_evaluation().greedy_param_list[i].clear();

  get_rb_evaluation().greedy_param_list.clear();

  Real training_greedy_error;


  // If we are continuing from a previous training run,
  // we might already be at the max number of basis functions.
  // If so, we can just return.
  if (get_rb_evaluation().get_n_basis_functions() >= get_Nmax())
    {
      libMesh::out << "Maximum number of basis functions reached: Nmax = "
                   << get_Nmax() << std::endl;
      return 0.;
    }


  // Compute the dual norms of the outputs if we haven't already done so
  compute_output_dual_innerprods();

  // Compute the Fq Riesz representor dual norms if we haven't already done so
  compute_Fq_representor_innerprods();

  libMesh::out << std::endl << "---- Performing Greedy basis enrichment ----" << std::endl;
  Real initial_greedy_error = 0.;
  bool initial_greedy_error_initialized = false;
  while (true)
    {
      libMesh::out << std::endl << "---- Basis dimension: "
                   << get_rb_evaluation().get_n_basis_functions() << " ----" << std::endl;

      if (count > 0 || (count==0 && use_empty_rb_solve_in_greedy))
        {
          libMesh::out << "Performing RB solves on training set" << std::endl;
          training_greedy_error = compute_max_error_bound();
          
          
          libMesh::out << "Maximum error bound is " << training_greedy_error << std::endl << std::endl;

          // record the initial error
          if (!initial_greedy_error_initialized)
            {
              initial_greedy_error = training_greedy_error;
              initial_greedy_error_initialized = true;
            }

          // Break out of training phase if we have reached Nmax
          // or if the training_tolerance is satisfied.
          if (greedy_termination_test(training_greedy_error, initial_greedy_error, count))
            break;
        }
      if (count == 1)
          _error_bound_normalization = training_greedy_error;

      libMesh::out << "Performing truth solve at parameter:" << std::endl;
      print_parameters();
      //GreedyOutputFile << get_parameters().get_value("mu_0") << ", " << get_parameters().get_value("mu_1") << ", " << training_greedy_error << std::endl; 
      
      // Update the list of Greedily selected parameters
      this->update_greedy_param_list();

      // Perform an Offline truth solve for the current parameter
      truth_solve(1);
      
      // Add orthogonal part of the snapshot to the RB space
      libMesh::out << "Enriching the RB space" << std::endl;
      enrich_RB_space();
      
      update_system();

      // Increment counter
      count++;
    }
  this->update_greedy_param_list();

  return training_greedy_error;

}
  
  RBParameters get_training_params(unsigned int index)
  {
      return this->get_params_from_training_set(index);
  }
  /**
   * Variable number for u.
   */
  unsigned int u_var;

  std::vector<std::unique_ptr<DwarfElephantEIMFAssembly>> _rb_eim_assembly_objects_new;
  std::ofstream GreedyOutputFile;
  
  Real _error_bound_normalization;
};

struct EIM_input_data{
        std::vector<Real> _cont_param_min;
        std::vector<Real> _cont_param_max;
        Real _rel_tol;
        Real _abs_tol;
        std::vector<std::string> _cont_param;
        std::string _best_fit_type;
        bool _deterministic_training;
        bool _quiet_mode;
        bool _normalize_bound;
        bool _log_scaling;

        unsigned int _n_training_samples;
        unsigned int _training_random_seed;
        unsigned int _N_max;
        
        Real EIM_error, RB_error_bound;
    };
    
    struct RB_input_data
    {
        bool _compliant;
        bool _deterministic_training_RB;
        bool _quiet_mode_RB;
        bool _normalize_RB_bound_in_greedy;
        
        unsigned int _n_training_samples;
        unsigned int _training_random_seed;
        unsigned int _N_max;
        
        std::vector<std::string> _cont_param;
        std::vector<std::string> _discrete_parameters_RB;
        std::vector<Real> _discrete_parameter_values_in_RB;
        mutable std::map<std::string,std::vector<Real>> _discrete_parameter_values_RB;
        
        Real _rel_tol;
        Real _abs_tol;
        std::vector<Real> _cont_param_min;
        std::vector<Real> _cont_param_max;
    };
    
class DwarfElephanthpEIMNode
{
    //Class defining a node of the M-ary tree required for hp EIM
    //The node object stores:
    // the number of parameters, 
    // their min and max values,
    // the largest possible number of children for each node, 
    // pointers to the children,
    // pointers to eim_construction and eim_evaluation objects of libmesh,
    // the error of the eim approximation in the node,
    // the gravity center of the parameter domain in the node
    //Methods:
    // constructor
    // set_gravity_center
    // set_child_subdomain_min
    // set_child_subdomain_max
    // split_param_domain
    // check_existence_of_all_children
    // check_non_existence_of_all_children
    // print_node
    // get_error
    // destructor
  public:
      
      
    DwarfElephanthpEIMNode(EquationSystems & _es, MooseMesh * _mesh_ptr, std::string system_name, std::string system_name_suffix, EIM_input_data _eim_data_in, std::string operation_mode) :
      //Constructor:
      //Input parameters:
      //pd_min: array containing min values of all parameters
      //pd_max: array containing max values of all parameters
      //_eq: Moose equation system object
      //_mesh_ptr: moose mesh pointer
      //number_of_params: number of parameters in the system
      //system_name: (string) base name of the EIM system
      //system_name_suffix: (string) suffix to the EIM system name (each EIM system name must be unique)
    number_of_params(-1),
    number_of_subdomains(-1),
    system_name(system_name),
    system_name_suffix(system_name_suffix),
    operation_mode(operation_mode),
            online_objects_initialized(false)
    {
        if (operation_mode == "offline")
        {
            _eim_con_ptr =  &_es.add_system<DwarfElephantEIMConstructionSteadyState>("hp_EIM_System" + system_name + system_name_suffix);
            _rb_con_ptr = &_es.add_system<DwarfElephantRBConstructionSteadyState>("RB_System" + system_name + system_name_suffix);
            _eim_con_ptr->init();
            _eim_con_ptr->get_explicit_system().init();
            _rb_con_ptr->init();
            _es.update();
            _eim_eval_ptr = new DwarfElephantEIMEvaluationSteadyState(_mesh_ptr->comm());
  
            // Pass a pointer of the RBEvaluation object to the
            // RBConstruction object
            _eim_con_ptr->set_rb_evaluation(*_eim_eval_ptr);

        
            _eim_data_this = _eim_data_in;
            _eim_data_child = _eim_data_in;
            initialize_EIM_parameters(_eim_data_in, operation_mode);
            _eim_con_ptr->initialize_rb_construction(true,true);
 
            set_gravity_center();
      
            //children.reserve(number_of_subdomains);
            for (unsigned int i = 0; i < number_of_subdomains; i++)
              children.push_back(NULL);
        }
        else if (operation_mode == "online")
        {
            initialize_EIM_parameters(_eim_data_in, operation_mode);
            EIM_error = _eim_data_in.EIM_error;
            RB_Error_bound = _eim_data_in.RB_error_bound;
            
            children.reserve(number_of_subdomains);
            for (unsigned int i = 0; i < number_of_subdomains; i++)
              children[i] = (NULL);
        }
        else mooseError("Invalid mode string provided to hpEIMNode constructor.");
    }

    void initialize_EIM_parameters(EIM_input_data _eim_data_in, std::string operation_mode)
    //initialize_EIM_parameters: initializes the parameters in the rb_eim_con and rb_eim_eval objects using data from the input file (through _eim_data_in)
    {
        if (operation_mode == "offline")
        {
            
            // Setting parameter values for the EIM construction object
            // Set the random seed for the RNG. By default -1 is set, meaning that std::time is used as a seed for the RNG.
            _eim_con_ptr->set_training_random_seed(_eim_data_in._training_random_seed);

            // Set quiet mode.
            _eim_con_ptr->set_quiet_mode(_eim_data_in._quiet_mode);

            // Initialization of the RB parameters.
            _eim_con_ptr->set_Nmax(_eim_data_in._N_max);

            _eim_con_ptr->set_rel_training_tolerance(_eim_data_in._rel_tol);
            //_eim_con_ptr->set_abs_training_tolerance(_abs_training_tolerance);

            _eim_con_ptr->set_normalize_rb_bound_in_greedy(_eim_data_in._normalize_bound);

            RBParameters _mu_min_EIM;
            RBParameters _mu_max_EIM;

            for (unsigned int i=0; i<_eim_data_in._cont_param.size(); i++)
            {
                _mu_min_EIM.set_value(_eim_data_in._cont_param[i], _eim_data_in._cont_param_min[i]);
                _mu_max_EIM.set_value(_eim_data_in._cont_param[i], _eim_data_in._cont_param_max[i]);
            }
      
            std::map<std::string,std::vector<Real>> _discrete_parameter_values_EIM;
            std::vector<std::string> _discrete_parameters_EIM;
            std::vector<Real> _discrete_parameter_values_in_EIM;
            for (unsigned int i=0; i<_discrete_parameters_EIM.size(); i++)
            {
                _discrete_parameter_values_EIM[_discrete_parameters_EIM[i]] = _discrete_parameter_values_in_EIM;
            }

            std::map<std::string,bool> _log_scaling;
            RBParameters::const_iterator it     = _mu_min_EIM.begin();
            RBParameters::const_iterator it_end = _mu_min_EIM.end();
            for ( ; it != it_end; ++it)
            {
                std::string _param_name = it->first;

                // For now, just set all entries to false.
                // TODO: Implement a decent way to specify log-scaling true/false
                // in the input text file
                _log_scaling[_param_name] = false;
            }

            _eim_con_ptr->initialize_parameters(_mu_min_EIM, _mu_max_EIM, _discrete_parameter_values_EIM);

            _eim_con_ptr->initialize_training_parameters(this->_eim_con_ptr->get_parameters_min(),
                                               this->_eim_con_ptr->get_parameters_max(),
                                               _eim_data_in._n_training_samples,
                                               _log_scaling,
                                               _eim_data_in._deterministic_training);
            _eim_con_ptr->set_best_fit_type_flag(_eim_data_in._best_fit_type);
            // End setting parameter values for the EIM construction object
      
            // Initialize useful parameters within the node object
            number_of_params = _eim_data_in._cont_param.size();
            number_of_subdomains = std::pow(2,number_of_params);
            for (unsigned int i = 0 ; i < _eim_data_in._cont_param.size(); i++)
            {
                param_domain_max.push_back(_eim_data_in._cont_param_max[i]);
                param_domain_min.push_back(_eim_data_in._cont_param_min[i]);
                gravity_center.push_back(std::sqrt(-1));
            }
        }
        else if (operation_mode == "online")
        {
                        // Initialize useful parameters within the node object
            number_of_params = _eim_data_in._cont_param.size();
            number_of_subdomains = std::pow(2,number_of_params);
            for (unsigned int i = 0 ; i < _eim_data_in._cont_param.size(); i++)
            {
                param_domain_max.push_back(_eim_data_in._cont_param_max[i]);
                param_domain_min.push_back(_eim_data_in._cont_param_min[i]);
                gravity_center.push_back(std::sqrt(-1));
            }
        }
        else mooseError("Invalid string provided for operation_mode");
    }
    
    void initialize_rb_parameters(RB_input_data _rb_data_in, std::string operation_mode)
    {
        if (operation_mode == "offline")
        {
            _rb_con_ptr->set_training_random_seed(_rb_data_in._training_random_seed);
            _rb_con_ptr->set_quiet_mode(_rb_data_in._quiet_mode_RB);
            _rb_con_ptr->set_Nmax(_rb_data_in._N_max);
            _rb_con_ptr->set_rel_training_tolerance(_rb_data_in._rel_tol);
            _rb_con_ptr->set_abs_training_tolerance(_rb_data_in._abs_tol);
            _rb_con_ptr->set_normalize_rb_bound_in_greedy(_rb_data_in._normalize_RB_bound_in_greedy);
            
            RBParameters _mu_min_RB;
            RBParameters _mu_max_RB;
            
            for (unsigned int i = 0; i < _eim_data_this._cont_param.size(); i++)
            {
                _mu_min_RB.set_value(_eim_data_this._cont_param[i], _eim_data_this._cont_param_min[i]);
                _mu_max_RB.set_value(_eim_data_this._cont_param[i], _eim_data_this._cont_param_max[i]);
            }
            
            for (unsigned int i = _eim_data_this._cont_param.size(); i < _rb_data_in._cont_param.size(); i++)
            {
                _mu_min_RB.set_value(_rb_data_in._cont_param[i], _rb_data_in._cont_param_min[i]);
                _mu_max_RB.set_value(_rb_data_in._cont_param[i], _rb_data_in._cont_param_max[i]);
            }
            
            for (unsigned int i = 0; i < _rb_data_in._discrete_parameters_RB.size(); i++)
            {
                //_rb_data_in._discrete_parameter_values_RB[_rb_data_in._discrete_parameters_RB[i]] = _rb_data_in._discrete_parameter_values_in_RB;
                _rb_data_in._discrete_parameter_values_RB.insert(std::pair<std::string,std::vector<Real>>(_rb_data_in._discrete_parameters_RB[i],_rb_data_in._discrete_parameter_values_in_RB));
            }
            
            std::map<std::string,bool> _log_scaling;
            RBParameters::const_iterator it = _mu_min_RB.begin();
            RBParameters::const_iterator it_end = _mu_min_RB.end();
            for (; it != it_end; ++it)
            {
                std::string _param_name = it->first;
                _log_scaling[_param_name] = false;
            }
            
            _rb_con_ptr->initialize_parameters(_mu_min_RB, _mu_max_RB, _rb_data_in._discrete_parameter_values_RB);
            
            _rb_con_ptr->initialize_training_parameters(_rb_con_ptr->get_parameters_min(),
                                                        _rb_con_ptr->get_parameters_max(),
                                                        _rb_data_in._n_training_samples,
                                                        _log_scaling,
                                                        _rb_data_in._deterministic_training_RB);
        }
        else if (operation_mode == "online")
        {
            
        }
        else mooseError("Invalid string provided for operation_mode argument");
    }
    
    void attach_inner_product_matrix(SparseMatrix<Number> * InnerProductMatrix)
    {
        InnerProductMatrix->get_transpose(static_cast<SparseMatrix<Number>&>( *(_eim_con_ptr->get_inner_product_matrix())) ); // works because the inner product matrix is symmetric
    }
    
    void set_gravity_center()
    //set_gravity_center: sets the gravity center of the parameter domain in the appropriate variable
    { 
      unsigned int  j = 0, num_training_samples = _eim_con_ptr->get_n_training_samples(); //variable for parameter number
      RBParameters temp_param;
      std::set<std::string> param_names;
      param_names = _eim_con_ptr->get_parameter_names();
      for (std::set<std::string>::iterator param_name = param_names.begin() ; param_name != param_names.end() ; param_name++)
      {
          if (std::isnan(param_domain_min[j]) || !(std::isnan(gravity_center[j])) || (gravity_center.size() == 0))
              mooseError("Root object has not been initialized or gravity center has already been found.");
          gravity_center[j] = 0;
          j++;
      }
      
      for (unsigned int i = 0 ; i < num_training_samples ; i++)
      {
          temp_param = _eim_con_ptr->get_training_params(i); 
          j = 0;
          for (std::set<std::string>::iterator param_name = param_names.begin() ; param_name != param_names.end() ; param_name++)
          {
              gravity_center[j] += temp_param.get_value(*param_name);
              j++;
          }
      }
      j = 0;
      for (std::set<std::string>::iterator param_name = param_names.begin() ; param_name != param_names.end() ; param_name++)
      {
          gravity_center[j] = gravity_center[j]/num_training_samples;
          j++;
      }
    }

    void split_param_domain(EquationSystems & _es, MooseMesh * _mesh_ptr)
    // split_param_domain: splits the parameter domain contained in the node. Each entry of the children array points to a child node containing one of the created subdomains
    // Input parameters:
    // _es: Moose equation system object
    // _mesh_ptr: Moose mesh pointer object
    {
        std::vector<Real> new_subdomain_min, new_subdomain_max;

        if (check_non_existence_of_all_children()) // if all children are NULL
        {
            for (unsigned int subdomain_number = 0; subdomain_number < number_of_subdomains; subdomain_number++)
            {
                for (unsigned int param_number = 0; param_number < number_of_params; param_number++)
                {
                    _eim_data_child._cont_param_min[param_number] = get_child_subdomain_min(param_number+1,subdomain_number+1);
                    _eim_data_child._cont_param_max[param_number] = get_child_subdomain_max(param_number+1,subdomain_number+1);
                }
                // update _eim_data_child with the min and max param values
                children[subdomain_number] = new DwarfElephanthpEIMNode(_es, _mesh_ptr, system_name + system_name_suffix, "_" + std::to_string(subdomain_number + 1), _eim_data_child, operation_mode);
                children[subdomain_number]->attach_inner_product_matrix(_eim_con_ptr->get_inner_product_matrix());
                children[subdomain_number]->_eim_con_ptr->get_inner_product_matrix()->close();
                children[subdomain_number]->_eim_con_ptr->train_reduced_basis();
                children[subdomain_number]->EIM_error = children[subdomain_number]->_eim_con_ptr->compute_max_error_bound()/children[subdomain_number]->_eim_con_ptr->get_error_bound_normalization(); 
            }
        }
    }

    void train_rb_model(EquationSystems & _es, MooseMesh * _mesh_ptr, FEProblemBase & _fe_problem, RB_input_data _rb_init_data, DwarfElephantRBConstructionSteadyState * _master_rb_con_ptr, unsigned int _eim_f_vec_offset)
    // Train the rb model associated with the hp EIM Node
    {        
        //_rb_con_ptr = &_es.add_system<DwarfElephantRBConstructionSteadyState>("RBSystem"+system_name+system_name_suffix);
        //_rb_con_ptr->init();
        _rb_eval_ptr = new DwarfElephantRBEvaluationSteadyState(_mesh_ptr->comm(), _fe_problem);
        _rb_con_ptr->set_rb_evaluation(*_rb_eval_ptr);
        _rb_data_in = _rb_init_data;
        initialize_rb_parameters(_rb_data_in,"offline"); // TODO: make arrangements to handle the case where there are non-EIM parameters involved
        _eim_eval_ptr->initialize_eim_theta_objects();
        _rb_eval_ptr->get_rb_theta_expansion().attach_multiple_F_theta(_eim_eval_ptr->get_eim_theta_objects());
        _eim_con_ptr->initialize_eim_assembly_objects();
        _rb_con_ptr->print_info();
        _rb_con_ptr->initialize_rb_construction(true,true);
        
        std::unique_ptr<SparseMatrix<Number>> temp_sparse_matrix = SparseMatrix<Number>::build(_rb_con_ptr->comm());
        DofMap & dof_map = _rb_con_ptr->get_dof_map();
        dof_map.attach_matrix(*temp_sparse_matrix);
        temp_sparse_matrix->init();
        temp_sparse_matrix->zero();
        
        // Copy Affine matrices (all Aq matrices), required Fq vectors, and rb inner product matrix from _master_rb_con_ptr object
        _master_rb_con_ptr->get_inner_product_matrix()->get_transpose(static_cast<SparseMatrix<Number>&>(*(_rb_con_ptr->get_inner_product_matrix())));
        
        for (unsigned int _q = 0; _q < _rb_con_ptr->get_rb_theta_expansion().get_n_A_terms(); _q++)
        {
            _master_rb_con_ptr->get_Aq(_q)->get_transpose(static_cast<SparseMatrix<Number>&>(*temp_sparse_matrix));
            temp_sparse_matrix->get_transpose(static_cast<SparseMatrix<Number>&>(*(_rb_con_ptr->get_Aq(_q))));
        }
        
        for (unsigned int _q = 0; _q < _rb_con_ptr->get_rb_theta_expansion().get_n_F_terms(); _q++)
        {
            _master_rb_con_ptr->get_Fq(_q + _eim_f_vec_offset)->swap(static_cast<NumericVector<Real>&>(*_rb_con_ptr->get_Fq(_q)));
        }
        _rb_con_ptr->train_reduced_basis();
        RB_Error_bound = _rb_con_ptr->compute_max_error_bound();
        
        #if defined(LIBMESH_HAVE_CAPNPROTO)
            RBDataSerialization::RBEIMEvaluationSerialization rb_eim_eval_writer(_eim__eval_ptr);
            rb_eim_eval_writer.write_to_file("rb_eim_eval.bin"+system_name+system_name_suffix);
        #else
            _eim_con_ptr->get_rb_evaluation().legacy_write_offline_data_to_files("eim_offline_data"+system_name+system_name_suffix);
        #endif
      
        #if defined(LIBMESH_HAVE_CAPNPROTO)
            RBDataSerialization::RBEvaluationSerialization _rb_eval_writer(_rb_con_ptr->get_rb_evaluation());
            _rb_eval_writer.write_to_file("rb_eval.bin"+system_name+system_name_suffix);
        #else
            // Write the offline data to file (xdr format).
            _rb_con_ptr->get_rb_evaluation().legacy_write_offline_data_to_files("rb_offline_data"+system_name+system_name_suffix);
        #endif

        // If desired, store the basis functions (xdr format).
  
        _eim_con_ptr -> get_rb_evaluation().write_out_basis_functions(_eim_con_ptr->get_explicit_system(),"eim_offline_data"+system_name+system_name_suffix);  
        _rb_con_ptr->get_rb_evaluation().write_out_basis_functions(*_rb_con_ptr,"rb_offline_data"+system_name+system_name_suffix);    
        
        _rb_eval_ptr->clear();
        //_rb_con_ptr->clear();
        _es.delete_system("RB_System" + system_name + system_name_suffix);
    }
        
    Real get_child_subdomain_min(unsigned int param_number, unsigned int child_subdomain_number)
    //get_child_subdomain_min: gets the minimum values of the parameters for a particular child subdomain
    //Input parameters:
    //param_number: number of the parameter for which the min value is to be found
    //child_subdomain_number: number of the child_subdomain in question
    {
      Real result;
      
      if (0 >= param_number && (param_number > number_of_params))
        mooseError("Invalid input to function hpEIMNode::get_child_subdomain(int,int)");
      if (0 >= child_subdomain_number && (child_subdomain_number > number_of_subdomains))
        mooseError("Invalid input to function hpEIMNode::get_child_subdomain(int,int)");
      

      if (((child_subdomain_number - 1)&(1<<(param_number - 1))) != 0)
        result = gravity_center[param_number-1];
      else
        result = param_domain_min[param_number-1];
      return result;
    }

    //get_child_subdomain_max: gets the maximum values of the parameters for a particular child subdomain
    //Input parameters:
    //param_number: number of the parameter for which the max value is to be found
    //child_subdomain_number: number of the child_subdomain in question
    Real get_child_subdomain_max(unsigned int param_number, unsigned int child_subdomain_number)
    {
      Real result;
      
      if (0 >= param_number && (param_number > number_of_params))
        mooseError("Invalid input to function hpEIMNode::get_child_subdomain(int,int)");
      if (0 >= child_subdomain_number && (child_subdomain_number > number_of_subdomains))
        mooseError("Invalid input to function hpEIMNode::get_child_subdomain(int,int)");
      

      if ( ( (child_subdomain_number-1)&(1<<(param_number-1)) ) != 0)
        result = param_domain_max[param_number-1];
      else
        result = gravity_center[param_number-1];
      return result;
    }

    bool check_existence_of_all_children()
    //check_existence_of_all_children: returns True iff all children of current nod exist (are not NULL)
    {
      bool all_children_exist = 1;
      for (unsigned int i = 0; i < number_of_subdomains; i++)
        all_children_exist = all_children_exist && (children[i]);
      return all_children_exist;
    }

    
    bool check_non_existence_of_all_children()
    //check_non_existence_of_all_children: returns False iff none of the children of the current node exist (all childred are NULL)
    {
      bool flag = 0;
      for (unsigned int i = 0; i < number_of_subdomains; i++)
        flag = flag || (children[i]);
      return !(flag);
   }
    
    void print_node(std::string operation_mode)
    //prints info about the node
    //function takes as input the operation mode (online/offline) in question
    {
        if (operation_mode == "offline")
        {
            
            std::cout << std::endl << "Node id: " << system_name << system_name_suffix << std::endl;

            for (unsigned int param_number = 0; param_number < number_of_params; param_number++)
            {  
                std::cout << "For param " << param_number << ": param domain  [" << param_domain_min[param_number] << ", " << param_domain_max[param_number] << "] " << std::endl;
                std::cout << "Gravity center : " << gravity_center[param_number] << std::endl;
            }
            std::cout << "Number of subdomains = " << number_of_subdomains << std::endl;

            libMesh::out << "EIMSystem Name: " << _eim_con_ptr->name() << std::endl;
            _eim_con_ptr->print_info();
            std::cout << "EIM Basis error = " << EIM_error << std::endl;
            std::cout << "RB Error bound = " << RB_Error_bound << std::endl;
            if (check_existence_of_all_children())
            {
                for (unsigned int i = 0; i < number_of_subdomains; i++)
                    std::cout << "Child " << i + 1 << " not NULL" << std::endl;
                for (unsigned int i = 0; i < number_of_subdomains; i++)
                    children[i]->print_node(operation_mode);
            }
            else if (check_non_existence_of_all_children())
            {
                for (unsigned int i = 0; i < number_of_subdomains; i++)
                    std::cout << "Child " << i + 1 << " NULL" << std::endl;
            }
        }
        else if (operation_mode == "online")
        {
            std::cout << std::endl << "Node id: " << system_name << system_name_suffix << std::endl;
            for (unsigned int i = 0; i < number_of_params; i++)
                std::cout << "For param " << i << ": param modain ["  << std::setprecision(std::numeric_limits<long double>::digits10) << param_domain_min[i] << ", "  << std::setprecision(std::numeric_limits<long double>::digits10) << param_domain_max[i] << "] " << std::endl;
            
            std::cout << "Number of subdomains = " << number_of_subdomains << std::endl;
            std::cout << "EIM Basis error = " << EIM_error << std::endl;
            std::cout << "RB Error bound = " << RB_Error_bound << std::endl;
            
            if (check_existence_of_all_children())
            {
                for (unsigned int i = 0; i < number_of_subdomains; i++)
                    std::cout << "Child " << i + 1 << " not NULL" << std::endl;
                for (unsigned int i = 0; i < number_of_subdomains; i++)
                    children[i]->print_node(operation_mode);
            }
            else if (check_non_existence_of_all_children())
            {
                for (unsigned int i = 0; i < number_of_subdomains; i++)
                    std::cout << "Child " << i + 1 << " NULL" << std::endl;
            }            
        }
        else mooseError("Ivalid operation mode provided to print_node()");
    }

    void write_to_file(std::ofstream & outfile)
    {
        std::string node_info = std::to_string(number_of_params);
        
        outfile << check_existence_of_all_children() << "," << number_of_params;
        
        outfile << "," << EIM_error << ",";
        if (!isnan(RB_Error_bound))
            outfile << RB_Error_bound;
                
        for (int i = 0; i < number_of_params; i++)
            outfile << "," << std::setprecision(std::numeric_limits<long double>::digits10) << param_domain_min[i];
            //node_info = node_info + "," + std::to_string(param_domain_min[i]);
        
        for (int i = 0; i < number_of_params; i++)
            outfile << "," << std::setprecision(std::numeric_limits<long double>::digits10) << param_domain_max[i];
            //node_info = node_info + "," + std::to_string(param_domain_max[i]);
        
        outfile << std::endl; // do not forget the endline. Otherwise the program will crash.
         //<< std::setprecision(std::numeric_limits<long double>::digits10 << "," + node_info << std::endl;
        //std::cout << check_existence_of_all_children() << "," + node_info << std::endl;
    }
    
    void read_and_extend_hpEIM_tree(EquationSystems & _es, MooseMesh * _mesh_ptr, EIM_input_data _eim_data_in, std::ifstream & infile, bool children_exist) 
    // reads the next line from the input file stream provided and creates the descendents of the node provided in the online hp EIM tree
    // will create the descendents in depth-first order
    {
        bool grandchildren_exist;
        int number_of_params;
        std::vector<Real> param_min, param_max;
        Real EIM_error_child, RB_error_bound_child;
                
        if (children_exist)
        {
            for (unsigned int i = 0; i < number_of_subdomains; i++)
            {
                extract_hpEIM_node_info(infile, grandchildren_exist, number_of_params, EIM_error_child, RB_error_bound_child, param_min, param_max);
                for (int i = 0; i < param_max.size(); i++)
                {
                    _eim_data_in._cont_param_max[i] = param_max[i];
                    _eim_data_in._cont_param_min[i] = param_min[i];
                }
                _eim_data_in.EIM_error = EIM_error_child;
                _eim_data_in.RB_error_bound = RB_error_bound_child;
                
                children[i] = new DwarfElephanthpEIMNode(_es, _mesh_ptr,system_name+system_name_suffix, "_" + std::to_string(i+1), _eim_data_in, "online");
                children[i]->read_and_extend_hpEIM_tree(_es, _mesh_ptr, _eim_data_in, infile, grandchildren_exist);
                //std::cout << param_max[0] << " " << param_min[0] << std::endl;
                param_max.clear();
                param_min.clear();
            }
        }
    }
    
    void extract_hpEIM_node_info(std::ifstream & input_file, bool & children_exist, int & number_of_params, Real & EIM_error, Real & RB_error_bound, std::vector<Real> & param_min, std::vector<Real> & param_max)
    // extracts info on existence of children and param domain min/max values from the input file stream provided
    // Input Parameters:
    // input_file: input file stream. The tree is stored in this file after the offline phase
    // children_exist: is True if the calling node has children and False if it doesn't
    //
    // Output Parameters:
    // input_file: input file stream. The internal file pointer is advanced when this function executes.
    // number_of_params: int. Number of params in the problem
    // param_min: vector of real values. stores the min values for the params for the calling node
    // param_max: vector of real values. stores the max values for the params for the calling node
    {
        std::vector<Real> temp_vec;
        std::string word_in;
        std::getline(input_file,word_in,','); // read child_exist flag
        children_exist = boost::lexical_cast<bool>(word_in);
        std::getline(input_file,word_in,','); // read number of params
        number_of_params = boost::lexical_cast<int>(word_in);
        std::getline(input_file,word_in,','); // read Eim_error
        EIM_error = boost::lexical_cast<double>(word_in);
        std::getline(input_file,word_in,','); // read RB_error_bound
        if (word_in != "")
            RB_error_bound = boost::lexical_cast<double>(word_in);
        else
            RB_error_bound = std::sqrt(-1);
        
        std::getline(input_file,word_in,'\n'); // read param limits
        std::stringstream ss(word_in);

        Real temp_double;

        while (ss >> std::setprecision(std::numeric_limits<long double>::digits10) >> temp_double)
        {
            temp_vec.push_back(temp_double);

            if (ss.peek() == ',')
              ss.ignore();
        }

        for (int i = 0; i < temp_vec.size(); i++)
        {
            if (i < temp_vec.size()/2.0)
                param_min.push_back(temp_vec[i]);
            else
                param_max.push_back(temp_vec[i]);
        }
    }
    
    Real get_error()
    //gets the EIM approximation error for the basis in the current node
    {
      if (std::isnan(EIM_error))
      mooseError("EIM_error is still nan");
      else
          return EIM_error;
    }

    //destructor (recursively deletes all child nodes)
    ~DwarfElephanthpEIMNode()
    {
      for (unsigned int i = 0; i < number_of_subdomains; i++)
          if (children[i])
              children[i]->~DwarfElephanthpEIMNode(); 

      if (_eim_eval_ptr)
          delete _eim_eval_ptr;
      
      if (_rb_eval_ptr)
          delete _rb_eval_ptr;
    }

    DwarfElephantEIMConstructionSteadyState * _eim_con_ptr;
    DwarfElephantEIMEvaluationSteadyState * _eim_eval_ptr = NULL; //contains greedy_param_list
    DwarfElephantRBConstructionSteadyState * _rb_con_ptr;
    DwarfElephantRBEvaluationSteadyState * _rb_eval_ptr = NULL;
    std::vector<DwarfElephanthpEIMNode*> children;
    //DwarfElephanthpEIMNode * children;
    unsigned int number_of_params = -1/* number parameters involved in the non-affine function only */, number_of_subdomains = -1;
    std::vector<Real> gravity_center, param_domain_min, param_domain_max; // these are only for the parameters involved in EIM
    Real EIM_error = std::sqrt(-1), RB_Error_bound = std::sqrt(-1);
    std::string system_name, system_name_suffix, operation_mode;
    EIM_input_data _eim_data_this;
    EIM_input_data _eim_data_child;
    RB_input_data _rb_data_in;
    bool online_objects_initialized;
};

class DwarfElephanthpEIMM_aryTree
{
    // Class defining the M-ary tree to be used for hp EIM
    // The generated EIM approximations are stored in the leaves of this tree
    // The tree has a train reduced basis function which creates a number of EIM approximations by splitting the parameter domain until the required error tolerance is achieved with a small enough M in each EIM basis
    // The tree also has a find_EIM_basis function which finds the appropriate EIM basis to use for a particular parameter value
  public:
    // Constructor: DwarfElephanthpEIMM_aryTree
    // Input parameters: 
    // pd_min: array containing min values of parameters
    // pd_max: array containing max values of parameters
    // number_of_params: total number of parameters
    // _es: Moose/Libmesh equation system object
    // _mesh_ptr: Moose mesh pointer
    // EIM_error_tol: EIM Error tolerance to be achieved
    DwarfElephanthpEIMM_aryTree(EquationSystems & _es, MooseMesh * _mesh_ptr, EIM_input_data _eim_data_in, std::string operation_mode) :
    EIM_error_tol(_eim_data_in._rel_tol),
    max_leaf_EIM_basis_size(-1),
    max_leaf_EIM_error(std::numeric_limits<double>::infinity()),
    num_EIM_bases(-1),
            leaf_nodes_obtained(false)
    {
        //std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        //std::cout << "Starting root node creation" << std::endl;
        root = new DwarfElephanthpEIMNode(_es, _mesh_ptr, "", "_0", _eim_data_in, operation_mode);
        //std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        //auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        //std::cout << "Time spent in root node creation" << duration << std::endl;
    }

    // train hp EIM basis
    // Input parameters:
    // _es: Moose/Libmesh equation system object
    // _mesh_ptr: Moose mesh pointer
    void train_EIM_basis(EquationSystems & _es, MooseMesh * _mesh_ptr)
    {
      if (max_leaf_EIM_error < EIM_error_tol)
        std::cout << "hp EIM h error is already below the required tolerance" << std::endl;
      else
      {
        max_leaf_EIM_error = 0;
        DwarfElephanthpEIMNode *node = root;
        max_leaf_EIM_basis_size = 0;
        num_EIM_bases = 0;
        root->_eim_con_ptr->get_inner_product_matrix()->close();
        root->_eim_con_ptr->train_reduced_basis();
        root->EIM_error = root->_eim_con_ptr->compute_max_error_bound()/root->_eim_con_ptr->get_error_bound_normalization();
        
        split_leaves(node, EIM_error_tol, _es, _mesh_ptr);
      }
    }   

    // split_leaves: recursively visits each leaf of the tree and splits it if it does not satisfy the error tolerance
    // Input parameters:
    // node: Pointer to DwarfElephanthpEIMNode object
    // error_tol: error tolerance to be achieved
    // _es: Moose/libmesh equation system object
    // _mesh_ptr: Moose mesh pointer
    void split_leaves(DwarfElephanthpEIMNode *node, Real error_tol, EquationSystems & _es, MooseMesh * _mesh_ptr)
    {
      if (node->check_existence_of_all_children())
      {
        for (unsigned int i=0; i < root->number_of_subdomains; i++)
          split_leaves(node->children[i], error_tol, _es, _mesh_ptr);
      }
      if (node->check_non_existence_of_all_children())
      {
        if (node->get_error() >= error_tol)
        {
            std::cout << "Splitting following node because current EIM error: " << node->get_error() << ", which is larger than user-set error tolerance of " << error_tol;
            node->print_node("offline");
            node->split_param_domain(_es, _mesh_ptr);
            for (unsigned int i = 0; i < root->number_of_subdomains; i++)
                split_leaves(node->children[i], error_tol, _es, _mesh_ptr);
        }
        else
        {
          max_leaf_EIM_error = std::max(max_leaf_EIM_error, node->EIM_error);
          num_EIM_bases += 1;
          if (max_leaf_EIM_basis_size < node->_eim_eval_ptr->get_n_basis_functions())
              max_leaf_EIM_basis_size = node->_eim_eval_ptr->get_n_basis_functions();
        }
      }
    }

    void get_leaf_nodes()
    // stores a vector containing pointers to all the leaf nodes as a member of the hp EIM tree
    {
        if (!leaf_nodes_obtained)
        {
            recurse_get_leaf_nodes(root);
            leaf_nodes_obtained = true;
        }
        else
            mooseError("Leaf nodes already found for hp EIM M-ary tree");
    }
    
    void recurse_get_leaf_nodes(DwarfElephanthpEIMNode * node)
    // Gets a vector containing pointers to all leaf nodes of the tree with the given node as root
    // To get all leaves this function must be called with root node as the argument.
    {
        if (node->check_existence_of_all_children())
        {
            for (int i = 0; i < node->number_of_subdomains; i++)
                recurse_get_leaf_nodes(node->children[i]);
        }
        else
        {
            leaf_nodes.push_back(node);
            //std::cout << "Node: " << node->system_name << node->system_name_suffix << std::endl;
        }
    }
    
    void train_all_rb_models(EquationSystems & _es, MooseMesh * _mesh_ptr, FEProblemBase & _fe_problem, RB_input_data _rb_init_data, DwarfElephantRBConstructionSteadyState * _master_rb_con_ptr)
    // This method performs RB greedy using the EIM bases present in each leaf node of the tree
    // Each leaf node thus has its own RB model
    {
        if (leaf_nodes.size() != 0)
        {
            unsigned int _eim_f_vec_offset = 0;
            for (int i = 0; i < leaf_nodes.size(); i++)
            {
                leaf_nodes[i]->train_rb_model(_es, _mesh_ptr, _fe_problem, _rb_init_data, _master_rb_con_ptr, _eim_f_vec_offset);
                _eim_f_vec_offset += leaf_nodes[i]->_eim_eval_ptr->get_n_basis_functions();
            }
        }
        else
            mooseError("hp EIM basis not generated properly");
        write_tree("hpEIMtree.txt");
    }
    
    void set_up_online_rb_objects(EquationSystems & _es, MooseMesh * _mesh_ptr,FEProblemBase & _fe_problem)
    {
        if (!leaf_nodes_obtained) {   mooseError("Leaf nodes of hpEIM tree not obtained.");}
        else
        {
            for (unsigned int i = 0; i < leaf_nodes.size(); i++)
            {
                leaf_nodes[i]->_eim_con_ptr = &_es.add_system<DwarfElephantEIMConstructionSteadyState>("hp_EIM_System" + leaf_nodes[i]->system_name + leaf_nodes[i]->system_name_suffix);
                leaf_nodes[i]->_rb_con_ptr = &_es.add_system<DwarfElephantRBConstructionSteadyState>("RB_System" + leaf_nodes[i]->system_name + leaf_nodes[i]->system_name_suffix);
                leaf_nodes[i]->_eim_con_ptr->init();
                leaf_nodes[i]->_eim_con_ptr->get_explicit_system().init();
                leaf_nodes[i]->_rb_con_ptr->init();
                _es.update();
                leaf_nodes[i]->_eim_eval_ptr = new DwarfElephantEIMEvaluationSteadyState(_mesh_ptr->comm());
  
                // Pass a pointer of the RBEvaluation object to the
                // RBConstruction object
                leaf_nodes[i]->_eim_con_ptr->set_rb_evaluation(*leaf_nodes[i]->_eim_eval_ptr);
                leaf_nodes[i]->_rb_eval_ptr = new DwarfElephantRBEvaluationSteadyState(_mesh_ptr->comm(), _fe_problem);
                leaf_nodes[i]->_rb_con_ptr->set_rb_evaluation(*leaf_nodes[i]->_rb_eval_ptr);
                
                #if defined(LIBMESH_HAVE_CAPNPROTO)
                RBDataDeserialization::RBEIMEvaluationDeserialization _rb_eim_eval_reader(leaf_nodes[i]->_eim_con_ptr -> get_rb_evaluation());
                rb_eim_eval_reader.read_from_file("rb_eim_eval.bin");
                #else
                leaf_nodes[i]->_eim_con_ptr -> get_rb_evaluation().legacy_read_offline_data_from_files("eim_offline_data" + leaf_nodes[i]->system_name + leaf_nodes[i]->system_name_suffix);
                #endif
                leaf_nodes[i]->_eim_eval_ptr->read_in_basis_functions(leaf_nodes[i]->_eim_con_ptr->get_explicit_system(),"eim_offline_data"+leaf_nodes[i]->system_name+leaf_nodes[i]->system_name_suffix);
                
                leaf_nodes[i]->_eim_eval_ptr->initialize_eim_theta_objects();
                leaf_nodes[i]->_rb_eval_ptr->get_rb_theta_expansion().attach_multiple_F_theta(leaf_nodes[i]->_eim_eval_ptr->get_eim_theta_objects());
                
                #if defined(LIBMESH_HAVE_CAPNPROTO)
                RBDataSerialization::RBEvaluationDeserialization rb_eval_reader(leaf_nodes[i]->_rb_con_ptr -> get_rb_evaluation());
                rb_eval_reader.read_from_file("rb_eval.bin");
                #else
                leaf_nodes[i]->_rb_con_ptr -> get_rb_evaluation().legacy_read_offline_data_from_files("rb_offline_data" + leaf_nodes[i]->system_name + leaf_nodes[i]->system_name_suffix);
                #endif
                leaf_nodes[i]->online_objects_initialized = true;
            }
        }
            
    }
    
    void online_solve(RBParameters _rb_online_mu, unsigned int _online_N, bool _output_file, EquationSystems & _es, FEProblemBase & _fe_problem, MooseMesh * _mesh_ptr, DwarfElephantRBConstructionSteadyState * _master_rb_con_ptr, bool hpEIMTesting)
    {
        DwarfElephanthpEIMNode * _required_node = find_EIM_basis(_rb_online_mu);
        
        //if (!(_required_node->online_objects_initialized)) // Find better way to manage this since _required_node goes out of scope (and gets deleted) when function terminates
        //{
            _required_node->_eim_con_ptr = &_es.add_system<DwarfElephantEIMConstructionSteadyState>("hp_EIM_System" + _required_node->system_name + _required_node->system_name_suffix);
            _required_node->_rb_con_ptr = &_es.add_system<DwarfElephantRBConstructionSteadyState>("RB_System" + _required_node->system_name + _required_node->system_name_suffix);
            if (_es.n_systems() <= 2)
            {
                std::cout << "New systems not being added." << std::endl;
            }
            _required_node->_eim_con_ptr->init();
            _required_node->_eim_con_ptr->get_explicit_system().init();
            _required_node->_rb_con_ptr->init();
            _es.update();
            _required_node->_eim_eval_ptr = new DwarfElephantEIMEvaluationSteadyState(_mesh_ptr->comm());
  
            // Pass a pointer of the RBEvaluation object to the
            // RBConstruction object
            _required_node->_eim_con_ptr->set_rb_evaluation(*_required_node->_eim_eval_ptr);
            _required_node->_rb_eval_ptr = new DwarfElephantRBEvaluationSteadyState(_mesh_ptr->comm(), _fe_problem);
            _required_node->_rb_con_ptr->set_rb_evaluation(*_required_node->_rb_eval_ptr);
                
            #if defined(LIBMESH_HAVE_CAPNPROTO)
            RBDataDeserialization::RBEIMEvaluationDeserialization _rb_eim_eval_reader(leaf_nodes[i]->_eim_con_ptr -> get_rb_evaluation());
            rb_eim_eval_reader.read_from_file("rb_eim_eval.bin");
            #else
            _required_node->_eim_con_ptr -> get_rb_evaluation().legacy_read_offline_data_from_files("eim_offline_data" + _required_node->system_name + _required_node->system_name_suffix);
            #endif
            _required_node->_eim_eval_ptr->read_in_basis_functions(_required_node->_eim_con_ptr->get_explicit_system(),"eim_offline_data"+_required_node->system_name+_required_node->system_name_suffix);
                
            _required_node->_eim_eval_ptr->initialize_eim_theta_objects();
            _required_node->_rb_eval_ptr->get_rb_theta_expansion().attach_multiple_F_theta(_required_node->_eim_eval_ptr->get_eim_theta_objects());
                
            #if defined(LIBMESH_HAVE_CAPNPROTO)
            RBDataSerialization::RBEvaluationDeserialization rb_eval_reader(leaf_nodes[i]->_rb_con_ptr -> get_rb_evaluation());
            rb_eval_reader.read_from_file("rb_eval.bin");
            #else
            _required_node->_rb_con_ptr -> get_rb_evaluation().legacy_read_offline_data_from_files("rb_offline_data" + _required_node->system_name + _required_node->system_name_suffix);
            #endif
            _required_node->_rb_eval_ptr ->read_in_basis_functions(*_required_node->_rb_con_ptr,"rb_offline_data"+_required_node->system_name+_required_node->system_name_suffix);
            //_required_node->online_objects_initialized = true;
        //}
        std::cout << std::endl << "RB System chosen for online solve: ";
        _required_node->print_node("online");
        _required_node->_rb_eval_ptr->set_parameters(_rb_online_mu);
        _required_node->_rb_eval_ptr->print_parameters();
        _required_node->_rb_eval_ptr->rb_solve(_required_node->_rb_eval_ptr->get_n_basis_functions());
        
        // Code for testing of hpEIM online implementation
        if (hpEIMTesting)
        {
            unsigned int _eim_f_vec_offset = 0;
            for (int i = 0; i < leaf_nodes.size(); i++)
            {
                if (leaf_nodes[i]->system_name+leaf_nodes[i]->system_name_suffix == _required_node->system_name+_required_node->system_name_suffix)
                    break;
                _eim_f_vec_offset += leaf_nodes[i]->_eim_eval_ptr->get_n_basis_functions();
            }
        
            std::unique_ptr<SparseMatrix<Number>> temp_sparse_matrix = SparseMatrix<Number>::build(_master_rb_con_ptr->comm());
            DofMap & dof_map = _master_rb_con_ptr->get_dof_map();
            dof_map.attach_matrix(*temp_sparse_matrix);
            temp_sparse_matrix->init();
            temp_sparse_matrix->zero();
            temp_sparse_matrix->close();
        
            // Copy Affine matrices (all Aq matrices), required Fq vectors, and rb inner product matrix from _master_rb_con_ptr object
            _required_node->_rb_con_ptr->initialize_rb_construction(true,true);
            //_required_node->_rb_con_ptr->get_inner_product_matrix()->close();
        
            _master_rb_con_ptr->get_inner_product_matrix()->get_transpose(static_cast<SparseMatrix<Number>&>(*(_required_node->_rb_con_ptr->get_inner_product_matrix())));
            _required_node->_rb_con_ptr->get_inner_product_matrix()->close();
            _required_node->_rb_con_ptr->get_inner_product_matrix()->print_matlab("rb_ip_mat_online.m");
            for (unsigned int _q = 0; _q < _master_rb_con_ptr->get_rb_theta_expansion().get_n_A_terms(); _q++)
            {
                _master_rb_con_ptr->get_Aq(_q)->get_transpose(static_cast<SparseMatrix<Number>&>(*temp_sparse_matrix));
                temp_sparse_matrix->get_transpose(static_cast<SparseMatrix<Number>&>(*(_required_node->_rb_con_ptr->get_Aq(_q))));
            }
        
            for (unsigned int _q = 0; _q < _required_node->_rb_con_ptr->get_rb_theta_expansion().get_n_F_terms(); _q++)
            {
                _master_rb_con_ptr->get_Fq(_q + _eim_f_vec_offset)->swap(static_cast<NumericVector<Real>&>(*_required_node->_rb_con_ptr->get_Fq(_q)));   
            }
        
            _required_node->_rb_con_ptr->allocate_RB_error_structures();
            _required_node->_rb_con_ptr->do_RB_vs_FE_Error_analysis(_rb_online_mu, _es);
        }
        // Code for testing of hpEIM online implementation
        
        if(_output_file)
        {
            //_required_node->_eim_con_ptr -> get_rb_evaluation().read_in_basis_functions(_required_node->_eim_con_ptr->get_explicit_system(),"eim_offline_data"+_required_node->system_name+_required_node->system_name_suffix);
            

            _required_node->_eim_con_ptr -> load_rb_solution();
            _required_node->_rb_con_ptr -> load_rb_solution();
            
            *_es.get_system("rb0").solution = *_es.get_system("RB_System"+_required_node->system_name+_required_node->system_name_suffix).solution;
            *_es.get_system("aux0").solution = *_es.get_system("hp_EIM_System"+_required_node->system_name+_required_node->system_name_suffix+"_explicit_sys").solution;
            //_fe_problem.getNonlinearSystemBase().update();
            unsigned int num_sys = _es.n_systems();
            std::vector<std::string> sys_names;
            for (unsigned int i = 0; i < num_sys; i++)
                sys_names.push_back(_es.get_system(i).name());
            
            for (unsigned int i = 0; _es.n_systems() > 2; i++)
            {
               
                if ((sys_names[i] != "rb0") && (sys_names[i] != "aux0"))
                {    
                    _es.delete_system(sys_names[i]);
                }
                //std::cout <<"Number of systems left" <<  _es.n_systems() << std::endl;
            }
            
            std::stringstream ss;
           
            ss << std::setw(2) << std::setfill('0') << _online_N;
         
	    #ifdef LIBMESH_HAVE_EXODUS_API
	    ExodusII_IO(_mesh_ptr->getMesh()).write_equation_systems("RB_sol_DwarfElephant.e-s"+ss.str(),_es);
	    #endif
            VTKIO(_mesh_ptr->getMesh()).write_equation_systems("out.pvtu", _es);
        }
        else
        {
            delete _required_node->_rb_eval_ptr;
            delete _required_node->_eim_eval_ptr;
        
            _required_node->_rb_eval_ptr = NULL;
            _required_node->_eim_eval_ptr = NULL;
        
            std::string eim_sys_name = _required_node->_eim_con_ptr->name();
            std::string eim_expl_sys_name = _required_node->_eim_con_ptr->get_explicit_system().name();
            std::string rb_sys_name = _required_node->_rb_con_ptr->name();
        
            _es.delete_system(rb_sys_name);
            _es.delete_system(eim_expl_sys_name);
            _es.delete_system(eim_sys_name);       
        }
    }
    // find_EIM_basis
    // Input parameters:
    // param_value: array containing all parameter values
    DwarfElephanthpEIMNode * find_EIM_basis(RBParameters _rb_online_mu)
    {
      bool subdomain_match = 1;
      DwarfElephanthpEIMNode *node = root;
      std::vector<Real> param_value;
      
      

      for (unsigned int j = 0; j < root->number_of_params; j++) // check if param_value is in root parameter domain
      {
          param_value.push_back(_rb_online_mu.get_value("mu_" + std::to_string(j)));
          subdomain_match = subdomain_match & ((param_value[j] >= node->param_domain_min[j]) & (param_value[j] <= node->param_domain_max[j]));
      }
      if (!subdomain_match)
        mooseError("hp M-ary Tree: param_value searched for is outside original parameter domain");

      while (node->check_existence_of_all_children())
      {
        for (unsigned int i = 0; i < root->number_of_subdomains; i++)
        {
          for (unsigned int j = 0; j < root->number_of_params; j++)
            subdomain_match = subdomain_match & ((param_value[j] >= node->children[i]->param_domain_min[j]) & (param_value[j] <= node->children[i]->param_domain_max[j]));
          if (subdomain_match)
          {
              node = node->children[i];
              break;
          }
          else
            subdomain_match = 1;
        }
      }
      return node;
    }

    void write_nodes(DwarfElephanthpEIMNode * node, std::ofstream & outfile)
    // writes all nodes of the hpEIM tree to file recursively in depth first order
    {
        node->write_to_file(outfile);
        
        if (node->check_existence_of_all_children())
        {
            for (int i = 0; i < node->number_of_subdomains; i++)
                write_nodes(node->children[i], outfile);
        }
    }
    
    void print_leaf_nodes(std::string operation_mode)
    {
        for (int i = 0; i < leaf_nodes.size(); i++)
        {
            leaf_nodes[i]->print_node(operation_mode);
        }
    }
    
    void write_tree(std::string filename)
    // Writes the current tree to a text file in minimal form so that it can be reconstructed for use in the online phase
    // Only param min/max info is stored for each node
    {
        std::ofstream outfile;
        outfile.open(filename);
        write_nodes(root, outfile);
        outfile.close();
    }
    
    
    // print_info: prints info about the tree object
    void print_info(std::string operation_mode)
    {
        std::cout << "Info about hpEIM M-ary tree:" << std::endl;
      std::cout << "EIM error tolerance = " << EIM_error_tol << std::endl;
      std::cout << "max. leaf EIM error = " << max_leaf_EIM_error << std::endl;
      std::cout << "max. leaf EIM basis size = " << max_leaf_EIM_basis_size << std::endl;
      std::cout << "number of EIM approximations = " << num_EIM_bases << std::endl;
      root->print_node(operation_mode);
    }

    // destructor
    ~DwarfElephanthpEIMM_aryTree()
    {
      root->~DwarfElephanthpEIMNode();
    }

    DwarfElephanthpEIMNode *root; // pointer to the root node of the tree
    std::vector<DwarfElephanthpEIMNode *> leaf_nodes; // stores pointers to all leaf nodes of the tree
    Real EIM_error_tol; // EIM error tolerance to be achieved
    unsigned int max_leaf_EIM_basis_size; // maximum basis size among all the leaves of the tree
    Real max_leaf_EIM_error; // maximum EIM error among all leaves of the tree (should be less than the overall EIM_error_tolerance)
    unsigned int num_EIM_bases; // number of leaves in tree
    bool leaf_nodes_obtained;
};



///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBCLASSESSTEADYSTATE_H
