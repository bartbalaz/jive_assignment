
#include <string>

#include "parameters.h"

using namespace Bx::Basic;

namespace po = boost::program_options;

Parameters::Parameters()
{
  _parameterDesc.add_options()
              ("version, v", "application version")
              ("help, h", "help information")
              ("file, f", po::value<string>(), "configuration file in INI format")
              ;
}

Parameters::getParams(int argc, char* pArgv[])
{
    po::store(po::command_line_parser(argc, pArgv));
    
}


