#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

int errorHandler(Display* display, XErrorEvent* error_event) {
    if (error_event->error_code == BadRRCrtc) {
        // Handle the error gracefully
        return 0;  // Ignore the error
    }
    return 1;  // Continue with the default error handling
}

int main() {
    // Command to turn off
    const char *off_command = "xrandr --output HDMI-0 --off --output eDP-1-1 --auto";
    // COmmand to turn on
    const char *on_command = "xrandr --output HDMI-0 --auto --right-of eDP-1-1";
    // target display
    const char *target_display = "HDMI-0";


    // Set the custom error handler
    XSetErrorHandler(errorHandler);

    Display* display = XOpenDisplay(NULL);

    if (display == NULL) {
        fprintf(stderr, "Unable to open X display\n");
        return 1;
    }

    Window root = DefaultRootWindow(display);

    XRRScreenResources* screen_resources = XRRGetScreenResources(display, root);

    if (screen_resources == NULL) {
        fprintf(stderr, "Unable to get screen resources\n");
        XCloseDisplay(display);
        return 1;
    }

    // printf("Monitors and their resolution:\n");

    for (int i = 0; i < screen_resources->noutput; i++) {
        XRROutputInfo* output_info = XRRGetOutputInfo(display, screen_resources, screen_resources->outputs[i]);

        // printf("Monitor: %s\n", output_info->name);

        if (output_info->connection == RR_Connected) {
            XRRCrtcInfo* crtc_info = XRRGetCrtcInfo(display, screen_resources, output_info->crtc);
            if (crtc_info != NULL) {
                // printf("Resolution: %dx%d\n", crtc_info->width, crtc_info->height);
                if (strcmp(output_info->name, target_display) == 0) {
                    system(off_command);
                }
                XRRFreeCrtcInfo(crtc_info);
            } else {
                // printf("Resolution: Unknown\n");
                if (strcmp(output_info->name, target_display) == 0) {
                    system(on_command);
                }
            }
        } else {
            // printf("Resolution: Unknown\n");
        }

        XRRFreeOutputInfo(output_info);
    }

    XRRFreeScreenResources(screen_resources);
    XCloseDisplay(display);

    return 0;
}
