/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ULP-Version-2-parameter-extensions"
 * 	found in "../ulp.asn1"
 * 	`asn1c -S ../../skeletons -pdu=ULP-PDU -pdu=SUPLINIT -fcompound-names -no-gen-OER`
 */

#include "ExtendedEphemeris.h"

static int
memb_validity_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 1 && value <= 256)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_validity_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 8,  8,  1,  256 }	/* (1..256) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_ExtendedEphemeris_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ExtendedEphemeris, validity),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ 0, &asn_PER_memb_validity_constr_2,  memb_validity_constraint_1 },
		0, 0, /* No default value */
		"validity"
		},
};
static const ber_tlv_tag_t asn_DEF_ExtendedEphemeris_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ExtendedEphemeris_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* validity */
};
asn_SEQUENCE_specifics_t asn_SPC_ExtendedEphemeris_specs_1 = {
	sizeof(struct ExtendedEphemeris),
	offsetof(struct ExtendedEphemeris, _asn_ctx),
	asn_MAP_ExtendedEphemeris_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ExtendedEphemeris = {
	"ExtendedEphemeris",
	"ExtendedEphemeris",
	&asn_OP_SEQUENCE,
	asn_DEF_ExtendedEphemeris_tags_1,
	sizeof(asn_DEF_ExtendedEphemeris_tags_1)
		/sizeof(asn_DEF_ExtendedEphemeris_tags_1[0]), /* 1 */
	asn_DEF_ExtendedEphemeris_tags_1,	/* Same as above */
	sizeof(asn_DEF_ExtendedEphemeris_tags_1)
		/sizeof(asn_DEF_ExtendedEphemeris_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ExtendedEphemeris_1,
	1,	/* Elements count */
	&asn_SPC_ExtendedEphemeris_specs_1	/* Additional specs */
};

