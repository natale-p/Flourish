/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "LibIts-ITS-Container-r1318.asn"
 */

#ifndef	_RelevanceTrafficDirection_H_
#define	_RelevanceTrafficDirection_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RelevanceTrafficDirection {
	RelevanceTrafficDirection_allTrafficDirections	= 0,
	RelevanceTrafficDirection_upstreamTraffic	= 1,
	RelevanceTrafficDirection_downstreamTraffic	= 2,
	RelevanceTrafficDirection_oppositeTraffic	= 3
} e_RelevanceTrafficDirection;

/* RelevanceTrafficDirection */
typedef long	 RelevanceTrafficDirection_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RelevanceTrafficDirection;
asn_struct_free_f RelevanceTrafficDirection_free;
asn_struct_print_f RelevanceTrafficDirection_print;
asn_constr_check_f RelevanceTrafficDirection_constraint;
ber_type_decoder_f RelevanceTrafficDirection_decode_ber;
der_type_encoder_f RelevanceTrafficDirection_encode_der;
xer_type_decoder_f RelevanceTrafficDirection_decode_xer;
xer_type_encoder_f RelevanceTrafficDirection_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _RelevanceTrafficDirection_H_ */
#include <asn_internal.h>