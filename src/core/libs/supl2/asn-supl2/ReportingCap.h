/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ver2-ULP-Components"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#ifndef	_ReportingCap_H_
#define	_ReportingCap_H_


#include "asn_application.h"

/* Including external dependencies */
#include <NativeInteger.h>
#include "Ver2-ULP-Components_RepMode.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct BatchRepCap;

/* ReportingCap */
typedef struct ReportingCap {
	long	 minInt;
	long	*maxInt	/* OPTIONAL */;
	Ver2_ULP_Components_RepMode_t	 repMode;
	struct BatchRepCap	*batchRepCap	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ReportingCap_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ReportingCap;
extern asn_SEQUENCE_specifics_t asn_SPC_ReportingCap_specs_1;
extern asn_TYPE_member_t asn_MBR_ReportingCap_1[4];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "BatchRepCap.h"

#endif	/* _ReportingCap_H_ */
#include <asn_internal.h>
