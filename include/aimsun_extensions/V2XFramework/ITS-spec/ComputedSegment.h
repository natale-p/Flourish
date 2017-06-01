/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "IVI"
 * 	found in "ISO_TS_19321.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_ComputedSegment_H_
#define	_ComputedSegment_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Zid.h"
#include "LanePosition.h"
#include "IVILaneWidth.h"
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct DeltaReferencePosition;

/* ComputedSegment */
typedef struct ComputedSegment {
	Zid_t	 zoneId;
	LanePosition_t	 laneNumber;
	IVILaneWidth_t	 laneWidth;
	long	*offsetDistance	/* OPTIONAL */;
	struct DeltaReferencePosition	*offsetPosition	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ComputedSegment_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ComputedSegment;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "DeltaReferencePosition.h"

#endif	/* _ComputedSegment_H_ */
#include <asn_internal.h>
