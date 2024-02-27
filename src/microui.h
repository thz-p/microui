/*
** Copyright (c) 2020 rxi
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the MIT license. See `microui.c` for details.
*/

#ifndef MICROUI_H
#define MICROUI_H

// 定义 MicroUI 的版本号常量
#define MU_VERSION "2.01"

// 定义不同数据结构的大小常量
#define MU_COMMANDLIST_SIZE     (256 * 1024)
#define MU_ROOTLIST_SIZE        32
#define MU_CONTAINERSTACK_SIZE  32
#define MU_CLIPSTACK_SIZE       32
#define MU_IDSTACK_SIZE         32
#define MU_LAYOUTSTACK_SIZE     16
#define MU_CONTAINERPOOL_SIZE   48
#define MU_TREENODEPOOL_SIZE    48
#define MU_MAX_WIDTHS           16

// 定义实数类型和格式化字符串常量
#define MU_REAL                 float
#define MU_REAL_FMT             "%.3g"
#define MU_SLIDER_FMT           "%.2f"
#define MU_MAX_FMT              127

// 定义一个栈结构的宏，参数 T 表示元素类型，参数 n 表示栈的大小
#define mu_stack(T, n)          struct { int idx; T items[n]; }

// 定义获取两个数中的最小值和最大值的宏
#define mu_min(a, b)            ((a) < (b) ? (a) : (b))
#define mu_max(a, b)            ((a) > (b) ? (a) : (b))

// 将一个数限制在给定范围内的宏
#define mu_clamp(x, a, b)       mu_min(b, mu_max(a, x))

#endif /* MICROUI_H */

// 枚举类型的定义
enum {
    MU_CLIP_PART = 1,  // 表示部分裁剪的枚举常量，值为 1
    MU_CLIP_ALL       // 表示全部裁剪的枚举常量，值为 MU_CLIP_PART + 1，即为 2
};

// 枚举类型的定义
enum {
    MU_COMMAND_JUMP = 1,  // 表示跳转命令的枚举常量，值为 1
    MU_COMMAND_CLIP,      // 表示裁剪命令的枚举常量，值为 MU_COMMAND_JUMP + 1，即为 2
    MU_COMMAND_RECT,      // 表示矩形绘制命令的枚举常量，值为 MU_COMMAND_CLIP + 1，即为 3
    MU_COMMAND_TEXT,      // 表示文本绘制命令的枚举常量，值为 MU_COMMAND_RECT + 1，即为 4
    MU_COMMAND_ICON,      // 表示图标绘制命令的枚举常量，值为 MU_COMMAND_TEXT + 1，即为 5
    MU_COMMAND_MAX        // 表示命令类型的枚举常量的数量
};

// 枚举类型的定义
enum {
    MU_COLOR_TEXT,         // 文本颜色
    MU_COLOR_BORDER,       // 边框颜色
    MU_COLOR_WINDOWBG,     // 窗口背景颜色
    MU_COLOR_TITLEBG,      // 标题栏背景颜色
    MU_COLOR_TITLETEXT,    // 标题栏文本颜色
    MU_COLOR_PANELBG,      // 面板背景颜色
    MU_COLOR_BUTTON,       // 按钮颜色
    MU_COLOR_BUTTONHOVER,  // 鼠标悬停在按钮上时的颜色
    MU_COLOR_BUTTONFOCUS,  // 按钮获得焦点时的颜色
    MU_COLOR_BASE,         // 基础颜色
    MU_COLOR_BASEHOVER,    // 鼠标悬停在基础元素上时的颜色
    MU_COLOR_BASEFOCUS,    // 基础元素获得焦点时的颜色
    MU_COLOR_SCROLLBASE,   // 滚动条基础颜色
    MU_COLOR_SCROLLTHUMB,  // 滚动条滑块颜色
    MU_COLOR_MAX           // 颜色类型的枚举常量的数量
};

// 枚举类型的定义
enum {
    MU_ICON_CLOSE = 1,     // 表示关闭图标的枚举常量，值为 1
    MU_ICON_CHECK,         // 表示勾选图标的枚举常量，值为 MU_ICON_CLOSE + 1，即为 2
    MU_ICON_COLLAPSED,     // 表示折叠图标的枚举常量，值为 MU_ICON_CHECK + 1，即为 3
    MU_ICON_EXPANDED,      // 表示展开图标的枚举常量，值为 MU_ICON_COLLAPSED + 1，即为 4
    MU_ICON_MAX            // 表示图标类型的枚举常量的数量
};

// 枚举类型的定义
enum {
    MU_RES_ACTIVE  = (1 << 0),  // 表示资源处于活动状态的枚举常量，值为 1 左移 0 位，即为 1
    MU_RES_SUBMIT  = (1 << 1),  // 表示资源被提交的枚举常量，值为 1 左移 1 位，即为 2
    MU_RES_CHANGE  = (1 << 2)   // 表示资源发生改变的枚举常量，值为 1 左移 2 位，即为 4
};

// 枚举类型的定义
enum {
    MU_OPT_ALIGNCENTER  = (1 << 0),  // 表示居中对齐的选项，值为 1 左移 0 位，即为 1
    MU_OPT_ALIGNRIGHT   = (1 << 1),  // 表示右对齐的选项，值为 1 左移 1 位，即为 2
    MU_OPT_NOINTERACT   = (1 << 2),  // 表示不可交互的选项，值为 1 左移 2 位，即为 4
    MU_OPT_NOFRAME      = (1 << 3),  // 表示无边框的选项，值为 1 左移 3 位，即为 8
    MU_OPT_NORESIZE     = (1 << 4),  // 表示不可改变大小的选项，值为 1 左移 4 位，即为 16
    MU_OPT_NOSCROLL     = (1 << 5),  // 表示无滚动条的选项，值为 1 左移 5 位，即为 32
    MU_OPT_NOCLOSE      = (1 << 6),  // 表示无关闭按钮的选项，值为 1 左移 6 位，即为 64
    MU_OPT_NOTITLE      = (1 << 7),  // 表示无标题的选项，值为 1 左移 7 位，即为 128
    MU_OPT_HOLDFOCUS    = (1 << 8),  // 表示保持焦点的选项，值为 1 左移 8 位，即为 256
    MU_OPT_AUTOSIZE     = (1 << 9),  // 表示自动调整大小的选项，值为 1 左移 9 位，即为 512
    MU_OPT_POPUP        = (1 << 10), // 表示弹出式窗口的选项，值为 1 左移 10 位，即为 1024
    MU_OPT_CLOSED       = (1 << 11), // 表示关闭状态的选项，值为 1 左移 11 位，即为 2048
    MU_OPT_EXPANDED     = (1 << 12)  // 表示展开状态的选项，值为 1 左移 12 位，即为 4096
};

// 枚举类型的定义
enum {
    MU_MOUSE_LEFT    = (1 << 0),  // 表示鼠标左键的枚举常量，值为 1 左移 0 位，即为 1
    MU_MOUSE_RIGHT   = (1 << 1),  // 表示鼠标右键的枚举常量，值为 1 左移 1 位，即为 2
    MU_MOUSE_MIDDLE  = (1 << 2)   // 表示鼠标中键的枚举常量，值为 1 左移 2 位，即为 4
};

// 枚举类型的定义
enum {
    MU_KEY_SHIFT       = (1 << 0),  // 表示 Shift 键的枚举常量，值为 1 左移 0 位，即为 1
    MU_KEY_CTRL        = (1 << 1),  // 表示 Ctrl 键的枚举常量，值为 1 左移 1 位，即为 2
    MU_KEY_ALT         = (1 << 2),  // 表示 Alt 键的枚举常量，值为 1 左移 2 位，即为 4
    MU_KEY_BACKSPACE   = (1 << 3),  // 表示退格键的枚举常量，值为 1 左移 3 位，即为 8
    MU_KEY_RETURN      = (1 << 4)   // 表示回车键的枚举常量，值为 1 左移 4 位，即为 16
};

typedef struct mu_Context mu_Context;
typedef unsigned mu_Id;
typedef MU_REAL mu_Real;
typedef void* mu_Font;

typedef struct { int x, y; } mu_Vec2;
typedef struct { int x, y, w, h; } mu_Rect;
typedef struct { unsigned char r, g, b, a; } mu_Color;
typedef struct { mu_Id id; int last_update; } mu_PoolItem;

typedef struct { int type, size; } mu_BaseCommand;
typedef struct { mu_BaseCommand base; void *dst; } mu_JumpCommand;
typedef struct { mu_BaseCommand base; mu_Rect rect; } mu_ClipCommand;
typedef struct { mu_BaseCommand base; mu_Rect rect; mu_Color color; } mu_RectCommand;
typedef struct { mu_BaseCommand base; mu_Font font; mu_Vec2 pos; mu_Color color; char str[1]; } mu_TextCommand;
typedef struct { mu_BaseCommand base; mu_Rect rect; int id; mu_Color color; } mu_IconCommand;

typedef union {
  int type;
  mu_BaseCommand base;
  mu_JumpCommand jump;
  mu_ClipCommand clip;
  mu_RectCommand rect;
  mu_TextCommand text;
  mu_IconCommand icon;
} mu_Command;

typedef struct {
  mu_Rect body;
  mu_Rect next;
  mu_Vec2 position;
  mu_Vec2 size;
  mu_Vec2 max;
  int widths[MU_MAX_WIDTHS];
  int items;
  int item_index;
  int next_row;
  int next_type;
  int indent;
} mu_Layout;

typedef struct {
  mu_Command *head, *tail;
  mu_Rect rect;
  mu_Rect body;
  mu_Vec2 content_size;
  mu_Vec2 scroll;
  int zindex;
  int open;
} mu_Container;

typedef struct {
  mu_Font font;
  mu_Vec2 size;
  int padding;
  int spacing;
  int indent;
  int title_height;
  int scrollbar_size;
  int thumb_size;
  mu_Color colors[MU_COLOR_MAX];
} mu_Style;

struct mu_Context {
  /* callbacks */
  int (*text_width)(mu_Font font, const char *str, int len);
  int (*text_height)(mu_Font font);
  void (*draw_frame)(mu_Context *ctx, mu_Rect rect, int colorid);
  /* core state */
  mu_Style _style;
  mu_Style *style;
  mu_Id hover;
  mu_Id focus;
  mu_Id last_id;
  mu_Rect last_rect;
  int last_zindex;
  int updated_focus;
  int frame;
  mu_Container *hover_root;
  mu_Container *next_hover_root;
  mu_Container *scroll_target;
  char number_edit_buf[MU_MAX_FMT];
  mu_Id number_edit;
  /* stacks */
  mu_stack(char, MU_COMMANDLIST_SIZE) command_list;
  mu_stack(mu_Container*, MU_ROOTLIST_SIZE) root_list;
  mu_stack(mu_Container*, MU_CONTAINERSTACK_SIZE) container_stack;
  mu_stack(mu_Rect, MU_CLIPSTACK_SIZE) clip_stack;
  mu_stack(mu_Id, MU_IDSTACK_SIZE) id_stack;
  mu_stack(mu_Layout, MU_LAYOUTSTACK_SIZE) layout_stack;
  /* retained state pools */
  mu_PoolItem container_pool[MU_CONTAINERPOOL_SIZE];
  mu_Container containers[MU_CONTAINERPOOL_SIZE];
  mu_PoolItem treenode_pool[MU_TREENODEPOOL_SIZE];
  /* input state */
  mu_Vec2 mouse_pos;
  mu_Vec2 last_mouse_pos;
  mu_Vec2 mouse_delta;
  mu_Vec2 scroll_delta;
  int mouse_down;
  int mouse_pressed;
  int key_down;
  int key_pressed;
  char input_text[32];
};


mu_Vec2 mu_vec2(int x, int y);
mu_Rect mu_rect(int x, int y, int w, int h);
mu_Color mu_color(int r, int g, int b, int a);

void mu_init(mu_Context *ctx);
void mu_begin(mu_Context *ctx);
void mu_end(mu_Context *ctx);
void mu_set_focus(mu_Context *ctx, mu_Id id);
mu_Id mu_get_id(mu_Context *ctx, const void *data, int size);
void mu_push_id(mu_Context *ctx, const void *data, int size);
void mu_pop_id(mu_Context *ctx);
void mu_push_clip_rect(mu_Context *ctx, mu_Rect rect);
void mu_pop_clip_rect(mu_Context *ctx);
mu_Rect mu_get_clip_rect(mu_Context *ctx);
int mu_check_clip(mu_Context *ctx, mu_Rect r);
mu_Container* mu_get_current_container(mu_Context *ctx);
mu_Container* mu_get_container(mu_Context *ctx, const char *name);
void mu_bring_to_front(mu_Context *ctx, mu_Container *cnt);

int mu_pool_init(mu_Context *ctx, mu_PoolItem *items, int len, mu_Id id);
int mu_pool_get(mu_Context *ctx, mu_PoolItem *items, int len, mu_Id id);
void mu_pool_update(mu_Context *ctx, mu_PoolItem *items, int idx);

void mu_input_mousemove(mu_Context *ctx, int x, int y);
void mu_input_mousedown(mu_Context *ctx, int x, int y, int btn);
void mu_input_mouseup(mu_Context *ctx, int x, int y, int btn);
void mu_input_scroll(mu_Context *ctx, int x, int y);
void mu_input_keydown(mu_Context *ctx, int key);
void mu_input_keyup(mu_Context *ctx, int key);
void mu_input_text(mu_Context *ctx, const char *text);

mu_Command* mu_push_command(mu_Context *ctx, int type, int size);
int mu_next_command(mu_Context *ctx, mu_Command **cmd);
void mu_set_clip(mu_Context *ctx, mu_Rect rect);
void mu_draw_rect(mu_Context *ctx, mu_Rect rect, mu_Color color);
void mu_draw_box(mu_Context *ctx, mu_Rect rect, mu_Color color);
void mu_draw_text(mu_Context *ctx, mu_Font font, const char *str, int len, mu_Vec2 pos, mu_Color color);
void mu_draw_icon(mu_Context *ctx, int id, mu_Rect rect, mu_Color color);

void mu_layout_row(mu_Context *ctx, int items, const int *widths, int height);
void mu_layout_width(mu_Context *ctx, int width);
void mu_layout_height(mu_Context *ctx, int height);
void mu_layout_begin_column(mu_Context *ctx);
void mu_layout_end_column(mu_Context *ctx);
void mu_layout_set_next(mu_Context *ctx, mu_Rect r, int relative);
mu_Rect mu_layout_next(mu_Context *ctx);

void mu_draw_control_frame(mu_Context *ctx, mu_Id id, mu_Rect rect, int colorid, int opt);
void mu_draw_control_text(mu_Context *ctx, const char *str, mu_Rect rect, int colorid, int opt);
int mu_mouse_over(mu_Context *ctx, mu_Rect rect);
void mu_update_control(mu_Context *ctx, mu_Id id, mu_Rect rect, int opt);

#define mu_button(ctx, label)             mu_button_ex(ctx, label, 0, MU_OPT_ALIGNCENTER)
#define mu_textbox(ctx, buf, bufsz)       mu_textbox_ex(ctx, buf, bufsz, 0)
#define mu_slider(ctx, value, lo, hi)     mu_slider_ex(ctx, value, lo, hi, 0, MU_SLIDER_FMT, MU_OPT_ALIGNCENTER)
#define mu_number(ctx, value, step)       mu_number_ex(ctx, value, step, MU_SLIDER_FMT, MU_OPT_ALIGNCENTER)
#define mu_header(ctx, label)             mu_header_ex(ctx, label, 0)
#define mu_begin_treenode(ctx, label)     mu_begin_treenode_ex(ctx, label, 0)
#define mu_begin_window(ctx, title, rect) mu_begin_window_ex(ctx, title, rect, 0)
#define mu_begin_panel(ctx, name)         mu_begin_panel_ex(ctx, name, 0)

void mu_text(mu_Context *ctx, const char *text);
void mu_label(mu_Context *ctx, const char *text);
int mu_button_ex(mu_Context *ctx, const char *label, int icon, int opt);
int mu_checkbox(mu_Context *ctx, const char *label, int *state);
int mu_textbox_raw(mu_Context *ctx, char *buf, int bufsz, mu_Id id, mu_Rect r, int opt);
int mu_textbox_ex(mu_Context *ctx, char *buf, int bufsz, int opt);
int mu_slider_ex(mu_Context *ctx, mu_Real *value, mu_Real low, mu_Real high, mu_Real step, const char *fmt, int opt);
int mu_number_ex(mu_Context *ctx, mu_Real *value, mu_Real step, const char *fmt, int opt);
int mu_header_ex(mu_Context *ctx, const char *label, int opt);
int mu_begin_treenode_ex(mu_Context *ctx, const char *label, int opt);
void mu_end_treenode(mu_Context *ctx);
int mu_begin_window_ex(mu_Context *ctx, const char *title, mu_Rect rect, int opt);
void mu_end_window(mu_Context *ctx);
void mu_open_popup(mu_Context *ctx, const char *name);
int mu_begin_popup(mu_Context *ctx, const char *name);
void mu_end_popup(mu_Context *ctx);
void mu_begin_panel_ex(mu_Context *ctx, const char *name, int opt);
void mu_end_panel(mu_Context *ctx);

#endif

// 这段代码是一个微型用户界面库，具有以下功能和特点：
// 1. 定义了用于表示用户界面元素的数据结构，如矩形区域、颜色等。
// 2. 提供了事件处理函数，包括处理鼠标和键盘输入事件。
// 3. 支持绘制基本的用户界面元素，如矩形、文本和图标等。
// 4. 提供了布局管理函数，用于管理用户界面元素的排列和尺寸。
// 5. 包含创建常见用户界面控件的函数，如按钮、复选框、文本框和滑块等。
// 6. 支持样式定制，允许开发者自定义用户界面的外观和风格。
// 7. 提供了状态管理函数，用于管理用户界面元素的状态，如焦点和悬停状态。
// 8. 包含了内存管理函数，用于管理内存池，创建、获取和更新用户界面元素。
// 这个库提供了一套简单但功能齐全的工具，能够帮助开发者快速构建基本的用户界面。