#include <inkview.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    iv_init();
    srand(time(NULL)); // seed the random number generator
    
    // Create the user interface
    iv_screen* screen = iv_default_screen();
    iv_canvas* canvas = iv_new_canvas();
    iv_set_color(canvas, BLACK);
    iv_set_font(canvas, iv_load_font_by_file("/usr/share/fonts/TTF/DejaVuSans.ttf"), 28);
    iv_clear_screen(canvas);
    iv_draw_text(canvas, "Random Number Generator", 0, 0);
    iv_draw_text(canvas, "Enter the minimum and maximum values:", 0, 50);
    iv_flip(screen, canvas);
    
    // Get the minimum value
    iv_text_input_params min_params = {0};
    min_params.prompt = "Minimum value:";
    min_params.flags = IV_TEXT_FLAG_MULTILINE | IV_TEXT_FLAG_NO_CANCEL;
    min_params.buffer = calloc(10, sizeof(char)); // allocate space for the user's input
    iv_text_input(canvas, &min_params);
    int min = atoi(min_params.buffer); // convert the user's input to an integer
    free(min_params.buffer); // free the memory allocated for the user's input
    
    // Get the maximum value
    iv_text_input_params max_params = {0};
    max_params.prompt = "Maximum value:";
    max_params.flags = IV_TEXT_FLAG_MULTILINE | IV_TEXT_FLAG_NO_CANCEL;
    max_params.buffer = calloc(10, sizeof(char)); // allocate space for the user's input
    iv_text_input(canvas, &max_params);
    int max = atoi(max_params.buffer); // convert the user's input to an integer
    free(max_params.buffer); // free the memory allocated for the user's input
    
    // Generate a random number within the given range
    int random_num = rand() % (max - min + 1) + min;
    
    // Display the random number to the user
    iv_clear_screen(canvas);
    iv_draw_text(canvas, "Your random number is:", 0, 0);
    char num_str[10];
    snprintf(num_str, 10, "%d", random_num); // convert the random number to a string
    iv_draw_text(canvas, num_str, 0, 50);
    iv_flip(screen, canvas);
    
    // Wait for the user to exit the application
    iv_wait_for_exit();
    
    // Clean up resources
    iv_free_canvas(canvas);
    iv_deinit();
    
    return 0;
}
