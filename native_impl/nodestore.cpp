/* -*- mode: c++; indent-tabs-mode: nil -*-
 *
 *  $Id: nodestore.cpp,v 1.1 2006/10/09 07:07:59 Paul Pedersen Exp $
 *
 *	Copyright 2006-2007 FLWOR Foundation.
 *
 *  Author: Paul Pedersen
 *
 */

#include "nodestore.h"

#include "../context/context.h"
#include "../runtime/iterator.h"
#include "../util/rchandle.h"
#include "../values/node_values.h"

#include <string>

using namespace std;
namespace xqp {

nodestore::nodestore(
	string const& path)
:
	store_p(new fxvector<char>(path+"/store")),
	index_p(new fxhash64map<off_t>(path+"/idx_"))
{
}
 
nodestore::~nodestore()
{
}

/*...........................................
	: node store                              :
	:.........................................:
*/

/*
off_t nodestore::put(
	context * ctx_p,
	item_iterator & it)
{
	off_t res = *store_p->offset_p;
	for (; !it.done(); ++it) {
		rchandle<item> i_h = *it;
		node* n_p = dynamic_cast<node*>(&*i_h);
		if (n_p==NULL) continue;	//log error
		put(ctx_p, n_p);
	}
	return res;
}
*/


/*...........................................
	: integers                                :
	:.........................................:
*/

void nodestore::put(
	context * ctx_p,
	uint16_t key)
{
	char g = key>>8 & 0xff;
	char h = key    & 0xff;
	store_p->push_back(g);
	store_p->push_back(h);
}

int nodestore::get(
	context * ctx_p,
	off_t offset0,
	uint16_t & v)
{
	off_t offset = offset0;
	uint16_t g = (uint16_t)store_p->operator[](offset++) << 8;
	uint16_t h = (uint16_t)store_p->operator[](offset++);
	v = g|h;
	return 2;
}

void nodestore::put(
	context * ctx_p,
	uint32_t key)
{
	char e = key>>24 & 0xff;
	char f = key>>16 & 0xff;
	char g = key>>8  & 0xff;
	char h = key     & 0xff;
	store_p->push_back(e);
	store_p->push_back(f);
	store_p->push_back(g);
	store_p->push_back(h);
}

int nodestore::get(
	context * ctx_p,
	off_t offset0,
	uint32_t & v)
{
	off_t offset = offset0;
	uint32_t e = (uint32_t)store_p->operator[](offset++) << 24;
	uint32_t f = (uint32_t)store_p->operator[](offset++) << 16;
	uint32_t g = (uint32_t)store_p->operator[](offset++) << 8;
	uint32_t h = (uint32_t)store_p->operator[](offset++);
	v = e|f|g|h;
	return 4;
}

void nodestore::put(
	context * ctx_p,
	uint64_t key)
{
	char a = key>>56 & 0xff;
	char b = key>>48 & 0xff;
	char c = key>>40 & 0xff;
	char d = key>>32 & 0xff;
	char e = key>>24 & 0xff;
	char f = key>>16 & 0xff;
	char g = key>>8  & 0xff;
	char h = key     & 0xff;
	store_p->push_back(a);
	store_p->push_back(b);
	store_p->push_back(c);
	store_p->push_back(d);
	store_p->push_back(e);
	store_p->push_back(f);
	store_p->push_back(g);
	store_p->push_back(h);
}

int nodestore::get(
	context * ctx_p,
	off_t offset0,
	uint64_t & v)
{
	off_t offset = offset0;
	uint64_t a = (uint64_t)store_p->operator[](offset++) << 56;
	uint64_t b = (uint64_t)store_p->operator[](offset++) << 48;
	uint64_t c = (uint64_t)store_p->operator[](offset++) << 40;
	uint64_t d = (uint64_t)store_p->operator[](offset++) << 32;
	uint64_t e = (uint64_t)store_p->operator[](offset++) << 24;
	uint64_t f = (uint64_t)store_p->operator[](offset++) << 16;
	uint64_t g = (uint64_t)store_p->operator[](offset++) << 8;
	uint64_t h = (uint64_t)store_p->operator[](offset++);
	v = a|b|c|d|e|f|g|h;
	return 8;
}


/*...........................................
	: text content                            :
	:.........................................:
*/

off_t nodestore::put(
	context * ctx_p,
	char const* content,
	uint32_t len)
{
	uint32_t res = store_p->size();
	store_p->push_back(STRING_CODE);
	put(ctx_p,(uint32_t)len);
	store_p->raw_copy(content, len);
	return res;
}

int nodestore::get(
	context * ctx_p,
	off_t offset0,
	char *& data,
	uint32_t & len)
{
	int k;
	off_t offset = offset0;
	if (store_p->operator[](offset++)!=STRING_CODE) return ERR_BAD_CODE;
	if ((k = get(ctx_p, offset, len)) < 0) return k; else offset += k;
	data = &store_p->operator[](offset);
	offset += len;
	return (offset-offset0);
}

off_t nodestore::put(
	context * ctx_p,
	string const& content)
{
	return put(ctx_p, content.c_str(), content.length());
}

int nodestore::get(
	context * ctx_p,
	off_t offset,
	string & content)
{
	char * data;
	uint32_t len;
	int k = get(ctx_p, offset, data, len);
	if (k<0) return k;
	content = string(data, 0, len); 
	return k;
}

off_t nodestore::put(
	context * ctx_p,
	rchandle<text_node> tnode_h)
{
	nodeid parentid = tnode_h->get_parentid();
	char const* content = tnode_h->get_content();
	uint32_t content_length = tnode_h->get_content_length();
	off_t offset = put(ctx_p, parentid, content, content_length);
	index_p->put(tnode_h->get_nodeid().id, offset);
	return offset;
}

int nodestore::get(
	context * ctx_p,
	nodeid nid,     
	rchandle<text_node>& tnode_h)
{
	off_t offset;
	if (!index_p->get(nid.id, offset)) return ERR_NODEID_NOT_FOUND;
	nodeid parentid;
	char * content;
	uint32_t content_length;
	int k = get(ctx_p, offset, parentid, content, content_length);
	if (k<0) return k;
	tnode_h = new text_node(nid, parentid,
							string((char *)content,0,content_length));
	return k;
}

off_t nodestore::put(
	context * ctx_p,
	nodeid parent,
	char const* content,
	uint32_t len)
{
	uint32_t res = store_p->size();
	store_p->push_back(STRING_CODE);
	put(ctx_p, (uint64_t)parent.id);
	put(ctx_p, (uint32_t)len);
	store_p->raw_copy(content, len);
	return res;
}

int nodestore::get(
	context * ctx_p,
	off_t offset0,
	nodeid & parent,
	char *& data,
	uint32_t & len)
{
	int k;
	uint64_t p;
	off_t offset = offset0;
	if (store_p->operator[](offset++)!=STRING_CODE) return ERR_BAD_CODE;
	if ((k = get(ctx_p, offset, p)) < 0) return k; else offset += k;
	if ((k = get(ctx_p, offset, len)) < 0) return k; else offset += k;
	data = &store_p->operator[](offset);
	offset += len;
	parent.id = p;
	return (offset-offset0);
}

off_t nodestore::put(
	context * ctx_p,
	nodeid parent,
	string const& content)
{
	return put(ctx_p, parent, content.c_str(), content.length());
}


/*...........................................
	: qname                                   :
	:.........................................:
*/

off_t nodestore::put(
	context * ctx_p,
	rchandle<QName> name_h)
{
	int k;
	off_t res = store_p->size();
	store_p->push_back(QNAME_CODE);
	store_p->push_back(name_h->get_type());
	put(ctx_p, name_h->get_namespace_hash());
	if ((k = put(ctx_p, name_h->get_name())) < 0) return k;
	if ((k = put(ctx_p, name_h->get_prefix())) < 0) return k;
	return res;
}

int nodestore::get(
	context * ctx_p,
	off_t offset0,
	rchandle<QName> & name_h)
{
	int k;
	uint64_t key;
	nodeid parent;

	off_t offset = offset0;
	if (store_p->operator[](offset++)!=QNAME_CODE) return ERR_BAD_CODE;

	QName::qname_type_t type = (QName::qname_type_t)store_p->operator[](offset++);
	if ((k = get(ctx_p, offset, key)) < 0) return k; else offset += k;

	char * name;
	uint32_t name_len;
	if ((k = get(ctx_p, offset, name, name_len)) < 0)
		return k;
	else
		offset += k;

	char * prefix;
	uint32_t prefix_len;
	if ((k = get(ctx_p, offset, prefix, prefix_len)) < 0)
		return k;
	else
		offset += k;

	name_h = new QName(type,
										 string((char *)prefix,0,prefix_len),
										 string((char *)name,0,name_len), key);
	return (offset-offset0);
}


/*...........................................
	: atribute nodes                          :
	:.........................................:
*/
off_t nodestore::put(
	context * ctx_p,
	rchandle<attribute_node> anode_h)
{
	uint32_t res = store_p->size();
	store_p->push_back(ATTR_CODE);
	put(ctx_p, (uint64_t)anode_h->get_parentid().id);
	put(ctx_p, anode_h->get_name());
	put(ctx_p, anode_h->get_val());
	index_p->put(anode_h->get_nodeid().id, res);
	return res;
}

int nodestore::get(
	context * ctx_p,
	nodeid nid,
	rchandle<attribute_node>& anode_h)
{
	int k = 0;
	off_t offset0;
	if (!index_p->get(nid.id, offset0)) return ERR_NODEID_NOT_FOUND;
	off_t offset = offset0;
	if (store_p->operator[](offset++)!=ATTR_CODE) return ERR_BAD_CODE;
	uint64_t parentid;
	if ((k = get(ctx_p, offset, parentid)) < 0) return k; else offset += k;
	rchandle<QName> name_h;
	if ((k = get(ctx_p, offset, name_h)) < 0) return k; else offset += k;
	string value;
	if ((k = get(ctx_p, offset, value)) < 0) return k; else offset += k;
	anode_h = new attribute_node(nid, parentid, name_h, value);
	return (offset-offset0);
}



/*
off_t nodestore::put(
	context * ctx_p,
	doc_node const* dnode)
{
	off_t res = offset;
	store[offset++] = DOC_CODE;
	store[offset++] = URI_CODE;
	put(ctx_p, dnode->get_baseuri();
	store[offset++] = URI_CODE;
	put(ctx_p, dnode->get_docuri();
	put(ctx_p, *dnode->children(ctx);
	return res;
}

off_t nodestore::put(
	context * ctx_p,
	element_node const* enode)
{
	off_t res = offset;
	store[offset++] = ELEM_CODE;
	put(ctx_p, enode->get_name());
	put(ctx_p, enode->ns_count());
	put(ctx_p, *enode->namespace_nodes(ctx));
	put(ctx_p, enode->attr_count());
	put(ctx_p, *enode->attributes(ctx));
	put(ctx_p, enode->elem_count());
	put(ctx_p, *enode->children(ctx));
	return res;
}


off_t nodestore::put(
	uint16_t code)
{
	store[offset++] = code;
	return offset; 
}


off_t nodestore::put(
	context * ctx_p,
	ns_node const* nsnode)
{
	off_t res = put(ctx_p, *nsnode->node_name(ctx));
	put_prefix(ctx_p, nsnode->get_prefix());
	put_uri(ctx_p, nsnode->get_uri());
	return res;
}

off_t nodestore::put(
	context * ctx_p,
	pi_node const* pnode)
{
	off_t res = put(ctx_p, *pnode->node_name(ctx));
	put_content(ctx_p, pnode->get_target());
	put_content(ctx_p, pnode->get_content());
	return res;
}

off_t nodestore::put(
	context * ctx_p,
	binary_node const* bnode)
{
	return 0;
}

*/

  
} /* namespace xqp */

