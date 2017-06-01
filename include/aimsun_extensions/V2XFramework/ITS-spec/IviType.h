/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "IVI"
 * 	found in "ISO_TS_19321.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_IviType_H_
#define	_IviType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum IviType {
	IviType_immediateDangerWarningMessages	= 0,
	IviType_regulatoryMessages	= 1,
	IviType_trafficRelatedInformationMessages	= 2,
	IviType_pollutionMessages	= 3,
	IviType_notTrafficRelatedInformationMessages	= 4
} e_IviType;

/* IviType */
typedef long	 IviType_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_IviType;
asn_struct_free_f IviType_free;
asn_struct_print_f IviType_print;
asn_constr_check_f IviType_constraint;
ber_type_decoder_f IviType_decode_ber;
der_type_encoder_f IviType_encode_der;
xer_type_decoder_f IviType_decode_xer;
xer_type_encoder_f IviType_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _IviType_H_ */
#include <asn_internal.h>
