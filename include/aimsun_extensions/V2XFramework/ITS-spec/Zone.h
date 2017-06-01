/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "IVI"
 * 	found in "ISO_TS_19321.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_Zone_H_
#define	_Zone_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Segment.h"
#include "PolygonalLine.h"
#include "ComputedSegment.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Zone_PR {
	Zone_PR_NOTHING,	/* No components present */
	Zone_PR_segment,
	Zone_PR_area,
	Zone_PR_computedSegment
	/* Extensions may appear below */
	
} Zone_PR;

/* Zone */
typedef struct Zone {
	Zone_PR present;
	union Zone_u {
		Segment_t	 segment;
		PolygonalLine_t	 area;
		ComputedSegment_t	 computedSegment;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Zone_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Zone;

#ifdef __cplusplus
}
#endif

#endif	/* _Zone_H_ */
#include <asn_internal.h>
