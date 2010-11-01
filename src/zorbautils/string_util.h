/*
 * Copyright 2006-2008 The FLWOR Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ZORBA_UTILS_STRING_UTIL_H
#define ZORBA_UTILS_STRING_UTIL_H

#include <cstring>

#include "zorbatypes/collation_manager.h"
#include "zorbatypes/zorbatypesError.h"

#include "util/unicode_util.h"
#include "util/utf8_util.h"

namespace zorba {

////////// find with collation ////////////////////////////////////////////////

ulong find( char const *s, size_t s_len, char const *ss, size_t ss_len,
            XQPCollator const *collator );

ulong rfind( char const *s, size_t s_len, char const *ss, size_t ss_len,
             XQPCollator const *collator );

inline ulong find( char const *s, char const *ss,
                   XQPCollator const *collator ) {
  return find( s, std::strlen( s ), ss, std::strlen( ss ), collator );
}

template<class StringType,class SubstringType> inline
ulong find( StringType const &s, SubstringType const &ss,
           XQPCollator const *collator ) {
  return find( s.c_str(), s.size(), ss.c_str(), ss.size(), collator );
}

template<class StringType> inline
ulong find( StringType const &s, char const *ss, XQPCollator const *collator ) {
  return find( s.c_str(), s.size(), ss, std::strlen( ss ), collator );
}

template<class SubstringType> inline
ulong find( char const *s, SubstringType const &ss,
            XQPCollator const *collator ) {
  return find( s, std::strlen( s ), ss.c_str(), ss.size(), collator );
}

////////// ends with //////////////////////////////////////////////////////////

template<class StringType, class SubstringType> inline
bool ends_with(
    const StringType& s,
    const SubstringType& suffix,
    XQPCollator const* collator)
{
  ulong pos = rfind(s.c_str(), s.size(), suffix.c_str(), suffix.size(), collator);

  return (pos != StringType::npos &&
          (pos + utf8::length(suffix.c_str()) == utf8::length(s.c_str())));
}

////////// regular expression matching ////////////////////////////////////////

bool match_part( char const *in, char const *pattern, char const *flags );

template<class InputStringType> inline
bool match_part( InputStringType const &in, char const *pattern,
                 char const *flags ) {
  return match_part( in.c_str(), pattern, flags );
}

template<class InputStringType,class PatternStringType> inline
bool match_part( InputStringType const &in, PatternStringType const &pattern,
                 char const *flags ) {
  return match_part( in.c_str(), pattern.c_str(), flags );
}

bool match_whole( char const *in, char const *pattern, char const *flags );

template<class InputStringType> inline
bool match_whole( InputStringType const &in, char const *pattern,
                  char const *flags ) {
  return match_whole( in.c_str(), pattern, flags );
}

template<class InputStringType,class PatternStringType> inline
bool match_whole( InputStringType const &in, PatternStringType const &pattern,
                  char const *flags ) {
  return match_whole( in.c_str(), pattern.c_str(), flags );
}

////////// regular expression replacement /////////////////////////////////////

namespace utf8 {

/**
 * Replaces all occurrences of a substring that matches the given regular
 * expression pattern.
 *
 * @tparam OutputStringType The output string type.
 * @param in The input string encoded in UTF-8.
 * @param pattern The regular expression pattern encoded in UTF-8.
 * @param flags The regular expression flags.
 * @param replacement The replacement string encoded in UTF-8.
 * @param out The output string.
 * @return Returns \c true only if the replacement and conversion to UTF-8
 * succeeded.
 */
template<class OutputStringType>
bool replace_all( char const *in, char const *pattern, char const *flags,
                  char const *replacement, OutputStringType *out ) {
  unicode::regex re;
  if ( !re.compile( pattern, flags ) )
    throw zorbatypesException( pattern, ZorbatypesError::FORX0002 );
  unicode::string u_out;
  return  re.replace_all( in, replacement, &u_out ) &&
          utf8::to_string( u_out.getBuffer(), u_out.length(), out );
}

/**
 * Replaces all occurrences of a substring that matches the given regular
 * expression pattern.
 *
 * @tparam InputStringType The input string type.
 * @tparam ReplacementStringType The replacement string type.
 * @tparam OutputStringType The output string type.
 * @param in The input string encoded in UTF-8.
 * @param pattern The regular expression pattern encoded in UTF-8.
 * @param flags The regular expression flags.
 * @param replacement The replacement string encoded in UTF-8.
 * @param out The output string.  It may be the same as the input string.
 * @return Returns \c true only if the replacement and conversion to UTF-8
 * succeeded.
 */
template<
  class InputStringType,
  class ReplacementStringType,
  class OutputStringType
>
bool replace_all( InputStringType const &in, char const *pattern,
                  char const *flags, ReplacementStringType const &replacement, 
                  OutputStringType *out ) {
  unicode::regex re;
  if ( !re.compile( pattern, flags ) )
    throw zorbatypesException( pattern, ZorbatypesError::FORX0002 );
  unicode::string u_out;
  return  re.replace_all( in, replacement, &u_out ) &&
          utf8::to_string( u_out.getBuffer(), u_out.length(), out );
}

/**
 * Replaces all occurrences of a substring that matches the given regular
 * expression pattern.
 *
 * @tparam InputStringType The input string type.
 * @tparam PatternStringType The pattern string type.
 * @tparam ReplacementStringType The replacement string type.
 * @tparam OutputStringType The output string type.
 * @param in The input string encoded in UTF-8.
 * @param pattern The regular expression pattern encoded in UTF-8.
 * @param flags The regular expression flags.
 * @param replacement The replacement string encoded in UTF-8.
 * @param out The output string.  It may be the same as the input string.
 * @return Returns \c true only if the replacement and conversion to UTF-8
 * succeeded.
 */
template<
  class InputStringType,
  class PatternStringType,
  class ReplacementStringType,
  class OutputStringType
>
bool replace_all( InputStringType const &in, PatternStringType const &pattern,
                  char const *flags, ReplacementStringType const &replacement,
                  OutputStringType *out ) {
  unicode::regex re;
  if ( !re.compile( pattern, flags ) )
    throw zorbatypesException( pattern.c_str(), ZorbatypesError::FORX0002 );
  unicode::string u_out;
  return  re.replace_all( in, replacement, &u_out ) &&
          utf8::to_string( u_out.getBuffer(), u_out.length(), out );
}

} // namespace utf8

} // namespace zorba
#endif  /* ZORBA_UTILS_STRING_UTIL_H */

/*
 * Local variables:
 * mode: c++
 * End:
 */
/* vim:set et sw=2 ts=2: */