#include "zorba/system/zorba_version.h"

#include <string>
#include <sstream>

namespace xqp {

  int ZorbaVersion::theMajorVersion = @ZORBA_MAJOR_VERSION@;
  int ZorbaVersion::theMinorVersion = @ZORBA_MINOR_VERSION@;
  int ZorbaVersion::thePatchVersion = @ZORBA_PATCH_VERSION@;

  int
  ZorbaVersion::getZorbaMajorVersion() { return theMajorVersion; }

  int
  ZorbaVersion::getZorbaMinorVersion() { return theMinorVersion; }

  int
  ZorbaVersion::getZorbaPatchVersion() { return thePatchVersion; }

  std::string
  ZorbaVersion::getZorbaVersion() 
  {
    std::ostringstream lStream;
    lStream << getZorbaMajorVersion() << "." << getZorbaMinorVersion() << "." << getZorbaPatchVersion();
    return lStream.str();
  }

} /* end namespace xqp */

