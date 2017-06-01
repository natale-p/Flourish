/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "ISO_TS_19091.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_GenericLane_H_
#define	_GenericLane_H_


#include <asn_application.h>

/* Including external dependencies */
#include "LaneID.h"
#include "DescriptiveName.h"
#include "ApproachID.h"
#include "LaneAttributes.h"
#include "AllowedManeuvers.h"
#include "NodeListXY.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ConnectsToList;
struct OverlayLaneList;
struct RegionalExtension;

/* GenericLane */
typedef struct GenericLane {
	LaneID_t	 laneID;
	DescriptiveName_t	*name	/* OPTIONAL */;
	ApproachID_t	*ingressApproach	/* OPTIONAL */;
	ApproachID_t	*egressApproach	/* OPTIONAL */;
	LaneAttributes_t	 laneAttributes;
	AllowedManeuvers_t	*maneuvers	/* OPTIONAL */;
	NodeListXY_t	 nodeList;
	struct ConnectsToList	*connectsTo	/* OPTIONAL */;
	struct OverlayLaneList	*overlays	/* OPTIONAL */;
	struct GenericLane__regional {
		A_SEQUENCE_OF(struct RegionalExtension) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *regional;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} GenericLane_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GenericLane;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ConnectsToList.h"
#include "OverlayLaneList.h"
#include "RegionalExtension.h"

#endif	/* _GenericLane_H_ */
#include <asn_internal.h>
