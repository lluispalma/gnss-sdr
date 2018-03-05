/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SUPL-INIT"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#ifndef _EncodingType_H_
#define _EncodingType_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeEnumerated.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Dependencies */
    typedef enum EncodingType
    {
        EncodingType_ucs2 = 0,
        EncodingType_gsmDefault = 1,
        EncodingType_utf8 = 2
        /*
	 * Enumeration is extensible
	 */
    } e_EncodingType;

    /* EncodingType */
    typedef long EncodingType_t;

    /* Implementation */
    extern asn_per_constraints_t asn_PER_type_EncodingType_constr_1;
    extern asn_TYPE_descriptor_t asn_DEF_EncodingType;
    extern const asn_INTEGER_specifics_t asn_SPC_EncodingType_specs_1;
    asn_struct_free_f EncodingType_free;
    asn_struct_print_f EncodingType_print;
    asn_constr_check_f EncodingType_constraint;
    ber_type_decoder_f EncodingType_decode_ber;
    der_type_encoder_f EncodingType_encode_der;
    xer_type_decoder_f EncodingType_decode_xer;
    xer_type_encoder_f EncodingType_encode_xer;
    per_type_decoder_f EncodingType_decode_uper;
    per_type_encoder_f EncodingType_encode_uper;

#ifdef __cplusplus
}
#endif

#endif /* _EncodingType_H_ */
#include "asn_internal.h"
