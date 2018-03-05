/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ver2-ULP-Components"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#include "RTDUnits.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
asn_per_constraints_t asn_PER_type_RTDUnits_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  3,  3,  0,  4 }	/* (0..4,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_RTDUnits_value2enum_1[] = {
	{ 0,	12,	"microseconds" },
	{ 1,	21,	"hundredsofnanoseconds" },
	{ 2,	17,	"tensofnanoseconds" },
	{ 3,	11,	"nanoseconds" },
	{ 4,	19,	"tenthsofnanoseconds" }
	/* This list is extensible */
};
static const unsigned int asn_MAP_RTDUnits_enum2value_1[] = {
	1,	/* hundredsofnanoseconds(1) */
	0,	/* microseconds(0) */
	3,	/* nanoseconds(3) */
	2,	/* tensofnanoseconds(2) */
	4	/* tenthsofnanoseconds(4) */
	/* This list is extensible */
};
const asn_INTEGER_specifics_t asn_SPC_RTDUnits_specs_1 = {
	asn_MAP_RTDUnits_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_RTDUnits_enum2value_1,	/* N => "tag"; sorted by N */
	5,	/* Number of elements in the maps */
	6,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_RTDUnits_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_RTDUnits = {
	"RTDUnits",
	"RTDUnits",
	&asn_OP_NativeEnumerated,
	asn_DEF_RTDUnits_tags_1,
	sizeof(asn_DEF_RTDUnits_tags_1)
		/sizeof(asn_DEF_RTDUnits_tags_1[0]), /* 1 */
	asn_DEF_RTDUnits_tags_1,	/* Same as above */
	sizeof(asn_DEF_RTDUnits_tags_1)
		/sizeof(asn_DEF_RTDUnits_tags_1[0]), /* 1 */
	{ 0, &asn_PER_type_RTDUnits_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_RTDUnits_specs_1	/* Additional specs */
};

