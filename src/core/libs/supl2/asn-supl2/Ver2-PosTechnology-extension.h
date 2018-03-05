/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ULP-Version-2-parameter-extensions"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#ifndef	_Ver2_PosTechnology_extension_H_
#define	_Ver2_PosTechnology_extension_H_


#include "asn_application.h"

/* Including external dependencies */
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct GANSSPositionMethods;

/* Ver2-PosTechnology-extension */
typedef struct Ver2_PosTechnology_extension {
	struct GANSSPositionMethods	*gANSSPositionMethods	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Ver2_PosTechnology_extension_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Ver2_PosTechnology_extension;
extern asn_SEQUENCE_specifics_t asn_SPC_Ver2_PosTechnology_extension_specs_1;
extern asn_TYPE_member_t asn_MBR_Ver2_PosTechnology_extension_1[1];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "GANSSPositionMethods.h"

#endif	/* _Ver2_PosTechnology_extension_H_ */
#include <asn_internal.h>
