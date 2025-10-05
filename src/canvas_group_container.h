#ifndef CANVAS_GROUP_CONTAINER_H
#define CANVAS_GROUP_CONTAINER_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/rendering_server.hpp>

namespace godot {

class CanvasGroupContainer : public Control {
    GDCLASS(CanvasGroupContainer, Control)

    real_t fit_margin = 10.0;
    real_t clear_margin = 10.0;
    bool use_mipmaps = false;

protected:
    static void _bind_methods();

public:
    void set_fit_margin(real_t p_fit_margin);
    real_t get_fit_margin() const;

    void set_clear_margin(real_t p_clear_margin);
    real_t get_clear_margin() const;

    void set_use_mipmaps(bool p_use_mipmaps);
    bool is_using_mipmaps() const;

    virtual PackedStringArray _get_configuration_warnings() const override;
    
    CanvasGroupContainer();
    ~CanvasGroupContainer();
};

} 

#endif