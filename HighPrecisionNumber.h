//
// Created by AisingioroHao on 2022/10/28.
//

#ifndef BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_HIGHPRECISIONNUMBER_H
#define BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_HIGHPRECISIONNUMBER_H
#include<string>
class HighPrecisionNumber {
    bool is_positive= true;
    std::string interger,decimal;
public:
    HighPrecisionNumber(){}
    HighPrecisionNumber(const std::string& x) {
        int l = 0, r = x.size() - 1;
        if (x.size() && x[0] == '-') {
            is_positive = false;
            l = 1;
        }
        for (int i = l; i <= r; i++) {
            if (x[i] == '.') {
                interger = x.substr(l, i - l);//i-1-l+1
                decimal = x.substr(i + 1, r - i);//r-(i+1)+1
                break;
            }
        }
        if (interger.empty() && decimal.empty()) {
            interger = x.substr(l, r - l + 1);
        }
    }
    bool operator >(const HighPrecisionNumber& x)const {
        if (is_positive && !x.is_positive) {
            return true;
        }
        if (!is_positive && x.is_positive) {
            return false;
        }
        bool res;
        if (interger.size() > x.interger.size()) {
            res = true;
        } else if (interger.size() < x.interger.size()) {
            res = false;
        } else {
            if (interger > x.interger) {
                res = true;
            } else if (interger < x.interger) {
                res = false;
            } else {
                for (int i = 0; i < decimal.size(); i++) {
                    if (i < x.decimal.size()) {
                        if (decimal[i] > x.decimal[i]) {
                            res = true;
                            break;
                        } else if (decimal[i] < x.decimal[i]) {
                            res = false;
                            break;
                        }
                    } else {
                        res = true;
                        break;
                    }
                }
                return false;
            }
        }
        if (!is_positive) {
            res = !res;
        }
        return res;
    }
};


#endif //BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_HIGHPRECISIONNUMBER_H
