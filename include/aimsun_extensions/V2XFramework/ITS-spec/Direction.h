/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "IVI"
 * 	found in "ISO_TS_19321.asn"
 * 	`asn1c -fcompound-names`
 */

#ifndef	_Direction_H_
#define	_Direction_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Direction {
	Direction_sameDirection	= 0,
	Direction_oppositeDirection	= 1,
	Direction_bothDirections	= 2,
	Direction_valueNotUsed	= 3
} e_Direction;

/* Direction */
typedef long	 Direction_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Direction;
asn_struct_free_f Direction_free;
asn_struct_print_f Direction_print;
asn_constr_check_f Direction_constraint;
ber_type_decoder_f Direction_decode_ber;
der_type_encoder_f Direction_encode_der;
xer_type_decoder_f Direction_decode_xer;
xer_type_encoder_f Direction_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _Direction_H_ */
#include <asn_internal.h>
