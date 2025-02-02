/* SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup editors
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct ImBuf;
struct Image;
struct ImageUser;
struct UndoStep;
struct UndoType;
struct bContext;
struct wmKeyConfig;
struct wmOperator;

/* paint_ops.c */

void ED_operatortypes_paint(void);
void ED_operatormacros_paint(void);
void ED_keymap_paint(struct wmKeyConfig *keyconf);

/* paint_image.c */

void ED_imapaint_clear_partial_redraw(void);
void ED_imapaint_dirty_region(struct Image *ima,
                              struct ImBuf *ibuf,
                              struct ImageUser *iuser,
                              int x,
                              int y,
                              int w,
                              int h,
                              bool find_old);
void ED_imapaint_bucket_fill(struct bContext *C,
                             float color[3],
                             struct wmOperator *op,
                             const int mouse[2]);

/* paint_image_proj.c */

void ED_paint_data_warning(struct ReportList *reports, bool uvs, bool mat, bool tex, bool stencil);
/**
 * Make sure that active object has a material,
 * and assign UVs and image layers if they do not exist.
 */
bool ED_paint_proj_mesh_data_check(
    struct Scene *scene, struct Object *ob, bool *uvs, bool *mat, bool *tex, bool *stencil);

/* image_undo.c */

/**
 * The caller is responsible for running #ED_image_undo_push_end,
 * failure to do so causes an invalid state for the undo system.
 */
void ED_image_undo_push_begin(const char *name, int paint_mode);
void ED_image_undo_push_begin_with_image(const char *name,
                                         struct Image *image,
                                         struct ImBuf *ibuf,
                                         struct ImageUser *iuser);

void ED_image_undo_push_end(void);
/**
 * Restore painting image to previous state. Used for anchored and drag-dot style brushes.
 */
void ED_image_undo_restore(struct UndoStep *us);

/** Export for ED_undo_sys. */
void ED_image_undosys_type(struct UndoType *ut);

void *ED_image_paint_tile_find(struct ListBase *paint_tiles,
                               struct Image *image,
                               struct ImBuf *ibuf,
                               struct ImageUser *iuser,
                               int x_tile,
                               int y_tile,
                               unsigned short **r_mask,
                               bool validate);
void *ED_image_paint_tile_push(struct ListBase *paint_tiles,
                               struct Image *image,
                               struct ImBuf *ibuf,
                               struct ImBuf **tmpibuf,
                               struct ImageUser *iuser,
                               int x_tile,
                               int y_tile,
                               unsigned short **r_mask,
                               bool **r_valid,
                               bool use_thread_lock,
                               bool find_prev);
void ED_image_paint_tile_lock_init(void);
void ED_image_paint_tile_lock_end(void);

struct ListBase *ED_image_paint_tile_list_get(void);

#define ED_IMAGE_UNDO_TILE_BITS 6
#define ED_IMAGE_UNDO_TILE_SIZE (1 << ED_IMAGE_UNDO_TILE_BITS)
#define ED_IMAGE_UNDO_TILE_NUMBER(size) \
  (((size) + ED_IMAGE_UNDO_TILE_SIZE - 1) >> ED_IMAGE_UNDO_TILE_BITS)

/* paint_curve_undo.c */

void ED_paintcurve_undo_push_begin(const char *name);
void ED_paintcurve_undo_push_end(struct bContext *C);

/** Export for ED_undo_sys. */
void ED_paintcurve_undosys_type(struct UndoType *ut);

#ifdef __cplusplus
}
#endif
