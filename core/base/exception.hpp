#ifndef BX_EXCEPTION_HPP
#define BX_EXCEPTION_HPP

#include <iostream>
#include <exception>
#include <errno.h>


namespace Bx {
  namespace Base {

    class Exception: public std::exception
    {
      public:
        Exception(const char* pFileName, const int lineNum,
          const char* pFormat,...);
        
        Exception(const char* pFileName, const int lineNum,
          const int error, const char* pFormat,...);

        virtual const char* what();

      private:
        enum {
          header_size = 100,
          body_size = 200,
        };
      
        char _pMsg[header_size + body_size];

    };
  }
}


#define BX_EXCEPTION(ARGS...) \
  throw Bx::Base::Exception(__FILE__, __LINE__, ARGS);
  
#define BX_EXCEPTION_E(ARGS...) \
  throw Bx::Base::Exception(__FILE__, __LINE__, errno, ARGS);

#define BX_ASSERT(EXPRESSION, ARGS...) \
  if(!(EXPRESSION)) { BX_EXCEPTION (ARGS); }

#define BX_ASSERT_E(EXPRESSION, ARGS...) \
  if(!(EXPRESSION)) { BX_EXCEPTION_E (ARGS); } 



#endif
