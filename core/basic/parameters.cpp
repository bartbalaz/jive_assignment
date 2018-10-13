
#include <string>
#include <iostream> 

#include "parameters.h"

using namespace Bx::Basic;

namespace po = boost::program_options;

Parameters::Parameters()
{
  _basicParams.add_options()
              ("version, v", "application version")
              ("help, h", "help information")
              ("file, f", po::value<string>(), "configuration file in INI format")
              ("log-level, ll", po::value<string>()->default_value("inf"),
                "log level: tra, dbg, inf (default), wrn, err, ftl")
              ("log-file, lf", po::value<string>(), "log file name")
              ;
}

Parameters::Cont
Parameters::getParams(int argc, char* pArgv[])
{
  BX_ASSERT((argc && pArgv), "Missing arguments");

  Cont ret(cont);

  po::options_description all_parameters;

  all_parameters.add(_basicParams).add(_specificParams);
  
  po::store(po::parse_command_line(argc, pArgv, all_parameters), _parameter_map);

  po:notify(_parameter_map);

  if(_parameter_map.count("help"))
  {
    // Help message requested
    std::cout << pArgv[0] << std::endl;
    
    if(_helpMessage.size())
      std::cout << _helpMessage << std::endl;
      
    std::cout << all_parameters << std::endl;

    ret = stop;
  }
  else
  {
    if(_parameter_map.count("file"))
    {
      // Need to load the configuration from the file
      po::store(parse_config_file(_parameter_map["file"], ), _parameter_map);
      
      po:notify(_parameter_map);

      ret = cont;
    }
  }

  return ret;
}


