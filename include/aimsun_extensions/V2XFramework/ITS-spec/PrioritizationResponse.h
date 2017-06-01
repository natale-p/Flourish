/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "AddGrpC"
 * 	found in "ISO_TS_19091.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_PrioritizationResponse_H_
#define	_PrioritizationResponse_H_


#include <asn_application.h>

/* Including external dependencies */
#include "StationID.h"
#include "PrioritizationResponseStatus.h"
#include "SignalGroupID.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PrioritizationResponse */
typedef struct PrioritizationResponse {
	StationID_t	 stationID;
	PrioritizationResponseStatus_t	 priorState;
	SignalGroupID_t	 signalGroup;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PrioritizationResponse_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PrioritizationResponse;

#ifdef __cplusplus
}
#endif

#endif	/* _PrioritizationResponse_H_ */
#include <asn_internal.h>
