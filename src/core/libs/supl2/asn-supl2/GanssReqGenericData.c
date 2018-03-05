/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ULP-Version-2-parameter-extensions"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#include "GanssReqGenericData.h"

static int
memb_ganssId_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 15)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_ganssSBASid_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const BIT_STRING_t *st = (const BIT_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	if(st->size > 0) {
		/* Size in bits */
		size = 8 * st->size - (st->bits_unused & 0x07);
	} else {
		size = 0;
	}
	
	if((size == 3)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_ganssTimeModels_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const BIT_STRING_t *st = (const BIT_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	if(st->size > 0) {
		/* Size in bits */
		size = 8 * st->size - (st->bits_unused & 0x07);
	} else {
		size = 0;
	}
	
	if((size == 16)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_ganssId_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_ganssSBASid_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  3,  3 }	/* (SIZE(3..3)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_ganssTimeModels_constr_8 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  16,  16 }	/* (SIZE(16..16)) */,
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_GanssReqGenericData_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct GanssReqGenericData, ganssId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ 0, &asn_PER_memb_ganssId_constr_2,  memb_ganssId_constraint_1 },
		0, 0, /* No default value */
		"ganssId"
		},
	{ ATF_POINTER, 1, offsetof(struct GanssReqGenericData, ganssSBASid),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		0,
		{ 0, &asn_PER_memb_ganssSBASid_constr_3,  memb_ganssSBASid_constraint_1 },
		0, 0, /* No default value */
		"ganssSBASid"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct GanssReqGenericData, ganssRealTimeIntegrity),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ganssRealTimeIntegrity"
		},
	{ ATF_POINTER, 1, offsetof(struct GanssReqGenericData, ganssDifferentialCorrection),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DGANSS_Sig_Id_Req,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ganssDifferentialCorrection"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct GanssReqGenericData, ganssAlmanac),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ganssAlmanac"
		},
	{ ATF_POINTER, 2, offsetof(struct GanssReqGenericData, ganssNavigationModelData),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GanssNavigationModelData,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ganssNavigationModelData"
		},
	{ ATF_POINTER, 1, offsetof(struct GanssReqGenericData, ganssTimeModels),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		0,
		{ 0, &asn_PER_memb_ganssTimeModels_constr_8,  memb_ganssTimeModels_constraint_1 },
		0, 0, /* No default value */
		"ganssTimeModels"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct GanssReqGenericData, ganssReferenceMeasurementInfo),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ganssReferenceMeasurementInfo"
		},
	{ ATF_POINTER, 1, offsetof(struct GanssReqGenericData, ganssDataBits),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GanssDataBits,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ganssDataBits"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct GanssReqGenericData, ganssUTCModel),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ganssUTCModel"
		},
	{ ATF_POINTER, 1, offsetof(struct GanssReqGenericData, ganssAdditionalDataChoices),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GanssAdditionalDataChoices,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ganssAdditionalDataChoices"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct GanssReqGenericData, ganssAuxiliaryInformation),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ganssAuxiliaryInformation"
		},
	{ ATF_POINTER, 2, offsetof(struct GanssReqGenericData, ganssExtendedEphemeris),
		(ASN_TAG_CLASS_CONTEXT | (12 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ExtendedEphemeris,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ganssExtendedEphemeris"
		},
	{ ATF_POINTER, 1, offsetof(struct GanssReqGenericData, ganssExtendedEphemerisCheck),
		(ASN_TAG_CLASS_CONTEXT | (13 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GanssExtendedEphCheck,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ganssExtendedEphemerisCheck"
		},
};
static const int asn_MAP_GanssReqGenericData_oms_1[] = { 1, 3, 5, 6, 8, 10, 12, 13 };
static const ber_tlv_tag_t asn_DEF_GanssReqGenericData_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_GanssReqGenericData_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ganssId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ganssSBASid */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* ganssRealTimeIntegrity */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* ganssDifferentialCorrection */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* ganssAlmanac */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* ganssNavigationModelData */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* ganssTimeModels */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* ganssReferenceMeasurementInfo */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* ganssDataBits */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* ganssUTCModel */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 }, /* ganssAdditionalDataChoices */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 11, 0, 0 }, /* ganssAuxiliaryInformation */
    { (ASN_TAG_CLASS_CONTEXT | (12 << 2)), 12, 0, 0 }, /* ganssExtendedEphemeris */
    { (ASN_TAG_CLASS_CONTEXT | (13 << 2)), 13, 0, 0 } /* ganssExtendedEphemerisCheck */
};
asn_SEQUENCE_specifics_t asn_SPC_GanssReqGenericData_specs_1 = {
	sizeof(struct GanssReqGenericData),
	offsetof(struct GanssReqGenericData, _asn_ctx),
	asn_MAP_GanssReqGenericData_tag2el_1,
	14,	/* Count of tags in the map */
	asn_MAP_GanssReqGenericData_oms_1,	/* Optional members */
	8, 0,	/* Root/Additions */
	14,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_GanssReqGenericData = {
	"GanssReqGenericData",
	"GanssReqGenericData",
	&asn_OP_SEQUENCE,
	asn_DEF_GanssReqGenericData_tags_1,
	sizeof(asn_DEF_GanssReqGenericData_tags_1)
		/sizeof(asn_DEF_GanssReqGenericData_tags_1[0]), /* 1 */
	asn_DEF_GanssReqGenericData_tags_1,	/* Same as above */
	sizeof(asn_DEF_GanssReqGenericData_tags_1)
		/sizeof(asn_DEF_GanssReqGenericData_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_GanssReqGenericData_1,
	14,	/* Elements count */
	&asn_SPC_GanssReqGenericData_specs_1	/* Additional specs */
};

