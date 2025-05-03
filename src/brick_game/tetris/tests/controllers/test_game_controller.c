
#include "controllers/game_controller.h"
#include "services/figure_service.h"
#include "test_controllers.h"
#include "tetris_backend_api.h"

START_TEST(test_update_curerntState) {
  init_game();
  updateCurrentState();
  ck_assert_ptr_nonnull(get_game()->game_info.field);
  ck_assert_ptr_nonnull(get_game()->game_info.next);
  destroy_game();
}
END_TEST;

START_TEST(test_update_curerntState_change_state) {
  const tetris_state states[] = {PAUSE_STATE, GAMEOVER, EXIT_STATE};
  figure_t figure = {0};
  figure_t next_figure = {0};

  for (int i = 0; i < 3; i++) {
    init_game();

    figure.figure_type = S_SHAPE;
    figure.center_x.int_coord = 0;
    figure.center_y.int_coord = 0;
    fill_figure_from_string(&figure, "[0 0] [1 0] [1 1] [2 1]");

    if (i > 1) {
      next_figure.figure_type = S_SHAPE;
      next_figure.center_x.int_coord = 0;
      next_figure.center_y.int_coord = 0;
      fill_figure_from_string(&next_figure, "[0 0] [1 0] [1 1] [2 1]");
      get_game()->next_figure = next_figure;
    }

    tetris_game_t *game = get_game();
    game->figure = figure;

    get_game()->state = states[i];

    updateCurrentState();
    ck_assert_ptr_nonnull(get_game()->game_info.field);
    ck_assert_ptr_nonnull(get_game()->game_info.next);
    destroy_game();
  }
}
END_TEST;

TCase *get_game_controller_test_case() {
  TCase *tc = tcase_create("game_controller");

  tcase_add_test(tc, test_update_curerntState);
  tcase_add_test(tc, test_update_curerntState_change_state);

  return tc;
}