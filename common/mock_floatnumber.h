#ifndef FLOAT_NUMBER_H
#define FLOAT_NUMBER_H

class FloatNumber {
public:
    FloatNumber() = delete;
    
    explicit FloatNumber(float v)
     : value_(new float(v)) {}

    FloatNumber(const FloatNumber& other) {
        value_ = new float(*other.value_);
    }

    FloatNumber(FloatNumber&& other) {
        value_ = other.value_;
        other.value_= nullptr;
    }

    ~FloatNumber() {
        if (value_ != nullptr) {
            delete value_;
        }
    }

    FloatNumber& operator=(const FloatNumber& other) {
        if (this != &other) {
            *value_ = *other.value_;
        }
        return *this;
    }

    FloatNumber& operator=(FloatNumber&& other) {
        if (this != &other) {
            *value_ = *other.value_;
            other.value_= nullptr;
        }
        return *this;
    }

    FloatNumber& operator+=(const FloatNumber& other) {
        *value_ += *other.value_;
        return *this;
    }

    FloatNumber& operator-=(const FloatNumber& other) {
        *value_ -= *other.value_;
        return *this;
    }

    FloatNumber& operator*=(const FloatNumber& other) {
        *value_ *= *other.value_;
        return *this;
    }

    FloatNumber& operator/=(const FloatNumber& other) {
        *value_ /= *other.value_;
        return *this;
    }

    const float& value() const {
        return *value_;
    }

private:
    float* value_;
};

inline FloatNumber operator+(const FloatNumber& lv, const FloatNumber& rv) {
    return FloatNumber(lv.value() + rv.value());
}

inline FloatNumber operator-(const FloatNumber& lv, const FloatNumber& rv) {
    return FloatNumber(lv.value() - rv.value());
}

inline FloatNumber operator*(const FloatNumber& lv, const FloatNumber& rv) {
    return FloatNumber(lv.value() * rv.value());
}

inline FloatNumber operator/(const FloatNumber& lv, const FloatNumber& rv) {
    return FloatNumber(lv.value() / rv.value());
}

inline std::ostream& operator<<(std::ostream& os, const FloatNumber& fn) {
	return os << "FloatNumber(" << fn.value() << ")";
}

#endif