///////////////////////////////
#define EMOJIS_TABLE_LIMIT    20
///////////////////////////////
#include <locale.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <xlocale.h>
///////////////////////////////
#include "emojis-test/emojis-test.h"
#include "submodules/c_greatest/greatest/greatest.h"


///////////////////////////////


TEST t_list_emojis_utf8table(void *EMOJIS_LIMIT){
//            ft_set_u8strwid_func(&u8strwid);
  ft_table_t *table = ft_create_table();

  ft_set_border_style(table, FT_FRAME_STYLE);
  ft_set_tbl_prop(table, FT_TPROP_LEFT_MARGIN, 0);
  ft_set_tbl_prop(table, FT_TPROP_TOP_MARGIN, 0);
  ft_set_tbl_prop(table, FT_TPROP_BOTTOM_MARGIN, 0);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_TEXT_STYLE, FT_TSTYLE_BOLD);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_GREEN);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_BG_COLOR, FT_COLOR_BLACK);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_u8write_ln(table,
                "Name",
                "Emoji "
                );
  ft_u8write_ln(table, "SMILING FACE WITH OPEN MOUTH", "😃");
  ft_u8write_ln(table, "SMILING FACE WITH HEART-SHAPED EYES", "😍");
  ft_u8write_ln(table, "SMILING FACE WITH HEART-SHAPED EYES", "🧑");
  ft_u8write_ln(table, "SMILING FACE WITH HEART-SHAPED EYES", "🔢");
  ft_u8write_ln(table, "SMILING FACE WITH HEART-SHAPED EYES", "👍");
  struct Vector *emojis = get_emojis_t_v();

  for (size_t i = 0; i < vector_size(emojis) && i < (size_t)EMOJIS_LIMIT; i++) {
    struct emojis_t       *e = get_emoji_t(i);
    struct parsed_emoji_t *E = get_parsed_emoji_t(e->emoji);
    printf("emoji:%s|len:%lu|padding len:%lu|\n",
           E->string,
           E->chars_qty,
           strlen(E->padding)
           );
    ft_u8write_ln(table, e->name, e->emoji);
    /*
     * ft_u8printf_ln(table,
     *   "%s|%s",
     *   e->name,
     *   e->emoji
     *   );
     */
  }
  const char *table_str = (const char *)ft_to_u8string(table);

  printf("%s\n", table_str);
  ft_destroy_table(table);
} /* t_list_emojis_utf8table */


TEST t_list_emojis_utf8table1(void *EMOJIS_LIMIT){
  ft_set_u8strwid_func(&u8strwid);
//  setlocale(LC_CTYPE, "");
  struct Vector *emojis         = get_emojis_t_v();
  size_t        id              = 0;
  struct Vector *emojis_names_v = get_emojis_names_v();
  printf("%lu emoji names\n", vector_size(emojis_names_v));
  ft_set_u8strwid_func(&u8strwid);
  ft_table_t *table = ft_create_table();
  ft_set_border_style(table, FT_FRAME_STYLE);
  ft_set_tbl_prop(table, FT_TPROP_LEFT_MARGIN, 0);
  ft_set_tbl_prop(table, FT_TPROP_TOP_MARGIN, 0);
  ft_set_tbl_prop(table, FT_TPROP_BOTTOM_MARGIN, 0);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_TEXT_STYLE, FT_TSTYLE_BOLD);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_GREEN);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_BG_COLOR, FT_COLOR_BLACK);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  /*
   *  ft_u8write_ln(table,
   *          "Name",
   *          "Length",
   *          "Width",
   *          "Emoji"
   *          );
   */
  const char *Character;
  for (size_t i = 0; i < vector_size(emojis) && i < (size_t)EMOJIS_LIMIT; i++) {
    struct emojis_t       *e = get_emoji_t(i);
    struct parsed_emoji_t *E = get_parsed_emoji_t(e->emoji);

    printf("emoji:%s|len:%lu|padding len:%lu|\n",
           E->string,
           E->chars_qty,
           strlen(E->padding)
           );
    //if(E->chars_qty != 2)continue;
    ft_write_ln(table, "x", "x", "SMILING FACE WITH OPEN MOUTH", "😃");
    /*
     * ft_u8printf_ln(table,
     *           "%s|%lu|%lu|%s",
     *           e->name,
     *           E->chars_qty,
     *           E->len,
     *           e->emoji
     *           );
     */
  }

  const char *tbl_s = ft_to_u8string(table);
  printf("%s", tbl_s);
  ft_destroy_table(table);

  PASS();
} /* t_list_emojis_table1 */


TEST t_list_emojis_table(void *EMOJIS_LIMIT){
  setlocale(LC_CTYPE, "");
  struct Vector *emojis         = get_emojis_t_v();
  size_t        id              = 0;
  struct Vector *emojis_names_v = get_emojis_names_v();
  printf("%lu emoji names\n", vector_size(emojis_names_v));
  //ft_set_u8strwid_func(&u8strwid);
  ft_table_t *table = ft_create_table();
  ft_set_border_style(table, FT_FRAME_STYLE);
  ft_set_tbl_prop(table, FT_TPROP_LEFT_MARGIN, 0);
  ft_set_tbl_prop(table, FT_TPROP_TOP_MARGIN, 0);
  ft_set_tbl_prop(table, FT_TPROP_BOTTOM_MARGIN, 0);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_TEXT_STYLE, FT_TSTYLE_BOLD);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_GREEN);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_BG_COLOR, FT_COLOR_BLACK);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_write_ln(table,
              "Name",
              "Length",
              "Width",
              "Emoji"
              );
  const char *Character;
  for (size_t i = 0; i < vector_size(emojis) && i < (size_t)EMOJIS_LIMIT; i++) {
    struct emojis_t       *e = get_emoji_t(i);
    struct parsed_emoji_t *E = get_parsed_emoji_t(e->emoji);

    printf("emoji:%s|len:%lu|padding len:%lu|\n",
           E->string,
           E->chars_qty,
           strlen(E->padding)
           );
    //if(E->chars_qty != 2)continue;
    ft_printf_ln(table,
                 "%s|%lu|%lu|%s",
                 e->name,
                 E->chars_qty,
                 E->len,
                 e->emoji
                 );
  }

  const char *tbl_s = ft_to_string(table);
  printf("%s", tbl_s);
  ft_destroy_table(table);

  PASS();
} /* t_list_emojis_table1 */


TEST t_list_emojis_t_h(void){
  PASS();
}


TEST t_list_emojis_t_v(void){
  struct Vector *emojis;

  BENCHMARK_QTY(benchmark_list_emojis, 20)
  emojis = get_emojis_t_v();
  END_BENCHMARK(benchmark_list_emojis)
  struct emojis_t *e;

  for (size_t i = 0; i < vector_size(emojis); i++) {
    e = get_emoji_t(i);
    printf(" #%.5lu %s -> %s (%lu chars)\n", i, e->name, e->emoji, e->chars);
  }
  printf("%lu emojis\n", vector_size(emojis));
  BENCHMARK_SUMMARY(benchmark_list_emojis);
  PASS();
}


TEST t_list_emojis_qty(void){
  printf("%lu emojis\n", get_emojis_qty());
  PASS();
}


TEST t_list_emojis_names(void){
  size_t        id              = 0;
  struct Vector *emojis_names_v = get_emojis_names_v();

  printf("%lu emoji names\n", vector_size(emojis_names_v));
  struct emojis_t *e = get_emoji_t(id);

  printf("%lu: %s\n", id, e->name);

  PASS();
}

SUITE(s_list_emojis_names) {
  RUN_TEST(t_list_emojis_t_v);
  RUN_TEST(t_list_emojis_names);
  RUN_TEST(t_list_emojis_qty);
  RUN_TEST(t_list_emojis_t_h);
  RUN_TESTp(t_list_emojis_table, (void *)EMOJIS_TABLE_LIMIT);
  RUN_TESTp(t_list_emojis_utf8table, (void *)EMOJIS_TABLE_LIMIT);
}

GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_list_emojis_names);
} /* main */
