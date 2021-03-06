#ifndef RECT_H
#define RECT_H

#include <vector>
#include <iostream>
#include <ostream>
#include <initializer_list>

/** 
 * @brief Rect模板类型.
 */
template<typename _Tp>
class Rect {
public:
    Rect() = delete;

    Rect(_Tp x, _Tp y, _Tp w, _Tp h) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }
    
    Rect(const Rect<_Tp>& other) {
        this->x = other.x;
        this->y = other.y;
        this->w = other.w;
        this->h = other.h;    
    }

    Rect(const std::vector<_Tp>& vec) {
        this->x = vec[0];
        this->y = vec[1];
        this->w = vec[2];
        this->h = vec[3];
    }

    ~Rect() = default;

    _Tp cx() {
        return x + w / 2;
    }

    _Tp cy() {
        return y + h / 2;
    }

    double aspect_ratio() const {
        return h / w;
    }

    _Tp area() const {
        return w * h;
    }

    double iou(const Rect<_Tp> &other) const {
        Rect<_Tp> inter = *this & other;
        double area_inter = inter.area();
        return  area_inter / (area() + other.area() - area_inter);
    }

    const std::vector<_Tp> xyxy() const {
        return {x, y, x + w, y + h};
    }

    const std::vector<_Tp> xywh() const {
        return {x, y, w, h};
    }

    const std::vector<_Tp> cxcywh() const {
        return {cx(), cy(), w, h};
    }

    template<typename _DstTp>
    Rect<_DstTp> cast() const {
        return cast_rect(*this);
    }

    _Tp x, y, w, h;
};

/** 
 * @brief 重载用于计算两个Rect交集的`&`运算符.
 */
template<typename _Tp>
inline Rect<_Tp> operator&(const Rect<_Tp>& a, const Rect<_Tp>& b) {
    auto inter_l = std::max(a.x, b.x);
    auto inter_t = std::max(a.y, b.y);
    auto inter_r = std::min(a.x + a.w, b.x + b.w);
    auto inter_b = std::min(a.y + a.h, b.y + b.h);
    auto inter_w = std::max(_Tp(0), inter_r - inter_l);
    auto inter_h = std::max(_Tp(0), inter_b - inter_t);

    return Rect<_Tp>(inter_l, inter_t, inter_w, inter_h);
}

/** 
 * @brief 重载用于标准输出的`<<`运算符.
 */
template<typename _Tp>
inline std::ostream& operator<<(std::ostream& os, const Rect<_Tp>& rect) {
	return os << "Rect(" <<
                 "x=" << rect.x << ", " << 
                 "y=" << rect.y << ", " << 
                 "w=" << rect.w << ", " <<
                 "h=" << rect.h <<
                 ")";
}

/** 
 * @brief 类型转换cast函数.
 */
template <typename _SrcTp, typename _DstTp>
inline Rect<_DstTp> cast_rect(const Rect<_SrcTp>& src) {
    return Rect<_DstTp>(_DstTp(src.x), _DstTp(src.y), _DstTp(src.w), _DstTp(src.h));
}

#endif