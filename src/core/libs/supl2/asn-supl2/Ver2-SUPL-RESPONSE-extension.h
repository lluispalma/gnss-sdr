/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ULP-Version-2-message-extensions"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#ifndef	_Ver2_SUPL_RESPONSE_extension_H_
#define	_Ver2_SUPL_RESPONSE_extension_H_


#include "asn_application.h"

/* Including external dependencies */
#include "SPCSETKey.h"
#include "SPCSETKeylifetime.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SupportedNetworkInformation;
struct SPCTID;
struct Position;
struct GNSSPosTechnology;

/* Ver2-SUPL-RESPONSE-extension */
typedef struct Ver2_SUPL_RESPONSE_extension {
	struct SupportedNetworkInformation	*supportedNetworkInformation	/* OPTIONAL */;
	SPCSETKey_t	*sPCSETKey	/* OPTIONAL */;
	struct SPCTID	*sPCTID	/* OPTIONAL */;
	SPCSETKeylifetime_t	*sPCSETKeylifetime	/* OPTIONAL */;
	struct Position	*initialApproximateposition	/* OPTIONAL */;
	struct GNSSPosTechnology	*gnssPosTechnology	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Ver2_SUPL_RESPONSE_extension_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Ver2_SUPL_RESPONSE_extension;
extern asn_SEQUENCE_specifics_t asn_SPC_Ver2_SUPL_RESPONSE_extension_specs_1;
extern asn_TYPE_member_t asn_MBR_Ver2_SUPL_RESPONSE_extension_1[6];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SupportedNetworkInformation.h"
#include "SPCTID.h"
#include "Position.h"
#include "GNSSPosTechnology.h"

#endif	/* _Ver2_SUPL_RESPONSE_extension_H_ */
#include <asn_internal.h>
