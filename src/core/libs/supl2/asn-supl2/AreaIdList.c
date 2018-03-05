/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SUPL-TRIGGERED-START"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#include "AreaIdList.h"

asn_TYPE_member_t asn_MBR_AreaIdList_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct AreaIdList, areaIdSet),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AreaIdSet,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"areaIdSet"
		},
	{ ATF_POINTER, 2, offsetof(struct AreaIdList, areaIdSetType),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AreaIdSetType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"areaIdSetType"
		},
	{ ATF_POINTER, 1, offsetof(struct AreaIdList, geoAreaMappingList),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GeoAreaMappingList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"geoAreaMappingList"
		},
};
static const int asn_MAP_AreaIdList_oms_1[] = { 1, 2 };
static const ber_tlv_tag_t asn_DEF_AreaIdList_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_AreaIdList_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* areaIdSet */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* areaIdSetType */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* geoAreaMappingList */
};
asn_SEQUENCE_specifics_t asn_SPC_AreaIdList_specs_1 = {
	sizeof(struct AreaIdList),
	offsetof(struct AreaIdList, _asn_ctx),
	asn_MAP_AreaIdList_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_AreaIdList_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_AreaIdList = {
	"AreaIdList",
	"AreaIdList",
	&asn_OP_SEQUENCE,
	asn_DEF_AreaIdList_tags_1,
	sizeof(asn_DEF_AreaIdList_tags_1)
		/sizeof(asn_DEF_AreaIdList_tags_1[0]), /* 1 */
	asn_DEF_AreaIdList_tags_1,	/* Same as above */
	sizeof(asn_DEF_AreaIdList_tags_1)
		/sizeof(asn_DEF_AreaIdList_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_AreaIdList_1,
	3,	/* Elements count */
	&asn_SPC_AreaIdList_specs_1	/* Additional specs */
};

