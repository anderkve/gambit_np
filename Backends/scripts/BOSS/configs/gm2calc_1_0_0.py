###################################
#                                 #
#  Configuration module for BOSS  #
#                                 #
###################################


# ~~~~~ CASTXML options ~~~~~

# See CastXML documentation for details on these options: 
#
#   https://github.com/CastXML/CastXML/blob/master/doc/manual/castxml.1.rst 
#

castxml_cc_id  = 'gnu'      # Reference compiler: 'gnu', 'gnu-c', 'msvc', 'msvc-c'
castxml_cc     = 'g++'      # Name a specific compiler: 'g++', 'cl', ...
castxml_cc_opt = ''         # Additional option string passed to the compiler in castxml_cc (e.g. '-m32')


# ~~~~~ GAMBIT-specific options ~~~~~

gambit_backend_name    = 'gm2calc'
gambit_backend_version = '1.0.0'
gambit_base_namespace  = ''


# ~~~~~ Information about the external code ~~~~~

# Use either absolute paths or paths relative to the main BOSS directory.

input_files = [
   '../../../Backends/installed/gm2calc/1.0.0/src/MSSMNoFV_onshell.hpp',
   '../../../Backends/installed/gm2calc/1.0.0/src/gm2_1loop.hpp',
   '../../../Backends/installed/gm2calc/1.0.0/src/gm2_2loop.hpp',
]

include_paths = [
    '../../../Backends/installed/gm2calc/1.0.0/src', 
    '/usr/include/eigen3',
    '/usr/include'
]

source_path   = '../../../Backends/installed/gm2calc/1.0.0/src'

accepted_paths = ['../../../Backends/installed/gm2calc/1.0.0']

loaded_classes = [
    'gm2calc::MSSMNoFV_onshell_susy_parameters',
    'gm2calc::MSSMNoFV_onshell',
    'gm2calc::MSSMNoFV_onshell_mass_eigenstates',
    'gm2calc::MSSMNoFV_onshell_problems',
    'gm2calc::MSSMNoFV_onshell_soft_parameters',
    'gm2calc::MSSMNoFV_onshell_physical',
]

loaded_functions = [
  'gm2calc::calculate_amu_1loop(const gm2calc::MSSMNoFV_onshell&)',
  'gm2calc::calculate_amu_1loop_non_tan_beta_resummed(const gm2calc::MSSMNoFV_onshell&)',
  'gm2calc::calculate_amu_2loop(const gm2calc::MSSMNoFV_onshell&)',
  'gm2calc::calculate_amu_2loop_non_tan_beta_resummed(const gm2calc::MSSMNoFV_onshell&)',
]

ditch = []


load_parent_classes    = False
wrap_inherited_members = False


header_extension = '.hpp'
source_extension = '.cpp'

indent = 3

extra_output_dir       = 'BOSS_output'
abstr_header_prefix    = 'abstract_'
wrapper_header_prefix  = 'wrapper_'
factory_file_prefix    = 'factory_'
function_files_prefix  = 'function_'


# ~~~~~ Information about other known types ~~~~~

known_classes = [ 
    "Eigen::Matrix<double,2,2,0,2,2>",
    "Eigen::Matrix<double,3,3,0,3,3>",
    "Eigen::Matrix<double,4,4,0,4,4>",
    "Eigen::Array<double,1,1,0,1,1>",
    "Eigen::Array<double,2,1,0,2,1>",
    "Eigen::Array<double,4,1,0,4,1>",
    "Eigen::Matrix<std::complex<double>,2,2,0,2,2>",
    "Eigen::Matrix<std::complex<double>,4,4,0,4,4>",
]


known_class_headers = {
    "Eigen::Matrix"          : "<Eigen/Core>",
    "Eigen::Array"           : "<Eigen/Core>",
}

