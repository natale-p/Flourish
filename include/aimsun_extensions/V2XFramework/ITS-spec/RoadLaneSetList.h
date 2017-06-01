/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "ISO_TS_19091.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_RoadLaneSetList_H_
#define	_RoadLaneSetList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct GenericLane;

/* RoadLaneSetList */
typedef struct RoadLaneSetList {
	A_SEQUENCE_OF(struct GenericLane) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RoadLaneSetList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RoadLaneSetList;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "GenericLane.h"

#endif	/* _RoadLaneSetList_H_ */
#include <asn_internal.h>
