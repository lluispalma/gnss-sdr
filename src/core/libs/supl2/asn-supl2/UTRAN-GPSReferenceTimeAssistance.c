/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ver2-ULP-Components"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#include "UTRAN-GPSReferenceTimeAssistance.h"

static int
memb_gpsReferenceTimeUncertainty_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 127)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_gpsReferenceTimeUncertainty_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 7,  7,  0,  127 }	/* (0..127) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_UTRAN_GPSReferenceTimeAssistance_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UTRAN_GPSReferenceTimeAssistance, utran_GPSReferenceTime),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UTRAN_GPSReferenceTime,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"utran-GPSReferenceTime"
		},
	{ ATF_POINTER, 2, offsetof(struct UTRAN_GPSReferenceTimeAssistance, gpsReferenceTimeUncertainty),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ 0, &asn_PER_memb_gpsReferenceTimeUncertainty_constr_3,  memb_gpsReferenceTimeUncertainty_constraint_1 },
		0, 0, /* No default value */
		"gpsReferenceTimeUncertainty"
		},
	{ ATF_POINTER, 1, offsetof(struct UTRAN_GPSReferenceTimeAssistance, utranGPSDriftRate),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UTRANGPSDriftRate,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"utranGPSDriftRate"
		},
};
static const int asn_MAP_UTRAN_GPSReferenceTimeAssistance_oms_1[] = { 1, 2 };
static const ber_tlv_tag_t asn_DEF_UTRAN_GPSReferenceTimeAssistance_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_UTRAN_GPSReferenceTimeAssistance_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* utran-GPSReferenceTime */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* gpsReferenceTimeUncertainty */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* utranGPSDriftRate */
};
asn_SEQUENCE_specifics_t asn_SPC_UTRAN_GPSReferenceTimeAssistance_specs_1 = {
	sizeof(struct UTRAN_GPSReferenceTimeAssistance),
	offsetof(struct UTRAN_GPSReferenceTimeAssistance, _asn_ctx),
	asn_MAP_UTRAN_GPSReferenceTimeAssistance_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_UTRAN_GPSReferenceTimeAssistance_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_UTRAN_GPSReferenceTimeAssistance = {
	"UTRAN-GPSReferenceTimeAssistance",
	"UTRAN-GPSReferenceTimeAssistance",
	&asn_OP_SEQUENCE,
	asn_DEF_UTRAN_GPSReferenceTimeAssistance_tags_1,
	sizeof(asn_DEF_UTRAN_GPSReferenceTimeAssistance_tags_1)
		/sizeof(asn_DEF_UTRAN_GPSReferenceTimeAssistance_tags_1[0]), /* 1 */
	asn_DEF_UTRAN_GPSReferenceTimeAssistance_tags_1,	/* Same as above */
	sizeof(asn_DEF_UTRAN_GPSReferenceTimeAssistance_tags_1)
		/sizeof(asn_DEF_UTRAN_GPSReferenceTimeAssistance_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_UTRAN_GPSReferenceTimeAssistance_1,
	3,	/* Elements count */
	&asn_SPC_UTRAN_GPSReferenceTimeAssistance_specs_1	/* Additional specs */
};

