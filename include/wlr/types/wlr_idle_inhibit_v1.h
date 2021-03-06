#ifndef WLR_TYPES_WLR_IDLE_INHIBIT_V1_H
#define WLR_TYPES_WLR_IDLE_INHIBIT_V1_H

#include <wayland-server.h>

/* This interface permits clients to inhibit the idle behavior such as
 * screenblanking, locking, and screensaving.
 *
 * This allows clients to ensure they stay visible instead of being hidden by
 * power-saving.
 *
 * Inhibitors are created for surfaces. They should only be in effect, while
 * this surface is visible.
 * The effect could also be limited to outputs it is displayed on (e.g.
 * dimm/dpms off outputs, except the one a video is displayed on).
 */

struct wlr_idle_inhibit_manager_v1 {
	struct wl_list wl_resources; // wl_resource_get_link
	struct wl_list inhibitors; // wlr_idle_inhibit_inhibitor_v1::link
	struct wl_global *global;
	
	struct wl_listener display_destroy;

	struct {
		struct wl_signal new_inhibitor;
	} events;

	void *data;
};

struct wlr_idle_inhibitor_v1 {
	struct wlr_surface *surface;
	struct wl_resource *resource;
	struct wl_listener surface_destroy;

	struct wl_list link; // wlr_idle_inhibit_manager_v1::inhibitors;

	struct {
		struct wl_signal destroy;
	} events;

	void *data;
};

struct wlr_idle_inhibit_manager_v1 *wlr_idle_inhibit_v1_create(struct wl_display *display);
void wlr_idle_inhibit_v1_destroy(struct wlr_idle_inhibit_manager_v1 *idle_inhibit);

#endif
