import subprocess
import os

def get_KernelIDs_and_blocks(filename):
  with open(filename,"r") as KernelList_File:
    KernelList_lines = KernelList_File.readlines()

  KernelIDs_and_blocks = []

  for i in range(len(KernelList_lines)):
    if KernelList_lines[i].find(" type") != -1:
      temp_list = KernelList_lines[i].split(" type = ")
      KernelID = temp_list[1].strip('\n')
      print KernelID
    if KernelList_lines[i].find("block") != -1:
      temp_list = KernelList_lines[i].split("block = ")
      block = temp_list[1].strip('\n')
      KernelIDs_and_blocks.append([KernelID,block])
  return KernelIDs_and_blocks

def writeInputFile(filename,mesh_file_name,r_new,l_new,offset,KernelIDs_and_blocks): #RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh0.msh
  PreKernelText = """[Mesh]
  file = """ + mesh_file_name + """
[]

[Variables]
  [./temperature]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./TissueDamage]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[GlobalParams]
  initial_rb_userobject = initializeRBSystem
  variable = temperature
[]
[Kernels]
"""

  KernelText=""

  if offset == 250:
    N = 3
  else:
    N = 10

  for i in range(N):
    KernelText += "[./Kernel_"+str(i)+"""]
  type = """ + KernelIDs_and_blocks[offset + i][0] + """
  simulation_type = transient
  ID_Aq = """+str(i)+"""
  block = """+KernelIDs_and_blocks[offset + i][1]+"""
  matrix_separation_according_to_subdomains = false
[../]
"""
    
  PostKernelText="""[./DummyKernel]
  type = Diffusion
  variable = temperature
[../]
#[./RB_inner_product_matrix]
#  type = RBInnerProductMatrixTransient
#[../]
[]

[AuxKernels]
  [./HeatSourceVisAux]
    type = FunctionAux
    function = 'gaussian'#'rf_heat_source'
    variable = TissueDamage
    execute_on = 'timestep_end'
  [../]
[]

[Functions]
  [./gaussian]
    type = ParsedFunction
    value = 'exp(-(x + 0.1)^2 - (y + 0.1)^2)'
  [../]
[]
[BCs]
[]

[Problem]
  type = DwarfElephantRBProblem
[]

[Executioner]
  type = DwarfElephantRBExecutioner
  simulation_type = 'transient'
  solve_type = 'Newton'
  l_tol = 1e-8#1.0e-8
  nl_rel_tol = 1e-8#1.0e-8
  #offline_stage = false
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemTransient
  use_EIM = false#true#
  N_max_EIM = 0#5#50#50#
  n_training_samples_EIM = 0#50#300#
  rel_training_tolerance_EIM = 1e-8
  #abs_training_tolerance_EIM = 1e-4
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3 mu_4 mu_5 mu_6 mu_7 mu_8 mu_9 mu_10 mu_11 mu_12'# mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '3e-3 5e-2 -0.01 -0.01 -0.01 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'#'0.001 0.002 -0.02 -0.02 -0.02'
  parameter_max_values_EIM = '3e-3 5e-2 -0.01 -0.01 -0.01 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'#'0.005 0.006 0.02 0.02 0.02'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  euler_theta_RB = 1 #backward euler
  execute_on = 'initial'
  N_max_RB = 1
  n_time_steps_RB = 2
  delta_N_RB = 1
  delta_t_RB = 0.707106781187
  POD_tol = -1e-6 #should be negative for the transient case
  max_truth_solves_RB = 500
  #offline_stage_RB = false
  n_training_samples_RB = 1#50
  rel_training_tolerance_RB = 1.e-3
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3 mu_4 mu_5 mu_6 mu_7 mu_8 mu_9 mu_10 mu_11 mu_12' # r0 l0 x_n y_n z_n theta_n phi_n P_n omega_p r l k rhoC #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '""" + str(r_new) + " " + str(l_new) + """ 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  parameter_max_values_RB = '""" + str(r_new) + " " + str(l_new) + """ 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  normalize_rb_bound_in_greedy = true
  RB_RFA = true#
[../]
[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageTransient
  #offline_stage = false
  online_stage = false
  online_mu = '""" + str(r_new) + " " + str(l_new) + """ 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  mu_ref = '""" + str(r_new) + " " + str(l_new) + """ 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  online_N = 0
  execute_on = 'timestep_end'
  num_online_solves = 1#3
  online_mu_0= '3e-3 5e-2 -0.01 -0.01 -0.01' 
  #online_mu_1= '2.2e-3 3e-2 -0.1 -0.1 -0.1 ' 
  #online_mu_2= '3.4e-3 5e-3 -0.1 -0.1 -0.1 '
  mesh_index = 0
  Aq_mat_offset = """+str(offset)+"""
  Mq_mat_offset = 0
[../]
[]
"""
  with open(filename,"w") as input_file:
    input_file.writelines(PreKernelText + KernelText + PostKernelText)

def subprocess_cmd(command):
    process = subprocess.Popen(command,stdout=subprocess.PIPE, shell=True)
    proc_stdout = process.communicate()[0].strip()
    print proc_stdout


KernelIDs_and_blocks = get_KernelIDs_and_blocks("Diff_and_Perf_Kernels_list.txt")
mesh_file_names = ["RBGeom_Test.msh"]#["RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh0.msh","RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh1.msh","RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh2.msh","RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh3.msh","RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh4.msh"]
r_l_new = ["00.003","00.04"]#[["00.0004","00.0005"],["00.003","00.04"],["00.005","00.07"]] #[[r_new,l_new]]
for mesh_file_name in mesh_file_names:
  for geom_param in r_l_new:
    for i in range(26):
      offset = i*10
      writeInputFile("Obtain_Aq.i",mesh_file_name,geom_param[0],geom_param[1],offset,KernelIDs_and_blocks)
      subprocess_cmd("qsh; ./DwarfElephant-opt -i Obtain_Aq.i")
      # add code to delete extra .m files
for i in range(253,260):
  subprocess.call("rm ./3DRBRFAMatrices/MeshConvMatrices/Aq_"+str(i)+".m",shell=True)
