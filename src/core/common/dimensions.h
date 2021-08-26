#pragma once

template<typename T>
struct Dimensions {
    T width;
    T height;

    Dimensions(T width, T height)
            : width(width),
              height(height) {}

    template<typename K>
    Dimensions<K> cast() {
        return Dimensions<K>(static_cast<K>(width), static_cast<K>(height));
    }

    bool operator==(const Dimensions& other) const {
        return width == other.width && height == other.height;
    }
};

typedef Dimensions<int> Dimensions2i;
typedef Dimensions<float> Dimensions2f;



