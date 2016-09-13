<b>Slide Layer</b> is a custom layer for Pebble smartwatch with sliding effect - ideal for immitation of old mechanical digital watches

To use the library  add <code>#include <pebble-slide-layer/pebble-slide-layer.h></code> to your source.

![Rustics Slider](http://i.imgur.com/b7QPvC5.gif "Rustic Slider - Example of using Slide Layer")

General use flow:

1. Create SlideLayer add add it to parent layer
2. If desired - set properties (animation direction and duration)
3. Create and assign next bitmap (e.g. next digit image on the wacthface)  to slide in
4. Call slide animation function

New image will slide in and remain in place until slide animation function is called again

<hr>
<h3>Functions</h3>

<code>SlideLayer* slide_layer_create(GRect frame)</code> - creates slide layer and returns pointer to it. Parameter is GRect with coordinates and layer size, for example <code>SlideLayer* slide_layer = slide_layer_create(GRect(50, 50, 20, 40));</code>.

<code>void slide_layer_destroy(SlideLayer *slide_layer)</code> - destroys slde layer and frees memory.

<codeLayer* slide_layer_get_layer(SlideLayer *slide_layer);</code> - gets underlying Layer of the slide layer for basic manipulations such as adding to Window root layer or layer changing frame or bounds

<code>void slide_layer_set_animation_duration(int duration, SlideLayer *slide_layer);</code> - sets duration of the slide-in in milliseconds.

<code>void slide_layer_set_animation_direction(int direction, SlideLayer *slide_layer);</code> - set direction of the slide-in animation. Possible values:
<ul>
<li>SLIDE_TO_RIGHT</li>
<li>SLIDE_TO_TOP_RIGHT</li>
<li>SLIDE_TO_TOP</li>
<li>SLIDE_TO_TOP_LEFT</li>
<li>SLIDE_TO_LEFT</li>
<li>SLIDE_TO_BOTTOM_LEFT</li>
<li>SLIDE_TO_BOTTOM</li>
<li>SLIDE_TO_BOTTOM_RIGHT</li>
</ul>

```c
//Example usage

//creating slide layer
slide_layer = slide_layer_create(GRect(10, 30, 59, 75));
layer_add_child(window_get_root_layer(my_window), slide_layer_get_layer(slide_layer));
 
window_stack_push(my_window, true);
  
//setting slide layer params
slide_layer_set_animation_direction(SLIDE_TO_RIGHT, slide_layer);
slide_layer_set_animation_duration(1000, slide_layer);

//assigning next bitmap to slide in
slide_layer->gbitmap = gbitmap_create_with_resource(RESOURCE_ID_MY_IMG);

// animating layer
slide_layer_animate(slide_layer);
  
  
```



