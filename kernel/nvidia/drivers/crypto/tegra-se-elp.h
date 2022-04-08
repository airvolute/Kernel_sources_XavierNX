/*
 * Header file for Tegra Security Elliptic Engine
 *
 * Copyright (c) 2015-2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#ifndef _CRYPTO_TEGRA_SE_ELP_H
#define _CRYPTO_TEGRA_SE_ELP_H

/* Curves IDs */
/* ECC_CURVE_NIST_P192 and ECC_CURVE_NIST_P256 are
 * defined in include/crypto/ecdh.h
 */
#define ECC_CURVE_NIST_P224		0x0000
#define ECC_CURVE_NIST_P384		0x0003
#define ECC_CURVE_NIST_P521		0x0004
#define C25519_CURVE_C256		0x0005
#define ECC_CURVE_BRAINPOOL_P256	0x0006
#define ED25519_CURVE_P256		0x0007

/* Security Engine operation modes */
enum tegra_se_elp_op_mode {
	SE_ELP_OP_MODE_RSA512,
	SE_ELP_OP_MODE_RSA768,
	SE_ELP_OP_MODE_RSA1024,
	SE_ELP_OP_MODE_RSA1536,
	SE_ELP_OP_MODE_RSA2048,
	SE_ELP_OP_MODE_RSA3072,
	SE_ELP_OP_MODE_RSA4096,

	SE_ELP_OP_MODE_ECC160,
	SE_ELP_OP_MODE_ECC192,
	SE_ELP_OP_MODE_ECC224,
	SE_ELP_OP_MODE_ECC256,
	SE_ELP_OP_MODE_ECC384,
	SE_ELP_OP_MODE_ECC512,
	SE_ELP_OP_MODE_ECC521,

	SE_ELP_OP_MODE_MOD160,
	SE_ELP_OP_MODE_MOD192,
	SE_ELP_OP_MODE_MOD224,
	SE_ELP_OP_MODE_MOD256,
	SE_ELP_OP_MODE_MOD384,
	SE_ELP_OP_MODE_MOD512,
};

struct tegra_se_ecc_point {
	u32 *x;
	u32 *y;
};

struct tegra_se_ecc_curve {
	char *name;
	struct tegra_se_ecc_point g;
	u32 *p;
	u32 *p2;
	u32 *p5inv8;
	u32 *p3inv8;
	u32 *p1inv4;
	u32 *n;
	u32 *a;
	unsigned int nbytes;
	unsigned int mode;
	u32 *vec;
};

/* NIST P-192 */
static u32 nist_p192_x[] = { 0x82FF1012ull, 0xF4FF0AFDull, 0x43A18800ull,
				0x7CBF20EBull, 0xB03090F6ull, 0x188DA80Eull };
static u32 nist_p192_y[] = { 0x1E794811ull, 0x73F977A1ull, 0x6B24CDD5ull,
				0x631011EDull, 0xFFC8DA78ull, 0x07192B95ull };
static u32 nist_p192_p[] = { 0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFEull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull };
static u32 nist_p192_n[] = { 0xB4D22831ull, 0x146BC9B1ull, 0x99DEF836ull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull };
static u32 nist_p192_a[] = { 0xFFFFFFFCull, 0xFFFFFFFFull, 0xFFFFFFFEull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull };

static struct tegra_se_ecc_curve curve_p192 = {
	.name = "NIST_P-192",
	.g = {
		.x = nist_p192_x,
		.y = nist_p192_y,
	},
	.p = nist_p192_p,
	.n = nist_p192_n,
	.a = nist_p192_a,
	.nbytes = 24,
	.mode = SE_ELP_OP_MODE_ECC192,
};

/* NIST P-224 */
static u32 nist_p224_x[] = { 0x115C1D21ull, 0x343280D6ull, 0x56C21122ull,
				0x4A03C1D3ull, 0x321390B9ull, 0x6BB4BF7Full,
				0xB70E0CBDull };
static u32 nist_p224_y[] = { 0x85007E34ull, 0x44D58199ull, 0x5A074764ull,
				0xCD4375A0ull, 0x4C22DFE6ull, 0xB5F723FBull,
				0xBD376388ull };
static u32 nist_p224_p[] = { 0x00000001ull, 0x00000000ull, 0x00000000ull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull };
static u32 nist_p224_n[] = { 0x5C5C2A3Dull, 0x13DD2945ull, 0xE0B8F03Eull,
				0xFFFF16A2ull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull };
static u32 nist_p224_a[] = { 0xFFFFFFFEull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFEull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull };

static struct tegra_se_ecc_curve curve_p224 = {
	.name = "NIST_P-224",
	.g = {
		.x = nist_p224_x,
		.y = nist_p224_y,
	},
	.p = nist_p224_p,
	.n = nist_p224_n,
	.a = nist_p224_a,
	.nbytes = 28,
	.mode = SE_ELP_OP_MODE_ECC224,
};

/* NIST P-256 */
static u32 nist_p256_x[] = { 0xD898C296ull, 0xF4A13945ull, 0x2DEB33A0ull,
				0x77037D81ull, 0x63A440F2ull, 0xF8BCE6E5ull,
				0xE12C4247ull, 0x6B17D1F2ull };
static u32 nist_p256_y[] = { 0x37BF51F5ull, 0xCBB64068ull, 0x6B315ECEull,
				0x2BCE3357ull, 0x7C0F9E16ull, 0x8EE7EB4Aull,
				0xFE1A7F9Bull, 0x4FE342E2ull };
static u32 nist_p256_p[] = { 0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0x00000000ull, 0x00000000ull, 0x00000000ull,
				0x00000001ull, 0xFFFFFFFFull };
static u32 nist_p256_n[] = { 0xFC632551ull, 0xF3B9CAC2ull, 0xA7179E84ull,
				0xBCE6FAADull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0x00000000ull, 0xFFFFFFFFull };
static u32 nist_p256_a[] = { 0xFFFFFFFCull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0x00000000ull, 0x00000000ull, 0x00000000ull,
				0x00000001ull, 0xFFFFFFFFull };

static struct tegra_se_ecc_curve curve_p256 = {
	.name = "NIST_P-256",
	.g = {
		.x = nist_p256_x,
		.y = nist_p256_y,
	},
	.p = nist_p256_p,
	.n = nist_p256_n,
	.a = nist_p256_a,
	.nbytes = 32,
	.mode = SE_ELP_OP_MODE_ECC256,
};

/* NIST P-384 */
static u32 nist_p384_x[] = { 0x72760AB7ull, 0x3A545E38ull, 0xBF55296Cull,
				0x5502F25Dull, 0x82542A38ull, 0x59F741E0ull,
				0x8BA79B98ull, 0x6E1D3B62ull, 0xF320AD74ull,
				0x8EB1C71Eull, 0xBE8B0537ull, 0xAA87CA22ull };
static u32 nist_p384_y[] = { 0x90EA0E5Full, 0x7A431D7Cull, 0x1d7e819dull,
				0x0A60B1CEull, 0xB5F0B8C0ull, 0xE9DA3113ull,
				0x289A147Cull, 0xF8F41DBDull, 0x9292DC29ull,
				0x5D9E98BFull, 0x96262C6Full, 0x3617DE4Aull };
static u32 nist_p384_p[] = { 0xFFFFFFFFull, 0x00000000ull, 0x00000000ull,
				0xFFFFFFFFull, 0xFFFFFFFEull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull };
static u32 nist_p384_n[] = { 0xCCC52973ull, 0xECEC196Aull, 0x48B0A77Aull,
				0x581A0DB2ull, 0xF4372DDFull, 0xC7634D81ull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull };
static u32 nist_p384_a[] = { 0xFFFFFFFCull, 0x00000000ull, 0x00000000ull,
				0xFFFFFFFFull, 0xFFFFFFFEull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull };

static struct tegra_se_ecc_curve curve_p384 = {
	.name = "NIST_P-384",
	.g = {
		.x = nist_p384_x,
		.y = nist_p384_y,
	},
	.p = nist_p384_p,
	.n = nist_p384_n,
	.a = nist_p384_a,
	.nbytes = 48,
	.mode = SE_ELP_OP_MODE_ECC384,
};

/* NIST P-521 */
static u32 nist_p521_x[] = { 0xBD660000ull, 0x7E31C2E5ull, 0x429BF97Eull,
				0xB3C1856Aull, 0xA8DE3348ull, 0xC127A2FFull,
				0x5928FE1Dull, 0x5E77EFE7ull, 0x3DBAA14Bull,
				0xAF606B4Dull, 0xB521F828ull, 0x8139053Full,
				0xB4429C64ull, 0xCB662395ull, 0xE9CD9E3Eull,
				0x06B70404ull, 0x00C6858Eull };
static u32 nist_p521_y[] = { 0x66500000ull, 0x94769FD1ull, 0xC24088BEull,
				0x7086A272ull, 0x0761353Cull, 0xB9013FADull,
				0x2640C550ull, 0x72995EF4ull, 0x662C97EEull,
				0xBD17273Eull, 0x446817AFull, 0x4449579Bull,
				0x1BD998F5ull, 0x5FB42C7Dull, 0xC0045C8Aull,
				0x6A789A3Bull, 0x01183929ull };
static u32 nist_p521_p[] = { 0xFFFF0000ull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0x01FFFFFFull };
static u32 nist_p521_n[] = { 0x64090000ull, 0xB71E9138ull, 0x47AEBB6Full,
				0xC9B8899Cull, 0xA5D03BB5ull, 0x0148F709ull,
				0x966B7FCCull, 0x8783BF2Full, 0xFFFA5186ull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0x01FFFFFFull };
static u32 nist_p521_a[] = { 0xFFFC0000ull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
				0xFFFFFFFFull, 0x01FFFFFFull };

static struct tegra_se_ecc_curve curve_p521 = {
	.name = "NIST_P-521",
	.g = {
		.x = nist_p521_x,
		.y = nist_p521_y,
	},
	.p = nist_p521_p,
	.n = nist_p521_n,
	.a = nist_p521_a,
	.nbytes = 68,
	.mode = SE_ELP_OP_MODE_ECC521,
};

/* BrainPool P-256 */
static u32 bp_p256_x[] = { 0x9ACE3262ull, 0x3A4453BDull, 0xE3BD23C2ull,
				0xB9DE27E1ull, 0xFC81B7AFull, 0x2C4B482Full,
				0xCB7E57CBull, 0x8BD2AEB9ull };

static u32 bp_p256_y[] = { 0x2F046997ull, 0x5C1D54C7ull, 0x2DED8E54ull,
				0xC2774513ull, 0x14611DC9ull, 0x97F8461Aull,
				0xC3DAC4FDull, 0x547EF835ull };

static u32 bp_p256_p[] = { 0x1F6E5377ull, 0x2013481Dull, 0xD5262028ull,
				0x6E3BF623ull, 0x9D838D72ull, 0x3E660A90ull,
				0xA1EEA9BCull, 0xA9FB57DBull };

static u32 bp_p256_n[] = { 0x974856A7ull, 0x901E0E82ull, 0xB561A6F7ull,
				0x8C397AA3ull, 0x9D838D71ull, 0x3E660A90ull,
				0xA1EEA9BCull, 0xA9FB57DBull };

static u32 bp_p256_a[] = { 0xF330B5D9ull, 0xE94A4B44ull, 0x26DC5C6Cull,
				0xFB8055C1ull, 0x417AFFE7ull, 0xEEF67530ull,
				0xFC2C3057ull, 0x7D5A0975ull };

static struct tegra_se_ecc_curve bpcurve_p256 = {
	.name = "BRAINPOOL_P-256",
	.g = {
		.x = bp_p256_x,
		.y = bp_p256_y,
	},
	.p = bp_p256_p,
	.n = bp_p256_n,
	.a = bp_p256_a,
	.nbytes = 32,
	.mode = SE_ELP_OP_MODE_ECC256,
};

static u32 c256_x[] = { 0x00000009ull, 0x00000000ull, 0x00000000ull,
			0x00000000ull, 0x00000000ull, 0x00000000ull,
			0x00000000ull, 0x00000000ull };

static u32 c256_p[] = { 0xFFFFFFEDull, 0xFFFFFFFFull, 0xFFFFFFFFull,
			0xFFFFFFFFull, 0xFFFFFFFFull, 0xFFFFFFFFull,
			0xFFFFFFFFull, 0x7FFFFFFFull };

static u32 c256_k[] = { 0x0001DB42ull, 0x00000000ull, 0x00000000ull,
			0x00000000ull, 0x00000000ull, 0x00000000ull,
			0x00000000ull, 0x00000000ull };

static u32 c256_n[] = { 0x5CF5D3EDull, 0x5812631Aull, 0xA2F79CD6ull,
			0x14DEF9DEull, 0x00000000ull, 0x00000000ull,
			0x00000000ull, 0x10000000ull };

static struct tegra_se_ecc_curve curve_c256 = {
	.name = "C25519",
	.g = {
		.x = c256_x,
	},
	.p = c256_p,
	.n = c256_n,
	.a = c256_k,
	.nbytes = 32,
	.mode = SE_ELP_OP_MODE_ECC256,
};

static u32 ed25519_d[] = { 0x135978A3ull, 0x75EB4DCAull, 0x4141D8ABull,
				0x00700A4Dull, 0x7779E898ull, 0x8CC74079ull,
				0x2B6FFE73ull, 0x52036CEEull };
static u32 ed25519_q[] = { 0x5CF5D3EDull, 0x5812631Aull, 0xA2F79CD6ull,
				0x14DEF9DEull, 0x00000000ull, 0x00000000ull,
				0x00000000ull, 0x10000000ull };
static u32 ed25519_x[] = { 0x8f25d51aull, 0xc9562d60ull, 0x9525a7b2ull,
			0x692cc760ull, 0xfdd6dc5cull, 0xc0a4e231ull,
			0xcd6e53feull, 0x216936d3ull };
static u32 ed25519_y[] = { 0x66666658ull, 0x66666666ull, 0x66666666ull,
			0x66666666ull, 0x66666666ull, 0x66666666ull,
			0x66666666ull, 0x66666666ull };
static u32 ed25519_p[] = { 0xffffffedull, 0xffffffffull, 0xffffffffull,
				0xffffffffull, 0xffffffffull, 0xffffffffull,
				0xffffffffull, 0x7fffffffull };
static u32 ed25519_p_2[] = { 0xffffffebull, 0xffffffffull, 0xffffffffull,
				0xffffffffull, 0xffffffffull, 0xffffffffull,
				0xffffffffull, 0x7fffffffull };
static u32 ed25519_p_5inv8[] = { 0xfffffffdull, 0xffffffffull, 0xffffffffull,
				0xffffffffull, 0xffffffffull, 0xffffffffull,
				0xffffffffull, 0x0fffffffull };
static u32 ed25519_p_3inv8[] = { 0xfffffffeull, 0xffffffffull, 0xffffffffull,
				0xffffffffull, 0xffffffffull, 0xffffffffull,
				0xffffffffull, 0x0fffffffull };
static  u32 ed25519_p_1inv4[] = { 0x4A0EA0B0ull, 0xC4EE1B27ull, 0xAD2FE478ull,
				0x2F431806ull, 0x3DFBD7A7ull, 0x2B4D0099ull,
				0x4FC1DF0Bull, 0x2B832480ull };

static  u32 ed25519_const[] = { 0x00000008ull, 0x00000000ull, 0x00000000ull,
				0x00000000ull, 0x00000000ull, 0x00000000ull,
				0x00000000ull, 0x00000000ull };

static struct tegra_se_ecc_curve edcurve_p256 = {
	.name = "ED25519",
	.g = {
		.x = ed25519_x,
		.y = ed25519_y,
	},
	.p = ed25519_p,
	.p2 = ed25519_p_2,
	.p5inv8 = ed25519_p_5inv8,
	.p3inv8 = ed25519_p_3inv8,
	.p1inv4 = ed25519_p_1inv4,
	.n = ed25519_q,
	.a = ed25519_d,
	.vec = ed25519_const,
	.nbytes = 32,
	.mode = SE_ELP_OP_MODE_ECC256,
};

#define TEGRA_SE_PKA1_KEYSLOT_COUNT	4

#define TEGRA_SE_PKA1_FLAGS_OFFSET			0xC024
#define TEGRA_SE_PKA1_FLAGS_FLAG_F0_SHIFT		4
#define TEGRA_SE_PKA1_FLAGS_FLAG_F0(x)	\
				(x << TEGRA_SE_PKA1_FLAGS_FLAG_F0_SHIFT)
#define TEGRA_SE_PKA1_FLAGS_FLAG_F1_SHIFT		5
#define TEGRA_SE_PKA1_FLAGS_FLAG_F1(x)	\
				(x << TEGRA_SE_PKA1_FLAGS_FLAG_F1_SHIFT)
#define TEGRA_SE_PKA1_FLAGS_FLAG_F3_SHIFT		7
#define TEGRA_SE_PKA1_FLAGS_FLAG_F3(x)	\
				(x << TEGRA_SE_PKA1_FLAGS_FLAG_F3_SHIFT)
#define TEGRA_SE_PKA1_FLAGS_FLAG_ZERO_SHIFT		0
#define TEGRA_SE_PKA1_FLAGS_FLAG_ZERO(x)	\
				(x << TEGRA_SE_PKA1_FLAGS_FLAG_ZERO_SHIFT)

#define TEGRA_SE_PKA1_FSTACK_PTR_OFFSET		0xC010

#define ELP_ENABLE		1
#define ELP_DISABLE		0
#define ELP_FALSE		0
#define ELP_TRUE		1

#define TEGRA_SE_PKA1_CTRL_ERROR_CAPTURE_OFFSET		0x8134

#define TEGRA_SE_PKA1_CTRL_SE_INTR_STATUS_OFFSET	0x813c
#define TEGRA_SE_PKA1_CTRL_SE_INTR_STATUS_ERR_SHIFT	16
#define TEGRA_SE_PKA1_CTRL_SE_INTR_STATUS_ERR(x)	\
			(x << TEGRA_SE_PKA1_CTRL_SE_INTR_STATUS_ERR_SHIFT)
#define TEGRA_SE_PKA1_CTRL_SE_INTR_STATUS_EIP1_TRNG_SHIFT	9
#define TEGRA_SE_PKA1_CTRL_SE_INTR_STATUS_EIP1_TRNG(x)	\
			(x << TEGRA_SE_PKA1_CTRL_SE_INTR_STATUS_EIP1_TRNG_SHIFT)
#define TEGRA_SE_PKA1_CTRL_SE_INTR_STATUS_EIP0_PKA1_SHIFT	8
#define TEGRA_SE_PKA1_CTRL_SE_INTR_STATUS_EIP0_PKA1(x)	\
			(x << TEGRA_SE_PKA1_CTRL_SE_INTR_STATUS_EIP0_PKA1_SHIFT)

#define TEGRA_SE_PKA1_CTRL_SE_INTR_MASK_OFFSET		0x8140
#define TEGRA_SE_PKA1_CTRL_SE_INTR_MASK_EIP1_TRNG_SHIFT	9
#define TEGRA_SE_PKA1_CTRL_SE_INTR_MASK_EIP1_TRNG(x) \
			(x << TEGRA_SE_PKA1_CTRL_SE_INTR_MASK_EIP1_TRNG_SHIFT)
#define TEGRA_SE_PKA1_CTRL_SE_INTR_MASK_EIP0_PKA_SHIFT	8
#define TEGRA_SE_PKA1_CTRL_SE_INTR_MASK_EIP0_PKA(x) \
			(x << TEGRA_SE_PKA1_CTRL_SE_INTR_MASK_EIP0_PKA_SHIFT)

#define TEGRA_SE_PKA1_INT_ENABLE_OFFSET			0xC040
#define TEGRA_SE_PKA1_INT_ENABLE_IE_IRQ_EN_SHIFT	30
#define TEGRA_SE_PKA1_INT_ENABLE_IE_IRQ_EN(x)	\
			(x << TEGRA_SE_PKA1_INT_ENABLE_IE_IRQ_EN_SHIFT)

#define TEGRA_SE_RNG1_INT_EN_OFFSET	0xFC0
#define TEGRA_SE_RNG1_IE_OFFSET		0xF10

#define TEGRA_SE_RNG1_STATUS_OFFSET		0xF0C
#define TEGRA_SE_RNG1_STATUS_BUSY_SHIFT	31
#define TEGRA_SE_RNG1_STATUS_BUSY(x)		\
		(x << TEGRA_SE_RNG1_STATUS_BUSY_SHIFT)

#define TEGRA_SE_RNG1_STATUS_SECURE_SHIFT		6
#define STATUS_SECURE			1
#define STATUS_PROMISCUOUS		0
#define TEGRA_SE_RNG1_STATUS_SECURE(x)	\
		(x << TEGRA_SE_RNG1_STATUS_SECURE_SHIFT)

#define TEGRA_SE_RNG1_ISTATUS_OFFSET	0xF14
#define ISTATUS_ACTIVE			1
#define ISTATUS_CLEAR			0

#define TEGRA_SE_RNG1_ISTATUS_NOISE_RDY_SHIFT	2
#define TEGRA_SE_RNG1_ISTATUS_NOISE_RDY(x)		\
			(x << TEGRA_SE_RNG1_ISTATUS_NOISE_RDY_SHIFT)
#define TEGRA_SE_RNG1_ISTATUS_DONE_SHIFT		4
#define TEGRA_SE_RNG1_ISTATUS_DONE(x)		\
				(x << TEGRA_SE_RNG1_ISTATUS_DONE_SHIFT)
#define TEGRA_SE_RNG1_ISTATUS_KAT_COMPLETED_SHIFT	1
#define TEGRA_SE_RNG1_ISTATUS_KAT_COMPLETED(x)	\
			(x << TEGRA_SE_RNG1_ISTATUS_KAT_COMPLETED_SHIFT)
#define TEGRA_SE_RNG1_ISTATUS_ZEROIZED_SHIFT		0
#define TEGRA_SE_RNG1_ISTATUS_ZEROIZED(x)		\
			(x << TEGRA_SE_RNG1_ISTATUS_ZEROIZED_SHIFT)

#define TEGRA_SE_RNG1_INT_STATUS_OFFSET		0xFC4
#define STATUS_ACTIVE			1
#define STATUS_CLEAR			0
#define TEGRA_SE_RNG1_INT_STATUS_EIP0_SHIFT		8
#define TEGRA_SE_RNG1_INT_STATUS_EIP0(x)		\
			(x << TEGRA_SE_RNG1_INT_STATUS_EIP0_SHIFT)

#define TEGRA_SE_RNG1_NPA_DATA0_OFFSET	0xF34

#define TEGRA_SE_RNG1_SE_MODE_OFFSET		0xF04
#define RNG1_MODE_ADDIN_PRESENT_SHIFT		4
#define RNG1_MODE_ADDIN_PRESENT			\
				(ELP_TRUE << RNG1_MODE_ADDIN_PRESENT_SHIFT)
#define RNG1_MODE_SEC_ALG_SHIFT			0
#define RNG1_MODE_SEC_ALG			\
					(ELP_TRUE << RNG1_MODE_SEC_ALG_SHIFT)
#define RNG1_MODE_PRED_RESIST_SHIFT			3
#define RNG1_MODE_PRED_RESIST			\
				(ELP_TRUE << RNG1_MODE_PRED_RESIST_SHIFT)

#define TEGRA_SE_RNG1_SE_SMODE_OFFSET		0xF08
#define TEGRA_SE_RNG1_SE_SMODE_SECURE_SHIFT	1
#define SMODE_SECURE			1
#define SMODE_PROMISCUOUS		0
#define TEGRA_SE_RNG1_SE_SMODE_SECURE(x)		\
				(x << TEGRA_SE_RNG1_SE_SMODE_SECURE_SHIFT)

#define TEGRA_SE_RNG1_SE_SMODE_NONCE_SHIFT	0
#define TEGRA_SE_RNG1_SE_SMODE_NONCE(x)	\
				(x << TEGRA_SE_RNG1_SE_SMODE_NONCE_SHIFT)

#define TEGRA_SE_RNG1_RAND0_OFFSET		0xF24
#define TEGRA_SE_RNG1_ALARMS_OFFSET		0xF18

#define TEGRA_SE_PKA1_STATUS_OFFSET			0xC020
#define TEGRA_SE_PKA1_STATUS_IRQ_STAT_SHIFT		30
#define TEGRA_SE_PKA1_STATUS_IRQ_STAT(x)	\
			(x << TEGRA_SE_PKA1_STATUS_IRQ_STAT_SHIFT)

#define TEGRA_SE_PKA1_CTRL_STATUS_OFFSET		0x810C
#define TEGRA_SE_PKA1_CTRL_SE_STATUS_SHIFT		0
#define SE_STATUS_BUSY					1
#define SE_STATUS_IDLE					0
#define TEGRA_SE_PKA1_CTRL_PKA_STATUS_SHIFT		1
#define PKA_STATUS_BUSY					1
#define PKA_STATUS_IDLE					0
#define TEGRA_SE_PKA1_CTRL_PKA_STATUS(x)	\
				(x << TEGRA_SE_PKA1_CTRL_PKA_STATUS_SHIFT)
#define TEGRA_SE_PKA1_CTRL_SE_STATUS(x)	\
				(x << TEGRA_SE_PKA1_CTRL_SE_STATUS_SHIFT)

#define TEGRA_SE_PKA1_RETURN_CODE_OFFSET			0xC008
#define TEGRA_SE_PKA1_RETURN_CODE_STOP_REASON_ABNORMAL	0xFF
#define TEGRA_SE_PKA1_RETURN_CODE_STOP_REASON_SHIFT		16
#define TEGRA_SE_PKA1_RETURN_CODE_STOP_REASON(x)	\
			(x << TEGRA_SE_PKA1_RETURN_CODE_STOP_REASON_SHIFT)

#define TEGRA_SE_PKA1_MUTEX_WATCHDOG_OFFSET	0x8110
#define TEGRA_SE_PKA1_MUTEX_OFFSET		0x8114
#define TEGRA_SE_PKA1_MUTEX_RELEASE_OFFSET	0x8118

#define TEGRA_SE_PKA1_MUTEX_TIMEOUT_ACTION_OFFSET	0x8128
#define TEGRA_SE_PKA1_MUTEX_TIMEOUT_ACTION		0x2

#define TEGRA_SE_RNG1_MUTEX_WATCHDOG_OFFSET		0xFD0
#define TEGRA_SE_RNG1_MUTEX_OFFSET			0xFD8
#define TEGRA_SE_RNG1_MUTEX_TIMEOUT_ACTION		0x2
#define TEGRA_SE_RNG1_MUTEX_TIMEOUT_ACTION_OFFSET	0xFD4

#define TEGRA_SE_RNG1_CTRL_OFFSET		0xF00

#define TEGRA_SE_PKA1_CTRL_OFFSET		0xC000
#define TEGRA_SE_PKA1_CTRL_PKA_CONTROL_OFFSET	0x8108

#define TEGRA_SE_PKA1_CTRL_M521_MODE_SHIFT	16
#define M521_MODE_VAL				0x9
#define NORMAL_MODE_VAL				0x0
#define TEGRA_SE_PKA1_CTRL_M521_MODE(x)		\
			(x << TEGRA_SE_PKA1_CTRL_M521_MODE_SHIFT)

#define TEGRA_SE_PKA1_CTRL_GO_SHIFT		31
#define TEGRA_SE_PKA1_CTRL_GO_START		1
#define TEGRA_SE_PKA1_CTRL_GO_NOP		0
#define TEGRA_SE_PKA1_CTRL_GO(x)	\
			(x << TEGRA_SE_PKA1_CTRL_GO_SHIFT)

#define TEGRA_SE_PKA1_CTRL_BASE_RADIX_SHIFT	8
#define TEGRA_SE_PKA1_CTRL_BASE_256		2
#define TEGRA_SE_PKA1_CTRL_BASE_512		3
#define TEGRA_SE_PKA1_CTRL_BASE_1024		4
#define TEGRA_SE_PKA1_CTRL_BASE_2048		5
#define TEGRA_SE_PKA1_CTRL_BASE_4096		6
#define TEGRA_SE_PKA1_CTRL_BASE_RADIX(x)	\
				(x << TEGRA_SE_PKA1_CTRL_BASE_RADIX_SHIFT)

#define TEGRA_SE_PKA1_CTRL_PARTIAL_RADIX_SHIFT	0

#define PKA1_OP_SIZE_256	256
#define PKA1_OP_SIZE_512	512
#define PKA1_OP_SIZE_1024	1024
#define PKA1_OP_SIZE_2048	2048
#define PKA1_OP_SIZE_4096	4096

#define TEGRA_SE_PKA1_CTRL_PARTIAL_RADIX(x)	\
				(x << TEGRA_SE_PKA1_CTRL_PARTIAL_RADIX_SHIFT)

#define TEGRA_SE_PKA1_TRNG_CTRL_OFFSET			0xBF00
#define TEGRA_SE_PKA1_TRNG_CTRL_CMD_SHIFT		0
#define TEGRA_SE_PKA1_TRNG_CTRL_CMD(x)	\
			(x << TEGRA_SE_PKA1_TRNG_CTRL_CMD_SHIFT)

#define TEGRA_SE_PKA1_TRNG_SMODE_OFFSET			0xBF0C
#define TEGRA_SE_PKA1_TRNG_SMODE_SECURE_SHIFT		8
#define TEGRA_SE_PKA1_TRNG_SMODE_SECURE(x)	\
				(x << TEGRA_SE_PKA1_TRNG_SMODE_SECURE_SHIFT)
#define TEGRA_SE_PKA1_TRNG_SMODE_NONCE_SHIFT			2
#define TEGRA_SE_PKA1_TRNG_SMODE_NONCE(x)	\
				(x << TEGRA_SE_PKA1_TRNG_SMODE_NONCE_SHIFT)

#define TEGRA_SE_PKA1_TRNG_IE_OFFSET			0xBF10
#define TEGRA_SE_PKA1_TRNG_IE_RAND_RDY_EN_SHIFT		0
#define TEGRA_SE_PKA1_TRNG_IE_RAND_RDY_EN(x) \
			(x << TEGRA_SE_PKA1_TRNG_IE_RAND_RDY_EN_SHIFT)
#define TEGRA_SE_PKA1_TRNG_IE_GLBL_EN_SHIFT		31
#define TEGRA_SE_PKA1_TRNG_IE_GLBL_EN(x) \
			(x << TEGRA_SE_PKA1_TRNG_IE_GLBL_EN_SHIFT)

#define TEGRA_SE_PKA1_TRNG_ISTAT_OFFSET			0xBF14
#define TEGRA_SE_PKA1_TRNG_ISTAT_RAND_RDY_SHIFT		0
#define TEGRA_SE_PKA1_TRNG_ISTAT_RAND_RDY(x)	\
				(x << TEGRA_SE_PKA1_TRNG_ISTAT_RAND_RDY_SHIFT)

#define TEGRA_SE_PKA1_TRNG_RAND0_OFFSET			0xBF20
#define TEGRA_SE_PKA1_TRNG_RAND1_OFFSET			0xBF24
#define TEGRA_SE_PKA1_TRNG_RAND2_OFFSET			0xBF28
#define TEGRA_SE_PKA1_TRNG_RAND3_OFFSET			0xBF2c
#define TEGRA_SE_PKA1_TRNG_RAND4_OFFSET			0xBF30
#define TEGRA_SE_PKA1_TRNG_RAND5_OFFSET			0xBF34
#define TEGRA_SE_PKA1_TRNG_RAND6_OFFSET			0xBF38
#define TEGRA_SE_PKA1_TRNG_RAND7_OFFSET			0xBF3c

#define TEGRA_SE_PKA1_CTRL_CONTROL_OFFSET			0x8104
#define TEGRA_SE_PKA1_CTRL_CONTROL_AUTO_RESEED_SHIFT		0
#define TEGRA_SE_PKA1_CTRL_CONTROL_AUTO_RESEED(x)	\
			(x << TEGRA_SE_PKA1_CTRL_CONTROL_AUTO_RESEED_SHIFT)
#define TEGRA_SE_PKA1_CTRL_CONTROL_LOAD_KEY_SHIFT		2
#define TEGRA_SE_PKA1_CTRL_CONTROL_LOAD_KEY(x)	\
			(x << TEGRA_SE_PKA1_CTRL_CONTROL_LOAD_KEY_SHIFT)

#define TEGRA_SE_PKA1_CTRL_CONTROL_KEYSLOT_SHIFT	16
#define TEGRA_SE_PKA1_CTRL_CONTROL_KEYSLOT_0		0x00
#define TEGRA_SE_PKA1_CTRL_CONTROL_KEYSLOT_1		0x01
#define TEGRA_SE_PKA1_CTRL_CONTROL_KEYSLOT_2		0x02
#define TEGRA_SE_PKA1_CTRL_CONTROL_KEYSLOT_3		0x03
#define TEGRA_SE_PKA1_CTRL_CONTROL_KEYSLOT(x)	\
			(x << TEGRA_SE_PKA1_CTRL_CONTROL_KEYSLOT_SHIFT)

#define TEGRA_SE_PKA1_TRNG_STATUS_OFFSET	0xBF04
#define TEGRA_SE_PKA1_TRNG_STATUS_SECURE_SHIFT	8
#define TEGRA_SE_PKA1_TRNG_STATUS_SECURE(x)	\
				(x << TEGRA_SE_PKA1_TRNG_STATUS_SECURE_SHIFT)

#define TEGRA_SE_PKA1_TRNG_STATUS_NONCE_SHIFT	2
#define TEGRA_SE_PKA1_TRNG_STATUS_NONCE(x)	\
				(x << TEGRA_SE_PKA1_TRNG_STATUS_NONCE_SHIFT)

#define TEGRA_SE_PKA1_TRNG_STATUS_SEEDED_SHIFT	9
#define TEGRA_SE_PKA1_TRNG_STATUS_SEEDED(x)	\
				(x << TEGRA_SE_PKA1_TRNG_STATUS_SEEDED_SHIFT)

#define TEGRA_SE_PKA1_TRNG_STATUS_LAST_RESEED_SHIFT		16
#define TRNG_LAST_RESEED_HOST					0
#define TRNG_LAST_RESEED_NONCE					3
#define TRNG_LAST_RESEED_RESEED					4
#define TRNG_LAST_RESEED_UNSEEDED				7
#define TEGRA_SE_PKA1_TRNG_STATUS_LAST_RESEED(x)	\
			(x << TEGRA_SE_PKA1_TRNG_STATUS_LAST_RESEED_SHIFT)

#define SE_PKA1_RSA_MOD_SHIFT	16
#define SE_PKA1_RSA_EXP_BITS	0xFFFF

#define TEGRA_SE_PKA1_RSA512_INPUT_SIZE		64
#define TEGRA_SE_PKA1_RSA768_INPUT_SIZE		96
#define TEGRA_SE_PKA1_RSA1024_INPUT_SIZE	128
#define TEGRA_SE_PKA1_RSA1536_INPUT_SIZE	192
#define TEGRA_SE_PKA1_RSA2048_INPUT_SIZE	256
#define TEGRA_SE_PKA1_RSA3072_INPUT_SIZE	384
#define TEGRA_SE_PKA1_RSA4096_INPUT_SIZE	512

#define TEGRA_SE_PKA1_PRG_ENTRY_OFFSET	0xC004

#define TEGRA_SE_PKA1_RSA_M_PRG_ENTRY_VAL		0x10
#define TEGRA_SE_PKA1_RSA_R2_PRG_ENTRY_VAL		0x12
#define TEGRA_SE_PKA1_RSA_RINV_PRG_ENTRY_VAL		0x11

#define TEGRA_SE_PKA1_RSA_MOD_EXP_PRG_ENTRY_VAL		0x14

#define ECC_ECPV_PRG_ENTRY_VAL			0x1E
#define ECC_POINT_ADD_PRG_ENTRY_VAL		0x1C
#define ECC_POINT_MUL_PRG_ENTRY_VAL		0x19
#define ECC_POINT_DOUBLE_PRG_ENTRY_VAL		0x1A
#define ECC_SHAMIR_TRICK_PRG_ENTRY_VAL		0x23
#define TEGRA_SE_PKA1_C25519_PMUL_PRG_ENTRY_VAL		0x2E
#define TEGRA_SE_PKA1_ED25519_PMUL_PRG_ENTRY_VAL	0x2B
#define TEGRA_SE_PKA1_ED25519_SHAMIR_PRG_ENTRY_VAL	0x33

#define ECC_WEIERSTRASS_ECPV_PRG_ENTRY_VAL               0x27
#define ECC_WEIERSTRASS_POINT_ADD_PRG_ENTRY_VAL          0x26
#define ECC_WEIERSTRASS_POINT_MUL_PRG_ENTRY_VAL          0x24
#define ECC_WEIERSTRASS_POINT_DOUBLE_PRG_ENTRY_VAL       0x25
#define ECC_WEIERSTRASS_SHAMIR_TRICK_PRG_ENTRY_VAL       0x2A

#define EDDSA_KEY_VEC_SIZE	(1 + 1 + 32) /* version + curve_id + key_data */

#define PKA1_ADDR_OFFSET		0xC000

#define PKA1_BANK_START_A	(PKA1_ADDR_OFFSET + 0x400)
#define PKA1_BANK_START_B	(PKA1_ADDR_OFFSET + 0x800)
#define PKA1_BANK_START_C	(PKA1_ADDR_OFFSET + 0xC00)
#define PKA1_BANK_START_D	(PKA1_ADDR_OFFSET + 0x1000)

#define BANK_A	0
#define BANK_B	1
#define BANK_C	2
#define BANK_D	3

#define TEGRA_SE_PKA1_RSA_MSG_BANK		BANK_A
#define TEGRA_SE_PKA1_RSA_MSG_ID		0
#define TEGRA_SE_PKA1_RSA_EXP_BANK		BANK_D
#define TEGRA_SE_PKA1_RSA_EXP_ID		2
#define TEGRA_SE_PKA1_RSA_RESULT_BANK	BANK_A
#define TEGRA_SE_PKA1_RSA_RESULT_ID		0

#define	TEGRA_SE_PKA1_M_BANK			BANK_D
#define	TEGRA_SE_PKA1_M_ID			1
#define TEGRA_SE_PKA1_RINV_BANK		BANK_C
#define TEGRA_SE_PKA1_RINV_ID		0
#define TEGRA_SE_PKA1_R2_BANK		BANK_D
#define TEGRA_SE_PKA1_R2_ID			3
#define TEGRA_SE_PKA1_MOD_BANK		BANK_D
#define TEGRA_SE_PKA1_MOD_ID			0

#define TEGRA_SE_PKA1_ECC_A_BANK	BANK_A
#define TEGRA_SE_PKA1_ECC_A_ID		6
#define TEGRA_SE_PKA1_ECC_B_BANK	BANK_A
#define TEGRA_SE_PKA1_ECC_B_ID		7
#define TEGRA_SE_PKA1_ECC_N_BANK	0
#define TEGRA_SE_PKA1_ECC_N_ID		0
#define TEGRA_SE_PKA1_ECC_XP_BANK	BANK_A
#define TEGRA_SE_PKA1_ECC_XP_ID		2
#define TEGRA_SE_PKA1_ECC_YP_BANK	BANK_B
#define TEGRA_SE_PKA1_ECC_YP_ID		2
#define TEGRA_SE_PKA1_ECC_XQ_BANK	BANK_A
#define TEGRA_SE_PKA1_ECC_XQ_ID		3
#define TEGRA_SE_PKA1_ECC_YQ_BANK	BANK_B
#define TEGRA_SE_PKA1_ECC_YQ_ID		3
#define TEGRA_SE_PKA1_ECC_K_BANK	BANK_D
#define TEGRA_SE_PKA1_ECC_K_ID		7
#define TEGRA_SE_PKA1_C25519_K_BANK	BANK_D
#define TEGRA_SE_PKA1_C25519_K_ID	2
#define TEGRA_SE_PKA1_ED25519_D_BANK	BANK_C
#define TEGRA_SE_PKA1_ED25519_D_ID	5
#define TEGRA_SE_PKA1_ED25519_K_BANK	BANK_A
#define TEGRA_SE_PKA1_ED25519_K_ID	5
#define TEGRA_SE_PKA1_ED25519_L_BANK	BANK_B
#define TEGRA_SE_PKA1_ED25519_L_ID	5

#define PKA1_C25519_FORMAT_KEY_MASK_0	0xfffffff8
#define PKA1_C25519_FORMAT_KEY_MASK_1	0x40000000
#define PKA1_C25519_FORMAT_KEY_MASK_2	0x7fffffff
#define PKA1_POINT_ENCODE_Y_MASK	0x7fffffff
#define PKA1_POINT_ENCODE_X_MASK	0x1
#define PKA1_POINT_ZERO_INDEX_SHIFT	31

#define TEGRA_SE_PKA1_ENTRY_MODMULT	0xa
#define TEGRA_SE_PKA1_ENTRY_MODADD	0xb
#define TEGRA_SE_PKA1_ENTRY_MODSUB	0xc
#define TEGRA_SE_PKA1_ENTRY_MODDIV	0xd
#define TEGRA_SE_PKA1_ENTRY_MODINV	0xe
#define TEGRA_SE_PKA1_ENTRY_REDUCE	0xf
#define TEGRA_SE_PKA1_ENTRY_C25519_MOD_EXP	0x30
#define TEGRA_SE_PKA1_ENTRY_C25519_MOD_SQR	0x32
#define TEGRA_SE_PKA1_ENTRY_BIT_SERIAL_DP_MOD_REDUCE	0x17
#define TEGRA_SE_PKA1_ENTRY_NON_MOD_MULT	0x13
#define TEGRA_SE_PKA1_ENTRY_C25519_MOD_MULT	0x31

#define TEGRA_SE_PKA1_KEYSLOT_ADDR_OFFSET(i)		(0x00008800 + ((i) * 4))
#define TEGRA_SE_PKA1_KEYSLOT_DATA_OFFSET(i)		(0x00008810 + ((i) * 4))

#define TEGRA_SE_PKA1_KEYSLOT_ADDR_AUTO_INC_SHIFT	31
#define TEGRA_SE_PKA1_KEYSLOT_ADDR_AUTO_INC_SET	1
#define TEGRA_SE_PKA1_KEYSLOT_ADDR_AUTO_INC_CLEAR	0
#define TEGRA_SE_PKA1_KEYSLOT_ADDR_AUTO_INC(x)	\
			(x << TEGRA_SE_PKA1_KEYSLOT_ADDR_AUTO_INC_SHIFT)

#define TEGRA_SE_PKA1_KEYSLOT_ADDR_FIELD_SHIFT	8
#define TEGRA_SE_PKA1_KEYSLOT_ADDR_FIELD(x)	\
				(x << TEGRA_SE_PKA1_KEYSLOT_ADDR_FIELD_SHIFT)

#define TEGRA_SE_PKA1_KEYSLOT_ADDR_WORD_SHIFT	0
#define TEGRA_SE_PKA1_KEYSLOT_ADDR_WORD(x)	\
				(x << TEGRA_SE_PKA1_KEYSLOT_ADDR_WORD_SHIFT)

#endif /* _CRYPTO_TEGRA_SE_ELP_H */
