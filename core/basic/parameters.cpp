
#include "parameters.h"

using namespace Bx::Basic;

namespace po = boost::program_options;

Parameters::Parameters()
{
  _parameterDesc.add_options()
              ("help, h", "help information")
              ("file, f", "configuration file")
}

Parameters::getParams(int argc, char* pArgv[])
{
    
}


