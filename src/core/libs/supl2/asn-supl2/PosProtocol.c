/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SUPL-START"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#include "PosProtocol.h"

asn_TYPE_member_t asn_MBR_PosProtocol_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PosProtocol, tia801),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"tia801"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PosProtocol, rrlp),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"rrlp"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PosProtocol, rrc),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"rrc"
		},
	{ ATF_POINTER, 1, offsetof(struct PosProtocol, ver2_PosProtocol_extension),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Ver2_PosProtocol_extension,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ver2-PosProtocol-extension"
		},
};
static const int asn_MAP_PosProtocol_oms_1[] = { 3 };
static const ber_tlv_tag_t asn_DEF_PosProtocol_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_PosProtocol_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* tia801 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* rrlp */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* rrc */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* ver2-PosProtocol-extension */
};
asn_SEQUENCE_specifics_t asn_SPC_PosProtocol_specs_1 = {
	sizeof(struct PosProtocol),
	offsetof(struct PosProtocol, _asn_ctx),
	asn_MAP_PosProtocol_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_PosProtocol_oms_1,	/* Optional members */
	0, 1,	/* Root/Additions */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_PosProtocol = {
	"PosProtocol",
	"PosProtocol",
	&asn_OP_SEQUENCE,
	asn_DEF_PosProtocol_tags_1,
	sizeof(asn_DEF_PosProtocol_tags_1)
		/sizeof(asn_DEF_PosProtocol_tags_1[0]), /* 1 */
	asn_DEF_PosProtocol_tags_1,	/* Same as above */
	sizeof(asn_DEF_PosProtocol_tags_1)
		/sizeof(asn_DEF_PosProtocol_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_PosProtocol_1,
	4,	/* Elements count */
	&asn_SPC_PosProtocol_specs_1	/* Additional specs */
};

