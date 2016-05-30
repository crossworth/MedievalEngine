### Medieval Engine Version: 1.4 - LuaAPI Reference


* **Function** void profiler_toggle() - show or hide the console
* **Function** void profiler_set_update_time(unsigned int) - set the update time for the profiler in Milli Seconds
* **Function** void profiler_set_output_type(int) - change the default time unit of the profiler, pass an int with the values: 1 to seconds, 2 to milli seconds, 3 to micro seconds
* **Function** bool window_is_open() - if the window is open or not, a hiden window still return true, to check if the window is visible use `window_is_visible`
* **Function** void window_set_title(string) - set the engine window title
* **Function** void window_set_icon(string) - set the engine window icon, must provide a path for an image file on ME::ENGINE_DEFAULTS::ASSETS_PATH folder
* **Function** void window_set_visible(bool) - set the window to be visible
* **Function** void window_is_visible(bool) - if the window to be visible or not
* **Function** void window_set_cursor(string) - set the window cursor and hide the default window cursor, must provide a path for the a image file on ME::ENGINE_DEFAULTS::ASSETS_PATH folder
* **Function** bool window_has_custom_cursor() - if the window has a custom cursor or not
* **Function** MEUInt64 window_get_delta() - get the delta time (the time that each frame is using to draw on screen in microseconds)
* **Function** unsigned int window_get_fps() - get the fps counter
* **Function** unsigned int window_get_draw_calls() - get the number of draw made on a single frame, should be called after the last draw call
* **Function** void window_set_cursor_visible(bool) - set the System cursor visible or not, don't have an effect if a custom cursor is set
* **Function** table window_get_position() - get the window position, return a table with members: x, y
* **Function** bool console_is_visible() - if the console is open or not
* **Function** void console_set_visible(bool) - show or hide the console
* **Function** void console_toggle() - show or hide the console
* **Function** void console_close() - close the console
* **Function** void console_open() - open the console
* **Function** void console_add_message() - add an message to the console
* **Function** void console_show_unicode_key_codes() - show the unicode codes of pressed keys on console
* **Function** void generate_function_list_file() - generate the Lua Reference.md file on the ENGINE_DEFAULTS::DATA_PATH folder
* **Function** void print_text(string) - abstract print string to console
* **Function** void print_table_verbose(table [,int]) - print a lua table on console with verbose mode, second argument control if it should have indentation or not, pass a int as the indentation number
* **Function** void print_table(table [,int]) - print a lua table on console, second argument control if it should have indentation or not, pass a int as the indentation number
* **Function** void log_v(string) - log a verbose message to console
* **Function** void log_w(string) - log a warning message to console
* **Function** void log_c(string) - log a critical message to console,
* **Function** void print() - print a value on console, argument could be table, variable, string, bool, integer, float
* **Function** void log(mixed) - log a value on console, argument could be table, variable, string, bool, integer, float
* **Function** void register_function(string) - register an function on the LuaExportAPI for the console Prediction list, pass the function name as argument
* **Function** void engine_close([int error_code]) - close the engine from the console or game script code
* **Function** bool engine_is_running() - return if the engine is current running or not
* **Function** bool engine_is_loading_thread_done() - if the loading thread is done loading, meaning that the engine must be on the first game state(menu)
