[Mesh]
 file = ReducedBasisGeom3D_7_fullylabeled_debug.msh
[]

[Variables]
  [./temperature]
    order = FIRST
    TYPE = LAGRANGE
  [../]
[]

[AuxVariables]
  [./HeatSourceVis]
    order = FIRST
    type = LAGRANGE
  [../]
[]

[GlobalParams]
  initial_rb_userobject = initializeRBSystem
  variable = temperature
[]
[Kernels]
[./DiffusionXX_maxZ1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 0
  simulation_type = transient
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxZ1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 1
  simulation_type = transient
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxZ1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 2
  simulation_type = transient
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 3
  simulation_type = transient
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 4
  simulation_type = transient
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxZ1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 5
  simulation_type = transient
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxZ1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 6
  simulation_type = transient
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxZ1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 7
  simulation_type = transient
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 8
  simulation_type = transient
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 9
  simulation_type = transient
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxZ2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 10
  simulation_type = transient
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxZ2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 11
  simulation_type = transient
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 12
  simulation_type = transient
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 13
  simulation_type = transient
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxZ2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 14
  simulation_type = transient
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxZ2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 15
  simulation_type = transient
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxZ2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 16
  simulation_type = transient
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 17
  simulation_type = transient
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 18
  simulation_type = transient
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxZ3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 19
  simulation_type = transient
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxZ3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 20
  simulation_type = transient
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 21
  simulation_type = transient
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 22
  simulation_type = transient
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxZ3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 23
  simulation_type = transient
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxZ3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 24
  simulation_type = transient
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxZ3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 25
  simulation_type = transient
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 26
  simulation_type = transient
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 27
  simulation_type = transient
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxZ4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 28
  simulation_type = transient
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxZ4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 29
  simulation_type = transient
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 30
  simulation_type = transient
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 31
  simulation_type = transient
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxZ4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 32
  simulation_type = transient
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxZ4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 33
  simulation_type = transient
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxZ4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 34
  simulation_type = transient
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 35
  simulation_type = transient
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 36
  simulation_type = transient
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxZ5]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 37
  simulation_type = transient
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ5]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 38
  simulation_type = transient
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 39
  simulation_type = transient
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 40
  simulation_type = transient
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 41
  simulation_type = transient
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minX1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 42
  simulation_type = transient
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minX1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 43
  simulation_type = transient
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minX1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 44
  simulation_type = transient
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 45
  simulation_type = transient
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minX1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 46
  simulation_type = transient
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minX1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 47
  simulation_type = transient
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minX1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 48
  simulation_type = transient
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 49
  simulation_type = transient
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 50
  simulation_type = transient
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minX2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 51
  simulation_type = transient
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minX2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 52
  simulation_type = transient
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minX2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 53
  simulation_type = transient
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 54
  simulation_type = transient
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minX2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 55
  simulation_type = transient
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minX2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 56
  simulation_type = transient
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minX2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 57
  simulation_type = transient
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 58
  simulation_type = transient
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 59
  simulation_type = transient
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minX3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 60
  simulation_type = transient
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minX3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 61
  simulation_type = transient
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minX3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 62
  simulation_type = transient
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 63
  simulation_type = transient
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minX3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 64
  simulation_type = transient
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minX3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 65
  simulation_type = transient
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minX3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 66
  simulation_type = transient
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 67
  simulation_type = transient
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 68
  simulation_type = transient
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minX4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 69
  simulation_type = transient
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minX4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 70
  simulation_type = transient
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minX4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 71
  simulation_type = transient
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 72
  simulation_type = transient
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minX4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 73
  simulation_type = transient
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minX4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 74
  simulation_type = transient
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minX4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 75
  simulation_type = transient
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 76
  simulation_type = transient
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 77
  simulation_type = transient
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 78
  simulation_type = transient
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minX5]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 79
  simulation_type = transient
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minX5]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 80
  simulation_type = transient
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 81
  simulation_type = transient
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 82
  simulation_type = transient
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxY1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 83
  simulation_type = transient
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxY1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 84
  simulation_type = transient
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxY1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 85
  simulation_type = transient
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 86
  simulation_type = transient
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxY1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 87
  simulation_type = transient
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxY1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 88
  simulation_type = transient
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxY1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 89
  simulation_type = transient
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 90
  simulation_type = transient
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 91
  simulation_type = transient
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxY2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 92
  simulation_type = transient
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxY2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 93
  simulation_type = transient
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxY2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 94
  simulation_type = transient
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 95
  simulation_type = transient
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxY2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 96
  simulation_type = transient
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxY2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 97
  simulation_type = transient
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxY2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 98
  simulation_type = transient
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 99
  simulation_type = transient
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 100
  simulation_type = transient
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxY3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 101
  simulation_type = transient
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxY3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 102
  simulation_type = transient
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxY3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 103
  simulation_type = transient
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 104
  simulation_type = transient
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxY3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 105
  simulation_type = transient
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxY3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 106
  simulation_type = transient
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxY3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 107
  simulation_type = transient
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 108
  simulation_type = transient
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 109
  simulation_type = transient
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxY4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 110
  simulation_type = transient
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxY4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 111
  simulation_type = transient
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxY4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 112
  simulation_type = transient
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 113
  simulation_type = transient
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxY4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 114
  simulation_type = transient
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxY4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 115
  simulation_type = transient
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxY4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 116
  simulation_type = transient
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 117
  simulation_type = transient
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 118
  simulation_type = transient
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxY5]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 119
  simulation_type = transient
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 120
  simulation_type = transient
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxY5]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 121
  simulation_type = transient
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 122
  simulation_type = transient
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 123
  simulation_type = transient
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxX1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 124
  simulation_type = transient
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxX1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 125
  simulation_type = transient
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxX1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 126
  simulation_type = transient
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 127
  simulation_type = transient
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxX1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 128
  simulation_type = transient
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxX1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 129
  simulation_type = transient
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxX1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 130
  simulation_type = transient
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 131
  simulation_type = transient
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 132
  simulation_type = transient
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxX2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 133
  simulation_type = transient
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxX2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 134
  simulation_type = transient
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxX2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 135
  simulation_type = transient
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 136
  simulation_type = transient
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxX2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 137
  simulation_type = transient
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxX2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 138
  simulation_type = transient
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxX2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 139
  simulation_type = transient
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 140
  simulation_type = transient
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 141
  simulation_type = transient
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxX3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 142
  simulation_type = transient
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxX3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 143
  simulation_type = transient
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxX3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 144
  simulation_type = transient
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 145
  simulation_type = transient
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxX3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 146
  simulation_type = transient
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxX3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 147
  simulation_type = transient
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxX3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 148
  simulation_type = transient
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 149
  simulation_type = transient
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 150
  simulation_type = transient
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxX4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 151
  simulation_type = transient
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxX4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 152
  simulation_type = transient
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxX4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 153
  simulation_type = transient
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 154
  simulation_type = transient
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxX4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 155
  simulation_type = transient
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxX4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 156
  simulation_type = transient
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxX4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 157
  simulation_type = transient
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 158
  simulation_type = transient
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 159
  simulation_type = transient
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 160
  simulation_type = transient
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxX5]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 161
  simulation_type = transient
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxX5]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 162
  simulation_type = transient
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 163
  simulation_type = transient
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 164
  simulation_type = transient
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minY1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 165
  simulation_type = transient
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minY1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 166
  simulation_type = transient
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minY1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 167
  simulation_type = transient
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 168
  simulation_type = transient
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minY1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 169
  simulation_type = transient
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minY1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 170
  simulation_type = transient
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minY1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 171
  simulation_type = transient
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 172
  simulation_type = transient
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 173
  simulation_type = transient
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minY2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 174
  simulation_type = transient
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minY2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 175
  simulation_type = transient
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minY2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 176
  simulation_type = transient
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 177
  simulation_type = transient
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minY2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 178
  simulation_type = transient
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minY2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 179
  simulation_type = transient
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minY2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 180
  simulation_type = transient
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 181
  simulation_type = transient
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 182
  simulation_type = transient
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minY3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 183
  simulation_type = transient
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minY3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 184
  simulation_type = transient
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minY3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 185
  simulation_type = transient
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 186
  simulation_type = transient
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minY3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 187
  simulation_type = transient
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minY3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 188
  simulation_type = transient
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minY3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 189
  simulation_type = transient
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 190
  simulation_type = transient
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 191
  simulation_type = transient
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minY4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 192
  simulation_type = transient
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minY4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 193
  simulation_type = transient
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minY4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 194
  simulation_type = transient
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 195
  simulation_type = transient
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minY4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 196
  simulation_type = transient
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minY4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 197
  simulation_type = transient
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minY4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 198
  simulation_type = transient
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 199
  simulation_type = transient
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 200
  simulation_type = transient
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minY5]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 201
  simulation_type = transient
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 202
  simulation_type = transient
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minY5]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 203
  simulation_type = transient
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 204
  simulation_type = transient
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 205
  simulation_type = transient
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 206
  simulation_type = transient
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minZ1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 207
  simulation_type = transient
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 208
  simulation_type = transient
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 209
  simulation_type = transient
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minZ1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 210
  simulation_type = transient
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minZ1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 211
  simulation_type = transient
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minZ1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 212
  simulation_type = transient
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 213
  simulation_type = transient
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 214
  simulation_type = transient
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 215
  simulation_type = transient
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minZ2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 216
  simulation_type = transient
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 217
  simulation_type = transient
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 218
  simulation_type = transient
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minZ2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 219
  simulation_type = transient
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minZ2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 220
  simulation_type = transient
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minZ2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 221
  simulation_type = transient
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 222
  simulation_type = transient
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 223
  simulation_type = transient
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 224
  simulation_type = transient
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minZ3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 225
  simulation_type = transient
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 226
  simulation_type = transient
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 227
  simulation_type = transient
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minZ3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 228
  simulation_type = transient
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minZ3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 229
  simulation_type = transient
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minZ3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 230
  simulation_type = transient
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 231
  simulation_type = transient
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 232
  simulation_type = transient
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 233
  simulation_type = transient
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minZ4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 234
  simulation_type = transient
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 235
  simulation_type = transient
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 236
  simulation_type = transient
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minZ4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 237
  simulation_type = transient
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minZ4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 238
  simulation_type = transient
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minZ4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 239
  simulation_type = transient
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 240
  simulation_type = transient
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 241
  simulation_type = transient
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ5]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 242
  simulation_type = transient
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ5]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 243
  simulation_type = transient
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 244
  simulation_type = transient
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 245
  simulation_type = transient
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_VesselCyl]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 246
  simulation_type = transient
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_VesselCyl]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 247
  simulation_type = transient
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_VesselCyl]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 248
  simulation_type = transient
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_BoundingBox]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 249
  simulation_type = transient
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_BoundingBox]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 250
  simulation_type = transient
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_BoundingBox]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 251
  simulation_type = transient
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./PennesPerfusion_VesselCyl]
  type = DwarfElephantRBPennesPerfusion
  ID_Aq = 252
  simulation_type = transient
  block = 31
matrix_seperation_according_to_subdomains = false
[../]

  [./EIM_1]
    type = DwarfElephantEIMFKernel
    block = 1
  [../]
   
  [./EIM_2]
    type = DwarfElephantEIMFKernel
    block = 2
  [../]
   
  [./EIM_3]
    type = DwarfElephantEIMFKernel
    block = 3
  [../]
   
  [./EIM_4]
    type = DwarfElephantEIMFKernel
    block = 4
  [../]
   
  [./EIM_5]
    type = DwarfElephantEIMFKernel
    block = 5
  [../]
   
  [./EIM_6]
    type = DwarfElephantEIMFKernel
    block = 6
  [../]
   
  [./EIM_7]
    type = DwarfElephantEIMFKernel
    block = 7
  [../]
   
  [./EIM_8]
    type = DwarfElephantEIMFKernel
    block = 8
  [../]
   
  [./EIM_9]
    type = DwarfElephantEIMFKernel
    block = 9
  [../]
   
  [./EIM_10]
    type = DwarfElephantEIMFKernel
    block = 10
  [../]
   
  [./EIM_11]
    type = DwarfElephantEIMFKernel
    block = 11
  [../]
   
  [./EIM_12]
    type = DwarfElephantEIMFKernel
    block = 12
  [../]
   
  [./EIM_13]
    type = DwarfElephantEIMFKernel
    block = 13
  [../]
   
  [./EIM_14]
    type = DwarfElephantEIMFKernel
    block = 14
  [../]
   
  [./EIM_15]
    type = DwarfElephantEIMFKernel
    block = 15
  [../]
   
  [./EIM_16]
    type = DwarfElephantEIMFKernel
    block = 16
  [../]
   
  [./EIM_17]
    type = DwarfElephantEIMFKernel
    block = 17
  [../]
   
  [./EIM_18]
    type = DwarfElephantEIMFKernel
    block = 18
  [../]
   
  [./EIM_19]
    type = DwarfElephantEIMFKernel
    block = 19
  [../]
   
  [./EIM_20]
    type = DwarfElephantEIMFKernel
    block = 20
  [../]
   
  [./EIM_21]
    type = DwarfElephantEIMFKernel
    block = 21
  [../]
   
  [./EIM_22]
    type = DwarfElephantEIMFKernel
    block = 22
  [../]
   
  [./EIM_23]
    type = DwarfElephantEIMFKernel
    block = 23
  [../]
   
  [./EIM_24]
    type = DwarfElephantEIMFKernel
    block = 24
  [../]
   
  [./EIM_25]
    type = DwarfElephantEIMFKernel
    block = 25
  [../]
   
  [./EIM_26]
    type = DwarfElephantEIMFKernel
    block = 26
  [../]
   
  [./EIM_27]
    type = DwarfElephantEIMFKernel
    block = 27
  [../]
   
  [./EIM_28]
    type = DwarfElephantEIMFKernel
    block = 28
  [../]
   
  [./EIM_29]
    type = DwarfElephantEIMFKernel
    block = 29
  [../]
   
  [./EIM_30]
    type = DwarfElephantEIMFKernel
    block = 30
  [../]
   
  [./EIM_31]
    type = DwarfElephantEIMFKernel
    block = 31
  [../]
   
  [./EIM_32]
    type = DwarfElephantEIMFKernel
    block = 32
  [../]
   
[./RB_inner_product_matrix]
  type = RBInnerProductMatrix
[../]
[]

[AuxKernels]
  [./HeatSourceVisAux]
    type = FunctionAux
    function = 'gaussian'#'rf_heat_source'
    variable = HeatSourceVis
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
[./Convection_BC]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = ' 33 34 35 36 37 38 39 40 41 42 43 44'
ID_Aq = 253
  value = 0
  penalty = 1.0
 variable = temperature
matrix_seperation_according_to_subdomains = false
[../]
[]

[Problem]
  type = DwarfElephantRBProblem
[]

[Executioner]
  type = DwarfElephantRBExecutioner
  solve_type = 'Newton'
  l_tol = 1.0e-8
  nl_rel_tol = 1.0e-8
  #offline_stage = false
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre    boomeramg      101'
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemSteadyState
  use_EIM = true
  use_hp_EIM = false
  #hp_EIM_testing = true # Testing of hp EIM implementation possbile only during the online phase
  N_max_EIM = 3
  n_training_samples_EIM = 6
  rel_training_tolerance_EIM = 1e-4
  #abs_training_tolerance_EIM = 1e-4
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3 mu_4'# mu_2'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '0.001 0.002 -0.02 -0.02 -0.02'# 0.01'
  parameter_max_values_EIM = '0.005 0.006 0.02 0.02 0.02'# 1.0'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  execute_on = 'initial'
  N_max_RB = 12
  #offline_stage = false
  n_training_samples_RB = 40
  rel_training_tolerance_RB = 1.e-3
  #abs_training_tolerance_RB = 1e-3
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3 mu_4'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '0.001 0.002 -0.02 -0.02 -0.02'
  parameter_max_values_RB = '0.005 0.006 0.02 0.02 0.02'
  deterministic_training_RB = false
  normalize_rb_bound_in_greedy = false
[../]

[./jEIMInnerProductMatrixComputation]
  type = DwarfElephantComputeEIMInnerProductMatrixSteadyState
  execute_on = "EIM"
  initialize_rb_userobject = initializeRBSystem
[../]

[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  #online_stage = true
  online_mu = '0.003 0.004 -0.01 -0.01 -0.01'
  online_N = 5
  #offline_stage = false
  execute_on = 'timestep_end'
[../]
[]

[Outputs]
exodus = true
print_perf_log = true
  [./console]
    type = Console
    outlier_variable_norms = false
  [../]
[]
