/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ver2-ULP-Components"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#ifndef	_LteCellInformation_H_
#define	_LteCellInformation_H_


#include "asn_application.h"

/* Including external dependencies */
#include "CellGlobalIdEUTRA.h"
#include "PhysCellId.h"
#include "TrackingAreaCode.h"
#include "RSRP-Range.h"
#include "RSRQ-Range.h"
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct MeasResultListEUTRA;

/* LteCellInformation */
typedef struct LteCellInformation {
	CellGlobalIdEUTRA_t	 cellGlobalIdEUTRA;
	PhysCellId_t	 physCellId;
	TrackingAreaCode_t	 trackingAreaCode;
	RSRP_Range_t	*rsrpResult	/* OPTIONAL */;
	RSRQ_Range_t	*rsrqResult	/* OPTIONAL */;
	long	*tA	/* OPTIONAL */;
	struct MeasResultListEUTRA	*measResultListEUTRA	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} LteCellInformation_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LteCellInformation;
extern asn_SEQUENCE_specifics_t asn_SPC_LteCellInformation_specs_1;
extern asn_TYPE_member_t asn_MBR_LteCellInformation_1[7];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "MeasResultListEUTRA.h"

#endif	/* _LteCellInformation_H_ */
#include <asn_internal.h>
