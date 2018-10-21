
#include <string>
#include <iostream> 

#include "parameters.hpp"
#include "application.hpp"
#include "log.hpp"

using namespace Bx::Base;

namespace po = boost::program_options;

Parameters::Parameters():
_commonParams("Common command line and configuration file paramters"),
_comandLineParams("Comand line only parameters"),
_fileParams("Configuraiton file only parameters")
{
  std::string logLevelHelp = "log levels: " + Log::logLevelHelp();

  _commonParams.add_options()
     ("log-level,l", po::value<std::string>()->default_value(Log::defaultLogLevel().c_str()),
      logLevelHelp.c_str())
    ("log-output-file,o", po::value<std::string>(), "log file name")
    ;
    
  _comandLineParams.add_options()
    ("version,v", "application version information")
    ("help,h", "help information")
    ("configuration-file,f", po::value<std::string>(), "configuration file in INI format")
    ;
    
  _comandLineParams.add(_commonParams);

  _fileParams.add(_commonParams);
           
}

int 
Parameters::getParams(int argc, const char* pArgv[])
{
  BX_ASSERT((argc && pArgv), "Missing arguments");

  int ret(0);
   
  po::store(po::parse_command_line(argc, pArgv, _comandLineParams),
    _parameter_map);
 
  if(_parameter_map.count("help"))
  {
    // Help message requested
    std::cout << pArgv[0] << std::endl << std::endl;
    
    if(_helpMessage.size())
    {
      std::cout << _helpMessage << std::endl << std::endl;
    }
      
    std::cout << _comandLineParams << std::endl;

    ret = 1;
  }
  else if(_parameter_map.count("version"))
  {
    // Help message requested
    std::cout << "Application version information:"
      << Application::appInfo() << std::endl;
  }
  else
  {
    // Actually process the parameters
    po::notify(_parameter_map);
    
    // Read the parameters from file if file was specified
    if(_parameter_map.count("file"))
    {
      BX_LOG(LOG_INF, "Reading parameters from file '%s'",
        _parameter_map["file"].as<std::string>().c_str())
      
      // Need to load the configuration from the file
      std::ifstream fileName(_parameter_map["file"].as<std::string>().c_str());
      po::store(po::parse_config_file(fileName, _fileParams),
        _parameter_map);
      
      po::notify(_parameter_map);
    }
  }

  // Extract some parameters if available
  if( _parameter_map.count("log-level") )
  {
    _logLevel = _parameter_map["log-level"].as<std::string>();
  }

  if(_parameter_map.count("log-output-file"))
  {
    _logFile = _parameter_map["log-output-file"].as<std::string>();
  }
 
  return ret;
}

