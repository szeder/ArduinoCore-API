/*
  Copyright (c) 2016 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include <inttypes.h>
#include <stdio.h> // for size_t

#include "String.h"
#include "Printable.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

class Print
{
  private:
    int write_error;

    size_t print_(const __FlashStringHelper *);
    size_t print_(const String &);
    size_t print_(const char[]);
    size_t print_(bool);
    size_t print_(char);
    size_t print_(unsigned char, int = DEC);
    size_t print_(int, int = DEC);
    size_t print_(unsigned int, int = DEC);
    size_t print_(long, int = DEC);
    size_t print_(unsigned long, int = DEC);
    size_t print_(long long, int = DEC);
    size_t print_(unsigned long long, int = DEC);
    size_t print_(float, int = 2);
    size_t print_(double, int = 2);
    size_t print_(const Printable&);

    size_t printNumber(unsigned long, uint8_t);
    size_t printULLNumber(unsigned long long, uint8_t);
    size_t printFloat(double, uint8_t);
  protected:
    void setWriteError(int err = 1) { write_error = err; }
  public:
    Print() : write_error(0) {}

    int getWriteError() { return write_error; }
    void clearWriteError() { setWriteError(0); }

    virtual size_t write(uint8_t) = 0;
    size_t write(const char *str) {
      if (str == NULL) return 0;
      return write((const uint8_t *)str, strlen(str));
    }
    virtual size_t write(const uint8_t *buffer, size_t size);
    size_t write(const char *buffer, size_t size) {
      return write((const uint8_t *)buffer, size);
    }

    size_t print(const __FlashStringHelper *fsh) { return print_(fsh); }
    size_t print(const String &s) { return print_(s); }
    size_t print(const char *s) { return print_(s); }
    size_t print(bool b) { return print_(b); }
    size_t print(char c) { return print_(c); }
    size_t print(unsigned char b, int base = DEC) { return print_(b, base); }
    size_t print(int n, int base = DEC) { return print_(n, base); }
    size_t print(unsigned int n, int base = DEC) { return print_(n, base); }
    size_t print(long n, int base = DEC) { return print_(n, base); }
    size_t print(unsigned long n, int base = DEC) { return print_(n, base); }
    size_t print(long long n, int base = DEC) { return print_(n, base); }
    size_t print(unsigned long long n, int base = DEC) { return print_(n, base); }
    size_t print(float n, int digits = 2) { return print_(n, digits); }
    size_t print(double n, int digits = 2) { return print_(n, digits); }
    size_t print(const Printable& x) { return print_(x); }

    size_t println(const __FlashStringHelper *);
    size_t println(const String &s);
    size_t println(const char[]);
    size_t println(bool);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(long long, int = DEC);
    size_t println(unsigned long long, int = DEC);
    size_t println(float, int = 2);
    size_t println(double, int = 2);
    size_t println(const Printable&);
    size_t println(void);

#if defined(__cpp_variadic_templates)
    template<typename T, typename... Args>
    size_t print(T first, Args... args) {
      return variadicPrint(first, args...);
    }

    template<typename T, typename... Args>
    size_t println(T first, Args... args) {
      return variadicPrint(first, args...) + println();
    }

  private:
    template<typename...Args>
    size_t variadicPrint(unsigned char b, int base, Args... args) {
      return print_(b, base) + variadicPrint(args...);
    }
    template<typename...Args>
    size_t variadicPrint(int n, int base, Args... args) {
      return print_(n, base) + variadicPrint(args...);
    }
    template<typename...Args>
    size_t variadicPrint(unsigned int n, int base, Args... args) {
      return print_(n, base) + variadicPrint(args...);
    }
    template<typename...Args>
    size_t variadicPrint(long n, int base, Args... args) {
      return print_(n, base) + variadicPrint(args...);
    }
    template<typename...Args>
    size_t variadicPrint(unsigned long n, int base, Args... args) {
      return print_(n, base) + variadicPrint(args...);
    }
    template<typename...Args>
    size_t variadicPrint(long long n, int base, Args... args) {
      return print_(n, base) + variadicPrint(args...);
    }
    template<typename...Args>
    size_t variadicPrint(unsigned long long n, int base, Args... args) {
      return print_(n, base) + variadicPrint(args...);
    }
    template<typename...Args>
    size_t variadicPrint(float n, int digits, Args... args) {
      return print_(n, digits) + variadicPrint(args...);
    }
    template<typename...Args>
    size_t variadicPrint(double n, int digits, Args... args) {
      return print_(n, digits) + variadicPrint(args...);
    }

    template<typename T, typename...Args>
    size_t variadicPrint(T first, Args... args) {
      return print_(first) + variadicPrint(args...);
    }

    size_t variadicPrint() {
      return 0;
    }
#endif
};

