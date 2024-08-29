#[repr(C)]
struct HiroObject {
    parent: *mut HiroObject,

    destroy: extern fn (*mut HiroObject),
}
