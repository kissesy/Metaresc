#include <check.h>
#include <reslib.h>
#include <regression.h>

TYPEDEF_STRUCT (string_rarray_t, RARRAY (string_t, x))
TYPEDEF_STRUCT (emb_rarray_t, RARRAY (emb_rarray_t, x))

RL_START_TEST (rarray_empty, "rarray empty") {
  string_rarray_t orig = {
    .x =
    {
      .data = NULL,
      .size = 0,
      .alloc_size = 0,
    },
  };
  ALL_METHODS (ASSERT_SAVE_LOAD, string_rarray_t, &orig);
} END_TEST

RL_START_TEST (rarray_embeded, "slef embeded rarray") {
  emb_rarray_t orig = {
    .x =
    {
      .data = (emb_rarray_t[]){
	{
	  .x =
	  {
	    .data = NULL,
	    .size = 0,
	    .alloc_size = 0,
	  },
	}
      },
      .size = sizeof (emb_rarray_t),
      .alloc_size = sizeof (emb_rarray_t),
    },
  };
  ALL_METHODS (ASSERT_SAVE_LOAD, emb_rarray_t, &orig);
  orig.x.data->x.data = &orig;
  orig.x.data->x.size = orig.x.data->x.alloc_size = sizeof (emb_rarray_t);
  ALL_METHODS (ASSERT_SAVE_LOAD, emb_rarray_t, &orig);
} END_TEST

RL_START_TEST (rarray_ext_eq_ptr_type, "rarray_t .ext = .ptr_type = \"string_t\"") {
  string_rarray_t orig = {
    .x =
    {
      .data = (string_t[]){ "0", "1", },
      .size = 2 * sizeof (string_t),
      .alloc_size = 2 * sizeof (string_t),
      .ext = { "string_t" },
      .ptr_type = "string_t",
    },
  };
  ALL_METHODS (ASSERT_SAVE_LOAD, string_rarray_t, &orig);
} END_TEST

RL_START_TEST (rarray_referenced_content, "referenced content") {
  string_rarray_t orig = {
    .x =
    {
      .data = (string_t[]){ "string_t", "string_t", },
      .size = 2 * sizeof (string_t),
      .alloc_size = 2 * sizeof (string_t),
      .ext = { "string_t" },
      .ptr_type = "string_t",
    },
  };
  ALL_METHODS (ASSERT_SAVE_LOAD, string_rarray_t, &orig);
} END_TEST

RL_START_TEST (rarray_referenced_elements, "referenced elements") {
  string_rarray_t orig = {
    .x =
    {
      .data = (string_t[]){ "0", "1", },
      .size = 2 * sizeof (string_t),
      .alloc_size = 2 * sizeof (string_t),
    },
  };
  orig.x.ext.ptr = &orig.x.data[1];
  ALL_METHODS (ASSERT_SAVE_LOAD, string_rarray_t, &orig);
  orig.x.ext.ptr = &orig.x.data[0];
  ALL_METHODS (ASSERT_SAVE_LOAD, string_rarray_t, &orig);
} END_TEST

MAIN ();
