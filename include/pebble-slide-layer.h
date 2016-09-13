#pragma once
#include <pebble.h>  


#define SLIDE_TO_RIGHT 0
#define SLIDE_TO_TOP_RIGHT 1
#define SLIDE_TO_TOP 2
#define SLIDE_TO_TOP_LEFT 3
#define SLIDE_TO_LEFT 4
#define SLIDE_TO_BOTTOM_LEFT 5
#define SLIDE_TO_BOTTOM 6
#define SLIDE_TO_BOTTOM_RIGHT 7


typedef struct {
	Layer       *layer;
  
  BitmapLayer *static_bitmap_layer;
  BitmapLayer *anim_bitmap_layer;

	PropertyAnimation *anim;
  GBitmap* gbitmap;
  
  // Animation duration & delay  
  int ANIMATION_DURATION;
  
  // Animation initial horizontal pozition: -1 = from left, 0 = center, 1 = from right
  int ANIM_START_X;
  
  // Animation initial vertical pozition: -1 = from top, 0 = center, 1 = from bottom
  int ANIM_START_Y;
  

} SlideLayer;


SlideLayer* slide_layer_create(GRect frame);

void slide_layer_destroy(SlideLayer *slide_layer);

Layer* slide_layer_get_layer(SlideLayer *slide_layer);

void slide_layer_animate(SlideLayer *slide_layer);

// sets animation direction based on passed in flag
void slide_layer_set_animation_direction(int direction, SlideLayer *slide_layer);

// sets animation duration
void slide_layer_set_animation_duration(int duration, SlideLayer *slide_layer);

