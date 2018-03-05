/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SUPL-POS-INIT"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#include "SatelliteInfo.h"

asn_per_constraints_t asn_PER_type_SatelliteInfo_constr_1 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  31 }	/* (SIZE(1..31)) */,
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_SatelliteInfo_1[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_SatelliteInfoElement,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_SatelliteInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
asn_SET_OF_specifics_t asn_SPC_SatelliteInfo_specs_1 = {
	sizeof(struct SatelliteInfo),
	offsetof(struct SatelliteInfo, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
asn_TYPE_descriptor_t asn_DEF_SatelliteInfo = {
	"SatelliteInfo",
	"SatelliteInfo",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_SatelliteInfo_tags_1,
	sizeof(asn_DEF_SatelliteInfo_tags_1)
		/sizeof(asn_DEF_SatelliteInfo_tags_1[0]), /* 1 */
	asn_DEF_SatelliteInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_SatelliteInfo_tags_1)
		/sizeof(asn_DEF_SatelliteInfo_tags_1[0]), /* 1 */
	{ 0, &asn_PER_type_SatelliteInfo_constr_1, SEQUENCE_OF_constraint },
	asn_MBR_SatelliteInfo_1,
	1,	/* Single element */
	&asn_SPC_SatelliteInfo_specs_1	/* Additional specs */
};

