/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "IVI"
 * 	found in "ISO_TS_19321.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_DBV_H_
#define	_DBV_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Distance.h"

#ifdef __cplusplus
extern "C" {
#endif

/* DBV */
typedef Distance_t	 DBV_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DBV;
asn_struct_free_f DBV_free;
asn_struct_print_f DBV_print;
asn_constr_check_f DBV_constraint;
ber_type_decoder_f DBV_decode_ber;
der_type_encoder_f DBV_encode_der;
xer_type_decoder_f DBV_decode_xer;
xer_type_encoder_f DBV_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _DBV_H_ */
#include <asn_internal.h>
