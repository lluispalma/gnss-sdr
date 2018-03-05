/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ULP-Components"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#ifndef _ChipRate_H_
#define _ChipRate_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeEnumerated.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Dependencies */
    typedef enum ChipRate
    {
        ChipRate_tdd128 = 0,
        ChipRate_tdd384 = 1,
        ChipRate_tdd768 = 2
        /*
	 * Enumeration is extensible
	 */
    } e_ChipRate;

    /* ChipRate */
    typedef long ChipRate_t;

    /* Implementation */
    extern asn_per_constraints_t asn_PER_type_ChipRate_constr_1;
    extern asn_TYPE_descriptor_t asn_DEF_ChipRate;
    extern const asn_INTEGER_specifics_t asn_SPC_ChipRate_specs_1;
    asn_struct_free_f ChipRate_free;
    asn_struct_print_f ChipRate_print;
    asn_constr_check_f ChipRate_constraint;
    ber_type_decoder_f ChipRate_decode_ber;
    der_type_encoder_f ChipRate_encode_der;
    xer_type_decoder_f ChipRate_decode_xer;
    xer_type_encoder_f ChipRate_encode_xer;
    per_type_decoder_f ChipRate_decode_uper;
    per_type_encoder_f ChipRate_encode_uper;

#ifdef __cplusplus
}
#endif

#endif /* _ChipRate_H_ */
#include "asn_internal.h"