/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "IVI"
 * 	found in "ISO_TS_19321.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_GeographicLocationContainer_H_
#define	_GeographicLocationContainer_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ReferencePosition.h"
#include "TimestampIts.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Heading;
struct Speed;
struct GlcPart;

/* GeographicLocationContainer */
typedef struct GeographicLocationContainer {
	ReferencePosition_t	 referencePosition;
	TimestampIts_t	*referencePositionTime	/* OPTIONAL */;
	struct Heading	*referencePositionHeading	/* OPTIONAL */;
	struct Speed	*referencePositionSpeed	/* OPTIONAL */;
	struct GeographicLocationContainer__parts {
		A_SEQUENCE_OF(struct GlcPart) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} parts;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} GeographicLocationContainer_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GeographicLocationContainer;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "Heading.h"
#include "Speed.h"
#include "GlcPart.h"

#endif	/* _GeographicLocationContainer_H_ */
#include <asn_internal.h>
