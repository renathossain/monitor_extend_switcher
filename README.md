# Dynamic Display Configuration Switcher

This code is a simple C program that uses the X11 library to control the display configuration of a Linux system. It can be used to turn a specific display output on or off based on your requirements.

## Table of Contents

1. [Overview](#overview)
2. [Usage](#usage)
3. [Adapting the Code](#adapting-the-code)
4. [License](#license)

## Overview

The code leverages the X11 and Xrandr libraries to interact with the display configuration. It defines two command strings to turn a target display on or off and specifies the target display's name. The program uses a custom error handler to gracefully handle errors and provides a foundation for dynamic display configuration.

## Usage

To compile and run the code:

1. Ensure you have the necessary libraries installed (X11 and Xrandr).
2. Compile the code using the following command:

   ```shell
   gcc -o extend extend.c -lX11 -lXrandr
   ```

3. Run the program:

   ```shell
   ./extend
   ```

This will execute the specified `off_command` and `on_command` based on the target display you've set in the code.

To make the program easy to execute with `dmenu` or from any directory, move the compiled binary to a directory included in your system's `PATH`. For example, you can move it to the `/usr/local/bin` directory:

   ```shell
   sudo mv extend /usr/local/bin/
   ```

Now, you can run the program from any location by simply typing `extend` in your terminal or using it with `dmenu`.

## Adapting the Code

You can adapt this code for various scenarios by modifying the `off_command`, `on_command`, and `target_display` variables to meet your specific requirements. Here's how you can do it:

### 1. Change the Commands

Modify the `off_command` and `on_command` variables to execute the desired actions for your specific use case. For example, you can change the resolution, position, or other display settings as needed.

```c
const char *off_command = "your_custom_off_command_here";
const char *on_command = "your_custom_on_command_here";
```

### 2. Specify the Target Display

Set the `target_display` variable to match the name of the display output you want to control. This allows you to target a specific monitor for configuration.

```c
const char *target_display = "your_target_display_name_here";
```

### 3. Handle Error Conditions

You can customize the `errorHandler` function to handle specific errors that might occur during display configuration. Currently, it gracefully handles the `BadRRCrtc` error, but you can extend error handling as needed.

```c
int errorHandler(Display* display, XErrorEvent* error_event) {
    // Add your custom error handling logic here
}
```

By making these changes, you can adapt the code to control display settings as required for your specific scenario.

## License

This code is provided under the [GNU General Public License (GPL) Version 3](https://www.gnu.org/licenses/gpl-3.0.en.html). You are free to use, modify, and distribute it under the terms and conditions specified in the GPL.

Please refer to the `LICENSE` file included with the code for the full text of the GNU GPL.

If you make any modifications or extensions to this code and distribute them, you must also follow the terms of the GNU GPL, including making your modified source code available to others under the same license.

For more details, refer to the [GNU GPL](https://www.gnu.org/licenses/gpl-3.0.en.html).
