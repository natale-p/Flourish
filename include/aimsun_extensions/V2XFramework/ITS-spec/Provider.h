/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "EfcDsrcApplication"
 * 	found in "ISO_TS_14906_Application.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_Provider_H_
#define	_Provider_H_


#include <asn_application.h>

/* Including external dependencies */
#include "CountryCode.h"
#include "IssuerIdentifier.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Provider */
typedef struct Provider {
	CountryCode_t	 countryCode;
	IssuerIdentifier_t	 providerIdentifier;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Provider_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Provider;

#ifdef __cplusplus
}
#endif

#endif	/* _Provider_H_ */
#include <asn_internal.h>
