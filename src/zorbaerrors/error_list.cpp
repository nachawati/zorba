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

#include <zorba/error_list.h>

namespace zorba {

#define XQUERY_DEF_ERROR(ERR) XQueryError ERR( #ERR )

namespace err {

////////// XQuery Errors //////////////////////////////////////////////////////

XQUERY_DEF_ERROR( XPST0001 );
XQUERY_DEF_ERROR( XPDY0002 );
XQUERY_DEF_ERROR( XPST0003 );
XQUERY_DEF_ERROR( XPTY0004 );
XQUERY_DEF_ERROR( XPST0005 );
XQUERY_DEF_ERROR( XPST0008 );
XQUERY_DEF_ERROR( XQST0009 );
XQUERY_DEF_ERROR( XQST0012 );
XQUERY_DEF_ERROR( XQST0013 );
XQUERY_DEF_ERROR( XPST0017 );
XQUERY_DEF_ERROR( XPTY0018 );
XQUERY_DEF_ERROR( XPTY0019 );
XQUERY_DEF_ERROR( XPTY0020 );
XQUERY_DEF_ERROR( XQST0022 );
XQUERY_DEF_ERROR( XQTY0024 );
XQUERY_DEF_ERROR( XQDY0025 );
XQUERY_DEF_ERROR( XQDY0026 );
XQUERY_DEF_ERROR( XQDY0027 );
XQUERY_DEF_ERROR( XQTY0030 );
XQUERY_DEF_ERROR( XQST0031 );
XQUERY_DEF_ERROR( XQST0032 );
XQUERY_DEF_ERROR( XQST0033 );
XQUERY_DEF_ERROR( XQST0034 );
XQUERY_DEF_ERROR( XQST0035 );
XQUERY_DEF_ERROR( XQST0036 );
XQUERY_DEF_ERROR( XQST0038 );
XQUERY_DEF_ERROR( XQST0039 );
XQUERY_DEF_ERROR( XQST0040 );
XQUERY_DEF_ERROR( XQDY0041 );
XQUERY_DEF_ERROR( XQDY0044 );
XQUERY_DEF_ERROR( XQST0045 );
XQUERY_DEF_ERROR( XQST0046 );
XQUERY_DEF_ERROR( XQST0047 );
XQUERY_DEF_ERROR( XQST0048 );
XQUERY_DEF_ERROR( XQST0049 );
XQUERY_DEF_ERROR( XPDY0050 );
XQUERY_DEF_ERROR( XPST0051 );
XQUERY_DEF_ERROR( XQST0054 );
XQUERY_DEF_ERROR( XQST0055 );
XQUERY_DEF_ERROR( XQST0057 );
XQUERY_DEF_ERROR( XQST0058 );
XQUERY_DEF_ERROR( XQST0059 );
XQUERY_DEF_ERROR( XQST0060 );
XQUERY_DEF_ERROR( XQDY0061 );
XQUERY_DEF_ERROR( XQDY0064 );
XQUERY_DEF_ERROR( XQST0065 );
XQUERY_DEF_ERROR( XQST0066 );
XQUERY_DEF_ERROR( XQST0067 );
XQUERY_DEF_ERROR( XQST0068 );
XQUERY_DEF_ERROR( XQST0069 );
XQUERY_DEF_ERROR( XQST0070 );
XQUERY_DEF_ERROR( XQST0071 );
XQUERY_DEF_ERROR( XQDY0072 );
XQUERY_DEF_ERROR( XQDY0074 );
XQUERY_DEF_ERROR( XQST0076 );
XQUERY_DEF_ERROR( XQST0079 );
XQUERY_DEF_ERROR( XPST0080 );
XQUERY_DEF_ERROR( XPST0081 );
XQUERY_DEF_ERROR( XPST0083 );
XQUERY_DEF_ERROR( XQDY0084 );
XQUERY_DEF_ERROR( XQST0085 );
XQUERY_DEF_ERROR( XQTY0086 );
XQUERY_DEF_ERROR( XQST0087 );
XQUERY_DEF_ERROR( XQST0088 );
XQUERY_DEF_ERROR( XQST0089 );
XQUERY_DEF_ERROR( XQST0090 );
XQUERY_DEF_ERROR( XQDY0091 );
XQUERY_DEF_ERROR( XQDY0092 );
XQUERY_DEF_ERROR( XQST0093 );
XQUERY_DEF_ERROR( XQDY0096 );
XQUERY_DEF_ERROR( XQST0098 );
XQUERY_DEF_ERROR( XQST0106 );
XQUERY_DEF_ERROR( XQST0111 );
XQUERY_DEF_ERROR( XTDE1310 );
XQUERY_DEF_ERROR( XTDE1340 );
XQUERY_DEF_ERROR( XTDE1350 );

////////// XQuery Functions & Operators Errors ////////////////////////////////

XQUERY_DEF_ERROR( FOER0000 );
XQUERY_DEF_ERROR( FOAR0001 );
XQUERY_DEF_ERROR( FOAR0002 );
XQUERY_DEF_ERROR( FOCA0001 );
XQUERY_DEF_ERROR( FOCA0002 );
XQUERY_DEF_ERROR( FOCA0003 );
XQUERY_DEF_ERROR( FOCA0005 );
XQUERY_DEF_ERROR( FOCA0006 );
XQUERY_DEF_ERROR( FOCH0001 );
XQUERY_DEF_ERROR( FOCH0002 );
XQUERY_DEF_ERROR( FOCH0003 );
XQUERY_DEF_ERROR( FOCH0004 );
XQUERY_DEF_ERROR( FODC0001 );
XQUERY_DEF_ERROR( FODC0002 );
XQUERY_DEF_ERROR( FODC0003 );
XQUERY_DEF_ERROR( FODC0004 );
XQUERY_DEF_ERROR( FODC0005 );
XQUERY_DEF_ERROR( FODC0006 );
XQUERY_DEF_ERROR( FODC0007 );
XQUERY_DEF_ERROR( FODF1280 );
XQUERY_DEF_ERROR( FODF1310 );
XQUERY_DEF_ERROR( FODT0001 );
XQUERY_DEF_ERROR( FODT0002 );
XQUERY_DEF_ERROR( FODT0003 );
XQUERY_DEF_ERROR( FOFI0001 );
XQUERY_DEF_ERROR( FOFI0002 );
XQUERY_DEF_ERROR( FONS0004 );
XQUERY_DEF_ERROR( FONS0005 );
XQUERY_DEF_ERROR( FORG0001 );
XQUERY_DEF_ERROR( FORG0002 );
XQUERY_DEF_ERROR( FORG0003 );
XQUERY_DEF_ERROR( FORG0004 );
XQUERY_DEF_ERROR( FORG0005 );
XQUERY_DEF_ERROR( FORG0006 );
XQUERY_DEF_ERROR( FORG0008 );
XQUERY_DEF_ERROR( FORG0009 );
XQUERY_DEF_ERROR( FORX0001 );
XQUERY_DEF_ERROR( FORX0002 );
XQUERY_DEF_ERROR( FORX0003 );
XQUERY_DEF_ERROR( FORX0004 );
XQUERY_DEF_ERROR( FOTY0012 );
XQUERY_DEF_ERROR( FOTY0013 );
XQUERY_DEF_ERROR( FOTY0014 );
XQUERY_DEF_ERROR( FOTY0015 );

////////// XQuery Full-Text Errors ////////////////////////////////////////////

#ifndef ZORBA_NO_FULL_TEXT
XQUERY_DEF_ERROR( FTST0008 );
XQUERY_DEF_ERROR( FTST0009 );
XQUERY_DEF_ERROR( FTDY0016 );
XQUERY_DEF_ERROR( FTDY0017 );
XQUERY_DEF_ERROR( FTST0018 );
XQUERY_DEF_ERROR( FTST0019 );
XQUERY_DEF_ERROR( FTDY0020 );
#endif /* ZORBA_NO_FULL_TEXT */

////////// XQuery Scripting ///////////////////////////////////////////////////

XQUERY_DEF_ERROR( XSST0001 );
XQUERY_DEF_ERROR( XSST0002 );
XQUERY_DEF_ERROR( XSST0003 );
XQUERY_DEF_ERROR( XSST0004 );
XQUERY_DEF_ERROR( XSST0005 );
XQUERY_DEF_ERROR( XSST0006 );
XQUERY_DEF_ERROR( XSST0007 );
XQUERY_DEF_ERROR( XSST0008 );

////////// XQuery Update Facility /////////////////////////////////////////////

XQUERY_DEF_ERROR( XUST0001 );
XQUERY_DEF_ERROR( XUST0002 );
XQUERY_DEF_ERROR( XUST0003 );
XQUERY_DEF_ERROR( XUTY0004 );
XQUERY_DEF_ERROR( XUTY0005 );
XQUERY_DEF_ERROR( XUTY0006 );
XQUERY_DEF_ERROR( XUTY0007 );
XQUERY_DEF_ERROR( XUTY0008 );
XQUERY_DEF_ERROR( XUDY0009 );
XQUERY_DEF_ERROR( XUTY0010 );
XQUERY_DEF_ERROR( XUTY0011 );
XQUERY_DEF_ERROR( XUTY0012 );
XQUERY_DEF_ERROR( XUTY0013 );
XQUERY_DEF_ERROR( XUDY0014 );
XQUERY_DEF_ERROR( XUDY0015 );
XQUERY_DEF_ERROR( XUDY0016 );
XQUERY_DEF_ERROR( XUDY0017 );
XQUERY_DEF_ERROR( XUDY0018 );
XQUERY_DEF_ERROR( XUDY0019 );
XQUERY_DEF_ERROR( XUDY0021 );
XQUERY_DEF_ERROR( XUTY0022 );
XQUERY_DEF_ERROR( XUDY0023 );
XQUERY_DEF_ERROR( XUDY0024 );
XQUERY_DEF_ERROR( XUDY0027 );
XQUERY_DEF_ERROR( XUST0028 );
XQUERY_DEF_ERROR( XUDY0029 );
XQUERY_DEF_ERROR( XUDY0030 );
XQUERY_DEF_ERROR( XUDY0031 );
XQUERY_DEF_ERROR( FOUP0001 );
XQUERY_DEF_ERROR( FOUP0002 );

////////// Serialization //////////////////////////////////////////////////////

XQUERY_DEF_ERROR( SENR0001 );
XQUERY_DEF_ERROR( SERE0003 );
XQUERY_DEF_ERROR( SEPM0004 );
XQUERY_DEF_ERROR( SERE0005 );
XQUERY_DEF_ERROR( SERE0006 );
XQUERY_DEF_ERROR( SESU0007 );
XQUERY_DEF_ERROR( SERE0008 );
XQUERY_DEF_ERROR( SEPM0009 );
XQUERY_DEF_ERROR( SEPM0010 );
XQUERY_DEF_ERROR( SESU0011 );
XQUERY_DEF_ERROR( SERE0012 );
XQUERY_DEF_ERROR( SESU0013 );
XQUERY_DEF_ERROR( SERE0014 );
XQUERY_DEF_ERROR( SERE0015 );
XQUERY_DEF_ERROR( SEPM0016 );

///////////////////////////////////////////////////////////////////////////////

} // namespace err

namespace zerr {

#define ZORBA_DEF_ERROR(QNAME,ERR) ZorbaError QNAME##_##ERR( #QNAME )

////////// Zorba API Errors ///////////////////////////////////////////////////

ZORBA_DEF_ERROR( ZAPI0002,XQUERY_COMPILATION_FAILED );
ZORBA_DEF_ERROR( ZAPI0003,XQUERY_NOT_COMPILED );
ZORBA_DEF_ERROR( ZAPI0004,XQUERY_ALREADY_COMPILED );
ZORBA_DEF_ERROR( ZAPI0005,XQUERY_ALREADY_EXECUTING );
ZORBA_DEF_ERROR( ZAPI0006,XQUERY_ALREADY_CLOSED );
ZORBA_DEF_ERROR( ZAPI0007,CANNOT_SERIALIZE_PUL );
ZORBA_DEF_ERROR( ZAPI0008,NOT_AN_UPDATE_XQUERY );
ZORBA_DEF_ERROR( ZAPI0009,XQUERY_NOT_COMPILED_IN_DEBUG_MODE );
ZORBA_DEF_ERROR( ZAPI0014,INVALID_ARGUMENT );
ZORBA_DEF_ERROR( ZAPI0015,CREATEMODULE_NOT_FOUND );
ZORBA_DEF_ERROR( ZAPI0019,MODULE_ALREADY_REGISTERED );
ZORBA_DEF_ERROR( ZAPI0020,DOCUMENT_ALREADY_EXISTS );
ZORBA_DEF_ERROR( ZAPI0021,ITEM_TO_LOAD_IS_NOT_NODE );
ZORBA_DEF_ERROR( ZAPI0027,CANNOT_UPDATE_DCTX_WITH_ITERATORS );
ZORBA_DEF_ERROR( ZAPI0028,INVALID_NODE_URI );
ZORBA_DEF_ERROR( ZAPI0039,XQUERY_HAS_ITERATOR_ALREADY );
ZORBA_DEF_ERROR( ZAPI0040,ITERATOR_NOT_OPEN );
ZORBA_DEF_ERROR( ZAPI0041,ITERATOR_ALREADY_OPEN );
ZORBA_DEF_ERROR( ZAPI0042,ITERATOR_CLOSED );
ZORBA_DEF_ERROR( ZAPI0051,REST_ERROR_PAYLOAD );
ZORBA_DEF_ERROR( ZAPI0070,INVALID_SERIALIZATION_METHOD_FOR_SAX );

////////// Zorba Class Serialization Errors ///////////////////////////////////

ZORBA_DEF_ERROR( ZCSE0001,NONEXISTENT_INPUT_FIELD );
ZORBA_DEF_ERROR( ZCSE0002,INCOMPATIBLE_INPUT_FIELD );
ZORBA_DEF_ERROR( ZCSE0003,UNRECOGNIZED_CLASS_FIELD );
ZORBA_DEF_ERROR( ZCSE0004,UNRESOLVED_FIELD_REFERENCE );
ZORBA_DEF_ERROR( ZCSE0005,CLASS_VERSION_TOO_NEW );
ZORBA_DEF_ERROR( ZCSE0006,CLASS_VERSION_TOO_OLD );
ZORBA_DEF_ERROR( ZCSE0007,INPUT_ARCHIVE_USED_FOR_OUT_SERIALIZATION );
ZORBA_DEF_ERROR( ZCSE0008,OUTPUT_ARCHIVE_USED_FOR_IN_SERIALIZATION );
ZORBA_DEF_ERROR( ZCSE0009,CLASS_NOT_SERIALIZABLE );
ZORBA_DEF_ERROR( ZCSE0010,ITEM_TYPE_NOT_SERIALIZABLE );
ZORBA_DEF_ERROR( ZCSE0011,INPUT_ARCHIVE_NOT_ZORBA_ARCHIVE );
ZORBA_DEF_ERROR( ZCSE0012,INCOMPATIBLE_ARCHIVE_VERSION );
ZORBA_DEF_ERROR( ZCSE0013,UNABLE_TO_LOAD_QUERY );
ZORBA_DEF_ERROR( ZCSE0014,INFINITE_CIRCULAR_DEPENDENCIES );
ZORBA_DEF_ERROR( ZCSE0015,INCOMPATIBLE_BETWEEN_32_AND_64_BITS_OR_LE_AND_BE );
ZORBA_DEF_ERROR( ZCSE0016,CANNOT_LOAD_FROM_RELEASE_TO_DEBUG );
ZORBA_DEF_ERROR( ZCSE0017,CANNOT_LOAD_FROM_DEBUG_TO_RELEASE );

////////// Zorba Data Definition Facility Errors //////////////////////////////

ZORBA_DEF_ERROR( ZDDY0001,COLLECTION_NOT_DECLARED );
ZORBA_DEF_ERROR( ZDDY0002,COLLECTION_ALREADY_EXISTS );
ZORBA_DEF_ERROR( ZDDY0003,COLLECTION_DOES_NOT_EXIST );
ZORBA_DEF_ERROR( ZDDY0004,COLLECTION_CONST_UPDATE );
ZORBA_DEF_ERROR( ZDDY0005,COLLECTION_APPEND_BAD_INSERT );
ZORBA_DEF_ERROR( ZDDY0006,COLLECTION_QUEUE_BAD_INSERT );
ZORBA_DEF_ERROR( ZDDY0007,COLLECTION_APPEND_BAD_DELETE );
ZORBA_DEF_ERROR( ZDDY0008,COLLECTION_QUEUE_BAD_DELETE );
ZORBA_DEF_ERROR( ZDDY0009,COLLECTION_QUEUE_BAD_DELETE );
ZORBA_DEF_ERROR( ZDDY0010,COLLECTION_CONST_NODE_UPDATE );
ZORBA_DEF_ERROR( ZDDY0011,COLLECTION_NODE_NOT_FOUND );
ZORBA_DEF_ERROR( ZDDY0012,COLLECTION_UNORDERED_BAD_INSERT );
ZORBA_DEF_ERROR( ZDDY0013,COLLECTION_BAD_DESTROY_INDEXES );
ZORBA_DEF_ERROR( ZDDY0014,COLLECTION_BAD_DESTROY_ICS );
ZORBA_DEF_ERROR( ZDDY0015,COLLECTION_BAD_DESTROY_NODES );
ZORBA_DEF_ERROR( ZDDY0016,COLLECTION_MULTIPLE_CREATES );
ZORBA_DEF_ERROR( ZDDY0017,NODE_IS_ORPHAN );
ZORBA_DEF_ERROR( ZDDY0018,NODES_NOT_IN_SAME_COLLECTION );
ZORBA_DEF_ERROR( ZDDY0020,INDEX_DOMAIN_NODE_NOT_IN_COLLECTION );
ZORBA_DEF_ERROR( ZDDY0021,INDEX_NOT_DECLARED );
ZORBA_DEF_ERROR( ZDDY0022,INDEX_ALREADY_EXISTS );
ZORBA_DEF_ERROR( ZDDY0023,INDEX_DOES_NOT_EXIST );
ZORBA_DEF_ERROR( ZDDY0024,INDEX_UNIQUE_VIOLATION );
ZORBA_DEF_ERROR( ZDDY0025,INDEX_WRONG_NUMBER_OF_PROBE_ARGS );
ZORBA_DEF_ERROR( ZDDY0026,INDEX_RANGE_PROBE_NOT_ALLOWED );
ZORBA_DEF_ERROR( ZDDY0027,INDEX_MULTIPLE_CREATES );
ZORBA_DEF_ERROR( ZDDY0028,INDEX_DOMAIN_HAS_DUPLICATE_NODES );
ZORBA_DEF_ERROR( ZDDY0029,INDEX_GENERAL_PROBE_NOT_ALLOWED );
ZORBA_DEF_ERROR( ZDDY0031,IC_NOT_DECLARED );
ZORBA_DEF_ERROR( ZDDY0032,IC_NOT_ACTIVATED );
ZORBA_DEF_ERROR( ZDDY0033,IC_NOT_MET );

ZORBA_DEF_ERROR( ZDST0001,COLLECTION_ALREADY_DECLARED );
ZORBA_DEF_ERROR( ZDST0002,COLLECTION_ALREADY_IMPORTED );
ZORBA_DEF_ERROR( ZDST0003,COLLECTION_DECL_IN_MAIN_MODULE );
ZORBA_DEF_ERROR( ZDST0004,COLLECTION_MULTIPLE_PROPERTY_VALUES );
ZORBA_DEF_ERROR( ZDST0005,COLLECTION_PROPERTIES_CONFLICT );
ZORBA_DEF_ERROR( ZDST0006,COLLECTION_INVALID_PROPERTY_VALUE );
ZORBA_DEF_ERROR( ZDST0007,COLLECTION_DECL_IN_FOREIGN_MODULE );
ZORBA_DEF_ERROR( ZDST0021,INDEX_ALREADY_DECLARED );
ZORBA_DEF_ERROR( ZDST0022,INDEX_ALREADY_IMPORTED );
ZORBA_DEF_ERROR( ZDST0023,INDEX_DECL_IN_MAIN_MODULE );
ZORBA_DEF_ERROR( ZDST0024,INDEX_MULTIPLE_PROPERTY_VALUES );
ZORBA_DEF_ERROR( ZDST0026,INDEX_INVALID_PROPERTY_VALUE );
ZORBA_DEF_ERROR( ZDST0027,INDEX_BAD_KEY_TYPE );
ZORBA_DEF_ERROR( ZDST0028,INDEX_NOT_DETERMINISTIC );
ZORBA_DEF_ERROR( ZDST0029,INDEX_INVALID_DATA_SOURCE );
ZORBA_DEF_ERROR( ZDST0030,INDEX_NON_CONST_DATA_SOURCE );
ZORBA_DEF_ERROR( ZDST0031,INDEX_HAS_FREE_VARS );
ZORBA_DEF_ERROR( ZDST0032,INDEX_REFERENCES_CTX_ITEM );
ZORBA_DEF_ERROR( ZDST0033,INDEX_NON_SIMPLE_EXPR );
ZORBA_DEF_ERROR( ZDST0034,INDEX_CANNOT_DO_AUTOMATIC_MAINTENANCE );
ZORBA_DEF_ERROR( ZDST0035,INDEX_GENERAL_MULTIKEY );
ZORBA_DEF_ERROR( ZDST0036,INDEX_DECL_IN_FOREIGN_MODULE );
ZORBA_DEF_ERROR( ZDST0041,IC_ALREADY_DECLARED );
ZORBA_DEF_ERROR( ZDST0044,IC_DECL_IN_MAIN_MODULE );
ZORBA_DEF_ERROR( ZDST0048,IC_DECL_IN_FOREIGN_MODULE );

ZORBA_DEF_ERROR( ZDTY0001,COLLECTION_INVALID_NODE_TYPE );
ZORBA_DEF_ERROR( ZDTY0010,INDEX_DOMAIN_TYPE_ERROR );
ZORBA_DEF_ERROR( ZDTY0011,INDEX_KEY_TYPE_ERROR );
ZORBA_DEF_ERROR( ZDTY0012,INDEX_KEY_TYPE_ERROR );

////////// Zorba Operating System Errors //////////////////////////////////////

ZORBA_DEF_ERROR( ZOSE0001,FILE_NOT_FOUND );
ZORBA_DEF_ERROR( ZOSE0002,NOT_PLAIN_FILE );
ZORBA_DEF_ERROR( ZOSE0003,STREAM_READ_FAILURE );
ZORBA_DEF_ERROR( ZOSE0004,IO_ERROR );

////////// Zorba Store Errors /////////////////////////////////////////////////

ZORBA_DEF_ERROR( ZSTR0001,INDEX_ALREADY_EXISTS );
ZORBA_DEF_ERROR( ZSTR0002,INDEX_DOES_NOT_EXIST );
ZORBA_DEF_ERROR( ZSTR0003,INDEX_PARTIAL_KEY_INSERT );
ZORBA_DEF_ERROR( ZSTR0004,INDEX_PARTIAL_KEY_REMOVE );
ZORBA_DEF_ERROR( ZSTR0005,INDEX_PARTIAL_KEY_PROBE );
ZORBA_DEF_ERROR( ZSTR0006,INDEX_INVALID_BOX_PROBE );
ZORBA_DEF_ERROR( ZSTR0007,INDEX_UNSUPPORTED_PROBE_CONDITION );
ZORBA_DEF_ERROR( ZSTR0008,COLLECTION_ALREADY_EXISTS );
ZORBA_DEF_ERROR( ZSTR0009,COLLECTION_NOT_FOUND );
ZORBA_DEF_ERROR( ZSTR0010,COLLECTION_NODE_ALREADY_IN_COLLECTION );
ZORBA_DEF_ERROR( ZSTR0011,COLLECTION_NON_ROOT_NODE );
ZORBA_DEF_ERROR( ZSTR0012,COLLECTION_ITEM_MUST_BE_A_NODE );
ZORBA_DEF_ERROR( ZSTR0015,IC_ALREADY_EXISTS );
ZORBA_DEF_ERROR( ZSTR0016,IC_DOES_NOT_EXIST );
ZORBA_DEF_ERROR( ZSTR0020,LOADER_IO_ERROR );
ZORBA_DEF_ERROR( ZSTR0021,LOADER_PARSING_ERROR );
ZORBA_DEF_ERROR( ZSTR0030,NODEID_ERROR );
ZORBA_DEF_ERROR( ZSTR0040,TYPE_ERROR );
ZORBA_DEF_ERROR( ZSTR0041,NAN_COMPARISON );
ZORBA_DEF_ERROR( ZSTR0045,DUPLICATE_NODE_ERROR );
ZORBA_DEF_ERROR( ZSTR0050,FUNCTION_NOT_IMPLEMENTED_FOR_ITEMTYPE );
ZORBA_DEF_ERROR( ZSTR0055,STREAMABLE_STRING_CONSUMED );

////////// Zorba XQuery Processor Errors //////////////////////////////////////

ZORBA_DEF_ERROR( ZXQP0000,NO_ERROR );
ZORBA_DEF_ERROR( ZXQP0001,DYNAMIC_RUNTIME_ERROR );
ZORBA_DEF_ERROR( ZXQP0005,NOT_SUPPORTED );
ZORBA_DEF_ERROR( ZXQP0006,ASSERT_FAILED );
ZORBA_DEF_ERROR( ZXQP0007,FUNCTION_SIGNATURE_NOT_EQUAL );
ZORBA_DEF_ERROR( ZXQP0008,FUNCTION_IMPL_NOT_FOUND );
ZORBA_DEF_ERROR( ZXQP0009,FUNCTION_LOCALNAME_MISMATCH );
ZORBA_DEF_ERROR( ZXQP0013,FXCHARHEAP_EXCEPTION );
ZORBA_DEF_ERROR( ZXQP0015,NOT_IMPLEMENTED );
ZORBA_DEF_ERROR( ZXQP0016,RESERVED_MODULE_TARGET_NAMESPACE );
ZORBA_DEF_ERROR( ZXQP0017,FILE_ACCESS_DISABLED );
ZORBA_DEF_ERROR( ZXQP0019,INTERNAL_ERROR );
ZORBA_DEF_ERROR( ZXQP0020,INVALID_URI );
ZORBA_DEF_ERROR( ZXQP0021,USER_ERROR );
ZORBA_DEF_ERROR( ZXQP0024,XML_DOES_NOT_MATCH_SCHEMA );
ZORBA_DEF_ERROR( ZXQP0025,ITEM_CREATION_FAILED );
ZORBA_DEF_ERROR( ZXQP0027,MS_DOM_ERROR );
ZORBA_DEF_ERROR( ZXQP0028,TARGET_NAMESPACE_NOT_PROVIDED );
ZORBA_DEF_ERROR( ZXQP0029,MODULE_IMPORT_NOT_ALLOWED );
ZORBA_DEF_ERROR( ZXQP0030,DEADLOCK );
ZORBA_DEF_ERROR( ZXQP0031,MALFORMED_XQUERYX_INPUT );
ZORBA_DEF_ERROR( ZXQP0032,ERROR_TRANSFORMING_XQUERYX_TO_XQUERY );
ZORBA_DEF_ERROR( ZXQP0036,BREAKITERATOR_CREATION_FAILED );

#ifndef ZORBA_NO_FULL_TEXT
ZORBA_DEF_ERROR( ZXQP8401,THESAURUS_VERSION_MISMATCH );
ZORBA_DEF_ERROR( ZXQP8402,THESAURUS_DATA_ERROR );
#endif /* ZORBA_NO_FULL_TEXT */

ZORBA_DEF_ERROR( ZXQD0001,PREFIX_NOT_DECLARED );
ZORBA_DEF_ERROR( ZXQD0002,DOCUMENT_NOT_VALID );

///////////////////////////////////////////////////////////////////////////////

} // namespace zerr
} // namespace zorba
/* vim:set et sw=2 ts=2: */
