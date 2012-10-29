#ifndef _FLT_VALUES_H_
#define _FLT_VALUES_H_

#include <metaresc.h>

#ifdef HAVE_CONFIG_H
#include <mr_config.h>
#endif /* HAVE_CONFIG_H */
#ifdef HAVE_VALUES_H
#include <values.h>
#else  /* HAVE_VALUES_H */
#define FLT_MAX (0x1.fffffep+127)
#define FLT_MIN (0x1p-126)
#define FLT_EPSILON (0x1p-23)
#define DBL_MAX (0x1.fffffffffffffp+1023)
#define DBL_MIN (0x1p-1022)
#define DBL_EPSILON (0x1p-52)
#define LDBL_MAX (0x1.ffffffffffffffffp+16383)
#define LDBL_MIN (0x1p-16382)
#define LDBL_EPSILON (0x1p-64)
#endif /* HAVE_VALUES_H */

TYPEDEF_ENUM (sign_t, (PLUS, = 0), (MINUS, = 1))
TYPEDEF_ENUM (boolean_t, (_FALSE_, = 0), (_TRUE_, = 1))

TYPEDEF_STRUCT (ieee_754_float_t,
		BITFIELD (unsigned int, mantissa, :23),
		BITFIELD (unsigned int, exponent, :8),
		BITFIELD (sign_t, sign, :1))

TYPEDEF_STRUCT (ieee_754_float_nan_t,
		BITFIELD (unsigned int, mantissa, :22),
		BITFIELD (boolean_t, quiet_nan, :1),
		BITFIELD (unsigned int, exponent, :8),
		BITFIELD (sign_t, sign, :1))

TYPEDEF_UNION (ieee_float_t,
	       ANON_UNION (),
	       (ieee_754_float_t, ieee_754_float),
	       (ieee_754_float_nan_t, ieee_754_float_nan),
	       float _float,
	       END_ANON_UNION ("quiet_nan"),
	       BITFIELD (unsigned char, quiet_nan, :1, , .offset = 22 / 8, .param = { .bitfield_param = { .width = 1, .shift = 22 % 8, }, } ),
	       )

TYPEDEF_STRUCT (ieee_754_double_t,
		BITFIELD (unsigned int, mantissa1, :32),
		BITFIELD (unsigned int, mantissa0, :20),
		BITFIELD (unsigned int, exponent, :11),
		BITFIELD (sign_t, sign, :1))

TYPEDEF_STRUCT (ieee_754_double_nan_t,
		BITFIELD (unsigned int, mantissa1, :32),
		BITFIELD (unsigned int, mantissa0, :19),
		BITFIELD (boolean_t, quiet_nan, :1),
		BITFIELD (unsigned int, exponent, :11),
		BITFIELD (sign_t, sign, :1))

TYPEDEF_UNION (ieee_double_t,
	       ANON_UNION (),
	       double _double,
	       (ieee_754_double_t, ieee_754_double),
	       (ieee_754_double_nan_t, ieee_754_double_nan),
	       END_ANON_UNION ("quiet_nan"),
	       BITFIELD (unsigned char, quiet_nan, :1, , .offset = (32 + 19) / 8, .param = { .bitfield_param = { .width = 1, .shift = (32 + 19) % 8, }, } ),
	       )

TYPEDEF_STRUCT (ieee_854_long_double_t,
		BITFIELD (unsigned int, mantissa1, :32),
		BITFIELD (unsigned int, mantissa0, :32),
		BITFIELD (unsigned int, exponent, :15),
		BITFIELD (sign_t, sign, :1),
		BITFIELD (unsigned int, empty, :16))

TYPEDEF_STRUCT (ieee_854_long_double_nan_t,
		BITFIELD (unsigned int, mantissa1, :32),
		BITFIELD (unsigned int, mantissa0, :30),
		BITFIELD (boolean_t, quiet_nan, :1),
		BITFIELD (unsigned int, one, :1),
		BITFIELD (unsigned int, exponent, :15),
		BITFIELD (sign_t, sign, :1),
		BITFIELD (unsigned int, empty, :16))

TYPEDEF_UNION (ieee_long_double_t,
	       ANON_UNION (),
	       long double long_double,
	       (ieee_854_long_double_t, ieee_854_long_double),
	       (ieee_854_long_double_nan_t, ieee_854_long_double_nan),
	       END_ANON_UNION ("quiet_nan"),
	       BITFIELD (unsigned char, quiet_nan, :1, , .offset = (32 + 30) / 8, .param = { .bitfield_param = { .width = 1, .shift = (32 + 30) % 8, }, } ),
	       )
#endif /* _FLT_VALUES_H_ */
