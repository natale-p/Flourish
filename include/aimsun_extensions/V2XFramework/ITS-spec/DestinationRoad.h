/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "IVI"
 * 	found in "ISO_TS_19321.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_DestinationRoad_H_
#define	_DestinationRoad_H_


#include <asn_application.h>

/* Including external dependencies */
#include "DDD-DER.h"
#include <NativeInteger.h>
#include <UTF8String.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DestinationRoad */
typedef struct DestinationRoad {
	DDD_DER_t	 derType;
	long	*ronId	/* OPTIONAL */;
	UTF8String_t	*ronText	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DestinationRoad_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DestinationRoad;

#ifdef __cplusplus
}
#endif

#endif	/* _DestinationRoad_H_ */
#include <asn_internal.h>
