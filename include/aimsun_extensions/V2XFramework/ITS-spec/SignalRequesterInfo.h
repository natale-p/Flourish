/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "ISO_TS_19091.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_SignalRequesterInfo_H_
#define	_SignalRequesterInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include "VehicleID.h"
#include "RequestID.h"
#include "MsgCount.h"
#include "BasicVehicleRole.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RequestorType;

/* SignalRequesterInfo */
typedef struct SignalRequesterInfo {
	VehicleID_t	 id;
	RequestID_t	 request;
	MsgCount_t	 sequenceNumber;
	BasicVehicleRole_t	*role	/* OPTIONAL */;
	struct RequestorType	*typeData	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SignalRequesterInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SignalRequesterInfo;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "RequestorType.h"

#endif	/* _SignalRequesterInfo_H_ */
#include <asn_internal.h>
