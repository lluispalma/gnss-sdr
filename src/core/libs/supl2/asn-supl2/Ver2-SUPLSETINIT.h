/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SUPL-SET-INIT"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#ifndef	_Ver2_SUPLSETINIT_H_
#define	_Ver2_SUPLSETINIT_H_


#include "asn_application.h"

/* Including external dependencies */
#include "SETId.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct QoP;
struct ApplicationID;

/* Ver2-SUPLSETINIT */
typedef struct Ver2_SUPLSETINIT {
	SETId_t	 targetSETID;
	struct QoP	*qoP	/* OPTIONAL */;
	struct ApplicationID	*applicationID	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Ver2_SUPLSETINIT_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Ver2_SUPLSETINIT;
extern asn_SEQUENCE_specifics_t asn_SPC_Ver2_SUPLSETINIT_specs_1;
extern asn_TYPE_member_t asn_MBR_Ver2_SUPLSETINIT_1[3];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "QoP.h"
#include "ApplicationID.h"

#endif	/* _Ver2_SUPLSETINIT_H_ */
#include <asn_internal.h>
