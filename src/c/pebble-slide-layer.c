#include <pebble.h>
#include "pebble-slide-layer.h"

// Animation delay  
#define ANIMATION_DELAY 0  
  

// animation stop callback 
void on_animation_stopped(Animation *anim, bool finished, SlideLayer *slide_layer)
{
  
   property_animation_destroy((PropertyAnimation*) anim);
  
   // destroying old bitmap in static layer if it exists
   GBitmap *old_bitmap = (GBitmap *)bitmap_layer_get_bitmap(slide_layer->static_bitmap_layer);
   if (old_bitmap) gbitmap_destroy(old_bitmap);
  
   // saving new bitmap in static layer
   bitmap_layer_set_bitmap(slide_layer->static_bitmap_layer, slide_layer->gbitmap);
}  
  
SlideLayer* slide_layer_create(GRect frame) {
  
  SlideLayer* slide_layer = malloc(sizeof(SlideLayer)); // allocating memory for side_layer items

	slide_layer->layer = layer_create(frame); // creating main layer

  
  // creating bitmap layers
  GRect bound = GRect(0, 0, frame.size.w, frame.size.h);
  slide_layer->static_bitmap_layer = bitmap_layer_create(bound);
  layer_add_child(slide_layer->layer, bitmap_layer_get_layer(slide_layer->static_bitmap_layer));
  slide_layer->anim_bitmap_layer = bitmap_layer_create(bound);
  layer_add_child(slide_layer->layer, bitmap_layer_get_layer(slide_layer->anim_bitmap_layer));
  
  // setting initial parameters
  slide_layer->ANIMATION_DURATION  = 1000;
  slide_layer->ANIM_START_X = -1;
  slide_layer->ANIM_START_Y = 0;
  
  return slide_layer;                    

}

void slide_layer_destroy(SlideLayer *slide_layer) {
  
  if (slide_layer->gbitmap) gbitmap_destroy(slide_layer->gbitmap);
  bitmap_layer_destroy(slide_layer->static_bitmap_layer);
  bitmap_layer_destroy(slide_layer->anim_bitmap_layer);
  layer_destroy(slide_layer->layer);
  free(slide_layer);

}

Layer* slide_layer_get_layer(SlideLayer *slide_layer){
  return slide_layer->layer;
}

void slide_layer_animate(SlideLayer *slide_layer){
  
    
    GRect finish = layer_get_bounds(slide_layer->layer);
    GRect start = GRect(finish.size.w * slide_layer->ANIM_START_X, finish.size.h * slide_layer->ANIM_START_Y, finish.size.w, finish.size.h);
    
    Layer *blayer = bitmap_layer_get_layer(slide_layer->anim_bitmap_layer);
    layer_set_frame(blayer, start);
    
    bitmap_layer_set_bitmap(slide_layer->anim_bitmap_layer, slide_layer->gbitmap);
    
    slide_layer->anim = property_animation_create_layer_frame(blayer, &start, &finish);
  
    AnimationHandlers handlers = {
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) slide_layer->anim, handlers, slide_layer);
    
    animation_set_curve((Animation*) slide_layer->anim, AnimationCurveLinear);
    animation_set_duration((Animation*) slide_layer->anim, slide_layer->ANIMATION_DURATION);
    animation_set_delay((Animation*) slide_layer->anim, ANIMATION_DELAY);
    animation_schedule((Animation*) slide_layer->anim);

}

// sets animation direction based on passed in flag
void slide_layer_set_animation_direction(int direction, SlideLayer *slide_layer) {
  switch (direction) {
    case SLIDE_TO_RIGHT: 
       slide_layer->ANIM_START_X = -1;
       slide_layer->ANIM_START_Y = 0;
       break;
    case SLIDE_TO_TOP_RIGHT:
       slide_layer->ANIM_START_X = -1;
       slide_layer->ANIM_START_Y = 1;
       break;    
    case SLIDE_TO_TOP: 
       slide_layer->ANIM_START_X = 0;
       slide_layer->ANIM_START_Y = 1;
       break;    
    case SLIDE_TO_TOP_LEFT: 
       slide_layer->ANIM_START_X = 1;
       slide_layer->ANIM_START_Y = 1;
       break;    
    case SLIDE_TO_LEFT: 
       slide_layer->ANIM_START_X = 1;
       slide_layer->ANIM_START_Y = 0;
       break;    
    case SLIDE_TO_BOTTOM_LEFT: 
       slide_layer->ANIM_START_X = 1;
       slide_layer->ANIM_START_Y = -1;
       break;    
    case SLIDE_TO_BOTTOM: 
       slide_layer->ANIM_START_X = 0;
       slide_layer->ANIM_START_Y = -1;
       break;    
    case SLIDE_TO_BOTTOM_RIGHT: 
       slide_layer->ANIM_START_X = -1;
       slide_layer->ANIM_START_Y = -1;
       break;
  }
  
}


// sets animation duration
void slide_layer_set_animation_duration(int duration, SlideLayer *slide_layer) {
    slide_layer->ANIMATION_DURATION = duration;
}

