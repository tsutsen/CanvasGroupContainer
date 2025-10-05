#include "canvas_group_container.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void CanvasGroupContainer::set_fit_margin(real_t p_fit_margin) {
    ERR_FAIL_COND(p_fit_margin < 0.0);
    
    fit_margin = p_fit_margin;
    RenderingServer::get_singleton()->canvas_item_set_canvas_group_mode(get_canvas_item(),RenderingServer::CANVAS_GROUP_MODE_TRANSPARENT,clear_margin,true,fit_margin,use_mipmaps);
    queue_redraw();
}

real_t CanvasGroupContainer::get_fit_margin() const {
    return fit_margin;
}

void CanvasGroupContainer::set_clear_margin(real_t p_clear_margin) {
    ERR_FAIL_COND(p_clear_margin < 0.0);
    
    clear_margin = p_clear_margin;
    RenderingServer::get_singleton()->canvas_item_set_canvas_group_mode(get_canvas_item(),RenderingServer::CANVAS_GROUP_MODE_TRANSPARENT,clear_margin,true,fit_margin,use_mipmaps);
    
    queue_redraw();
}

real_t CanvasGroupContainer::get_clear_margin() const {
    return clear_margin;
}

void CanvasGroupContainer::set_use_mipmaps(bool p_use_mipmaps) {
    use_mipmaps = p_use_mipmaps;
    RenderingServer::get_singleton()->canvas_item_set_canvas_group_mode(get_canvas_item(), RenderingServer::CANVAS_GROUP_MODE_TRANSPARENT, clear_margin, true, fit_margin, use_mipmaps);
}

bool CanvasGroupContainer::is_using_mipmaps() const {
    return use_mipmaps;
}

PackedStringArray CanvasGroupContainer::_get_configuration_warnings() const {
    PackedStringArray warnings = Control::_get_configuration_warnings();
    
    if (is_inside_tree()) {
        bool warned_about_ancestor_clipping = false;
        bool warned_about_canvasgroup_ancestor = false;
        Node *n = get_parent();
        while (n) {
            CanvasItem *as_canvas_item = Object::cast_to<CanvasItem>(n);
            if (!warned_about_ancestor_clipping && as_canvas_item && as_canvas_item->get_clip_children_mode() != CanvasItem::CLIP_CHILDREN_DISABLED) {
                warnings.push_back(vformat("Ancestor \"%s\" clips its children, so this CanvasGroupContainer will not function properly.", as_canvas_item->get_name()));
                warned_about_ancestor_clipping = true;
            }
            
            CanvasGroupContainer *as_canvas_group = Object::cast_to<CanvasGroupContainer>(n);
            if (!warned_about_canvasgroup_ancestor && as_canvas_group) {
                warnings.push_back(vformat("Ancestor \"%s\" is a CanvasGroupContainer, so this CanvasGroupContainer will not function properly.", as_canvas_group->get_name()));
                warned_about_canvasgroup_ancestor = true;
            }

			// Only break out early once both warnings have been triggered, so
			// that the user is aware of both possible reasons for clipping not working.
            if (warned_about_ancestor_clipping && warned_about_canvasgroup_ancestor) {
                break;
            }
            n = n->get_parent();
        }
    }
    
    return warnings;
}

void CanvasGroupContainer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_fit_margin", "fit_margin"), &CanvasGroupContainer::set_fit_margin);
    ClassDB::bind_method(D_METHOD("get_fit_margin"), &CanvasGroupContainer::get_fit_margin);
    
    ClassDB::bind_method(D_METHOD("set_clear_margin", "clear_margin"), &CanvasGroupContainer::set_clear_margin);
    ClassDB::bind_method(D_METHOD("get_clear_margin"), &CanvasGroupContainer::get_clear_margin);
    
    ClassDB::bind_method(D_METHOD("set_use_mipmaps", "use_mipmaps"), &CanvasGroupContainer::set_use_mipmaps);
    ClassDB::bind_method(D_METHOD("is_using_mipmaps"), &CanvasGroupContainer::is_using_mipmaps);
    
    ADD_GROUP("Tweaks", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fit_margin", PROPERTY_HINT_RANGE, "0,1024,1.0,or_greater,suffix:px"), "set_fit_margin", "get_fit_margin");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "clear_margin", PROPERTY_HINT_RANGE, "0,1024,1.0,or_greater,suffix:px"), "set_clear_margin", "get_clear_margin");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_mipmaps"), "set_use_mipmaps", "is_using_mipmaps");
}

// FIXME: Avoid `Parameter "canvas_item" is null` runtime error.
CanvasGroupContainer::CanvasGroupContainer() {
    set_fit_margin(10.0);
}

CanvasGroupContainer::~CanvasGroupContainer() {
    RenderingServer *rs = RenderingServer::get_singleton();
    if (rs && get_canvas_item().is_valid()) {
        rs->canvas_item_set_canvas_group_mode(get_canvas_item(), RenderingServer::CANVAS_GROUP_MODE_DISABLED);
    }
}