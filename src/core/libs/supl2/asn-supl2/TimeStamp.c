/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SUPL-REPORT"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#include "TimeStamp.h"

static int
memb_relativeTime_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 31536000)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_relativeTime_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 25, -1,  0,  31536000 }	/* (0..31536000) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_per_constraints_t asn_PER_type_TimeStamp_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_TimeStamp_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct TimeStamp, choice.absoluteTime),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UTCTime,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"absoluteTime"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TimeStamp, choice.relativeTime),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ 0, &asn_PER_memb_relativeTime_constr_3,  memb_relativeTime_constraint_1 },
		0, 0, /* No default value */
		"relativeTime"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_TimeStamp_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* absoluteTime */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* relativeTime */
};
asn_CHOICE_specifics_t asn_SPC_TimeStamp_specs_1 = {
	sizeof(struct TimeStamp),
	offsetof(struct TimeStamp, _asn_ctx),
	offsetof(struct TimeStamp, present),
	sizeof(((struct TimeStamp *)0)->present),
	asn_MAP_TimeStamp_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_TimeStamp = {
	"TimeStamp",
	"TimeStamp",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ 0, &asn_PER_type_TimeStamp_constr_1, CHOICE_constraint },
	asn_MBR_TimeStamp_1,
	2,	/* Elements count */
	&asn_SPC_TimeStamp_specs_1	/* Additional specs */
};

