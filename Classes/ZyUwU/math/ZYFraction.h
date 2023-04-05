#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "cocos2d.h"
#include "ZyUwU/platform/ZYMacros.h"
#include "SmartAlgorithm.h"
#include "ZyUwU/base/ZYSupport.h"

NS_ZY_BEGIN

class Fraction
{
public:
    Fraction(int nNumerator, int nDenominator);
    Fraction(float fNum);
    Fraction(const Fraction &f);
public:
    /**
     * Shortcut this fraction
     */
    void shortCut();
    void log();
    Fraction clone(bool bIsShortCut = true);
    void reduceFractionToCommonDenominator(Fraction& f, bool bIsShortCut = true);

    void add(Fraction& f, bool bIsShortCut = true);
    void subtract(Fraction& f, bool bIsShortCut = true);
    void multiple(Fraction& f, bool bIsShortCut = true);
    void divide(Fraction& f, bool bIsShortCut = true);
    void replace(Fraction& f, bool bIsShortCut = true);
    void negate();
    float toFloat();
    std::string toString();
protected:
    void setMemory();
    void loadMemory();
    void autoValid();
public:
    /**
     * Create a new fraction then shortcut it
     *
     * @pragma nNumerator: the numerator of the fraction
     * @pragma nDenominator: the denominator of the fraction
     * @return The shortcut fraction
     */
    static Fraction fastShortCut(int nNumerator, int nDenominator);
    static Fraction clone(Fraction cCLone, bool bIsShortCut = true);
    static float fastPercent(float numerator);

    /**
     * Get the fraction in decimal
     *
     * @pragma f: the fraction to be converted
     * @return The fraction in decimal
     */
    static float toFloat(Fraction f);
    static float toFloat(int nNumerator, int nDenominator);

    static Fraction toFraction(float fNumber);

    /**
     * Adds the specified fractions and stores the result in dst.
     *
     * @pragma f1: The first fraction
     * @pragma f2: The second fraction
     * @pragma dst: A Fraction to store the result in
     * @pragma bIsShortCut: if you want to shortcut the fraction(dst)
     */
    static void add(Fraction& f1, Fraction& f2, Fraction *dst, bool bIsShortCut = true);
    static void subtract(Fraction& f1, Fraction& f2, Fraction *dst, bool bIsShortCut = true);
    static void multiple(Fraction& f1, Fraction& f2, Fraction *dst, bool bIsShortCut = true);
    static void divide(Fraction& f1, Fraction& f2, Fraction *dst, bool bIsShortCut = true);
public:
    inline void setNumerator(int nNumerator) {this->m_nNumerator = nNumerator;}
    inline void setDenominator(int nDenominator) {this->m_nDenominator = nDenominator;}
public:
    inline int getNumerator() {return this->m_nNumerator;}
    inline int getDenominator() {return this->m_nDenominator;}

    inline int getNumerator() const {return this->m_nNumerator;}
    inline int getDenominator() const {return this->m_nDenominator;}
public:
    /**
     *  Calculate the sum of this fraction with the given fraction
     *
     *  @Note: This does not modify this fraction
     *
     *  @pragma f: The fraction to add
     *  @return The fraction sum
     */
    Fraction operator+(Fraction& f);
    Fraction operator+=(Fraction& f);
    Fraction operator+(float f);
    Fraction operator+=(float f);

    Fraction operator-(Fraction& f);
    Fraction operator-=(Fraction& f);
    Fraction operator-(float f);
    Fraction operator-=(float f);

    Fraction operator-();

    void operator=(Fraction& f);

    Fraction operator*(Fraction& f);
    Fraction operator*=(Fraction& f);
    Fraction operator*(float f);
    Fraction operator*=(float f);

    Fraction operator/(Fraction& f);
    Fraction operator/=(Fraction& f);
    Fraction operator/(float f);
    Fraction operator/=(float f);

    bool operator==(Fraction& f);
    bool operator!=(Fraction& f);
    bool operator<(Fraction& f);
    bool operator>(Fraction& f);
    bool operator<=(Fraction& f);
    bool operator>=(Fraction& f);

    bool operator==(float f);
    bool operator!=(float f);
    bool operator<(float f);
    bool operator>(float f);
    bool operator<=(float f);
    bool operator>=(float f);
protected:
    int m_nNumerator, m_nDenominator;
private:
    static const Fraction DEFAULT;
private:
    bool isValid();
    bool isValid() const;
private:
    int p_nNumeratorMem, p_nDenominatorMem;
};

using Frac = Fraction;

NS_ZY_END
