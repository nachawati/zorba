#include <iostream>
#include "system/globalenv.h"
#include "types/typeconstants.h"
#include "types/typeimpl.h"
#include "types/root_typemanager.h"

namespace xqp {

const char *XQType::KIND_STRINGS[XQType::NONE_KIND + 1] =
{
  "ATOMIC_TYPE_KIND",
  "NODE_TYPE_KIND",
  "ANY_TYPE_KIND",
  "ITEM_KIND",
  "ANY_SIMPLE_TYPE_KIND",
  "UNTYPED_KIND",
  "EMPTY_KIND",
  "NONE_KIND"
};

const char *AtomicXQType::ATOMIC_TYPE_CODE_STRINGS[TypeConstants::ATOMIC_TYPE_CODE_LIST_SIZE] =
{
  "XS_ANY_ATOMIC",
  "XS_STRING",
  "XS_NORMALIZED_STRING",
  "XS_TOKEN",
  "XS_LANGUAGE",
  "XS_NMTOKEN",
  "XS_NAME",
  "XS_NCNAME",
  "XS_ID",
  "XS_IDREF",
  "XS_ENTITY",
  "XS_UNTYPED_ATOMIC",
  "XS_DATETIME",
  "XS_DATE",
  "XS_TIME",
  "XS_DURATION",
  "XS_DT_DURATION",
  "XS_YM_DURATION",
  "XS_FLOAT",
  "XS_DOUBLE",
  "XS_DECIMAL",
  "XS_INTEGER",
  "XS_NON_POSITIVE_INTEGER",
  "XS_NEGATIVE_INTEGER",
  "XS_LONG",
  "XS_INT",
  "XS_SHORT",
  "XS_BYTE",
  "XS_NON_NEGATIVE_INTEGER",
  "XS_UNSIGNED_LONG",
  "XS_UNSIGNED_INT",
  "XS_UNSIGNED_SHORT",
  "XS_UNSIGNED_BYTE",
  "XS_POSITIVE_INTEGER",
  "XS_GYEAR_MONTH",
  "XS_GYEAR",
  "XS_GMONTH_DAY",
  "XS_GDAY",
  "XS_GMONTH",
  "XS_BOOLEAN",
  "XS_BASE64BINARY",
  "XS_HEXBINARY",
  "XS_ANY_URI",
  "XS_QNAME",
  "XS_NOTATION"
};

static inline const char *decode_quantifier (TypeConstants::quantifier_t quant) {
  switch (quant) {
  case TypeConstants::QUANT_ONE:
    return "";
  case TypeConstants::QUANT_QUESTION:
    return "?";
  case TypeConstants::QUANT_STAR:
    return "*";
  case TypeConstants::QUANT_PLUS:
    return "+";
  default:
    return "<unknown-quant>";
  }
}

std::ostream& XQType::serialize(std::ostream& os) const
{
  return os << "[XQType " << KIND_STRINGS[type_kind()] << decode_quantifier (GENV_TYPESYSTEM.quantifier (*this)) << "]";
}


std::string XQType::toString() const
{
  std::ostringstream os;
  serialize(os);
  return os.str();
}

std::ostream& AtomicXQType::serialize(std::ostream& os) const
{
  return os << "[AtomicXQType " << ATOMIC_TYPE_CODE_STRINGS[get_type_code()] << decode_quantifier (GENV_TYPESYSTEM.quantifier (*this)) << "]";
}

NodeXQType::NodeXQType(
    rchandle<NodeTest> nodetest,
    xqtref_t content_type,
    TypeConstants::quantifier_t quantifier)
  :
  XQType(quantifier), m_nodetest(nodetest), m_content_type(content_type)
{
}

}
