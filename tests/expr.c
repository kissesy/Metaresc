#include <math.h>
#include <complex.h>

#include <check.h>
#include <metaresc.h>
#include <regression.h>

#define ASSERT_LOAD_EXPR(TYPE, VALUE)					\
  ck_assert_msg (((TYPE)(VALUE) == MR_LOAD_CINIT (TYPE, #VALUE)),	\
		 "restored value mismatched original for method CINIT on expression " #VALUE); \

#define ASSERT_LOAD_TYPE_SCM(TYPE, VALUE, RESULT)			\
  ck_assert_msg (((TYPE)(RESULT) == MR_LOAD_SCM (TYPE, VALUE)),		\
		 "restored value mismatched original for method SCM on expression " VALUE)

MR_START_TEST (parse_bool_true, "parse bool true = (0)") { ASSERT_LOAD_EXPR (bool, true); } END_TEST
MR_START_TEST (parse_int_zero, "parse int 1") { ASSERT_LOAD_EXPR (int, 1); } END_TEST
MR_START_TEST (parse_int_paren, "parse int x = (1)") { ASSERT_LOAD_EXPR (int, (1)); } END_TEST
MR_START_TEST (parse_unary_minus, "parse int x = (1 + -1)") { ASSERT_LOAD_EXPR (int, (1 + -1)); } END_TEST
MR_START_TEST (parse_int_sum, "parse int x = 1 + 1") { ASSERT_LOAD_EXPR (int, 1 + 1); } END_TEST
MR_START_TEST (parse_complex_sum, "parse float complex x = 1 + 1i") { ASSERT_LOAD_EXPR (complex float, 1 + 1i); } END_TEST
MR_START_TEST (parse_float_op1, "parse float x = (1. + 1i) / 2") { ASSERT_LOAD_EXPR (float, (1. + 1i) / 2); } END_TEST
MR_START_TEST (parse_float_op2, "parse float x = M_PI + 2 * M_E") { ASSERT_LOAD_EXPR (float, 3.14159265358979323846 + 2 * 2.7182818284590452354); } END_TEST
MR_START_TEST (parse_bits_op1, "parse int x = 7 ^ 5 * 8") { ASSERT_LOAD_EXPR (int, 7 ^ 5 * 8); } END_TEST
MR_START_TEST (parse_bits_op2, "parse int x = 2 | 5 * 8") { ASSERT_LOAD_EXPR (int, 2 | 5 * 8); } END_TEST

MR_START_TEST (scm_add_3args, "parse int ( + 1 2 3)") { ASSERT_LOAD_TYPE_SCM (int, "( + 1 2 3)", 6); } END_TEST
MR_START_TEST (scm_add_1arg, "parse int ( + 1)") { ASSERT_LOAD_TYPE_SCM (int, "( + 1)", 1); } END_TEST
MR_START_TEST (scm_add_0args, "parse int ( + )") { ASSERT_LOAD_TYPE_SCM (int, "( + )", 0); } END_TEST
MR_START_TEST (scm_sub_3args, "parse int ( - 1 2 3)") { ASSERT_LOAD_TYPE_SCM (int, "( - 1 2 3 )", -4); } END_TEST
MR_START_TEST (scm_sub_1arg, "parse int ( - 1 )") { ASSERT_LOAD_TYPE_SCM (int, "( - 1 )", -1); } END_TEST
MR_START_TEST (scm_sub_0args, "parse int ( - )") { ASSERT_LOAD_TYPE_SCM (int, "( - )", 0); } END_TEST
MR_START_TEST (scm_mul_3args, "parse int ( * 1 2 3 )") { ASSERT_LOAD_TYPE_SCM (int, "( * 1 2 3 )", 6); } END_TEST
MR_START_TEST (scm_mul_1arg, "parse int ( * 1 )") { ASSERT_LOAD_TYPE_SCM (int, "( * 1 )", 1); } END_TEST
MR_START_TEST (scm_mul_0args, "parse int ( * )") { ASSERT_LOAD_TYPE_SCM (int, "( * )", 1); } END_TEST
MR_START_TEST (scm_div_3args, "parse int ( / 12 2 3 )") { ASSERT_LOAD_TYPE_SCM (int, "( / 12 2 3 )", 2); } END_TEST
MR_START_TEST (scm_div_1arg, "parse int ( / 4 2)") { ASSERT_LOAD_TYPE_SCM (int, "( / 4 2 )", 2); } END_TEST
MR_START_TEST (scm_mod_1arg, "parse int ( % 12 5)") { ASSERT_LOAD_TYPE_SCM (int, "( % 12 5 )", 2); } END_TEST
MR_START_TEST (scm_logior_3args, "parse int ( logior 1 2 3 )") { ASSERT_LOAD_TYPE_SCM (int, "( logior 1 2 3 )", 3); } END_TEST
MR_START_TEST (scm_logior_1arg, "parse int ( logior 2 )") { ASSERT_LOAD_TYPE_SCM (int, "( logior 2 )", 2); } END_TEST
MR_START_TEST (scm_logior_0args, "parse int ( logior )") { ASSERT_LOAD_TYPE_SCM (int, "( logior )", 0); } END_TEST
MR_START_TEST (scm_logand_3args, "parse int ( logand 1 2 3 )") { ASSERT_LOAD_TYPE_SCM (int, "( logand 1 2 3 )", 0); } END_TEST
MR_START_TEST (scm_logand_1arg, "parse int ( logand 2 )") { ASSERT_LOAD_TYPE_SCM (int, "( logand 2 )", 2); } END_TEST
MR_START_TEST (scm_logand_0args, "parse int ( logand )") { ASSERT_LOAD_TYPE_SCM (int, "( logand )", 0); } END_TEST
MR_START_TEST (scm_logxor_3args, "parse int ( logxor 1 2 3 )") { ASSERT_LOAD_TYPE_SCM (int, "( logxor 1 2 3 )", 0); } END_TEST
MR_START_TEST (scm_logxor_1arg, "parse int ( logxor 2 )") { ASSERT_LOAD_TYPE_SCM (int, "( logxor 2 )", 2); } END_TEST
MR_START_TEST (scm_logxor_0args, "parse int ( logxor )") { ASSERT_LOAD_TYPE_SCM (int, "( logxor )", 0); } END_TEST

MR_START_TEST (scm_complex_expr, "parse complex double") { ASSERT_LOAD_TYPE_SCM (complex double, "( + 2 1i )", 2 + 1i); } END_TEST
MR_START_TEST (scm_mix_expr, "parse all operation") { ASSERT_LOAD_TYPE_SCM (complex double, "( + ( * 2 3 1i ) ( % 12 5 ) ( logior 1 2 ) ( logxor 1 2 ) )", 8 + 6i); } END_TEST

MAIN ();
