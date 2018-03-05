/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SUPL-TRIGGERED-START"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#include "AreaId.h"

asn_per_constraints_t asn_PER_type_AreaId_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  3,  3,  0,  7 }	/* (0..7,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_AreaId_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct AreaId, choice.gSMAreaId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GSMAreaId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gSMAreaId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AreaId, choice.wCDMAAreaId),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_WCDMAAreaId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"wCDMAAreaId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AreaId, choice.cDMAAreaId),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CDMAAreaId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"cDMAAreaId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AreaId, choice.hRPDAreaId),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HRPDAreaId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"hRPDAreaId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AreaId, choice.uMBAreaId),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UMBAreaId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"uMBAreaId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AreaId, choice.lTEAreaId),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LTEAreaId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"lTEAreaId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AreaId, choice.wLANAreaId),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_WLANAreaId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"wLANAreaId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AreaId, choice.wiMAXAreaId),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_WimaxAreaId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"wiMAXAreaId"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_AreaId_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* gSMAreaId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* wCDMAAreaId */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* cDMAAreaId */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* hRPDAreaId */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* uMBAreaId */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* lTEAreaId */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* wLANAreaId */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 } /* wiMAXAreaId */
};
asn_CHOICE_specifics_t asn_SPC_AreaId_specs_1 = {
	sizeof(struct AreaId),
	offsetof(struct AreaId, _asn_ctx),
	offsetof(struct AreaId, present),
	sizeof(((struct AreaId *)0)->present),
	asn_MAP_AreaId_tag2el_1,
	8,	/* Count of tags in the map */
	0, 0,
	8	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_AreaId = {
	"AreaId",
	"AreaId",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ 0, &asn_PER_type_AreaId_constr_1, CHOICE_constraint },
	asn_MBR_AreaId_1,
	8,	/* Elements count */
	&asn_SPC_AreaId_specs_1	/* Additional specs */
};

