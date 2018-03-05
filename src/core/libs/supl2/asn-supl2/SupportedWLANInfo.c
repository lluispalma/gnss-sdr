/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ver2-ULP-Components"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#include "SupportedWLANInfo.h"

asn_TYPE_member_t asn_MBR_SupportedWLANInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, apTP),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"apTP"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, apAG),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"apAG"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, apSN),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"apSN"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, apDevType),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"apDevType"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, apRSSI),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"apRSSI"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, apChanFreq),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"apChanFreq"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, apRTD),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"apRTD"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, setTP),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"setTP"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, setAG),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"setAG"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, setSN),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"setSN"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, setRSSI),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"setRSSI"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SupportedWLANInfo, apRepLoc),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"apRepLoc"
		},
};
static const ber_tlv_tag_t asn_DEF_SupportedWLANInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SupportedWLANInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* apTP */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* apAG */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* apSN */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* apDevType */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* apRSSI */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* apChanFreq */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* apRTD */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* setTP */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* setAG */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* setSN */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 }, /* setRSSI */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 11, 0, 0 } /* apRepLoc */
};
asn_SEQUENCE_specifics_t asn_SPC_SupportedWLANInfo_specs_1 = {
	sizeof(struct SupportedWLANInfo),
	offsetof(struct SupportedWLANInfo, _asn_ctx),
	asn_MAP_SupportedWLANInfo_tag2el_1,
	12,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	12,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_SupportedWLANInfo = {
	"SupportedWLANInfo",
	"SupportedWLANInfo",
	&asn_OP_SEQUENCE,
	asn_DEF_SupportedWLANInfo_tags_1,
	sizeof(asn_DEF_SupportedWLANInfo_tags_1)
		/sizeof(asn_DEF_SupportedWLANInfo_tags_1[0]), /* 1 */
	asn_DEF_SupportedWLANInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_SupportedWLANInfo_tags_1)
		/sizeof(asn_DEF_SupportedWLANInfo_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_SupportedWLANInfo_1,
	12,	/* Elements count */
	&asn_SPC_SupportedWLANInfo_specs_1	/* Additional specs */
};

