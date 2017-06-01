/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "IVI"
 * 	found in "ISO_TS_19321.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_DDD_H_
#define	_DDD_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct DDD_IO;

/* DDD */
typedef struct DDD {
	long	*dcj	/* OPTIONAL */;
	long	*dcr	/* OPTIONAL */;
	long	*tpl	/* OPTIONAL */;
	struct DDD__ioList {
		A_SEQUENCE_OF(struct DDD_IO) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} ioList;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DDD_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DDD;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "DDD-IO.h"

#endif	/* _DDD_H_ */
#include <asn_internal.h>
