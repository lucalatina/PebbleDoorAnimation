#include <pebble.h>

static Window *window;
static TextLayer *text;

static GBitmap *image_doorA;
static GBitmap *image_doorB;

static BitmapLayer *doorA;
static BitmapLayer *doorB;

void on_animation_stopped(Animation *anim, bool finished, void *context){
    //Free the memory used by the Animation
    property_animation_destroy((PropertyAnimation*) anim);
}
 
void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration, int delay){
    PropertyAnimation *anim = property_animation_create_layer_frame(layer, start, finish);

    animation_set_duration((Animation*) anim, duration);
    animation_set_delay((Animation*) anim, delay);
     
    AnimationHandlers handlers = {
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);
     
    //Start animation
    animation_schedule((Animation*) anim);
}

void init(void) {
  
  image_doorA = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DOOR_A);
  image_doorB = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DOOR_B);
    
  window = window_create();
  //window_set_click_config_provider(window, (ClickConfigProvider) config_provider);
  window_stack_push(window, true /* Animated */);

  text = text_layer_create(GRect(0, 45, 144, 73));
  text_layer_set_text(text, "OPEN\nED");
  
  doorA = bitmap_layer_create(GRect(27, 30, 45, 90));
  bitmap_layer_set_bitmap(doorA,image_doorA);
  
  doorB = bitmap_layer_create(GRect(73, 30, 45, 90));
  bitmap_layer_set_bitmap(doorB,image_doorB);
  
  text_layer_set_font(text, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(text, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(doorA));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(doorB));
 
  GRect to_dest1 = GRect(0, 30, 45, 90);
  GRect to_dest2 = GRect(99, 30, 45, 90);
  
  GRect to_start1 = GRect(27, 30, 45, 90);
  GRect to_start2 = GRect(73, 30, 45, 90);
  
  animate_layer(bitmap_layer_get_layer(doorA), NULL, &to_dest1, 500, 0);
	animate_layer(bitmap_layer_get_layer(doorB), NULL, &to_dest2, 500, 0);
	animate_layer(bitmap_layer_get_layer(doorA), NULL, &to_start1, 0, 500);
	animate_layer(bitmap_layer_get_layer(doorB), NULL, &to_start2, 0, 500);
  
  animate_layer(bitmap_layer_get_layer(doorA), NULL, &to_dest1, 500, 550);
	animate_layer(bitmap_layer_get_layer(doorB), NULL, &to_dest2, 500, 550);
	animate_layer(bitmap_layer_get_layer(doorA), NULL, &to_start1, 0, 1050);
	animate_layer(bitmap_layer_get_layer(doorB), NULL, &to_start2, 0, 1050);
  
  animate_layer(bitmap_layer_get_layer(doorA), NULL, &to_dest1, 500, 1100);
	animate_layer(bitmap_layer_get_layer(doorB), NULL, &to_dest2, 500, 1100);
  //animate_layer(bitmap_layer_get_layer(doorA), NULL, &to_start1, 0, 1600);
	//animate_layer(bitmap_layer_get_layer(doorB), NULL, &to_start2, 0, 1600);
  
  //animate_layer(bitmap_layer_get_layer(doorA), NULL, &to_dest1, 500, 1650);
	//animate_layer(bitmap_layer_get_layer(doorB), NULL, &to_dest2, 500, 1650);
}

void deinit(void) {
  
  gbitmap_destroy(image_doorA);
  gbitmap_destroy(image_doorB);
  
  animation_unschedule_all();
  
  text_layer_destroy(text);
  bitmap_layer_destroy(doorA);
  bitmap_layer_destroy(doorB);
  
  window_destroy(window);
}

int main(void) {
  //test guthub integration
  init();
  app_event_loop();
  deinit();
}